package org.mybuild.myfile.conversions;

import org.eclipse.xtext.conversion.ValueConverterException;
import org.eclipse.xtext.conversion.impl.STRINGValueConverter;
import org.eclipse.xtext.nodemodel.INode;
import org.eclipse.xtext.util.Strings;

public class TripleQuotedStringConverter extends STRINGValueConverter {

	@Override
	public String toValue(String string, INode node) {
		if (string == null) {
			return null;
		}

		if (string.startsWith("'''") && string.endsWith("'''")) {
			try {
				return Strings.convertFromJavaString(
						string.substring(3, string.length() - 3), false);
			} catch (IllegalArgumentException e) {
				throw new ValueConverterException(e.getMessage(), node, e);
			}
		} else {
			return super.toValue(string, node);
		}
	}

}
