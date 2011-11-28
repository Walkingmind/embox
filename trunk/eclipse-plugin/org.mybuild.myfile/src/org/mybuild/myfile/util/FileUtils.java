package org.mybuild.myfile.util;

import static com.google.common.base.Predicates.and;
import static com.google.common.base.Predicates.instanceOf;
import static com.google.common.collect.Iterables.filter;
import static java.util.Arrays.asList;
import static java.util.Collections.emptyList;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.Platform;
import org.eclipse.core.runtime.content.IContentType;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;

import com.google.common.base.Predicate;

/**
 * @author Eldar Abusalimov
 */
public class FileUtils {

	public static final String MYBUILD_CONTENT_TYPE_ID = "org.mybuild.myfile.contentType";
	public static final String TEXT_CONTENT_TYPE_ID = "org.eclipse.core.runtime.text";

	public static IFile fileOfEObject(EObject eObject) {
		return fileFromResource(eObject.eResource());
	}

	public static IFile fileFromResource(Resource eResource) {
		return fileFromURI(eResource.getURI());
	}

	public static IFile fileFromURI(URI uri) {
		if (!uri.isPlatform()) {
			return null;
		}
		return ResourcesPlugin.getWorkspace().getRoot()
				.getFile(new Path(uri.toPlatformString(true)));
	}

	public static IContentType getMybuildContentType() {
		return getContentTypeById(MYBUILD_CONTENT_TYPE_ID);
	}

	public static IContentType getTextContentType() {
		return getContentTypeById(TEXT_CONTENT_TYPE_ID);
	}

	public static IContentType getContentTypeById(String contentTypeIdentifier) {
		return Platform.getContentTypeManager().getContentType(
				contentTypeIdentifier);
	}

	public static Iterable<IFile> listFiles(IContainer folder) {
		try {
			return filter(asList(folder.members()), IFile.class);
		} catch (CoreException e) {
			return emptyList();
		}
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static Iterable<IFile> listFiles(IContainer folder,
			Predicate<IFile> predicate) {
		try {
			return filter(asList(folder.members()),
					(Predicate) and(instanceOf(IFile.class), predicate));
		} catch (CoreException e) {
			return emptyList();
		}
	}

}
