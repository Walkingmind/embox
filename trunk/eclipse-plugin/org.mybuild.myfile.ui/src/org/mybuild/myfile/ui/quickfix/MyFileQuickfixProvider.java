package org.mybuild.myfile.ui.quickfix;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.xtext.ui.editor.model.edit.IModificationContext;
import org.eclipse.xtext.ui.editor.model.edit.ISemanticModification;
import org.eclipse.xtext.ui.editor.quickfix.DefaultQuickfixProvider;
import org.eclipse.xtext.ui.editor.quickfix.Fix;
import org.eclipse.xtext.ui.editor.quickfix.IssueResolutionAcceptor;
import org.eclipse.xtext.validation.Issue;
import org.mybuild.myfile.myFile.Module;
import org.mybuild.myfile.validation.IssueCodes;

public class MyFileQuickfixProvider extends DefaultQuickfixProvider {

	@Fix(IssueCodes.INVALID_MODULE_NAME)
	public void capitalizeName(final Issue issue,
			IssueResolutionAcceptor acceptor) {

		ISemanticModification modification = new ISemanticModification() {
			public void apply(EObject element, IModificationContext context)
					throws Exception {
				Module module = (Module) element;

				String name = module.getName();
				String firstLetter = name.substring(0, 1).toUpperCase();
				module.setName(firstLetter + name.substring(1));
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
