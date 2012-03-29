/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Feature</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.Feature#getSuperType <em>Super Type</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getFeature()
 * @model
 * @generated
 */
public interface Feature extends Type
{
	/**
	 * Returns the value of the '<em><b>Super Type</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Super Type</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Super Type</em>' reference.
	 * @see #setSuperType(Feature)
	 * @see org.mybuild.myfile.MyFilePackage#getFeature_SuperType()
	 * @model
	 * @generated
	 */
	Feature getSuperType();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Feature#getSuperType <em>Super Type</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Super Type</em>' reference.
	 * @see #getSuperType()
	 * @generated
	 */
	void setSuperType(Feature value);

} // Feature
