=========================================================================================================
=========================================================================================================
  Twnkl
  (c) Paul Alan Freshney 2023

    paul@freshney.org
	
  Source code, example scenes and textures
    https://github.com/MaximumOctopus/Twnkl

  October 7th 2023
=========================================================================================================
=========================================================================================================

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
C++ 17 with C++ Builder 11.3
	
An early beta, proof of concept, WIP, GUI front-end for Twnkl. Mostly built as something for me to play with.


=========================================================================================================
=========================================================================================================

 Credits:

   All coding       : Paul A Freshney
   Development Cats : Rutherford, Freeman, and Maxwell
					  
   Dedicated to Julie, Adam, and Dyanne.

All of my software is free and open source; please consider donating to a local cat charity or shelter. Thanks.

=========================================================================================================

Release History

0.10 Console and GUI / October 7th 2023

GUI/Console
Added: Noise option to many of the pattern types (include textures)
Added: Many new example scenes to show off the new noise options

GUI
Added: Texture viewer on the right hand panel
Added: Error/status output viewer for sceneloader and world handler
Fixed: (GUI) error when loading scenes with arealights

Added: Project information to scene files.

Lots of minor fixes and tweaks.

0.9 Console and GUI / August 13th 2023

GUI
Added: index of refraction editing and selectable option
Added: icons to buttons :)
Added: about box
Fixed: object loader to correctly load objects used by example scene files
       face data can appear in a few different formats, and it appears I broke
       the code so it only loaded one format correctly :(
       there might still be some objects that won't load, but hopefully all the simple
       files on the internet will work now.
Fixed: setting pattern to "none" now removes pattern and sets GUI to reflect that

Rewritten "resize to display" functionality so it works as you'd expect. Moved the checkbox to
the camera panel. Automatically updates width/height to fit display as main window is resized.

Console
Object loader code fixed (see above)

Several tweaks and minor changes.

I've disabled bounding box checks for now, there seems to be a bug in there somewhere.

0.8 Console and GUI / April 14th 2023

Added multi-texture cube texture (one texture per face).
Few minor tweaks. Core code now identical across console/GUI versions.

0.7 GUI / April 13th 2023

Lots of editable fields now work. Rendered image can be exported to PNG.

No significant changes to console version, code not uploaded.

0.7 / April 8th 2023

Mainly updating the source code so that the GUI and console versions can share the same core.

0.6 / March 30th 2023

Added three Perlin noise pattern options.
Added cube checkerboard pattern
Simplified scene file pattern syntax.
Scene loader tidy

0.5 / March 28th 2023

First public release.

=========================================================================================================
=========================================================================================================
