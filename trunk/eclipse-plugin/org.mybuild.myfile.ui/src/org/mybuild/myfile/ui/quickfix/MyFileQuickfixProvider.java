package org.mybuild.myfile.ui.quickfix;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.jface.text.BadLocationException;
import org.eclipse.xtext.ui.editor.model.IXtextDocument;
import org.eclipse.xtext.ui.editor.model.edit.IModification;
import org.eclipse.xtext.ui.editor.model.edit.IModificationContext;
import org.eclipse.xtext.ui.editor.model.edit.ISemanticModification;
import org.eclipse.xtext.ui.editor.quickfix.DefaultQuickfixProvider;
import org.eclipse.xtext.ui.editor.quickfix.Fix;
import org.eclipse.xtext.ui.editor.quickfix.IssueResolutionAcceptor;
import org.eclipse.xtext.validation.Issue;
import org.mybuild.myfile.validation.IssueCodes;

public class MyFileQuickfixProvider extends DefaultQuickfixProvider {

	@Fix(IssueCodes.INVALID_MODULE_NAME)
	public void capitalizeName(final Issue issue,
			IssueResolutionAcceptor acceptor) {

		IModification modification = new IModification() {
			public void apply(IModificationContext context)
					throws BadLocationException {
				IXtextDocument xtextDocument = context.getXtextDocument();
				String firstLetter = xtextDocument.get(issue.getOffset(), 1);
				xtextDocument.replace(issue.getOffset(), 1,
						firstLetter.toUpperCase());
			}
		};

		acceptor.accept(issue, "Capitalize name", "Capitalize the name.",
				"upcase.png", modification);
	}

	@Fix(IssueCodes.DUPLICATE_FILE_NAME)
	public void removeDuplicateFile(final Issue issue,
			IssueResolutionAcceptor acceptor) {

		ISemanticModification modification = new ISemanticModification() {
			public void apply(EObject element, IModificationContext context)
					throws Exception {
				EObject container = element.eContainer();
				if (container.eContents().size() > 1) {
					EcoreUtil.remove(element);
				} else {
					EcoreUtil.remove(container);
				}
			}
		};

		acceptor.accept(issue, "Remove duplicate",
				"Remove the duplicate filename.", "remove.png", modification);
	}

}
