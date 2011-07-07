/**
 * <copyright>
 * </copyright>
 *
 */
package org.embuild.emdsl.emDsl;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see org.embuild.emdsl.emDsl.EmDslFactory
 * @model kind="package"
 * @generated
 */
public interface EmDslPackage extends EPackage
{
  /**
   * The package name.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  String eNAME = "emDsl";

  /**
   * The package namespace URI.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  String eNS_URI = "http://www.embuild.org/emdsl/EmDsl";

  /**
   * The package namespace name.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  String eNS_PREFIX = "emDsl";

  /**
   * The singleton instance of the package.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  EmDslPackage eINSTANCE = org.embuild.emdsl.emDsl.impl.EmDslPackageImpl.init();

  /**
   * The meta object id for the '{@link org.embuild.emdsl.emDsl.impl.ModelImpl <em>Model</em>}' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see org.embuild.emdsl.emDsl.impl.ModelImpl
   * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getModel()
   * @generated
   */
  int MODEL = 0;

  /**
   * The feature id for the '<em><b>Elements</b></em>' containment reference list.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODEL__ELEMENTS = 0;

  /**
   * The number of structural features of the '<em>Model</em>' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODEL_FEATURE_COUNT = 1;

  /**
   * The meta object id for the '{@link org.embuild.emdsl.emDsl.impl.EntityImpl <em>Entity</em>}' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see org.embuild.emdsl.emDsl.impl.EntityImpl
   * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getEntity()
   * @generated
   */
  int ENTITY = 1;

  /**
   * The number of structural features of the '<em>Entity</em>' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int ENTITY_FEATURE_COUNT = 0;

  /**
   * The meta object id for the '{@link org.embuild.emdsl.emDsl.impl.ModuleImpl <em>Module</em>}' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see org.embuild.emdsl.emDsl.impl.ModuleImpl
   * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getModule()
   * @generated
   */
  int MODULE = 3;

  /**
   * The feature id for the '<em><b>Name</b></em>' attribute.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODULE__NAME = ENTITY_FEATURE_COUNT + 0;

  /**
   * The feature id for the '<em><b>Super Type</b></em>' reference.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODULE__SUPER_TYPE = ENTITY_FEATURE_COUNT + 1;

  /**
   * The feature id for the '<em><b>Features</b></em>' containment reference list.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODULE__FEATURES = ENTITY_FEATURE_COUNT + 2;

  /**
   * The number of structural features of the '<em>Module</em>' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODULE_FEATURE_COUNT = ENTITY_FEATURE_COUNT + 3;

  /**
   * The meta object id for the '{@link org.embuild.emdsl.emDsl.impl.ModifierImpl <em>Modifier</em>}' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see org.embuild.emdsl.emDsl.impl.ModifierImpl
   * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getModifier()
   * @generated
   */
  int MODIFIER = 2;

  /**
   * The feature id for the '<em><b>Name</b></em>' attribute.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODIFIER__NAME = MODULE__NAME;

  /**
   * The feature id for the '<em><b>Super Type</b></em>' reference.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODIFIER__SUPER_TYPE = MODULE__SUPER_TYPE;

  /**
   * The feature id for the '<em><b>Features</b></em>' containment reference list.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODIFIER__FEATURES = MODULE__FEATURES;

  /**
   * The feature id for the '<em><b>Abstract</b></em>' attribute.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODIFIER__ABSTRACT = MODULE_FEATURE_COUNT + 0;

  /**
   * The number of structural features of the '<em>Modifier</em>' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int MODIFIER_FEATURE_COUNT = MODULE_FEATURE_COUNT + 1;

  /**
   * The meta object id for the '{@link org.embuild.emdsl.emDsl.impl.FeatureImpl <em>Feature</em>}' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see org.embuild.emdsl.emDsl.impl.FeatureImpl
   * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getFeature()
   * @generated
   */
  int FEATURE = 4;

  /**
   * The number of structural features of the '<em>Feature</em>' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int FEATURE_FEATURE_COUNT = 0;

  /**
   * The meta object id for the '{@link org.embuild.emdsl.emDsl.impl.SourceFeatureImpl <em>Source Feature</em>}' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see org.embuild.emdsl.emDsl.impl.SourceFeatureImpl
   * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getSourceFeature()
   * @generated
   */
  int SOURCE_FEATURE = 5;

  /**
   * The feature id for the '<em><b>Filenames</b></em>' attribute list.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int SOURCE_FEATURE__FILENAMES = FEATURE_FEATURE_COUNT + 0;

  /**
   * The number of structural features of the '<em>Source Feature</em>' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int SOURCE_FEATURE_FEATURE_COUNT = FEATURE_FEATURE_COUNT + 1;

  /**
   * The meta object id for the '{@link org.embuild.emdsl.emDsl.impl.DependFeatureImpl <em>Depend Feature</em>}' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @see org.embuild.emdsl.emDsl.impl.DependFeatureImpl
   * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getDependFeature()
   * @generated
   */
  int DEPEND_FEATURE = 6;

  /**
   * The feature id for the '<em><b>Modules</b></em>' reference list.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int DEPEND_FEATURE__MODULES = FEATURE_FEATURE_COUNT + 0;

  /**
   * The number of structural features of the '<em>Depend Feature</em>' class.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   * @ordered
   */
  int DEPEND_FEATURE_FEATURE_COUNT = FEATURE_FEATURE_COUNT + 1;


  /**
   * Returns the meta object for class '{@link org.embuild.emdsl.emDsl.Model <em>Model</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for class '<em>Model</em>'.
   * @see org.embuild.emdsl.emDsl.Model
   * @generated
   */
  EClass getModel();

  /**
   * Returns the meta object for the containment reference list '{@link org.embuild.emdsl.emDsl.Model#getElements <em>Elements</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for the containment reference list '<em>Elements</em>'.
   * @see org.embuild.emdsl.emDsl.Model#getElements()
   * @see #getModel()
   * @generated
   */
  EReference getModel_Elements();

  /**
   * Returns the meta object for class '{@link org.embuild.emdsl.emDsl.Entity <em>Entity</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for class '<em>Entity</em>'.
   * @see org.embuild.emdsl.emDsl.Entity
   * @generated
   */
  EClass getEntity();

  /**
   * Returns the meta object for class '{@link org.embuild.emdsl.emDsl.Modifier <em>Modifier</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for class '<em>Modifier</em>'.
   * @see org.embuild.emdsl.emDsl.Modifier
   * @generated
   */
  EClass getModifier();

  /**
   * Returns the meta object for the attribute '{@link org.embuild.emdsl.emDsl.Modifier#isAbstract <em>Abstract</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for the attribute '<em>Abstract</em>'.
   * @see org.embuild.emdsl.emDsl.Modifier#isAbstract()
   * @see #getModifier()
   * @generated
   */
  EAttribute getModifier_Abstract();

  /**
   * Returns the meta object for class '{@link org.embuild.emdsl.emDsl.Module <em>Module</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for class '<em>Module</em>'.
   * @see org.embuild.emdsl.emDsl.Module
   * @generated
   */
  EClass getModule();

  /**
   * Returns the meta object for the attribute '{@link org.embuild.emdsl.emDsl.Module#getName <em>Name</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for the attribute '<em>Name</em>'.
   * @see org.embuild.emdsl.emDsl.Module#getName()
   * @see #getModule()
   * @generated
   */
  EAttribute getModule_Name();

  /**
   * Returns the meta object for the reference '{@link org.embuild.emdsl.emDsl.Module#getSuperType <em>Super Type</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for the reference '<em>Super Type</em>'.
   * @see org.embuild.emdsl.emDsl.Module#getSuperType()
   * @see #getModule()
   * @generated
   */
  EReference getModule_SuperType();

  /**
   * Returns the meta object for the containment reference list '{@link org.embuild.emdsl.emDsl.Module#getFeatures <em>Features</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for the containment reference list '<em>Features</em>'.
   * @see org.embuild.emdsl.emDsl.Module#getFeatures()
   * @see #getModule()
   * @generated
   */
  EReference getModule_Features();

  /**
   * Returns the meta object for class '{@link org.embuild.emdsl.emDsl.Feature <em>Feature</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for class '<em>Feature</em>'.
   * @see org.embuild.emdsl.emDsl.Feature
   * @generated
   */
  EClass getFeature();

  /**
   * Returns the meta object for class '{@link org.embuild.emdsl.emDsl.SourceFeature <em>Source Feature</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for class '<em>Source Feature</em>'.
   * @see org.embuild.emdsl.emDsl.SourceFeature
   * @generated
   */
  EClass getSourceFeature();

  /**
   * Returns the meta object for the attribute list '{@link org.embuild.emdsl.emDsl.SourceFeature#getFilenames <em>Filenames</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for the attribute list '<em>Filenames</em>'.
   * @see org.embuild.emdsl.emDsl.SourceFeature#getFilenames()
   * @see #getSourceFeature()
   * @generated
   */
  EAttribute getSourceFeature_Filenames();

  /**
   * Returns the meta object for class '{@link org.embuild.emdsl.emDsl.DependFeature <em>Depend Feature</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for class '<em>Depend Feature</em>'.
   * @see org.embuild.emdsl.emDsl.DependFeature
   * @generated
   */
  EClass getDependFeature();

  /**
   * Returns the meta object for the reference list '{@link org.embuild.emdsl.emDsl.DependFeature#getModules <em>Modules</em>}'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the meta object for the reference list '<em>Modules</em>'.
   * @see org.embuild.emdsl.emDsl.DependFeature#getModules()
   * @see #getDependFeature()
   * @generated
   */
  EReference getDependFeature_Modules();

  /**
   * Returns the factory that creates the instances of the model.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the factory that creates the instances of the model.
   * @generated
   */
  EmDslFactory getEmDslFactory();

  /**
   * <!-- begin-user-doc -->
   * Defines literals for the meta objects that represent
   * <ul>
   *   <li>each class,</li>
   *   <li>each feature of each class,</li>
   *   <li>each enum,</li>
   *   <li>and each data type</li>
   * </ul>
   * <!-- end-user-doc -->
   * @generated
   */
  interface Literals
  {
    /**
     * The meta object literal for the '{@link org.embuild.emdsl.emDsl.impl.ModelImpl <em>Model</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.embuild.emdsl.emDsl.impl.ModelImpl
     * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getModel()
     * @generated
     */
    EClass MODEL = eINSTANCE.getModel();

    /**
     * The meta object literal for the '<em><b>Elements</b></em>' containment reference list feature.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    EReference MODEL__ELEMENTS = eINSTANCE.getModel_Elements();

    /**
     * The meta object literal for the '{@link org.embuild.emdsl.emDsl.impl.EntityImpl <em>Entity</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.embuild.emdsl.emDsl.impl.EntityImpl
     * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getEntity()
     * @generated
     */
    EClass ENTITY = eINSTANCE.getEntity();

    /**
     * The meta object literal for the '{@link org.embuild.emdsl.emDsl.impl.ModifierImpl <em>Modifier</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.embuild.emdsl.emDsl.impl.ModifierImpl
     * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getModifier()
     * @generated
     */
    EClass MODIFIER = eINSTANCE.getModifier();

    /**
     * The meta object literal for the '<em><b>Abstract</b></em>' attribute feature.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    EAttribute MODIFIER__ABSTRACT = eINSTANCE.getModifier_Abstract();

    /**
     * The meta object literal for the '{@link org.embuild.emdsl.emDsl.impl.ModuleImpl <em>Module</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.embuild.emdsl.emDsl.impl.ModuleImpl
     * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getModule()
     * @generated
     */
    EClass MODULE = eINSTANCE.getModule();

    /**
     * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    EAttribute MODULE__NAME = eINSTANCE.getModule_Name();

    /**
     * The meta object literal for the '<em><b>Super Type</b></em>' reference feature.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    EReference MODULE__SUPER_TYPE = eINSTANCE.getModule_SuperType();

    /**
     * The meta object literal for the '<em><b>Features</b></em>' containment reference list feature.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    EReference MODULE__FEATURES = eINSTANCE.getModule_Features();

    /**
     * The meta object literal for the '{@link org.embuild.emdsl.emDsl.impl.FeatureImpl <em>Feature</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.embuild.emdsl.emDsl.impl.FeatureImpl
     * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getFeature()
     * @generated
     */
    EClass FEATURE = eINSTANCE.getFeature();

    /**
     * The meta object literal for the '{@link org.embuild.emdsl.emDsl.impl.SourceFeatureImpl <em>Source Feature</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.embuild.emdsl.emDsl.impl.SourceFeatureImpl
     * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getSourceFeature()
     * @generated
     */
    EClass SOURCE_FEATURE = eINSTANCE.getSourceFeature();

    /**
     * The meta object literal for the '<em><b>Filenames</b></em>' attribute list feature.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    EAttribute SOURCE_FEATURE__FILENAMES = eINSTANCE.getSourceFeature_Filenames();

    /**
     * The meta object literal for the '{@link org.embuild.emdsl.emDsl.impl.DependFeatureImpl <em>Depend Feature</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.embuild.emdsl.emDsl.impl.DependFeatureImpl
     * @see org.embuild.emdsl.emDsl.impl.EmDslPackageImpl#getDependFeature()
     * @generated
     */
    EClass DEPEND_FEATURE = eINSTANCE.getDependFeature();

    /**
     * The meta object literal for the '<em><b>Modules</b></em>' reference list feature.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    EReference DEPEND_FEATURE__MODULES = eINSTANCE.getDependFeature_Modules();

  }

} //EmDslPackage
