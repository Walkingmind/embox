package org.mybuild.myfile.validation;

import static com.google.common.collect.Iterators.filter;
import static com.google.common.collect.Lists.newArrayList;
import static com.google.common.collect.Sets.newHashSet;
import static org.mybuild.myfile.util.Annotations.MYBUILD_GENERATED;
import static org.mybuild.myfile.util.Annotations.isAnnotatedWith;
import static org.mybuild.myfile.util.FileUtils.fileOfEObject;

import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.Path;
import org.eclipse.xtext.validation.Check;
import org.mybuild.myfile.FileName;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.MyFilePackage.Literals;
import org.mybuild.myfile.SourceMember;
import org.mybuild.myfile.Type;

public class MyFileJavaValidator extends AbstractMyFileJavaValidator {

//	@Check
//	public void checkTypeNameStartsWithCapital(Type type) {
//		if (!Character.isUpperCase(type.getName().charAt(0))) {
//			warning("Name should start with a capital", Literals.NAMED__NAME,
//					IssueCodes.INVALID_MODULE_NAME);
//		}
//	}

	@Check
	public void checkSourceFileExists(SourceMember source) {
		if (isAnnotatedWith(source, MYBUILD_GENERATED)) {
			return;
		}

		IFile file = fileOfEObject(source);
		if (file == null) {
			return;
		}

		for (FileName fileName : source.getFiles()) {
			String name = fileName.getValue();
			if (!file.getParent().exists(new Path(name))) {
				error("File does not exist", fileName,
						Literals.FILE_NAME__VALUE,
						IssueCodes.FILE_DOES_NOT_EXIST, name);
			}
		}
	}

//	@Check
//	public void checkFileFeaturesSpecifyUniqueNames(Module module) {
//		final List<Filename> filenames = newArrayList();
//		final Set<String> names = newHashSet();
//		final Set<String> duplicates = newHashSet();
//
//		Iterator<Filename> iterator = filter(module.eAllContents(),
//				Filename.class);
//
//		while (iterator.hasNext()) {
//			Filename filename = iterator.next();
//
//			String name = filename.getName().trim();
//
//			filenames.add(filename);
//			if (!names.add(name)) {
//				duplicates.add(name);
//			}
//		}
//
//		if (duplicates.isEmpty()) {
//			return;
//		}
//
//		for (Filename filename : filenames) {
//			if (duplicates.contains(filename.getName().trim())) {
//				error("Duplicate file name", filename, Literals.FILENAME__NAME,
//						IssueCodes.DUPLICATE_FILE_NAME, filename.getName());
//			}
//		}
//	}

}
