/* main.c */
#include <stdio.h>
#include <string.h>
#include "portaudio.h"
#include "fir.h"

#define SAMPLE_RATE 48000
#define NUM_SECONDS 9
/* Switch between filters every 3 seconds */
#define SWITCH_NUM (NUM_SECONDS * SAMPLE_RATE / 3.0)

static int callback(const void *input, void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    static unsigned long long num_calls = 0;
    int i;
    float *in = (float*)input;
    float *out = (float*)output;

    num_calls += frameCount;

    if(num_calls < SWITCH_NUM)
    {
        return fir_process(input, output, frameCount, 0);
    }
    else if(num_calls > SWITCH_NUM && num_calls < 2*SWITCH_NUM)
    {
        return fir_process(input, output, frameCount, 1);
    }
    else
    {
        return fir_process(input, output, frameCount, 2);
    }
}

int main(int argc, char *argv[])
{   
    PaStream *stream;
    PaError err;

    fir_init();

    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, 48000, 256, callback, NULL);
    Pa_StartStream(stream);
    Pa_Sleep(NUM_SECONDS * 1000);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    fir_destroy();

    return 0;    
}
