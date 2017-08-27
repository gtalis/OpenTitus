Compiling instructions for MinGW/Windows
OpenTitus 0.8.0

OpenTitus is released under the Gnu GPL version 3 or (at your option) any later version of the license, and it is released "as is"; without any warranty.


Compile time dependencies:
LibSDL development headers
LibSDLMixer library (rename SDL_mixer.lib from the devel-VC package to libSDL_mixer.a, or use extras/libSDL_mixer.a)
Chocolate-Doom (1.6.0)'s OPL library (opl/libopl_win32.a), check out opl/opl_readme.txt for further details

To compile, use the following commands:

All:
make -f Makefile_win32


Clean:
make -f Makefile_win32 clean
