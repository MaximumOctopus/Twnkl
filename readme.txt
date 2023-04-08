==========================================================================================================================
==========================================================================================================================
  Twnkl
  (c) Paul Alan Freshney 2023

    paul@freshney.org
	
  Source code, example scenes and textures
    https://github.com/MaximumOctopus/Twnkl

  April 8th 2023
==========================================================================================================================
==========================================================================================================================

Implements the following chapters:

    Chapter 1    Tuples/points/vectors
    Chapter 2    Drawing on a canvas
    Chapter 3    Matrices 
    Chapter 4    Matrix transformations
    Chapter 5    Ray-sphere intersections
    Chapter 6    Light and shading
    Chapter 7    Making a scene
    Chapter 8    Shadows
    Chapter 9    Planes
    Chapter 10   Patterns
    Chapter 11   Reflection and refraction
    Chapter 12   Cubes
    Chapter 13   Cylinders
    Chapter 14   Groups
    Chapter 15   Triangles
	
    Bonus        Texture mapping
    Bonus        Bounding boxes (for loaded obj files only)
    Bonus        Soft shadows

Also implements a supersampling algorithm based on the code from the website
    "Ray Tracing in One Weekend"

    https://raytracing.github.io/books/RayTracingInOneWeekend.html

\Twnkl\
Console application

C++ 20 with Visual Studio 2022.

\Twnkl_GUI\
C++ 17 with C++ Builder 10.4
	
An early alpha, proof of concept, WIP, GUI front-end for Twnkl.

There are currently a few differences between the core source files of the GUI version and the console version, but these will be gone asap. My plan is to keep all source files compatible with either a console or gui build.

==========================================================================================================================
==========================================================================================================================

 Credits:

   All coding       : Paul A Freshney
   Development Cats : Rutherford, Freeman, and Maxwell
					  
   Dedicated to Julie, Adam, and Dyanne.

All of my software is free and open source; please consider donating to a local cat charity or shelter. Thanks.

==========================================================================================================================

Release History

0.7 / April 8th 2023

Mainly updating the source code so that the GUI and console versions can share the same core.

0.6 / March 30th 2023

Added three Perlin noise pattern options.
Added cube checkerboard pattern
Simplified scene file pattern syntax.
Scene loader tidy


0.5 / March 28th 2023

First public release.

==========================================================================================================================
==========================================================================================================================