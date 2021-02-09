# This is the OpenGL implementation of NWTE.

The main reason to change SDL2 rendering engine was making the rendering efficient through batching.

![](https://im.ezgif.com/tmp/ezgif-1-a54f4654cd89.gif)

Scene above being rendered with 3 Draw Calls.

# Build instructions :
#### Linux:
Required packages:
	- libsdl2-dev
	- libglfw3-dev
`cd lbuild/`
`chmod +x build.sh`
`./build.sh`

#### Microsoft Windows:
Set Visual Studio environment variables (vcvarsall.bat)
And run `build.bat`.
