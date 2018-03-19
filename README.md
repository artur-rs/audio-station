Audio-Station project README:
@author Artur Raglis

Application uses script written in bash - "speech.sh" ( which requires installed mplayer): 
- by default:
  "audio.out" must be in the same folder with speech.sh script
- new destination:
  change script location in main.cpp file (textToSpeech(const char * ptr) method).
  Default location: ./speech.sh

After changes compile with -std=c++11, ex.:
$ g++ src/*.cpp -o audio.out -lcurl -std=c++11 

Successful compilation requires installed libcurl4-openssl-dev.
