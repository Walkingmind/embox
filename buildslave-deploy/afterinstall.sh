
SUDO=sudo
APT_GET_INSTALL="$SUDO apt-get -qy install"

enable_autostart() {
	for i; do
		$SUDO update-rc.d $i enable
	done
}

install_bootstrap() {
	$APT_GET_INSTALL openssh-server vim subversion build-essential libncurses5-dev gcc-multilib g++-multilib texinfo
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
	INSTALL_CROSSCOMPILERS_PATH="/opt"
	pushd crosstool
	PATH_ADD=""
	for i in *-toolchain.tar.*; do
		$SUDO tar -C $INSTALL_CROSSCOMPILERS_PATH -axf $i
		PATH_ADD=$PATH_ADD":${INSTALL_CROSSCOMPILERS_PATH}/${i%.tar.*}/bin"
	done
	popd

	$SUDO ./write_compiler_path.sh "$PATH_ADD" /etc/profile.d/compiler_path.sh
}

install_qemu() {
	$APT_GET_INSTALL qemu-system
}

do_devel() {
	install_bootstrap
	download_crosstool
	do_crosscompilers
	install_crosscompilers
	install_qemu
}

do_buildslave_sudo() {
	$SUDO usermod -a -G sudo buildbot
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo "buildbot now is a member of sudo group."
	echo "Allow the group to execute commands without password prompt"
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
