/*
* generated by Xtext
*/
package org.embuild.emdsl.parser.antlr;

import java.io.InputStream;
import org.eclipse.xtext.parser.antlr.IAntlrTokenFileProvider;

public class EmDslAntlrTokenFileProvider implements IAntlrTokenFileProvider {
	
	public InputStream getAntlrTokenFile() {
		ClassLoader classLoader = getClass().getClassLoader();
    	return classLoader.getResourceAsStream("org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.tokens");
	}
}
