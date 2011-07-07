/*
* generated by Xtext
*/
package org.embuild.emdsl.parser.antlr;

import com.google.inject.Inject;

import org.eclipse.xtext.parser.antlr.XtextTokenStream;
import org.embuild.emdsl.services.EmDslGrammarAccess;

public class EmDslParser extends org.eclipse.xtext.parser.antlr.AbstractAntlrParser {
	
	@Inject
	private EmDslGrammarAccess grammarAccess;
	
	@Override
	protected void setInitialHiddenTokens(XtextTokenStream tokenStream) {
		tokenStream.setInitialHiddenTokens("RULE_WS", "RULE_ML_COMMENT", "RULE_SL_COMMENT");
	}
	
	@Override
	protected org.embuild.emdsl.parser.antlr.internal.InternalEmDslParser createParser(XtextTokenStream stream) {
		return new org.embuild.emdsl.parser.antlr.internal.InternalEmDslParser(stream, getGrammarAccess());
	}
	
	@Override 
	protected String getDefaultRuleName() {
		return "Model";
	}
	
	public EmDslGrammarAccess getGrammarAccess() {
		return this.grammarAccess;
	}
	
	public void setGrammarAccess(EmDslGrammarAccess grammarAccess) {
		this.grammarAccess = grammarAccess;
	}
	
}
