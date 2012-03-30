/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Annotation Target</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.AnnotationTarget#getAnnotations <em>Annotations</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getAnnotationTarget()
 * @model
 * @generated
 */
public interface AnnotationTarget extends EObject {
	/**
	 * Returns the value of the '<em><b>Annotations</b></em>' containment reference list.
	 * The list contents are of type {@link org.mybuild.myfile.Annotation}.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.Annotation#getTarget <em>Target</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Annotations</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Annotations</em>' containment reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getAnnotationTarget_Annotations()
	 * @see org.mybuild.myfile.Annotation#getTarget
	 * @model opposite="target" containment="true"
	 * @generated
	 */
	EList<Annotation> getAnnotations();

} // AnnotationTarget
