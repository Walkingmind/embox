$_MODS += test
$_SRCS-test += test.c
$_USES-test += libframework.a

$_BRIEF-test = Interacts with Embox testing framework

define $_DETAILS-test
	NAME
		test - an interface to Embox testing framework
	SYNOPSIS
		test [-h] [-n <test_nr>] [-t <test_name>]
	DESCRIPTION
		Shows tests available in the system and runs the specified ones
	OPTIONS
		-t test_name
			Run a test by its name
		-n test_nr
			Run a test with the specified number
	
		If no option is specified then the command shows the list of available
		tests.
	AUTHORS
		Alexey Fomin
		Eldar Abusalimov
endef
