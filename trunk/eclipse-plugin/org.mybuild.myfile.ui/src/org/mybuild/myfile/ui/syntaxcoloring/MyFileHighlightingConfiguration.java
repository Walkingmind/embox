package org.mybuild.myfile.ui.syntaxcoloring;

import org.eclipse.swt.SWT;
import org.eclipse.xtext.ui.editor.syntaxcoloring.DefaultHighlightingConfiguration;
import org.eclipse.xtext.ui.editor.syntaxcoloring.IHighlightingConfigurationAcceptor;
import org.eclipse.xtext.ui.editor.utils.TextStyle;

/**
 * 
 * @author Eldar Abusalimov
 */
public class MyFileHighlightingConfiguration extends
		DefaultHighlightingConfiguration {

	public final static String FEATURE_REF = "FeatureReference";

	@Override
	public void configure(IHighlightingConfigurationAcceptor acceptor) {
		super.configure(acceptor);
		acceptor.acceptDefaultHighlighting(FEATURE_REF, "Feature References",
				featureReferenceTextStyle());
	}

	public TextStyle featureReferenceTextStyle() {
		TextStyle textStyle = defaultTextStyle().copy();
		textStyle.setStyle(SWT.ITALIC);
		return textStyle;
	}
}
