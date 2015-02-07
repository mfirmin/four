four
====

### Description 
four (version 0.0000001)

Inspired by three.js, _four_ is designed to be an all-in-one rendering and rigid body physics simulation engine. 
It is essentially a wrapper for OpenGL, GLFW, and the simulation engine Open Dynamics Engine.

_four_ is the very beginning of my attempt at crowd sourcing my 
[Master's Thesis](http://www.cs.ubc.ca/~mfirmin/research.php) work.

Suggestions, comments, constructive criticism are all welcome! 
(But keep in mind that this project is still in its very early stages)

### Dependencies

* OpenGL

* GLFW3 - http://www.glfw.org/

* ODE - http://www.ode.org/

### Usage

From the root directory, run make. This will place the executable world in the bin directory. 
It has been tested on and should work on OSX Yosemite. It should also run on Linux Mint/Ubuntu, 
but I haven't tested this in awhile.

To run, type bin/world. Play around with adding entities and joints (coming soon!) in the main function in world.cpp
(eventually this project will become a library that you include in your own project instead...)

