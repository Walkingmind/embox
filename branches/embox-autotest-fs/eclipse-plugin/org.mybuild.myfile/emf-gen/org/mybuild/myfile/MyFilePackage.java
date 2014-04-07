/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile;

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
 * @see org.mybuild.myfile.MyFileFactory
 * @model kind="package"
 * @generated
 */
public interface MyFilePackage extends EPackage {
	/**
	 * The package name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNAME = "myfile";

	/**
	 * The package namespace URI.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_URI = "http://www.mybuild.org/MyFile";

	/**
	 * The package namespace name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_PREFIX = "MyFile";

	/**
	 * The singleton instance of the package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	MyFilePackage eINSTANCE = org.mybuild.myfile.impl.MyFilePackageImpl.init();

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.ModelImpl <em>Model</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.ModelImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getModel()
	 * @generated
	 */
	int MODEL = 0;

	/**
	 * The feature id for the '<em><b>Package</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODEL__PACKAGE = 0;

	/**
	 * The feature id for the '<em><b>Imports</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODEL__IMPORTS = 1;

	/**
	 * The feature id for the '<em><b>Types</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODEL__TYPES = 2;

	/**
	 * The number of structural features of the '<em>Model</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODEL_FEATURE_COUNT = 3;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.PackageImpl <em>Package</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.PackageImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getPackage()
	 * @generated
	 */
	int PACKAGE = 1;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PACKAGE__NAME = 0;

	/**
	 * The number of structural features of the '<em>Package</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PACKAGE_FEATURE_COUNT = 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.ImportImpl <em>Import</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.ImportImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getImport()
	 * @generated
	 */
	int IMPORT = 2;

	/**
	 * The feature id for the '<em><b>Imported Namespace</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int IMPORT__IMPORTED_NAMESPACE = 0;

	/**
	 * The number of structural features of the '<em>Import</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int IMPORT_FEATURE_COUNT = 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.NamedImpl <em>Named</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.NamedImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getNamed()
	 * @generated
	 */
	int NAMED = 31;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NAMED__NAME = 0;

	/**
	 * The number of structural features of the '<em>Named</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NAMED_FEATURE_COUNT = 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.TypeImpl <em>Type</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.TypeImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getType()
	 * @generated
	 */
	int TYPE = 3;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE__NAME = NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE__ANNOTATIONS = NAMED_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Type</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE_FEATURE_COUNT = NAMED_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.AnnotationTypeImpl <em>Annotation Type</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.AnnotationTypeImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAnnotationType()
	 * @generated
	 */
	int ANNOTATION_TYPE = 4;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION_TYPE__NAME = TYPE__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION_TYPE__ANNOTATIONS = TYPE__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Elements</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION_TYPE__ELEMENTS = TYPE_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Annotation Type</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION_TYPE_FEATURE_COUNT = TYPE_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.AnnotationImpl <em>Annotation</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.AnnotationImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAnnotation()
	 * @generated
	 */
	int ANNOTATION = 5;

	/**
	 * The feature id for the '<em><b>Type</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION__TYPE = 0;

	/**
	 * The feature id for the '<em><b>Target</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION__TARGET = 1;

	/**
	 * The feature id for the '<em><b>Elements</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION__ELEMENTS = 2;

	/**
	 * The feature id for the '<em><b>Single Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION__SINGLE_VALUE = 3;

	/**
	 * The number of structural features of the '<em>Annotation</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION_FEATURE_COUNT = 4;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.AnnotationTargetImpl <em>Annotation Target</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.AnnotationTargetImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAnnotationTarget()
	 * @generated
	 */
	int ANNOTATION_TARGET = 6;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION_TARGET__ANNOTATIONS = 0;

	/**
	 * The number of structural features of the '<em>Annotation Target</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ANNOTATION_TARGET_FEATURE_COUNT = 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.InterfaceImpl <em>Interface</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.InterfaceImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getInterface()
	 * @generated
	 */
	int INTERFACE = 7;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int INTERFACE__NAME = TYPE__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int INTERFACE__ANNOTATIONS = TYPE__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Super Type</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int INTERFACE__SUPER_TYPE = TYPE_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Features</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int INTERFACE__FEATURES = TYPE_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Interface</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int INTERFACE_FEATURE_COUNT = TYPE_FEATURE_COUNT + 2;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.FeatureImpl <em>Feature</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.FeatureImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getFeature()
	 * @generated
	 */
	int FEATURE = 8;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE__NAME = TYPE__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE__ANNOTATIONS = TYPE__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Super Type</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE__SUPER_TYPE = TYPE_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Feature</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FEATURE_FEATURE_COUNT = TYPE_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.ModuleImpl <em>Module</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.ModuleImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getModule()
	 * @generated
	 */
	int MODULE = 9;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__NAME = TYPE__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__ANNOTATIONS = TYPE__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Static</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__STATIC = TYPE_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Abstract</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__ABSTRACT = TYPE_FEATURE_COUNT + 1;

	/**
	 * The feature id for the '<em><b>Super Type</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__SUPER_TYPE = TYPE_FEATURE_COUNT + 2;

	/**
	 * The feature id for the '<em><b>Sub Types</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__SUB_TYPES = TYPE_FEATURE_COUNT + 3;

	/**
	 * The feature id for the '<em><b>All Super Types</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__ALL_SUPER_TYPES = TYPE_FEATURE_COUNT + 4;

	/**
	 * The feature id for the '<em><b>All Sub Types</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__ALL_SUB_TYPES = TYPE_FEATURE_COUNT + 5;

	/**
	 * The feature id for the '<em><b>Members</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__MEMBERS = TYPE_FEATURE_COUNT + 6;

	/**
	 * The feature id for the '<em><b>Depends</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__DEPENDS = TYPE_FEATURE_COUNT + 7;

	/**
	 * The feature id for the '<em><b>Dependent</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__DEPENDENT = TYPE_FEATURE_COUNT + 8;

	/**
	 * The feature id for the '<em><b>Provides</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__PROVIDES = TYPE_FEATURE_COUNT + 9;

	/**
	 * The feature id for the '<em><b>Requires</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__REQUIRES = TYPE_FEATURE_COUNT + 10;

	/**
	 * The feature id for the '<em><b>Sources</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__SOURCES = TYPE_FEATURE_COUNT + 11;

	/**
	 * The feature id for the '<em><b>Objects</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__OBJECTS = TYPE_FEATURE_COUNT + 12;

	/**
	 * The feature id for the '<em><b>Options</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE__OPTIONS = TYPE_FEATURE_COUNT + 13;

	/**
	 * The number of structural features of the '<em>Module</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MODULE_FEATURE_COUNT = TYPE_FEATURE_COUNT + 14;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.MemberImpl <em>Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.MemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getMember()
	 * @generated
	 */
	int MEMBER = 10;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MEMBER__ANNOTATIONS = ANNOTATION_TARGET__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MEMBER__CONTAINING_MODULE = ANNOTATION_TARGET_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MEMBER_FEATURE_COUNT = ANNOTATION_TARGET_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.DependsMemberImpl <em>Depends Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.DependsMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getDependsMember()
	 * @generated
	 */
	int DEPENDS_MEMBER = 11;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DEPENDS_MEMBER__ANNOTATIONS = MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DEPENDS_MEMBER__CONTAINING_MODULE = MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Modules</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DEPENDS_MEMBER__MODULES = MEMBER_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Depends Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DEPENDS_MEMBER_FEATURE_COUNT = MEMBER_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.AbstractFeatureListMemberImpl <em>Abstract Feature List Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.AbstractFeatureListMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAbstractFeatureListMember()
	 * @generated
	 */
	int ABSTRACT_FEATURE_LIST_MEMBER = 12;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FEATURE_LIST_MEMBER__ANNOTATIONS = MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FEATURE_LIST_MEMBER__CONTAINING_MODULE = MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Features</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FEATURE_LIST_MEMBER__FEATURES = MEMBER_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Abstract Feature List Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FEATURE_LIST_MEMBER_FEATURE_COUNT = MEMBER_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.RequiresMemberImpl <em>Requires Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.RequiresMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getRequiresMember()
	 * @generated
	 */
	int REQUIRES_MEMBER = 13;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int REQUIRES_MEMBER__ANNOTATIONS = ABSTRACT_FEATURE_LIST_MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int REQUIRES_MEMBER__CONTAINING_MODULE = ABSTRACT_FEATURE_LIST_MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Features</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int REQUIRES_MEMBER__FEATURES = ABSTRACT_FEATURE_LIST_MEMBER__FEATURES;

	/**
	 * The number of structural features of the '<em>Requires Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int REQUIRES_MEMBER_FEATURE_COUNT = ABSTRACT_FEATURE_LIST_MEMBER_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.ProvidesMemberImpl <em>Provides Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.ProvidesMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getProvidesMember()
	 * @generated
	 */
	int PROVIDES_MEMBER = 14;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROVIDES_MEMBER__ANNOTATIONS = ABSTRACT_FEATURE_LIST_MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROVIDES_MEMBER__CONTAINING_MODULE = ABSTRACT_FEATURE_LIST_MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Features</b></em>' reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROVIDES_MEMBER__FEATURES = ABSTRACT_FEATURE_LIST_MEMBER__FEATURES;

	/**
	 * The number of structural features of the '<em>Provides Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROVIDES_MEMBER_FEATURE_COUNT = ABSTRACT_FEATURE_LIST_MEMBER_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.AbstractFileListMemberImpl <em>Abstract File List Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.AbstractFileListMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAbstractFileListMember()
	 * @generated
	 */
	int ABSTRACT_FILE_LIST_MEMBER = 15;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FILE_LIST_MEMBER__ANNOTATIONS = MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FILE_LIST_MEMBER__CONTAINING_MODULE = MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Files</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FILE_LIST_MEMBER__FILES = MEMBER_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Abstract File List Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ABSTRACT_FILE_LIST_MEMBER_FEATURE_COUNT = MEMBER_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.SourceMemberImpl <em>Source Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.SourceMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getSourceMember()
	 * @generated
	 */
	int SOURCE_MEMBER = 16;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SOURCE_MEMBER__ANNOTATIONS = ABSTRACT_FILE_LIST_MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SOURCE_MEMBER__CONTAINING_MODULE = ABSTRACT_FILE_LIST_MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Files</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SOURCE_MEMBER__FILES = ABSTRACT_FILE_LIST_MEMBER__FILES;

	/**
	 * The number of structural features of the '<em>Source Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SOURCE_MEMBER_FEATURE_COUNT = ABSTRACT_FILE_LIST_MEMBER_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.ObjectMemberImpl <em>Object Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.ObjectMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getObjectMember()
	 * @generated
	 */
	int OBJECT_MEMBER = 17;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OBJECT_MEMBER__ANNOTATIONS = ABSTRACT_FILE_LIST_MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OBJECT_MEMBER__CONTAINING_MODULE = ABSTRACT_FILE_LIST_MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Files</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OBJECT_MEMBER__FILES = ABSTRACT_FILE_LIST_MEMBER__FILES;

	/**
	 * The number of structural features of the '<em>Object Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OBJECT_MEMBER_FEATURE_COUNT = ABSTRACT_FILE_LIST_MEMBER_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.FileNameImpl <em>File Name</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.FileNameImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getFileName()
	 * @generated
	 */
	int FILE_NAME = 18;

	/**
	 * The feature id for the '<em><b>Value</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FILE_NAME__VALUE = 0;

	/**
	 * The number of structural features of the '<em>File Name</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FILE_NAME_FEATURE_COUNT = 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.OptionMemberImpl <em>Option Member</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.OptionMemberImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getOptionMember()
	 * @generated
	 */
	int OPTION_MEMBER = 19;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OPTION_MEMBER__ANNOTATIONS = MEMBER__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Containing Module</b></em>' container reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OPTION_MEMBER__CONTAINING_MODULE = MEMBER__CONTAINING_MODULE;

	/**
	 * The feature id for the '<em><b>Property</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OPTION_MEMBER__PROPERTY = MEMBER_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Option Member</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int OPTION_MEMBER_FEATURE_COUNT = MEMBER_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.PropertyImpl <em>Property</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.PropertyImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getProperty()
	 * @generated
	 */
	int PROPERTY = 20;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROPERTY__NAME = NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROPERTY__ANNOTATIONS = NAMED_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Default Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROPERTY__DEFAULT_VALUE = NAMED_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Property</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROPERTY_FEATURE_COUNT = NAMED_FEATURE_COUNT + 2;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.StringPropertyImpl <em>String Property</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.StringPropertyImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getStringProperty()
	 * @generated
	 */
	int STRING_PROPERTY = 21;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRING_PROPERTY__NAME = PROPERTY__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRING_PROPERTY__ANNOTATIONS = PROPERTY__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Default Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRING_PROPERTY__DEFAULT_VALUE = PROPERTY__DEFAULT_VALUE;

	/**
	 * The number of structural features of the '<em>String Property</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRING_PROPERTY_FEATURE_COUNT = PROPERTY_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.NumberPropertyImpl <em>Number Property</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.NumberPropertyImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getNumberProperty()
	 * @generated
	 */
	int NUMBER_PROPERTY = 22;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NUMBER_PROPERTY__NAME = PROPERTY__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NUMBER_PROPERTY__ANNOTATIONS = PROPERTY__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Default Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NUMBER_PROPERTY__DEFAULT_VALUE = PROPERTY__DEFAULT_VALUE;

	/**
	 * The number of structural features of the '<em>Number Property</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NUMBER_PROPERTY_FEATURE_COUNT = PROPERTY_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.BooleanPropertyImpl <em>Boolean Property</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.BooleanPropertyImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getBooleanProperty()
	 * @generated
	 */
	int BOOLEAN_PROPERTY = 23;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BOOLEAN_PROPERTY__NAME = PROPERTY__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BOOLEAN_PROPERTY__ANNOTATIONS = PROPERTY__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Default Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BOOLEAN_PROPERTY__DEFAULT_VALUE = PROPERTY__DEFAULT_VALUE;

	/**
	 * The number of structural features of the '<em>Boolean Property</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BOOLEAN_PROPERTY_FEATURE_COUNT = PROPERTY_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.TypePropertyImpl <em>Type Property</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.TypePropertyImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getTypeProperty()
	 * @generated
	 */
	int TYPE_PROPERTY = 24;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE_PROPERTY__NAME = PROPERTY__NAME;

	/**
	 * The feature id for the '<em><b>Annotations</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE_PROPERTY__ANNOTATIONS = PROPERTY__ANNOTATIONS;

	/**
	 * The feature id for the '<em><b>Default Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE_PROPERTY__DEFAULT_VALUE = PROPERTY__DEFAULT_VALUE;

	/**
	 * The number of structural features of the '<em>Type Property</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE_PROPERTY_FEATURE_COUNT = PROPERTY_FEATURE_COUNT + 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.ValueImpl <em>Value</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.ValueImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getValue()
	 * @generated
	 */
	int VALUE = 25;

	/**
	 * The number of structural features of the '<em>Value</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int VALUE_FEATURE_COUNT = 0;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.StringLiteralImpl <em>String Literal</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.StringLiteralImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getStringLiteral()
	 * @generated
	 */
	int STRING_LITERAL = 26;

	/**
	 * The feature id for the '<em><b>Value</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRING_LITERAL__VALUE = VALUE_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>String Literal</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int STRING_LITERAL_FEATURE_COUNT = VALUE_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.NumberLiteralImpl <em>Number Literal</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.NumberLiteralImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getNumberLiteral()
	 * @generated
	 */
	int NUMBER_LITERAL = 27;

	/**
	 * The feature id for the '<em><b>Value</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NUMBER_LITERAL__VALUE = VALUE_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Number Literal</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int NUMBER_LITERAL_FEATURE_COUNT = VALUE_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.BooleanLiteralImpl <em>Boolean Literal</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.BooleanLiteralImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getBooleanLiteral()
	 * @generated
	 */
	int BOOLEAN_LITERAL = 28;

	/**
	 * The feature id for the '<em><b>Is True</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BOOLEAN_LITERAL__IS_TRUE = VALUE_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Boolean Literal</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int BOOLEAN_LITERAL_FEATURE_COUNT = VALUE_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.TypeLiteralImpl <em>Type Literal</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.TypeLiteralImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getTypeLiteral()
	 * @generated
	 */
	int TYPE_LITERAL = 29;

	/**
	 * The feature id for the '<em><b>Value</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE_LITERAL__VALUE = VALUE_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Type Literal</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int TYPE_LITERAL_FEATURE_COUNT = VALUE_FEATURE_COUNT + 1;

	/**
	 * The meta object id for the '{@link org.mybuild.myfile.impl.PropertyValueBindingImpl <em>Property Value Binding</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see org.mybuild.myfile.impl.PropertyValueBindingImpl
	 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getPropertyValueBinding()
	 * @generated
	 */
	int PROPERTY_VALUE_BINDING = 30;

	/**
	 * The feature id for the '<em><b>Property</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROPERTY_VALUE_BINDING__PROPERTY = 0;

	/**
	 * The feature id for the '<em><b>Value</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROPERTY_VALUE_BINDING__VALUE = 1;

	/**
	 * The number of structural features of the '<em>Property Value Binding</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PROPERTY_VALUE_BINDING_FEATURE_COUNT = 2;

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Model <em>Model</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Model</em>'.
	 * @see org.mybuild.myfile.Model
	 * @generated
	 */
	EClass getModel();

	/**
	 * Returns the meta object for the containment reference '{@link org.mybuild.myfile.Model#getPackage <em>Package</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference '<em>Package</em>'.
	 * @see org.mybuild.myfile.Model#getPackage()
	 * @see #getModel()
	 * @generated
	 */
	EReference getModel_Package();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.Model#getImports <em>Imports</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Imports</em>'.
	 * @see org.mybuild.myfile.Model#getImports()
	 * @see #getModel()
	 * @generated
	 */
	EReference getModel_Imports();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.Model#getTypes <em>Types</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Types</em>'.
	 * @see org.mybuild.myfile.Model#getTypes()
	 * @see #getModel()
	 * @generated
	 */
	EReference getModel_Types();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Package <em>Package</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Package</em>'.
	 * @see org.mybuild.myfile.Package
	 * @generated
	 */
	EClass getPackage();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.Package#getName <em>Name</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Name</em>'.
	 * @see org.mybuild.myfile.Package#getName()
	 * @see #getPackage()
	 * @generated
	 */
	EAttribute getPackage_Name();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Import <em>Import</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Import</em>'.
	 * @see org.mybuild.myfile.Import
	 * @generated
	 */
	EClass getImport();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.Import#getImportedNamespace <em>Imported Namespace</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Imported Namespace</em>'.
	 * @see org.mybuild.myfile.Import#getImportedNamespace()
	 * @see #getImport()
	 * @generated
	 */
	EAttribute getImport_ImportedNamespace();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Type <em>Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Type</em>'.
	 * @see org.mybuild.myfile.Type
	 * @generated
	 */
	EClass getType();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.AnnotationType <em>Annotation Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Annotation Type</em>'.
	 * @see org.mybuild.myfile.AnnotationType
	 * @generated
	 */
	EClass getAnnotationType();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.AnnotationType#getElements <em>Elements</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Elements</em>'.
	 * @see org.mybuild.myfile.AnnotationType#getElements()
	 * @see #getAnnotationType()
	 * @generated
	 */
	EReference getAnnotationType_Elements();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Annotation <em>Annotation</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Annotation</em>'.
	 * @see org.mybuild.myfile.Annotation
	 * @generated
	 */
	EClass getAnnotation();

	/**
	 * Returns the meta object for the reference '{@link org.mybuild.myfile.Annotation#getType <em>Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Type</em>'.
	 * @see org.mybuild.myfile.Annotation#getType()
	 * @see #getAnnotation()
	 * @generated
	 */
	EReference getAnnotation_Type();

	/**
	 * Returns the meta object for the container reference '{@link org.mybuild.myfile.Annotation#getTarget <em>Target</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the container reference '<em>Target</em>'.
	 * @see org.mybuild.myfile.Annotation#getTarget()
	 * @see #getAnnotation()
	 * @generated
	 */
	EReference getAnnotation_Target();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.Annotation#getElements <em>Elements</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Elements</em>'.
	 * @see org.mybuild.myfile.Annotation#getElements()
	 * @see #getAnnotation()
	 * @generated
	 */
	EReference getAnnotation_Elements();

	/**
	 * Returns the meta object for the containment reference '{@link org.mybuild.myfile.Annotation#getSingleValue <em>Single Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference '<em>Single Value</em>'.
	 * @see org.mybuild.myfile.Annotation#getSingleValue()
	 * @see #getAnnotation()
	 * @generated
	 */
	EReference getAnnotation_SingleValue();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.AnnotationTarget <em>Annotation Target</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Annotation Target</em>'.
	 * @see org.mybuild.myfile.AnnotationTarget
	 * @generated
	 */
	EClass getAnnotationTarget();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.AnnotationTarget#getAnnotations <em>Annotations</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Annotations</em>'.
	 * @see org.mybuild.myfile.AnnotationTarget#getAnnotations()
	 * @see #getAnnotationTarget()
	 * @generated
	 */
	EReference getAnnotationTarget_Annotations();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Interface <em>Interface</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Interface</em>'.
	 * @see org.mybuild.myfile.Interface
	 * @generated
	 */
	EClass getInterface();

	/**
	 * Returns the meta object for the reference '{@link org.mybuild.myfile.Interface#getSuperType <em>Super Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Super Type</em>'.
	 * @see org.mybuild.myfile.Interface#getSuperType()
	 * @see #getInterface()
	 * @generated
	 */
	EReference getInterface_SuperType();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.Interface#getFeatures <em>Features</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Features</em>'.
	 * @see org.mybuild.myfile.Interface#getFeatures()
	 * @see #getInterface()
	 * @generated
	 */
	EReference getInterface_Features();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Feature <em>Feature</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Feature</em>'.
	 * @see org.mybuild.myfile.Feature
	 * @generated
	 */
	EClass getFeature();

	/**
	 * Returns the meta object for the reference '{@link org.mybuild.myfile.Feature#getSuperType <em>Super Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Super Type</em>'.
	 * @see org.mybuild.myfile.Feature#getSuperType()
	 * @see #getFeature()
	 * @generated
	 */
	EReference getFeature_SuperType();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Module <em>Module</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Module</em>'.
	 * @see org.mybuild.myfile.Module
	 * @generated
	 */
	EClass getModule();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.Module#isStatic <em>Static</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Static</em>'.
	 * @see org.mybuild.myfile.Module#isStatic()
	 * @see #getModule()
	 * @generated
	 */
	EAttribute getModule_Static();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.Module#isAbstract <em>Abstract</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Abstract</em>'.
	 * @see org.mybuild.myfile.Module#isAbstract()
	 * @see #getModule()
	 * @generated
	 */
	EAttribute getModule_Abstract();

	/**
	 * Returns the meta object for the reference '{@link org.mybuild.myfile.Module#getSuperType <em>Super Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Super Type</em>'.
	 * @see org.mybuild.myfile.Module#getSuperType()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_SuperType();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getSubTypes <em>Sub Types</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Sub Types</em>'.
	 * @see org.mybuild.myfile.Module#getSubTypes()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_SubTypes();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getAllSuperTypes <em>All Super Types</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>All Super Types</em>'.
	 * @see org.mybuild.myfile.Module#getAllSuperTypes()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_AllSuperTypes();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getAllSubTypes <em>All Sub Types</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>All Sub Types</em>'.
	 * @see org.mybuild.myfile.Module#getAllSubTypes()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_AllSubTypes();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.Module#getMembers <em>Members</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Members</em>'.
	 * @see org.mybuild.myfile.Module#getMembers()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Members();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getDepends <em>Depends</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Depends</em>'.
	 * @see org.mybuild.myfile.Module#getDepends()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Depends();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getDependent <em>Dependent</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Dependent</em>'.
	 * @see org.mybuild.myfile.Module#getDependent()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Dependent();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getProvides <em>Provides</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Provides</em>'.
	 * @see org.mybuild.myfile.Module#getProvides()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Provides();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getRequires <em>Requires</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Requires</em>'.
	 * @see org.mybuild.myfile.Module#getRequires()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Requires();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getSources <em>Sources</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Sources</em>'.
	 * @see org.mybuild.myfile.Module#getSources()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Sources();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getObjects <em>Objects</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Objects</em>'.
	 * @see org.mybuild.myfile.Module#getObjects()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Objects();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.Module#getOptions <em>Options</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Options</em>'.
	 * @see org.mybuild.myfile.Module#getOptions()
	 * @see #getModule()
	 * @generated
	 */
	EReference getModule_Options();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Member <em>Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Member</em>'.
	 * @see org.mybuild.myfile.Member
	 * @generated
	 */
	EClass getMember();

	/**
	 * Returns the meta object for the container reference '{@link org.mybuild.myfile.Member#getContainingModule <em>Containing Module</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the container reference '<em>Containing Module</em>'.
	 * @see org.mybuild.myfile.Member#getContainingModule()
	 * @see #getMember()
	 * @generated
	 */
	EReference getMember_ContainingModule();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.DependsMember <em>Depends Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Depends Member</em>'.
	 * @see org.mybuild.myfile.DependsMember
	 * @generated
	 */
	EClass getDependsMember();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.DependsMember#getModules <em>Modules</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Modules</em>'.
	 * @see org.mybuild.myfile.DependsMember#getModules()
	 * @see #getDependsMember()
	 * @generated
	 */
	EReference getDependsMember_Modules();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.AbstractFeatureListMember <em>Abstract Feature List Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Abstract Feature List Member</em>'.
	 * @see org.mybuild.myfile.AbstractFeatureListMember
	 * @generated
	 */
	EClass getAbstractFeatureListMember();

	/**
	 * Returns the meta object for the reference list '{@link org.mybuild.myfile.AbstractFeatureListMember#getFeatures <em>Features</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference list '<em>Features</em>'.
	 * @see org.mybuild.myfile.AbstractFeatureListMember#getFeatures()
	 * @see #getAbstractFeatureListMember()
	 * @generated
	 */
	EReference getAbstractFeatureListMember_Features();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.RequiresMember <em>Requires Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Requires Member</em>'.
	 * @see org.mybuild.myfile.RequiresMember
	 * @generated
	 */
	EClass getRequiresMember();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.ProvidesMember <em>Provides Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Provides Member</em>'.
	 * @see org.mybuild.myfile.ProvidesMember
	 * @generated
	 */
	EClass getProvidesMember();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.AbstractFileListMember <em>Abstract File List Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Abstract File List Member</em>'.
	 * @see org.mybuild.myfile.AbstractFileListMember
	 * @generated
	 */
	EClass getAbstractFileListMember();

	/**
	 * Returns the meta object for the containment reference list '{@link org.mybuild.myfile.AbstractFileListMember#getFiles <em>Files</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Files</em>'.
	 * @see org.mybuild.myfile.AbstractFileListMember#getFiles()
	 * @see #getAbstractFileListMember()
	 * @generated
	 */
	EReference getAbstractFileListMember_Files();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.SourceMember <em>Source Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Source Member</em>'.
	 * @see org.mybuild.myfile.SourceMember
	 * @generated
	 */
	EClass getSourceMember();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.ObjectMember <em>Object Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Object Member</em>'.
	 * @see org.mybuild.myfile.ObjectMember
	 * @generated
	 */
	EClass getObjectMember();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.FileName <em>File Name</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>File Name</em>'.
	 * @see org.mybuild.myfile.FileName
	 * @generated
	 */
	EClass getFileName();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.FileName#getValue <em>Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Value</em>'.
	 * @see org.mybuild.myfile.FileName#getValue()
	 * @see #getFileName()
	 * @generated
	 */
	EAttribute getFileName_Value();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.OptionMember <em>Option Member</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Option Member</em>'.
	 * @see org.mybuild.myfile.OptionMember
	 * @generated
	 */
	EClass getOptionMember();

	/**
	 * Returns the meta object for the containment reference '{@link org.mybuild.myfile.OptionMember#getProperty <em>Property</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference '<em>Property</em>'.
	 * @see org.mybuild.myfile.OptionMember#getProperty()
	 * @see #getOptionMember()
	 * @generated
	 */
	EReference getOptionMember_Property();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Property <em>Property</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Property</em>'.
	 * @see org.mybuild.myfile.Property
	 * @generated
	 */
	EClass getProperty();

	/**
	 * Returns the meta object for the containment reference '{@link org.mybuild.myfile.Property#getDefaultValue <em>Default Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference '<em>Default Value</em>'.
	 * @see org.mybuild.myfile.Property#getDefaultValue()
	 * @see #getProperty()
	 * @generated
	 */
	EReference getProperty_DefaultValue();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.StringProperty <em>String Property</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>String Property</em>'.
	 * @see org.mybuild.myfile.StringProperty
	 * @generated
	 */
	EClass getStringProperty();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.NumberProperty <em>Number Property</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Number Property</em>'.
	 * @see org.mybuild.myfile.NumberProperty
	 * @generated
	 */
	EClass getNumberProperty();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.BooleanProperty <em>Boolean Property</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Boolean Property</em>'.
	 * @see org.mybuild.myfile.BooleanProperty
	 * @generated
	 */
	EClass getBooleanProperty();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.TypeProperty <em>Type Property</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Type Property</em>'.
	 * @see org.mybuild.myfile.TypeProperty
	 * @generated
	 */
	EClass getTypeProperty();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Value <em>Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Value</em>'.
	 * @see org.mybuild.myfile.Value
	 * @generated
	 */
	EClass getValue();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.StringLiteral <em>String Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>String Literal</em>'.
	 * @see org.mybuild.myfile.StringLiteral
	 * @generated
	 */
	EClass getStringLiteral();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.StringLiteral#getValue <em>Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Value</em>'.
	 * @see org.mybuild.myfile.StringLiteral#getValue()
	 * @see #getStringLiteral()
	 * @generated
	 */
	EAttribute getStringLiteral_Value();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.NumberLiteral <em>Number Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Number Literal</em>'.
	 * @see org.mybuild.myfile.NumberLiteral
	 * @generated
	 */
	EClass getNumberLiteral();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.NumberLiteral#getValue <em>Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Value</em>'.
	 * @see org.mybuild.myfile.NumberLiteral#getValue()
	 * @see #getNumberLiteral()
	 * @generated
	 */
	EAttribute getNumberLiteral_Value();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.BooleanLiteral <em>Boolean Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Boolean Literal</em>'.
	 * @see org.mybuild.myfile.BooleanLiteral
	 * @generated
	 */
	EClass getBooleanLiteral();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.BooleanLiteral#isIsTrue <em>Is True</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Is True</em>'.
	 * @see org.mybuild.myfile.BooleanLiteral#isIsTrue()
	 * @see #getBooleanLiteral()
	 * @generated
	 */
	EAttribute getBooleanLiteral_IsTrue();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.TypeLiteral <em>Type Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Type Literal</em>'.
	 * @see org.mybuild.myfile.TypeLiteral
	 * @generated
	 */
	EClass getTypeLiteral();

	/**
	 * Returns the meta object for the reference '{@link org.mybuild.myfile.TypeLiteral#getValue <em>Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Value</em>'.
	 * @see org.mybuild.myfile.TypeLiteral#getValue()
	 * @see #getTypeLiteral()
	 * @generated
	 */
	EReference getTypeLiteral_Value();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.PropertyValueBinding <em>Property Value Binding</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Property Value Binding</em>'.
	 * @see org.mybuild.myfile.PropertyValueBinding
	 * @generated
	 */
	EClass getPropertyValueBinding();

	/**
	 * Returns the meta object for the reference '{@link org.mybuild.myfile.PropertyValueBinding#getProperty <em>Property</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Property</em>'.
	 * @see org.mybuild.myfile.PropertyValueBinding#getProperty()
	 * @see #getPropertyValueBinding()
	 * @generated
	 */
	EReference getPropertyValueBinding_Property();

	/**
	 * Returns the meta object for the containment reference '{@link org.mybuild.myfile.PropertyValueBinding#getValue <em>Value</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference '<em>Value</em>'.
	 * @see org.mybuild.myfile.PropertyValueBinding#getValue()
	 * @see #getPropertyValueBinding()
	 * @generated
	 */
	EReference getPropertyValueBinding_Value();

	/**
	 * Returns the meta object for class '{@link org.mybuild.myfile.Named <em>Named</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Named</em>'.
	 * @see org.mybuild.myfile.Named
	 * @generated
	 */
	EClass getNamed();

	/**
	 * Returns the meta object for the attribute '{@link org.mybuild.myfile.Named#getName <em>Name</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Name</em>'.
	 * @see org.mybuild.myfile.Named#getName()
	 * @see #getNamed()
	 * @generated
	 */
	EAttribute getNamed_Name();

	/**
	 * Returns the factory that creates the instances of the model.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the factory that creates the instances of the model.
	 * @generated
	 */
	MyFileFactory getMyFileFactory();

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
	interface Literals {
		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.ModelImpl <em>Model</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.ModelImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getModel()
		 * @generated
		 */
		EClass MODEL = eINSTANCE.getModel();

		/**
		 * The meta object literal for the '<em><b>Package</b></em>' containment reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODEL__PACKAGE = eINSTANCE.getModel_Package();

		/**
		 * The meta object literal for the '<em><b>Imports</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODEL__IMPORTS = eINSTANCE.getModel_Imports();

		/**
		 * The meta object literal for the '<em><b>Types</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODEL__TYPES = eINSTANCE.getModel_Types();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.PackageImpl <em>Package</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.PackageImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getPackage()
		 * @generated
		 */
		EClass PACKAGE = eINSTANCE.getPackage();

		/**
		 * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute PACKAGE__NAME = eINSTANCE.getPackage_Name();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.ImportImpl <em>Import</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.ImportImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getImport()
		 * @generated
		 */
		EClass IMPORT = eINSTANCE.getImport();

		/**
		 * The meta object literal for the '<em><b>Imported Namespace</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute IMPORT__IMPORTED_NAMESPACE = eINSTANCE
				.getImport_ImportedNamespace();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.TypeImpl <em>Type</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.TypeImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getType()
		 * @generated
		 */
		EClass TYPE = eINSTANCE.getType();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.AnnotationTypeImpl <em>Annotation Type</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.AnnotationTypeImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAnnotationType()
		 * @generated
		 */
		EClass ANNOTATION_TYPE = eINSTANCE.getAnnotationType();

		/**
		 * The meta object literal for the '<em><b>Elements</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ANNOTATION_TYPE__ELEMENTS = eINSTANCE
				.getAnnotationType_Elements();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.AnnotationImpl <em>Annotation</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.AnnotationImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAnnotation()
		 * @generated
		 */
		EClass ANNOTATION = eINSTANCE.getAnnotation();

		/**
		 * The meta object literal for the '<em><b>Type</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ANNOTATION__TYPE = eINSTANCE.getAnnotation_Type();

		/**
		 * The meta object literal for the '<em><b>Target</b></em>' container reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ANNOTATION__TARGET = eINSTANCE.getAnnotation_Target();

		/**
		 * The meta object literal for the '<em><b>Elements</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ANNOTATION__ELEMENTS = eINSTANCE.getAnnotation_Elements();

		/**
		 * The meta object literal for the '<em><b>Single Value</b></em>' containment reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ANNOTATION__SINGLE_VALUE = eINSTANCE
				.getAnnotation_SingleValue();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.AnnotationTargetImpl <em>Annotation Target</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.AnnotationTargetImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAnnotationTarget()
		 * @generated
		 */
		EClass ANNOTATION_TARGET = eINSTANCE.getAnnotationTarget();

		/**
		 * The meta object literal for the '<em><b>Annotations</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ANNOTATION_TARGET__ANNOTATIONS = eINSTANCE
				.getAnnotationTarget_Annotations();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.InterfaceImpl <em>Interface</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.InterfaceImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getInterface()
		 * @generated
		 */
		EClass INTERFACE = eINSTANCE.getInterface();

		/**
		 * The meta object literal for the '<em><b>Super Type</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference INTERFACE__SUPER_TYPE = eINSTANCE.getInterface_SuperType();

		/**
		 * The meta object literal for the '<em><b>Features</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference INTERFACE__FEATURES = eINSTANCE.getInterface_Features();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.FeatureImpl <em>Feature</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.FeatureImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getFeature()
		 * @generated
		 */
		EClass FEATURE = eINSTANCE.getFeature();

		/**
		 * The meta object literal for the '<em><b>Super Type</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference FEATURE__SUPER_TYPE = eINSTANCE.getFeature_SuperType();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.ModuleImpl <em>Module</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.ModuleImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getModule()
		 * @generated
		 */
		EClass MODULE = eINSTANCE.getModule();

		/**
		 * The meta object literal for the '<em><b>Static</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute MODULE__STATIC = eINSTANCE.getModule_Static();

		/**
		 * The meta object literal for the '<em><b>Abstract</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute MODULE__ABSTRACT = eINSTANCE.getModule_Abstract();

		/**
		 * The meta object literal for the '<em><b>Super Type</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__SUPER_TYPE = eINSTANCE.getModule_SuperType();

		/**
		 * The meta object literal for the '<em><b>Sub Types</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__SUB_TYPES = eINSTANCE.getModule_SubTypes();

		/**
		 * The meta object literal for the '<em><b>All Super Types</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__ALL_SUPER_TYPES = eINSTANCE
				.getModule_AllSuperTypes();

		/**
		 * The meta object literal for the '<em><b>All Sub Types</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__ALL_SUB_TYPES = eINSTANCE.getModule_AllSubTypes();

		/**
		 * The meta object literal for the '<em><b>Members</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__MEMBERS = eINSTANCE.getModule_Members();

		/**
		 * The meta object literal for the '<em><b>Depends</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__DEPENDS = eINSTANCE.getModule_Depends();

		/**
		 * The meta object literal for the '<em><b>Dependent</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__DEPENDENT = eINSTANCE.getModule_Dependent();

		/**
		 * The meta object literal for the '<em><b>Provides</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__PROVIDES = eINSTANCE.getModule_Provides();

		/**
		 * The meta object literal for the '<em><b>Requires</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__REQUIRES = eINSTANCE.getModule_Requires();

		/**
		 * The meta object literal for the '<em><b>Sources</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__SOURCES = eINSTANCE.getModule_Sources();

		/**
		 * The meta object literal for the '<em><b>Objects</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__OBJECTS = eINSTANCE.getModule_Objects();

		/**
		 * The meta object literal for the '<em><b>Options</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MODULE__OPTIONS = eINSTANCE.getModule_Options();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.MemberImpl <em>Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.MemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getMember()
		 * @generated
		 */
		EClass MEMBER = eINSTANCE.getMember();

		/**
		 * The meta object literal for the '<em><b>Containing Module</b></em>' container reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference MEMBER__CONTAINING_MODULE = eINSTANCE
				.getMember_ContainingModule();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.DependsMemberImpl <em>Depends Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.DependsMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getDependsMember()
		 * @generated
		 */
		EClass DEPENDS_MEMBER = eINSTANCE.getDependsMember();

		/**
		 * The meta object literal for the '<em><b>Modules</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference DEPENDS_MEMBER__MODULES = eINSTANCE
				.getDependsMember_Modules();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.AbstractFeatureListMemberImpl <em>Abstract Feature List Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.AbstractFeatureListMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAbstractFeatureListMember()
		 * @generated
		 */
		EClass ABSTRACT_FEATURE_LIST_MEMBER = eINSTANCE
				.getAbstractFeatureListMember();

		/**
		 * The meta object literal for the '<em><b>Features</b></em>' reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ABSTRACT_FEATURE_LIST_MEMBER__FEATURES = eINSTANCE
				.getAbstractFeatureListMember_Features();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.RequiresMemberImpl <em>Requires Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.RequiresMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getRequiresMember()
		 * @generated
		 */
		EClass REQUIRES_MEMBER = eINSTANCE.getRequiresMember();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.ProvidesMemberImpl <em>Provides Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.ProvidesMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getProvidesMember()
		 * @generated
		 */
		EClass PROVIDES_MEMBER = eINSTANCE.getProvidesMember();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.AbstractFileListMemberImpl <em>Abstract File List Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.AbstractFileListMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getAbstractFileListMember()
		 * @generated
		 */
		EClass ABSTRACT_FILE_LIST_MEMBER = eINSTANCE
				.getAbstractFileListMember();

		/**
		 * The meta object literal for the '<em><b>Files</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ABSTRACT_FILE_LIST_MEMBER__FILES = eINSTANCE
				.getAbstractFileListMember_Files();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.SourceMemberImpl <em>Source Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.SourceMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getSourceMember()
		 * @generated
		 */
		EClass SOURCE_MEMBER = eINSTANCE.getSourceMember();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.ObjectMemberImpl <em>Object Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.ObjectMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getObjectMember()
		 * @generated
		 */
		EClass OBJECT_MEMBER = eINSTANCE.getObjectMember();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.FileNameImpl <em>File Name</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.FileNameImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getFileName()
		 * @generated
		 */
		EClass FILE_NAME = eINSTANCE.getFileName();

		/**
		 * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute FILE_NAME__VALUE = eINSTANCE.getFileName_Value();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.OptionMemberImpl <em>Option Member</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.OptionMemberImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getOptionMember()
		 * @generated
		 */
		EClass OPTION_MEMBER = eINSTANCE.getOptionMember();

		/**
		 * The meta object literal for the '<em><b>Property</b></em>' containment reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference OPTION_MEMBER__PROPERTY = eINSTANCE
				.getOptionMember_Property();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.PropertyImpl <em>Property</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.PropertyImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getProperty()
		 * @generated
		 */
		EClass PROPERTY = eINSTANCE.getProperty();

		/**
		 * The meta object literal for the '<em><b>Default Value</b></em>' containment reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PROPERTY__DEFAULT_VALUE = eINSTANCE
				.getProperty_DefaultValue();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.StringPropertyImpl <em>String Property</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.StringPropertyImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getStringProperty()
		 * @generated
		 */
		EClass STRING_PROPERTY = eINSTANCE.getStringProperty();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.NumberPropertyImpl <em>Number Property</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.NumberPropertyImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getNumberProperty()
		 * @generated
		 */
		EClass NUMBER_PROPERTY = eINSTANCE.getNumberProperty();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.BooleanPropertyImpl <em>Boolean Property</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.BooleanPropertyImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getBooleanProperty()
		 * @generated
		 */
		EClass BOOLEAN_PROPERTY = eINSTANCE.getBooleanProperty();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.TypePropertyImpl <em>Type Property</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.TypePropertyImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getTypeProperty()
		 * @generated
		 */
		EClass TYPE_PROPERTY = eINSTANCE.getTypeProperty();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.ValueImpl <em>Value</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.ValueImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getValue()
		 * @generated
		 */
		EClass VALUE = eINSTANCE.getValue();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.StringLiteralImpl <em>String Literal</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.StringLiteralImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getStringLiteral()
		 * @generated
		 */
		EClass STRING_LITERAL = eINSTANCE.getStringLiteral();

		/**
		 * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute STRING_LITERAL__VALUE = eINSTANCE.getStringLiteral_Value();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.NumberLiteralImpl <em>Number Literal</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.NumberLiteralImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getNumberLiteral()
		 * @generated
		 */
		EClass NUMBER_LITERAL = eINSTANCE.getNumberLiteral();

		/**
		 * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute NUMBER_LITERAL__VALUE = eINSTANCE.getNumberLiteral_Value();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.BooleanLiteralImpl <em>Boolean Literal</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.BooleanLiteralImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getBooleanLiteral()
		 * @generated
		 */
		EClass BOOLEAN_LITERAL = eINSTANCE.getBooleanLiteral();

		/**
		 * The meta object literal for the '<em><b>Is True</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute BOOLEAN_LITERAL__IS_TRUE = eINSTANCE
				.getBooleanLiteral_IsTrue();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.TypeLiteralImpl <em>Type Literal</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.TypeLiteralImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getTypeLiteral()
		 * @generated
		 */
		EClass TYPE_LITERAL = eINSTANCE.getTypeLiteral();

		/**
		 * The meta object literal for the '<em><b>Value</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference TYPE_LITERAL__VALUE = eINSTANCE.getTypeLiteral_Value();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.PropertyValueBindingImpl <em>Property Value Binding</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.PropertyValueBindingImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getPropertyValueBinding()
		 * @generated
		 */
		EClass PROPERTY_VALUE_BINDING = eINSTANCE.getPropertyValueBinding();

		/**
		 * The meta object literal for the '<em><b>Property</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PROPERTY_VALUE_BINDING__PROPERTY = eINSTANCE
				.getPropertyValueBinding_Property();

		/**
		 * The meta object literal for the '<em><b>Value</b></em>' containment reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PROPERTY_VALUE_BINDING__VALUE = eINSTANCE
				.getPropertyValueBinding_Value();

		/**
		 * The meta object literal for the '{@link org.mybuild.myfile.impl.NamedImpl <em>Named</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see org.mybuild.myfile.impl.NamedImpl
		 * @see org.mybuild.myfile.impl.MyFilePackageImpl#getNamed()
		 * @generated
		 */
		EClass NAMED = eINSTANCE.getNamed();

		/**
		 * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute NAMED__NAME = eINSTANCE.getNamed_Name();

	}

} //MyFilePackage
