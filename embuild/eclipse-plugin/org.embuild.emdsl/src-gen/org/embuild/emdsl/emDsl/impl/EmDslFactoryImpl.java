/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl.impl;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

import org.embuild.emdsl.emDsl.*;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class EmDslFactoryImpl extends EFactoryImpl implements EmDslFactory
{
  /**
   * Creates the default factory implementation.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public static EmDslFactory init()
  {
    try
    {
      EmDslFactory theEmDslFactory = (EmDslFactory)EPackage.Registry.INSTANCE.getEFactory("http://www.embuild.org/emdsl/EmDsl"); 
      if (theEmDslFactory != null)
      {
        return theEmDslFactory;
      }
    }
    catch (Exception exception)
    {
      EcorePlugin.INSTANCE.log(exception);
    }
    return new EmDslFactoryImpl();
  }

  /**
   * Creates an instance of the factory.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public EmDslFactoryImpl()
  {
    super();
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  @Override
  public EObject create(EClass eClass)
  {
    switch (eClass.getClassifierID())
    {
      case EmDslPackage.MODEL: return createModel();
      case EmDslPackage.ENTITY: return createEntity();
      case EmDslPackage.MODIFIER: return createModifier();
      case EmDslPackage.MODULE: return createModule();
      case EmDslPackage.FEATURE: return createFeature();
      case EmDslPackage.SOURCE_FEATURE: return createSourceFeature();
      case EmDslPackage.DEPEND_FEATURE: return createDependFeature();
      default:
        throw new IllegalArgumentException("The class '" + eClass.getName() + "' is not a valid classifier");
    }
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public Model createModel()
  {
    ModelImpl model = new ModelImpl();
    return model;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public Entity createEntity()
  {
    EntityImpl entity = new EntityImpl();
    return entity;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public Modifier createModifier()
  {
    ModifierImpl modifier = new ModifierImpl();
    return modifier;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public Module createModule()
  {
    ModuleImpl module = new ModuleImpl();
    return module;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public Feature createFeature()
  {
    FeatureImpl feature = new FeatureImpl();
    return feature;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public SourceFeature createSourceFeature()
  {
    SourceFeatureImpl sourceFeature = new SourceFeatureImpl();
    return sourceFeature;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public DependFeature createDependFeature()
  {
    DependFeatureImpl dependFeature = new DependFeatureImpl();
    return dependFeature;
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  public EmDslPackage getEmDslPackage()
  {
    return (EmDslPackage)getEPackage();
  }

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @deprecated
   * @generated
   */
  @Deprecated
  public static EmDslPackage getPackage()
  {
    return EmDslPackage.eINSTANCE;
  }

} //EmDslFactoryImpl
