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
import org.eclipse.emf.ecore.util.EObjectEList;
import org.eclipse.emf.ecore.util.EObjectWithInverseEList;
import org.eclipse.emf.ecore.util.EObjectWithInverseResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.mybuild.myfile.Feature;
import org.mybuild.myfile.FileName;
import org.mybuild.myfile.Member;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.MyFilePackage;
import org.mybuild.myfile.ObjectMember;
import org.mybuild.myfile.ProvidesMember;
import org.mybuild.myfile.RequiresMember;
import org.mybuild.myfile.SourceMember;
import org.mybuild.myfile.util.MyFileSwitch;

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
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getSubTypes <em>Sub Types</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getAllSuperTypes <em>All Super Types</em>}</li>
 *   <li>{@link org.mybuild.myfile.impl.ModuleImpl#getAllSubTypes <em>All Sub Types</em>}</li>
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
public class ModuleImpl extends TypeImpl implements Module {
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
	 * The cached value of the '{@link #getSubTypes() <em>Sub Types</em>}' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getSubTypes()
	 * @generated
	 * @ordered
	 */
	protected EList<Module> subTypes;

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
	protected ModuleImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return MyFilePackage.Literals.MODULE;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isStatic() {
		return static_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setStatic(boolean newStatic) {
		boolean oldStatic = static_;
		static_ = newStatic;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET,
					MyFilePackage.MODULE__STATIC, oldStatic, static_));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isAbstract() {
		return abstract_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setAbstract(boolean newAbstract) {
		boolean oldAbstract = abstract_;
		abstract_ = newAbstract;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET,
					MyFilePackage.MODULE__ABSTRACT, oldAbstract, abstract_));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Module getSuperType() {
		if (superType != null && superType.eIsProxy()) {
			InternalEObject oldSuperType = (InternalEObject) superType;
			superType = (Module) eResolveProxy(oldSuperType);
			if (superType != oldSuperType) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE,
							MyFilePackage.MODULE__SUPER_TYPE, oldSuperType,
							superType));
			}
		}
		return superType;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Module basicGetSuperType() {
		return superType;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NotificationChain basicSetSuperType(Module newSuperType,
			NotificationChain msgs) {
		Module oldSuperType = superType;
		superType = newSuperType;
		if (eNotificationRequired()) {
			ENotificationImpl notification = new ENotificationImpl(this,
					Notification.SET, MyFilePackage.MODULE__SUPER_TYPE,
					oldSuperType, newSuperType);
			if (msgs == null)
				msgs = notification;
			else
				msgs.add(notification);
		}
		return msgs;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setSuperType(Module newSuperType) {
		if (newSuperType != superType) {
			NotificationChain msgs = null;
			if (superType != null)
				msgs = ((InternalEObject) superType).eInverseRemove(this,
						MyFilePackage.MODULE__SUB_TYPES, Module.class, msgs);
			if (newSuperType != null)
				msgs = ((InternalEObject) newSuperType).eInverseAdd(this,
						MyFilePackage.MODULE__SUB_TYPES, Module.class, msgs);
			msgs = basicSetSuperType(newSuperType, msgs);
			if (msgs != null)
				msgs.dispatch();
		} else if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET,
					MyFilePackage.MODULE__SUPER_TYPE, newSuperType,
					newSuperType));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getSubTypes() {
		if (subTypes == null) {
			subTypes = new EObjectWithInverseResolvingEList<Module>(
					Module.class, this, MyFilePackage.MODULE__SUB_TYPES,
					MyFilePackage.MODULE__SUPER_TYPE);
		}
		return subTypes;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated NOT
	 */
	public EList<Module> getAllSuperTypes() {
		EList<Module> allSuperTypes = new EObjectWithInverseResolvingEList<Module>(
				Module.class, this, MyFilePackage.MODULE__ALL_SUPER_TYPES,
				MyFilePackage.MODULE__ALL_SUB_TYPES);
		for (Module m = getSuperType(); m != null; m = m.getSuperType()) {
			if (allSuperTypes.contains(m)) {
				// inheritance loop.
				break;
			}
			allSuperTypes.add(m);
		}
		return allSuperTypes;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated NOT
	 */
	public EList<Module> getAllSubTypes() {
		EList<Module> allSubTypes = new EObjectWithInverseResolvingEList<Module>(
				Module.class, this, MyFilePackage.MODULE__ALL_SUB_TYPES,
				MyFilePackage.MODULE__ALL_SUPER_TYPES);
		internalPopulateSubTypesList(allSubTypes);
		return allSubTypes;
	}

	private void internalPopulateSubTypesList(EList<Module> allSubTypes) {
		for (Module m : getSubTypes()) {
			if (allSubTypes.contains(m)) {
				continue;
			}
			if (m instanceof ModuleImpl) {
				allSubTypes.add(m);
				((ModuleImpl) m).internalPopulateSubTypesList(allSubTypes);
			}
		}
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Member> getMembers() {
		if (members == null) {
			members = new EObjectContainmentWithInverseEList<Member>(
					Member.class, this, MyFilePackage.MODULE__MEMBERS,
					MyFilePackage.MEMBER__CONTAINING_MODULE);
		}
		return members;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getDepends() {
		// TODO: implement this method to return the 'Depends' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
//		throw new UnsupportedOperationException();
		return new EObjectEList<Module>(Module.class, this, MyFilePackage.MODULE__DEPENDS);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Module> getDependent() {
		// TODO: implement this method to return the 'Dependent' reference list
		// Ensure that you remove @generated or mark it @generated NOT
		// The list is expected to implement org.eclipse.emf.ecore.util.InternalEList and org.eclipse.emf.ecore.EStructuralFeature.Setting
		// so it's likely that an appropriate subclass of org.eclipse.emf.ecore.util.EcoreEList should be used.
//		throw new UnsupportedOperationException();
		return new EObjectEList<Module>(Module.class, this, MyFilePackage.MODULE__DEPENDENT);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated NOT
	 */
	public EList<Feature> getProvides() {
		return flattenMembers(Feature.class, MyFilePackage.MODULE__PROVIDES,
				new MyFileSwitch<EList<Feature>>() {
					@Override
					public EList<Feature> caseProvidesMember(
							ProvidesMember member) {
						return member.getFeatures();
					}
				});
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated NOT
	 */
	public EList<Feature> getRequires() {
		return flattenMembers(Feature.class, MyFilePackage.MODULE__REQUIRES,
				new MyFileSwitch<EList<Feature>>() {
					@Override
					public EList<Feature> caseRequiresMember(
							RequiresMember member) {
						return member.getFeatures();
					}
				});
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated NOT
	 */
	public EList<FileName> getSources() {
		return flattenMembers(FileName.class, MyFilePackage.MODULE__SOURCES,
				new MyFileSwitch<EList<FileName>>() {
					@Override
					public EList<FileName> caseSourceMember(SourceMember member) {
						return member.getFiles();
					}
				});
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated NOT
	 */
	public EList<FileName> getObjects() {
		return flattenMembers(FileName.class, MyFilePackage.MODULE__OBJECTS,
				new MyFileSwitch<EList<FileName>>() {
					@Override
					public EList<FileName> caseObjectMember(ObjectMember member) {
						return member.getFiles();
					}
				});
	}

	private <E> EList<E> flattenMembers(Class<E> clazz, int featureID,
			MyFileSwitch<EList<E>> visitor) {
		EList<E> elements = new EObjectEList<E>(clazz, this, featureID);
		for (Member member : getMembers()) {
			EList<E> memberElements = visitor.doSwitch(member);
			if (memberElements != null) {
				elements.addAll(memberElements);
			}
		}
		return elements;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@SuppressWarnings("unchecked")
	@Override
	public NotificationChain eInverseAdd(InternalEObject otherEnd,
			int featureID, NotificationChain msgs) {
		switch (featureID) {
		case MyFilePackage.MODULE__SUPER_TYPE:
			if (superType != null)
				msgs = ((InternalEObject) superType).eInverseRemove(this,
						MyFilePackage.MODULE__SUB_TYPES, Module.class, msgs);
			return basicSetSuperType((Module) otherEnd, msgs);
		case MyFilePackage.MODULE__SUB_TYPES:
			return ((InternalEList<InternalEObject>) (InternalEList<?>) getSubTypes())
					.basicAdd(otherEnd, msgs);
		case MyFilePackage.MODULE__MEMBERS:
			return ((InternalEList<InternalEObject>) (InternalEList<?>) getMembers())
					.basicAdd(otherEnd, msgs);
		}
		return super.eInverseAdd(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseRemove(InternalEObject otherEnd,
			int featureID, NotificationChain msgs) {
		switch (featureID) {
		case MyFilePackage.MODULE__SUPER_TYPE:
			return basicSetSuperType(null, msgs);
		case MyFilePackage.MODULE__SUB_TYPES:
			return ((InternalEList<?>) getSubTypes()).basicRemove(otherEnd,
					msgs);
		case MyFilePackage.MODULE__MEMBERS:
			return ((InternalEList<?>) getMembers())
					.basicRemove(otherEnd, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case MyFilePackage.MODULE__STATIC:
			return isStatic();
		case MyFilePackage.MODULE__ABSTRACT:
			return isAbstract();
		case MyFilePackage.MODULE__SUPER_TYPE:
			if (resolve)
				return getSuperType();
			return basicGetSuperType();
		case MyFilePackage.MODULE__SUB_TYPES:
			return getSubTypes();
		case MyFilePackage.MODULE__ALL_SUPER_TYPES:
			return getAllSuperTypes();
		case MyFilePackage.MODULE__ALL_SUB_TYPES:
			return getAllSubTypes();
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
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
		case MyFilePackage.MODULE__STATIC:
			setStatic((Boolean) newValue);
			return;
		case MyFilePackage.MODULE__ABSTRACT:
			setAbstract((Boolean) newValue);
			return;
		case MyFilePackage.MODULE__SUPER_TYPE:
			setSuperType((Module) newValue);
			return;
		case MyFilePackage.MODULE__SUB_TYPES:
			getSubTypes().clear();
			getSubTypes().addAll((Collection<? extends Module>) newValue);
			return;
		case MyFilePackage.MODULE__MEMBERS:
			getMembers().clear();
			getMembers().addAll((Collection<? extends Member>) newValue);
			return;
		case MyFilePackage.MODULE__DEPENDS:
			getDepends().clear();
			getDepends().addAll((Collection<? extends Module>) newValue);
			return;
		case MyFilePackage.MODULE__DEPENDENT:
			getDependent().clear();
			getDependent().addAll((Collection<? extends Module>) newValue);
			return;
		case MyFilePackage.MODULE__PROVIDES:
			getProvides().clear();
			getProvides().addAll((Collection<? extends Feature>) newValue);
			return;
		case MyFilePackage.MODULE__REQUIRES:
			getRequires().clear();
			getRequires().addAll((Collection<? extends Feature>) newValue);
			return;
		case MyFilePackage.MODULE__SOURCES:
			getSources().clear();
			getSources().addAll((Collection<? extends FileName>) newValue);
			return;
		case MyFilePackage.MODULE__OBJECTS:
			getObjects().clear();
			getObjects().addAll((Collection<? extends FileName>) newValue);
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
	public void eUnset(int featureID) {
		switch (featureID) {
		case MyFilePackage.MODULE__STATIC:
			setStatic(STATIC_EDEFAULT);
			return;
		case MyFilePackage.MODULE__ABSTRACT:
			setAbstract(ABSTRACT_EDEFAULT);
			return;
		case MyFilePackage.MODULE__SUPER_TYPE:
			setSuperType((Module) null);
			return;
		case MyFilePackage.MODULE__SUB_TYPES:
			getSubTypes().clear();
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
	public boolean eIsSet(int featureID) {
		switch (featureID) {
		case MyFilePackage.MODULE__STATIC:
			return static_ != STATIC_EDEFAULT;
		case MyFilePackage.MODULE__ABSTRACT:
			return abstract_ != ABSTRACT_EDEFAULT;
		case MyFilePackage.MODULE__SUPER_TYPE:
			return superType != null;
		case MyFilePackage.MODULE__SUB_TYPES:
			return subTypes != null && !subTypes.isEmpty();
		case MyFilePackage.MODULE__ALL_SUPER_TYPES:
			return !getAllSuperTypes().isEmpty();
		case MyFilePackage.MODULE__ALL_SUB_TYPES:
			return !getAllSubTypes().isEmpty();
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
	public String toString() {
		if (eIsProxy())
			return super.toString();

		StringBuffer result = new StringBuffer(super.toString());
		result.append(" (static: ");
		result.append(static_);
		result.append(", abstract: ");
		result.append(abstract_);
		result.append(')');
		return result.toString();
	}

} //ModuleImpl
