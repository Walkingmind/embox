/*
* generated by Xtext
*/

package org.embuild.emdsl.services;

import com.google.inject.Singleton;
import com.google.inject.Inject;

import org.eclipse.xtext.*;
import org.eclipse.xtext.service.GrammarProvider;
import org.eclipse.xtext.service.AbstractElementFinder.*;

import org.eclipse.xtext.common.services.TerminalsGrammarAccess;

@Singleton
public class EmDslGrammarAccess extends AbstractGrammarElementFinder {
	
	
	public class ModelElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "Model");
		private final Assignment cElementsAssignment = (Assignment)rule.eContents().get(1);
		private final RuleCall cElementsEntityParserRuleCall_0 = (RuleCall)cElementsAssignment.eContents().get(0);
		
		//Model:
		//	elements+=Entity*;
		public ParserRule getRule() { return rule; }

		//elements+=Entity*
		public Assignment getElementsAssignment() { return cElementsAssignment; }

		//Entity
		public RuleCall getElementsEntityParserRuleCall_0() { return cElementsEntityParserRuleCall_0; }
	}

	public class EntityElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "Entity");
		private final RuleCall cModuleParserRuleCall = (RuleCall)rule.eContents().get(1);
		
		//Entity:
		//	Module;
		public ParserRule getRule() { return rule; }

		//Module
		public RuleCall getModuleParserRuleCall() { return cModuleParserRuleCall; }
	}

	public class ModifierElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "Modifier");
		private final Assignment cAbstractAssignment = (Assignment)rule.eContents().get(1);
		private final Keyword cAbstractAbstractKeyword_0 = (Keyword)cAbstractAssignment.eContents().get(0);
		
		//Modifier:
		//	abstract?="abstract";
		public ParserRule getRule() { return rule; }

		//abstract?="abstract"
		public Assignment getAbstractAssignment() { return cAbstractAssignment; }

		//"abstract"
		public Keyword getAbstractAbstractKeyword_0() { return cAbstractAbstractKeyword_0; }
	}

	public class ModuleElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "Module");
		private final Group cGroup = (Group)rule.eContents().get(1);
		private final RuleCall cModifierParserRuleCall_0 = (RuleCall)cGroup.eContents().get(0);
		private final Keyword cModuleKeyword_1 = (Keyword)cGroup.eContents().get(1);
		private final Assignment cNameAssignment_2 = (Assignment)cGroup.eContents().get(2);
		private final RuleCall cNameIDTerminalRuleCall_2_0 = (RuleCall)cNameAssignment_2.eContents().get(0);
		private final Group cGroup_3 = (Group)cGroup.eContents().get(3);
		private final Keyword cExtendsKeyword_3_0 = (Keyword)cGroup_3.eContents().get(0);
		private final Assignment cSuperTypeAssignment_3_1 = (Assignment)cGroup_3.eContents().get(1);
		private final CrossReference cSuperTypeModuleCrossReference_3_1_0 = (CrossReference)cSuperTypeAssignment_3_1.eContents().get(0);
		private final RuleCall cSuperTypeModuleQualifiedNameParserRuleCall_3_1_0_1 = (RuleCall)cSuperTypeModuleCrossReference_3_1_0.eContents().get(1);
		private final Keyword cLeftCurlyBracketKeyword_4 = (Keyword)cGroup.eContents().get(4);
		private final Assignment cFeaturesAssignment_5 = (Assignment)cGroup.eContents().get(5);
		private final RuleCall cFeaturesFeatureParserRuleCall_5_0 = (RuleCall)cFeaturesAssignment_5.eContents().get(0);
		private final Keyword cRightCurlyBracketKeyword_6 = (Keyword)cGroup.eContents().get(6);
		
		//Module:
		//	Modifier? "module" name=ID ("extends" superType=[Module|QualifiedName])? "{" features+=Feature* "}";
		public ParserRule getRule() { return rule; }

		//Modifier? "module" name=ID ("extends" superType=[Module|QualifiedName])? "{" features+=Feature* "}"
		public Group getGroup() { return cGroup; }

		//Modifier?
		public RuleCall getModifierParserRuleCall_0() { return cModifierParserRuleCall_0; }

		//"module"
		public Keyword getModuleKeyword_1() { return cModuleKeyword_1; }

		//name=ID
		public Assignment getNameAssignment_2() { return cNameAssignment_2; }

		//ID
		public RuleCall getNameIDTerminalRuleCall_2_0() { return cNameIDTerminalRuleCall_2_0; }

		//("extends" superType=[Module|QualifiedName])?
		public Group getGroup_3() { return cGroup_3; }

		//"extends"
		public Keyword getExtendsKeyword_3_0() { return cExtendsKeyword_3_0; }

		//superType=[Module|QualifiedName]
		public Assignment getSuperTypeAssignment_3_1() { return cSuperTypeAssignment_3_1; }

		//[Module|QualifiedName]
		public CrossReference getSuperTypeModuleCrossReference_3_1_0() { return cSuperTypeModuleCrossReference_3_1_0; }

		//QualifiedName
		public RuleCall getSuperTypeModuleQualifiedNameParserRuleCall_3_1_0_1() { return cSuperTypeModuleQualifiedNameParserRuleCall_3_1_0_1; }

		//"{"
		public Keyword getLeftCurlyBracketKeyword_4() { return cLeftCurlyBracketKeyword_4; }

		//features+=Feature*
		public Assignment getFeaturesAssignment_5() { return cFeaturesAssignment_5; }

		//Feature
		public RuleCall getFeaturesFeatureParserRuleCall_5_0() { return cFeaturesFeatureParserRuleCall_5_0; }

		//"}"
		public Keyword getRightCurlyBracketKeyword_6() { return cRightCurlyBracketKeyword_6; }
	}

	public class FeatureElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "Feature");
		private final Alternatives cAlternatives = (Alternatives)rule.eContents().get(1);
		private final RuleCall cSourceFeatureParserRuleCall_0 = (RuleCall)cAlternatives.eContents().get(0);
		private final RuleCall cDependFeatureParserRuleCall_1 = (RuleCall)cAlternatives.eContents().get(1);
		
		//Feature:
		//	SourceFeature | DependFeature;
		public ParserRule getRule() { return rule; }

		//SourceFeature | DependFeature
		public Alternatives getAlternatives() { return cAlternatives; }

		//SourceFeature
		public RuleCall getSourceFeatureParserRuleCall_0() { return cSourceFeatureParserRuleCall_0; }

		//DependFeature
		public RuleCall getDependFeatureParserRuleCall_1() { return cDependFeatureParserRuleCall_1; }
	}

	public class SourceFeatureElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "SourceFeature");
		private final Group cGroup = (Group)rule.eContents().get(1);
		private final Keyword cSourceKeyword_0 = (Keyword)cGroup.eContents().get(0);
		private final Assignment cFilenamesAssignment_1 = (Assignment)cGroup.eContents().get(1);
		private final RuleCall cFilenamesFilenameParserRuleCall_1_0 = (RuleCall)cFilenamesAssignment_1.eContents().get(0);
		
		//SourceFeature:
		//	"source" filenames+=Filename+;
		public ParserRule getRule() { return rule; }

		//"source" filenames+=Filename+
		public Group getGroup() { return cGroup; }

		//"source"
		public Keyword getSourceKeyword_0() { return cSourceKeyword_0; }

		//filenames+=Filename+
		public Assignment getFilenamesAssignment_1() { return cFilenamesAssignment_1; }

		//Filename
		public RuleCall getFilenamesFilenameParserRuleCall_1_0() { return cFilenamesFilenameParserRuleCall_1_0; }
	}

	public class FilenameElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "Filename");
		private final RuleCall cSTRINGTerminalRuleCall = (RuleCall)rule.eContents().get(1);
		
		//Filename:
		//	STRING;
		public ParserRule getRule() { return rule; }

		//STRING
		public RuleCall getSTRINGTerminalRuleCall() { return cSTRINGTerminalRuleCall; }
	}

	public class DependFeatureElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "DependFeature");
		private final Group cGroup = (Group)rule.eContents().get(1);
		private final Keyword cDependKeyword_0 = (Keyword)cGroup.eContents().get(0);
		private final Assignment cModulesAssignment_1 = (Assignment)cGroup.eContents().get(1);
		private final CrossReference cModulesModuleCrossReference_1_0 = (CrossReference)cModulesAssignment_1.eContents().get(0);
		private final RuleCall cModulesModuleIDTerminalRuleCall_1_0_1 = (RuleCall)cModulesModuleCrossReference_1_0.eContents().get(1);
		
		//DependFeature:
		//	"depend" modules+=[Module]+;
		public ParserRule getRule() { return rule; }

		//"depend" modules+=[Module]+
		public Group getGroup() { return cGroup; }

		//"depend"
		public Keyword getDependKeyword_0() { return cDependKeyword_0; }

		//modules+=[Module]+
		public Assignment getModulesAssignment_1() { return cModulesAssignment_1; }

		//[Module]
		public CrossReference getModulesModuleCrossReference_1_0() { return cModulesModuleCrossReference_1_0; }

		//ID
		public RuleCall getModulesModuleIDTerminalRuleCall_1_0_1() { return cModulesModuleIDTerminalRuleCall_1_0_1; }
	}

	public class QualifiedNameElements extends AbstractParserRuleElementFinder {
		private final ParserRule rule = (ParserRule) GrammarUtil.findRuleForName(getGrammar(), "QualifiedName");
		private final Group cGroup = (Group)rule.eContents().get(1);
		private final RuleCall cIDTerminalRuleCall_0 = (RuleCall)cGroup.eContents().get(0);
		private final Group cGroup_1 = (Group)cGroup.eContents().get(1);
		private final Keyword cFullStopKeyword_1_0 = (Keyword)cGroup_1.eContents().get(0);
		private final RuleCall cIDTerminalRuleCall_1_1 = (RuleCall)cGroup_1.eContents().get(1);
		
		//QualifiedName:
		//	ID ("." ID)*;
		public ParserRule getRule() { return rule; }

		//ID ("." ID)*
		public Group getGroup() { return cGroup; }

		//ID
		public RuleCall getIDTerminalRuleCall_0() { return cIDTerminalRuleCall_0; }

		//("." ID)*
		public Group getGroup_1() { return cGroup_1; }

		//"."
		public Keyword getFullStopKeyword_1_0() { return cFullStopKeyword_1_0; }

		//ID
		public RuleCall getIDTerminalRuleCall_1_1() { return cIDTerminalRuleCall_1_1; }
	}
	
	
	private ModelElements pModel;
	private EntityElements pEntity;
	private ModifierElements pModifier;
	private ModuleElements pModule;
	private FeatureElements pFeature;
	private SourceFeatureElements pSourceFeature;
	private FilenameElements pFilename;
	private DependFeatureElements pDependFeature;
	private QualifiedNameElements pQualifiedName;
	
	private final GrammarProvider grammarProvider;

	private TerminalsGrammarAccess gaTerminals;

	@Inject
	public EmDslGrammarAccess(GrammarProvider grammarProvider,
		TerminalsGrammarAccess gaTerminals) {
		this.grammarProvider = grammarProvider;
		this.gaTerminals = gaTerminals;
	}
	
	public Grammar getGrammar() {	
		return grammarProvider.getGrammar(this);
	}
	

	public TerminalsGrammarAccess getTerminalsGrammarAccess() {
		return gaTerminals;
	}

	
	//Model:
	//	elements+=Entity*;
	public ModelElements getModelAccess() {
		return (pModel != null) ? pModel : (pModel = new ModelElements());
	}
	
	public ParserRule getModelRule() {
		return getModelAccess().getRule();
	}

	//Entity:
	//	Module;
	public EntityElements getEntityAccess() {
		return (pEntity != null) ? pEntity : (pEntity = new EntityElements());
	}
	
	public ParserRule getEntityRule() {
		return getEntityAccess().getRule();
	}

	//Modifier:
	//	abstract?="abstract";
	public ModifierElements getModifierAccess() {
		return (pModifier != null) ? pModifier : (pModifier = new ModifierElements());
	}
	
	public ParserRule getModifierRule() {
		return getModifierAccess().getRule();
	}

	//Module:
	//	Modifier? "module" name=ID ("extends" superType=[Module|QualifiedName])? "{" features+=Feature* "}";
	public ModuleElements getModuleAccess() {
		return (pModule != null) ? pModule : (pModule = new ModuleElements());
	}
	
	public ParserRule getModuleRule() {
		return getModuleAccess().getRule();
	}

	//Feature:
	//	SourceFeature | DependFeature;
	public FeatureElements getFeatureAccess() {
		return (pFeature != null) ? pFeature : (pFeature = new FeatureElements());
	}
	
	public ParserRule getFeatureRule() {
		return getFeatureAccess().getRule();
	}

	//SourceFeature:
	//	"source" filenames+=Filename+;
	public SourceFeatureElements getSourceFeatureAccess() {
		return (pSourceFeature != null) ? pSourceFeature : (pSourceFeature = new SourceFeatureElements());
	}
	
	public ParserRule getSourceFeatureRule() {
		return getSourceFeatureAccess().getRule();
	}

	//Filename:
	//	STRING;
	public FilenameElements getFilenameAccess() {
		return (pFilename != null) ? pFilename : (pFilename = new FilenameElements());
	}
	
	public ParserRule getFilenameRule() {
		return getFilenameAccess().getRule();
	}

	//DependFeature:
	//	"depend" modules+=[Module]+;
	public DependFeatureElements getDependFeatureAccess() {
		return (pDependFeature != null) ? pDependFeature : (pDependFeature = new DependFeatureElements());
	}
	
	public ParserRule getDependFeatureRule() {
		return getDependFeatureAccess().getRule();
	}

	//QualifiedName:
	//	ID ("." ID)*;
	public QualifiedNameElements getQualifiedNameAccess() {
		return (pQualifiedName != null) ? pQualifiedName : (pQualifiedName = new QualifiedNameElements());
	}
	
	public ParserRule getQualifiedNameRule() {
		return getQualifiedNameAccess().getRule();
	}

	//terminal ID:
	//	"^"? ("a".."z" | "A".."Z" | "_") ("a".."z" | "A".."Z" | "_" | "0".."9")*;
	public TerminalRule getIDRule() {
		return gaTerminals.getIDRule();
	} 

	//terminal INT returns ecore::EInt:
	//	"0".."9"+;
	public TerminalRule getINTRule() {
		return gaTerminals.getINTRule();
	} 

	//terminal STRING:
	//	"\"" ("\\" ("b" | "t" | "n" | "f" | "r" | "u" | "\"" | "\'" | "\\") | !("\\" | "\""))* "\"" | "\'" ("\\" ("b" | "t" |
	//	"n" | "f" | "r" | "u" | "\"" | "\'" | "\\") | !("\\" | "\'"))* "\'";
	public TerminalRule getSTRINGRule() {
		return gaTerminals.getSTRINGRule();
	} 

	//terminal ML_COMMENT:
	//	"/ *"->"* /";
	public TerminalRule getML_COMMENTRule() {
		return gaTerminals.getML_COMMENTRule();
	} 

	//terminal SL_COMMENT:
	//	"//" !("\n" | "\r")* ("\r"? "\n")?;
	public TerminalRule getSL_COMMENTRule() {
		return gaTerminals.getSL_COMMENTRule();
	} 

	//terminal WS:
	//	(" " | "\t" | "\r" | "\n")+;
	public TerminalRule getWSRule() {
		return gaTerminals.getWSRule();
	} 

	//terminal ANY_OTHER:
	//	.;
	public TerminalRule getANY_OTHERRule() {
		return gaTerminals.getANY_OTHERRule();
	} 
}
