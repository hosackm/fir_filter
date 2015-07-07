/* main.c */
#include <stdio.h>
#include "portaudio.h"
#include "fir.h"

static int callback(const void *input, void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    int i;
    double *in = (double*)input, *out = (double*)output;

    return fir_process(input, output, frameCount);
}

int main(int argc, char *argv[])
{
    PaStream *stream;
    PaError err;

    fir_init();

    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, 48000, 256, callback, NULL);
    Pa_StartStream(stream);
    Pa_Sleep(5000);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    fir_destroy();

    return 0;    
}
