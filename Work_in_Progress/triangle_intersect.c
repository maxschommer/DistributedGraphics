/*Computes the location of the intersection between 
a ray and a triangle*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define WIDTH 800
#define HEIGHT 800
/*#include "../main.h"
*/
//Missing header level comments/ move into a header file
//explain better structs

typedef struct{
    float x,y,z;
}vector;

typedef struct{
    vector p1;
    vector p2;
    vector p3;
}triangle;

typedef struct{
    vector start;
    vector dir;
    float reflectance;
}ray;

typedef struct
{
	int FLAG;
	vector point;
}hit_tri;

typedef struct
{
	vector point;
	float diff_int; //Diffuse Intensity
	float spec_int; //Specular Intensity
}point_light;

//This is used to test Trace code,
//which requires a global object. We're
//using a triangle to be our object.
triangle tglobal;
point_light light;



/*Returns a float that is the vector dot product
of two vectors*/
float dotProduct(vector *v1, vector *v2){
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

float det2x2(float *a, float *b, float *c, float *d){
    float result = (*a)*(*d)-(*c)*(*b); //Dereference the pointers.
    return result;
}

float det3x3(triangle *Mat){
    float det = 
        Mat->p1.x*(det2x2(&Mat->p2.y, &Mat->p2.z, &Mat->p3.y, &Mat->p3.z))-
        Mat->p1.y*(det2x2(&Mat->p2.x, &Mat->p2.z, &Mat->p3.x, &Mat->p3.z)) + 
        Mat->p1.z*(det2x2(&Mat->p2.x, &Mat->p2.y, &Mat->p3.x, &Mat->p3.y));
    return det;
}

//This subtracts vector 2 from vector 1. Ex. v1-v2 
vector vecSub(vector *v1, vector *v2){
    vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return result;
}

//This subtracts vector 2 from vector 1. Ex. v1-v2 
vector vecSum(vector *v1, vector *v2){
    vector result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
    return result;
}

/*Scales a vector by a constant*/
vector vecScale(vector *v, float *d){
	vector result = {(v->x )* *d, (v->y) * *d, (v->z) * *d};
	return result;
}


/*Returns the unit vector of a vector input.*/
vector vecNorm(vector *v){
    float invSqrt = 1.0/sqrtf((v->x)*(v->x)+(v->y)*(v->y)+(v->z)*(v->z));
    vector result = {(v->x)*invSqrt, (v->y)*invSqrt, (v->z)*invSqrt};
    return result;
}

/*Returns the crossproduct u x v for two vectors
u and v.*/
//TODO
vector crossProduct(vector *u, vector *v){
    vector result;
    result.x = u->y * v->z - u->z * v->y;
    result.y = u->z * v->x - u->x * v->z;
    result.z = u->x * v->y - u->y * v->x;
    //printf("from crossproduct: %f\n", result);
    return result;
}


/*This is used to calculate the intensity of
light of a point source. It is the 
distance function, and takes two vectors,
and returns the distance between them*/
float distance(vector *u, vector *v){
	vector diff = vecSub(u, v);
	return sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}

/*Finds the normal of a triangle and returns
a vector.

We define v1 as p3-p1, and v2 as p2-p1. We
take the cross product of these (v1 x v2) and normalize
in order to find the unit normal.*/
vector triangleNormal(triangle *tri){
    vector v1 = vecSub(&tri->p3, &tri->p1);
    vector v2 = vecSub(&tri->p2, &tri->p1);
    vector cross = crossProduct(&v1, &v2);
    vector result = vecNorm(&cross);
    return result;
}


/*Uses a triangle as a three by three matrix, 
where the rows are p1, p2, and p3. The collumns
are x, y, z. */
triangle matInv(triangle *A){
    float aDet = det3x3(A);

    triangle B;

    B.p1.x = det2x2(&A->p2.y, &A->p2.z, &A->p3.y, &A->p3.z)/aDet;
    B.p1.y = det2x2(&A->p1.z, &A->p1.y, &A->p3.z, &A->p3.y)/aDet;
    B.p1.z = det2x2(&A->p1.y, &A->p1.z, &A->p2.y, &A->p2.z)/aDet;

    B.p2.x = det2x2(&A->p2.z, &A->p2.x, &A->p3.z, &A->p3.x)/aDet;
    B.p2.y = det2x2(&A->p1.x, &A->p1.z, &A->p3.x, &A->p3.z)/aDet;
    B.p2.z = det2x2(&A->p1.z, &A->p1.x, &A->p2.z, &A->p2.x)/aDet;

    B.p3.x = det2x2(&A->p2.x, &A->p2.y, &A->p3.x, &A->p3.y)/aDet;
    B.p3.y = det2x2(&A->p1.y, &A->p1.x, &A->p3.y, &A->p3.x)/aDet;
    B.p3.z = det2x2(&A->p1.x, &A->p1.y, &A->p2.x, &A->p2.y)/aDet;

    return B;

}

/*Calculates the point of intersection between the ray 
and the plane of the triangle. If the ray is firing
in the wrong direction, then the FLAG variable
is set to 0, signaling a lack of intersection
with the plane of the triangle.*/
hit_tri planeIntersect(triangle *tri, ray *r){
    /*Formula is (a . n)/(r . n)*/
    vector n = triangleNormal(tri);
    vector a = vecSub(&tri->p1, &r->start);
    float d = dotProduct(&a, &n)/dotProduct(&r->dir, &n);
    if (d<=0)
    {
    	hit_tri no_intersect;
    	no_intersect.FLAG = 0;
    	return no_intersect;
    }
    vector v1 = vecScale(&r->dir, &d);
    vector v2 = r->start;
    hit_tri result;
    result.point = vecSum(&v1, &v2);
    result.FLAG = 1;
    return result;
}

/*Checks to see if point of intersection lies within the
bounds of the triangle

Returns true or false*/
int inTri(triangle *t, vector *p){
	// define vectors from point to point of triangle
	// to define triangle boundaries
	vector v1 = vecSub(&t->p1, &t->p2);
	vector v2 = vecSub(&t->p2, &t->p3);
	vector v3 = vecSub(&t->p3, &t->p1);

	vector n = triangleNormal(t);

	vector cv1 = crossProduct(&v1, &n);
	vector cv2 = crossProduct(&v2, &n);
	vector cv3 = crossProduct(&v3, &n);

	// define vectors from given point to 
	// one of the points that make up the triangle
	vector fplane1 = vecSub(p, &t->p1);
	vector fplane2 = vecSub(p, &t->p2);
	vector fplane3 = vecSub(p, &t->p3);

	// determine if given point lies above
	// or below plane defined by triangle
	float dv1 = dotProduct(&cv1, &fplane1);
	float dv2 = dotProduct(&cv2, &fplane2);
	float dv3 = dotProduct(&cv3, &fplane3);

	// if all three have positive directions
	// point does lies within inside triangle
	// and so returns true (which returns 1)
	if ((dv1 <= 0) && (dv2 <= 0) && (dv3 <= 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

/*Returns the point of intersection between 
a ray and the nearest object (just one triangle
for now). Otherwise, it returns None. 
The inputed triangle should be removed
when function is verified to work, and
the function should act on a global 
collection of triangles called an object*/
hit_tri Intersect(ray *r){
    //int inside;
    hit_tri find_intersect = planeIntersect(&tglobal, r);
    if ((find_intersect.FLAG) && (inTri(&tglobal,&find_intersect.point))){
        find_intersect.FLAG = 1;
        return find_intersect;
    }else{
        find_intersect.FLAG = 0;
        return find_intersect;
    }

}


/*Returns a ray in the direction of the reflected
ray given by the normal of the surface and the initial
ray. Takes as input the ray, the normal to the 
triangle, and a vector that represents the point
of intersection between the ray and the triangle*/
ray reflectedRay(ray *d, vector *n, vector *p){
    ray sent_ray = *d;
    sent_ray.dir.x = -sent_ray.dir.x;
    sent_ray.dir.y = -sent_ray.dir.y;
    sent_ray.dir.z = -sent_ray.dir.z;


    vector normal_vector = *n;
    vector point = *p;
    sent_ray.dir = vecNorm(&sent_ray.dir);
    normal_vector = vecNorm(&normal_vector);

	float dn = 2*(dotProduct(&sent_ray.dir, &normal_vector));
	vector c = vecScale(&normal_vector, &dn);
	ray result;
	result.dir = vecSub(&c, &sent_ray.dir);
	result.start = *p;
	return result;
}

/*This function accumulates the light gathered
from all of the light sources.
It takes in a point, which is the point of intersection
between the ray and the triangle, and the normal of 
the triangle, and the vector of the direction of the 
ray hitting the triangle (used for specular highlights).
Currently, it just does this for one light source. It needs
to be able to loop.*/
float AccLightSource(vector *q, ray *v){
	float ia = .1; //This needs to become global
	float color = ia;
    float gamma = 12;
    ray view = *v;

    vector buffer; //This is the distance away from the triangle's
                   //surface that the ray should start so that the intersect
                   //is correctly calculated without ambiguity. 
    buffer.x = -v->dir.x*.01;
    buffer.y = -v->dir.y*.01;
    buffer.z = -v->dir.z*.01;

	//For loop goes here, to do all light sources
	ray r;

    r.start = vecSum(q, &buffer);
    r.dir = vecSub(&light.point, &r.start);
    r.dir = vecNorm(&r.dir);

	hit_tri w = Intersect(&r);
    printf("wFLAG = %d \n", w.FLAG);
	//This checks if the ray intersects
	//something before hitting a light source.
	if (w.FLAG == 0)
	{
		float kd = .5; //Diffusion/reflection constant
		vector Lhat = vecNorm(&r.dir); //Normal of vector from point to 
								       //light source.
		vector Nhat = triangleNormal(&tglobal);//Normal of triangle
		float light_intensity_diff = 1 / distance(q, &light.point) * light.diff_int; //Use point source light definition
                                                                                     //for distance dropout
		float diff_int = dotProduct(&Lhat, &Nhat) * kd * light_intensity_diff; //Diffusion Intensity
        float ks = .7;
        
        ray V = reflectedRay(&view, &Nhat, q);//Viewer ray
        V.dir = vecNorm(&V.dir);
        ray R = reflectedRay(&r, &Nhat, q);//Perfectly reflected light ray
        R.dir = vecNorm(&R.dir);



        view.dir = vecNorm(&view.dir);
        float RdotV = dotProduct(&view.dir, &R.dir);
        float light_intensity_spec = 1 / distance(q, &light.point) * light.spec_int; 
        float spec_int = pow(RdotV, gamma) * light_intensity_spec * ks;

		color += diff_int;
        if (spec_int > 0)
        {
            color += spec_int;
        }
        
	}
	//End the for loop

	return color;
}


float Trace(ray *r, int depth){
	float ia = .1; //This needs to become global
	
    if (depth >4) //Checks if maximum recursion depth is met
	{
		return ia;
	}

	hit_tri q = Intersect(r);
	
	
	if (q.FLAG==0){
		
		return ia;
	}
	//This is the color of the pixel in intensity  for one 
	//color chanel (RGB)
	float color;



	color = AccLightSource(&q.point,r);
	//printf("color = :%f\n", color);
	//Reflection and refraction recursion starts here
	return color;
}



//http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
void writePPM(const char *filename, unsigned char myimg[WIDTH][HEIGHT][3], int w, int h)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
    }

    //write the header file
    //image format
    fprintf(fp, "P6\n");

    //image size
    fprintf(fp, "%d %d\n",w,h);

    // rgb component depth
    fprintf(fp, "%d\n",255);

    // pixel data
    fwrite(myimg, 3, w*h, fp);
    fclose(fp);
}



int main()
{
	light.point.x = -1;
	light.point.y = 0;
	light.point.z = 2;
	light.diff_int = 1400;
    light.spec_int = 700;

	tglobal.p1.x = 3; //Triangle is parallel to the yz plane, and is isoceles.
	tglobal.p1.y = 3;
	tglobal.p1.z = -3;

	tglobal.p2.x = 3;
	tglobal.p2.y = -3;
	tglobal.p2.z = -3;

	tglobal.p3.x = 3;
	tglobal.p3.y = 0;
	tglobal.p3.z = 4;

    ray r;
    r.start.x = 0;
    r.start.y = 0;
    r.start.z = 0;

    r.dir.x = 4;
    r.dir.y = 0;
    r.dir.z = 0;

    int y,z;

    unsigned char img[WIDTH][HEIGHT][3];

    float yf;
    float zf;
    for (z=0;z<HEIGHT;z++){
    	zf = z;
        r.dir.z = ((zf-HEIGHT/2)/HEIGHT) * 20;
        for (y=0;y<WIDTH;y++){
        	yf = y;
            r.dir.y = ((yf-WIDTH/2)/WIDTH) * 20;

        	float red = Trace(&r, 0);
            if (red > 255.0)
            {
                red = 255.0;
            }
            img[z][HEIGHT-y][0] = red;
            img[z][HEIGHT-y][1] = 0;
            img[z][HEIGHT-y][2] = 0;

    
        }
    }

    writePPM("image.ppm",img,WIDTH,HEIGHT);

    return 0;
}
