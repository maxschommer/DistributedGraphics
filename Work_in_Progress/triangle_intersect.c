/*Computes the location of the intersection between 
a ray and a triangle*/

#include <stdio.h>
#include <stdbool.h>
#include "../main.h"

//REMINDER: Use Fast inverse square root

/*Calculates the point of intersection between the ray 
and the plane of the triangle*/
vector triangleIntersect(triangle *tri, ray *r){
    vector triNormal = triangleNormal(&tri);  
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
    printf("%f, %f, %f\n", norm.x, norm.y, norm.z); //The modified vR is the cross product
    
}
