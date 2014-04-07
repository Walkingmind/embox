
package org.mybuild.myfile;

/**
 * Initialization support for running Xtext languages 
 * without equinox extension registry
 */
public class MyFileStandaloneSetup extends MyFileStandaloneSetupGenerated{

	public static void doSetup() {
		new MyFileStandaloneSetup().createInjectorAndDoEMFRegistration();
	}
}

