#if !defined(RLAY_H)
#define RLAY_H

/*
// Rlay -- a very small and simple rect 'layout' library. Aka. utilities to
// modify and split rectangles. I think this way of making UI is middle between
// stupidly hardcoding and having a real layout system.
//
// DEFINES:
// RLAY_NO_STATIC -- If defined, all of the procedures are no longer static.
// RLAY_IMPLEMENTATION -- If defined, includes implementation of the api.
//
// API:
// rlay_init(): Creates new Rectange.
// rlay_hidden(): Returns true if rectange is negative.
// rlay_points(): Converts x,y,w,h repesentation into array of points.
// rlay_inside(): Is coordinate inside of rectangle.
//
// rlay_pad(): Pads the rectangle on all four sides.
//
// rlay_vsplit(): Split by vertical line with bias to the left one.
// rlay_hsplit(): Split by horizontal line with bias to the top one.
//
// rlay_vsplit_size(): Split vertically N times with minimal size of M.
// rlay_hsplit_size(): Split horizontally N times with minimal size of M.
//
// rlay_vsplit_count(): Returns the verical split count.
// rlay_hsplit_count(): Returns the horizontal split count.
//
// Example 1:
// Spliting screen vertically by half and then adding uniform pad of 10 pixels.
``
{
    Rlay_Rect rr, l, r;
    rr = rlay_init(0, 0, window_width, window_height);

    l = rlay_vsplit(1, 2, rr, rlay_false);
    r = rlay_vsplit(1, 2, rr, rlay_true);

    l = rlay_pad(10, 10, 5, 10, l);
    r = rlay_pad(5, 10, 10, 10, r);

    example_rect_render(rlay_points(l));
    example_rect_render(rlay_points(r));
}
``
// 
// Example 2:
// Splitting screen horizontally by 100 px elements:
``
{
    Rlay_Rect rr, curr;
    int i;

    rr = rlay_init(0, 0, window_width, window_height);
    for (i = 0; rlay_hsplit_size(i, 100, rr, &curr); i++) {
        example_rect_render(rlay_points(curr));
    }
}
``
//
// CHANGELOG:
// v1.0.1: 21 July 2026 -- Changing behaviour for last index in list, It was
//         returning one more of rectangles that needed (I thought it would be
//         intentional but it doens't make sense) (rlay_hsplit_size/rlay_vsplit_size).
// v1.0.0: 21 July 2026 -- Initial. @Nonsensayer
``

-------------------------------- L I C E N S E --------------------------------

  Copyright (C) 2026 Nonsensayer

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

-------------------------------------------------------------------------------
*/

#if !defined(rlay_s32)
#   include <stdint.h>
#   define rlay_u32 uint32_t
#   define rlay_s32 int32_t
#   define rlay_b32 int32_t
#   define rlay_true 1
#   define rlay_false 0
#endif // rlay_s32

#if !defined(RLAY_assert)
#   include <assert.h>
#   if defined(NDEBUG)
#       define RLAY_assert(expr) assert(expr)
#else
#       define RLAY_assert(expr) (void)(0)
#   endif
#endif // RLAY_assert

#if !defined(RLAY_NO_STATIC)
#   define RLAY_API static
#else
#   define RLAY_API
#endif // RLAY_NO_STATIC

#if defined(__cplusplus)
#   define RLAY_LIT(type) type
#else
#   define RLAY_LIT(type) (type)
#endif // __cplusplus

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

typedef rlay_u32 Rlay_Point;
enum Rlay_Point {
    RLAY_TL = 0,
    RLAY_TR = 1,
    RLAY_BL = 2,
    RLAY_BR = 3,
    RLAY_COUNT
};

typedef struct {
    rlay_s32 x, y, w, h;
} Rlay_Rect;

typedef struct {
    rlay_s32 x[RLAY_COUNT];
    rlay_s32 y[RLAY_COUNT];
} Rlay_Points;

RLAY_API Rlay_Rect   rlay_init(rlay_s32 x, rlay_s32 y, rlay_s32 w, rlay_s32 h);
RLAY_API rlay_b32    rlay_hidden(Rlay_Rect rect);
RLAY_API rlay_b32    rlay_inside(rlay_s32 x, rlay_s32 y, Rlay_Rect rect);
RLAY_API Rlay_Points rlay_points(Rlay_Rect rect);

RLAY_API Rlay_Rect   rlay_pad(rlay_s32 left, rlay_s32 top, rlay_s32 right, rlay_s32 bottom, Rlay_Rect rect);

RLAY_API Rlay_Rect   rlay_vsplit(rlay_s32 bias, rlay_s32 bias_range, Rlay_Rect base, b32 return_second);
RLAY_API Rlay_Rect   rlay_hsplit(rlay_s32 bias, rlay_s32 bias_range, Rlay_Rect base, b32 return_second);

RLAY_API rlay_b32    rlay_vsplit_size(rlay_u32 index, rlay_u32 size, Rlay_Rect base, Rlay_Rect *output);
RLAY_API rlay_b32    rlay_hsplit_size(rlay_u32 index, rlay_s32 size, Rlay_Rect base, Rlay_Rect *output);

RLAY_API rlay_u32    rlay_vsplit_count(rlay_u32 size, Rlay_Rect base);
RLAY_API rlay_b32    rlay_hsplit_count(rlay_u32 size, Rlay_Rect base);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if defined(RLAY_IMPLEMENTATION)

RLAY_API Rlay_Rect rlay_init(rlay_s32 x, rlay_s32 y, rlay_s32 w, rlay_s32 h) {
    return RLAY_LIT(Rlay_Rect) { x, y, w, h };
}

RLAY_API rlay_b32 rlay_hidden(Rlay_Rect rect) {
    return rect.w <= 0 || rect.h <= 0;
}

RLAY_API rlay_b32 rlay_inside(rlay_s32 x, rlay_s32 y, Rlay_Rect rect) {
    if (x < rect.x) return rlay_false;
    if (y < rect.y) return rlay_false;

    if (x >= (rect.x + rect.w)) return rlay_false;
    if (y >= (rect.y + rect.h)) return rlay_false;

    return rlay_true;
}

RLAY_API Rlay_Points rlay_points(Rlay_Rect rect) {
    Rlay_Points rp = { 0 };

    rp.x[RLAY_TL] = rect.x;
    rp.x[RLAY_TR] = rect.x + rect.w;
    rp.x[RLAY_BL] = rect.x;
    rp.x[RLAY_BR] = rect.x + rect.w;

    rp.y[RLAY_TL] = rect.y;
    rp.y[RLAY_TR] = rect.y;
    rp.y[RLAY_BL] = rect.y + rect.h;
    rp.y[RLAY_BR] = rect.y + rect.h;

    return rp;
}

RLAY_API Rlay_Rect rlay_pad(rlay_s32 left, rlay_s32 top, rlay_s32 right, rlay_s32 bottom, Rlay_Rect rect) {
    return rlay_init(rect.x + left, rect.y + top, rect.w - left - right, rect.h - top - bottom);
}

RLAY_API Rlay_Rect rlay_vsplit(rlay_s32 bias, rlay_s32 bias_range, Rlay_Rect base, b32 return_second) {
    rlay_s32 first, second;

    RLAY_assert(bias >= 0);
    RLAY_assert(bias_range > 0);

    first  = (base.w * bias) / bias_range;
    second = (base.w * (bias_range - bias)) / bias_range;

    if (return_second) return rlay_init(base.x + first, base.y, second, base.h);
    else               return rlay_init(base.x, base.y, first, base.h);
}

RLAY_API Rlay_Rect rlay_hsplit(rlay_s32 bias, rlay_s32 bias_range, Rlay_Rect base, b32 return_second) {
    rlay_s32 first, second;

    RLAY_assert(bias >= 0);
    RLAY_assert(bias_range > 0);

    first  = (base.h * bias) / bias_range;
    second = (base.h * (bias_range - bias)) / bias_range;

    if (return_second) return rlay_init(base.x, base.y + first, base.w, second);
    else               return rlay_init(base.x, base.y, base.w, first);
}

RLAY_API rlay_b32 rlay_vsplit_size(rlay_u32 index, rlay_u32 size, Rlay_Rect base, Rlay_Rect *output) {
    rlay_s32 begin, end;
    rlay_u32 divisions;

    RLAY_assert(size > 0);
    divisions = base.w / size;
    if (divisions == 0) divisions = 1;

    begin = (base.w * index) / divisions;
    end = (base.w * (index + 1)) / divisions;

    if (index >= divisions) return rlay_false;

    *output = rlay_init(base.x + begin, base.y, end - begin, base.h);
    return rlay_true;
}

RLAY_API rlay_b32 rlay_hsplit_size(rlay_u32 index, rlay_s32 size, Rlay_Rect base, Rlay_Rect *output) {
    rlay_s32 begin, end;
    rlay_u32 divisions;

    RLAY_assert(size > 0);
    divisions = base.h / size;
    if (divisions == 0) divisions = 1;

    begin = (base.h * index) / divisions;
    end = (base.h * (index + 1)) / divisions;

    if (index >= divisions) return rlay_false;

    *output = rlay_init(base.x, base.y + begin, base.w, end - begin);
    return rlay_true;
}

RLAY_API rlay_u32 rlay_vsplit_count(rlay_u32 size, Rlay_Rect base) {
    rlay_u32 divisions;
    RLAY_assert(size > 0);
    divisions = base.w / size;
    if (divisions == 0) divisions = 1;
    return divisions;
}

RLAY_API rlay_b32 rlay_hsplit_count(rlay_u32 size, Rlay_Rect base) {
    rlay_u32 divisions;
    RLAY_assert(size > 0);
    divisions = base.h / size;
    if (divisions == 0) divisions = 1;
    return divisions;
}

#endif // RLAY_IMPLEMENTATION
#endif // RLAY_H
