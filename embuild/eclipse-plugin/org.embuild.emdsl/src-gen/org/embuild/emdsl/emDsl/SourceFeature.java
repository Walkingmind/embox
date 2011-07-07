/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Source Feature</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.embuild.emdsl.emDsl.SourceFeature#getFilenames <em>Filenames</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.embuild.emdsl.emDsl.EmDslPackage#getSourceFeature()
 * @model
 * @generated
 */
public interface SourceFeature extends Feature
{
  /**
   * Returns the value of the '<em><b>Filenames</b></em>' attribute list.
   * The list contents are of type {@link java.lang.String}.
   * <!-- begin-user-doc -->
   * <p>
   * If the meaning of the '<em>Filenames</em>' attribute list isn't clear,
   * there really should be more of a description here...
   * </p>
   * <!-- end-user-doc -->
   * @return the value of the '<em>Filenames</em>' attribute list.
   * @see org.embuild.emdsl.emDsl.EmDslPackage#getSourceFeature_Filenames()
   * @model unique="false"
   * @generated
   */
  EList<String> getFilenames();

} // SourceFeature
