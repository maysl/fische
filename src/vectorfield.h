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


#ifndef VECTORFIELD_H
#define VECTORFIELD_H

#include <stdint.h>

struct fische;
struct _fische__vectorfield_;
struct fische__vectorfield;



struct fische__vectorfield* fische__vectorfield_new (struct fische* parent, double* progress, uint_fast8_t* cancel);
void                        fische__vectorfield_free (struct fische__vectorfield* self);

void                        fische__vectorfield_change (struct fische__vectorfield* self);



struct _fische__vectorfield_ {
    uint16_t*	        fields;
    uint_fast32_t       fieldsize;
    uint_fast16_t       width;
    uint_fast16_t       height;
    uint_fast16_t       dimension;
    uint_fast16_t       center_x;
    uint_fast16_t       center_y;
    uint_fast8_t        threads;
    uint_fast8_t        n_fields;
    uint_fast8_t        cancelled;

    struct fische*    fische;
};



struct fische__vectorfield {
    uint16_t* field;

    struct _fische__vectorfield_* priv;
};

#endif
