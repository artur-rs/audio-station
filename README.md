Audio-Station project README:
@author Artur Raglis

Application uses script written in bash - "speech.sh" - 
copy it to destination folder to enable text to speech option.

Don't forget to change script location in main.cpp file (textToSpeech(const char * ptr) method).
Default location (Raspbian OS): /home/pi/Desktop/audiocpp/speech.sh

Successful compilation requires installed libcurl! 

After changes compile with -std=c++11, ex.:
-g++ src/*.cpp -o audio.out -L/usr/lib/ -lcurl -std=c++11 
