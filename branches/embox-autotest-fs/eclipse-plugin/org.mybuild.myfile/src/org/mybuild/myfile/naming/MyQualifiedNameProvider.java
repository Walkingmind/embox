package org.mybuild.myfile.naming;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.xtext.naming.DefaultDeclarativeQualifiedNameProvider;
import org.eclipse.xtext.naming.QualifiedName;
import org.mybuild.myfile.Model;
import org.mybuild.myfile.Package;

/**
 * @author Eldar Abusalimov
 */
public class MyQualifiedNameProvider extends
		DefaultDeclarativeQualifiedNameProvider {

	@Override
	public QualifiedName getFullyQualifiedName(EObject obj) {
		if (obj instanceof Model) {
			Model model = (Model) obj;
			Package pkg = model.getPackage();
			return pkg != null ? getConverter().toQualifiedName(pkg.getName())
					: null;
		}

		if (obj instanceof Package) {
			Package pkg = (Package) obj;
			return getConverter().toQualifiedName(pkg.getName());
		}

		return super.getFullyQualifiedName(obj);
	}

}
