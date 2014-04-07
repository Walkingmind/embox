
package org.mybuild.configfile;

/**
 * Initialization support for running Xtext languages 
 * without equinox extension registry
 */
public class ConfigFileStandaloneSetup extends ConfigFileStandaloneSetupGenerated{

	public static void doSetup() {
		new ConfigFileStandaloneSetup().createInjectorAndDoEMFRegistration();
	}
}

