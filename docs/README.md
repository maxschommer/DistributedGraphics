# Abstract
We implemented a ray tracer in C to create a rendered, realistic image of an object. By simulating light particles that bounce off an STL object with material properties, we created beautiful images of STLs using our ray tracer, and can do the same for any STL imputed into the program. 

# Background
Ray tracing is one technique to generate a 2D image from a 3D object by following the path of light and simulating the effects of its interactions with other objects in the scene. Our rays fire through each pixel in the 2D canvas, checks to see if the ray intersects with any object or the light source, and uses this information to add dimension to the image such as reflection and shadowing. For each point on the surface of an object that a ray hits, the shading is calculated using various properties of light and material. 

Linear algebra and other mathematical formulas were necessary in implementing ray tracing. Generalizing rays into vectors, this project required the usage of dot products, cross products, matrix inversions, and inverse square roots, as well as intersection formulas to understand how to determine where a line and a plane intersect.

# Implementation
In order to do ray tracing, quite a bit of linear algebra is needed. We wrote all of our own linear algebra functions, from matrix multiplications, vector addition/subtraction to rotation matrices, partly as a learning goal and partly because it was critical to understanding all of the math in order to do a proper implementation of ray tracing. 

We decided to ray trace STLs, because although the math to do this is more complex than spheres, it solves a much more general problem (you can render any object represented by an STL). An STL is composed of a series of triangles and their associated normals. The first step we took was to render a single triangle by ray tracing. We initially were unable to read STLs, and calculated the normal of a triangle by taking the cross product of two vectors that made up edges of a triangle. 

Knowing the equation for the plane of the triangle, we could solve for where the ray would intersect the plane by defining the ray parametrically as v_start + v_dir*t = ax+by+cz+d and solving for t, when a, b, c, and d are defined by the particular triangle. We only want to consider positive t values (we don’t want the ray to intersect triangles behind it). After we find the plane intersect, if it exists, we want to check whether the intersection point of the ray and the plane is inside the triangle. In order to do this, we want to define what “inside” means. If we consider three planes which lie along the edges of the triangle, with the normals facing inwards parallel to the face of the triangle, we can say the point lies inside the triangle if the dot products of all of the vectors joining a point on a respective plane to the point we are checking with the normal of each respective plane are the same sign. 

By doing this, we are able to see if a given ray hits a triangle. If it does, then we calculate the shading at that point on the triangle. If it doesn’t, we return the ambient lighting. 

# Results
The following videos (linked in yellow) are outputted from our ray tracer. These videos represent our best attempts at generating 3D images with a given light source from input stl files. 

### Fragmentation
[video](https://github.com/maxschommer/SoftSys_Terminally_Eeeel/blob/master/Work_in_Progress/Video4/a_bit_less_sad_rays.gif)

A rendering of a sphere splitting apart.

### Fragmentation Pt. II
[video](https://github.com/maxschommer/SoftSys_Terminally_Eeeel/blob/master/Work_in_Progress/Video5/diseased_rays.gif) 

Similar to the previous video, but at a higher and more destructive decay rate.

### Morning Rays
[video](https://github.com/maxschommer/SoftSys_Terminally_Eeeel/blob/master/Work_in_Progress/Video1/morning_rays.gif)

Showcases the upwards movement of the light source, imitating a rising sun.

### Sphere 
[video](https://github.com/maxschommer/SoftSys_Terminally_Eeeel/blob/master/Work_in_Progress/Video6/moviefast.gif)

Rotates a sphere, demonstrating the transformation matrix that displays movement of the light source.

### Big Sphere
[video](https://github.com/maxschommer/SoftSys_Terminally_Eeeel/blob/master/Work_in_Progress/Video7/sick_rays.gif)

Similar to the previous one, but zoomed in to make the sphere larger, and illustrates the closer proximity of the light source.

# Next Steps
If we were to continue this project, we would have implemented linear interpolation and recursion to be able to better implement curves around rounded objects. Recursion would have allowed us to also include mirror reflection in our model. We also expect to implement refraction and shading to our ray tracer in future work. 
