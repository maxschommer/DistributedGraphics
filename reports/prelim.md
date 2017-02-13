
# Project I Preliminary Report: Terminally Eel
###### Bill Du, Jeremy Garcia, Max Schommer, and Rachel Yang
###### February 13, 2017

## Project Goal

   We desire to create a rendering environment using C. We will implement a version of ray tracing using copious amounts of linear algebra and the power of STLs (STereoLithography files that define a triangulated surface by unit normals and vertices), and create beautiful images of spheres, bunnies, teapots and other objects.
    
   At a minimum, we desire to implement ray tracing for a sphere, and output a rendered image of that sphere with one layer of reflection. This will require detecting where the ray intersects the sphere, calculating the reflected ray, and calculating the light source that the reflected ray hits.
    
   For a stretch goal, we want to implement a video rendering of STLs and spheres that uses recursion to back-propagate the ray’s path as it reflects and refracts off of the objects in the video. With this, we would also like to implement color rendering, full STL rendering, and custom environments. Our definition of full video capability, includes turntable renders and camera path linear (and possibly polynomial) interpolation.

## Product Backlog
[Trello Board](https://trello.com/b/5pgqGMIn/softsys17-terminally-eel)

   Within this Trello board, on the right side, lies our Sprint 1 and Sprint 2 "Done" cards. For many of the Sprint 1 completed cards, we don't have physical evidence for because it was done on an individual basis and, because it was more for cursory research, we didn't save the articles we studied. However, for Sprint 2, we did much better in terms of documentation, and by looking at the comments in each card, we should have links to code or articles that show physical evidence confirming that we did, in fact, complete these cards.

## Preliminary Results

## Potential Roadblocks
 
   Time is a limiting factor in terms of us finishing everything that we want to. It’s been difficult prioritizing readings and exercises for understanding the core material over project work time. 
    
   Our next challenge is figuring out how to implement reflection and refraction, as well as recursion, since we are struggling with understanding how to even start coding these functions.
    
   For our stretch goal, downloading and running CUDA programs on our computers is still an intimidating roadblock, considering that two of our computers have had major problems trying to do this in the research phase of our project.
 
## Resources
1. [Introduction to Ray Tracing](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/implementing-the-raytracing-algorithm)

    This resource goes through a brief introduction to ray tracing, going into detail about the basic concepts such as why ray-tracing is preferable over forward tracing and how important perspective projection and light / color / shading come into play when creating 3D images on a 2D screen. It includes some pseudo-code to show an example of a ray tracing implementation, from shooting rays through pixels to adding shading to create the sense of depth.

2. [Ray Tracing](https://www.ics.uci.edu/~gopi/CS211B/RayTracing%20tutorial.pdf)

    Here, we have a resource that confirms the basic concepts and implementations of ray tracing, but that also delves deeper into the math behind the algorithm. It especially elaborates on how to find the closest intersection points between the ray and the object and how to determine if a ray that bounces off of the object shoots directly into the light source (versus being blocked by another object and thus identifying shadow points). It also goes into the math formulas behind reflection, using Phong / Blinn-Phong theorems. For our stretch goal, it offers some hints as to how to approach texturing and blurring.
    
3. [3D Basic Rendering](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/geometry-of-a-triangle)

    This resource also touches on ray-tracing by exploring the basics of geometric rendering in 3D programs. It focuses on rendering triangles, providing details on the geometry of triangles and how to detect intersection points between the ray and the triangle. It progresses into how optimizing Barycentric coordinates helps render the object’s shading and how the Moller-Trumbore algorithm optimizes ray-triangle intersection.
    
4. [Ray Tracing Tutorials](http://www.purplealienplanet.com/node/23)

    This resource is a series of tutorials on how to ray trace in C. It contains various levels of implementation, from simple boolean return functions to full color rendering. We read through this resource in order to see how ray tracing worked, and then stopped looking at it so that we could develop our own method of ray tracing that doesn’t rely on other’s code.
    
5. [Intersection Formulas](https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection)

    Here is where we got the formulas to determine where a line and a plane intersect. We initially used the matrix solution, which required a matrix inverse, but later simplified to a faster solution that simply meant solving for a single variable (instead of t, u, and v). 
    
6. [Ray Reflection](https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf)

    This is a graphics paper that describes in depth methods for solving the reflection of a ray. It also describes refraction, which will be useful if we want to solve for transparent or translucent objects. 
