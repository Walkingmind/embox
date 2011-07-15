/*
* generated by Xtext
*/
grammar InternalEmDsl;

options {
	superClass=AbstractInternalAntlrParser;
	
}

@lexer::header {
package org.embuild.emdsl.parser.antlr.internal;

// Hack: Use our own Lexer superclass by means of import. 
// Currently there is no other way to specify the superclass for the lexer.
import org.eclipse.xtext.parser.antlr.Lexer;
}

@parser::header {
package org.embuild.emdsl.parser.antlr.internal; 

import org.eclipse.xtext.*;
import org.eclipse.xtext.parser.*;
import org.eclipse.xtext.parser.impl.*;
import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.xtext.parser.antlr.AbstractInternalAntlrParser;
import org.eclipse.xtext.parser.antlr.XtextTokenStream;
import org.eclipse.xtext.parser.antlr.XtextTokenStream.HiddenTokens;
import org.eclipse.xtext.parser.antlr.AntlrDatatypeRuleToken;
import org.embuild.emdsl.services.EmDslGrammarAccess;

}

@parser::members {

 	private EmDslGrammarAccess grammarAccess;
 	
    public InternalEmDslParser(TokenStream input, EmDslGrammarAccess grammarAccess) {
        this(input);
        this.grammarAccess = grammarAccess;
        registerRules(grammarAccess.getGrammar());
    }
    
    @Override
    protected String getFirstRuleName() {
    	return "Model";	
   	}
   	
   	@Override
   	protected EmDslGrammarAccess getGrammarAccess() {
   		return grammarAccess;
   	}
}

@rulecatch { 
    catch (RecognitionException re) { 
        recover(input,re); 
        appendSkippedTokens();
    } 
}




// Entry rule entryRuleModel
entryRuleModel returns [EObject current=null] 
	:
	{ newCompositeNode(grammarAccess.getModelRule()); }
	 iv_ruleModel=ruleModel 
	 { $current=$iv_ruleModel.current; } 
	 EOF 
;

// Rule Model
ruleModel returns [EObject current=null] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
(
(
		{ 
	        newCompositeNode(grammarAccess.getModelAccess().getElementsEntityParserRuleCall_0()); 
	    }
		lv_elements_0_0=ruleEntity		{
	        if ($current==null) {
	            $current = createModelElementForParent(grammarAccess.getModelRule());
	        }
       		add(
       			$current, 
       			"elements",
        		lv_elements_0_0, 
        		"Entity");
	        afterParserOrEnumRuleCall();
	    }

)
)*
;





// Entry rule entryRuleEntity
entryRuleEntity returns [EObject current=null] 
	:
	{ newCompositeNode(grammarAccess.getEntityRule()); }
	 iv_ruleEntity=ruleEntity 
	 { $current=$iv_ruleEntity.current; } 
	 EOF 
;

// Rule Entity
ruleEntity returns [EObject current=null] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:

    { 
        newCompositeNode(grammarAccess.getEntityAccess().getModuleParserRuleCall()); 
    }
    this_Module_0=ruleModule
    { 
        $current = $this_Module_0.current; 
        afterParserOrEnumRuleCall();
    }

;





// Entry rule entryRuleModifier
entryRuleModifier returns [EObject current=null] 
	:
	{ newCompositeNode(grammarAccess.getModifierRule()); }
	 iv_ruleModifier=ruleModifier 
	 { $current=$iv_ruleModifier.current; } 
	 EOF 
;

// Rule Modifier
ruleModifier returns [EObject current=null] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
(
(
		lv_abstract_0_0=	'abstract' 
    {
        newLeafNode(lv_abstract_0_0, grammarAccess.getModifierAccess().getAbstractAbstractKeyword_0());
    }
 
	    {
	        if ($current==null) {
	            $current = createModelElement(grammarAccess.getModifierRule());
	        }
       		setWithLastConsumed($current, "abstract", true, "abstract");
	    }

)
)
;





// Entry rule entryRuleModule
entryRuleModule returns [EObject current=null] 
	:
	{ newCompositeNode(grammarAccess.getModuleRule()); }
	 iv_ruleModule=ruleModule 
	 { $current=$iv_ruleModule.current; } 
	 EOF 
;

// Rule Module
ruleModule returns [EObject current=null] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
((
    { 
        newCompositeNode(grammarAccess.getModuleAccess().getModifierParserRuleCall_0()); 
    }
    this_Modifier_0=ruleModifier
    { 
        $current = $this_Modifier_0.current; 
        afterParserOrEnumRuleCall();
    }
)?	otherlv_1='module' 
    {
    	newLeafNode(otherlv_1, grammarAccess.getModuleAccess().getModuleKeyword_1());
    }
(
(
		lv_name_2_0=RULE_ID
		{
			newLeafNode(lv_name_2_0, grammarAccess.getModuleAccess().getNameIDTerminalRuleCall_2_0()); 
		}
		{
	        if ($current==null) {
	            $current = createModelElement(grammarAccess.getModuleRule());
	        }
       		setWithLastConsumed(
       			$current, 
       			"name",
        		lv_name_2_0, 
        		"ID");
	    }

)
)(	otherlv_3='extends' 
    {
    	newLeafNode(otherlv_3, grammarAccess.getModuleAccess().getExtendsKeyword_3_0());
    }
(
(
		{
			if ($current==null) {
	            $current = createModelElement(grammarAccess.getModuleRule());
	        }
        }
		{ 
	        newCompositeNode(grammarAccess.getModuleAccess().getSuperTypeModuleCrossReference_3_1_0()); 
	    }
		ruleQualifiedName		{ 
	        afterParserOrEnumRuleCall();
	    }

)
))?	otherlv_5='{' 
    {
    	newLeafNode(otherlv_5, grammarAccess.getModuleAccess().getLeftCurlyBracketKeyword_4());
    }
(
(
		{ 
	        newCompositeNode(grammarAccess.getModuleAccess().getFeaturesFeatureParserRuleCall_5_0()); 
	    }
		lv_features_6_0=ruleFeature		{
	        if ($current==null) {
	            $current = createModelElementForParent(grammarAccess.getModuleRule());
	        }
       		add(
       			$current, 
       			"features",
        		lv_features_6_0, 
        		"Feature");
	        afterParserOrEnumRuleCall();
	    }

)
)*	otherlv_7='}' 
    {
    	newLeafNode(otherlv_7, grammarAccess.getModuleAccess().getRightCurlyBracketKeyword_6());
    }
)
;





// Entry rule entryRuleFeature
entryRuleFeature returns [EObject current=null] 
	:
	{ newCompositeNode(grammarAccess.getFeatureRule()); }
	 iv_ruleFeature=ruleFeature 
	 { $current=$iv_ruleFeature.current; } 
	 EOF 
;

// Rule Feature
ruleFeature returns [EObject current=null] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
(
    { 
        newCompositeNode(grammarAccess.getFeatureAccess().getSourceFeatureParserRuleCall_0()); 
    }
    this_SourceFeature_0=ruleSourceFeature
    { 
        $current = $this_SourceFeature_0.current; 
        afterParserOrEnumRuleCall();
    }

    |
    { 
        newCompositeNode(grammarAccess.getFeatureAccess().getDependFeatureParserRuleCall_1()); 
    }
    this_DependFeature_1=ruleDependFeature
    { 
        $current = $this_DependFeature_1.current; 
        afterParserOrEnumRuleCall();
    }
)
;





// Entry rule entryRuleSourceFeature
entryRuleSourceFeature returns [EObject current=null] 
	:
	{ newCompositeNode(grammarAccess.getSourceFeatureRule()); }
	 iv_ruleSourceFeature=ruleSourceFeature 
	 { $current=$iv_ruleSourceFeature.current; } 
	 EOF 
;

// Rule SourceFeature
ruleSourceFeature returns [EObject current=null] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
(	otherlv_0='source' 
    {
    	newLeafNode(otherlv_0, grammarAccess.getSourceFeatureAccess().getSourceKeyword_0());
    }
(
(
		{ 
	        newCompositeNode(grammarAccess.getSourceFeatureAccess().getFilenamesFilenameParserRuleCall_1_0()); 
	    }
		lv_filenames_1_0=ruleFilename		{
	        if ($current==null) {
	            $current = createModelElementForParent(grammarAccess.getSourceFeatureRule());
	        }
       		add(
       			$current, 
       			"filenames",
        		lv_filenames_1_0, 
        		"Filename");
	        afterParserOrEnumRuleCall();
	    }

)
)+)
;





// Entry rule entryRuleFilename
entryRuleFilename returns [String current=null] 
	:
	{ newCompositeNode(grammarAccess.getFilenameRule()); } 
	 iv_ruleFilename=ruleFilename 
	 { $current=$iv_ruleFilename.current.getText(); }  
	 EOF 
;

// Rule Filename
ruleFilename returns [AntlrDatatypeRuleToken current=new AntlrDatatypeRuleToken()] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
    this_STRING_0=RULE_STRING    {
		$current.merge(this_STRING_0);
    }

    { 
    newLeafNode(this_STRING_0, grammarAccess.getFilenameAccess().getSTRINGTerminalRuleCall()); 
    }

    ;





// Entry rule entryRuleDependFeature
entryRuleDependFeature returns [EObject current=null] 
	:
	{ newCompositeNode(grammarAccess.getDependFeatureRule()); }
	 iv_ruleDependFeature=ruleDependFeature 
	 { $current=$iv_ruleDependFeature.current; } 
	 EOF 
;

// Rule DependFeature
ruleDependFeature returns [EObject current=null] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
(	otherlv_0='depend' 
    {
    	newLeafNode(otherlv_0, grammarAccess.getDependFeatureAccess().getDependKeyword_0());
    }
(
(
		{
			if ($current==null) {
	            $current = createModelElement(grammarAccess.getDependFeatureRule());
	        }
        }
	otherlv_1=RULE_ID
	{
		newLeafNode(otherlv_1, grammarAccess.getDependFeatureAccess().getModulesModuleCrossReference_1_0()); 
	}

)
)+)
;





// Entry rule entryRuleQualifiedName
entryRuleQualifiedName returns [String current=null] 
	:
	{ newCompositeNode(grammarAccess.getQualifiedNameRule()); } 
	 iv_ruleQualifiedName=ruleQualifiedName 
	 { $current=$iv_ruleQualifiedName.current.getText(); }  
	 EOF 
;

// Rule QualifiedName
ruleQualifiedName returns [AntlrDatatypeRuleToken current=new AntlrDatatypeRuleToken()] 
    @init { enterRule(); 
    }
    @after { leaveRule(); }:
(    this_ID_0=RULE_ID    {
		$current.merge(this_ID_0);
    }

    { 
    newLeafNode(this_ID_0, grammarAccess.getQualifiedNameAccess().getIDTerminalRuleCall_0()); 
    }
(
	kw='.' 
    {
        $current.merge(kw);
        newLeafNode(kw, grammarAccess.getQualifiedNameAccess().getFullStopKeyword_1_0()); 
    }
    this_ID_2=RULE_ID    {
		$current.merge(this_ID_2);
    }

    { 
    newLeafNode(this_ID_2, grammarAccess.getQualifiedNameAccess().getIDTerminalRuleCall_1_1()); 
    }
)*)
    ;





RULE_ID : '^'? ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')*;

RULE_INT : ('0'..'9')+;

RULE_STRING : ('"' ('\\' ('b'|'t'|'n'|'f'|'r'|'u'|'"'|'\''|'\\')|~(('\\'|'"')))* '"'|'\'' ('\\' ('b'|'t'|'n'|'f'|'r'|'u'|'"'|'\''|'\\')|~(('\\'|'\'')))* '\'');

RULE_ML_COMMENT : '/*' ( options {greedy=false;} : . )*'*/';

RULE_SL_COMMENT : '//' ~(('\n'|'\r'))* ('\r'? '\n')?;

RULE_WS : (' '|'\t'|'\r'|'\n')+;

RULE_ANY_OTHER : .;


