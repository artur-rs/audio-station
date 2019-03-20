### README OUT-OF-DATE (possible deprecation).
> below configuration and theory of operation is not tested with audiostation v2 (TBD)

---

### Audio-Station project

Application uses script written in bash - `speech.sh` ( which requires installed `mplayer`): 
* by default:
  - `audio.out` must be in the same folder with `speech.sh` script
* new destination:
  - change script location in `Audiostation.cpp` file (`textToSpeech(const char * ptr)` method).
  Default location: `./speech.sh`

After changes compile with `-std=c++11`, ex.:

```
$ g++ src/*.cpp -o audio.out -lcurl -std=c++11 
```

Successful compilation requires `libcurl4-openssl-dev` installed.
