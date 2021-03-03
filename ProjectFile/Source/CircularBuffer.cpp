/*
  ==============================================================================

    CilcularBuffer.cpp
    Created: 3 Mar 2021 8:10:06am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#include "CircularBuffer.h"


circularBuffer::circularBuffer(){
    
    buffer = juce::AudioSampleBuffer();
    writeIndex2 = 0;
    readIndex = 0;
    delayLength = 0;
}

circularBuffer::circularBuffer(int bufferSize, int delayLength){
    
}

float circularBuffer::getData(){
    return 0.0f;
}

void circularBuffer::setData(float data){
    
}

void circularBuffer::movePointer(){
    
}
