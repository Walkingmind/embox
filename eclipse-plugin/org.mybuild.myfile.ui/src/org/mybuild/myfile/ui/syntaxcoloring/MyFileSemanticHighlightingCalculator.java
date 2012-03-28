package org.mybuild.myfile.ui.syntaxcoloring;

import org.eclipse.xtext.CrossReference;
import org.eclipse.xtext.Keyword;
import org.eclipse.xtext.nodemodel.ICompositeNode;
import org.eclipse.xtext.nodemodel.INode;
import org.eclipse.xtext.resource.XtextResource;
import org.eclipse.xtext.ui.editor.syntaxcoloring.IHighlightedPositionAcceptor;
import org.eclipse.xtext.ui.editor.syntaxcoloring.ISemanticHighlightingCalculator;
import org.mybuild.myfile.AbstractFeatureListMember;

public class MyFileSemanticHighlightingCalculator implements
		ISemanticHighlightingCalculator {

	public void provideHighlightingFor(final XtextResource resource,
			IHighlightedPositionAcceptor acceptor) {
		if (resource == null || resource.getParseResult() == null)
			return;

		for (INode node : resource.getParseResult().getRootNode()
				.getAsTreeIterable()) {
			if (node.getGrammarElement() instanceof CrossReference
					&& node.getSemanticElement() instanceof AbstractFeatureListMember) {
				highlightFeatureRef(node, acceptor);
			}
		}
	}

	private void highlightFeatureRef(INode node,
			IHighlightedPositionAcceptor acceptor) {
		while (node instanceof ICompositeNode) {
			node = ((ICompositeNode) node).getLastChild();
		}

		if (node == null || node.getGrammarElement() instanceof Keyword) {
			return;
		}

		acceptor.addPosition(node.getOffset(), node.getLength(),
				MyFileHighlightingConfiguration.FEATURE_REF);
	}

}
