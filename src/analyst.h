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


#ifndef ANALYST_H
#define ANALYST_H

#include <stdint.h>

struct fische;
struct _fische__analyst_;
struct fische__analyst;



struct fische__analyst* fische__analyst_new (struct fische* parent);
void                    fische__analyst_free (struct fische__analyst* self);

int_fast8_t             fische__analyst_analyse (struct fische__analyst* self, double* data, uint_fast16_t size);



struct _fische__analyst_ {
    uint_fast8_t    state;
    double          moving_avg_30;
    double          moving_avg_03;
    double          std_dev;
    double          intensity_moving_avg;
    double          intensity_std_dev;
    uint_fast32_t   last_beat_frame;
    uint_fast16_t*  beat_gap_history;
    uint_fast8_t    bghist_head;

    struct fische*    fische;
};

struct fische__analyst {
    double relative_energy;
    double frames_per_beat;

    struct _fische__analyst_* priv;
};

#endif
