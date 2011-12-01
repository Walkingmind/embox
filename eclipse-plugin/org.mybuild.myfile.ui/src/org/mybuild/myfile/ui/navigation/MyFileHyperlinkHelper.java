package org.mybuild.myfile.ui.navigation;

import static org.mybuild.myfile.util.FileUtils.fileFromResource;

import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IResource;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.jface.text.Region;
import org.eclipse.ui.IEditorDescriptor;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.ide.IDE;
import org.eclipse.xtext.common.types.xtext.ui.TypeAwareHyperlinkHelper;
import org.eclipse.xtext.nodemodel.INode;
import org.eclipse.xtext.nodemodel.util.NodeModelUtils;
import org.eclipse.xtext.resource.EObjectAtOffsetHelper;
import org.eclipse.xtext.resource.XtextResource;
import org.eclipse.xtext.ui.editor.hyperlinking.AbstractHyperlink;
import org.eclipse.xtext.ui.editor.hyperlinking.IHyperlinkAcceptor;
import org.mybuild.myfile.myFile.Filename;
import org.mybuild.myfile.myFile.MyFilePackage;

import com.google.inject.Inject;

public class MyFileHyperlinkHelper extends TypeAwareHyperlinkHelper {

	private final static class FileHyperlink extends AbstractHyperlink {
		private final IEditorDescriptor editor;
		private final IFile file;

		private FileHyperlink(IFile file, IEditorDescriptor editor) {
			this.editor = editor;
			this.file = file;
		}

		@Override
		public void open() {
			IWorkbenchPage page = PlatformUI.getWorkbench()
					.getActiveWorkbenchWindow().getActivePage();
			try {
				IDE.openEditor(page, file, editor.getId());
			} catch (PartInitException e) {
			}
		}

	}

	@Inject
	private EObjectAtOffsetHelper eObjectAtOffsetHelper;

	@Override
	public void createHyperlinksByOffset(XtextResource resource, int offset,
			IHyperlinkAcceptor acceptor) {
		super.createHyperlinksByOffset(resource, offset, acceptor);

		EObject eObject = eObjectAtOffsetHelper.resolveElementAt(resource,
				offset);
		if (!(eObject instanceof Filename)) {
			return;
		}

		Filename filename = (Filename) eObject;
		IFile resourceFile = fileFromResource(resource);
		if (resourceFile == null) {
			return;
		}

		IResource referredResource = resourceFile.getParent()
				.findMember(filename.getName());
		if (!(referredResource instanceof IFile)) {
			return;
		}

		IFile referredFile = (IFile) referredResource;
		IEditorDescriptor editor;
		try {
			editor = IDE.getEditorDescriptor(referredFile);
		} catch (PartInitException e) {
			return;
		}

		Region hyperlinkRegion = null;
		List<INode> nodes = NodeModelUtils.findNodesForFeature(eObject,
				MyFilePackage.Literals.FILENAME__NAME);
		if (!nodes.isEmpty()) {
			INode node = nodes.get(0);
			hyperlinkRegion = new Region(node.getOffset(), node.getLength());
		}

		FileHyperlink hyperlink = new FileHyperlink(referredFile, editor);
		hyperlink.setHyperlinkRegion(hyperlinkRegion);
		hyperlink.setHyperlinkText("Open " + referredFile.getName() + " in "
				+ editor.getLabel());
		hyperlink.setTypeLabel("Navigate to file.");

		acceptor.accept(hyperlink);
	}

}
