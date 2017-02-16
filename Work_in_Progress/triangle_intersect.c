/*Computes the location of the intersection between 
a ray and a triangle*/

#include <stdio.h>
#include <stdbool.h>
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
    float refract;
}ray;

/*This is a fast inverse square root function.
I did not write it, and barely comprehend it.*/
float Q_rsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the flux? 
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

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
    float invSqrt = Q_rsqrt((v->x)*(v->x)+(v->y)*(v->y)+(v->z)*(v->z));
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
    return result;
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
and the plane of the triangle*/
vector triangleIntersect(triangle *tri, ray *r){
    /*Formula is (a . n)/(r . n)*/
    vector n = triangleNormal(tri);
    vector a = vecSub(&tri->p1, &r->start);
    float d = dotProduct(&a, &n)/dotProduct(&r->dir, &n);
    vector v1 = vecScale(&r->dir, &d);
    vector v2 = r->start;
    vector result = vecSum(&v1, &v2);
    return result;
}

/*Checks to see if point of intersection lies within the
bounds of the triangle

Returns true or false*/
bool inTri(triangle *t, vector *p){
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
	if ((dv1 >= 0) && (dv2 >= 0) && (dv3 >= 0)) {
		return true;
	}
	else {
		return false;
	}
}
/*Returns a vector in the direction of the reflected
ray given by the normal of the surface and the initial
ray.*/
vector reflectedRay(ray *d, vector *n){
	float dn = 2*(dotProduct(&d->dir, n));
	vector c = vecScale(n, &dn);
	vector r = vecSub(&d->dir, &c);
	return r;
}


int main()
{
    triangle t;
    t.p1.x = 3; //Triangle is parallel to the yz plane, and is isoceles.
    t.p1.y = 3;
    t.p1.z = 0;

    t.p2.x = 3;
    t.p2.y = -3;
    t.p2.z = 0;
    
    t.p3.x = 3;
    t.p3.y = 0;
    t.p3.z = 6;

    ray r;
    r.start.x = 0;
    r.start.y = 0;
    r.start.z = 0;

    r.dir.x = 4;
    r.dir.y = 0;
    r.dir.z = 0;

    /*vector cross = crossProduct(&t.p1, &t.p2);
    vector norm = triangleNormal(&t);
    triangle inv = matInv(&t);

    vector intersect = triangleIntersect(&t, &r);
    bool inside = inTri(&t, &intersect);

    printf("%f, %f, %f\n", norm.x, norm.y, norm.z); //The modified vR is the cross product
    printf("|%.3f %.3f %.3f|\n|%.3f %.3f %.3f|\n|%.3f %.3f %.3f|\n", inv.p1.x, inv.p1.y, inv.p1.z, inv.p2.x, inv.p2.y, inv.p2.z, inv.p3.x, inv.p3.y, inv.p3.z);

    printf("%f\n", det3x3(&t));
    printf("(%f, %f, %f\n)", intersect.x, intersect.y, intersect.z);
    printf("%d\n", inside);*/

    int y,z;
    bool inside;

    for (z=10;z>-11;z--){
        r.dir.z=z;
        printf("\n");
        for (y=-10; y<11;y++){
            r.dir.y = y;
            vector intersect = triangleIntersect(&t, &r);
            inside = inTri(&t,&intersect);
            if (inside){
                printf("++");
            }else{
                printf("--");
            }
        }
    }
    r.start.x = 0;
    r.start.y = 0;
    r.start.z = 0;

    r.dir.x = 4;
    r.dir.y = 0;
    r.dir.z = 0;
    vector norm = triangleNormal(&t);
    vector Ref = reflectedRay(&r, &norm);
    printf("\nNormal:      \n%f, %f, %f\n", norm.x, norm.y, norm.z);
    printf("Unreflected: \n%f, %f, %f\n", r.dir.x, r.dir.y, r.dir.z);
    printf("Reflected:   \n%f, %f, %f\n", Ref.x, Ref.y, Ref.z);
    return 0;
}
