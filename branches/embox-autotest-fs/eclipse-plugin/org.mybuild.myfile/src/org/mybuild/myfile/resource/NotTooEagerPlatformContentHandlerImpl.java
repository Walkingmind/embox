package org.mybuild.myfile.resource;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.ContentHandler;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.URIConverter;
import org.eclipse.emf.ecore.resource.impl.PlatformContentHandlerImpl;
import org.eclipse.xtext.resource.impl.ResourceServiceProviderRegistryImpl;

/**
 * Workaround for {@link ResourceServiceProviderRegistryImpl.InternalData}
 * implementation of {@link Resource.Factory.Registry} which omits
 * {@link PlatformContentHandlerImpl} when constructing {@link URIConverter}
 * because it {@link ContentHandler#canHandle(URI) can handle} <code>null</code>
 * {@link URI}.
 * 
 * TODO I don't know if it is a good idea to exploit such internal features (and
 * I guess it is not), but this is the only working solution that I've found.
 * 
 * @author Eldar Abusalimov
 */
public class NotTooEagerPlatformContentHandlerImpl extends
		PlatformContentHandlerImpl {

	@Override
	public boolean canHandle(URI uri) {
		return uri != null;
	}

}
