/*
  ==============================================================================

    Compressor.h
    Created: 16 Feb 2021 9:27:51am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#pragma once
#include "AudioEffect.h"
// derived class from AudioEffect


class Compressor : public AudioEffect
{
public:
    Compressor();
    float compressSample(float data, float thresh, float ratio, float attack, float release, float knee);
    void setCompressorThresh(float newThresh);
    
private:
    
    float thresh = 0.f;
//    CircularBuffer buffer; need to learn about this
    float tav;
    float rms;
    float gain;
};
