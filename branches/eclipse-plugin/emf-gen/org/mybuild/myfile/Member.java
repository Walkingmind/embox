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
 *   <li>{@link org.mybuild.myfile.Member#getModule <em>Module</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getMember()
 * @model
 * @generated
 */
public interface Member extends AnnotationTarget
{
	/**
	 * Returns the value of the '<em><b>Module</b></em>' container reference.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Module#getMembers <em>Members</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Module</em>' container reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Module</em>' container reference.
	 * @see #setModule(Module)
	 * @see org.mybuild.myfile.MyFilePackage#getMember_Module()
	 * @see org.mybuild.myfile.Module#getMembers
	 * @model opposite="members" transient="false"
	 * @generated
	 */
	Module getModule();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Member#getModule <em>Module</em>}' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Module</em>' container reference.
	 * @see #getModule()
	 * @generated
	 */
	void setModule(Module value);

} // Member
