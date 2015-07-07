/* fir.c */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fir.h"

#define NUM_TAPS 63
#define BUF_SIZE 512

static float insamp[BUF_SIZE];
/* coefficients stored in taps.c */
extern const float lowpass[NUM_TAPS];
extern const float bandpass[NUM_TAPS];
extern const float highpass[NUM_TAPS];

void fir_init()
{
    memset(&insamp[0], 0.0f, sizeof(float) * BUF_SIZE);
}

int fir_process(const void* input, void *output, unsigned long numFrames, unsigned int filter)
{
    float acc; // accumulator for MACs
    const float *coeffp; // pointer to coefficients
    const float *in = (float*)input;
    float *out = (float *)output;
    unsigned int n;
    unsigned int k;
 
    // put the new samples at the high end of the buffer
    memcpy(&insamp[NUM_TAPS - 1], input, sizeof(float) * numFrames);
 
    // convolve input samples with filter taps
    for (n = 0; n < numFrames; ++n) {
        switch(filter)
        {
            case 0:
            coeffp = &lowpass[0];
            break;
            case 1:
            coeffp = &bandpass[0];
            break;
            default:
            case 2:
            coeffp = &highpass[0];
            break;
        }

        in = &insamp[NUM_TAPS - 1 + n];
        acc = 0;
        
        for (k = 0; k < NUM_TAPS; ++k) {
            acc += (*coeffp++) * (*in--);
        }
        
        *out++ = acc;
    }
    
    // shift input samples back in time for next time
    memmove(&insamp[0], &insamp[numFrames], sizeof(float) * (NUM_TAPS - 1));

    return 0;
} 

void fir_destroy()
{
    /* No mallocs yet */
    return;
}
