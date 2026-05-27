#include <cairo/cairo.h>
#include <mint/memory/builtin/iterator.h>
#include <mint/memory/builtin/libobject.h>
#include <mint/memory/cast_tools.h>
#include <mint/memory/function_tools.h>
#include <mint/memory/reference.h>

namespace {

template<class Type>
Type* get_object(const mint::Reference& object) {
	return object.data<mint::LibObject<Type>>().ptr;
}

mint::Reference mint_cairo_create(mint::Cursor& cursor, const mint::Reference& target) {
	return mint::create_c_object(cursor.ast(), cairo_create(get_object<cairo_surface_t>(target)));
}

mint::Reference mint_cairo_destroy(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_destroy(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_append_path(mint::Cursor& /*cursor*/, const mint::Reference& cr,
    const mint::Reference& path) {
	cairo_append_path(get_object<cairo_t>(cr), get_object<cairo_path_t>(path));
	return {};
}

mint::Reference mint_cairo_arc(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& xc,
    const mint::Reference& yc, const mint::Reference& radius, const mint::Reference& angle1,
    const mint::Reference& angle2) {
	cairo_arc(get_object<cairo_t>(cr), to_number(cursor, xc), to_number(cursor, yc), to_number(cursor, radius),
	    to_number(cursor, angle1), to_number(cursor, angle2));
	return {};
}

mint::Reference mint_cairo_arc_negative(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& xc,
    const mint::Reference& yc, const mint::Reference& radius, const mint::Reference& angle1,
    const mint::Reference& angle2) {
	cairo_arc_negative(get_object<cairo_t>(cr), to_number(cursor, xc), to_number(cursor, yc), to_number(cursor, radius),
	    to_number(cursor, angle1), to_number(cursor, angle2));
	return {};
}

mint::Reference mint_cairo_clip(mint::Cursor& /*cursor*/, mint::Reference& cr) {
	cairo_clip(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_clip_extents(mint::Cursor& cursor, mint::Reference& cr) {
	auto x1 = double();
	auto y1 = double();
	auto x2 = double();
	auto y2 = double();
	cairo_clip_extents(get_object<cairo_t>(cr), &x1, &y1, &x2, &y2);
	return mint::create_iterator_from(cursor, mint::create_number(x1), mint::create_number(y1), mint::create_number(x2),
	    mint::create_number(y2));
}

}

MINT_EXPORT_FUNCTION(mint_cairo_create, 1)
MINT_EXPORT_FUNCTION(mint_cairo_destroy, 1)
MINT_EXPORT_FUNCTION(mint_cairo_append_path, 2)
MINT_EXPORT_FUNCTION(mint_cairo_arc, 6)
MINT_EXPORT_FUNCTION(mint_cairo_arc_negative, 6)
MINT_EXPORT_FUNCTION(mint_cairo_clip, 1)
MINT_EXPORT_FUNCTION(mint_cairo_clip_extents, 1)
