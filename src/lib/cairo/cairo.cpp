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

int to_int(mint::Cursor& cursor, const mint::Reference& value) {
	return static_cast<int>(to_number(cursor, value));
}

cairo_content_t to_content(mint::Cursor& cursor, const mint::Reference& value) {
	switch (to_int(cursor, value)) {
	case 0:
		return CAIRO_CONTENT_COLOR;
	case 1:
		return CAIRO_CONTENT_ALPHA;
	case 2:
		return CAIRO_CONTENT_COLOR_ALPHA;
	default:
		return static_cast<cairo_content_t>(to_int(cursor, value));
	}
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

mint::Reference mint_cairo_copy_path(mint::Cursor& cursor, const mint::Reference& cr) {
	return mint::create_c_object(cursor.ast(), cairo_copy_path(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_copy_path_flat(mint::Cursor& cursor, const mint::Reference& cr) {
	return mint::create_c_object(cursor.ast(), cairo_copy_path_flat(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_path_destroy(mint::Cursor& /*cursor*/, const mint::Reference& path) {
	cairo_path_destroy(get_object<cairo_path_t>(path));
	return {};
}

mint::Reference mint_cairo_save(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_save(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_restore(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_restore(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_push_group(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_push_group(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_push_group_with_content(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& content) {
	cairo_push_group_with_content(get_object<cairo_t>(cr), to_content(cursor, content));
	return {};
}

mint::Reference mint_cairo_pop_group(mint::Cursor& cursor, const mint::Reference& cr) {
	return mint::create_c_object(cursor.ast(), cairo_pop_group(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_pop_group_to_source(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_pop_group_to_source(get_object<cairo_t>(cr));
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

mint::Reference mint_cairo_curve_to(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x1,
    const mint::Reference& y1, const mint::Reference& x2, const mint::Reference& y2, const mint::Reference& x3,
    const mint::Reference& y3) {
	cairo_curve_to(get_object<cairo_t>(cr), to_number(cursor, x1), to_number(cursor, y1), to_number(cursor, x2),
	    to_number(cursor, y2), to_number(cursor, x3), to_number(cursor, y3));
	return {};
}

mint::Reference mint_cairo_close_path(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_close_path(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_new_path(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_new_path(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_new_sub_path(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_new_sub_path(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_move_to(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x,
    const mint::Reference& y) {
	cairo_move_to(get_object<cairo_t>(cr), to_number(cursor, x), to_number(cursor, y));
	return {};
}

mint::Reference mint_cairo_line_to(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x,
    const mint::Reference& y) {
	cairo_line_to(get_object<cairo_t>(cr), to_number(cursor, x), to_number(cursor, y));
	return {};
}

mint::Reference mint_cairo_rel_move_to(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& dx,
    const mint::Reference& dy) {
	cairo_rel_move_to(get_object<cairo_t>(cr), to_number(cursor, dx), to_number(cursor, dy));
	return {};
}

mint::Reference mint_cairo_rel_line_to(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& dx,
    const mint::Reference& dy) {
	cairo_rel_line_to(get_object<cairo_t>(cr), to_number(cursor, dx), to_number(cursor, dy));
	return {};
}

mint::Reference mint_cairo_rectangle(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x,
    const mint::Reference& y, const mint::Reference& width, const mint::Reference& height) {
	cairo_rectangle(get_object<cairo_t>(cr), to_number(cursor, x), to_number(cursor, y), to_number(cursor, width),
	    to_number(cursor, height));
	return {};
}

mint::Reference mint_cairo_clip(mint::Cursor& /*cursor*/, mint::Reference& cr) {
	cairo_clip(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_clip_preserve(mint::Cursor& /*cursor*/, mint::Reference& cr) {
	cairo_clip_preserve(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_reset_clip(mint::Cursor& /*cursor*/, mint::Reference& cr) {
	cairo_reset_clip(get_object<cairo_t>(cr));
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

mint::Reference mint_cairo_fill(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_fill(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_fill_preserve(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_fill_preserve(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_fill_extents(mint::Cursor& cursor, const mint::Reference& cr) {
	auto x1 = double();
	auto y1 = double();
	auto x2 = double();
	auto y2 = double();
	cairo_fill_extents(get_object<cairo_t>(cr), &x1, &y1, &x2, &y2);
	return mint::create_iterator_from(cursor, mint::create_number(x1), mint::create_number(y1), mint::create_number(x2),
	    mint::create_number(y2));
}

mint::Reference mint_cairo_in_fill(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x,
    const mint::Reference& y) {
	return mint::create_boolean(cairo_in_fill(get_object<cairo_t>(cr), to_number(cursor, x), to_number(cursor, y)));
}

mint::Reference mint_cairo_stroke(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_stroke(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_stroke_preserve(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_stroke_preserve(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_stroke_extents(mint::Cursor& cursor, const mint::Reference& cr) {
	auto x1 = double();
	auto y1 = double();
	auto x2 = double();
	auto y2 = double();
	cairo_stroke_extents(get_object<cairo_t>(cr), &x1, &y1, &x2, &y2);
	return mint::create_iterator_from(cursor, mint::create_number(x1), mint::create_number(y1), mint::create_number(x2),
	    mint::create_number(y2));
}

mint::Reference mint_cairo_in_stroke(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x,
    const mint::Reference& y) {
	return mint::create_boolean(cairo_in_stroke(get_object<cairo_t>(cr), to_number(cursor, x), to_number(cursor, y)));
}

mint::Reference mint_cairo_paint(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_paint(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_paint_with_alpha(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& alpha) {
	cairo_paint_with_alpha(get_object<cairo_t>(cr), to_number(cursor, alpha));
	return {};
}

mint::Reference mint_cairo_copy_page(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_copy_page(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_show_page(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_show_page(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_set_source_rgb(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& red,
    const mint::Reference& green, const mint::Reference& blue) {
	cairo_set_source_rgb(get_object<cairo_t>(cr), to_number(cursor, red), to_number(cursor, green),
	    to_number(cursor, blue));
	return {};
}

mint::Reference mint_cairo_set_source_rgba(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& red,
    const mint::Reference& green, const mint::Reference& blue, const mint::Reference& alpha) {
	cairo_set_source_rgba(get_object<cairo_t>(cr), to_number(cursor, red), to_number(cursor, green),
	    to_number(cursor, blue), to_number(cursor, alpha));
	return {};
}

mint::Reference mint_cairo_set_source(mint::Cursor& /*cursor*/, const mint::Reference& cr,
    const mint::Reference& source) {
	cairo_set_source(get_object<cairo_t>(cr), get_object<cairo_pattern_t>(source));
	return {};
}

mint::Reference mint_cairo_set_source_surface(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& surface, const mint::Reference& x, const mint::Reference& y) {
	cairo_set_source_surface(get_object<cairo_t>(cr), get_object<cairo_surface_t>(surface), to_number(cursor, x),
	    to_number(cursor, y));
	return {};
}

mint::Reference mint_cairo_mask(mint::Cursor& /*cursor*/, const mint::Reference& cr, const mint::Reference& pattern) {
	cairo_mask(get_object<cairo_t>(cr), get_object<cairo_pattern_t>(pattern));
	return {};
}

mint::Reference mint_cairo_mask_surface(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& surface,
    const mint::Reference& surface_x, const mint::Reference& surface_y) {
	cairo_mask_surface(get_object<cairo_t>(cr), get_object<cairo_surface_t>(surface), to_number(cursor, surface_x),
	    to_number(cursor, surface_y));
	return {};
}

mint::Reference mint_cairo_set_line_width(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& width) {
	cairo_set_line_width(get_object<cairo_t>(cr), to_number(cursor, width));
	return {};
}

mint::Reference mint_cairo_get_line_width(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_line_width(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_set_miter_limit(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& limit) {
	cairo_set_miter_limit(get_object<cairo_t>(cr), to_number(cursor, limit));
	return {};
}

mint::Reference mint_cairo_get_miter_limit(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_miter_limit(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_set_tolerance(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& tolerance) {
	cairo_set_tolerance(get_object<cairo_t>(cr), to_number(cursor, tolerance));
	return {};
}

mint::Reference mint_cairo_get_tolerance(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_tolerance(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_set_operator(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& op) {
	cairo_set_operator(get_object<cairo_t>(cr), static_cast<cairo_operator_t>(to_int(cursor, op)));
	return {};
}

mint::Reference mint_cairo_get_operator(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_operator(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_set_antialias(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& antialias) {
	cairo_set_antialias(get_object<cairo_t>(cr), static_cast<cairo_antialias_t>(to_int(cursor, antialias)));
	return {};
}

mint::Reference mint_cairo_get_antialias(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_antialias(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_set_fill_rule(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& fill_rule) {
	cairo_set_fill_rule(get_object<cairo_t>(cr), static_cast<cairo_fill_rule_t>(to_int(cursor, fill_rule)));
	return {};
}

mint::Reference mint_cairo_get_fill_rule(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_fill_rule(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_set_line_cap(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& line_cap) {
	cairo_set_line_cap(get_object<cairo_t>(cr), static_cast<cairo_line_cap_t>(to_int(cursor, line_cap)));
	return {};
}

mint::Reference mint_cairo_get_line_cap(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_line_cap(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_set_line_join(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& line_join) {
	cairo_set_line_join(get_object<cairo_t>(cr), static_cast<cairo_line_join_t>(to_int(cursor, line_join)));
	return {};
}

mint::Reference mint_cairo_get_line_join(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_get_line_join(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_translate(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& tx,
    const mint::Reference& ty) {
	cairo_translate(get_object<cairo_t>(cr), to_number(cursor, tx), to_number(cursor, ty));
	return {};
}

mint::Reference mint_cairo_scale(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& sx,
    const mint::Reference& sy) {
	cairo_scale(get_object<cairo_t>(cr), to_number(cursor, sx), to_number(cursor, sy));
	return {};
}

mint::Reference mint_cairo_rotate(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& angle) {
	cairo_rotate(get_object<cairo_t>(cr), to_number(cursor, angle));
	return {};
}

mint::Reference mint_cairo_identity_matrix(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	cairo_identity_matrix(get_object<cairo_t>(cr));
	return {};
}

mint::Reference mint_cairo_user_to_device(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x,
    const mint::Reference& y) {
	auto x_value = to_number(cursor, x);
	auto y_value = to_number(cursor, y);
	cairo_user_to_device(get_object<cairo_t>(cr), &x_value, &y_value);
	return mint::create_iterator_from(cursor, mint::create_number(x_value), mint::create_number(y_value));
}

mint::Reference mint_cairo_user_to_device_distance(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& dx, const mint::Reference& dy) {
	auto dx_value = to_number(cursor, dx);
	auto dy_value = to_number(cursor, dy);
	cairo_user_to_device_distance(get_object<cairo_t>(cr), &dx_value, &dy_value);
	return mint::create_iterator_from(cursor, mint::create_number(dx_value), mint::create_number(dy_value));
}

mint::Reference mint_cairo_device_to_user(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& x,
    const mint::Reference& y) {
	auto x_value = to_number(cursor, x);
	auto y_value = to_number(cursor, y);
	cairo_device_to_user(get_object<cairo_t>(cr), &x_value, &y_value);
	return mint::create_iterator_from(cursor, mint::create_number(x_value), mint::create_number(y_value));
}

mint::Reference mint_cairo_device_to_user_distance(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& dx, const mint::Reference& dy) {
	auto dx_value = to_number(cursor, dx);
	auto dy_value = to_number(cursor, dy);
	cairo_device_to_user_distance(get_object<cairo_t>(cr), &dx_value, &dy_value);
	return mint::create_iterator_from(cursor, mint::create_number(dx_value), mint::create_number(dy_value));
}

mint::Reference mint_cairo_get_current_point(mint::Cursor& cursor, const mint::Reference& cr) {
	auto x = double();
	auto y = double();
	cairo_get_current_point(get_object<cairo_t>(cr), &x, &y);
	return mint::create_iterator_from(cursor, mint::create_number(x), mint::create_number(y));
}

mint::Reference mint_cairo_path_extents(mint::Cursor& cursor, const mint::Reference& cr) {
	auto x1 = double();
	auto y1 = double();
	auto x2 = double();
	auto y2 = double();
	cairo_path_extents(get_object<cairo_t>(cr), &x1, &y1, &x2, &y2);
	return mint::create_iterator_from(cursor, mint::create_number(x1), mint::create_number(y1), mint::create_number(x2),
	    mint::create_number(y2));
}

mint::Reference mint_cairo_status(mint::Cursor& /*cursor*/, const mint::Reference& cr) {
	return mint::create_number(cairo_status(get_object<cairo_t>(cr)));
}

mint::Reference mint_cairo_select_font_face(mint::Cursor& cursor, const mint::Reference& cr,
    const mint::Reference& family, const mint::Reference& slant, const mint::Reference& weight) {
	cairo_select_font_face(get_object<cairo_t>(cr), to_string(family).c_str(),
	    static_cast<cairo_font_slant_t>(to_int(cursor, slant)),
	    static_cast<cairo_font_weight_t>(to_int(cursor, weight)));
	return {};
}

mint::Reference mint_cairo_set_font_size(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& size) {
	cairo_set_font_size(get_object<cairo_t>(cr), to_number(cursor, size));
	return {};
}

mint::Reference mint_cairo_show_text(mint::Cursor& /*cursor*/, const mint::Reference& cr, const mint::Reference& utf8) {
	cairo_show_text(get_object<cairo_t>(cr), to_string(utf8).c_str());
	return {};
}

mint::Reference mint_cairo_text_path(mint::Cursor& /*cursor*/, const mint::Reference& cr, const mint::Reference& utf8) {
	cairo_text_path(get_object<cairo_t>(cr), to_string(utf8).c_str());
	return {};
}

mint::Reference mint_cairo_text_extents(mint::Cursor& cursor, const mint::Reference& cr, const mint::Reference& utf8) {
	auto extents = cairo_text_extents_t();
	cairo_text_extents(get_object<cairo_t>(cr), to_string(utf8).c_str(), &extents);
	return mint::create_iterator_from(cursor, mint::create_number(extents.x_bearing),
	    mint::create_number(extents.y_bearing), mint::create_number(extents.width), mint::create_number(extents.height),
	    mint::create_number(extents.x_advance), mint::create_number(extents.y_advance));
}

mint::Reference mint_cairo_font_extents(mint::Cursor& cursor, const mint::Reference& cr) {
	auto extents = cairo_font_extents_t();
	cairo_font_extents(get_object<cairo_t>(cr), &extents);
	return mint::create_iterator_from(cursor, mint::create_number(extents.ascent), mint::create_number(extents.descent),
	    mint::create_number(extents.height), mint::create_number(extents.max_x_advance),
	    mint::create_number(extents.max_y_advance));
}

mint::Reference mint_cairo_surface_create_image(mint::Cursor& cursor, const mint::Reference& format,
    const mint::Reference& width, const mint::Reference& height) {
	return mint::create_c_object(cursor.ast(),
	    cairo_image_surface_create(static_cast<cairo_format_t>(to_int(cursor, format)), to_int(cursor, width),
	        to_int(cursor, height)));
}

mint::Reference mint_cairo_surface_create_from_png(mint::Cursor& cursor, const mint::Reference& filename) {
	return mint::create_c_object(cursor.ast(), cairo_image_surface_create_from_png(to_string(filename).c_str()));
}

mint::Reference mint_cairo_surface_create_similar(mint::Cursor& cursor, const mint::Reference& other,
    const mint::Reference& content, const mint::Reference& width, const mint::Reference& height) {
	return mint::create_c_object(cursor.ast(),
	    cairo_surface_create_similar(get_object<cairo_surface_t>(other), to_content(cursor, content),
	        to_int(cursor, width), to_int(cursor, height)));
}

mint::Reference mint_cairo_surface_create_similar_image(mint::Cursor& cursor, const mint::Reference& other,
    const mint::Reference& format, const mint::Reference& width, const mint::Reference& height) {
	return mint::create_c_object(cursor.ast(),
	    cairo_surface_create_similar_image(get_object<cairo_surface_t>(other),
	        static_cast<cairo_format_t>(to_int(cursor, format)), to_int(cursor, width), to_int(cursor, height)));
}

mint::Reference mint_cairo_surface_destroy(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	cairo_surface_destroy(get_object<cairo_surface_t>(surface));
	return {};
}

mint::Reference mint_cairo_surface_finish(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	cairo_surface_finish(get_object<cairo_surface_t>(surface));
	return {};
}

mint::Reference mint_cairo_surface_flush(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	cairo_surface_flush(get_object<cairo_surface_t>(surface));
	return {};
}

mint::Reference mint_cairo_surface_mark_dirty(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	cairo_surface_mark_dirty(get_object<cairo_surface_t>(surface));
	return {};
}

mint::Reference mint_cairo_surface_mark_dirty_rectangle(mint::Cursor& cursor, const mint::Reference& surface,
    const mint::Reference& x, const mint::Reference& y, const mint::Reference& width, const mint::Reference& height) {
	cairo_surface_mark_dirty_rectangle(get_object<cairo_surface_t>(surface), to_int(cursor, x), to_int(cursor, y),
	    to_int(cursor, width), to_int(cursor, height));
	return {};
}

mint::Reference mint_cairo_surface_copy_page(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	cairo_surface_copy_page(get_object<cairo_surface_t>(surface));
	return {};
}

mint::Reference mint_cairo_surface_show_page(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	cairo_surface_show_page(get_object<cairo_surface_t>(surface));
	return {};
}

mint::Reference mint_cairo_surface_status(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	return mint::create_number(cairo_surface_status(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_surface_get_type(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	return mint::create_number(cairo_surface_get_type(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_surface_get_content(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	return mint::create_number(cairo_surface_get_content(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_surface_write_to_png(mint::Cursor& /*cursor*/, const mint::Reference& surface,
    const mint::Reference& filename) {
	return mint::create_number(
	    cairo_surface_write_to_png(get_object<cairo_surface_t>(surface), to_string(filename).c_str()));
}

mint::Reference mint_cairo_surface_set_device_scale(mint::Cursor& cursor, const mint::Reference& surface,
    const mint::Reference& x_scale, const mint::Reference& y_scale) {
	cairo_surface_set_device_scale(get_object<cairo_surface_t>(surface), to_number(cursor, x_scale),
	    to_number(cursor, y_scale));
	return {};
}

mint::Reference mint_cairo_surface_get_device_scale(mint::Cursor& cursor, const mint::Reference& surface) {
	auto x_scale = double();
	auto y_scale = double();
	cairo_surface_get_device_scale(get_object<cairo_surface_t>(surface), &x_scale, &y_scale);
	return mint::create_iterator_from(cursor, mint::create_number(x_scale), mint::create_number(y_scale));
}

mint::Reference mint_cairo_surface_set_device_offset(mint::Cursor& cursor, const mint::Reference& surface,
    const mint::Reference& x_offset, const mint::Reference& y_offset) {
	cairo_surface_set_device_offset(get_object<cairo_surface_t>(surface), to_number(cursor, x_offset),
	    to_number(cursor, y_offset));
	return {};
}

mint::Reference mint_cairo_surface_get_device_offset(mint::Cursor& cursor, const mint::Reference& surface) {
	auto x_offset = double();
	auto y_offset = double();
	cairo_surface_get_device_offset(get_object<cairo_surface_t>(surface), &x_offset, &y_offset);
	return mint::create_iterator_from(cursor, mint::create_number(x_offset), mint::create_number(y_offset));
}

mint::Reference mint_cairo_surface_set_fallback_resolution(mint::Cursor& cursor, const mint::Reference& surface,
    const mint::Reference& x_pixels_per_inch, const mint::Reference& y_pixels_per_inch) {
	cairo_surface_set_fallback_resolution(get_object<cairo_surface_t>(surface), to_number(cursor, x_pixels_per_inch),
	    to_number(cursor, y_pixels_per_inch));
	return {};
}

mint::Reference mint_cairo_surface_get_fallback_resolution(mint::Cursor& cursor, const mint::Reference& surface) {
	auto x_pixels_per_inch = double();
	auto y_pixels_per_inch = double();
	cairo_surface_get_fallback_resolution(get_object<cairo_surface_t>(surface), &x_pixels_per_inch, &y_pixels_per_inch);
	return mint::create_iterator_from(cursor, mint::create_number(x_pixels_per_inch),
	    mint::create_number(y_pixels_per_inch));
}

mint::Reference mint_cairo_image_surface_get_width(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	return mint::create_number(cairo_image_surface_get_width(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_image_surface_get_height(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	return mint::create_number(cairo_image_surface_get_height(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_image_surface_get_stride(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	return mint::create_number(cairo_image_surface_get_stride(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_image_surface_get_format(mint::Cursor& /*cursor*/, const mint::Reference& surface) {
	return mint::create_number(cairo_image_surface_get_format(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_pattern_create_rgb(mint::Cursor& cursor, const mint::Reference& red,
    const mint::Reference& green, const mint::Reference& blue) {
	return mint::create_c_object(cursor.ast(),
	    cairo_pattern_create_rgb(to_number(cursor, red), to_number(cursor, green), to_number(cursor, blue)));
}

mint::Reference mint_cairo_pattern_create_rgba(mint::Cursor& cursor, const mint::Reference& red,
    const mint::Reference& green, const mint::Reference& blue, const mint::Reference& alpha) {
	return mint::create_c_object(cursor.ast(),
	    cairo_pattern_create_rgba(to_number(cursor, red), to_number(cursor, green), to_number(cursor, blue),
	        to_number(cursor, alpha)));
}

mint::Reference mint_cairo_pattern_create_for_surface(mint::Cursor& cursor, const mint::Reference& surface) {
	return mint::create_c_object(cursor.ast(), cairo_pattern_create_for_surface(get_object<cairo_surface_t>(surface)));
}

mint::Reference mint_cairo_pattern_create_linear(mint::Cursor& cursor, const mint::Reference& x0,
    const mint::Reference& y0, const mint::Reference& x1, const mint::Reference& y1) {
	return mint::create_c_object(cursor.ast(), cairo_pattern_create_linear(to_number(cursor, x0), to_number(cursor, y0),
	                                               to_number(cursor, x1), to_number(cursor, y1)));
}

mint::Reference mint_cairo_pattern_create_radial(mint::Cursor& cursor, const mint::Reference& cx0,
    const mint::Reference& cy0, const mint::Reference& radius0, const mint::Reference& cx1, const mint::Reference& cy1,
    const mint::Reference& radius1) {
	return mint::create_c_object(cursor.ast(),
	    cairo_pattern_create_radial(to_number(cursor, cx0), to_number(cursor, cy0), to_number(cursor, radius0),
	        to_number(cursor, cx1), to_number(cursor, cy1), to_number(cursor, radius1)));
}

mint::Reference mint_cairo_pattern_destroy(mint::Cursor& /*cursor*/, const mint::Reference& pattern) {
	cairo_pattern_destroy(get_object<cairo_pattern_t>(pattern));
	return {};
}

mint::Reference mint_cairo_pattern_status(mint::Cursor& /*cursor*/, const mint::Reference& pattern) {
	return mint::create_number(cairo_pattern_status(get_object<cairo_pattern_t>(pattern)));
}

mint::Reference mint_cairo_pattern_get_type(mint::Cursor& /*cursor*/, const mint::Reference& pattern) {
	return mint::create_number(cairo_pattern_get_type(get_object<cairo_pattern_t>(pattern)));
}

mint::Reference mint_cairo_pattern_add_color_stop_rgb(mint::Cursor& cursor, const mint::Reference& pattern,
    const mint::Reference& offset, const mint::Reference& red, const mint::Reference& green,
    const mint::Reference& blue) {
	cairo_pattern_add_color_stop_rgb(get_object<cairo_pattern_t>(pattern), to_number(cursor, offset),
	    to_number(cursor, red), to_number(cursor, green), to_number(cursor, blue));
	return {};
}

mint::Reference mint_cairo_pattern_add_color_stop_rgba(mint::Cursor& cursor, const mint::Reference& pattern,
    const mint::Reference& offset, const mint::Reference& red, const mint::Reference& green,
    const mint::Reference& blue, const mint::Reference& alpha) {
	cairo_pattern_add_color_stop_rgba(get_object<cairo_pattern_t>(pattern), to_number(cursor, offset),
	    to_number(cursor, red), to_number(cursor, green), to_number(cursor, blue), to_number(cursor, alpha));
	return {};
}

}

MINT_EXPORT_FUNCTION(mint_cairo_create, 1)
MINT_EXPORT_FUNCTION(mint_cairo_destroy, 1)
MINT_EXPORT_FUNCTION(mint_cairo_append_path, 2)
MINT_EXPORT_FUNCTION(mint_cairo_copy_path, 1)
MINT_EXPORT_FUNCTION(mint_cairo_copy_path_flat, 1)
MINT_EXPORT_FUNCTION(mint_cairo_path_destroy, 1)
MINT_EXPORT_FUNCTION(mint_cairo_save, 1)
MINT_EXPORT_FUNCTION(mint_cairo_restore, 1)
MINT_EXPORT_FUNCTION(mint_cairo_push_group, 1)
MINT_EXPORT_FUNCTION(mint_cairo_push_group_with_content, 2)
MINT_EXPORT_FUNCTION(mint_cairo_pop_group, 1)
MINT_EXPORT_FUNCTION(mint_cairo_pop_group_to_source, 1)
MINT_EXPORT_FUNCTION(mint_cairo_arc, 6)
MINT_EXPORT_FUNCTION(mint_cairo_arc_negative, 6)
MINT_EXPORT_FUNCTION(mint_cairo_curve_to, 7)
MINT_EXPORT_FUNCTION(mint_cairo_close_path, 1)
MINT_EXPORT_FUNCTION(mint_cairo_new_path, 1)
MINT_EXPORT_FUNCTION(mint_cairo_new_sub_path, 1)
MINT_EXPORT_FUNCTION(mint_cairo_move_to, 3)
MINT_EXPORT_FUNCTION(mint_cairo_line_to, 3)
MINT_EXPORT_FUNCTION(mint_cairo_rel_move_to, 3)
MINT_EXPORT_FUNCTION(mint_cairo_rel_line_to, 3)
MINT_EXPORT_FUNCTION(mint_cairo_rectangle, 5)
MINT_EXPORT_FUNCTION(mint_cairo_clip, 1)
MINT_EXPORT_FUNCTION(mint_cairo_clip_preserve, 1)
MINT_EXPORT_FUNCTION(mint_cairo_reset_clip, 1)
MINT_EXPORT_FUNCTION(mint_cairo_clip_extents, 1)
MINT_EXPORT_FUNCTION(mint_cairo_fill, 1)
MINT_EXPORT_FUNCTION(mint_cairo_fill_preserve, 1)
MINT_EXPORT_FUNCTION(mint_cairo_fill_extents, 1)
MINT_EXPORT_FUNCTION(mint_cairo_in_fill, 3)
MINT_EXPORT_FUNCTION(mint_cairo_stroke, 1)
MINT_EXPORT_FUNCTION(mint_cairo_stroke_preserve, 1)
MINT_EXPORT_FUNCTION(mint_cairo_stroke_extents, 1)
MINT_EXPORT_FUNCTION(mint_cairo_in_stroke, 3)
MINT_EXPORT_FUNCTION(mint_cairo_paint, 1)
MINT_EXPORT_FUNCTION(mint_cairo_paint_with_alpha, 2)
MINT_EXPORT_FUNCTION(mint_cairo_copy_page, 1)
MINT_EXPORT_FUNCTION(mint_cairo_show_page, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_source_rgb, 4)
MINT_EXPORT_FUNCTION(mint_cairo_set_source_rgba, 5)
MINT_EXPORT_FUNCTION(mint_cairo_set_source, 2)
MINT_EXPORT_FUNCTION(mint_cairo_set_source_surface, 4)
MINT_EXPORT_FUNCTION(mint_cairo_mask, 2)
MINT_EXPORT_FUNCTION(mint_cairo_mask_surface, 4)
MINT_EXPORT_FUNCTION(mint_cairo_set_line_width, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_line_width, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_miter_limit, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_miter_limit, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_tolerance, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_tolerance, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_operator, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_operator, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_antialias, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_antialias, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_fill_rule, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_fill_rule, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_line_cap, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_line_cap, 1)
MINT_EXPORT_FUNCTION(mint_cairo_set_line_join, 2)
MINT_EXPORT_FUNCTION(mint_cairo_get_line_join, 1)
MINT_EXPORT_FUNCTION(mint_cairo_translate, 3)
MINT_EXPORT_FUNCTION(mint_cairo_scale, 3)
MINT_EXPORT_FUNCTION(mint_cairo_rotate, 2)
MINT_EXPORT_FUNCTION(mint_cairo_identity_matrix, 1)
MINT_EXPORT_FUNCTION(mint_cairo_user_to_device, 3)
MINT_EXPORT_FUNCTION(mint_cairo_user_to_device_distance, 3)
MINT_EXPORT_FUNCTION(mint_cairo_device_to_user, 3)
MINT_EXPORT_FUNCTION(mint_cairo_device_to_user_distance, 3)
MINT_EXPORT_FUNCTION(mint_cairo_get_current_point, 1)
MINT_EXPORT_FUNCTION(mint_cairo_path_extents, 1)
MINT_EXPORT_FUNCTION(mint_cairo_status, 1)
MINT_EXPORT_FUNCTION(mint_cairo_select_font_face, 4)
MINT_EXPORT_FUNCTION(mint_cairo_set_font_size, 2)
MINT_EXPORT_FUNCTION(mint_cairo_show_text, 2)
MINT_EXPORT_FUNCTION(mint_cairo_text_path, 2)
MINT_EXPORT_FUNCTION(mint_cairo_text_extents, 2)
MINT_EXPORT_FUNCTION(mint_cairo_font_extents, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_create_image, 3)
MINT_EXPORT_FUNCTION(mint_cairo_surface_create_from_png, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_create_similar, 4)
MINT_EXPORT_FUNCTION(mint_cairo_surface_create_similar_image, 4)
MINT_EXPORT_FUNCTION(mint_cairo_surface_destroy, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_finish, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_flush, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_mark_dirty, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_mark_dirty_rectangle, 5)
MINT_EXPORT_FUNCTION(mint_cairo_surface_copy_page, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_show_page, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_status, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_get_type, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_get_content, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_write_to_png, 2)
MINT_EXPORT_FUNCTION(mint_cairo_surface_set_device_scale, 3)
MINT_EXPORT_FUNCTION(mint_cairo_surface_get_device_scale, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_set_device_offset, 3)
MINT_EXPORT_FUNCTION(mint_cairo_surface_get_device_offset, 1)
MINT_EXPORT_FUNCTION(mint_cairo_surface_set_fallback_resolution, 3)
MINT_EXPORT_FUNCTION(mint_cairo_surface_get_fallback_resolution, 1)
MINT_EXPORT_FUNCTION(mint_cairo_image_surface_get_width, 1)
MINT_EXPORT_FUNCTION(mint_cairo_image_surface_get_height, 1)
MINT_EXPORT_FUNCTION(mint_cairo_image_surface_get_stride, 1)
MINT_EXPORT_FUNCTION(mint_cairo_image_surface_get_format, 1)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_create_rgb, 3)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_create_rgba, 4)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_create_for_surface, 1)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_create_linear, 4)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_create_radial, 6)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_destroy, 1)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_status, 1)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_get_type, 1)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_add_color_stop_rgb, 5)
MINT_EXPORT_FUNCTION(mint_cairo_pattern_add_color_stop_rgba, 6)
