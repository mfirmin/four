four
====

### Description 
four (version 0.0000001)

Inspired by three.js, _four_ is designed to be an all-in-one rendering and rigid body physics simulation engine. 
It is essentially a wrapper for OpenGL, GLFW, and the simulation engine Open Dynamics Engine.

_four_ is the very beginning of my attempt at crowd sourcing my 
[Master's Thesis](http://www.cs.ubc.ca/~mfirmin/research.php) work.

### Dependencies

* OpenGL

* GLFW3 - http://www.glfw.org/

* ODE - http://www.ode.org/

### Usage

From the root directory, run make. This will place the executable world in the bin directory. 
It has been tested on and should work on OSX Yosemite, and Linux Mint/Ubuntu.

To run, type ./bin/world. Play around with adding entities and joints. See simpleWorld.cpp for examples of how to add entities and joints.

### TODO

* JSON renderer - output a json file to send to a client-side renderer.
* Incorporate control language back in (possibly using client side javascript (live editing with codemirror, tangle(?!)))
* incorporate openFLT models for rendering characters


