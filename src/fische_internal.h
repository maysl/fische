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


#ifndef FISCHE_INTERNAL_H
#define FISCHE_INTERNAL_H

#include "fische.h"
#include "wavepainter.h"
#include "screenbuffer.h"
#include "analyst.h"
#include "vector.h"
#include "vectorfield.h"
#include "blurengine.h"
#include "audiobuffer.h"

#ifdef WIN32
#define rand_r(_seed) (_seed == _seed ? rand() : rand())
#endif

#define FISCHE_PRIVATE(P) ((struct _fische__internal_*) P->fische->priv)

uint_fast8_t _fische__cpu_detect_();


struct _fische__internal_ {
    struct fische__screenbuffer*    screenbuffer;
    struct fische__wavepainter*     wavepainter;
    struct fische__analyst*         analyst;
    struct fische__blurengine*      blurengine;
    struct fische__vectorfield*     vectorfield;
    struct fische__audiobuffer*     audiobuffer;
    double                          init_progress;
    uint_fast8_t                    init_cancel;
    uint_fast8_t                    audio_valid;
};

#endif
