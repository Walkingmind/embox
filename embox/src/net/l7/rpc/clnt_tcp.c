/**
 * @file
 * @brief
 * @date 04.06.2012
 * @author Andrey Gazukin
 * @author Ilia Vaprol
 */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <net/socket.h>
#include <net/ksocket.h>
#include <unistd.h>

#include <net/rpc/clnt.h>
#include <net/rpc/rpc.h>
#include <net/rpc/rpc_msg.h>
#include <net/rpc/auth.h>
#include <net/rpc/pmap.h>

#define TCP_MSG_MAX_SZ 1024

static int readtcp(struct client *clnt, char *buf, size_t len);
static int writetcp(struct client *clnt, char *buf, size_t len);

static const struct clnt_ops clnttcp_ops;

struct client * clnttcp_create(struct sockaddr_in *raddr, uint32_t prognum,
		uint32_t versnum, struct socket **psock, unsigned int sendsz, unsigned int recvsz) {
	int ret;
	struct client *clnt;
	struct auth *ath;
	struct socket *sock;
	struct sockaddr_in sin;

	assert((raddr != NULL) && (psock != NULL));

	clnt = (struct client *)malloc(sizeof *clnt), ath = authnone_create();
	if ((clnt == NULL) || (ath == NULL)) {
		rpc_create_error.stat = RPC_SYSTEMERROR;
		rpc_create_error.err.extra.error = ENOMEM;
		goto exit_with_error;
	}

	memcpy(&sin, raddr, sizeof *raddr);
	if (sin.sin_port == 0) {
		sin.sin_port = htons(pmap_getport(raddr, prognum, versnum, IPPROTO_TCP));
		if (sin.sin_port == 0) {
			goto exit_with_error;
		}
	}

	sock = NULL;
	assert(*psock == NULL);
	if ((0 != (ret = ksocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock)))
			|| (0 != (ret = kconnect(sock, (struct sockaddr *)&sin, sizeof sin, 0)))) {
		rpc_create_error.stat = RPC_SYSTEMERROR;
		rpc_create_error.err.extra.error = -ret;
		if (sock != NULL) {
			ksocket_close(sock);
		}
		goto exit_with_error;
	}

	/* Fill client structure */
	clnt->ops = &clnttcp_ops;
	clnt->sock = sock;
	clnt->ath = ath;
	clnt->prognum = prognum;
	clnt->versnum = versnum;
	clnt->extra.tcp.sendsz = sendsz;
	clnt->extra.tcp.recvsz = recvsz;

	*psock = sock;

	return clnt;
exit_with_error:
	auth_destroy(ath);
	free(clnt);
	return NULL;
}

static enum clnt_stat clnttcp_call(struct client *clnt, uint32_t procnum,
		xdrproc_t inproc, char *in, xdrproc_t outproc, char *out,
		struct timeval timeout) {
	struct xdr xstream;
	struct rpc_msg msg_reply, msg_call;

	assert((clnt != NULL) && (inproc != NULL));

	msg_call.xid = (uint32_t)rand();
	msg_call.type = CALL;
	msg_call.b.call.rpcvers = RPC_VERSION;
	msg_call.b.call.prog = clnt->prognum;
	msg_call.b.call.vers = clnt->versnum;
	msg_call.b.call.proc = procnum;
	memcpy(&msg_call.b.call.cred, &clnt->ath->cred, sizeof clnt->ath->cred);
	memcpy(&msg_call.b.call.verf, &clnt->ath->verf, sizeof clnt->ath->verf);

	xdrrec_create(&xstream, clnt->extra.tcp.sendsz, clnt->extra.tcp.recvsz,
			(char *)clnt, (xdrrec_hnd_t)readtcp, (xdrrec_hnd_t)writetcp);

	xstream.oper = XDR_ENCODE;

	clnt->err.status = RPC_SUCCESS;
	if (!xdr_rpc_msg(&xstream, &msg_call)
			|| !(*inproc)(&xstream, in)) {
		if (clnt->err.status == RPC_SUCCESS) {
			clnt->err.status = RPC_CANTENCODEARGS;
		}
		goto exit_with_status;
	}

	if (!xdrrec_endofrecord(&xstream, 1)) {
		clnt->err.status = RPC_CANTSEND;
		goto exit_with_status;
	}

	xstream.oper = XDR_DECODE;

	msg_reply.b.reply.r.accepted.d.result.decoder = outproc;
	msg_reply.b.reply.r.accepted.d.result.param = out;
	if (!xdr_rpc_msg(&xstream, &msg_reply)) {
		clnt->err.status = RPC_CANTDECODERES;
		goto exit_with_status;
	}

	clnt->err.status = RPC_SUCCESS;
exit_with_status:
	xdr_destroy(&xstream);
	return clnt->err.status;
}

static void clnttcp_geterr(struct client *clnt, struct rpc_err *perr) {
	assert((clnt != NULL) && (perr != NULL));

	memcpy(perr, &clnt->err, sizeof clnt->err);
}

static void clnttcp_destroy(struct client *clnt) {
	assert(clnt != NULL);

	auth_destroy(clnt->ath);
	ksocket_close(clnt->sock);
	free(clnt);
}

static int readtcp(struct client *clnt, char *buff, size_t len) {
	int ret;
	struct msghdr msg;
	struct iovec iov;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;

	iov.iov_base = (void *)buff;
	iov.iov_len = len;

	ret = krecvmsg(clnt->sock, &msg, 0);
	if (ret != 0) {
		clnt->err.status = RPC_CANTRECV;
		clnt->err.extra.error = -ret;
		return -1;
	}

	return iov.iov_len;
}

static int writetcp(struct client *clnt, char *buff, size_t len) {
	int ret;
	struct msghdr msg;
	struct iovec iov;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;

	iov.iov_base = (void *)buff;
	iov.iov_len = len;

	ret = ksendmsg(clnt->sock, &msg, 0);
	if (ret != 0) {
		clnt->err.status = RPC_CANTSEND;
		clnt->err.extra.error = -ret;
		return -1;
	}

	return iov.iov_len;
}

static const struct clnt_ops clnttcp_ops = {
		.call = clnttcp_call,
		.geterr = clnttcp_geterr,
		.destroy = clnttcp_destroy
};
