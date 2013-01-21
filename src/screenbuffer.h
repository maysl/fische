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


#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <stdint.h>

struct fische;
struct _fische__screenbuffer;
struct fische__screenbuffer;



struct fische__screenbuffer*    fische__screenbuffer_new (struct fische* parent);
void                            fische__screenbuffer_free (struct fische__screenbuffer* self);

void                            fische__screenbuffer_lock (struct fische__screenbuffer* self);
void                            fische__screenbuffer_unlock (struct fische__screenbuffer* self);

void fische__screenbuffer_line (struct fische__screenbuffer* self,
                                int_fast16_t x1,
                                int_fast16_t y1,
                                int_fast16_t x2,
                                int_fast16_t y2,
                                uint32_t color);



struct _fische__screenbuffer_ {
    uint_fast8_t        is_locked;
    int_fast16_t        width;
    int_fast16_t        height;
    uint_fast8_t        red_shift;
    uint_fast8_t        blue_shift;
    uint_fast8_t        green_shift;
    uint_fast8_t        alpha_shift;

    struct fische*    fische;
};

struct fische__screenbuffer {
    uint32_t*       pixels;

    struct _fische__screenbuffer_* priv;
};

#endif
