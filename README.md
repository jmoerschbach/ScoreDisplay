# Self-built ScoreDisplay
shows game time, score and halftime

# How to compile
use the Arduino IDE to compile the sketches. Since there is shared code and Arduino IDE does not support relative paths, there are two options:
- Windows (and Linux):
copy all the files inside Code/common into the respective sketch directories
- Linux only (but more elegant):
  - find out where the sketchbook location is (in Arduino IDE File -> Preferences, "Sketchbook location") and `cd` into the libraries folder of that directory
  - create a symlink from within the libraries folder to Code/common: `ln -s <path-where-you-cloned-into>/Code/common`