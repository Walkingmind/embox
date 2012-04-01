package org.mybuild.configfile.scoping;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.mybuild.configfile.configFile.ConfigFileModel;
import org.mybuild.myfile.Package;
import org.mybuild.myfile.scoping.MyImportedNamespaceAwareLocalScopeProvider;

/**
 * @author Eldar Abusalimov
 */
public class ConfigFileImportedNamespaceAwareLocalScopeProvider extends
		MyImportedNamespaceAwareLocalScopeProvider {

	protected String getOwnPackageName(Resource res) {
		EObject context = res.getContents().get(0);
		Package pkg = ((ConfigFileModel) context).getPackage();
		return pkg == null ? null : pkg.getName();
	}

}
