package org.mybuild.myfile.ui.syntaxcoloring;

import org.eclipse.jface.text.TextAttribute;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.xtext.ui.editor.syntaxcoloring.DefaultHighlightingConfiguration;
import org.eclipse.xtext.ui.editor.syntaxcoloring.IHighlightingConfigurationAcceptor;
import org.eclipse.xtext.ui.editor.utils.TextStyle;

/**
 * 
 * @author Eldar Abusalimov
 */
public class MyFileHighlightingConfiguration extends
		DefaultHighlightingConfiguration {

	public final static String FEATURE_REFERENCE = "mybuild.FeatureReference";
	public final static String ANNOTATION_TYPE_REFERENCE = "mybuild.AnnotationTypeReference";
	public static final String DEPRECATED = "mybuild.Deprecated";

	@Override
	public void configure(IHighlightingConfigurationAcceptor acceptor) {
		super.configure(acceptor);
		acceptor.acceptDefaultHighlighting(FEATURE_REFERENCE,
				"Feature Reference", featureReferenceTextStyle());
		acceptor.acceptDefaultHighlighting(ANNOTATION_TYPE_REFERENCE,
				"Annotation", annotationTypeReferenceTextStyle());
		acceptor.acceptDefaultHighlighting(DEPRECATED, "Deprecated",
				deprecated());
	}

	public TextStyle featureReferenceTextStyle() {
		TextStyle textStyle = defaultTextStyle().copy();
		textStyle.setStyle(SWT.ITALIC);
		return textStyle;
	}

	public TextStyle annotationTypeReferenceTextStyle() {
		TextStyle textStyle = defaultTextStyle().copy();
		textStyle.setColor(new RGB(100, 100, 100));
		return textStyle;
	}

	public TextStyle deprecated() {
		TextStyle textStyle = defaultTextStyle().copy();
		textStyle.setStyle(TextAttribute.STRIKETHROUGH);
		return textStyle;
	}
}
