package org.mybuild.myfile.ui.labeling;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.edit.ui.provider.AdapterFactoryLabelProvider;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.viewers.DecorationOverlayIcon;
import org.eclipse.jface.viewers.IDecoration;
import org.eclipse.swt.graphics.Image;
import org.eclipse.xtext.ui.IImageHelper;
import org.eclipse.xtext.ui.label.DefaultEObjectLabelProvider;
import org.mybuild.myfile.myFile.Dependencies;
import org.mybuild.myfile.myFile.Filename;
import org.mybuild.myfile.myFile.Import;
import org.mybuild.myfile.myFile.Module;
import org.mybuild.myfile.myFile.Objects;
import org.mybuild.myfile.myFile.Package;
import org.mybuild.myfile.myFile.Sources;

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

	public String image(EList<Import> imports) {
		return "imports.png";
	}

	public String image(Import imp) {
		return "import.png";
	}

	public String image(Package pkg) {
		return "package.png";
	}

	public String image(Dependencies deps) {
		return "dependency.png";
	}

	public String image(Sources sources) {
		return "file.png";
	}

	public Image image(Objects objects) {
		Image image = imageHelper.getImage("file.png");

		ImageDescriptor binaryAdornment = ImageDescriptor
				.createFromImage(imageHelper.getImage("binary.png"));
		image = new DecorationOverlayIcon(image, binaryAdornment,
				IDecoration.BOTTOM_RIGHT).createImage();

		return image;
	}

	public Image image(Filename file) {
		return getImage(file.eContainer());
	}

}
