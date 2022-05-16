#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(gainCustomComp);

    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    /**Here we are printing in the console through custom JUCE function */
    juce::String msg;
    
    /**This value can be set from the component class or here...*/
    //gainCustomComp.gainSlider.setValue(0.1f);
    //gainCustomComp.decibelSlider.setValue(juce::Decibels::gainToDecibels( (float) 0.1f));
    
    msg << "Prepare to play audio...\n";
    msg << "samples per block: " << samplesPerBlockExpected << "\n";
    msg << "Sample Rate: " << sampleRate << "\n\n";
    msg << "Gain: " << gainCustomComp.gainSlider.getValue() << "\n";
    juce::Logger::getCurrentLogger()->writeToLog(msg);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    /**Clear the buffer to avoid random noises */
    bufferToFill.clearActiveBufferRegion();
    
    /**Create the connection between the slider and the volume*/
    auto currentLevel = gainCustomComp.gainSlider.getValue();
    //auto levelScale = currentLevel;
    
    //auto level = (float) gainCustomComp.gainSlider.getValue();
    
    /**The buffer first is set to a local pointer variable. */
    auto* buffer = bufferToFill.buffer;             //This is a container, floating values.
    auto numChannels = buffer->getNumChannels();    //Get the num of channesl
    auto numSamples = buffer->getNumSamples();      //Get the samples used
    
    /**Iterate through both channels*/
    for(auto ch = 0; ch < numChannels; ++ch)
    {
        /**Permission to write information */
        auto* writePointer = buffer->getWritePointer(ch);
        
        for(auto localSample = 0; localSample < numSamples; ++localSample)
        {
            /**This is the pointer where we can write data to the output */
            auto output = randomGen.nextFloat() * currentLevel;
            writePointer[localSample] = output;
        }
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    gainCustomComp.setBounds(10, 10, 780, 580);
}

