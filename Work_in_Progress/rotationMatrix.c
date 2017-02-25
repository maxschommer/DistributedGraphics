#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../main.h"
#define PI 3.141592653587

vector xRotate(vector *v, float alpha){
	triangle matrix;
	vector new_vector;
	float rad = PI / 180 * alpha;

	matrix.p1.x = 1;
	matrix.p1.y = 0;
	matrix.p1.z = 0;

	matrix.p2.x = 0;
	matrix.p2.y = cos(rad);
	matrix.p2.z = sin(rad);

	matrix.p3.x = 0;
	matrix.p3.y = -sin(rad);
	matrix.p3.z = cos(rad);

	new_vector.x = dotProduct(&matrix.p1, v);
	new_vector.y = dotProduct(&matrix.p2, v);
	new_vector.z = dotProduct(&matrix.p3, v);

	return new_vector;
}


vector yRotate(vector *v, float beta){
	triangle matrix;
	vector new_vector;
	float rad = PI / 180 * beta;

	matrix.p1.x = cos(rad);
	matrix.p1.y = 0;
	matrix.p1.z = -sin(rad);

	matrix.p2.x = 0;
	matrix.p2.y = 1;
	matrix.p2.z = 0;

	matrix.p3.x = sin(rad);
	matrix.p3.y = 0;
	matrix.p3.z = cos(rad);

	new_vector.x = dotProduct(&matrix.p1, v);
	new_vector.y = dotProduct(&matrix.p2, v);
	new_vector.z = dotProduct(&matrix.p3, v);

	return new_vector;
}

vector zRotate(vector *v, float gamma){
	triangle matrix;
	vector new_vector;
	float rad = PI / 180 * gamma;

	matrix.p1.x = cos(rad);
	matrix.p1.y = sin(rad);
	matrix.p1.z = 0;

	matrix.p2.x = -sin(rad);
	matrix.p2.y = cos(rad);
	matrix.p2.z = 0;

	matrix.p3.x = 0;
	matrix.p3.y = 0;
	matrix.p3.z = 1;

	new_vector.x = dotProduct(&matrix.p1, v);
	new_vector.y = dotProduct(&matrix.p2, v);
	new_vector.z = dotProduct(&matrix.p3, v);

	return new_vector;
}

vector rotate(vector *v, float x, float y, float z){
	vector new_vector;
	vector v1, v2;
	v1 = xRotate(v, x);
	v2 = yRotate(&v1, y);
	new_vector = zRotate(&v2, z);
	return new_vector;
}

int main(){
	vector v, u;
	v.x = 3;
	v.y = 4;
	v.z = 5;

	u = rotate(&v, 0, 45, 0);
	printf("the new vector is (%f, %f, %f)\n", u.x, u.y, u.z);
}
