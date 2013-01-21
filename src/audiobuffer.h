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


#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <stdint.h>

struct fische;
struct _fische__audiobuffer_;
struct fische__audiobuffer;



struct fische__audiobuffer* fische__audiobuffer_new (struct fische* parent);
void                        fische__audiobuffer_free (struct fische__audiobuffer* self);

void                        fische__audiobuffer_insert (struct fische__audiobuffer* self, const void* data, uint_fast32_t size);
void                        fische__audiobuffer_lock (struct fische__audiobuffer* self);
void                        fische__audiobuffer_unlock (struct fische__audiobuffer* self);
void                        fische__audiobuffer_get (struct fische__audiobuffer* self);



struct _fische__audiobuffer_ {
    double*         buffer;
    uint_fast32_t   buffer_size;
    uint_fast8_t    format;
    uint_fast8_t    is_locked;
    uint_fast32_t   puts;
    uint_fast32_t   gets;
    uint_fast32_t   last_get;

    struct fische*    fische;
};

struct fische__audiobuffer {
    double* front_samples;
    uint_fast16_t front_sample_count;
    double* back_samples;
    uint_fast16_t back_sample_count;

    struct _fische__audiobuffer_* priv;
};

#endif
