/*
  ==============================================================================

    MultiBand.cpp
    Created: 16 Feb 2021 9:28:14am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#include "MultiBandComp.h"

MultiBandComp::MultiBandComp(){
    
    
}


void MultiBandComp::processBlock(juce::AudioBuffer<float> &buffer){
    // pass in buffer
    
    // run splitBlock() to get individual buffers of L,M,H
    
    // processBand() 3 times for each band
    // processBand()
    // processBand()
    
    // rebuildBlock();
    
}

void MultiBandComp::splitBlock(){
    
    // take buffer and split based on input parameter(?)
    
}

void MultiBandComp::processBand(){
    
    // process band based on respective compressor parameters
}

void MultiBandComp::rebuildBlock(){

    // combine together processed bands into an audioBlock
}

float MultiBandComp::getMeterVals(juce::AudioBuffer<float> &buffer, int c, int n, const int N){
    
//    for (int n = 0; n < N; n++){
        float x = buffer.getReadPointer(c)[n];
        meterVals = vuAnalysis.processSample(x,c);
        return meterVals;
//    }
    
    // obtain values of buffer for the meter
    // need for meters of L,M,H, and overall
    
}


