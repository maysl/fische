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


#ifndef WAVEPAINTER_H
#define WAVEPAINTER_H

#include <stdint.h>

struct fische;
struct _fische__wavepainter_;
struct fische__wavepainter;



struct fische__wavepainter* fische__wavepainter_new (struct fische* parent);
void                        fische__wavepainter_free (struct fische__wavepainter* self);

void                        fische__wavepainter_paint (struct fische__wavepainter* self, double* data, uint_fast16_t size);
void                        fische__wavepainter_beat (struct fische__wavepainter* self, double bpm);
void                        fische__wavepainter_change_color (struct fische__wavepainter* self, double bpm, double energy);
void                        fische__wavepainter_change_shape (struct fische__wavepainter* self);



struct _fische__wavepainter_ {
    uint_fast16_t   width;
    uint_fast16_t   height;
    uint_fast16_t   center_x;
    uint_fast16_t   center_y;
    int_fast8_t     direction;
    uint_fast8_t    shape;
    uint_fast8_t    n_shapes;
    uint32_t        color_1;
    uint32_t        color_2;
    double          angle;
    uint_fast8_t    is_rotating;
    double          rotation_increment;

    struct fische* fische;
};

struct fische__wavepainter {
    struct _fische__wavepainter_* priv;
};

#endif
