#!/bin/bash

ROOT_DIR=.
BASE_DIR=$ROOT_DIR
DATA_DIR=$(dirname $0)

PID_FILE=$BASE_DIR/qemu_bg.pid

CONT_BASE=$ROOT_DIR/scripts/continuous
CONT_RUN=$CONT_BASE/run.sh

EXPECT_TESTS_BASE=$ROOT_DIR/scripts/expect

EMBOX_IP=10.0.2.16
HOST_IP=10.0.2.10

test_case_target_should_reply_to_ping() {
	ping $EMBOX_IP -c 4
	test_retcode
}

test_case_correct_index_html_should_be_downloaded() {

	wget $EMBOX_IP 
	test_retcode

	diff -q index.html $DATA_DIR/index.html
	test_retcode

	rm index.html
}

#test_case_ssh_should_be_able_to_execute_command_and_show_output() {
#}

test_case_snmp_should_reply() {
	str=$(snmpget -v 1 -c public $EMBOX_IP 1.3.6.1.2.1.2.2.1.6.2)
	test_retcode

	echo $str | grep "AA BB CC DD EE 02" >/dev/null
	test_retcode
}

test_case_interactive_tests_should_success() {
	runtest $EXPECT_TESTS_BASE/telnet.exp \
		$EXPECT_TESTS_BASE/ntpdate.exp
	test_retcode

	cat testrun.log
}

#test_case_ftp_should_be_able_to_upload_a_file() {
#}

test_suite_code=0

test_code=0
test_desc=""
test_begin() {
	test_desc=$1
	test_code=0
}

test_retcode() {
	if [ 0 -ne $? ]; then
		test_suite_code=1
		test_code=1

		echo "Test code is not 0"
	fi
}

test_end() {

	if [ 0 -ne $test_code ]; then
		echo Test case \"$test_desc\" failed
	else
		echo Test case \"$test_desc\" OK
	fi
}

determ_dns() {
	cat /etc/resolv.conf | sed -n 's/nameserver[\ \t]\+//p' | head -n 1 | sed 's/\(127\.0\.0\.1\|localhost\)/$HOST_IP/'
}

tap_up() {
	sudo /sbin/ip tuntap add mode tap tap0
	sudo /sbin/ifconfig tap0 10.0.2.10 dstaddr 10.0.2.0 netmask 255.255.255.0 down
	sudo /sbin/ifconfig tap0 hw ether aa:bb:cc:dd:ee:ff up
	sudo /sbin/ifconfig tap0 inet6 del fe80::a8bb:ccff:fedd:eeff/64
	sudo /sbin/ifconfig tap0 inet6 add fe80::10:0:2:10/64
	sudo service isc-dhcp-server start
}

tap_down() {
	sudo service isc-dhcp-server stop
	sudo /sbin/ip tuntap del mode tap tap0
}

sed -i "s/CONTINIOUS_RUN_DNS_SERVER/$(determ_dns)/" conf/mods.config
make >/dev/null 2>/dev/null

tap_up

export AUTOQEMU_START_SCRIPT=no
export AUTOQEMU_STOP_SCRIPT=no

export CONTINIOUS_RUN_TIMEOUT=60
$CONT_RUN generic/qemu_bg "" $PID_FILE
if [ 0 -ne $? ]; then
	run_failed=1
fi

if [ ! $run_failed ]; then
	case_prefix=test_case_
	for test in $(declare -F | cut -d \  -f 3 | grep "^$case_prefix"); do 
		test_begin "$(echo ${test#$case_prefix} | tr _ \ )"
		${test}
		test_end
	done

	$CONT_RUN generic/qemu_bg_kill "" $PID_FILE
	rm $PID_FILE
else
	test_suite_code=1

fi

tap_down

exit $test_suite_code
