#include <lib/service/script.h>

#include <string.h>

int service_script_init (struct sevice_script * srv_scrpt, const char * script_file) {
	int var, i;
	if (!srv_scrpt || !script_file) {
		return -1;
	}

	script->vars_count = 0;

	for (var = 0; var < SERVICE_MAX_VARS; var++) {
		srv_scrpt->vars[var].name[0] = '\0';
		srv_scrpt->vars[var].value[0] = '\0';
		srv_scrpt->vars[var].type = SRV_VAR_NAN;
	}

	strncpy(srv_scrpt->script_file, script_file, SERVICE_FILE_NAME_LEN - 1);
	
	return 0;
}

int service_script_preprocess_file (struct service_script * srv_scrpt, const char * out_file_name, struct variable vars[]) {
	return 0;
}

int service_script_get_variable_id (struct service_script * srv_scrpt, const char * name) {
	int i;
	for (i = 0; i < VAR_COUNT; i++) {
		if (!strcmp(vars[i].name, name))
			return i;
	}
	return -1;
}

char * service_script_get_variable_string (struct service_script * srv_scrpt, const char * name) {
	int id = service_script_get_variable_id(srv_scrpt, name);
	if (id < 0) {
		return NULL;
	} else {
		return srv_scrpt->vars[id].value;
	}
}

void service_script_set_variable_string (struct service_script * srv_scrpt, const char * name, const char * val) {
	int id;
	id = service_script_get_variable_id(srv_scrpt, name);
	strncpy(srv_scrpt->vars[id].value, val, SERVICE_VAR_LEN);
	srv_scrpt->vars.type = SRV_VAR_STRING;
}

static int service_script_get_hex(char val) {
	return (val >= '0' && val <= '9') ? val - '0' : 
			(val >= 'A' && val <= 'F') ? val -'A' : 
			(val >= 'a' && val <= 'f') ? val -'a' : 0;
}

static unsigned int service_script_get_char_from_hexcode (char * val, int len) {
	int i;
	unsigned int res = 0;
	for (i = 0; i < len; i++) {
		res += service_script_get_hex(val[i]) * (0x10 << (i * 4));
	}
	return res;
}

int service_script_get_vars_from_query (struct service_script * srv_scrpt, const char * query) {
	int i, qptr, len;
	char * dump;

	for (i = 0; i < VAR_COUNT; i++) {
		vars[i].name[0] = '\0';
		vars[i].value[0] = '\0';
	}

	if (query) {
		qptr = 0;
		for (i = 0; query[qptr] && i < VAR_COUNT; i++) {
			dump = vars[i].name;
			len = 0;
			for (; query[qptr] && query[qptr] != '&'; qptr++) {
				if (query[qptr] == '=') {
					dump[len] = '\0';
					dump = vars[i].value;
					len = 0;
				} else if (query[qptr] == '%') {
					if (query[qptr+1] != '\0' && query[qptr+1] != '&' && query[qptr+2] != '\0' && query[qptr+2] != '&') {
						dump[len] = service_script_get_char_from_hexcode(query+qptr+1, 2);
						len++;
						qptr += 2;
					}
				} else {
					if (len < VAR_LEN - 1) {
						dump[len] = query[qptr];
						len++;
					} else if (len == VAR_LEN - 1) {
						dump[len] = '\0';
					}
				}
				if (query[qptr+1] == '\0' || query[qptr+1] == '&') {
					dump[len] = '\0';
				}
			}
			if (query[qptr] == '&')
				qptr++;
		}
	}
	return 0;
}

int service_script_get_vars_count(struct service_script * srv_scrpt) {
	return 0;
}
int service_script_get_vars_left(struct service_script * srv_scrpt) {
	return 0;
}
