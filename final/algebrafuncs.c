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

vector z_rot(vector v, float angle){
    vector result;
    result.x = 0;
    result.y = 0;
    result.z = 0;
    result.x = cos(angle) * (v.x) - sin(angle) * (v.y);
    result.y = sin(angle) * (v.x) + cos(angle) * (v.y);
    result.z = v.z;

    return result;
}

/*Rotate a vector in the z direction around
a point in space on the xy plane*/
vector rot_point(vector r, vector o, float angle){
    vector temp;
    temp.x = 0;
    temp.y = 0;
    temp.z = 0;

    vector temp2;
    temp2.x = 0;
    temp2.y = 0;
    temp2.z = 0;
    vector result;
    result.x = 0;
    result.y = 0;
    result.z = 0;

    temp = vecSub(&r, &o);

    temp2 = z_rot(temp, angle);

    result = vecSum(&o, &temp2);

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
vector crossProduct(vector *u, vector *v){
    vector result;
    result.x = u->y * v->z - u->z * v->y;
    result.y = u->z * v->x - u->x * v->z;
    result.z = u->x * v->y - u->y * v->x;
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
    return tri->normal;
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