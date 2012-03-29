/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Member</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.Member#getContainingModule <em>Containing Module</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getMember()
 * @model
 * @generated
 */
public interface Member extends AnnotationTarget {
	/**
	 * Returns the value of the '<em><b>Containing Module</b></em>' container reference.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getMembers <em>Members</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Containing Module</em>' container reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Containing Module</em>' container reference.
	 * @see #setContainingModule(Module)
	 * @see org.mybuild.myfile.MyFilePackage#getMember_ContainingModule()
	 * @see org.mybuild.myfile.Module#getMembers
	 * @model opposite="members" transient="false"
	 * @generated
	 */
	Module getContainingModule();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Member#getContainingModule <em>Containing Module</em>}' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Containing Module</em>' container reference.
	 * @see #getContainingModule()
	 * @generated
	 */
	void setContainingModule(Module value);

} // Member
