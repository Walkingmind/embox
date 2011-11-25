package org.mybuild.myfile.naming;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.xtext.naming.DefaultDeclarativeQualifiedNameProvider;
import org.eclipse.xtext.naming.QualifiedName;
import org.mybuild.myfile.myFile.Model;
import org.mybuild.myfile.myFile.Package;

public class MyQualifiedNameProvider extends
		DefaultDeclarativeQualifiedNameProvider {

	@Override
	public QualifiedName getFullyQualifiedName(EObject obj) {
		QualifiedName name = super.getFullyQualifiedName(obj);

		if (name == null) {
			return null;
		}

		Resource resource = obj.eResource();
		EObject context = resource.getContents().get(0);
		Package pkg = ((Model) context).getPackage();

		if (pkg != null) {
			name = getConverter().toQualifiedName(pkg.getName()).append(name);
		}

		return name;
	}

}
