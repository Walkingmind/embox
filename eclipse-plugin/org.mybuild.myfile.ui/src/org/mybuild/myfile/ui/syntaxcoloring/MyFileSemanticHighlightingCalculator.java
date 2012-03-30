package org.mybuild.myfile.ui.syntaxcoloring;

import java.util.List;

import org.eclipse.emf.common.util.TreeIterator;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.xtext.nodemodel.ICompositeNode;
import org.eclipse.xtext.nodemodel.ILeafNode;
import org.eclipse.xtext.nodemodel.INode;
import org.eclipse.xtext.nodemodel.util.NodeModelUtils;
import org.eclipse.xtext.resource.XtextResource;
import org.eclipse.xtext.ui.editor.syntaxcoloring.IHighlightedPositionAcceptor;
import org.eclipse.xtext.ui.editor.syntaxcoloring.ISemanticHighlightingCalculator;
import org.mybuild.myfile.AbstractFeatureListMember;
import org.mybuild.myfile.Annotation;
import org.mybuild.myfile.AnnotationType;
import org.mybuild.myfile.Feature;
import org.mybuild.myfile.MyFilePackage;

/*
 * The most of code is taken from XbaseHighlightingCalculator. -- Eldar
 */
public class MyFileSemanticHighlightingCalculator implements
		ISemanticHighlightingCalculator {

	public void provideHighlightingFor(final XtextResource resource,
			IHighlightedPositionAcceptor acceptor) {
		if (resource == null || resource.getParseResult() == null
				|| resource.getParseResult().getRootASTElement() == null)
			return;

		TreeIterator<EObject> iterator = resource.getAllContents();
		while (iterator.hasNext()) {
			EObject object = iterator.next();
			if (object instanceof Annotation) {
				highlightAnnotation((Annotation) object, acceptor);
			} else if (object instanceof AbstractFeatureListMember) {
				highlightFeatureReference((AbstractFeatureListMember) object,
						acceptor);
			}
		}
	}

	protected void highlightFeatureReference(AbstractFeatureListMember member,
			IHighlightedPositionAcceptor acceptor) {
		for (Feature feature : member.getFeatures()) {
			if (!feature.eIsProxy()) {
				highlightObjectAtFeature(
						acceptor,
						feature,
						MyFilePackage.Literals.ABSTRACT_FEATURE_LIST_MEMBER__FEATURES,
						MyFileHighlightingConfiguration.FEATURE_REFERENCE);
			}
		}
	}

	protected void highlightAnnotation(Annotation annotation,
			IHighlightedPositionAcceptor acceptor) {
		AnnotationType annotationType = annotation.getType();
		if (annotationType != null && !annotationType.eIsProxy()) {
			// Handle Annotation in a special way because of @ sign.
			ICompositeNode annotationNode = NodeModelUtils
					.findActualNodeFor(annotation);
			ILeafNode firstLeafNode = NodeModelUtils.findLeafNodeAtOffset(
					annotationNode, annotationNode.getOffset());
			if (firstLeafNode != null)
				highlightNode(
						firstLeafNode,
						MyFileHighlightingConfiguration.ANNOTATION_TYPE_REFERENCE,
						acceptor);
			highlightObjectAtFeature(acceptor, annotation,
					MyFilePackage.Literals.ANNOTATION__TYPE,
					MyFileHighlightingConfiguration.ANNOTATION_TYPE_REFERENCE);
		}
	}

	protected void highlightObjectAtFeature(
			IHighlightedPositionAcceptor acceptor, EObject object,
			EStructuralFeature feature, String id) {
		List<INode> childs = NodeModelUtils
				.findNodesForFeature(object, feature);
		if (childs.size() > 0)
			highlightNode(childs.get(0), id, acceptor);
	}

	protected void highlightNode(INode node, String id,
			IHighlightedPositionAcceptor acceptor) {
		if (node == null)
			return;
		if (node instanceof ILeafNode) {
			acceptor.addPosition(node.getOffset(), node.getLength(), id);
		} else {
			for (ILeafNode leaf : node.getLeafNodes()) {
				if (!leaf.isHidden()) {
					acceptor.addPosition(leaf.getOffset(), leaf.getLength(), id);
				}
			}
		}
	}

}
