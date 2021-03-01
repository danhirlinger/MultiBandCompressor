/*
  ==============================================================================

    Compressor.cpp
    Created: 16 Feb 2021 9:27:51am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#include "Compressor.h"
#include <tgmath.h>


Compressor::Compressor()
{
//    buffer = CircularBuffer(150, 20);
    tav = 0.01;
    rms = 0;
    gain = 1;
    
}

float Compressor::compressSample(float data, float thresh, float ratio, float attack, float release, float knee){
    
    // calculate gain of incoming signal
    rms = (1- tav) * rms + tav * pow(data, 2.0f); // adjusts rms value depending on incoming signal
    float dbRMS = 10 * log10(rms); // converts above value to decibel scale
    
    // calculate desired gain reduction
    float slope = 1 - (1/ratio); // calculate slope from ratio
    float dbGain = fmin(0.0f, (slope * (thresh - dbRMS))); // find gain to be applied in dB; make sure it's less than 0.0f
    float newGain = pow(10, dbGain / 20); // calculate newGain in linear scale
    
    // smooth the gain transition
    float coeff;
    if (newGain < gain) coeff = attack; //  if ... then set coeff to the attack variable
    else coeff = release; // else set to release
    gain = (1 - coeff) * gain + coeff * newGain; // adjust gain based on new gain, coeff
    
//    float compressSample = gain * buffer.getData();
//    buffer.setData(data);
//    buffer.nextSample();
//    return compressSample;
    return 0.0f;
}



//void Compressor::setCompressorThresh(float newThresh){
//    thresh = newThresh;
//}


