#include <mint/memory/functiontool.h>
#include <mint/memory/casttool.h>
#include <cairo/cairo.h>

using namespace mint;

template<class Type>
static Type *get_object(Reference &object) {
	return object.data<LibObject<Type>>()->impl;
}

MINT_FUNCTION(cairo_create, 1, cursor) {

	FunctionHelper helper(cursor, 1);
	Reference &target = helper.pop_parameter();

	helper.return_value(create_object(cairo_create(get_object<cairo_surface_t>(target))));
}

MINT_FUNCTION(cairo_destroy, 1, cursor) {

	FunctionHelper helper(cursor, 1);
	Reference &cr = helper.pop_parameter();

	cairo_destroy(get_object<cairo_t>(cr));
}

MINT_FUNCTION(cairo_append_path, 2, cursor) {

	FunctionHelper helper(cursor, 2);
	Reference &path = helper.pop_parameter();
	Reference &cr = helper.pop_parameter();

	cairo_append_path(get_object<cairo_t>(cr), get_object<cairo_path_t>(path));
}

MINT_FUNCTION(cairo_arc, 6, cursor) {

	FunctionHelper helper(cursor, 6);
	Reference &angle2 = helper.pop_parameter();
	Reference &angle1 = helper.pop_parameter();
	Reference &radius = helper.pop_parameter();
	Reference &yc = helper.pop_parameter();
	Reference &xc = helper.pop_parameter();
	Reference &cr = helper.pop_parameter();

	cairo_arc(get_object<cairo_t>(cr), to_number(cursor, xc), to_number(cursor, yc), to_number(cursor, radius), to_number(cursor, angle1), to_number(cursor, angle2));
}

MINT_FUNCTION(cairo_arc_negative, 6, cursor) {

	FunctionHelper helper(cursor, 6);
	Reference &angle2 = helper.pop_parameter();
	Reference &angle1 = helper.pop_parameter();
	Reference &radius = helper.pop_parameter();
	Reference &yc = helper.pop_parameter();
	Reference &xc = helper.pop_parameter();
	Reference &cr = helper.pop_parameter();

	cairo_arc_negative(get_object<cairo_t>(cr), to_number(cursor, xc), to_number(cursor, yc), to_number(cursor, radius), to_number(cursor, angle1), to_number(cursor, angle2));
}

MINT_FUNCTION(cairo_clip, 1, cursor) {

	FunctionHelper helper(cursor, 1);
	Reference &cr = helper.pop_parameter();

	cairo_clip(get_object<cairo_t>(cr));
}

MINT_FUNCTION(cairo_clip_extents, 1, cursor) {

	FunctionHelper helper(cursor, 1);
	Reference &cr = helper.pop_parameter();

	double x1, y1, x2, y2;
	cairo_clip_extents(get_object<cairo_t>(cr), &x1, &y1, &x2, &y2);

	WeakReference result = create_iterator();
	iterator_insert(result.data<Iterator>(), create_number(x1));
	iterator_insert(result.data<Iterator>(), create_number(y1));
	iterator_insert(result.data<Iterator>(), create_number(x2));
	iterator_insert(result.data<Iterator>(), create_number(y2));
	helper.return_value(std::move(result));
}
