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
 *   <li>{@link org.mybuild.myfile.Module#getSubTypes <em>Sub Types</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getAllSuperTypes <em>All Super Types</em>}</li>
 *   <li>{@link org.mybuild.myfile.Module#getAllSubTypes <em>All Sub Types</em>}</li>
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
public interface Module extends Type {
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
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getSubTypes <em>Sub Types</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Super Type</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Super Type</em>' reference.
	 * @see #setSuperType(Module)
	 * @see org.mybuild.myfile.MyFilePackage#getModule_SuperType()
	 * @see org.mybuild.myfile.Module#getSubTypes
	 * @model opposite="subTypes" resolveProxies="false"
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
	 * Returns the value of the '<em><b>Sub Types</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getSuperType <em>Super Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Sub Types</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Sub Types</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_SubTypes()
	 * @see org.mybuild.myfile.Module#getSuperType
	 * @model opposite="superType" resolveProxies="false" transient="true"
	 * @generated
	 */
	EList<Module> getSubTypes();

	/**
	 * Returns the value of the '<em><b>All Super Types</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getAllSubTypes <em>All Sub Types</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>All Super Types</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>All Super Types</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_AllSuperTypes()
	 * @see org.mybuild.myfile.Module#getAllSubTypes
	 * @model opposite="allSubTypes" resolveProxies="false" transient="true" changeable="false" volatile="true" derived="true"
	 * @generated
	 */
	EList<Module> getAllSuperTypes();

	/**
	 * Returns the value of the '<em><b>All Sub Types</b></em>' reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Module}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getAllSuperTypes <em>All Super Types</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>All Sub Types</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>All Sub Types</em>' reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getModule_AllSubTypes()
	 * @see org.mybuild.myfile.Module#getAllSuperTypes
	 * @model opposite="allSuperTypes" resolveProxies="false" transient="true" changeable="false" volatile="true" derived="true"
	 * @generated
	 */
	EList<Module> getAllSubTypes();

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
	 * @model resolveProxies="false" transient="true" volatile="true" derived="true"
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
	 * @model resolveProxies="false" transient="true" volatile="true" derived="true"
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
	 * @model resolveProxies="false" transient="true" volatile="true" derived="true"
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
	 * @model resolveProxies="false" transient="true" volatile="true" derived="true"
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
	 * @model resolveProxies="false" transient="true" volatile="true" derived="true"
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
	 * @model resolveProxies="false" transient="true" volatile="true" derived="true"
	 * @generated
	 */
	EList<FileName> getObjects();

} // Module
