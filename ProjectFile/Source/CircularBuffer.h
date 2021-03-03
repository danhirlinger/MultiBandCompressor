/*
  ==============================================================================

    CilcularBuffer.h
    Created: 3 Mar 2021 8:10:06am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class circularBuffer{
    
public:
    
    circularBuffer();
    circularBuffer(int bufferSize, int delayLength);
    
    float getData();
    void setData(float data);
    void movePointer();
    
    
private:
    
    static const int bufferSize = 96000;
    float w[2][bufferSize] = {0.f};
    int writeIndex[2] = {47999,47999};
    
    
    int writeIndex2;
    int readIndex;
    int delayLength;
    
    juce::AudioSampleBuffer buffer;
    
};
