/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Depend Feature</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.embuild.emdsl.emDsl.DependFeature#getModules <em>Modules</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.embuild.emdsl.emDsl.EmDslPackage#getDependFeature()
 * @model
 * @generated
 */
public interface DependFeature extends Feature
{
  /**
   * Returns the value of the '<em><b>Modules</b></em>' reference list.
   * The list contents are of type {@link org.embuild.emdsl.emDsl.Module}.
   * <!-- begin-user-doc -->
   * <p>
   * If the meaning of the '<em>Modules</em>' reference list isn't clear,
   * there really should be more of a description here...
   * </p>
   * <!-- end-user-doc -->
   * @return the value of the '<em>Modules</em>' reference list.
   * @see org.embuild.emdsl.emDsl.EmDslPackage#getDependFeature_Modules()
   * @model
   * @generated
   */
  EList<Module> getModules();

} // DependFeature
