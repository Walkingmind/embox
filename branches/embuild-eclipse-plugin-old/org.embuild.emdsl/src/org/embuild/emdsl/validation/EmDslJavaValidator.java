package org.embuild.emdsl.validation;

import static java.util.Collections.singletonMap;
import static org.eclipse.emf.ecore.resource.URIConverter.ATTRIBUTE_DIRECTORY;

import java.util.List;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.URIConverter;
import org.eclipse.xtext.validation.Check;
import org.embuild.emdsl.emDsl.EmDslPackage;
import org.embuild.emdsl.emDsl.Ifdef;
import org.embuild.emdsl.emDsl.SrcsPropAssign;

public class EmDslJavaValidator extends AbstractEmDslJavaValidator {

	@Check
	public void checkSourseFileExistsInSameDir(SrcsPropAssign s) {
		String[] files = s.getFilenames().get(0).split(" ");
		
		for (String fileName : files) {
			if (checkFileNameContainsGlob(fileName)) {
				return;
			}

			Resource r = s.eResource();
			URIConverter uriConverter = r.getResourceSet().getURIConverter();

			URI uri = r.getURI();
			uri = uri.appendSegments(new String[] { "..", fileName });
			if (!uriConverter.exists(uri,
					singletonMap(ATTRIBUTE_DIRECTORY, false))) {
				warning("File " + fileName + " does not exist",
						EmDslPackage.Literals.SRCS_PROP_ASSIGN__FILENAMES);
			}
		}
	}

	@Check
	public void checkIfdefExist(Ifdef ifdef) {
		warning("Ifdef considered harmful",
				EmDslPackage.Literals.IFDEF__CONDITION);
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
