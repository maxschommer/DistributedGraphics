/*
 * Header file defining structs used in the ray tracer.
 */

// Defines a 3D vector
typedef struct{
    float x,y,z; // Positions in x, y, z axis
}vector;

// Defines a triangle
typedef struct{
    // Three vectors that define the position of the triangle
    vector p1;
    vector p2;
    vector p3;

    vector normal; // The normal of the triangle    
    float ks; // Specular reflection constant
    float kd; // Diffuse reflection constant
    float ka; // Ambient reflection constant
    float gamma; // Shininess constant
}triangle;

// Defines a ray of light
typedef struct{
    vector start; // Position of the light source
    vector dir; // Direction of the light source
    float reflectance; // Reflectance
}ray;

// Defines the intersection between a vector and a triangle
typedef struct
{
	int FLAG; // 1 if the light hits the triangle, 0 otherwise
    int index; // Index of the triangle 
    vector normal; // The normal to the triangle that passes through
                   // the point of intersection
	vector point;  // Point of intersection

}hit_tri;

// Defines a point of light
typedef struct
{
	vector point;
	float diff_int; //Diffuse Intensity
	float spec_int; //Specular Intensity
}point_light;
