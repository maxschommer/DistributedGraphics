# Abstract
We implemented a ray tracer in C to create a rendered, realistic image of an object. By simulating light particles that bounce off an STL object with material properties, we created beautiful images of STLs using our ray tracer, and can do the same for any STL imputed into the program. 

# Background
Ray tracing is one technique to generate a 2D image from a 3D object by following the path of light and simulating the effects of its interactions with other objects in the scene. Our rays fire through each pixel in the 2D canvas, checks to see if the ray intersects with any object or the light source, and uses this information to add dimension to the image such as reflection and shadowing. For each point on the surface of an object that a ray hits, the shading is calculated using various properties of light and material. 

Linear algebra and other mathematical formulas were necessary in implementing ray tracing. Generalizing rays into vectors, this project required the usage of dot products, cross products, matrix inversions, and inverse square roots, as well as intersection formulas to understand how to determine where a line and a plane intersect.

# Implementation
In order to do ray tracing, quite a bit of linear algebra is needed. We wrote all of our own linear algebra functions, from matrix multiplications, vector addition/subtraction to rotation matrices, partly as a learning goal and partly because it was critical to understanding all of the math in order to do a proper implementation of ray tracing. 

# Results
We will include 2-3 videos of our ray tracer. These videos represent our best attempts at generating 3D images with a given light source from input stl files. 
