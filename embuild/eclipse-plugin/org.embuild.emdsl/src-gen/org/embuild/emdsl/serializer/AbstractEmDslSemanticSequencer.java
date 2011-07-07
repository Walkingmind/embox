package org.embuild.emdsl.serializer;

import com.google.inject.Inject;
import com.google.inject.Provider;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.xtext.serializer.acceptor.ISemanticSequenceAcceptor;
import org.eclipse.xtext.serializer.diagnostic.ISemanticSequencerDiagnosticProvider;
import org.eclipse.xtext.serializer.diagnostic.ISerializationDiagnostic.Acceptor;
import org.eclipse.xtext.serializer.sequencer.AbstractSemanticSequencer;
import org.eclipse.xtext.serializer.sequencer.GenericSequencer;
import org.eclipse.xtext.serializer.sequencer.ISemanticSequencer;
import org.eclipse.xtext.serializer.sequencer.ITransientValueService;
import org.embuild.emdsl.emDsl.DependFeature;
import org.embuild.emdsl.emDsl.EmDslPackage;
import org.embuild.emdsl.emDsl.Model;
import org.embuild.emdsl.emDsl.Modifier;
import org.embuild.emdsl.emDsl.Module;
import org.embuild.emdsl.emDsl.SourceFeature;
import org.embuild.emdsl.services.EmDslGrammarAccess;

@SuppressWarnings("restriction")
public class AbstractEmDslSemanticSequencer extends AbstractSemanticSequencer {

	@Inject
	protected EmDslGrammarAccess grammarAccess;
	
	@Inject
	protected ISemanticSequencerDiagnosticProvider diagnosticProvider;
	
	@Inject
	protected ITransientValueService transientValues;
	
	@Inject
	@GenericSequencer
	protected Provider<ISemanticSequencer> genericSequencerProvider;
	
	protected ISemanticSequencer genericSequencer;
	
	
	@Override
	public void init(ISemanticSequencer sequencer, ISemanticSequenceAcceptor sequenceAcceptor, Acceptor errorAcceptor) {
		super.init(sequencer, sequenceAcceptor, errorAcceptor);
		this.genericSequencer = genericSequencerProvider.get();
		this.genericSequencer.init(sequencer, sequenceAcceptor, errorAcceptor);
	}
	
	public void createSequence(EObject context, EObject semanticObject) {
		if(semanticObject.eClass().getEPackage() == EmDslPackage.eINSTANCE) switch(semanticObject.eClass().getClassifierID()) {
			case EmDslPackage.DEPEND_FEATURE:
				if(context == grammarAccess.getFeatureRule() ||
				   context == grammarAccess.getDependFeatureRule()) {
					sequence_DependFeature_DependFeature(context, (DependFeature) semanticObject); 
					return; 
				}
				else break;
			case EmDslPackage.MODEL:
				if(context == grammarAccess.getModelRule()) {
					sequence_Model_Model(context, (Model) semanticObject); 
					return; 
				}
				else break;
			case EmDslPackage.MODIFIER:
				if(context == grammarAccess.getModifierRule()) {
					sequence_Modifier_Modifier(context, (Modifier) semanticObject); 
					return; 
				}
				else if(context == grammarAccess.getEntityRule() ||
				   context == grammarAccess.getModuleRule()) {
					sequence_Module_Modifier(context, (Modifier) semanticObject); 
					return; 
				}
				else break;
			case EmDslPackage.MODULE:
				if(context == grammarAccess.getEntityRule() ||
				   context == grammarAccess.getModuleRule()) {
					sequence_Module_Module(context, (Module) semanticObject); 
					return; 
				}
				else break;
			case EmDslPackage.SOURCE_FEATURE:
				if(context == grammarAccess.getFeatureRule() ||
				   context == grammarAccess.getSourceFeatureRule()) {
					sequence_SourceFeature_SourceFeature(context, (SourceFeature) semanticObject); 
					return; 
				}
				else break;
			}
		if (errorAcceptor != null) errorAcceptor.accept(diagnosticProvider.createInvalidContextOrTypeDiagnostic(semanticObject, context));
	}
	
	/**
	 * Constraint:
	 *     modules+=[Module|ID]+
	 *
	 * Features:
	 *    modules[1, *]
	 */
	protected void sequence_DependFeature_DependFeature(EObject context, DependFeature semanticObject) {
		genericSequencer.createSequence(context, semanticObject);
	}
	
	
	/**
	 * Constraint:
	 *     elements+=Entity*
	 *
	 * Features:
	 *    elements[0, *]
	 */
	protected void sequence_Model_Model(EObject context, Model semanticObject) {
		genericSequencer.createSequence(context, semanticObject);
	}
	
	
	/**
	 * Constraint:
	 *     abstract?='abstract'
	 *
	 * Features:
	 *    abstract[1, 1]
	 */
	protected void sequence_Modifier_Modifier(EObject context, Modifier semanticObject) {
		genericSequencer.createSequence(context, semanticObject);
	}
	
	
	/**
	 * Constraint:
	 *     (abstract?='abstract' name=ID superType=[Module|QualifiedName]? features+=Feature*)
	 *
	 * Features:
	 *    name[1, 1]
	 *    superType[0, 1]
	 *    features[0, *]
	 *    abstract[1, 1]
	 */
	protected void sequence_Module_Modifier(EObject context, Modifier semanticObject) {
		genericSequencer.createSequence(context, semanticObject);
	}
	
	
	/**
	 * Constraint:
	 *     (name=ID superType=[Module|QualifiedName]? features+=Feature*)
	 *
	 * Features:
	 *    name[1, 1]
	 *    superType[0, 1]
	 *    features[0, *]
	 */
	protected void sequence_Module_Module(EObject context, Module semanticObject) {
		genericSequencer.createSequence(context, semanticObject);
	}
	
	
	/**
	 * Constraint:
	 *     filenames+=Filename+
	 *
	 * Features:
	 *    filenames[1, *]
	 */
	protected void sequence_SourceFeature_SourceFeature(EObject context, SourceFeature semanticObject) {
		genericSequencer.createSequence(context, semanticObject);
	}
}
