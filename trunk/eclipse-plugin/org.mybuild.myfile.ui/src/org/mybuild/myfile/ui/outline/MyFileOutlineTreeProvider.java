/*
 * generated by Xtext
 */
package org.mybuild.myfile.ui.outline;

import static org.mybuild.myfile.MyFilePackage.Literals.DEPENDS_MEMBER__MODULES;
import static org.mybuild.myfile.MyFilePackage.Literals.IMPORT__IMPORTED_NAMESPACE;
import static org.mybuild.myfile.MyFilePackage.Literals.MODEL__IMPORTS;
import static org.mybuild.myfile.MyFilePackage.Literals.PACKAGE__NAME;

import org.eclipse.emf.common.util.EList;
import org.eclipse.swt.graphics.Image;
import org.eclipse.xtext.ui.editor.outline.IOutlineNode;
import org.eclipse.xtext.ui.editor.outline.impl.DefaultOutlineTreeProvider;
import org.eclipse.xtext.ui.editor.outline.impl.DocumentRootNode;
import org.mybuild.myfile.AbstractFileListMember;
import org.mybuild.myfile.DependsMember;
import org.mybuild.myfile.FileName;
import org.mybuild.myfile.Import;
import org.mybuild.myfile.Model;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.Package;
import org.mybuild.myfile.Type;

/**
 * customization of the default outline structure
 * 
 */
public class MyFileOutlineTreeProvider extends DefaultOutlineTreeProvider {

	protected void _createChildren(DocumentRootNode parent, Model model) {
		Package pkg = model.getPackage();

		if (pkg != null) {
			createEStructuralFeatureNode(parent, pkg, PACKAGE__NAME,
					labelProvider.getImage(pkg), pkg.getName(), true);
		}

		EList<Import> imports = model.getImports();
		if (!imports.isEmpty()) {
			createEStructuralFeatureNode(parent, model, MODEL__IMPORTS,
					labelProvider.getImage(imports), "import declarations",
					false);
		}

		for (Type entity : model.getTypes()) {
			createNode(parent, entity);
		}
	}

	protected void _createNode(IOutlineNode parent, Import imp) {
		createEStructuralFeatureNode(parent, imp, IMPORT__IMPORTED_NAMESPACE,
				labelProvider.getImage(imp), imp.getImportedNamespace(), true);
	}

	protected void _createNode(IOutlineNode parent, DependsMember depends) {
		Image image = labelProvider.getImage(depends);

		for (Module module : depends.getModules()) {
			String name = module.getName();
			if (name != null) {
				createEStructuralFeatureNode(parent, depends, DEPENDS_MEMBER__MODULES,
						image, name, true);
			}
		}
	}

	protected void _createNode(IOutlineNode parent,
			AbstractFileListMember filesMember) {
		for (FileName filename : filesMember.getFiles()) {
			createNode(parent, filename);
		}
	}

}