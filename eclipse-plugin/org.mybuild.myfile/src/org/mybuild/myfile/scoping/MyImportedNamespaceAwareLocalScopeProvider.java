package org.mybuild.myfile.scoping;

import static java.util.Collections.singletonList;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EReference;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.xtext.naming.QualifiedName;
import org.eclipse.xtext.scoping.IScope;
import org.eclipse.xtext.scoping.impl.ImportNormalizer;
import org.eclipse.xtext.scoping.impl.ImportedNamespaceAwareLocalScopeProvider;
import org.mybuild.myfile.myFile.Model;
import org.mybuild.myfile.myFile.Package;

/**
 * @author Eldar Abusalimov
 */
public class MyImportedNamespaceAwareLocalScopeProvider extends
		ImportedNamespaceAwareLocalScopeProvider {

	@Override
	protected IScope getResourceScope(Resource res, EReference reference) {
		EObject context = res.getContents().get(0);
		Package pkg = ((Model) context).getPackage();

		IScope globalScope = getGlobalScope(res, reference);

		if (pkg != null) {
			ImportNormalizer ownNamespaceNormalizer = new ImportNormalizer(
					QualifiedName.create(pkg.getName()), true,
					isIgnoreCase(reference));

			globalScope = createImportScope(globalScope,
					singletonList(ownNamespaceNormalizer), null,
					reference.getEReferenceType(), isIgnoreCase(reference));
		}

		return getResourceScope(globalScope, context, reference);
	}

}
