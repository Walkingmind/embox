/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Source Member</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.SourceMember#getFiles <em>Files</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getSourceMember()
 * @model
 * @generated
 */
public interface SourceMember extends Member
{
	/**
	 * Returns the value of the '<em><b>Files</b></em>' containment reference list.
	 * The list contents are of type {@link org.mybuild.myfile.FileName}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Files</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Files</em>' containment reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getSourceMember_Files()
	 * @model containment="true"
	 * @generated
	 */
	EList<FileName> getFiles();

} // SourceMember
