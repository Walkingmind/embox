package org.mybuild.myfile.validation;

public interface IssueCodes {

	String PREFIX = "org.mybuild.myfile.validation.IssueCodes.";

	String INVALID_MODULE_NAME = PREFIX + "InvalidModuleName";

	String DUPLICATE_FILE_NAME = PREFIX + "DuplicateFileName";

	String WHITESPACE_IN_FILE_NAME = PREFIX + "WhitespaceInFileName";

	String FILE_DOES_NOT_EXIST = PREFIX + "FileDoesNotExist";

}
