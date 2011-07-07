/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl.impl;

import java.util.Collection;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.util.EObjectResolvingEList;

import org.embuild.emdsl.emDsl.DependFeature;
import org.embuild.emdsl.emDsl.EmDslPackage;
import org.embuild.emdsl.emDsl.Module;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Depend Feature</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.embuild.emdsl.emDsl.impl.DependFeatureImpl#getModules <em>Modules</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class DependFeatureImpl extends FeatureImpl implements DependFeature
{
  /**
   * The cached value of the '{@link #getModules() <em>Modules</em>}' reference list.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see #getModules()
   * @generated
   * @ordered
   */
  protected EList<Module> modules;

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  protected DependFeatureImpl()
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
    return EmDslPackage.Literals.DEPEND_FEATURE;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public EList<Module> getModules()
  {
    if (modules == null)
    {
      modules = new EObjectResolvingEList<Module>(Module.class, this, EmDslPackage.DEPEND_FEATURE__MODULES);
    }
    return modules;
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
      case EmDslPackage.DEPEND_FEATURE__MODULES:
        return getModules();
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
      case EmDslPackage.DEPEND_FEATURE__MODULES:
        getModules().clear();
        getModules().addAll((Collection<? extends Module>)newValue);
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
      case EmDslPackage.DEPEND_FEATURE__MODULES:
        getModules().clear();
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
      case EmDslPackage.DEPEND_FEATURE__MODULES:
        return modules != null && !modules.isEmpty();
    }
    return super.eIsSet(featureID);
  }

} //DependFeatureImpl
