/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Modifier</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.embuild.emdsl.emDsl.Modifier#isAbstract <em>Abstract</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.embuild.emdsl.emDsl.EmDslPackage#getModifier()
 * @model
 * @generated
 */
public interface Modifier extends Module
{
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
   * @see org.embuild.emdsl.emDsl.EmDslPackage#getModifier_Abstract()
   * @model
   * @generated
   */
  boolean isAbstract();

  /**
   * Sets the value of the '{@link org.embuild.emdsl.emDsl.Modifier#isAbstract <em>Abstract</em>}' attribute.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @param value the new value of the '<em>Abstract</em>' attribute.
   * @see #isAbstract()
   * @generated
   */
  void setAbstract(boolean value);

} // Modifier
