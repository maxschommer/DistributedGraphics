/*Computes the location of the intersection between 
a ray and a triangle*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "parse_stl.c"
#include "raytracermake.h"
#include "algebrafuncs.c"
#include "raytracerfuncs.c"
#define WIDTH 800
#define HEIGHT 800


int main(int argc, char *argv[])
{
	light.point.x = -1;
	light.point.y = 0;
	light.point.z = 2;
	light.diff_int = 600;
    light.spec_int = 2400;

    ray r;
    r.start.x = 0;
    r.start.y = 0;
    r.start.z = 0;

    r.dir.x = 4;
    r.dir.y = 0;
    r.dir.z = 0;

    triray stl;

    stl = search_for_vertex(argv[1]);
    int images = 100;
    float progress = 0.0;
    for (int i = 0; i < images; ++i)
    {
        progress = 1.0*i/images;
        printProg(progress, i);

        int y,z;

        unsigned char img[HEIGHT][WIDTH][3];

        float yf;
        float zf;
        
        for (z=0;z<HEIGHT;z++){
            zf = z;
            r.dir.z = ((zf-HEIGHT/2)/HEIGHT) * 12;
            for (y=0;y<WIDTH;y++){
                // Iterate over the pixels of the image

                yf = y;
                r.dir.y = ((yf-WIDTH/2)/WIDTH) * 12;

                float red = Trace(&r, 0, &stl);

                if (red > 255.0)
                {
                    red = 255.0;
                }
                img[HEIGHT-z-1][y][0] = red;
                img[HEIGHT-z-1][y][1] = 0;
                img[HEIGHT-z-1][y][2] = 0;

            }
        }
        char str[20];
        snprintf(str, sizeof(str), "Images/image%03d.ppm", i);
        writePPM(str, img,WIDTH,HEIGHT);

        vector o = {5,0,0};
        float angle = 3.14159/100/4;
        rot_object(&stl, o, angle);

    }

    return 0;
}
