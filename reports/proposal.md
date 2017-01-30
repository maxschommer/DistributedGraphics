
# Project I Proposal: Terminally Eel
###### Bill Du, Jeremy Garcia, Max Schommer, and Rachel Yang

## Project Goal
   We desire to create a rendering environment using C. We will implement a version of ray tracing using copious amounts of linear algebra and the power of STLs, and create beautiful images of spheres, bunnies, teapots and other objects. 


   At a minimum, we desire to implement ray tracing for a triangle or sphere, and output a grayscale image of the triangle or sphere. This will require detecting where the ray intersects the plane of triangle, calculating whether the intersected ray is contained within the triangle, and calculating the light source of the ray. 


   For a stretch goal, we want to implement volume rendering using either OpenCL or CUDA. We would also like to implement color rendering, full STL rendering, and custom environments.

## Product Backlog
[Trello Board](https://trello.com/b/5pgqGMIn/softsys17-terminally-eel)

## Potential Roadblocks
   To enable ray tracing requires some advanced knowledge in linear algebra, which might be a roadblock for us to implement in C (since simple arrays aren’t optimized for linear algebra). We have gone through an introduction to ray tracing algorithms to help us understand different techniques. We will try to implement these algorithms in C for this project. 

   After achieving ray tracing in basic C programming, we will also seek to optimize the program by using GPU through parallel programming. However, it has been hard for us to compile and run CUDA programs on our laptop, so making sure each of us has CUDA/OpenCL working on our GPU and diving into parallel programming might also be a problem reaching our stretch goal.
```

## Resources
1. [Introduction to Ray Tracing](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/implementing-the-raytracing-algorithm)

    This resource goes through a brief introduction to ray tracing, going into detail about the basic concepts such as why ray-tracing is preferable over forward tracing and how important perspective projection and light / color / shading come into play when creating 3D images on a 2D screen. It includes some pseudo-code to show an example of a ray tracing implementation, from shooting rays through pixels to adding shading to create the sense of depth.

2. [Ray Tracing](https://www.ics.uci.edu/~gopi/CS211B/RayTracing%20tutorial.pdf)

    Here, we have a resource that confirms the basic concepts and implementations of ray tracing, but that also delves deeper into the math behind the algorithm. It especially elaborates on how to find the closest intersection points between the ray and the object and how to determine if a ray that bounces off of the object shoots directly into the light source (versus being blocked by another object and thus identifying shadow points). It also goes into the math formulas behind reflection and refraction, using Phong / Blinn-Phong theorems. For our stretch goal, it offers some hints as to how to approach texturing and blurring.
    
 3. [3D Basic Rendering](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/geometry-of-a-triangle)

    This resource also touches on ray-tracing by exploring the basics of geometric rendering in 3d programs. It focuses on rendering triangles, providing details on the geometry of triangles and how to detect intersection points between the ray and the triangle. It progresses into how optimizing Barycentric coordinates helps render the object’s shading and how the Moller-Trumbore algorithm optimizes ray-triangle intersection.

