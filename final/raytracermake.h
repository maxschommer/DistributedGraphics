typedef struct{
    float x,y,z;
}vector;

typedef struct{
    vector p1;
    vector p2;
    vector p3;
    vector normal;
    float ks;
    float kd;
    float ka;
    float gamma;
}triangle;

typedef struct{
    vector start;
    vector dir;
    float reflectance;
}ray;

typedef struct
{
	int FLAG;
    int index;
    vector normal;
	vector point;

}hit_tri;

typedef struct
{
	vector point;
	float diff_int; //Diffuse Intensity
	float spec_int; //Specular Intensity
}point_light;
