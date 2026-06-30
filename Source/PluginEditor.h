/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Adelay_JUCEAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Adelay_JUCEAudioProcessorEditor (Adelay_JUCEAudioProcessor&);
    ~Adelay_JUCEAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Adelay_JUCEAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Adelay_JUCEAudioProcessorEditor)
};
