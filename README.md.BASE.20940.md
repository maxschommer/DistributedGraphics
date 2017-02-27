# Ray-Tracing
We desire to create a rendering environment using C. We will implement a version of ray tracing using copious amounts of linear algebra and the power of STLs (STereoLithography files that define a triangulated surface by unit normals and vertices), and create beautiful images of spheres, bunnies, teapots and other objects.

At a minimum, we desire to implement ray tracing for a sphere, and output a rendered image of that sphere with one layer of reflection. This will require detecting where the ray intersects the sphere, calculating the reflected ray, and calculating the light source that the reflected ray hits.

For a stretch goal, we want to implement a video rendering of STLs and spheres that uses recursion to back-propagate the ray’s path as it reflects and refracts off of the objects in the video. With this, we would also like to implement color rendering, full STL rendering, and custom environments. Our definition of full video capability, includes turntable renders and camera path linear (and possibly polynomial) interpolation..

