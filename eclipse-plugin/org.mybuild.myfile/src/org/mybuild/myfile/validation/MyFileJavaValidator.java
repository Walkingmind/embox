package org.mybuild.myfile.validation;

import static com.google.common.collect.Iterators.filter;
import static com.google.common.collect.Lists.newArrayList;
import static com.google.common.collect.Sets.newHashSet;
import static org.mybuild.myfile.util.FileUtils.fileOfEObject;

import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.Path;
import org.eclipse.xtext.validation.Check;
import org.mybuild.myfile.myFile.Entity;
import org.mybuild.myfile.myFile.Filename;
import org.mybuild.myfile.myFile.Module;
import org.mybuild.myfile.myFile.MyFilePackage.Literals;

public class MyFileJavaValidator extends AbstractMyFileJavaValidator {

	@Check
	public void checkEntityNameStartsWithCapital(Entity entity) {
		if (!Character.isUpperCase(entity.getName().charAt(0))) {
			warning("Name should start with a capital", Literals.ENTITY__NAME,
					IssueCodes.INVALID_MODULE_NAME);
		}
	}

	@Check
	public void checkFileExists(Filename filename) {
		IFile file = fileOfEObject(filename);

		if (file == null) {
			return;
		}

		if (!file.getParent().exists(new Path(filename.getName()))) {
			error("File does not exist", filename, Literals.FILENAME__NAME,
					IssueCodes.FILE_DOES_NOT_EXIST, filename.getName());
		}
	}

	@Check
	public void checkFileFeaturesSpecifyUniqueNames(Module module) {
		final List<Filename> filenames = newArrayList();
		final Set<String> names = newHashSet();
		final Set<String> duplicates = newHashSet();

		Iterator<Filename> iterator = filter(module.eAllContents(),
				Filename.class);

		while (iterator.hasNext()) {
			Filename filename = iterator.next();

			String name = filename.getName().trim();

			filenames.add(filename);
			if (!names.add(name)) {
				duplicates.add(name);
			}
		}

		if (duplicates.isEmpty()) {
			return;
		}

		for (Filename filename : filenames) {
			if (duplicates.contains(filename.getName().trim())) {
				error("Duplicate file name", filename, Literals.FILENAME__NAME,
						IssueCodes.DUPLICATE_FILE_NAME, filename.getName());
			}
		}
	}

}
