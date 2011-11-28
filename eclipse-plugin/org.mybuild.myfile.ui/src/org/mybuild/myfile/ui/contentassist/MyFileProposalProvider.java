package org.mybuild.myfile.ui.contentassist;

import static org.eclipse.ui.ide.IDE.getContentType;
import static org.mybuild.myfile.ui.util.FileUtils.fileOfEObject;
import static org.mybuild.myfile.ui.util.FileUtils.getMybuildContentType;
import static org.mybuild.myfile.ui.util.FileUtils.listFiles;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.content.IContentType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.jface.text.BadLocationException;
import org.eclipse.jface.text.Region;
import org.eclipse.xtext.Assignment;
import org.eclipse.xtext.ui.editor.contentassist.ConfigurableCompletionProposal;
import org.eclipse.xtext.ui.editor.contentassist.ContentAssistContext;
import org.eclipse.xtext.ui.editor.contentassist.ICompletionProposalAcceptor;

import com.google.common.base.Predicate;

/**
 * see
 * http://www.eclipse.org/Xtext/documentation/latest/xtext.html#contentAssist on
 * how to customize content assistant
 */
public class MyFileProposalProvider extends AbstractMyFileProposalProvider {

	public void completeFilename_Name(EObject model, Assignment assignment,
			ContentAssistContext context, ICompletionProposalAcceptor acceptor) {
		boolean cursorAtEndOfString = isCursorAtEndOfString(context);

		for (IFile localFile : listLocalFiles(model)) {
			System.out.println(localFile);
			String string = getValueConverter().toString(localFile.getName(),
					"STRING");
			ConfigurableCompletionProposal proposal = (ConfigurableCompletionProposal) createCompletionProposal(
					string, string, getLabelProvider().getImage(localFile),
					context);

			if (proposal != null) {
				if (cursorAtEndOfString) {
					proposal.setReplaceContextLength(proposal
							.getReplaceContextLength() - 1);
					proposal.setReplacementString(string.substring(0,
							string.length() - 1));
				}
				acceptor.accept(proposal);
			}
		}
	}

	private static boolean isCursorAtEndOfString(ContentAssistContext context) {
		Region replaceRegion = context.getReplaceRegion();
		int replacementEnd = replaceRegion.getOffset()
				+ replaceRegion.getLength();
		try {
			return context.getDocument().getChar(replacementEnd) == '"';
		} catch (BadLocationException e) {
			return false;
		}
	}

	private Iterable<IFile> listLocalFiles(EObject model) {
		IFile file = fileOfEObject(model);

		final IContentType mybuildContentType = getMybuildContentType();
		Iterable<IFile> localFiles = listFiles(file.getParent(),
				new Predicate<IFile>() {
					public boolean apply(IFile input) {
						IContentType contentType = getContentType(input);
						return contentType == null
								|| !contentType.isKindOf(mybuildContentType);
					}
				});
		return localFiles;
	}
}
