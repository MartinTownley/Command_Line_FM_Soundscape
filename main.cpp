//Student 33537140
//Advanced Audiovisual Processing Portfolio, part 1
//FM Soundscape

//INSTRUCTIONS: Easiest launch is from the command line – cd into the project folder, and type "./run.sh"

//DESCRIPTION:
// A carrier wave is being modulated by a modulator, whose frequency is the carrier frequency * the harmonicity Ratio.
// The amplitude of this modulator is determined by a very low frequency phasor, which in turn has its own amplitude.
// The harmonicity ratio remains static, but for every half cycle of the modulating phasor, the carrier frequency switches between 118 and 1072, and the amplitude of the phasor switches between 200 and 100. These are values I found through experimentation in Max/MSP.
// My intention was to create a rich FM soundscape using a very limited amount of elements, and to practice using Max/MSP as a sound design prototyping tool.

#include "maximilian.h"
//OSCILLATORS
maxiOsc carrier, modulator0, modulator1, sineTime, myCounter;

//FILTER
maxiFilter myFilter;

//OUTPUTS
double myOscOutput, myFilteredOutput;

//TIMING
int currentCount;

//OSCILLATOR VALUES
double carrierFreq = 118 ;

double harmRatio;

double mod0freq;

double mod1freq = 0.04;

double mod1amp = 200 ;

//RECORD
double out;

maxiRecorder recorder; //used for recording output

void setup() {
 
    harmRatio = 32; //sets the harmonicity ratio

//RECORD
    recorder.setup("recording.wav");
    
    recorder.startRecording();
   
}

void play(double *output) {
    
    
    currentCount = myCounter.phasor(0.02, 1, 9);
    
    mod0freq =  carrierFreq * harmRatio;
    
    
//If statements are used to progress the piece - it has two sections
    if (currentCount < 5)
    {
        carrierFreq = 118;
        mod1amp = 200;
    } else if (currentCount >= 5)
    {
        carrierFreq = 1072;
        mod1amp = 100;
    }
//Here is where the FM synthesis happens:
    
    
    myOscOutput = carrier.sinewave(carrierFreq
                  + ((modulator0.sinewave(mod0freq))
                  * (mod0freq
                  * ((modulator1.phasor(mod1freq)
                  * mod1amp))) ));
    
    
    myFilteredOutput = myFilter.lores(myOscOutput, 2000, 0); //filter the output to eliminate harsh high-pitched sounds
    
    output[0]=myFilteredOutput;
    
    output[0]=output[0] * 0.6; //amplifier at the end
    output[1]=output[0];
    
    //Uncomment the recorder below to create a .WAV file recording
    recorder.passData(output, maxiSettings::channels);
    
}


