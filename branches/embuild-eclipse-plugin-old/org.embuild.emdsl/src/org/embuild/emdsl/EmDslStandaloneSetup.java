package org.embuild.emdsl;


/**
 * Initialization support for running Xtext languages without equinox extension
 * registry
 */
public class EmDslStandaloneSetup extends EmDslStandaloneSetupGenerated {

	public static void doSetup() {
		new EmDslStandaloneSetup().createInjectorAndDoEMFRegistration();
	}
}
