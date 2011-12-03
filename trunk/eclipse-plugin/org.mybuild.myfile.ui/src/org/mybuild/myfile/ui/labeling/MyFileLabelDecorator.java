/**
 * 
 */
package org.mybuild.myfile.ui.labeling;

import static org.eclipse.ui.ide.IDE.getContentType;
import static org.mybuild.myfile.util.FileUtils.getMybuildContentType;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.content.IContentType;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.viewers.IDecoration;
import org.eclipse.jface.viewers.ILabelProviderListener;
import org.eclipse.jface.viewers.ILightweightLabelDecorator;
import org.eclipse.ui.part.FileEditorInput;
import org.eclipse.xtext.resource.IEObjectDescription;
import org.eclipse.xtext.resource.IResourceDescription;
import org.eclipse.xtext.resource.XtextResource;
import org.eclipse.xtext.ui.IImageHelper;
import org.eclipse.xtext.ui.editor.model.XtextDocumentProvider;
import org.mybuild.myfile.myFile.MyFilePackage;

import com.google.inject.Inject;

/**
 * @author Eldar Abusalimov
 */
public class MyFileLabelDecorator implements ILightweightLabelDecorator {

	@Inject
	private XtextDocumentProvider documentProvider;
	@Inject
	private IResourceDescription.Manager resourceDescriptionManager;
	@Inject
	private IImageHelper imageHelper;

	@Override
	public void decorate(Object element, IDecoration decoration) {
		if (!(element instanceof IFile)) {
			return;
		}

		IFile file = (IFile) element;
		if (file.getFileExtension() == null) {
			// 'Mybuild' files are not decorated.
			return;
		}

		IContentType contentType = getContentType(file);
		if (contentType == null
				|| !contentType.isKindOf(getMybuildContentType())) {
			return;
		}

		EClass entityClass = getPrimaryEntityClass(file);
		if (entityClass == null) {
			return;
		}

		String adornmentName = MyFilePackage.Literals.INTERFACE
				.isSuperTypeOf(entityClass) ? "interface_tsk.png"
				: "module_tsk.png";

		ImageDescriptor entityAdornment = ImageDescriptor
				.createFromImage(imageHelper.getImage(adornmentName));
		decoration.addOverlay(entityAdornment, IDecoration.TOP_RIGHT);
	}

	private EClass getPrimaryEntityClass(IFile file) {
		FileEditorInput input = new FileEditorInput(file);
		Resource resource = (XtextResource) documentProvider
				.getResourceForEditorInputFactory().createResource(input);
		IResourceDescription resourceDescription = resourceDescriptionManager
				.getResourceDescription(resource);

		EClass found = null;

		for (IEObjectDescription objectDescription : resourceDescription
				.getExportedObjectsByType(MyFilePackage.Literals.ENTITY)) {
			if (found != null) {
				// More than one entity in the resource.
				return null;
			}
			found = objectDescription.getEClass();
		}

		return found;
	}

	@Override
	public void addListener(ILabelProviderListener listener) {
	}

	@Override
	public void dispose() {
	}

	@Override
	public boolean isLabelProperty(Object element, String property) {
		return false;
	}

	@Override
	public void removeListener(ILabelProviderListener listener) {
	}

}
