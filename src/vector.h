/***************************************************************
 * Copyright (C) 2013 Marcel Ebmer
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documen-
 * tation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **************************************************************/


#ifndef F_VECTOR_H
#define F_VECTOR_H

#include <math.h>
#include <stdint.h>

struct _fische__vector_ {
    double x;
    double y;
};

typedef struct _fische__vector_ fische__vector;
typedef struct _fische__vector_ fische__point;

enum {_FISCHE__VECTOR_LEFT_, _FISCHE__VECTOR_RIGHT_};

double          fische__vector_length (fische__vector* self);
fische__vector  fische__vector_normal (fische__vector* self);
fische__vector  fische__vector_single (fische__vector* self);
double          fische__vector_angle (fische__vector* self);
uint16_t        fische__vector_to_uint16 (fische__vector* self);
fische__vector  fische__vector_from_uint16 (uint16_t val);
void            fische__vector_add (fische__vector* self, fische__vector* other);
void            fische__vector_sub (fische__vector* self, fische__vector* other);
void            fische__vector_mul (fische__vector* self, double val);
void            fische__vector_div (fische__vector* self, double val);

fische__vector  fische__vector_intersect_border (fische__vector* self,
        fische__vector* normal_vec,
        uint_fast16_t width,
        uint_fast16_t height,
        int_fast8_t direction);

#endif
