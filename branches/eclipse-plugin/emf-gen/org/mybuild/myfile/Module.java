/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Module</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.Module#isStatic <em>Static</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#isAbstract <em>Abstract</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getSuperType <em>Super Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getSubType <em>Sub Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getAllSuperType <em>All Super Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getAllSubType <em>All Sub Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getMembers <em>Members</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getDepends <em>Depends</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getDependent <em>Dependent</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getProvides <em>Provides</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getRequires <em>Requires</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getSources <em>Sources</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getObjects <em>Objects</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getModule()
 * @model
 * @generated
 */
public interface Module extends Type
{
	/**
	 * Returns the value of the '<em><b>Static</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Static</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Static</em>' attribute.
	 * @see #setStatic(boolean)
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Static()
	 * @model
	 * @generated
	 */
	boolean isStatic();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Module#isStatic <em>Static</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Static</em>' attribute.
	 * @see #isStatic()
	 * @generated
	 */
	void setStatic(boolean value);

	/**
	 * Returns the value of the '<em><b>Abstract</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Abstract</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Abstract</em>' attribute.
	 * @see #setAbstract(boolean)
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Abstract()
	 * @model
	 * @generated
	 */
	boolean isAbstract();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Module#isAbstract <em>Abstract</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Abstract</em>' attribute.
	 * @see #isAbstract()
	 * @generated
	 */
	void setAbstract(boolean value);

	/**
	 * Returns the value of the '<em><b>Super Type</b></em>' reference.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getSubType <em>Sub Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Super Type</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Super Type</em>' reference.
	 * @see #setSuperType(Module)
	 * @see org.mybuild.myfile.MyFilePackage#getModule_SuperType()
	 * @see org.mybuild.myfile.Module#getSubType
	 * @model opposite="subType"
	 * @generated
	 */
	Module getSuperType();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Module#getSuperType <em>Super Type</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Super Type</em>' reference.
	 * @see #getSuperType()
	 * @generated
	 */
	void setSuperType(Module value);

	/**
	 * Returns the value of the '<em><b>Sub Type</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getSuperType <em>Super Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Sub Type</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Sub Type</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_SubType()
	 * @see org.mybuild.myfile.Module#getSuperType
	 * @model opposite="superType"
	 * @generated
	 */
	EList<Module> getSubType();

	/**
	 * Returns the value of the '<em><b>All Super Type</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getAllSubType <em>All Sub Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>All Super Type</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>All Super Type</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_AllSuperType()
	 * @see org.mybuild.myfile.Module#getAllSubType
	 * @model opposite="allSubType" transient="true" changeable="false" volatile="true" derived="true"
	 * @generated
	 */
	EList<Module> getAllSuperType();

	/**
	 * Returns the value of the '<em><b>All Sub Type</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getAllSuperType <em>All Super Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>All Sub Type</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>All Sub Type</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_AllSubType()
	 * @see org.mybuild.myfile.Module#getAllSuperType
	 * @model opposite="allSuperType" transient="true" changeable="false" volatile="true" derived="true"
	 * @generated
	 */
	EList<Module> getAllSubType();

	/**
	 * Returns the value of the '<em><b>Members</b></em>' containment reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Member}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Member#getContainingModule <em>Containing Module</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Members</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Members</em>' containment reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Members()
	 * @see org.mybuild.myfile.Member#getContainingModule
	 * @model opposite="containingModule" containment="true"
	 * @generated
	 */
	EList<Member> getMembers();

	/**
	 * Returns the value of the '<em><b>Depends</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Depends</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Depends</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Depends()
	 * @model transient="true" volatile="true" derived="true"
	 * @generated
	 */
	EList<Module> getDepends();

	/**
	 * Returns the value of the '<em><b>Dependent</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Dependent</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Dependent</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Dependent()
	 * @model transient="true" volatile="true" derived="true"
	 * @generated
	 */
	EList<Module> getDependent();

	/**
	 * Returns the value of the '<em><b>Provides</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Feature}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Provides</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Provides</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Provides()
	 * @model transient="true" volatile="true" derived="true"
	 * @generated
	 */
	EList<Feature> getProvides();

	/**
	 * Returns the value of the '<em><b>Requires</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Feature}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Requires</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Requires</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Requires()
	 * @model transient="true" volatile="true" derived="true"
	 * @generated
	 */
	EList<Feature> getRequires();

	/**
	 * Returns the value of the '<em><b>Sources</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.FileName}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Sources</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Sources</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Sources()
	 * @model transient="true" volatile="true" derived="true"
	 * @generated
	 */
	EList<FileName> getSources();

	/**
	 * Returns the value of the '<em><b>Objects</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.FileName}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Objects</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Objects</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_Objects()
	 * @model transient="true" volatile="true" derived="true"
	 * @generated
	 */
	EList<FileName> getObjects();

} // Module
