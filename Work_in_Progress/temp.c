/*Computes the location of the intersection between 
a ray and a triangle*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define WIDTH 80
#define HEIGHT 50
/*#include "../main.h"
*/


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
ray.*/
ray reflectedRay(ray *d, vector *n, vector *p){
	float dn = 2*(dotProduct(&d->dir, n));
	vector c = vecScale(n, &dn);
	ray result;
	result.dir = vecSub(&d->dir, &c);
	result.start = *p;
	return result;
}

/*This function accumulates the light gathered
from all of the light sources. Currently,
it just does this for one light source. It needs
to be able to loop.*/
float AccLightSource(vector *q){
	float ia = .1; //This needs to become global
	float color = ia;
	//For loop goes here, to do all light sources
	ray r;
	r.start = *q;
	r.dir = vecSub(&light.point, q);

	hit_tri w = Intersect(&r);
    printf("wFLAG = %d \n", w.FLAG);
    //printf("Wflag %d\n",w.FLAG );
	//This checks if the ray intersects
	//something before hitting a light source.
	//Its not reliable, and should be improved
	//if (w.FLAG == 0)
	//{
		float kd = .5; //Diffusion/reflection constant
		vector Lhat = vecNorm(&r.dir); //Normal of vector from point to 
								//light source.
		vector Nhat = triangleNormal(&tglobal);//Normal of triangle
		float light_intensity = 1 / distance(q, &light.point) * light.diff_int;
		/*if (w.FLAG)
		{
			printf("light_intensity: %f\n", light_intensity);
		}*/
		float diff_int = dotProduct(&Lhat, &Nhat) * kd * light_intensity;
        //printf("Diff Int: %f \n", diff_int);




		color += diff_int;
		//color += specular intensity;*/
        //printf("color = %f \n", diff_int);
	//}
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
	//printf("\nq = %f, %f, %f, %d\n", q.point.x, q.point.y,q.point.z, q.FLAG);

	
	if (q.FLAG==0){
		//printf("Target Hit!");
		return ia;
	}
	//This is the color of the pixel in intensity  for one 
	//color chanel (RGB)
	float color;



	color = AccLightSource(&q.point);
	//printf("color = :%f\n", color);
	//Reflection and refraction recursion starts here
	return color;
}



//http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
void writePPM(const char *filename, unsigned char *myimg, int w, int h)
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
	light.point.z = 0;
	light.diff_int = 500;

	tglobal.p1.x = 3; //Triangle is parallel to the yz plane, and is isoceles.
	tglobal.p1.y = 3;
	tglobal.p1.z = 3;

	tglobal.p2.x = 3;
	tglobal.p2.y = -3;
	tglobal.p2.z = 3;

	tglobal.p3.x = 3;
	tglobal.p3.y = 0;
	tglobal.p3.z = -4;


    triangle t;

    t.p1.x = 3; //Triangle is parallel to the yz plane, and is isoceles.
    t.p1.y = 3;
    t.p1.z = 0;

    t.p2.x = 3;
    t.p2.y = -3;
    t.p2.z = 0;
    
    t.p3.x = 3;
    t.p3.y = -4;
    t.p3.z = 6;

    ray r;
    r.start.x = 0;
    r.start.y = 0;
    r.start.z = 0;

    r.dir.x = 4;
    r.dir.y = 0;
    r.dir.z = 0;

    int y,z;
    //int inside;

    for (z=10;z>-11;z--){
        r.dir.z=z;
        printf("\n");
        for (y=-10; y<11;y++){
            r.dir.y = y;
            if (Trace(&r, 0)){
                printf("++");
            }else{
                printf("--");
            }
        }
    }

//

    unsigned char img[WIDTH * HEIGHT * 3];
    float yf;
    float zf;
    for (z=0;z<HEIGHT;z++){
    	zf = z;
        r.dir.z = ((zf-HEIGHT/2)/HEIGHT) * 20;
        //printf("r.dir.z = %f", r.dir.z);
        for (y=0;y<WIDTH;y++){
        	yf = y;
            r.dir.y = ((yf-WIDTH/2)/WIDTH) * 20;
            //printf("\nyf: %f", r.dir.y);
            
/*            if (Trace(&r, 0)>.11)
            {
            	printf("Trace: %f\n", Trace(&r, 0));
            }*/
        	
            img[(WIDTH-y+z*WIDTH)*3 +0] = Trace(&r, 0);
            img[(WIDTH-y+z*WIDTH)*3 +1] = 0;
            img[(WIDTH-y+z*WIDTH)*3 +2] = 0;

    
        }
    }

    writePPM("image.ppm",img,WIDTH,HEIGHT);
//


    r.start.x = 0;
    r.start.y = 0;
    r.start.z = 0;

    r.dir.x = 4;
    r.dir.y = 1;
    r.dir.z = 0;

    hit_tri intersect = planeIntersect(&t, &r);
    vector norm = triangleNormal(&t);
    ray Ref = reflectedRay(&r, &norm, &intersect.point);
    printf("\nNormal:      \n%f, %f, %f\n", norm.x, norm.y, norm.z);
    printf("Unreflected: \n%f, %f, %f\n", r.dir.x, r.dir.y, r.dir.z);
    printf("Reflected Direction:   \n%f, %f, %f\n", Ref.dir.x, Ref.dir.y, Ref.dir.z);
    printf("Reflected Start:  %f, %f, %f\n", Ref.start.x, Ref.start.y, Ref.start.z);
    return 0;
}
