package org.mybuild.myfile.util;

import static com.google.common.collect.Iterables.*;

import org.mybuild.myfile.Annotation;
import org.mybuild.myfile.AnnotationTarget;
import org.mybuild.myfile.AnnotationType;

import com.google.common.base.Predicate;

/**
 * @author Eldar Abusalimov
 */
public class Annotations {
	
	public static final String MYBUILD_GENERATED = "Generated";

	public static Iterable<Annotation> getAnnotationsByName(AnnotationTarget o,
			final String name) {
		if (name == null) {
			throw new NullPointerException("name is null");
		}
		return filter(o.getAnnotations(), new Predicate<Annotation>() {
			public boolean apply(Annotation a) {
				AnnotationType type = a.getType();
				return type != null && name.equals(type.getName());
			}
		});
	}

	public static boolean isAnnotatedWith(AnnotationTarget o, final String name) {
		if (name == null) {
			throw new NullPointerException("name is null");
		}
		return find(o.getAnnotations(), new Predicate<Annotation>() {
			public boolean apply(Annotation a) {
				AnnotationType type = a.getType();
				return type != null && name.equals(type.getName());
			}
		}) != null;
	}
}
