/**
 * <copyright>
 * </copyright>
 *
 */
package org.mybuild.myfile.util;

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notifier;

import org.eclipse.emf.common.notify.impl.AdapterFactoryImpl;

import org.eclipse.emf.ecore.EObject;

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
 * The <b>Adapter Factory</b> for the model.
 * It provides an adapter <code>createXXX</code> method for each class of the model.
 * <!-- end-user-doc -->
 * @see org.mybuild.myfile.MyFilePackage
 * @generated
 */
public class MyFileAdapterFactory extends AdapterFactoryImpl
{
	/**
	 * The cached model package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected static MyFilePackage modelPackage;

	/**
	 * Creates an instance of the adapter factory.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public MyFileAdapterFactory()
	{
		if (modelPackage == null)
		{
			modelPackage = MyFilePackage.eINSTANCE;
		}
	}

	/**
	 * Returns whether this factory is applicable for the type of the object.
	 * <!-- begin-user-doc -->
	 * This implementation returns <code>true</code> if the object is either the model's package or is an instance object of the model.
	 * <!-- end-user-doc -->
	 * @return whether this factory is applicable for the type of the object.
	 * @generated
	 */
	@Override
	public boolean isFactoryForType(Object object)
	{
		if (object == modelPackage)
		{
			return true;
		}
		if (object instanceof EObject)
		{
			return ((EObject)object).eClass().getEPackage() == modelPackage;
		}
		return false;
	}

	/**
	 * The switch that delegates to the <code>createXXX</code> methods.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected MyFileSwitch<Adapter> modelSwitch =
		new MyFileSwitch<Adapter>()
		{
			@Override
			public Adapter caseModel(Model object)
			{
				return createModelAdapter();
			}
			@Override
			public Adapter casePackage(org.mybuild.myfile.Package object)
			{
				return createPackageAdapter();
			}
			@Override
			public Adapter caseImport(Import object)
			{
				return createImportAdapter();
			}
			@Override
			public Adapter caseType(Type object)
			{
				return createTypeAdapter();
			}
			@Override
			public Adapter caseAnnotationType(AnnotationType object)
			{
				return createAnnotationTypeAdapter();
			}
			@Override
			public Adapter caseAnnotation(Annotation object)
			{
				return createAnnotationAdapter();
			}
			@Override
			public Adapter caseAnnotationTarget(AnnotationTarget object)
			{
				return createAnnotationTargetAdapter();
			}
			@Override
			public Adapter caseInterface(Interface object)
			{
				return createInterfaceAdapter();
			}
			@Override
			public Adapter caseFeature(Feature object)
			{
				return createFeatureAdapter();
			}
			@Override
			public Adapter caseModule(Module object)
			{
				return createModuleAdapter();
			}
			@Override
			public Adapter caseMember(Member object)
			{
				return createMemberAdapter();
			}
			@Override
			public Adapter caseDependsMember(DependsMember object)
			{
				return createDependsMemberAdapter();
			}
			@Override
			public Adapter caseRequiresMember(RequiresMember object)
			{
				return createRequiresMemberAdapter();
			}
			@Override
			public Adapter caseProvidesMember(ProvidesMember object)
			{
				return createProvidesMemberAdapter();
			}
			@Override
			public Adapter caseSourceMember(SourceMember object)
			{
				return createSourceMemberAdapter();
			}
			@Override
			public Adapter caseObjectMember(ObjectMember object)
			{
				return createObjectMemberAdapter();
			}
			@Override
			public Adapter caseFileName(FileName object)
			{
				return createFileNameAdapter();
			}
			@Override
			public Adapter caseOptionMember(OptionMember object)
			{
				return createOptionMemberAdapter();
			}
			@Override
			public Adapter caseProperty(Property object)
			{
				return createPropertyAdapter();
			}
			@Override
			public Adapter caseStringProperty(StringProperty object)
			{
				return createStringPropertyAdapter();
			}
			@Override
			public Adapter caseNumberProperty(NumberProperty object)
			{
				return createNumberPropertyAdapter();
			}
			@Override
			public Adapter caseBooleanProperty(BooleanProperty object)
			{
				return createBooleanPropertyAdapter();
			}
			@Override
			public Adapter caseTypeProperty(TypeProperty object)
			{
				return createTypePropertyAdapter();
			}
			@Override
			public Adapter caseValue(Value object)
			{
				return createValueAdapter();
			}
			@Override
			public Adapter caseStringLiteral(StringLiteral object)
			{
				return createStringLiteralAdapter();
			}
			@Override
			public Adapter caseNumberLiteral(NumberLiteral object)
			{
				return createNumberLiteralAdapter();
			}
			@Override
			public Adapter caseBooleanLiteral(BooleanLiteral object)
			{
				return createBooleanLiteralAdapter();
			}
			@Override
			public Adapter caseTypeLiteral(TypeLiteral object)
			{
				return createTypeLiteralAdapter();
			}
			@Override
			public Adapter casePropertyValueBinding(PropertyValueBinding object)
			{
				return createPropertyValueBindingAdapter();
			}
			@Override
			public Adapter caseNamed(Named object)
			{
				return createNamedAdapter();
			}
			@Override
			public Adapter defaultCase(EObject object)
			{
				return createEObjectAdapter();
			}
		};

	/**
	 * Creates an adapter for the <code>target</code>.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param target the object to adapt.
	 * @return the adapter for the <code>target</code>.
	 * @generated
	 */
	@Override
	public Adapter createAdapter(Notifier target)
	{
		return modelSwitch.doSwitch((EObject)target);
	}


	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Model <em>Model</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Model
	 * @generated
	 */
	public Adapter createModelAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Package <em>Package</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Package
	 * @generated
	 */
	public Adapter createPackageAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Import <em>Import</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Import
	 * @generated
	 */
	public Adapter createImportAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Type <em>Type</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Type
	 * @generated
	 */
	public Adapter createTypeAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.AnnotationType <em>Annotation Type</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.AnnotationType
	 * @generated
	 */
	public Adapter createAnnotationTypeAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Annotation <em>Annotation</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Annotation
	 * @generated
	 */
	public Adapter createAnnotationAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.AnnotationTarget <em>Annotation Target</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.AnnotationTarget
	 * @generated
	 */
	public Adapter createAnnotationTargetAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Interface <em>Interface</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Interface
	 * @generated
	 */
	public Adapter createInterfaceAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Feature <em>Feature</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Feature
	 * @generated
	 */
	public Adapter createFeatureAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Module <em>Module</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Module
	 * @generated
	 */
	public Adapter createModuleAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Member <em>Member</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Member
	 * @generated
	 */
	public Adapter createMemberAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.DependsMember <em>Depends Member</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.DependsMember
	 * @generated
	 */
	public Adapter createDependsMemberAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.RequiresMember <em>Requires Member</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.RequiresMember
	 * @generated
	 */
	public Adapter createRequiresMemberAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.ProvidesMember <em>Provides Member</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.ProvidesMember
	 * @generated
	 */
	public Adapter createProvidesMemberAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.SourceMember <em>Source Member</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.SourceMember
	 * @generated
	 */
	public Adapter createSourceMemberAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.ObjectMember <em>Object Member</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.ObjectMember
	 * @generated
	 */
	public Adapter createObjectMemberAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.FileName <em>File Name</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.FileName
	 * @generated
	 */
	public Adapter createFileNameAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.OptionMember <em>Option Member</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.OptionMember
	 * @generated
	 */
	public Adapter createOptionMemberAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Property <em>Property</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Property
	 * @generated
	 */
	public Adapter createPropertyAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.StringProperty <em>String Property</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.StringProperty
	 * @generated
	 */
	public Adapter createStringPropertyAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.NumberProperty <em>Number Property</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.NumberProperty
	 * @generated
	 */
	public Adapter createNumberPropertyAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.BooleanProperty <em>Boolean Property</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.BooleanProperty
	 * @generated
	 */
	public Adapter createBooleanPropertyAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.TypeProperty <em>Type Property</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.TypeProperty
	 * @generated
	 */
	public Adapter createTypePropertyAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Value <em>Value</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Value
	 * @generated
	 */
	public Adapter createValueAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.StringLiteral <em>String Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.StringLiteral
	 * @generated
	 */
	public Adapter createStringLiteralAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.NumberLiteral <em>Number Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.NumberLiteral
	 * @generated
	 */
	public Adapter createNumberLiteralAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.BooleanLiteral <em>Boolean Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.BooleanLiteral
	 * @generated
	 */
	public Adapter createBooleanLiteralAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.TypeLiteral <em>Type Literal</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.TypeLiteral
	 * @generated
	 */
	public Adapter createTypeLiteralAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.PropertyValueBinding <em>Property Value Binding</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.PropertyValueBinding
	 * @generated
	 */
	public Adapter createPropertyValueBindingAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link org.mybuild.myfile.Named <em>Named</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see org.mybuild.myfile.Named
	 * @generated
	 */
	public Adapter createNamedAdapter()
	{
		return null;
	}

	/**
	 * Creates a new adapter for the default case.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @generated
	 */
	public Adapter createEObjectAdapter()
	{
		return null;
	}

} //MyFileAdapterFactory
