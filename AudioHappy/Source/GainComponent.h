/*
  ==============================================================================

    GainComponent.h
    Created: 11 May 2022 9:19:35pm
    Author:  Brian Mendoza

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DecibelSlider : public juce::Slider
{
public:
    //Constructor
    DecibelSlider() {};
    
    //Override the virtual function
    double getValueFromText (const juce::String &txt) override
    {
        auto minusInfdB = -100.0f;
        auto decibelText = txt.upToFirstOccurrenceOf ("dB", false, false).trim();   //function from juce::String I think
        
        return decibelText.equalsIgnoreCase("-INF") ? minusInfdB : decibelText.getDoubleValue();
    }
    
    juce::String getTextFromValue (double value) override
    {
        return juce::Decibels::toString(value);
    }
};

class GainComponent : public juce::Component,
                      public juce::Slider::Listener
{
public:
    GainComponent();
    ~GainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**From Tutorial "JUCE (5) Tutorial 05 - The Slider, Slider Listener & Label classes, a pure virtual functions needs to be  override */
    void sliderValueChanged (juce::Slider* slider) override
    {
        juce::String msg;     //To log a message in the console
        double tempValue;
        
        if(slider == &gainSlider)
        {
            /**Commented code to log the value */
            /* tempValue = 10.0 * log(gainSlider.getValue() );
            msg << tempValue << "\n";
            juce::Logger::getCurrentLogger()->writeToLog(msg); */
            decibelSlider.setValue( 10.0f * log(gainSlider.getValue()) );
        }
        else if(slider == &decibelSlider)
        {
            /**Commented code to log the value in console */
            /*
            */
            tempValue = juce::Decibels::decibelsToGain( (float)decibelSlider.getValue() );
            msg << tempValue << "\n";
            juce::Logger::getCurrentLogger()->writeToLog(msg);
            //gainSlider.setValue( tempValue );
        }
    }
    
    /**Combining the tutorial, let connect a Slider within the component with the output in the audio*/
    juce::Slider gainSlider;
    /**Create a label*/
    juce::Label gainLabel;
    
    /**Lets create two objects.
     Goals 1: a Decibel slider.
     Golas 2: connect with the listener both sliders */
    DecibelSlider decibelSlider;
    juce::Label decibelLabel;
    float levelSlider = 0.0f;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComponent)
};
