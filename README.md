## "MEGA_FM"

### A C++ / Synthesis Toolkit / Qt5 FM synthesizer + sequencer

![Image of program running](./images/mega_fm.jpg)

#### Features:
- Tone generator:
  - 8 voices of 2 operator FM
- Sequencer:
  - 8 patterns
  - 32 steps
  - Parameters for steps 1 9 17 25, 2 10 18 26, etc. are the same, so in effect you have an eight step pattern with some added variety through the 32 trig switches
- Reverb:
  - Mono reverb

See it in action on YouTube: [Example 1](https://youtu.be/nPyFqWjyMAo ) [Example 2](https://youtu.be/j0YUTtWCITk)

#### Controls:

Each of the 8 voices has:
- **Pitch** sets the base pitch for the oscillators
- **Ramp** sets the pitch envelope amount. The envelope is a simple decay envelope, always starting at max value
- **Decay (blue)** sets the pitch envelope decay time
- **FM** sets the amount of modulation from oscillator 2 to oscillator 1
- **Freq** sets the frequency of oscillator 2 relative to the base pitch
- **Decay (pink)** sets the decay of the modulation amount so that short decay only allows for modulation on the beginning of the sound
- **FB** sets the amount by which oscillator 2 modulates itself. High amounts of FB produce noise, low amounts are still a bit quirky
- **AEG** sets the amplitude envelope decay for determining the length of the sound
- **Volume** sets the volume of the step
- **Below the controls** four step buttons controlling whether the sound will trigger by default or not.
- **%** which introduces random variation to the step trigges. % at zero means the sound will trig if and only if the step button is active. % at full means the step will trig with a probability of 0.5 regardless of the step button status

Below the **pattern** label, 8 lights indicating the 8 patterns. **Press a number key** from 1 to 8 to **switch** to another pattern. The currently playing pattern is saved automaticallt. **Press shift + number key** from 1 to 8 to **save** the current pattern to another, overwriting its contents.

Additionally, there are **master controls** for pitch and volume. Also controls for tempo, swing and reverb parameters which do what you would expect. Tempo can be set in the range [60, 180] bpm.

The **Mutate** control changes dial values randomly as the sequence plays.

#### How to run (Linux):
From the source directory:
```
mkdir build
cd build
cmake ..
make
./mega_fm
```

### TODO:
- MIDI clock input
- Add STK as submodule?
- "Mutate lock" for steps / parameters that are not wanted to mutate? Or get rid of mutate, it's not very good
- Sound saving and loading. It should work like this: Right click on the dial strip brings up a context menu with the options to save and load. Choose save -> prompt for sound name, save sound. Choose load -> display saved sounds, select one, the step is set to those parameters. Perhaps also have categories of sounds such as "bass drum", "perc", "snare" etc
