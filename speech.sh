#!/bin/bash
say() { local IFS=+;/usr/bin/mplayer -ao alsa -volume 100 -really-quiet -noconsolecontrols "http://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=$*&tl=Pl-pl"; }
say $*
