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


#include "fische_internal.h"

#include <string.h>

#if defined(__x86_64__)

void
_fische__host_get_cpuid_ (uint32_t t, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx)
{
    asm ("pushq %%rbx\n\t"
         "movl %%esi, %%ebx\n\t"
         "cpuid\n\t"
         "movl %%ebx, %%esi\n\t"
         "popq %%rbx"
         : "=a" (*eax)
         , "=S" (*ebx)
         , "=c" (*ecx)
         , "=d" (*edx)
         : "a" (t)
         , "c" (0)
         , "S" (0)
         , "d" (0));
}

#elif defined(__i386__)

void
_fische__host_get_cpuid_ (uint32_t t, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx)
{
    asm ("pushl %%ebx\n\t"
         "movl %%esi, %%ebx\n\t"
         "cpuid\n\t"
         "movl %%ebx, %%esi\n\t"
         "popl %%ebx"
         : "=a" (*eax)
         , "=S" (*ebx)
         , "=c" (*ecx)
         , "=d" (*edx)
         : "a" (t)
         , "c" (0)
         , "S" (0)
         , "d" (0));
}

#endif

uint_fast8_t
_fische__cpu_detect_()
{

#if defined(__i386__) || defined(__x86_64__)
    int n = 1;
    uint32_t eax, ebx, ecx, edx;
    _fische__host_get_cpuid_ (0x0, &eax, &ebx, &ecx, &edx);

    char cpuid[13];
    memcpy (cpuid, &ebx, 4);
    memcpy (cpuid + 4, &edx, 4);
    memcpy (cpuid + 8, &ecx, 4);
    cpuid[12] = '\0';

    if (!strcmp (cpuid, "AuthenticAMD")) {
        _fische__host_get_cpuid_ (0x80000000, &eax, &ebx, &ecx, &edx);
        if (eax < 0x80000008) return 1;
        _fische__host_get_cpuid_ (0x80000008, &eax, &ebx, &ecx, &edx);
        n = (ecx & 0xff) + 1;

    } else { /* if it's not AMD, it's most likely Intel */
        _fische__host_get_cpuid_ (0x00000000, &eax, &ebx, &ecx, &edx);
        if (eax < 4) return 1;
        _fische__host_get_cpuid_ (0x4, &eax, &ebx, &ecx, &edx);
        n = (eax >> 26) + 1;
    }

    return n;

#else /* don't have cpuid */
    return 1;
#endif
}
