/*
  ==============================================================================

    GainComponent.cpp
    Created: 11 May 2022 9:19:35pm
    Author:  Brian Mendoza

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainComponent.h"

//==============================================================================
GainComponent::GainComponent()
{
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gainSlider.setRange(0.0, 0.25);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    gainSlider.setValue(0.1f);
    gainLabel.setText("Noise Level!", juce::dontSendNotification);
    
    /**Create the decibel Slider with the class created in the header */
    decibelSlider.setRange(-100, -12);
    decibelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    /**The lambda function that I dont get yet */
    //decibelSlider.onValueChange = [this] { levelSlider = juce::Decibels::decibelsToGain( (float)decibelSlider.getValue() ); };
    decibelSlider.setValue(juce::Decibels::gainToDecibels( gainSlider.getValue() ));
    decibelLabel.setText("Noise Level in dB", juce::dontSendNotification);
    
    /**To add these listeners below, we had to add "public juce:Slider::Listener in the .h class and override the virtualfunction "SliderValueChanged()*/
    gainSlider.addListener(this);
    decibelSlider.addListener(this);
    
    addAndMakeVisible(decibelSlider);
    addAndMakeVisible(decibelLabel);
    
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(gainSlider);
}

GainComponent::~GainComponent()
{
}

void GainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void GainComponent::resized()
{
    gainSlider.setBounds(20, 20, 300, 300);
    gainLabel.setBounds(130, 330, 80, 20);
    
    decibelSlider.setBounds(20, 360, 360, 30);
    decibelLabel.setBounds(30, 390, 120, 20);
}
