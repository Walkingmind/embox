package org.mybuild.myfile.ui;

import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.eclipse.xtext.ui.editor.hyperlinking.IHyperlinkHelper;
import org.eclipse.xtext.ui.editor.syntaxcoloring.IHighlightingConfiguration;
import org.eclipse.xtext.ui.editor.syntaxcoloring.ISemanticHighlightingCalculator;
import org.mybuild.myfile.ui.navigation.MyFileHyperlinkHelper;
import org.mybuild.myfile.ui.syntaxcoloring.MyFileHighlightingConfiguration;
import org.mybuild.myfile.ui.syntaxcoloring.MyFileSemanticHighlightingCalculator;

/**
 * Use this class to register components to be used within the IDE.
 */
public class MyFileUiModule extends
		org.mybuild.myfile.ui.AbstractMyFileUiModule {
	public MyFileUiModule(AbstractUIPlugin plugin) {
		super(plugin);
	}

	@Override
	public Class<? extends IHyperlinkHelper> bindIHyperlinkHelper() {
		return MyFileHyperlinkHelper.class;
	}

	public Class<? extends ISemanticHighlightingCalculator> bindISemanticHighlightingCalculator() {
		return MyFileSemanticHighlightingCalculator.class;
	}

	public Class<? extends IHighlightingConfiguration> bindIHighlightingConfiguration() {
		return MyFileHighlightingConfiguration.class;
	}

}
