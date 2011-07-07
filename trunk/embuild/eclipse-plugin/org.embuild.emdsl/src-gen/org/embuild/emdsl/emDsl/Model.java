/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Model</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.embuild.emdsl.emDsl.Model#getElements <em>Elements</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.embuild.emdsl.emDsl.EmDslPackage#getModel()
 * @model
 * @generated
 */
public interface Model extends EObject
{
  /**
   * Returns the value of the '<em><b>Elements</b></em>' containment reference list.
   * The list contents are of type {@link org.embuild.emdsl.emDsl.Entity}.
   * <!-- begin-user-doc -->
   * <p>
   * If the meaning of the '<em>Elements</em>' containment reference list isn't clear,
   * there really should be more of a description here...
   * </p>
   * <!-- end-user-doc -->
   * @return the value of the '<em>Elements</em>' containment reference list.
   * @see org.embuild.emdsl.emDsl.EmDslPackage#getModel_Elements()
   * @model containment="true"
   * @generated
   */
  EList<Entity> getElements();

} // Model
