package org.mybuild.myfile.ui.labeling;

import static org.eclipse.ui.ide.IDE.getEditorDescriptor;

import org.eclipse.core.resources.IFile;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.edit.ui.provider.AdapterFactoryLabelProvider;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.viewers.DecorationOverlayIcon;
import org.eclipse.jface.viewers.IDecoration;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.PartInitException;
import org.eclipse.xtext.ui.IImageHelper;
import org.eclipse.xtext.ui.label.DefaultEObjectLabelProvider;
import org.mybuild.myfile.DependsMember;
import org.mybuild.myfile.FileName;
import org.mybuild.myfile.Import;
import org.mybuild.myfile.Interface;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.ObjectMember;
import org.mybuild.myfile.Package;
import org.mybuild.myfile.SourceMember;

import com.google.inject.Inject;

/**
 * Provides labels for a EObjects.
 * 
 * see
 * http://www.eclipse.org/Xtext/documentation/latest/xtext.html#labelProvider
 */
public class MyFileLabelProvider extends DefaultEObjectLabelProvider {

	@Inject
	private IImageHelper imageHelper;

	@Inject
	public MyFileLabelProvider(AdapterFactoryLabelProvider delegate) {
		super(delegate);
	}

	public Image image(Module module) {
		Image image = imageHelper.getImage("module.png");

		if (module.isAbstract()) {
			ImageDescriptor abstractAdornment = ImageDescriptor
					.createFromImage(imageHelper.getImage("abstract.png"));
			image = new DecorationOverlayIcon(image, abstractAdornment,
					IDecoration.TOP_RIGHT).createImage();
		}

		return image;
	}

	public String image(Interface iface) {
		return "interface.png";
	}
	
	public String image(EList<Import> imports) {
		return "imports.png";
	}

	public String image(Import imp) {
		return "import.png";
	}

	public String image(Package pkg) {
		return "package.png";
	}

	public String image(DependsMember deps) {
		return "dependency.png";
	}

	public String image(SourceMember sources) {
		return "file.png";
	}

	public Image image(ObjectMember objects) {
		Image image = imageHelper.getImage("file.png");

		ImageDescriptor binaryAdornment = ImageDescriptor
				.createFromImage(imageHelper.getImage("binary.png"));
		image = imageHelper.getImage(new DecorationOverlayIcon(image, binaryAdornment,
				IDecoration.BOTTOM_RIGHT));

		return image;
	}

	public Image image(FileName file) {
		return getImage(file.eContainer());
	}

	public Image image(IFile file) {
		Image image = null;

		try {
			ImageDescriptor imageDescriptor = getEditorDescriptor(file)
					.getImageDescriptor();
			if (imageDescriptor != null) {
				image = imageDescriptor.createImage();
			}

		} catch (PartInitException e) {
		}

		return image;
	}
}
