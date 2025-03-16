#include <iostream>
#include <portaudio.h>
#include <aubio/aubio.h>
#include <vector>
#include <cmath>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512
#define VOLUME_THRESHOLD 0.015f

aubio_pitch_t* pitchDetector;
fvec_t *inFvec = nullptr;
fvec_t *outFvec = nullptr;

float calculateRMS(const float* buffer, unsigned long framesPerBuffer) {
    float sum = 0.0f;
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        sum += buffer[i] * buffer[i];
    }
    return sqrt(sum / framesPerBuffer);
}

static int audioCallback(const void* inputBuffer, void* outputBuffer,unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,void* userData) {


    if (!inputBuffer)
    return paContinue;
                    
    const float* in = static_cast<const float*>(inputBuffer);

    float volume = calculateRMS(in, framesPerBuffer);

    if (volume < VOLUME_THRESHOLD) {
        return paContinue;
    }

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        fvec_set_sample(inFvec, in[i], i);
    }
    
    
    aubio_pitch_do(pitchDetector, inFvec, outFvec);

    float freq = fvec_get_sample(outFvec, 0);
    if (freq > 0) {
        std::cout << "Detected Pitch: " << freq << " Hz | Volume: " << volume << std::endl;
    }
    
    return paContinue;
}
int main(){
    pitchDetector = new_aubio_pitch("default", FRAMES_PER_BUFFER, FRAMES_PER_BUFFER, SAMPLE_RATE);
    inFvec  = new_fvec(FRAMES_PER_BUFFER);
    outFvec = new_fvec(1);

    Pa_Initialize();

    PaStream* stream;
    Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallback, nullptr);
    Pa_StartStream(stream);

    std::cout << "Recording... Press Enter to stop.\n";
    std::cin.get();
    
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    del_aubio_pitch(pitchDetector);
    del_fvec(inFvec);
    del_fvec(outFvec);
    
    return 0;
}