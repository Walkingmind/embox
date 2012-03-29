/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile.impl;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import org.mybuild.myfile.BooleanLiteral;
import org.mybuild.myfile.MyFilePackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Boolean Literal</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.mybuild.myfile.impl.BooleanLiteralImpl#isIsTrue <em>Is True</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class BooleanLiteralImpl extends ValueImpl implements BooleanLiteral {
	/**
	 * The default value of the '{@link #isIsTrue() <em>Is True</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isIsTrue()
	 * @generated
	 * @ordered
	 */
	protected static final boolean IS_TRUE_EDEFAULT = false;

	/**
	 * The cached value of the '{@link #isIsTrue() <em>Is True</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isIsTrue()
	 * @generated
	 * @ordered
	 */
	protected boolean isTrue = IS_TRUE_EDEFAULT;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected BooleanLiteralImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return MyFilePackage.Literals.BOOLEAN_LITERAL;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isIsTrue() {
		return isTrue;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setIsTrue(boolean newIsTrue) {
		boolean oldIsTrue = isTrue;
		isTrue = newIsTrue;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET,
					MyFilePackage.BOOLEAN_LITERAL__IS_TRUE, oldIsTrue, isTrue));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case MyFilePackage.BOOLEAN_LITERAL__IS_TRUE:
			return isIsTrue();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
		case MyFilePackage.BOOLEAN_LITERAL__IS_TRUE:
			setIsTrue((Boolean) newValue);
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
		case MyFilePackage.BOOLEAN_LITERAL__IS_TRUE:
			setIsTrue(IS_TRUE_EDEFAULT);
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
		case MyFilePackage.BOOLEAN_LITERAL__IS_TRUE:
			return isTrue != IS_TRUE_EDEFAULT;
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
		result.append(" (isTrue: ");
		result.append(isTrue);
		result.append(')');
		return result.toString();
	}

} //BooleanLiteralImpl
