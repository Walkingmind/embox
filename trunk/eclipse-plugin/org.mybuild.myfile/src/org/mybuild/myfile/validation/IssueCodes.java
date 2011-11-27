package org.mybuild.myfile.validation;

public interface IssueCodes {

	String PREFIX = IssueCodes.class.getName() + ".";

	String INVALID_MODULE_NAME = PREFIX + "InvalidModuleName";

	String DUPLICATE_FILE_NAME = PREFIX + "DuplicateFileName";

	String WHITESPACE_IN_FILE_NAME = PREFIX + "WhitespaceInFileName";

}
