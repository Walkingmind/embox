/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Type Literal</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.TypeLiteral#getValue <em>Value</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getTypeLiteral()
 * @model
 * @generated
 */
public interface TypeLiteral extends Value {
	/**
	 * Returns the value of the '<em><b>Value</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Value</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Value</em>' reference.
	 * @see #setValue(Type)
	 * @see org.mybuild.myfile.MyFilePackage#getTypeLiteral_Value()
	 * @model
	 * @generated
	 */
	Type getValue();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.TypeLiteral#getValue <em>Value</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Value</em>' reference.
	 * @see #getValue()
	 * @generated
	 */
	void setValue(Type value);

} // TypeLiteral
