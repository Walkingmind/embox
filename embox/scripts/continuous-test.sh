#!/bin/bash
# bash is required by declare -A
# @file 
# @brief 
#
# @author  Anton Kozlov 
# @date    30.07.2013
#

# ATML == arch + template, i.e. x86/debug
ATML="$1"
ARCH=$(echo $ATML | cut -d \/ -f 1)

TESTABLES="x86/nonvga_debug mips/debug ppc/debug microblaze/petalogix \
	sparc/debug"
#"sparc/qemu" not supported due qemu bug 

if ! echo $TESTABLES | grep $ATML &>/dev/null; then 
	echo Template testing not supported
	exit 0
fi

TIMEOUT=15
EMKERNEL=./build/base/bin/embox
OUTPUT_FILE=./cont.out

do_it() {
	echo $@ | sh
}

declare -A atml2sim

QEMU_COMMON="-kernel $EMKERNEL -serial file:${OUTPUT_FILE} -display none"

atml2sim['x86/nonvga_debug']="qemu-system-i386 -m 512 -no-kvm $QEMU_COMMON"

atml2sim['mips/debug']="qemu-system-mips -M mipssim $QEMU_COMMON"

atml2sim['ppc/debug']="qemu-system-ppc -M virtex-ml507 -m 256 -net none \
	$QEMU_COMMON"

atml2sim['microblaze/petalogix']="qemu-system-microblaze \
	-M petalogix-s3adsp1800 -net none \
	$QEMU_COMMON"

atml2sim['sparc/qemu']="qemu-system-sparc -M leon3_generic -cpu LEON3 \
	$QEMU_COMMON"

atml2sim['sparc/debug']="tsim-leon3 -c $(dirname $0)/tsim_run.cmd $EMKERNEL \
	> $OUTPUT_FILE"

# qemu refuses to write if run with -serial stdio. So we buffer to file,
# cat it, and analyze

[ -f $OUTPUT_FILE ] && rm $OUTPUT_FILE
do_it timeout -s 9 $TIMEOUT "${atml2sim[$ATML]}"

cat $OUTPUT_FILE 

for success_pattern in "Started shell" "embox>"; do
	grep "$success_pattern" $OUTPUT_FILE &>/dev/null && exit 0
done

exit 1

