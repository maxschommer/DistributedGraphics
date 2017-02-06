#include <stdio.h>

int main()
{
float point[3];

printf("Enter the values of your point: ");
scanf("%f", &point[0]);
scanf("%f", &point[1]);
scanf("%f", &point[2]);
printf("Your point is:[%f,%f,%f]\n", point[0], point[1], point[2]);
}
