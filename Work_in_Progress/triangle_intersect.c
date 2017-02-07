/*Computes the location of the intersection between 
a ray and a triangle*/

#include <stdio.h>
#include <stdbool.h>

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

/*This subtracts vector 2 from vector 1. Ex. v1-v2 */
vector vecSub(vector *v1, vector* v2){
    vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return result;
}

/*Returns the unit vector of a vector input.*/
vector vecNorm(vector *v){
    float invSqrt = Q_rsqrt((v->x)*(v->x)+(v->y)*(v->y)+(v->z)*(v->z));
    vector result = {(v->x)*invSqrt, (v->y)*invSqrt, (v->z)*invSqrt};
    return result;
}

/*Returns the crosproduct u x v for two vectors
u and v.*/
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
    vector triNormal = triangleNormal(tri);
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
    t.p3.z = 3;

    vector cross = crossProduct(&t.p1, &t.p2);
    vector norm = triangleNormal(&t);
    triangle inv = matInv(&t);
    printf("%f, %f, %f\n", norm.x, norm.y, norm.z); //The modified vR is the cross product
    printf("|%.3f %.3f %.3f|\n|%.3f %.3f %.3f|\n|%.3f %.3f %.3f|\n", inv.p1.x, inv.p1.y, inv.p1.z, inv.p2.x, inv.p2.y, inv.p2.z, inv.p3.x, inv.p3.y, inv.p3.z);

    printf("%f", det3x3(&t));
    
}
