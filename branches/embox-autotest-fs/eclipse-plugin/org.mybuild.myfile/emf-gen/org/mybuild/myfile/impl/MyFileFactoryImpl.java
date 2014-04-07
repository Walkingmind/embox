/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile.impl;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

import org.mybuild.myfile.Annotation;
import org.mybuild.myfile.AnnotationTarget;
import org.mybuild.myfile.AnnotationType;
import org.mybuild.myfile.BooleanLiteral;
import org.mybuild.myfile.BooleanProperty;
import org.mybuild.myfile.DependsMember;
import org.mybuild.myfile.Feature;
import org.mybuild.myfile.FileName;
import org.mybuild.myfile.Import;
import org.mybuild.myfile.Interface;
import org.mybuild.myfile.Member;
import org.mybuild.myfile.Model;
import org.mybuild.myfile.Module;
import org.mybuild.myfile.MyFileFactory;
import org.mybuild.myfile.MyFilePackage;
import org.mybuild.myfile.Named;
import org.mybuild.myfile.NumberLiteral;
import org.mybuild.myfile.NumberProperty;
import org.mybuild.myfile.ObjectMember;
import org.mybuild.myfile.OptionMember;
import org.mybuild.myfile.Property;
import org.mybuild.myfile.PropertyValueBinding;
import org.mybuild.myfile.ProvidesMember;
import org.mybuild.myfile.RequiresMember;
import org.mybuild.myfile.SourceMember;
import org.mybuild.myfile.StringLiteral;
import org.mybuild.myfile.StringProperty;
import org.mybuild.myfile.Type;
import org.mybuild.myfile.TypeLiteral;
import org.mybuild.myfile.TypeProperty;
import org.mybuild.myfile.Value;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class MyFileFactoryImpl extends EFactoryImpl implements MyFileFactory {
	/**
	 * Creates the default factory implementation.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static MyFileFactory init() {
		try {
			MyFileFactory theMyFileFactory = (MyFileFactory) EPackage.Registry.INSTANCE
					.getEFactory("http://www.mybuild.org/MyFile");
			if (theMyFileFactory != null) {
				return theMyFileFactory;
			}
		} catch (Exception exception) {
			EcorePlugin.INSTANCE.log(exception);
		}
		return new MyFileFactoryImpl();
	}

	/**
	 * Creates an instance of the factory.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public MyFileFactoryImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public EObject create(EClass eClass) {
		switch (eClass.getClassifierID()) {
		case MyFilePackage.MODEL:
			return createModel();
		case MyFilePackage.PACKAGE:
			return createPackage();
		case MyFilePackage.IMPORT:
			return createImport();
		case MyFilePackage.TYPE:
			return createType();
		case MyFilePackage.ANNOTATION_TYPE:
			return createAnnotationType();
		case MyFilePackage.ANNOTATION:
			return createAnnotation();
		case MyFilePackage.ANNOTATION_TARGET:
			return createAnnotationTarget();
		case MyFilePackage.INTERFACE:
			return createInterface();
		case MyFilePackage.FEATURE:
			return createFeature();
		case MyFilePackage.MODULE:
			return createModule();
		case MyFilePackage.MEMBER:
			return createMember();
		case MyFilePackage.DEPENDS_MEMBER:
			return createDependsMember();
		case MyFilePackage.REQUIRES_MEMBER:
			return createRequiresMember();
		case MyFilePackage.PROVIDES_MEMBER:
			return createProvidesMember();
		case MyFilePackage.SOURCE_MEMBER:
			return createSourceMember();
		case MyFilePackage.OBJECT_MEMBER:
			return createObjectMember();
		case MyFilePackage.FILE_NAME:
			return createFileName();
		case MyFilePackage.OPTION_MEMBER:
			return createOptionMember();
		case MyFilePackage.PROPERTY:
			return createProperty();
		case MyFilePackage.STRING_PROPERTY:
			return createStringProperty();
		case MyFilePackage.NUMBER_PROPERTY:
			return createNumberProperty();
		case MyFilePackage.BOOLEAN_PROPERTY:
			return createBooleanProperty();
		case MyFilePackage.TYPE_PROPERTY:
			return createTypeProperty();
		case MyFilePackage.VALUE:
			return createValue();
		case MyFilePackage.STRING_LITERAL:
			return createStringLiteral();
		case MyFilePackage.NUMBER_LITERAL:
			return createNumberLiteral();
		case MyFilePackage.BOOLEAN_LITERAL:
			return createBooleanLiteral();
		case MyFilePackage.TYPE_LITERAL:
			return createTypeLiteral();
		case MyFilePackage.PROPERTY_VALUE_BINDING:
			return createPropertyValueBinding();
		case MyFilePackage.NAMED:
			return createNamed();
		default:
			throw new IllegalArgumentException("The class '" + eClass.getName()
					+ "' is not a valid classifier");
		}
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Model createModel() {
		ModelImpl model = new ModelImpl();
		return model;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public org.mybuild.myfile.Package createPackage() {
		PackageImpl package_ = new PackageImpl();
		return package_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Import createImport() {
		ImportImpl import_ = new ImportImpl();
		return import_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Type createType() {
		TypeImpl type = new TypeImpl();
		return type;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public AnnotationType createAnnotationType() {
		AnnotationTypeImpl annotationType = new AnnotationTypeImpl();
		return annotationType;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Annotation createAnnotation() {
		AnnotationImpl annotation = new AnnotationImpl();
		return annotation;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public AnnotationTarget createAnnotationTarget() {
		AnnotationTargetImpl annotationTarget = new AnnotationTargetImpl();
		return annotationTarget;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Interface createInterface() {
		InterfaceImpl interface_ = new InterfaceImpl();
		return interface_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Feature createFeature() {
		FeatureImpl feature = new FeatureImpl();
		return feature;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Module createModule() {
		ModuleImpl module = new ModuleImpl();
		return module;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Member createMember() {
		MemberImpl member = new MemberImpl();
		return member;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public DependsMember createDependsMember() {
		DependsMemberImpl dependsMember = new DependsMemberImpl();
		return dependsMember;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public RequiresMember createRequiresMember() {
		RequiresMemberImpl requiresMember = new RequiresMemberImpl();
		return requiresMember;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ProvidesMember createProvidesMember() {
		ProvidesMemberImpl providesMember = new ProvidesMemberImpl();
		return providesMember;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public SourceMember createSourceMember() {
		SourceMemberImpl sourceMember = new SourceMemberImpl();
		return sourceMember;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ObjectMember createObjectMember() {
		ObjectMemberImpl objectMember = new ObjectMemberImpl();
		return objectMember;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public FileName createFileName() {
		FileNameImpl fileName = new FileNameImpl();
		return fileName;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public OptionMember createOptionMember() {
		OptionMemberImpl optionMember = new OptionMemberImpl();
		return optionMember;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Property createProperty() {
		PropertyImpl property = new PropertyImpl();
		return property;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public StringProperty createStringProperty() {
		StringPropertyImpl stringProperty = new StringPropertyImpl();
		return stringProperty;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NumberProperty createNumberProperty() {
		NumberPropertyImpl numberProperty = new NumberPropertyImpl();
		return numberProperty;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public BooleanProperty createBooleanProperty() {
		BooleanPropertyImpl booleanProperty = new BooleanPropertyImpl();
		return booleanProperty;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public TypeProperty createTypeProperty() {
		TypePropertyImpl typeProperty = new TypePropertyImpl();
		return typeProperty;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Value createValue() {
		ValueImpl value = new ValueImpl();
		return value;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public StringLiteral createStringLiteral() {
		StringLiteralImpl stringLiteral = new StringLiteralImpl();
		return stringLiteral;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NumberLiteral createNumberLiteral() {
		NumberLiteralImpl numberLiteral = new NumberLiteralImpl();
		return numberLiteral;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public BooleanLiteral createBooleanLiteral() {
		BooleanLiteralImpl booleanLiteral = new BooleanLiteralImpl();
		return booleanLiteral;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public TypeLiteral createTypeLiteral() {
		TypeLiteralImpl typeLiteral = new TypeLiteralImpl();
		return typeLiteral;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public PropertyValueBinding createPropertyValueBinding() {
		PropertyValueBindingImpl propertyValueBinding = new PropertyValueBindingImpl();
		return propertyValueBinding;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Named createNamed() {
		NamedImpl named = new NamedImpl();
		return named;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public MyFilePackage getMyFilePackage() {
		return (MyFilePackage) getEPackage();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @deprecated
	 * @generated
	 */
	@Deprecated
	public static MyFilePackage getPackage() {
		return MyFilePackage.eINSTANCE;
	}

} //MyFileFactoryImpl
