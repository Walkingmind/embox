/*
 * generated by Xtext
 */
package org.mybuild.myfile.ui.contentassist;

import java.io.File;
import java.io.FileFilter;

import org.eclipse.emf.common.CommonPlugin;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.jface.text.BadLocationException;
import org.eclipse.jface.text.Region;
import org.eclipse.xtext.Assignment;
import org.eclipse.xtext.conversion.IValueConverterService;
import org.eclipse.xtext.ui.editor.contentassist.ConfigurableCompletionProposal;
import org.eclipse.xtext.ui.editor.contentassist.ContentAssistContext;
import org.eclipse.xtext.ui.editor.contentassist.ICompletionProposalAcceptor;

/**
 * see
 * http://www.eclipse.org/Xtext/documentation/latest/xtext.html#contentAssist on
 * how to customize content assistant
 */
public class MyFileProposalProvider extends AbstractMyFileProposalProvider {

	public void completeFilename_Name(EObject model, Assignment assignment,
			ContentAssistContext context, ICompletionProposalAcceptor acceptor) {
		Resource res = model.eResource();
		URI uri = res.getURI();

		File dir = new File(CommonPlugin.resolve(uri.appendSegment(".."))
				.toFileString());

		File[] files = dir.listFiles(new FileFilter() {
			public boolean accept(File f) {
				String name = f.getName();
				return f.isFile() && !"Mybuild".equals(name)
						&& !name.endsWith(".my");
			}
		});

		IValueConverterService converter = getValueConverter();

		Region replaceRegion = context.getReplaceRegion();
		int replacementLength = replaceRegion.getLength();
		int replacementEnd = replaceRegion.getOffset() + replacementLength;

		boolean isAtEndOfString = false;
		try {
			isAtEndOfString = context.getDocument().getChar(replacementEnd) == '"';

		} catch (BadLocationException e) {
			e.printStackTrace();
		}

		for (File file : files) {
			String string = converter.toString(file.getName(), "STRING");
			ConfigurableCompletionProposal proposal = (ConfigurableCompletionProposal) createCompletionProposal(
					string, string, getLabelProvider().getImage(model), context);

			if (proposal != null) {
				if (isAtEndOfString) {
					proposal.setReplacementLength(replacementLength + 1);
					proposal.setReplacementString(string.substring(0,
							string.length() - 1));
				}
				acceptor.accept(proposal);
			}
		}
	}
}
