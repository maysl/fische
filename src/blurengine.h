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


#ifndef BLURENGINE_H
#define BLURENGINE_H

#include <stdint.h>
#include <pthread.h>

struct fische;

struct _fische__blurworker_;
struct _fische__blurengine_;
struct fische__blurengine;



struct fische__blurengine*  fische__blurengine_new (struct fische* parent);
void                        fische__blurengine_free (struct fische__blurengine* self);

void                        fische__blurengine_blur (struct fische__blurengine* self, uint16_t* vectors);
void                        fische__blurengine_swapbuffers (struct fische__blurengine* self);



struct _fische__blurworker_ {
    pthread_t       thread_id;
    uint32_t*       source;
    uint32_t*       destination;
    uint_fast16_t   width;
    uint_fast16_t   y_start;
    uint_fast16_t   y_end;
    uint16_t*       vectors;
    uint_fast8_t    work;
    uint_fast8_t    kill;
};

struct _fische__blurengine_ {
    int_fast16_t        width;
    int_fast16_t        height;
    uint_fast8_t        threads;
    uint32_t*           sourcebuffer;
    uint32_t*           destinationbuffer;

    struct _fische__blurworker_ worker[8];

    struct fische*    fische;
};

struct fische__blurengine {
    struct _fische__blurengine_* priv;
};

#endif
