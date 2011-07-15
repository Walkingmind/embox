/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Module</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.embuild.emdsl.emDsl.Module#getName <em>Name</em>}</li>
 *   <li>{@link org.embuild.emdsl.emDsl.Module#getSuperType <em>Super Type</em>}</li>
 *   <li>{@link org.embuild.emdsl.emDsl.Module#getFeatures <em>Features</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.embuild.emdsl.emDsl.EmDslPackage#getModule()
 * @model
 * @generated
 */
public interface Module extends Entity
{
  /**
   * Returns the value of the '<em><b>Name</b></em>' attribute.
   * <!-- begin-user-doc -->
   * <p>
   * If the meaning of the '<em>Name</em>' attribute isn't clear,
   * there really should be more of a description here...
   * </p>
   * <!-- end-user-doc -->
   * @return the value of the '<em>Name</em>' attribute.
   * @see #setName(String)
   * @see org.embuild.emdsl.emDsl.EmDslPackage#getModule_Name()
   * @model
   * @generated
   */
  String getName();

  /**
   * Sets the value of the '{@link org.embuild.emdsl.emDsl.Module#getName <em>Name</em>}' attribute.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @param value the new value of the '<em>Name</em>' attribute.
   * @see #getName()
   * @generated
   */
  void setName(String value);

  /**
   * Returns the value of the '<em><b>Super Type</b></em>' reference.
   * <!-- begin-user-doc -->
   * <p>
   * If the meaning of the '<em>Super Type</em>' reference isn't clear,
   * there really should be more of a description here...
   * </p>
   * <!-- end-user-doc -->
   * @return the value of the '<em>Super Type</em>' reference.
   * @see #setSuperType(Module)
   * @see org.embuild.emdsl.emDsl.EmDslPackage#getModule_SuperType()
   * @model
   * @generated
   */
  Module getSuperType();

  /**
   * Sets the value of the '{@link org.embuild.emdsl.emDsl.Module#getSuperType <em>Super Type</em>}' reference.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @param value the new value of the '<em>Super Type</em>' reference.
   * @see #getSuperType()
   * @generated
   */
  void setSuperType(Module value);

  /**
   * Returns the value of the '<em><b>Features</b></em>' containment reference list.
   * The list contents are of type {@link org.embuild.emdsl.emDsl.Feature}.
   * <!-- begin-user-doc -->
   * <p>
   * If the meaning of the '<em>Features</em>' containment reference list isn't clear,
   * there really should be more of a description here...
   * </p>
   * <!-- end-user-doc -->
   * @return the value of the '<em>Features</em>' containment reference list.
   * @see org.embuild.emdsl.emDsl.EmDslPackage#getModule_Features()
   * @model containment="true"
   * @generated
   */
  EList<Feature> getFeatures();

} // Module
