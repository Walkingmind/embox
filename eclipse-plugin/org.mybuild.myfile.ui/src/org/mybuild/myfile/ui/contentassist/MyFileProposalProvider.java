package org.mybuild.myfile.ui.contentassist;

import static java.util.Collections.emptyList;
import static org.eclipse.ui.ide.IDE.getContentType;
import static org.eclipse.xtext.EcoreUtil2.getContainerOfType;
import static org.mybuild.myfile.util.FileUtils.fileOfEObject;
import static org.mybuild.myfile.util.FileUtils.getFileBaseName;
import static org.mybuild.myfile.util.FileUtils.getMybuildContentType;
import static org.mybuild.myfile.util.FileUtils.listFiles;

import java.util.regex.Pattern;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.content.IContentType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.jface.text.BadLocationException;
import org.eclipse.jface.text.Region;
import org.eclipse.xtext.Assignment;
import org.eclipse.xtext.RuleCall;
import org.eclipse.xtext.ui.editor.contentassist.ConfigurableCompletionProposal;
import org.eclipse.xtext.ui.editor.contentassist.ContentAssistContext;
import org.eclipse.xtext.ui.editor.contentassist.ICompletionProposalAcceptor;
import org.mybuild.myfile.myFile.Module;

import com.google.common.base.Predicate;

/**
 * see
 * http://www.eclipse.org/Xtext/documentation/latest/xtext.html#contentAssist on
 * how to customize content assistant
 */
public class MyFileProposalProvider extends AbstractMyFileProposalProvider {

	private final static class FileProposalPriorityHelper {

		private static final Pattern SIMPLIFY_PATTERN = Pattern
				.compile("[-_.]");

		private String name;
		private String lowerCaseName;
		private String simplifiedName;

		public FileProposalPriorityHelper(Module module) {
			this(module == null ? null : module.getName());
		}

		public FileProposalPriorityHelper(String moduleName) {
			if (moduleName != null) {
				name = moduleName;
				lowerCaseName = name.toLowerCase();
				simplifiedName = simplifyName(lowerCaseName);
			}
		}

		public int adjustPriority(IFile file, int priority) {
			return adjustPriority(file.getName(), priority);
		}

		public int adjustPriority(String filename, int priority) {
			if (this.name == null) {
				return priority;
			}

			String baseName = getFileBaseName(filename);
			String lowerCaseBaseName = baseName.toLowerCase();
			String simplifiedBaseName = simplifyName(lowerCaseBaseName);

			if (baseName.equals(name)) {
				priority *= 2;
			}
			if (lowerCaseBaseName.equals(lowerCaseName)) {
				priority *= 2;
			}
			if (simplifiedBaseName.equals(simplifiedName)) {
				priority *= 2;
			}
			if (baseName.startsWith(name)) {
				priority *= 2;
			}
			if (lowerCaseBaseName.startsWith(lowerCaseName)) {
				priority *= 2;
			}
			if (simplifiedBaseName.startsWith(simplifiedName)) {
				priority *= 2;
			}

			return priority;
		}

		private static String simplifyName(String name) {
			return SIMPLIFY_PATTERN.matcher(name).replaceAll("");
		}
	}

	@Override
	public void complete_STRING(EObject model, RuleCall ruleCall,
			ContentAssistContext context, ICompletionProposalAcceptor acceptor) {
	}

	public void completeFilename_Name(EObject model, Assignment assignment,
			ContentAssistContext context, ICompletionProposalAcceptor acceptor) {
		FileProposalPriorityHelper priorityHelper = new FileProposalPriorityHelper(
				getContainerOfType(model, Module.class));

		boolean cursorAtEndOfString = isCursorAtEndOfString(context);

		for (IFile localFile : listLocalFiles(model)) {
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

				int priority = proposal.getPriority();
				priority = priorityHelper.adjustPriority(localFile, priority);
				proposal.setPriority(priority);

				acceptor.accept(proposal);
			}
		}

		System.out.println();
	}

	private static boolean isCursorAtEndOfString(ContentAssistContext context) {
		Region replaceRegion = context.getReplaceRegion();
		int replacementEnd = replaceRegion.getOffset()
				+ replaceRegion.getLength();
		try {
			char c = context.getDocument().getChar(replacementEnd);
			return c == '"' || c == '\'';
		} catch (BadLocationException e) {
			return false;
		}
	}

	private Iterable<IFile> listLocalFiles(EObject model) {
		IFile file = fileOfEObject(model);
		if (file == null) {
			return emptyList();
		}

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
