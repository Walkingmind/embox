package org.mybuild.myfile.formatting;

import org.eclipse.xtext.Keyword;
import org.eclipse.xtext.formatting.impl.AbstractDeclarativeFormatter;
import org.eclipse.xtext.formatting.impl.FormattingConfig;
import org.eclipse.xtext.util.Pair;
import org.mybuild.myfile.services.MyFileGrammarAccess;

/**
 * This class contains custom formatting description.
 * 
 * see : http://www.eclipse.org/Xtext/documentation/latest/xtext.html#formatting
 * on how and when to use it
 * 
 * Also see {@link org.eclipse.xtext.xtext.XtextFormattingTokenSerializer} as an
 * example
 */
public class MyFileFormatter extends AbstractDeclarativeFormatter {

	@Override
	protected void configureFormatting(FormattingConfig c) {
		MyFileGrammarAccess f = (MyFileGrammarAccess) getGrammarAccess();

		c.setAutoLinewrap(80);

		c.setLinewrap(0, 1, 1).before(f.getPackageRule());
		c.setLinewrap(2).after(f.getPackageRule());

		c.setLinewrap(1, 2, 2).around(f.getModuleRule());
		c.setLinewrap(1, 2, 2).around(f.getFeatureRule());

		for (Pair<Keyword, Keyword> pair : f.findKeywordPairs("{", "}")) {
			c.setIndentation(pair.getFirst(), pair.getSecond());
		}

		for (Keyword comma : f.findKeywords(",")) {
			c.setNoSpace().before(comma);
		}

//		for (Keyword semicolon : f.findKeywords(";")) {
//			c.setNoSpace().before(semicolon);
//			c.setLinewrap().after(semicolon);
//		}

		c.setLinewrap(0, 1, 2).before(f.getSL_COMMENTRule());
		c.setLinewrap(0, 1, 2).before(f.getML_COMMENTRule());

		c.setLinewrap(0, 1, 1).after(f.getSL_COMMENTRule());
		c.setLinewrap(0, 1, 1).after(f.getML_COMMENTRule());
	}
}
