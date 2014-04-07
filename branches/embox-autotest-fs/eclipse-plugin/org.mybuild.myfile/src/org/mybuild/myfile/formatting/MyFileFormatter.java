package org.mybuild.myfile.formatting;

import org.eclipse.xtext.Keyword;
import org.eclipse.xtext.formatting.impl.AbstractDeclarativeFormatter;
import org.eclipse.xtext.formatting.impl.FormattingConfig;
import org.eclipse.xtext.util.Pair;
import org.mybuild.myfile.services.MyFileGrammarAccess;
import org.mybuild.myfile.services.MyFileGrammarAccess.AnnotationElements;

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

		c.setLinewrap(0, 1, 2).around(f.getMemberRule());

		for (Pair<Keyword, Keyword> braces : f.findKeywordPairs("{", "}")) {
			c.setIndentation(braces.getFirst(), braces.getSecond());
		}

		for (Pair<Keyword, Keyword> parens : f.findKeywordPairs("(", ")")) {
			c.setNoSpace().after(parens.getFirst());
			c.setNoSpace().before(parens.getSecond());
		}
		
		for (Keyword comma : f.findKeywords(",")) {
			c.setNoSpace().before(comma);
		}
		
		AnnotationElements ann = f.getAnnotationAccess();
		c.setNoSpace().after(ann.getCommercialAtKeyword_0());
		c.setNoSpace().before(ann.getLeftParenthesisKeyword_2_0());

		c.setLinewrap(0, 1, 2).before(f.getSL_COMMENTRule());
		c.setLinewrap(0, 1, 2).before(f.getML_COMMENTRule());

		c.setLinewrap(0, 1, 1).after(f.getSL_COMMENTRule());
		c.setLinewrap(0, 1, 1).after(f.getML_COMMENTRule());
	}
}
