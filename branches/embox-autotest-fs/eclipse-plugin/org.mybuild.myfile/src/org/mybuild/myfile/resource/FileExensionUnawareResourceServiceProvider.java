package org.mybuild.myfile.resource;

import org.eclipse.emf.common.util.URI;
import org.eclipse.xtext.resource.IResourceServiceProvider;
import org.eclipse.xtext.resource.impl.DefaultResourceServiceProvider;

/**
 * This implementation of {@link IResourceServiceProvider} tells
 * <code>true</code> for {@link IResourceServiceProvider#canHandle(URI)} called
 * on any {@link URI} regardless its extension. This is ok since resource
 * service provider registry maps only resources of proper content type to
 * instance of this class.
 * 
 * @author Eldar Abusalimov
 */
public class FileExensionUnawareResourceServiceProvider extends
		DefaultResourceServiceProvider implements IResourceServiceProvider {

	@Override
	public boolean canHandle(URI uri) {
		return true;
	}

}
