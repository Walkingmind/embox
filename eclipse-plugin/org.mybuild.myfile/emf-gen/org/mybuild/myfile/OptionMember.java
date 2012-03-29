/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Option Member</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.OptionMember#getProperty <em>Property</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getOptionMember()
 * @model
 * @generated
 */
public interface OptionMember extends Member
{
	/**
	 * Returns the value of the '<em><b>Property</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Property</em>' containment reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Property</em>' containment reference.
	 * @see #setProperty(Property)
	 * @see org.mybuild.myfile.MyFilePackage#getOptionMember_Property()
	 * @model containment="true"
	 * @generated
	 */
	Property getProperty();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.OptionMember#getProperty <em>Property</em>}' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Property</em>' containment reference.
	 * @see #getProperty()
	 * @generated
	 */
	void setProperty(Property value);

} // OptionMember
