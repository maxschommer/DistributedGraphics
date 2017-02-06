#include <stdio.h>
#include <stdbool.h>

typedef struct{
    float x,y,z;
}vector;

typedef struct{
    vector pos;
    float radius;
}sphere;

typedef struct{
    vector start;
    vector dir;
}ray;

//http://www.purplealienplanet.com/node/20
vector vectorSub(vector *v1, vector *v2){
    vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
    return result;
}

float vectorDot(vector *v1, vector *v2){
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

bool intersectRaySphere(ray *r, sphere *s){

    float A = vectorDot(&r->dir, &r->dir); 

    /* vector representing the distance between the start of 
    * the ray and the position of the circle.
    */
    vector dist = vectorSub(&r->start, &s->pos);
  
    float B = 2 * vectorDot(&r->dir, &dist);

    float C = vectorDot(&dist, &dist) - (s->radius * s->radius);

    /* Solving the discriminant */
    float discr = B * B - 4 * A * C;

    if(discr < 0)
        return false;
    else
        return true;
}
