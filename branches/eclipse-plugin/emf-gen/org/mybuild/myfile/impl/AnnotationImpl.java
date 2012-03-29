/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile.impl;

import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.emf.ecore.util.InternalEList;

import org.mybuild.myfile.Annotation;
import org.mybuild.myfile.AnnotationTarget;
import org.mybuild.myfile.AnnotationType;
import org.mybuild.myfile.MyFilePackage;
import org.mybuild.myfile.PropertyValueBinding;
import org.mybuild.myfile.Value;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Annotation</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.mybuild.myfile.impl.AnnotationImpl#getType <em>Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.AnnotationImpl#getTarget <em>Target</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.AnnotationImpl#getElements <em>Elements</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.AnnotationImpl#getSingleValue <em>Single Value</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class AnnotationImpl extends EObjectImpl implements Annotation
{
	/**
	 * The cached value of the '{@link #getType() <em>Type</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getType()
	 * @generated
	 * @ordered
	 */
	protected AnnotationType type;

	/**
	 * The cached value of the '{@link #getElements() <em>Elements</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getElements()
	 * @generated
	 * @ordered
	 */
	protected EList<PropertyValueBinding> elements;

	/**
	 * The cached value of the '{@link #getSingleValue() <em>Single Value</em>}' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getSingleValue()
	 * @generated
	 * @ordered
	 */
	protected Value singleValue;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected AnnotationImpl()
	{
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass()
	{
		return MyFilePackage.Literals.ANNOTATION;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public AnnotationType getType()
	{
		if (type != null && type.eIsProxy()) {
			InternalEObject oldType = (InternalEObject)type;
			type = (AnnotationType)eResolveProxy(oldType);
			if (type != oldType) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, MyFilePackage.ANNOTATION__TYPE, oldType, type));
			}
		}
		return type;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public AnnotationType basicGetType()
	{
		return type;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setType(AnnotationType newType)
	{
		AnnotationType oldType = type;
		type = newType;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, MyFilePackage.ANNOTATION__TYPE, oldType, type));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public AnnotationTarget getTarget()
	{
		if (eContainerFeatureID() != MyFilePackage.ANNOTATION__TARGET) return null;
		return (AnnotationTarget)eContainer();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NotificationChain basicSetTarget(AnnotationTarget newTarget, NotificationChain msgs)
	{
		msgs = eBasicSetContainer((InternalEObject)newTarget, MyFilePackage.ANNOTATION__TARGET, msgs);
		return msgs;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setTarget(AnnotationTarget newTarget)
	{
		if (newTarget != eInternalContainer() || (eContainerFeatureID() != MyFilePackage.ANNOTATION__TARGET && newTarget != null)) {
			if (EcoreUtil.isAncestor(this, newTarget))
				throw new IllegalArgumentException("Recursive containment not allowed for " + toString());
			NotificationChain msgs = null;
			if (eInternalContainer() != null)
				msgs = eBasicRemoveFromContainer(msgs);
			if (newTarget != null)
				msgs = ((InternalEObject)newTarget).eInverseAdd(this, MyFilePackage.ANNOTATION_TARGET__ANNOTATIONS, AnnotationTarget.class, msgs);
			msgs = basicSetTarget(newTarget, msgs);
			if (msgs != null) msgs.dispatch();
		}
		else if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, MyFilePackage.ANNOTATION__TARGET, newTarget, newTarget));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<PropertyValueBinding> getElements()
	{
		if (elements == null) {
			elements = new EObjectContainmentEList<PropertyValueBinding>(PropertyValueBinding.class, this, MyFilePackage.ANNOTATION__ELEMENTS);
		}
		return elements;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Value getSingleValue()
	{
		return singleValue;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NotificationChain basicSetSingleValue(Value newSingleValue, NotificationChain msgs)
	{
		Value oldSingleValue = singleValue;
		singleValue = newSingleValue;
		if (eNotificationRequired()) {
			ENotificationImpl notification = new ENotificationImpl(this, Notification.SET, MyFilePackage.ANNOTATION__SINGLE_VALUE, oldSingleValue, newSingleValue);
			if (msgs == null) msgs = notification; else msgs.add(notification);
		}
		return msgs;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setSingleValue(Value newSingleValue)
	{
		if (newSingleValue != singleValue) {
			NotificationChain msgs = null;
			if (singleValue != null)
				msgs = ((InternalEObject)singleValue).eInverseRemove(this, EOPPOSITE_FEATURE_BASE - MyFilePackage.ANNOTATION__SINGLE_VALUE, null, msgs);
			if (newSingleValue != null)
				msgs = ((InternalEObject)newSingleValue).eInverseAdd(this, EOPPOSITE_FEATURE_BASE - MyFilePackage.ANNOTATION__SINGLE_VALUE, null, msgs);
			msgs = basicSetSingleValue(newSingleValue, msgs);
			if (msgs != null) msgs.dispatch();
		}
		else if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, MyFilePackage.ANNOTATION__SINGLE_VALUE, newSingleValue, newSingleValue));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseAdd(InternalEObject otherEnd, int featureID, NotificationChain msgs)
	{
		switch (featureID) {
			case MyFilePackage.ANNOTATION__TARGET:
				if (eInternalContainer() != null)
					msgs = eBasicRemoveFromContainer(msgs);
				return basicSetTarget((AnnotationTarget)otherEnd, msgs);
		}
		return super.eInverseAdd(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs)
	{
		switch (featureID) {
			case MyFilePackage.ANNOTATION__TARGET:
				return basicSetTarget(null, msgs);
			case MyFilePackage.ANNOTATION__ELEMENTS:
				return ((InternalEList<?>)getElements()).basicRemove(otherEnd, msgs);
			case MyFilePackage.ANNOTATION__SINGLE_VALUE:
				return basicSetSingleValue(null, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eBasicRemoveFromContainerFeature(NotificationChain msgs)
	{
		switch (eContainerFeatureID()) {
			case MyFilePackage.ANNOTATION__TARGET:
				return eInternalContainer().eInverseRemove(this, MyFilePackage.ANNOTATION_TARGET__ANNOTATIONS, AnnotationTarget.class, msgs);
		}
		return super.eBasicRemoveFromContainerFeature(msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType)
	{
		switch (featureID) {
			case MyFilePackage.ANNOTATION__TYPE:
				if (resolve) return getType();
				return basicGetType();
			case MyFilePackage.ANNOTATION__TARGET:
				return getTarget();
			case MyFilePackage.ANNOTATION__ELEMENTS:
				return getElements();
			case MyFilePackage.ANNOTATION__SINGLE_VALUE:
				return getSingleValue();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@SuppressWarnings("unchecked")
	@Override
	public void eSet(int featureID, Object newValue)
	{
		switch (featureID) {
			case MyFilePackage.ANNOTATION__TYPE:
				setType((AnnotationType)newValue);
				return;
			case MyFilePackage.ANNOTATION__TARGET:
				setTarget((AnnotationTarget)newValue);
				return;
			case MyFilePackage.ANNOTATION__ELEMENTS:
				getElements().clear();
				getElements().addAll((Collection<? extends PropertyValueBinding>)newValue);
				return;
			case MyFilePackage.ANNOTATION__SINGLE_VALUE:
				setSingleValue((Value)newValue);
				return;
		}
		super.eSet(featureID, newValue);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eUnset(int featureID)
	{
		switch (featureID) {
			case MyFilePackage.ANNOTATION__TYPE:
				setType((AnnotationType)null);
				return;
			case MyFilePackage.ANNOTATION__TARGET:
				setTarget((AnnotationTarget)null);
				return;
			case MyFilePackage.ANNOTATION__ELEMENTS:
				getElements().clear();
				return;
			case MyFilePackage.ANNOTATION__SINGLE_VALUE:
				setSingleValue((Value)null);
				return;
		}
		super.eUnset(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public boolean eIsSet(int featureID)
	{
		switch (featureID) {
			case MyFilePackage.ANNOTATION__TYPE:
				return type != null;
			case MyFilePackage.ANNOTATION__TARGET:
				return getTarget() != null;
			case MyFilePackage.ANNOTATION__ELEMENTS:
				return elements != null && !elements.isEmpty();
			case MyFilePackage.ANNOTATION__SINGLE_VALUE:
				return singleValue != null;
		}
		return super.eIsSet(featureID);
	}

} //AnnotationImpl
