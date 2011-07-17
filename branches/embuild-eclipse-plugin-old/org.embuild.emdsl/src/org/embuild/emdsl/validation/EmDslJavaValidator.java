package org.embuild.emdsl.validation;

import static java.util.Collections.singletonMap;
import static org.eclipse.emf.ecore.resource.URIConverter.ATTRIBUTE_DIRECTORY;

import java.io.File;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.URIConverter;
import org.eclipse.xtext.validation.Check;
import org.embuild.emdsl.emDsl.EmDslPackage;
import org.embuild.emdsl.emDsl.Source;

public class EmDslJavaValidator extends AbstractEmDslJavaValidator {

	// @Check
	// public void checkAllModulesStartsWithCapital(Module m) {
	// if (!Character.isUpperCase(m.getName().charAt(0))) {
	// warning("Name should start with a capital",
	// EmDslPackage.Literals.MODULE__NAME);
	// }
	// }
	//
	// @Check
	// public void checkNameAllModuleExistInFile(Package p) {
	// EList<Entity> entities = p.getEntities();
	// }

	@Check
	public void checkSourseFileExistsInSameDir(Source s) {
		String fileName = s.getFilename();

		if (checkFileNameContainsGlob(fileName)) {
			return;
		}

		Resource r = s.eResource();
		ResourceSet rSet = r.getResourceSet();
		URIConverter uriConverter = rSet.getURIConverter();

		URI uri = r.getURI();
		uri = uri.appendSegments(new String[] { "..", fileName });
		if (!uriConverter.exists(uri, singletonMap(ATTRIBUTE_DIRECTORY, false))) {
			warning("File " + fileName + " does not exist",
					EmDslPackage.Literals.SOURCE__FILENAME);
		}

	}

	private boolean checkFileNameContainsGlob(String fileName) {
		char[] name = fileName.toCharArray();
		for (int i = 0; i < name.length; i++) {
			char c = name[i];
			if (c == '*' || c == '?' || c == '[' || c == ']') {
				return true;
			}
		}
		return false;
	}
}
