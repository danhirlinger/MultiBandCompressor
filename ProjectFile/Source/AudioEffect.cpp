/*
  ==============================================================================

    AudioEffect.cpp
    Created: 25 Feb 2021 2:44:33pm
    Author:  Dan Hirlinger

  ==============================================================================
*/

#include "AudioEffect.h"

float AudioEffect::processSample(float x){
    return x;
}

void AudioEffect::prepare(float newFs){
    Fs = newFs;
}
