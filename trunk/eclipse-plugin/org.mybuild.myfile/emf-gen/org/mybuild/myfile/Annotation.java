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
 * A representation of the model object '<em><b>Annotation</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.mybuild.myfile.Annotation#getType <em>Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.Annotation#getTarget <em>Target</em>}</li>
 *   <li>{@link org.mybuild.myfile.Annotation#getElements <em>Elements</em>}</li>
 *   <li>{@link org.mybuild.myfile.Annotation#getSingleValue <em>Single Value</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.mybuild.myfile.MyFilePackage#getAnnotation()
 * @model
 * @generated
 */
public interface Annotation extends EObject {
	/**
	 * Returns the value of the '<em><b>Type</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Type</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Type</em>' reference.
	 * @see #setType(AnnotationType)
	 * @see org.mybuild.myfile.MyFilePackage#getAnnotation_Type()
	 * @model
	 * @generated
	 */
	AnnotationType getType();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Annotation#getType <em>Type</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Type</em>' reference.
	 * @see #getType()
	 * @generated
	 */
	void setType(AnnotationType value);

	/**
	 * Returns the value of the '<em><b>Target</b></em>' container reference.
	 * It is bidirectional and its opposite is '{@link org.mybuild.myfile.AnnotationTarget#getAnnotations <em>Annotations</em>}'.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Target</em>' container reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Target</em>' container reference.
	 * @see #setTarget(AnnotationTarget)
	 * @see org.mybuild.myfile.MyFilePackage#getAnnotation_Target()
	 * @see org.mybuild.myfile.AnnotationTarget#getAnnotations
	 * @model opposite="annotations" transient="false"
	 * @generated
	 */
	AnnotationTarget getTarget();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Annotation#getTarget <em>Target</em>}' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Target</em>' container reference.
	 * @see #getTarget()
	 * @generated
	 */
	void setTarget(AnnotationTarget value);

	/**
	 * Returns the value of the '<em><b>Elements</b></em>' containment reference list.
	 * The list contents are of type {@link org.mybuild.myfile.PropertyValueBinding}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Elements</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Elements</em>' containment reference list.
	 * @see org.mybuild.myfile.MyFilePackage#getAnnotation_Elements()
	 * @model containment="true"
	 * @generated
	 */
	EList<PropertyValueBinding> getElements();

	/**
	 * Returns the value of the '<em><b>Single Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Single Value</em>' containment reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Single Value</em>' containment reference.
	 * @see #setSingleValue(Value)
	 * @see org.mybuild.myfile.MyFilePackage#getAnnotation_SingleValue()
	 * @model containment="true"
	 * @generated
	 */
	Value getSingleValue();

	/**
	 * Sets the value of the '{@link org.mybuild.myfile.Annotation#getSingleValue <em>Single Value</em>}' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Single Value</em>' containment reference.
	 * @see #getSingleValue()
	 * @generated
	 */
	void setSingleValue(Value value);

} // Annotation
