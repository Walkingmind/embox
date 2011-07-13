package org.embuild.emdsl.validation;

import java.awt.List;
import java.io.File;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.xtext.validation.Check;
import org.embuild.emdsl.emDsl.EmDslPackage;
import org.embuild.emdsl.emDsl.Model;
import org.embuild.emdsl.emDsl.Module;

public class EmDslJavaValidator extends AbstractEmDslJavaValidator {

	@Check
	public void checkAllModulesStartsWithCapital(Module m) {
		if (!Character.isUpperCase(m.getName().charAt(0))) {
			warning("Name should start with a capital",
					EmDslPackage.Literals.MODULE__NAME);
		}
	}

	@Check
	public void checkModuleNameEqualsFileName(Module m) {
		URI uri = m.eResource().getURI();
		String name = uri.toPlatformString(true);
		
		name = name.substring(name.lastIndexOf('/') + 1, name.lastIndexOf('.'));

		if (!name.equals(m.getName())) {
			error("Module " + m.getName() + " must be defined in its own file",
					EmDslPackage.Literals.MODULE__NAME);
		}
	}

	@Check
	public void checkFileMustContainsSingleModule(Model model) {
		if (model.getElements().isEmpty()) {
			warning("No module definitions in file",
					EmDslPackage.Literals.MODEL__ELEMENTS);
		}
	}
	
}
