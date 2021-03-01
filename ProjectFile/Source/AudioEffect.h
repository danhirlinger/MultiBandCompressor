/*
  ==============================================================================

    AudioEffect.h
    Created: 25 Feb 2021 2:44:33pm
    Author:  Dan Hirlinger

  ==============================================================================
*/

#pragma once

// Base  class for general audio effect

class AudioEffect{

public:
    
    float processSample(float x);
    
    void prepare(float newFs);
    
    
private:
    float Fs;
    
};
