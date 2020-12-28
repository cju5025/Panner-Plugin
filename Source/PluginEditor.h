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
class Panner01AudioProcessorEditor  : public juce::AudioProcessorEditor,
public Slider::Listener
{
public:
    Panner01AudioProcessorEditor (Panner01AudioProcessor&);
    ~Panner01AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider* slider) override;

private:
    Panner01AudioProcessor& audioProcessor;
    
    Slider mTimeSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Panner01AudioProcessorEditor)
};
