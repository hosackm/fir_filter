/* fir.h */
#ifndef __FIR_FILT_H__
#define __FIR_FILT_H__

void fir_init();
int fir_process(const void* input, void *output, unsigned long numFrames);
void fir_destroy();

#endif