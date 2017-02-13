#include <stdio.h>
#include <stdbool.h>

//http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
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

#define WIDTH 800
#define HEIGHT 500

int main (int argc, char *argv){
    sphere s;
    ray r;

    s.pos.x = 500;
    s.pos.y = 300;
    s.pos.z = 500;

    s.radius = 100;

    r.dir.x = 0;
    r.dir.y = 0;
    r.dir.z = 1;

    r.start.z = 0;

    bool hit;

    int x,y;
    unsigned char img[WIDTH * HEIGHT * 3];

    for (y=0;y<HEIGHT;y++){
        r.start.y = y;
        for (x=0;x<WIDTH;x++){
            r.start.x = x;

            hit = intersectRaySphere(&r, &s);
            if (hit){
                img[(x+y*WIDTH)*3 +0] = 255;
                img[(x+y*WIDTH)*3 +1] = 128;
                img[(x+y*WIDTH)*3 +2] = 0;
            }else{
                img[(x+y*WIDTH)*3 +0] = 0;
                img[(x+y*WIDTH)*3 +1] = 0;
                img[(x+y*WIDTH)*3 +2] = 0;
            }
        }
    }

    writePPM("image.ppm",img,WIDTH,HEIGHT);

    return 0;
}
