package org.mybuild.myfile.validation;

import static com.google.common.collect.Lists.newArrayList;
import static com.google.common.collect.Sets.newHashSet;

import java.util.List;
import java.util.Set;

import org.eclipse.emf.common.util.TreeIterator;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.xtext.validation.Check;
import org.mybuild.myfile.myFile.Dependencies;
import org.mybuild.myfile.myFile.Filename;
import org.mybuild.myfile.myFile.Module;
import org.mybuild.myfile.myFile.MyFilePackage.Literals;
import org.mybuild.myfile.myFile.util.MyFileSwitch;

public class MyFileJavaValidator extends AbstractMyFileJavaValidator {

	@Check
	public void checkFileFeaturesSpecifyUniqueNames(Module module) {
		final List<Filename> files = newArrayList();
		final Set<String> names = newHashSet();
		final Set<String> duplicates = newHashSet();

		final TreeIterator<EObject> iterator = module.eAllContents();

		MyFileSwitch<Void> visitor = new MyFileSwitch<Void>() {
			
			@Override
			public Void caseFilename(Filename file) {
				String name = file.getName().trim();
				
				files.add(file);
				if (!names.add(name)) {
					duplicates.add(name);
				}
				
				return null;
			}
			
			@Override
			public Void caseDependencies(Dependencies object) {
				iterator.prune();
				
				return null;
			}
		};

		while (iterator.hasNext()) {
			visitor.doSwitch(iterator.next());
		}

		if (duplicates.isEmpty()) {
			return;
		}

		for (Filename file : files) {
			if (duplicates.contains(file.getName().trim())) {
				error("Duplicate file name", file, Literals.FILENAME__NAME,
						IssueCodes.DUPLICATE_FILE_NAME, file.getName());
			}
		}
	}

}
