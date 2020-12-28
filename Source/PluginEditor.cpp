/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Panner01AudioProcessorEditor::Panner01AudioProcessorEditor (Panner01AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (350, 100);
    
    
    mTimeSlider.setRange(1.f, 10000.f, 0.1f);
    mTimeSlider.setValue(100.f);
    mTimeSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    mTimeSlider.addListener(this);
    addAndMakeVisible(mTimeSlider);
}

Panner01AudioProcessorEditor::~Panner01AudioProcessorEditor()
{
}

//==============================================================================
void Panner01AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::darkslategrey);
    g.drawText("Time", ((getWidth() / 2) * 1) - (40), (getHeight() / 2) - 40, 100, 100, Justification::left, false);
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::lightslategrey);
    getLookAndFeel().setColour (juce::Slider::textBoxTextColourId, juce::Colours::lightslategrey);
}

void Panner01AudioProcessorEditor::resized()
{
    mTimeSlider.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 175, 300, 350);
}

void Panner01AudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    auto& params = processor.getParameters();
    
    if (slider == &mTimeSlider)
    {
        AudioParameterFloat* timeParameter = (AudioParameterFloat*)params.getUnchecked(0);
        *timeParameter = mTimeSlider.getValue();
    }
}
