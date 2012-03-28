/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile.impl;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import org.eclipse.emf.ecore.util.EcoreUtil;

import org.mybuild.myfile.Member;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.MyFilePackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Member</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.mybuild.myfile.impl.MemberImpl#getContainingModule <em>Containing Module</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class MemberImpl extends AnnotationTargetImpl implements Member
{
	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected MemberImpl()
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
		return MyFilePackage.Literals.MEMBER;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Module getContainingModule()
	{
		if (eContainerFeatureID() != MyFilePackage.MEMBER__CONTAINING_MODULE) return null;
		return (Module)eContainer();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NotificationChain basicSetContainingModule(Module newContainingModule, NotificationChain msgs)
	{
		msgs = eBasicSetContainer((InternalEObject)newContainingModule, MyFilePackage.MEMBER__CONTAINING_MODULE, msgs);
		return msgs;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setContainingModule(Module newContainingModule)
	{
		if (newContainingModule != eInternalContainer() || (eContainerFeatureID() != MyFilePackage.MEMBER__CONTAINING_MODULE && newContainingModule != null))
		{
			if (EcoreUtil.isAncestor(this, newContainingModule))
				throw new IllegalArgumentException("Recursive containment not allowed for " + toString());
			NotificationChain msgs = null;
			if (eInternalContainer() != null)
				msgs = eBasicRemoveFromContainer(msgs);
			if (newContainingModule != null)
				msgs = ((InternalEObject)newContainingModule).eInverseAdd(this, MyFilePackage.MODULE__MEMBERS, Module.class, msgs);
			msgs = basicSetContainingModule(newContainingModule, msgs);
			if (msgs != null) msgs.dispatch();
		}
		else if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, MyFilePackage.MEMBER__CONTAINING_MODULE, newContainingModule, newContainingModule));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseAdd(InternalEObject otherEnd, int featureID, NotificationChain msgs)
	{
		switch (featureID)
		{
			case MyFilePackage.MEMBER__CONTAINING_MODULE:
				if (eInternalContainer() != null)
					msgs = eBasicRemoveFromContainer(msgs);
				return basicSetContainingModule((Module)otherEnd, msgs);
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
		switch (featureID)
		{
			case MyFilePackage.MEMBER__CONTAINING_MODULE:
				return basicSetContainingModule(null, msgs);
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
		switch (eContainerFeatureID())
		{
			case MyFilePackage.MEMBER__CONTAINING_MODULE:
				return eInternalContainer().eInverseRemove(this, MyFilePackage.MODULE__MEMBERS, Module.class, msgs);
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
		switch (featureID)
		{
			case MyFilePackage.MEMBER__CONTAINING_MODULE:
				return getContainingModule();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eSet(int featureID, Object newValue)
	{
		switch (featureID)
		{
			case MyFilePackage.MEMBER__CONTAINING_MODULE:
				setContainingModule((Module)newValue);
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
		switch (featureID)
		{
			case MyFilePackage.MEMBER__CONTAINING_MODULE:
				setContainingModule((Module)null);
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
		switch (featureID)
		{
			case MyFilePackage.MEMBER__CONTAINING_MODULE:
				return getContainingModule() != null;
		}
		return super.eIsSet(featureID);
	}

} //MemberImpl
