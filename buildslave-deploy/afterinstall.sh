
TSIM_URL="http://www.gaisler.com/anonftp/tsim/tsim-eval-2.0.32.tar.gz"
QEMU_LINARO_URL="https://launchpad.net/qemu-linaro/trunk/2014.01/+download/qemu-linaro-1.7.0-2014.01.tar.gz"

INSTALL_PATH="/opt"

SUDO=sudo
APT_GET_INSTALL="$SUDO apt-get -qy install"

__path_add=""
path_add() {
	__path_add="$__path_add:$1"
}

__path_prepend=""
path_prepend() {
	__path_prepend="$1:$__path_prepend"
}

enable_autostart() {
	for i; do
		$SUDO update-rc.d $i enable
	done
}

install_tsim() {
	INSTALL_TSIM="$INSTALL_PATH/tsim-eval"

	wget -c $TSIM_URL
	bname=$(basename $TSIM_URL)

	tar -axf $bname

	$SUDO mkdir $INSTALL_TSIM
	$SUDO cp ./tsim-eval/tsim/linux-x64/tsim-leon3 $INSTALL_TSIM

	path_add $INSTALL_TSIM
}

install_bootstrap() {
	$APT_GET_INSTALL openssh-server vim subversion build-essential libncurses5-dev gcc-multilib g++-multilib texinfo flex bison
	$APT_GET_INSTALL cmake u-boot-tools libgmp-dev libmpfr-dev libmpc-dev #build dependencies for embox
	install_tsim
	enable_autostart ssh
}

download_crosstool() {
	svn co http://embox.googlecode.com/svn/trunk/crosstool crosstool
}

build_crosscompiler() {
	pushd crosstool
	./crosstool.sh $1
	popd
}

do_crosscompilers() {
	for i in arm microblaze mips powerpc sparc; do
		build_crosscompiler $i
	done
}

install_crosscompilers() {
	pushd crosstool
	for i in *-toolchain.tar.*; do
		$SUDO tar -C $INSTALL_PATH -axf $i
		path_add "$INSTALL_PATH/${i%.tar.*}/bin"
	done
	popd

}

write_path() {
	$SUDO ./write_compiler_path.sh "$__path_prepend" "$__path_add" /etc/profile.d/compiler_path.sh
	$SUDO cp ./sbin.sh /etc/profile.d/
	$SUDO chmod a+x /etc/profile.d/sbin.sh
}

install_qemu() {
	$APT_GET_INSTALL qemu-system
}

install_qemu_linaro_arm() {
	INSTALL_QEMU_LINARO_PATH=$INSTALL_PATH/qemu-linaro

	$APT_GET_INSTALL zlib1g-dev libglib2.0-dev libpixman-1-dev libfdt-dev

	wget -c $QEMU_LINARO_URL
	bname=$(basename $QEMU_LINARO_URL)
	tar -axf $bname
	dname=${bname%.tar.*}
	pushd $dname

	
	./configure --target-list=arm-softmmu
	make
	sudo make DESTDIR=$INSTALL_QEMU_LINARO_PATH install

	path_prepend $INSTALL_QEMU_LINARO_PATH/usr/local/bin

	popd
}

do_devel() {
	install_bootstrap
	download_crosstool
	do_crosscompilers
	install_crosscompilers
	install_qemu
	install_qemu_linaro_arm

	write_path
}

do_buildslave_sudo() {
	$SUDO usermod -a -G sudo buildbot
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo "buildbot now is a member of sudo group."
	echo "Allow the group to execute commands without password prompt."
	echo "Also, adjust secure path to \"Defaults !secure_path\""
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo Press any key to continue

	$SUDO visudo
}

do_buildslave_start() {
	$SUDO /etc/init.d/buildslave start
}

do_buildslave() {
	$APT_GET_INSTALL buildbot-slave
	$SUDO cp buildslave.sample /etc/default/buildslave	

	pushd /var/lib/buildbot/slaves/
	if [ ! $MASTER_ADDR ] || [ ! $SLAVE_NAME ] || [ ! $SLAVE_PASSWORD ]; then
		echo "some parameter(s) are missing"
		exit 1
	fi
	$SUDO buildslave create-slave embox $MASTER_ADDR $SLAVE_NAME $SLAVE_PASSWORD
	$SUDO chown buildbot -R embox
	popd

	do_buildslave_sudo

	enable_autostart buildslave
	do_buildslave_start
}

do_devel
do_buildslave
