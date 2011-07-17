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
		String filename = s.getFilename();
		// * ? [|||] dl*fk.[c|h]

		Resource r = s.eResource();
		ResourceSet rSet = r.getResourceSet();
		URIConverter uriConverter = rSet.getURIConverter();

		URI uri = r.getURI();
		uri = uri.appendSegments(new String[] { "..", filename });
		if (!uriConverter.exists(uri, singletonMap(ATTRIBUTE_DIRECTORY, false))) {
			warning("File " + filename + " does not exist",
					EmDslPackage.Literals.SOURCE__FILENAME);
		}

	}

	private boolean find(String name, String directory) {
		File dir = new File(directory);
		assert dir.exists() : "directory " + directory + " is assumed to exist";
		if (dir.isDirectory()) {
			File[] l = dir.listFiles();
			for (int i = 0; i < l.length; i++) {
				if (name.equals(l[i].getName())) {
					return true;
				}
			}
		}
		return false;

	}

	private boolean search(String name, File dir) {
		if (!dir.isDirectory()) {
			return false;
		}
		File[] l = dir.listFiles();
		for (int i = 0; i < l.length; i++) {
			File cur = l[i];
			if (cur.getName().equals(name)) {
				return true;
			}
			if (cur.isDirectory()) {
				return search(name, l[i]);
			}
		}
		return false;
	}

}
