/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile.util;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.util.Switch;

import org.mybuild.myfile.AbstractFeatureListMember;
import org.mybuild.myfile.AbstractFileListMember;
import org.mybuild.myfile.Annotation;
import org.mybuild.myfile.AnnotationTarget;
import org.mybuild.myfile.AnnotationType;
import org.mybuild.myfile.BooleanLiteral;
import org.mybuild.myfile.BooleanProperty;
import org.mybuild.myfile.DependsMember;
import org.mybuild.myfile.Feature;
import org.mybuild.myfile.FileName;
import org.mybuild.myfile.Import;
import org.mybuild.myfile.Interface;
import org.mybuild.myfile.Member;
import org.mybuild.myfile.Model;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.MyFilePackage;
import org.mybuild.myfile.Named;
import org.mybuild.myfile.NumberLiteral;
import org.mybuild.myfile.NumberProperty;
import org.mybuild.myfile.ObjectMember;
import org.mybuild.myfile.OptionMember;
import org.mybuild.myfile.Property;
import org.mybuild.myfile.PropertyValueBinding;
import org.mybuild.myfile.ProvidesMember;
import org.mybuild.myfile.RequiresMember;
import org.mybuild.myfile.SourceMember;
import org.mybuild.myfile.StringLiteral;
import org.mybuild.myfile.StringProperty;
import org.mybuild.myfile.Type;
import org.mybuild.myfile.TypeLiteral;
import org.mybuild.myfile.TypeProperty;
import org.mybuild.myfile.Value;

/**
 * <!-- begin-user-doc -->
 * The <b>Switch</b> for the model's inheritance hierarchy.
 * It supports the call {@link #doSwitch(EObject) doSwitch(object)}
 * to invoke the <code>caseXXX</code> method for each class of the model,
 * starting with the actual class of the object
 * and proceeding up the inheritance hierarchy
 * until a non-null result is returned,
 * which is the result of the switch.
 * <!-- end-user-doc -->
 * @see org.mybuild.myfile.MyFilePackage
 * @generated
 */
public class MyFileSwitch<T> extends Switch<T>
{
	/**
	 * The cached model package
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected static MyFilePackage modelPackage;

	/**
	 * Creates an instance of the switch.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public MyFileSwitch()
	{
		if (modelPackage == null) {
			modelPackage = MyFilePackage.eINSTANCE;
		}
	}

	/**
	 * Checks whether this is a switch for the given package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @parameter ePackage the package in question.
	 * @return whether this is a switch for the given package.
	 * @generated
	 */
	@Override
	protected boolean isSwitchFor(EPackage ePackage)
	{
		return ePackage == modelPackage;
	}

	/**
	 * Calls <code>caseXXX</code> for each class of the model until one returns a non null result; it yields that result.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the first non-null result returned by a <code>caseXXX</code> call.
	 * @generated
	 */
	@Override
	protected T doSwitch(int classifierID, EObject theEObject)
	{
		switch (classifierID) {
			case MyFilePackage.MODEL: {
				Model model = (Model)theEObject;
				T result = caseModel(model);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.PACKAGE: {
				org.mybuild.myfile.Package package_ = (org.mybuild.myfile.Package)theEObject;
				T result = casePackage(package_);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.IMPORT: {
				Import import_ = (Import)theEObject;
				T result = caseImport(import_);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.TYPE: {
				Type type = (Type)theEObject;
				T result = caseType(type);
				if (result == null) result = caseNamed(type);
				if (result == null) result = caseAnnotationTarget(type);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.ANNOTATION_TYPE: {
				AnnotationType annotationType = (AnnotationType)theEObject;
				T result = caseAnnotationType(annotationType);
				if (result == null) result = caseType(annotationType);
				if (result == null) result = caseNamed(annotationType);
				if (result == null) result = caseAnnotationTarget(annotationType);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.ANNOTATION: {
				Annotation annotation = (Annotation)theEObject;
				T result = caseAnnotation(annotation);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.ANNOTATION_TARGET: {
				AnnotationTarget annotationTarget = (AnnotationTarget)theEObject;
				T result = caseAnnotationTarget(annotationTarget);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.INTERFACE: {
				Interface interface_ = (Interface)theEObject;
				T result = caseInterface(interface_);
				if (result == null) result = caseType(interface_);
				if (result == null) result = caseNamed(interface_);
				if (result == null) result = caseAnnotationTarget(interface_);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.FEATURE: {
				Feature feature = (Feature)theEObject;
				T result = caseFeature(feature);
				if (result == null) result = caseType(feature);
				if (result == null) result = caseNamed(feature);
				if (result == null) result = caseAnnotationTarget(feature);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.MODULE: {
				Module module = (Module)theEObject;
				T result = caseModule(module);
				if (result == null) result = caseType(module);
				if (result == null) result = caseNamed(module);
				if (result == null) result = caseAnnotationTarget(module);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.MEMBER: {
				Member member = (Member)theEObject;
				T result = caseMember(member);
				if (result == null) result = caseAnnotationTarget(member);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.DEPENDS_MEMBER: {
				DependsMember dependsMember = (DependsMember)theEObject;
				T result = caseDependsMember(dependsMember);
				if (result == null) result = caseMember(dependsMember);
				if (result == null) result = caseAnnotationTarget(dependsMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.ABSTRACT_FEATURE_LIST_MEMBER: {
				AbstractFeatureListMember abstractFeatureListMember = (AbstractFeatureListMember)theEObject;
				T result = caseAbstractFeatureListMember(abstractFeatureListMember);
				if (result == null) result = caseMember(abstractFeatureListMember);
				if (result == null) result = caseAnnotationTarget(abstractFeatureListMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.REQUIRES_MEMBER: {
				RequiresMember requiresMember = (RequiresMember)theEObject;
				T result = caseRequiresMember(requiresMember);
				if (result == null) result = caseAbstractFeatureListMember(requiresMember);
				if (result == null) result = caseMember(requiresMember);
				if (result == null) result = caseAnnotationTarget(requiresMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.PROVIDES_MEMBER: {
				ProvidesMember providesMember = (ProvidesMember)theEObject;
				T result = caseProvidesMember(providesMember);
				if (result == null) result = caseAbstractFeatureListMember(providesMember);
				if (result == null) result = caseMember(providesMember);
				if (result == null) result = caseAnnotationTarget(providesMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.ABSTRACT_FILE_LIST_MEMBER: {
				AbstractFileListMember abstractFileListMember = (AbstractFileListMember)theEObject;
				T result = caseAbstractFileListMember(abstractFileListMember);
				if (result == null) result = caseMember(abstractFileListMember);
				if (result == null) result = caseAnnotationTarget(abstractFileListMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.SOURCE_MEMBER: {
				SourceMember sourceMember = (SourceMember)theEObject;
				T result = caseSourceMember(sourceMember);
				if (result == null) result = caseAbstractFileListMember(sourceMember);
				if (result == null) result = caseMember(sourceMember);
				if (result == null) result = caseAnnotationTarget(sourceMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.OBJECT_MEMBER: {
				ObjectMember objectMember = (ObjectMember)theEObject;
				T result = caseObjectMember(objectMember);
				if (result == null) result = caseAbstractFileListMember(objectMember);
				if (result == null) result = caseMember(objectMember);
				if (result == null) result = caseAnnotationTarget(objectMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.FILE_NAME: {
				FileName fileName = (FileName)theEObject;
				T result = caseFileName(fileName);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.OPTION_MEMBER: {
				OptionMember optionMember = (OptionMember)theEObject;
				T result = caseOptionMember(optionMember);
				if (result == null) result = caseMember(optionMember);
				if (result == null) result = caseAnnotationTarget(optionMember);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.PROPERTY: {
				Property property = (Property)theEObject;
				T result = caseProperty(property);
				if (result == null) result = caseNamed(property);
				if (result == null) result = caseAnnotationTarget(property);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.STRING_PROPERTY: {
				StringProperty stringProperty = (StringProperty)theEObject;
				T result = caseStringProperty(stringProperty);
				if (result == null) result = caseProperty(stringProperty);
				if (result == null) result = caseNamed(stringProperty);
				if (result == null) result = caseAnnotationTarget(stringProperty);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.NUMBER_PROPERTY: {
				NumberProperty numberProperty = (NumberProperty)theEObject;
				T result = caseNumberProperty(numberProperty);
				if (result == null) result = caseProperty(numberProperty);
				if (result == null) result = caseNamed(numberProperty);
				if (result == null) result = caseAnnotationTarget(numberProperty);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.BOOLEAN_PROPERTY: {
				BooleanProperty booleanProperty = (BooleanProperty)theEObject;
				T result = caseBooleanProperty(booleanProperty);
				if (result == null) result = caseProperty(booleanProperty);
				if (result == null) result = caseNamed(booleanProperty);
				if (result == null) result = caseAnnotationTarget(booleanProperty);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.TYPE_PROPERTY: {
				TypeProperty typeProperty = (TypeProperty)theEObject;
				T result = caseTypeProperty(typeProperty);
				if (result == null) result = caseProperty(typeProperty);
				if (result == null) result = caseNamed(typeProperty);
				if (result == null) result = caseAnnotationTarget(typeProperty);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.VALUE: {
				Value value = (Value)theEObject;
				T result = caseValue(value);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.STRING_LITERAL: {
				StringLiteral stringLiteral = (StringLiteral)theEObject;
				T result = caseStringLiteral(stringLiteral);
				if (result == null) result = caseValue(stringLiteral);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.NUMBER_LITERAL: {
				NumberLiteral numberLiteral = (NumberLiteral)theEObject;
				T result = caseNumberLiteral(numberLiteral);
				if (result == null) result = caseValue(numberLiteral);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.BOOLEAN_LITERAL: {
				BooleanLiteral booleanLiteral = (BooleanLiteral)theEObject;
				T result = caseBooleanLiteral(booleanLiteral);
				if (result == null) result = caseValue(booleanLiteral);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.TYPE_LITERAL: {
				TypeLiteral typeLiteral = (TypeLiteral)theEObject;
				T result = caseTypeLiteral(typeLiteral);
				if (result == null) result = caseValue(typeLiteral);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.PROPERTY_VALUE_BINDING: {
				PropertyValueBinding propertyValueBinding = (PropertyValueBinding)theEObject;
				T result = casePropertyValueBinding(propertyValueBinding);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			case MyFilePackage.NAMED: {
				Named named = (Named)theEObject;
				T result = caseNamed(named);
				if (result == null) result = defaultCase(theEObject);
				return result;
			}
			default: return defaultCase(theEObject);
		}
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Model</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Model</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseModel(Model object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Package</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Package</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T casePackage(org.mybuild.myfile.Package object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Import</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Import</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseImport(Import object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Type</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Type</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseType(Type object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Annotation Type</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Annotation Type</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseAnnotationType(AnnotationType object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Annotation</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Annotation</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseAnnotation(Annotation object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Annotation Target</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Annotation Target</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseAnnotationTarget(AnnotationTarget object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Interface</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Interface</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseInterface(Interface object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Feature</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Feature</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseFeature(Feature object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Module</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Module</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseModule(Module object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseMember(Member object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Depends Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Depends Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseDependsMember(DependsMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Abstract Feature List Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Abstract Feature List Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseAbstractFeatureListMember(AbstractFeatureListMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Requires Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Requires Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseRequiresMember(RequiresMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Provides Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Provides Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseProvidesMember(ProvidesMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Abstract File List Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Abstract File List Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseAbstractFileListMember(AbstractFileListMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Source Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Source Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseSourceMember(SourceMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Object Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Object Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseObjectMember(ObjectMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>File Name</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>File Name</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseFileName(FileName object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Option Member</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Option Member</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseOptionMember(OptionMember object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Property</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Property</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseProperty(Property object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>String Property</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>String Property</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseStringProperty(StringProperty object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Number Property</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Number Property</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseNumberProperty(NumberProperty object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Boolean Property</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Boolean Property</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseBooleanProperty(BooleanProperty object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Type Property</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Type Property</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseTypeProperty(TypeProperty object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Value</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Value</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseValue(Value object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>String Literal</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>String Literal</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseStringLiteral(StringLiteral object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Number Literal</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Number Literal</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseNumberLiteral(NumberLiteral object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Boolean Literal</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Boolean Literal</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseBooleanLiteral(BooleanLiteral object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Type Literal</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Type Literal</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseTypeLiteral(TypeLiteral object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Property Value Binding</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Property Value Binding</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T casePropertyValueBinding(PropertyValueBinding object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>Named</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>Named</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
	 * @generated
	 */
	public T caseNamed(Named object)
	{
		return null;
	}

	/**
	 * Returns the result of interpreting the object as an instance of '<em>EObject</em>'.
	 * <!-- begin-user-doc -->
	 * This implementation returns null;
	 * returning a non-null result will terminate the switch, but this is the last case anyway.
	 * <!-- end-user-doc -->
	 * @param object the target of the switch.
	 * @return the result of interpreting the object as an instance of '<em>EObject</em>'.
	 * @see #doSwitch(org.eclipse.emf.ecore.EObject)
	 * @generated
	 */
	@Override
	public T defaultCase(EObject object)
	{
		return null;
	}

} //MyFileSwitch
