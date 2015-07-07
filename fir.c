/* fir.c */
#include <string.h>
#include "fir.h"

#define NUM_TAPS 512

static double circular_buffer[NUM_TAPS];
static const double taps[NUM_TAPS] = {
    0.00212772,  0.0022048 ,  0.00240508,  0.00272921,  0.00317643,
    0.00374454,  0.00442991,  0.00522754,  0.00613105,  0.00713279,
    0.00822388,  0.00939434,  0.01063316,  0.01192843,  0.01326749,
    0.01463704,  0.01602331,  0.01741222,  0.01878951,  0.02014096,
    0.02145249,  0.02271036,  0.02390133,  0.02501279,  0.02603293,
    0.02695089,  0.02775685,  0.02844218,  0.02899951,  0.02942284,
    0.02970763,  0.0298508 ,  0.0298508 ,  0.02970763,  0.02942284,
    0.02899951,  0.02844218,  0.02775685,  0.02695089,  0.02603293,
    0.02501279,  0.02390133,  0.02271036,  0.02145249,  0.02014096,
    0.01878951,  0.01741222,  0.01602331,  0.01463704,  0.01326749,
    0.01192843,  0.01063316,  0.00939434,  0.00822388,  0.00713279,
    0.00613105,  0.00522754,  0.00442991,  0.00374454,  0.00317643,
    0.00272921,  0.00240508,  0.0022048 ,  0.00212772
};
static void circular_buffer_insert(const double input);
static double circular_buffer_shift();


void fir_init()
{
    memset(circular_buffer, 0.0f, sizeof(double) * NUM_TAPS);
}

int fir_process(const void* input, void *output, unsigned long numFrames)
{
    unsigned long i;
    double *out = (double *)output, *in = (double *)input;

    for(i = 0; i < numFrames; ++i)
    {
        *out++ = circular_buffer_shift();
        circular_buffer_insert(*in++);
    }

    return 0;
}

void fir_destroy()
{
    /* No mallocs yet */
    return;
}

static void circular_buffer_insert(const double input)
{
    circular_buffer[0] = input * taps[0];
}

static double circular_buffer_shift()
{
    double ret = circular_buffer[NUM_TAPS - 1];
    unsigned long i;

    for(i = 0; i < NUM_TAPS - 1; ++i)
    {
        circular_buffer[i+1] = circular_buffer[i] * taps[i + 1];
    }

    return ret;
}
