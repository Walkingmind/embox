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

import org.eclipse.emf.ecore.util.EObjectContainmentWithInverseEList;
import org.eclipse.emf.ecore.util.EObjectWithInverseResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.mybuild.myfile.Feature;
import org.mybuild.myfile.FileName;
import org.mybuild.myfile.Member;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.MyFilePackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Module</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#isStatic <em>Static</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#isAbstract <em>Abstract</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getSuperType <em>Super Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getSubType <em>Sub Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getAllSuperType <em>All Super Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getAllSubType <em>All Sub Type</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getMembers <em>Members</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getDepends <em>Depends</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getDependent <em>Dependent</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getProvides <em>Provides</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getRequires <em>Requires</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getSources <em>Sources</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getObjects <em>Objects</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class ModuleImpl extends TypeImpl implements Module
{
	/**
	 * The default value of the '{@link #isStatic() <em>Static</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isStatic()
	 * @generated
	 * @ordered
	 */
	protected static final boolean STATIC_EDEFAULT = false;

	/**
	 * The cached value of the '{@link #isStatic() <em>Static</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isStatic()
	 * @generated
	 * @ordered
	 */
	protected boolean static_ = STATIC_EDEFAULT;

	/**
	 * The default value of the '{@link #isAbstract() <em>Abstract</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isAbstract()
	 * @generated
	 * @ordered
	 */
	protected static final boolean ABSTRACT_EDEFAULT = false;

	/**
	 * The cached value of the '{@link #isAbstract() <em>Abstract</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isAbstract()
	 * @generated
	 * @ordered
	 */
	protected boolean abstract_ = ABSTRACT_EDEFAULT;

	/**
	 * The cached value of the '{@link #getSuperType() <em>Super Type</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getSuperType()
	 * @generated
	 * @ordered
	 */
	protected Module superType;

	/**
	 * The cached value of the '{@link #getSubType() <em>Sub Type</em>}' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getSubType()
	 * @generated
	 * @ordered
	 */
	protected EList<Module> subType;

	/**
	 * The cached value of the '{@link #getMembers() <em>Members</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getMembers()
	 * @generated
	 * @ordered
	 */
	protected EList<Member> members;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected ModuleImpl()
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
		return MyFilePackage.Literals.MODULE;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isStatic()
	{
		return static_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setStatic(boolean newStatic)
	{
		boolean oldStatic = static_;
		static_ = newStatic;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, MyFilePackage.MODULE__STATIC, oldStatic, static_));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isAbstract()
	{
		return abstract_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setAbstract(boolean newAbstract)
	{
		boolean oldAbstract = abstract_;
		abstract_ = newAbstract;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, MyFilePackage.MODULE__ABSTRACT, oldAbstract, abstract_));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Module getSuperType()
	{
		if (superType != null && superType.eIsProxy())
		{
			InternalEObject oldSuperType = (InternalEObject)superType;
			superType = (Module)eResolveProxy(oldSuperType);
			if (superType != oldSuperType)
			{
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, MyFilePackage.MODULE__SUPER_TYPE, oldSuperType, superType));
			}
		}
		return superType;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Module basicGetSuperType()
	{
		return superType;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NotificationChain basicSetSuperType(Module newSuperType, NotificationChain msgs)
	{
		Module oldSuperType = superType;
		superType = newSuperType;
		if (eNotificationRequired())
		{
			ENotificationImpl notification = new ENotificationImpl(this, Notification.SET, MyFilePackage.MODULE__SUPER_TYPE, oldSuperType, newSuperType);
			if (msgs == null) msgs = notification; else msgs.add(notification);
		}
		return msgs;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setSuperType(Module newSuperType)
	{
		if (newSuperType != superType)
		{
			NotificationChain msgs = null;
			if (superType != null)
				msgs = ((InternalEObject)superType).eInverseRemove(this, MyFilePackage.MODULE__SUB_TYPE, Module.class, msgs);
			if (newSuperType != null)
				msgs = ((InternalEObject)newSuperType).eInverseAdd(this, MyFilePackage.MODULE__SUB_TYPE, Module.class, msgs);
			msgs = basicSetSuperType(newSuperType, msgs);
			if (msgs != null) msgs.dispatch();
		}
		else if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, MyFilePackage.MODULE__SUPER_TYPE, newSuperType, newSuperType));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getSubType()
	{
		if (subType == null)
		{
			subType = new EObjectWithInverseResolvingEList<Module>(Module.class, this, MyFilePackage.MODULE__SUB_TYPE, MyFilePackage.MODULE__SUPER_TYPE);
		}
		return subType;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getAllSuperType()
	{
		// TODO: implement this method to return the 'All Super Type' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getAllSubType()
	{
		// TODO: implement this method to return the 'All Sub Type' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Member> getMembers()
	{
		if (members == null)
		{
			members = new EObjectContainmentWithInverseEList<Member>(Member.class, this, MyFilePackage.MODULE__MEMBERS, MyFilePackage.MEMBER__CONTAINING_MODULE);
		}
		return members;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getDepends()
	{
		// TODO: implement this method to return the 'Depends' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getDependent()
	{
		// TODO: implement this method to return the 'Dependent' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Feature> getProvides()
	{
		// TODO: implement this method to return the 'Provides' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Feature> getRequires()
	{
		// TODO: implement this method to return the 'Requires' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<FileName> getSources()
	{
		// TODO: implement this method to return the 'Sources' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<FileName> getObjects()
	{
		// TODO: implement this method to return the 'Objects' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
		throw new UnsupportedOperationException();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@SuppressWarnings("unchecked")
	@Override
	public NotificationChain eInverseAdd(InternalEObject otherEnd, int featureID, NotificationChain msgs)
	{
		switch (featureID)
		{
			case MyFilePackage.MODULE__SUPER_TYPE:
				if (superType != null)
					msgs = ((InternalEObject)superType).eInverseRemove(this, MyFilePackage.MODULE__SUB_TYPE, Module.class, msgs);
				return basicSetSuperType((Module)otherEnd, msgs);
			case MyFilePackage.MODULE__SUB_TYPE:
				return ((InternalEList<InternalEObject>)(InternalEList<?>)getSubType()).basicAdd(otherEnd, msgs);
			case MyFilePackage.MODULE__MEMBERS:
				return ((InternalEList<InternalEObject>)(InternalEList<?>)getMembers()).basicAdd(otherEnd, msgs);
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
			case MyFilePackage.MODULE__SUPER_TYPE:
				return basicSetSuperType(null, msgs);
			case MyFilePackage.MODULE__SUB_TYPE:
				return ((InternalEList<?>)getSubType()).basicRemove(otherEnd, msgs);
			case MyFilePackage.MODULE__MEMBERS:
				return ((InternalEList<?>)getMembers()).basicRemove(otherEnd, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
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
			case MyFilePackage.MODULE__STATIC:
				return isStatic();
			case MyFilePackage.MODULE__ABSTRACT:
				return isAbstract();
			case MyFilePackage.MODULE__SUPER_TYPE:
				if (resolve) return getSuperType();
				return basicGetSuperType();
			case MyFilePackage.MODULE__SUB_TYPE:
				return getSubType();
			case MyFilePackage.MODULE__ALL_SUPER_TYPE:
				return getAllSuperType();
			case MyFilePackage.MODULE__ALL_SUB_TYPE:
				return getAllSubType();
			case MyFilePackage.MODULE__MEMBERS:
				return getMembers();
			case MyFilePackage.MODULE__DEPENDS:
				return getDepends();
			case MyFilePackage.MODULE__DEPENDENT:
				return getDependent();
			case MyFilePackage.MODULE__PROVIDES:
				return getProvides();
			case MyFilePackage.MODULE__REQUIRES:
				return getRequires();
			case MyFilePackage.MODULE__SOURCES:
				return getSources();
			case MyFilePackage.MODULE__OBJECTS:
				return getObjects();
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
		switch (featureID)
		{
			case MyFilePackage.MODULE__STATIC:
				setStatic((Boolean)newValue);
				return;
			case MyFilePackage.MODULE__ABSTRACT:
				setAbstract((Boolean)newValue);
				return;
			case MyFilePackage.MODULE__SUPER_TYPE:
				setSuperType((Module)newValue);
				return;
			case MyFilePackage.MODULE__SUB_TYPE:
				getSubType().clear();
				getSubType().addAll((Collection<? extends Module>)newValue);
				return;
			case MyFilePackage.MODULE__MEMBERS:
				getMembers().clear();
				getMembers().addAll((Collection<? extends Member>)newValue);
				return;
			case MyFilePackage.MODULE__DEPENDS:
				getDepends().clear();
				getDepends().addAll((Collection<? extends Module>)newValue);
				return;
			case MyFilePackage.MODULE__DEPENDENT:
				getDependent().clear();
				getDependent().addAll((Collection<? extends Module>)newValue);
				return;
			case MyFilePackage.MODULE__PROVIDES:
				getProvides().clear();
				getProvides().addAll((Collection<? extends Feature>)newValue);
				return;
			case MyFilePackage.MODULE__REQUIRES:
				getRequires().clear();
				getRequires().addAll((Collection<? extends Feature>)newValue);
				return;
			case MyFilePackage.MODULE__SOURCES:
				getSources().clear();
				getSources().addAll((Collection<? extends FileName>)newValue);
				return;
			case MyFilePackage.MODULE__OBJECTS:
				getObjects().clear();
				getObjects().addAll((Collection<? extends FileName>)newValue);
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
			case MyFilePackage.MODULE__STATIC:
				setStatic(STATIC_EDEFAULT);
				return;
			case MyFilePackage.MODULE__ABSTRACT:
				setAbstract(ABSTRACT_EDEFAULT);
				return;
			case MyFilePackage.MODULE__SUPER_TYPE:
				setSuperType((Module)null);
				return;
			case MyFilePackage.MODULE__SUB_TYPE:
				getSubType().clear();
				return;
			case MyFilePackage.MODULE__MEMBERS:
				getMembers().clear();
				return;
			case MyFilePackage.MODULE__DEPENDS:
				getDepends().clear();
				return;
			case MyFilePackage.MODULE__DEPENDENT:
				getDependent().clear();
				return;
			case MyFilePackage.MODULE__PROVIDES:
				getProvides().clear();
				return;
			case MyFilePackage.MODULE__REQUIRES:
				getRequires().clear();
				return;
			case MyFilePackage.MODULE__SOURCES:
				getSources().clear();
				return;
			case MyFilePackage.MODULE__OBJECTS:
				getObjects().clear();
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
			case MyFilePackage.MODULE__STATIC:
				return static_ != STATIC_EDEFAULT;
			case MyFilePackage.MODULE__ABSTRACT:
				return abstract_ != ABSTRACT_EDEFAULT;
			case MyFilePackage.MODULE__SUPER_TYPE:
				return superType != null;
			case MyFilePackage.MODULE__SUB_TYPE:
				return subType != null && !subType.isEmpty();
			case MyFilePackage.MODULE__ALL_SUPER_TYPE:
				return !getAllSuperType().isEmpty();
			case MyFilePackage.MODULE__ALL_SUB_TYPE:
				return !getAllSubType().isEmpty();
			case MyFilePackage.MODULE__MEMBERS:
				return members != null && !members.isEmpty();
			case MyFilePackage.MODULE__DEPENDS:
				return !getDepends().isEmpty();
			case MyFilePackage.MODULE__DEPENDENT:
				return !getDependent().isEmpty();
			case MyFilePackage.MODULE__PROVIDES:
				return !getProvides().isEmpty();
			case MyFilePackage.MODULE__REQUIRES:
				return !getRequires().isEmpty();
			case MyFilePackage.MODULE__SOURCES:
				return !getSources().isEmpty();
			case MyFilePackage.MODULE__OBJECTS:
				return !getObjects().isEmpty();
		}
		return super.eIsSet(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString()
	{
		if (eIsProxy()) return super.toString();

		StringBuffer result = new StringBuffer(super.toString());
		result.append(" (static: ");
		result.append(static_);
		result.append(", abstract: ");
		result.append(abstract_);
		result.append(')');
		return result.toString();
	}

} //ModuleImpl
