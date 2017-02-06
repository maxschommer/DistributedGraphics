#include <stdio.h>
#include <stdbool.h>
#include "../main.h"

//REMINDER: Use Fast inverse square root

/*We define v1 as p3-p1, and v2 as p2-p1. We
take the cross product of these (v1 x v2) and normalize
in order to find the unit normal.*/
vector triangleNormal(triangle *tri){
    vector v1 = vecSub(&tri->p3, &tri->p1);
    vector v2 = vecSub(&tri->p2, &tri->p1);
    vector cross = crossProduct(&v1, &v2);
    vector result = vecNorm(&cross);
    return result;
}

int main()
{
    triangle t;
    t.p1.x = 3; //Triangle is parrell to the yz plane, and is isoceles.
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
