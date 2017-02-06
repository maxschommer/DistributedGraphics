#include <stdio.h>
#include <stdbool.h>

//REMINDER: Use Fast inverse square root

typedef struct{
    float x,y,z;
}vector;

typedef struct{
    vector p1;
    vector p2;
    vector p3;
}triangle;

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

float dotProduct(vector *v1, vector *v2){
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/*This subtracts vector 2 from vector 1. Ex. v1-v2 */
vector vecSub(vector *v1, vector* v2){
    vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return result;
}

vector vecNorm(vector *v){
    float invSqrt = Q_rsqrt((v->x)*(v->x)+(v->y)*(v->y)+(v->z)*(v->z));
    vector result = {(v->x)*invSqrt, (v->y)*invSqrt, (v->z)*invSqrt};
    return result;
}

vector crossProduct(vector *u, vector *v){
    vector result;
    result.x = u->y * v->z - u->z * v->y;
    result.y = u->z * v->x - u->x * v->z;
    result.z = u->x * v->y - u->y * v->x;
    return result;
}
