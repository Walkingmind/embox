/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl.impl;

import java.util.Collection;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.util.EDataTypeEList;

import org.embuild.emdsl.emDsl.EmDslPackage;
import org.embuild.emdsl.emDsl.SourceFeature;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Source Feature</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.embuild.emdsl.emDsl.impl.SourceFeatureImpl#getFilenames <em>Filenames</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class SourceFeatureImpl extends FeatureImpl implements SourceFeature
{
  /**
   * The cached value of the '{@link #getFilenames() <em>Filenames</em>}' attribute list.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see #getFilenames()
   * @generated
   * @ordered
   */
  protected EList<String> filenames;

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  protected SourceFeatureImpl()
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
    return EmDslPackage.Literals.SOURCE_FEATURE;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public EList<String> getFilenames()
  {
    if (filenames == null)
    {
      filenames = new EDataTypeEList<String>(String.class, this, EmDslPackage.SOURCE_FEATURE__FILENAMES);
    }
    return filenames;
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
      case EmDslPackage.SOURCE_FEATURE__FILENAMES:
        return getFilenames();
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
      case EmDslPackage.SOURCE_FEATURE__FILENAMES:
        getFilenames().clear();
        getFilenames().addAll((Collection<? extends String>)newValue);
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
      case EmDslPackage.SOURCE_FEATURE__FILENAMES:
        getFilenames().clear();
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
      case EmDslPackage.SOURCE_FEATURE__FILENAMES:
        return filenames != null && !filenames.isEmpty();
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
    result.append(" (filenames: ");
    result.append(filenames);
    result.append(')');
    return result.toString();
  }

} //SourceFeatureImpl
