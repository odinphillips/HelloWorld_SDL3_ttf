# HelloWorld_SDL3_ttf

Quickstart for using the SDL3_ttf font library on Windows (msys).

https://github.com/libsdl-org/SDL_ttf

## Installation of SDL_ttf

First find a location on your machine to clone the SDL repo. Then do the following commands.

```
git clone --recurse-submodules -j4 https://github.com/libsdl-org/SDL_ttf.git
```

Note: SDL_ttf has three external dependencies (as Git submodules) located in `external/`:
- freetype
- harfbuzz
- SDL

## Building for Windows (msys2)

We will build SDL_ttf using the msys2 terminal environment. First go to the official msys2 website here: https://www.msys2.org/

Then follow the installation steps on their webpage and install the standard build tools etc that you need using `pacman` (package installer).

**Note:** we are using the msys terminal program located here: (it may be different on your machine, depending on where you have installed it.)
```
C:\msys64\ucrt64.exe
```

*Example:* `pacman` tool usage:
```
pacman S <SEARCH>  # To search for all packages with name <SEARCH>.

pacman Ss <package_name>  # To install <package_name>
```

## SDL3_ttf build and install

Launch a new msys `ucrt64` terminal (remember to right-click on the app and 'Run as administrator' this is needed for the cmake install step later).

Go to the directory on your system where you cloned the SDL_ttf repo. E.g.

```
odinp@Moon UCRT64 ~
# cd /c/Work/SDL_ttf

odinp@Moon UCRT64 /c/Work/SDL_ttf
#
```
Then do the following `cmake` build procedure:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --parallel
cmake --install . --config Release
```
Make a note of where it installs the built files, e.g.
```
-- Installing: C:/Program Files (x86)/SDL3_ttf/*
```
Now you are ready to run the HelloWorld_SDL3_ttf example from this repo.

(**Note:** the SDL_ttf repo also has some code samples in the directory `examples/`)

## HelloWorld_SDL3_ttf

Clone the repo if you haven't already done so.

```
git clone https://github.com/odinphillips/HelloWorld_SDL3_ttf.git
```

## Copy dll files
- Copy the installed `SDL3.dll` to the local `dlls` directory.
- Copy the installed `SDL3_ttf.dll` to the local `dlls` directory.
- Copy the installed `libfreetype-6.dll` to the local `dlls` directory.
- Copy msys ucrt64 bin directory .dlls to the local `dlls` directory:
  - `libbz2-1.dll`
  - `libbrotlicommon.dll`
  - `libbrotlidec.dll`

E.g.

```
cp /c/Program\ Files\ \(x86\)/SDL3/bin/SDL3.dll HelloWorld_SDL3/dlls
cp /c/Program\ Files\ \(x86\)/SDL3_ttf/bin/SDL3_ttf.dll HelloWorld_SDL3/dlls
cp /c/msys64/ucrt64/bin/libfreetype-6.dll HelloWorld_SDL3/dlls
cp /c/msys64/ucrt64/bin/libbz2-1.dll HelloWorld_SDL3/dlls
cp /c/msys64/ucrt64/bin/libbrotlicommon.dll HelloWorld_SDL3/dlls
cp /c/msys64/ucrt64/bin/libbrotlidec.dll HelloWorld_SDL3/dlls
```

## Build

```
cd HelloWorld_SDL3_ttf
mkdir build
cd build
cmake ..
make
# or try any of the following commands
# ninja
# cmake --build .
```

An executable file should have been created in the current directory.

Run it!
```
.\helloworld-sdl3-ttf.exe
```

**Note:** The program above may fail to execute, due to missing `.dll` files. You can see this in the logs when running the program in a termainl such as Windows Powershell.

See the **'Copy dll files'** section above. You may need to install other libraries on your system in order to have all the required dll files for `helloworld-sdl3-ttf.exe`. 

**IMPORTANT:** the dll files *must* be in the same directory as the executable `helloworld-sdl3-ttf.exe`.
