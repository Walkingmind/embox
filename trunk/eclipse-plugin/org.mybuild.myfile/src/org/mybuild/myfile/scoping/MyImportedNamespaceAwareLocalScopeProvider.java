package org.mybuild.myfile.scoping;

import static com.google.common.collect.Lists.newLinkedList;

import java.util.List;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EReference;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.xtext.naming.QualifiedName;
import org.eclipse.xtext.scoping.IScope;
import org.eclipse.xtext.scoping.impl.ImportNormalizer;
import org.eclipse.xtext.scoping.impl.ImportedNamespaceAwareLocalScopeProvider;
import org.mybuild.myfile.Model;
import org.mybuild.myfile.Package;

/**
 * @author Eldar Abusalimov
 */
public class MyImportedNamespaceAwareLocalScopeProvider extends
		ImportedNamespaceAwareLocalScopeProvider {

	@Override
	protected IScope getResourceScope(Resource res, EReference reference) {
		IScope globalScope = getGlobalScope(res, reference);
		List<ImportNormalizer> normalizers = newLinkedList();

		EObject context = res.getContents().get(0);
		Package pkg = ((Model) context).getPackage();

		if (pkg != null) {
			normalizers.add(createImportedNamespaceResolver(pkg.getName()
					+ ".*", isIgnoreCase(reference)));
		}
		normalizers.add(new ImportNormalizer(QualifiedName.create("mybuild",
				"lang"), true, false));

		globalScope = createImportScope(globalScope, normalizers, null,
				reference.getEReferenceType(), isIgnoreCase(reference));
		return getResourceScope(globalScope, context, reference);
	}

	@Override
	protected boolean isRelativeImport() {
		return false;
	}

}
