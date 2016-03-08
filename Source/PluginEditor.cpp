/*
  ==============================================================================

  This file was auto-generated by the Introjucer!

  It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Grnlr_kleinAudioProcessorEditor::Grnlr_kleinAudioProcessorEditor (Grnlr_kleinAudioProcessor& p)
  : AudioProcessorEditor (&p), processor (p)
{
  addAndMakeVisible(openButton);
  openButton.setButtonText("Open...");
  openButton.addListener(this);
  
  addAndMakeVisible(clearButton);
  clearButton.setButtonText("clear");
  clearButton.addListener(this);
  
  addAndMakeVisible(lengthSlider);
  lengthSlider.setRange(0.0, 0.3);
  lengthSlider.addListener(this);
  
  addAndMakeVisible(positionSlider);
  positionSlider.setRange(0.0, 1.0);
  positionSlider.addListener(this);
  
  formatManager.registerBasicFormats();
  
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize (400, 300);
}

Grnlr_kleinAudioProcessorEditor::~Grnlr_kleinAudioProcessorEditor()
{
}

//==============================================================================
void Grnlr_kleinAudioProcessorEditor::paint (Graphics& g)
{
  g.fillAll (Colours::white);
}

void Grnlr_kleinAudioProcessorEditor::resized()
{
  int width = getWidth() - 20;
  openButton.setBounds(10, 10, width, 20);
  clearButton.setBounds(10, 40, width, 20);

  lengthSlider.setBounds(10, 90, width, 40);
  positionSlider.setBounds(10, 150, width, 40);
}

void Grnlr_kleinAudioProcessorEditor::buttonClicked (Button* button)
{
  if(button == &openButton) openButtonClicked();
  if(button == &clearButton) clearButtonClicked();
}

void Grnlr_kleinAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
  if(slider == &lengthSlider)
    processor.lengthRatio = (float) lengthSlider.getValue();
  if(slider == &positionSlider)
    processor.positionOffset = (float) positionSlider.getValue();
}

void Grnlr_kleinAudioProcessorEditor::openButtonClicked()
{  
  FileChooser chooser ("Select a Wave file...",
		       File::nonexistent,
		       "*.wav");
  if (chooser.browseForFileToOpen() ) {
    const File file (chooser.getResult());
    
    ScopedPointer<AudioFormatReader> reader(formatManager.createReaderFor(file));
    
    if (reader != nullptr) {
      const double duration = reader->lengthInSamples / reader->sampleRate;
      
      if(duration < 5){
      processor.fileBuffer.setSize(reader->numChannels, reader->lengthInSamples);
      reader->read(&processor.fileBuffer, 0, reader->lengthInSamples, 0, true, true);
      
      processor.position = 0;
      //setAudioChannels(0, reader->numChannels); 
      
      // Show some info when loading was succesful
      std::cout << "name: " << file.getFileName()
		<< " duraiton: " << duration << std::endl;
      }
    } else { std::cout << "something went wrong while loading :( " << std::endl; }
  }
}
      
void Grnlr_kleinAudioProcessorEditor::clearButtonClicked()
{
    using namespace std::chrono;
    steady_clock::time_point timeNow = steady_clock::now();
    
    duration<double> time_span = duration_cast<duration<double>>(timeNow - processor.startTime);
    
    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;

}
