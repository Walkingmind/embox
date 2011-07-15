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



import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings("all")
public class InternalEmDslParser extends AbstractInternalAntlrParser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "RULE_ID", "RULE_STRING", "RULE_INT", "RULE_ML_COMMENT", "RULE_SL_COMMENT", "RULE_WS", "RULE_ANY_OTHER", "'abstract'", "'module'", "'extends'", "'{'", "'}'", "'source'", "'depend'", "'.'"
    };
    public static final int RULE_ID=4;
    public static final int RULE_STRING=5;
    public static final int T__16=16;
    public static final int T__15=15;
    public static final int T__18=18;
    public static final int T__17=17;
    public static final int T__12=12;
    public static final int T__11=11;
    public static final int T__14=14;
    public static final int T__13=13;
    public static final int RULE_ANY_OTHER=10;
    public static final int RULE_INT=6;
    public static final int RULE_WS=9;
    public static final int RULE_SL_COMMENT=8;
    public static final int EOF=-1;
    public static final int RULE_ML_COMMENT=7;

    // delegates
    // delegators


        public InternalEmDslParser(TokenStream input) {
            this(input, new RecognizerSharedState());
        }
        public InternalEmDslParser(TokenStream input, RecognizerSharedState state) {
            super(input, state);
             
        }
        

    public String[] getTokenNames() { return InternalEmDslParser.tokenNames; }
    public String getGrammarFileName() { return "../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g"; }



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



    // $ANTLR start "entryRuleModel"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:67:1: entryRuleModel returns [EObject current=null] : iv_ruleModel= ruleModel EOF ;
    public final EObject entryRuleModel() throws RecognitionException {
        EObject current = null;

        EObject iv_ruleModel = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:68:2: (iv_ruleModel= ruleModel EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:69:2: iv_ruleModel= ruleModel EOF
            {
             newCompositeNode(grammarAccess.getModelRule()); 
            pushFollow(FOLLOW_ruleModel_in_entryRuleModel75);
            iv_ruleModel=ruleModel();

            state._fsp--;

             current =iv_ruleModel; 
            match(input,EOF,FOLLOW_EOF_in_entryRuleModel85); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleModel"


    // $ANTLR start "ruleModel"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:76:1: ruleModel returns [EObject current=null] : ( (lv_elements_0_0= ruleEntity ) )* ;
    public final EObject ruleModel() throws RecognitionException {
        EObject current = null;

        EObject lv_elements_0_0 = null;


         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:79:28: ( ( (lv_elements_0_0= ruleEntity ) )* )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:80:1: ( (lv_elements_0_0= ruleEntity ) )*
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:80:1: ( (lv_elements_0_0= ruleEntity ) )*
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( ((LA1_0>=11 && LA1_0<=12)) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:81:1: (lv_elements_0_0= ruleEntity )
            	    {
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:81:1: (lv_elements_0_0= ruleEntity )
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:82:3: lv_elements_0_0= ruleEntity
            	    {
            	     
            	    	        newCompositeNode(grammarAccess.getModelAccess().getElementsEntityParserRuleCall_0()); 
            	    	    
            	    pushFollow(FOLLOW_ruleEntity_in_ruleModel130);
            	    lv_elements_0_0=ruleEntity();

            	    state._fsp--;


            	    	        if (current==null) {
            	    	            current = createModelElementForParent(grammarAccess.getModelRule());
            	    	        }
            	           		add(
            	           			current, 
            	           			"elements",
            	            		lv_elements_0_0, 
            	            		"Entity");
            	    	        afterParserOrEnumRuleCall();
            	    	    

            	    }


            	    }
            	    break;

            	default :
            	    break loop1;
                }
            } while (true);


            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleModel"


    // $ANTLR start "entryRuleEntity"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:106:1: entryRuleEntity returns [EObject current=null] : iv_ruleEntity= ruleEntity EOF ;
    public final EObject entryRuleEntity() throws RecognitionException {
        EObject current = null;

        EObject iv_ruleEntity = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:107:2: (iv_ruleEntity= ruleEntity EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:108:2: iv_ruleEntity= ruleEntity EOF
            {
             newCompositeNode(grammarAccess.getEntityRule()); 
            pushFollow(FOLLOW_ruleEntity_in_entryRuleEntity166);
            iv_ruleEntity=ruleEntity();

            state._fsp--;

             current =iv_ruleEntity; 
            match(input,EOF,FOLLOW_EOF_in_entryRuleEntity176); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleEntity"


    // $ANTLR start "ruleEntity"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:115:1: ruleEntity returns [EObject current=null] : this_Module_0= ruleModule ;
    public final EObject ruleEntity() throws RecognitionException {
        EObject current = null;

        EObject this_Module_0 = null;


         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:118:28: (this_Module_0= ruleModule )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:120:5: this_Module_0= ruleModule
            {
             
                    newCompositeNode(grammarAccess.getEntityAccess().getModuleParserRuleCall()); 
                
            pushFollow(FOLLOW_ruleModule_in_ruleEntity222);
            this_Module_0=ruleModule();

            state._fsp--;

             
                    current = this_Module_0; 
                    afterParserOrEnumRuleCall();
                

            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleEntity"


    // $ANTLR start "entryRuleModifier"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:136:1: entryRuleModifier returns [EObject current=null] : iv_ruleModifier= ruleModifier EOF ;
    public final EObject entryRuleModifier() throws RecognitionException {
        EObject current = null;

        EObject iv_ruleModifier = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:137:2: (iv_ruleModifier= ruleModifier EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:138:2: iv_ruleModifier= ruleModifier EOF
            {
             newCompositeNode(grammarAccess.getModifierRule()); 
            pushFollow(FOLLOW_ruleModifier_in_entryRuleModifier256);
            iv_ruleModifier=ruleModifier();

            state._fsp--;

             current =iv_ruleModifier; 
            match(input,EOF,FOLLOW_EOF_in_entryRuleModifier266); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleModifier"


    // $ANTLR start "ruleModifier"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:145:1: ruleModifier returns [EObject current=null] : ( (lv_abstract_0_0= 'abstract' ) ) ;
    public final EObject ruleModifier() throws RecognitionException {
        EObject current = null;

        Token lv_abstract_0_0=null;

         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:148:28: ( ( (lv_abstract_0_0= 'abstract' ) ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:149:1: ( (lv_abstract_0_0= 'abstract' ) )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:149:1: ( (lv_abstract_0_0= 'abstract' ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:150:1: (lv_abstract_0_0= 'abstract' )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:150:1: (lv_abstract_0_0= 'abstract' )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:151:3: lv_abstract_0_0= 'abstract'
            {
            lv_abstract_0_0=(Token)match(input,11,FOLLOW_11_in_ruleModifier308); 

                    newLeafNode(lv_abstract_0_0, grammarAccess.getModifierAccess().getAbstractAbstractKeyword_0());
                

            	        if (current==null) {
            	            current = createModelElement(grammarAccess.getModifierRule());
            	        }
                   		setWithLastConsumed(current, "abstract", true, "abstract");
            	    

            }


            }


            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleModifier"


    // $ANTLR start "entryRuleModule"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:172:1: entryRuleModule returns [EObject current=null] : iv_ruleModule= ruleModule EOF ;
    public final EObject entryRuleModule() throws RecognitionException {
        EObject current = null;

        EObject iv_ruleModule = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:173:2: (iv_ruleModule= ruleModule EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:174:2: iv_ruleModule= ruleModule EOF
            {
             newCompositeNode(grammarAccess.getModuleRule()); 
            pushFollow(FOLLOW_ruleModule_in_entryRuleModule356);
            iv_ruleModule=ruleModule();

            state._fsp--;

             current =iv_ruleModule; 
            match(input,EOF,FOLLOW_EOF_in_entryRuleModule366); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleModule"


    // $ANTLR start "ruleModule"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:181:1: ruleModule returns [EObject current=null] : ( (this_Modifier_0= ruleModifier )? otherlv_1= 'module' ( (lv_name_2_0= RULE_ID ) ) (otherlv_3= 'extends' ( ( ruleQualifiedName ) ) )? otherlv_5= '{' ( (lv_features_6_0= ruleFeature ) )* otherlv_7= '}' ) ;
    public final EObject ruleModule() throws RecognitionException {
        EObject current = null;

        Token otherlv_1=null;
        Token lv_name_2_0=null;
        Token otherlv_3=null;
        Token otherlv_5=null;
        Token otherlv_7=null;
        EObject this_Modifier_0 = null;

        EObject lv_features_6_0 = null;


         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:184:28: ( ( (this_Modifier_0= ruleModifier )? otherlv_1= 'module' ( (lv_name_2_0= RULE_ID ) ) (otherlv_3= 'extends' ( ( ruleQualifiedName ) ) )? otherlv_5= '{' ( (lv_features_6_0= ruleFeature ) )* otherlv_7= '}' ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:185:1: ( (this_Modifier_0= ruleModifier )? otherlv_1= 'module' ( (lv_name_2_0= RULE_ID ) ) (otherlv_3= 'extends' ( ( ruleQualifiedName ) ) )? otherlv_5= '{' ( (lv_features_6_0= ruleFeature ) )* otherlv_7= '}' )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:185:1: ( (this_Modifier_0= ruleModifier )? otherlv_1= 'module' ( (lv_name_2_0= RULE_ID ) ) (otherlv_3= 'extends' ( ( ruleQualifiedName ) ) )? otherlv_5= '{' ( (lv_features_6_0= ruleFeature ) )* otherlv_7= '}' )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:185:2: (this_Modifier_0= ruleModifier )? otherlv_1= 'module' ( (lv_name_2_0= RULE_ID ) ) (otherlv_3= 'extends' ( ( ruleQualifiedName ) ) )? otherlv_5= '{' ( (lv_features_6_0= ruleFeature ) )* otherlv_7= '}'
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:185:2: (this_Modifier_0= ruleModifier )?
            int alt2=2;
            int LA2_0 = input.LA(1);

            if ( (LA2_0==11) ) {
                alt2=1;
            }
            switch (alt2) {
                case 1 :
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:186:5: this_Modifier_0= ruleModifier
                    {
                     
                            newCompositeNode(grammarAccess.getModuleAccess().getModifierParserRuleCall_0()); 
                        
                    pushFollow(FOLLOW_ruleModifier_in_ruleModule414);
                    this_Modifier_0=ruleModifier();

                    state._fsp--;

                     
                            current = this_Modifier_0; 
                            afterParserOrEnumRuleCall();
                        

                    }
                    break;

            }

            otherlv_1=(Token)match(input,12,FOLLOW_12_in_ruleModule427); 

                	newLeafNode(otherlv_1, grammarAccess.getModuleAccess().getModuleKeyword_1());
                
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:198:1: ( (lv_name_2_0= RULE_ID ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:199:1: (lv_name_2_0= RULE_ID )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:199:1: (lv_name_2_0= RULE_ID )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:200:3: lv_name_2_0= RULE_ID
            {
            lv_name_2_0=(Token)match(input,RULE_ID,FOLLOW_RULE_ID_in_ruleModule444); 

            			newLeafNode(lv_name_2_0, grammarAccess.getModuleAccess().getNameIDTerminalRuleCall_2_0()); 
            		

            	        if (current==null) {
            	            current = createModelElement(grammarAccess.getModuleRule());
            	        }
                   		setWithLastConsumed(
                   			current, 
                   			"name",
                    		lv_name_2_0, 
                    		"ID");
            	    

            }


            }

            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:216:2: (otherlv_3= 'extends' ( ( ruleQualifiedName ) ) )?
            int alt3=2;
            int LA3_0 = input.LA(1);

            if ( (LA3_0==13) ) {
                alt3=1;
            }
            switch (alt3) {
                case 1 :
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:216:4: otherlv_3= 'extends' ( ( ruleQualifiedName ) )
                    {
                    otherlv_3=(Token)match(input,13,FOLLOW_13_in_ruleModule462); 

                        	newLeafNode(otherlv_3, grammarAccess.getModuleAccess().getExtendsKeyword_3_0());
                        
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:220:1: ( ( ruleQualifiedName ) )
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:221:1: ( ruleQualifiedName )
                    {
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:221:1: ( ruleQualifiedName )
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:222:3: ruleQualifiedName
                    {

                    			if (current==null) {
                    	            current = createModelElement(grammarAccess.getModuleRule());
                    	        }
                            
                     
                    	        newCompositeNode(grammarAccess.getModuleAccess().getSuperTypeModuleCrossReference_3_1_0()); 
                    	    
                    pushFollow(FOLLOW_ruleQualifiedName_in_ruleModule485);
                    ruleQualifiedName();

                    state._fsp--;

                     
                    	        afterParserOrEnumRuleCall();
                    	    

                    }


                    }


                    }
                    break;

            }

            otherlv_5=(Token)match(input,14,FOLLOW_14_in_ruleModule499); 

                	newLeafNode(otherlv_5, grammarAccess.getModuleAccess().getLeftCurlyBracketKeyword_4());
                
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:239:1: ( (lv_features_6_0= ruleFeature ) )*
            loop4:
            do {
                int alt4=2;
                int LA4_0 = input.LA(1);

                if ( ((LA4_0>=16 && LA4_0<=17)) ) {
                    alt4=1;
                }


                switch (alt4) {
            	case 1 :
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:240:1: (lv_features_6_0= ruleFeature )
            	    {
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:240:1: (lv_features_6_0= ruleFeature )
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:241:3: lv_features_6_0= ruleFeature
            	    {
            	     
            	    	        newCompositeNode(grammarAccess.getModuleAccess().getFeaturesFeatureParserRuleCall_5_0()); 
            	    	    
            	    pushFollow(FOLLOW_ruleFeature_in_ruleModule520);
            	    lv_features_6_0=ruleFeature();

            	    state._fsp--;


            	    	        if (current==null) {
            	    	            current = createModelElementForParent(grammarAccess.getModuleRule());
            	    	        }
            	           		add(
            	           			current, 
            	           			"features",
            	            		lv_features_6_0, 
            	            		"Feature");
            	    	        afterParserOrEnumRuleCall();
            	    	    

            	    }


            	    }
            	    break;

            	default :
            	    break loop4;
                }
            } while (true);

            otherlv_7=(Token)match(input,15,FOLLOW_15_in_ruleModule533); 

                	newLeafNode(otherlv_7, grammarAccess.getModuleAccess().getRightCurlyBracketKeyword_6());
                

            }


            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleModule"


    // $ANTLR start "entryRuleFeature"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:269:1: entryRuleFeature returns [EObject current=null] : iv_ruleFeature= ruleFeature EOF ;
    public final EObject entryRuleFeature() throws RecognitionException {
        EObject current = null;

        EObject iv_ruleFeature = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:270:2: (iv_ruleFeature= ruleFeature EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:271:2: iv_ruleFeature= ruleFeature EOF
            {
             newCompositeNode(grammarAccess.getFeatureRule()); 
            pushFollow(FOLLOW_ruleFeature_in_entryRuleFeature569);
            iv_ruleFeature=ruleFeature();

            state._fsp--;

             current =iv_ruleFeature; 
            match(input,EOF,FOLLOW_EOF_in_entryRuleFeature579); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleFeature"


    // $ANTLR start "ruleFeature"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:278:1: ruleFeature returns [EObject current=null] : (this_SourceFeature_0= ruleSourceFeature | this_DependFeature_1= ruleDependFeature ) ;
    public final EObject ruleFeature() throws RecognitionException {
        EObject current = null;

        EObject this_SourceFeature_0 = null;

        EObject this_DependFeature_1 = null;


         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:281:28: ( (this_SourceFeature_0= ruleSourceFeature | this_DependFeature_1= ruleDependFeature ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:282:1: (this_SourceFeature_0= ruleSourceFeature | this_DependFeature_1= ruleDependFeature )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:282:1: (this_SourceFeature_0= ruleSourceFeature | this_DependFeature_1= ruleDependFeature )
            int alt5=2;
            int LA5_0 = input.LA(1);

            if ( (LA5_0==16) ) {
                alt5=1;
            }
            else if ( (LA5_0==17) ) {
                alt5=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 5, 0, input);

                throw nvae;
            }
            switch (alt5) {
                case 1 :
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:283:5: this_SourceFeature_0= ruleSourceFeature
                    {
                     
                            newCompositeNode(grammarAccess.getFeatureAccess().getSourceFeatureParserRuleCall_0()); 
                        
                    pushFollow(FOLLOW_ruleSourceFeature_in_ruleFeature626);
                    this_SourceFeature_0=ruleSourceFeature();

                    state._fsp--;

                     
                            current = this_SourceFeature_0; 
                            afterParserOrEnumRuleCall();
                        

                    }
                    break;
                case 2 :
                    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:293:5: this_DependFeature_1= ruleDependFeature
                    {
                     
                            newCompositeNode(grammarAccess.getFeatureAccess().getDependFeatureParserRuleCall_1()); 
                        
                    pushFollow(FOLLOW_ruleDependFeature_in_ruleFeature653);
                    this_DependFeature_1=ruleDependFeature();

                    state._fsp--;

                     
                            current = this_DependFeature_1; 
                            afterParserOrEnumRuleCall();
                        

                    }
                    break;

            }


            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleFeature"


    // $ANTLR start "entryRuleSourceFeature"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:309:1: entryRuleSourceFeature returns [EObject current=null] : iv_ruleSourceFeature= ruleSourceFeature EOF ;
    public final EObject entryRuleSourceFeature() throws RecognitionException {
        EObject current = null;

        EObject iv_ruleSourceFeature = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:310:2: (iv_ruleSourceFeature= ruleSourceFeature EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:311:2: iv_ruleSourceFeature= ruleSourceFeature EOF
            {
             newCompositeNode(grammarAccess.getSourceFeatureRule()); 
            pushFollow(FOLLOW_ruleSourceFeature_in_entryRuleSourceFeature688);
            iv_ruleSourceFeature=ruleSourceFeature();

            state._fsp--;

             current =iv_ruleSourceFeature; 
            match(input,EOF,FOLLOW_EOF_in_entryRuleSourceFeature698); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleSourceFeature"


    // $ANTLR start "ruleSourceFeature"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:318:1: ruleSourceFeature returns [EObject current=null] : (otherlv_0= 'source' ( (lv_filenames_1_0= ruleFilename ) )+ ) ;
    public final EObject ruleSourceFeature() throws RecognitionException {
        EObject current = null;

        Token otherlv_0=null;
        AntlrDatatypeRuleToken lv_filenames_1_0 = null;


         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:321:28: ( (otherlv_0= 'source' ( (lv_filenames_1_0= ruleFilename ) )+ ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:322:1: (otherlv_0= 'source' ( (lv_filenames_1_0= ruleFilename ) )+ )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:322:1: (otherlv_0= 'source' ( (lv_filenames_1_0= ruleFilename ) )+ )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:322:3: otherlv_0= 'source' ( (lv_filenames_1_0= ruleFilename ) )+
            {
            otherlv_0=(Token)match(input,16,FOLLOW_16_in_ruleSourceFeature735); 

                	newLeafNode(otherlv_0, grammarAccess.getSourceFeatureAccess().getSourceKeyword_0());
                
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:326:1: ( (lv_filenames_1_0= ruleFilename ) )+
            int cnt6=0;
            loop6:
            do {
                int alt6=2;
                int LA6_0 = input.LA(1);

                if ( (LA6_0==RULE_STRING) ) {
                    alt6=1;
                }


                switch (alt6) {
            	case 1 :
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:327:1: (lv_filenames_1_0= ruleFilename )
            	    {
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:327:1: (lv_filenames_1_0= ruleFilename )
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:328:3: lv_filenames_1_0= ruleFilename
            	    {
            	     
            	    	        newCompositeNode(grammarAccess.getSourceFeatureAccess().getFilenamesFilenameParserRuleCall_1_0()); 
            	    	    
            	    pushFollow(FOLLOW_ruleFilename_in_ruleSourceFeature756);
            	    lv_filenames_1_0=ruleFilename();

            	    state._fsp--;


            	    	        if (current==null) {
            	    	            current = createModelElementForParent(grammarAccess.getSourceFeatureRule());
            	    	        }
            	           		add(
            	           			current, 
            	           			"filenames",
            	            		lv_filenames_1_0, 
            	            		"Filename");
            	    	        afterParserOrEnumRuleCall();
            	    	    

            	    }


            	    }
            	    break;

            	default :
            	    if ( cnt6 >= 1 ) break loop6;
                        EarlyExitException eee =
                            new EarlyExitException(6, input);
                        throw eee;
                }
                cnt6++;
            } while (true);


            }


            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleSourceFeature"


    // $ANTLR start "entryRuleFilename"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:352:1: entryRuleFilename returns [String current=null] : iv_ruleFilename= ruleFilename EOF ;
    public final String entryRuleFilename() throws RecognitionException {
        String current = null;

        AntlrDatatypeRuleToken iv_ruleFilename = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:353:2: (iv_ruleFilename= ruleFilename EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:354:2: iv_ruleFilename= ruleFilename EOF
            {
             newCompositeNode(grammarAccess.getFilenameRule()); 
            pushFollow(FOLLOW_ruleFilename_in_entryRuleFilename794);
            iv_ruleFilename=ruleFilename();

            state._fsp--;

             current =iv_ruleFilename.getText(); 
            match(input,EOF,FOLLOW_EOF_in_entryRuleFilename805); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleFilename"


    // $ANTLR start "ruleFilename"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:361:1: ruleFilename returns [AntlrDatatypeRuleToken current=new AntlrDatatypeRuleToken()] : this_STRING_0= RULE_STRING ;
    public final AntlrDatatypeRuleToken ruleFilename() throws RecognitionException {
        AntlrDatatypeRuleToken current = new AntlrDatatypeRuleToken();

        Token this_STRING_0=null;

         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:364:28: (this_STRING_0= RULE_STRING )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:365:5: this_STRING_0= RULE_STRING
            {
            this_STRING_0=(Token)match(input,RULE_STRING,FOLLOW_RULE_STRING_in_ruleFilename844); 

            		current.merge(this_STRING_0);
                
             
                newLeafNode(this_STRING_0, grammarAccess.getFilenameAccess().getSTRINGTerminalRuleCall()); 
                

            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleFilename"


    // $ANTLR start "entryRuleDependFeature"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:380:1: entryRuleDependFeature returns [EObject current=null] : iv_ruleDependFeature= ruleDependFeature EOF ;
    public final EObject entryRuleDependFeature() throws RecognitionException {
        EObject current = null;

        EObject iv_ruleDependFeature = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:381:2: (iv_ruleDependFeature= ruleDependFeature EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:382:2: iv_ruleDependFeature= ruleDependFeature EOF
            {
             newCompositeNode(grammarAccess.getDependFeatureRule()); 
            pushFollow(FOLLOW_ruleDependFeature_in_entryRuleDependFeature888);
            iv_ruleDependFeature=ruleDependFeature();

            state._fsp--;

             current =iv_ruleDependFeature; 
            match(input,EOF,FOLLOW_EOF_in_entryRuleDependFeature898); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleDependFeature"


    // $ANTLR start "ruleDependFeature"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:389:1: ruleDependFeature returns [EObject current=null] : (otherlv_0= 'depend' ( (otherlv_1= RULE_ID ) )+ ) ;
    public final EObject ruleDependFeature() throws RecognitionException {
        EObject current = null;

        Token otherlv_0=null;
        Token otherlv_1=null;

         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:392:28: ( (otherlv_0= 'depend' ( (otherlv_1= RULE_ID ) )+ ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:393:1: (otherlv_0= 'depend' ( (otherlv_1= RULE_ID ) )+ )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:393:1: (otherlv_0= 'depend' ( (otherlv_1= RULE_ID ) )+ )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:393:3: otherlv_0= 'depend' ( (otherlv_1= RULE_ID ) )+
            {
            otherlv_0=(Token)match(input,17,FOLLOW_17_in_ruleDependFeature935); 

                	newLeafNode(otherlv_0, grammarAccess.getDependFeatureAccess().getDependKeyword_0());
                
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:397:1: ( (otherlv_1= RULE_ID ) )+
            int cnt7=0;
            loop7:
            do {
                int alt7=2;
                int LA7_0 = input.LA(1);

                if ( (LA7_0==RULE_ID) ) {
                    alt7=1;
                }


                switch (alt7) {
            	case 1 :
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:398:1: (otherlv_1= RULE_ID )
            	    {
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:398:1: (otherlv_1= RULE_ID )
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:399:3: otherlv_1= RULE_ID
            	    {

            	    			if (current==null) {
            	    	            current = createModelElement(grammarAccess.getDependFeatureRule());
            	    	        }
            	            
            	    otherlv_1=(Token)match(input,RULE_ID,FOLLOW_RULE_ID_in_ruleDependFeature955); 

            	    		newLeafNode(otherlv_1, grammarAccess.getDependFeatureAccess().getModulesModuleCrossReference_1_0()); 
            	    	

            	    }


            	    }
            	    break;

            	default :
            	    if ( cnt7 >= 1 ) break loop7;
                        EarlyExitException eee =
                            new EarlyExitException(7, input);
                        throw eee;
                }
                cnt7++;
            } while (true);


            }


            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleDependFeature"


    // $ANTLR start "entryRuleQualifiedName"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:418:1: entryRuleQualifiedName returns [String current=null] : iv_ruleQualifiedName= ruleQualifiedName EOF ;
    public final String entryRuleQualifiedName() throws RecognitionException {
        String current = null;

        AntlrDatatypeRuleToken iv_ruleQualifiedName = null;


        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:419:2: (iv_ruleQualifiedName= ruleQualifiedName EOF )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:420:2: iv_ruleQualifiedName= ruleQualifiedName EOF
            {
             newCompositeNode(grammarAccess.getQualifiedNameRule()); 
            pushFollow(FOLLOW_ruleQualifiedName_in_entryRuleQualifiedName993);
            iv_ruleQualifiedName=ruleQualifiedName();

            state._fsp--;

             current =iv_ruleQualifiedName.getText(); 
            match(input,EOF,FOLLOW_EOF_in_entryRuleQualifiedName1004); 

            }

        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "entryRuleQualifiedName"


    // $ANTLR start "ruleQualifiedName"
    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:427:1: ruleQualifiedName returns [AntlrDatatypeRuleToken current=new AntlrDatatypeRuleToken()] : (this_ID_0= RULE_ID (kw= '.' this_ID_2= RULE_ID )* ) ;
    public final AntlrDatatypeRuleToken ruleQualifiedName() throws RecognitionException {
        AntlrDatatypeRuleToken current = new AntlrDatatypeRuleToken();

        Token this_ID_0=null;
        Token kw=null;
        Token this_ID_2=null;

         enterRule(); 
            
        try {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:430:28: ( (this_ID_0= RULE_ID (kw= '.' this_ID_2= RULE_ID )* ) )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:431:1: (this_ID_0= RULE_ID (kw= '.' this_ID_2= RULE_ID )* )
            {
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:431:1: (this_ID_0= RULE_ID (kw= '.' this_ID_2= RULE_ID )* )
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:431:6: this_ID_0= RULE_ID (kw= '.' this_ID_2= RULE_ID )*
            {
            this_ID_0=(Token)match(input,RULE_ID,FOLLOW_RULE_ID_in_ruleQualifiedName1044); 

            		current.merge(this_ID_0);
                
             
                newLeafNode(this_ID_0, grammarAccess.getQualifiedNameAccess().getIDTerminalRuleCall_0()); 
                
            // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:438:1: (kw= '.' this_ID_2= RULE_ID )*
            loop8:
            do {
                int alt8=2;
                int LA8_0 = input.LA(1);

                if ( (LA8_0==18) ) {
                    alt8=1;
                }


                switch (alt8) {
            	case 1 :
            	    // ../org.embuild.emdsl/src-gen/org/embuild/emdsl/parser/antlr/internal/InternalEmDsl.g:439:2: kw= '.' this_ID_2= RULE_ID
            	    {
            	    kw=(Token)match(input,18,FOLLOW_18_in_ruleQualifiedName1063); 

            	            current.merge(kw);
            	            newLeafNode(kw, grammarAccess.getQualifiedNameAccess().getFullStopKeyword_1_0()); 
            	        
            	    this_ID_2=(Token)match(input,RULE_ID,FOLLOW_RULE_ID_in_ruleQualifiedName1078); 

            	    		current.merge(this_ID_2);
            	        
            	     
            	        newLeafNode(this_ID_2, grammarAccess.getQualifiedNameAccess().getIDTerminalRuleCall_1_1()); 
            	        

            	    }
            	    break;

            	default :
            	    break loop8;
                }
            } while (true);


            }


            }

             leaveRule(); 
        }
         
            catch (RecognitionException re) { 
                recover(input,re); 
                appendSkippedTokens();
            } 
        finally {
        }
        return current;
    }
    // $ANTLR end "ruleQualifiedName"

    // Delegated rules


 

    public static final BitSet FOLLOW_ruleModel_in_entryRuleModel75 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleModel85 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleEntity_in_ruleModel130 = new BitSet(new long[]{0x0000000000001802L});
    public static final BitSet FOLLOW_ruleEntity_in_entryRuleEntity166 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleEntity176 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleModule_in_ruleEntity222 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleModifier_in_entryRuleModifier256 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleModifier266 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_11_in_ruleModifier308 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleModule_in_entryRuleModule356 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleModule366 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleModifier_in_ruleModule414 = new BitSet(new long[]{0x0000000000001000L});
    public static final BitSet FOLLOW_12_in_ruleModule427 = new BitSet(new long[]{0x0000000000000010L});
    public static final BitSet FOLLOW_RULE_ID_in_ruleModule444 = new BitSet(new long[]{0x0000000000006000L});
    public static final BitSet FOLLOW_13_in_ruleModule462 = new BitSet(new long[]{0x0000000000000010L});
    public static final BitSet FOLLOW_ruleQualifiedName_in_ruleModule485 = new BitSet(new long[]{0x0000000000004000L});
    public static final BitSet FOLLOW_14_in_ruleModule499 = new BitSet(new long[]{0x0000000000038000L});
    public static final BitSet FOLLOW_ruleFeature_in_ruleModule520 = new BitSet(new long[]{0x0000000000038000L});
    public static final BitSet FOLLOW_15_in_ruleModule533 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleFeature_in_entryRuleFeature569 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleFeature579 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleSourceFeature_in_ruleFeature626 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleDependFeature_in_ruleFeature653 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleSourceFeature_in_entryRuleSourceFeature688 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleSourceFeature698 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_16_in_ruleSourceFeature735 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_ruleFilename_in_ruleSourceFeature756 = new BitSet(new long[]{0x0000000000000022L});
    public static final BitSet FOLLOW_ruleFilename_in_entryRuleFilename794 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleFilename805 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_RULE_STRING_in_ruleFilename844 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ruleDependFeature_in_entryRuleDependFeature888 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleDependFeature898 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_17_in_ruleDependFeature935 = new BitSet(new long[]{0x0000000000000010L});
    public static final BitSet FOLLOW_RULE_ID_in_ruleDependFeature955 = new BitSet(new long[]{0x0000000000000012L});
    public static final BitSet FOLLOW_ruleQualifiedName_in_entryRuleQualifiedName993 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_entryRuleQualifiedName1004 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_RULE_ID_in_ruleQualifiedName1044 = new BitSet(new long[]{0x0000000000040002L});
    public static final BitSet FOLLOW_18_in_ruleQualifiedName1063 = new BitSet(new long[]{0x0000000000000010L});
    public static final BitSet FOLLOW_RULE_ID_in_ruleQualifiedName1078 = new BitSet(new long[]{0x0000000000040002L});

}