#define WIDTH 800
#define HEIGHT 800
//global variable to define light source
point_light light;

/*Calculates the point of intersection between the ray 
and the plane of the triangle. If the ray is firing
in the wrong direction, then the FLAG variable
is set to 0, signaling a lack of intersection
with the plane of the triangle.*/
hit_tri planeIntersect(triangle *tri, ray *r){
    /*Formula is (a . n)/(r . n)*/

    vector n = triangleNormal(tri);
    vector a = vecSub(&tri->p1, &r->start);
    float d = dotProduct(&a, &n)/dotProduct(&r->dir, &n);
    if (d<=0)
    {
        hit_tri no_intersect;
        no_intersect.FLAG = 0;
        no_intersect.normal = tri->normal;
        return no_intersect;
    }
    vector v1 = vecScale(&r->dir, &d);
    vector v2 = r->start;
    hit_tri result;

    result.point = vecSum(&v1, &v2);
    result.FLAG = 1;
    result.normal = tri->normal;
    return result;
}

triangle tri_init(triray* m, int i){
    triangle t;


    t.normal.x = m->triangles[i][0][0]; 
    t.normal.y = m->triangles[i][0][1];
    t.normal.z = m->triangles[i][0][2];
    
    t.p1.x = m->triangles[i][1][0];
    t.p1.y = m->triangles[i][1][1];
    t.p1.z = m->triangles[i][1][2];

    t.p2.x = m->triangles[i][2][0];
    t.p2.y = m->triangles[i][2][1];
    t.p2.z = m->triangles[i][2][2];

    t.p3.x = m->triangles[i][3][0];
    t.p3.y = m->triangles[i][3][1];
    t.p3.z = m->triangles[i][3][2];
    return t;
}

/*Rotates an STL around a z axis based on a point*/
void rot_object(triray *m, vector o, float angle){
    vector temp;
    temp.x = 0;
    temp.y = 0;
    temp.z = 0;
    vector temp2;
    temp2.x = 0;
    temp2.y = 0;
    temp2.z = 0;

    
    for (int i = 0; i < m->length; ++i)
    {
        temp.x = m->triangles[i][0][0];
        temp.y = m->triangles[i][0][1];
        temp.z = m->triangles[i][0][2];
        
        temp2 = z_rot(temp, angle);
        
        m->triangles[i][0][0] = temp2.x;
        m->triangles[i][0][1] = temp2.y;
        m->triangles[i][0][2] = temp2.z;

        for (int j = 1; j < 4; ++j)
        {
            
            temp.x = m->triangles[i][j][0];
            temp.y = m->triangles[i][j][1];
            temp.z = m->triangles[i][j][2];
            
            temp2 = rot_point(temp, o, angle);
            
            m->triangles[i][j][0] = temp2.x;
            m->triangles[i][j][1] = temp2.y;
            m->triangles[i][j][2] = temp2.z;
        }

    }

}

/*Returns the index of the minimum, non-zero value in an array.*/
int find_minimum(float a[], int n) {
    float min = 0;
    int index = 0 ;
    float epsilon = .01;
    min = a[0];

    for (int c = 0; c < n; c++) {
        if ((a[c] < min) && (a[c] > epsilon)){
            index = c;
            min = a[c];
        }
    }
    return index;
}

/*Checks to see if point of intersection lies within the
bounds of the triangle

Returns true or false*/
int inTri(triangle *t, vector *p){
    // define vectors from point to point of triangle
    // to define triangle boundaries
    vector v1 = vecSub(&t->p1, &t->p2);
    vector v2 = vecSub(&t->p2, &t->p3);
    vector v3 = vecSub(&t->p3, &t->p1);

    vector n = triangleNormal(t);

    vector cv1 = crossProduct(&v1, &n);
    vector cv2 = crossProduct(&v2, &n);
    vector cv3 = crossProduct(&v3, &n);

    // define vectors from given point to 
    // one of the points that make up the triangle
    vector fplane1 = vecSub(p, &t->p1);
    vector fplane2 = vecSub(p, &t->p2);
    vector fplane3 = vecSub(p, &t->p3);

    // determine if given point lies above
    // or below plane defined by triangle
    float dv1 = dotProduct(&cv1, &fplane1);
    float dv2 = dotProduct(&cv2, &fplane2);
    float dv3 = dotProduct(&cv3, &fplane3);

    // if all three have positive directions
    // point does lies within inside triangle
    // and so returns true (which returns 1)
    if ((dv1 >= 0) && (dv2 >= 0) && (dv3 >= 0)) {
        return 1;
    }
    else {
        return 0;
    }
}

//http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
void writePPM(const char *filename, unsigned char myimg[HEIGHT][WIDTH][3], int w, int h)
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

void printProg(float progress, int images){
    int barWidth = 70;

    printf("Rendering: [");
    int pos = barWidth * progress;
    for (int p = 0; p < barWidth; ++p) {
        if (p < pos){
            printf("=");
        }else if (p == pos) {
            printf(">");
        }
        else printf(" ");
    }
    int print_prog = progress * 100.0;
    printf("] %d%% \r", print_prog);
    fflush(stdout);
}

/*Returns the point of intersection between 
a ray and the nearest object (just one triangle
for now). Otherwise, it returns None. 
The inputed triangle should be removed
when function is verified to work, and
the function should act on a global 
collection of triangles called an object*/
hit_tri Intersect(ray r, triray m){


    int hit_array[m.length];
    float hit_dist[m.length]; //This is the distance of the hit point to the camera.
    triangle t;

    int isHit = 0;

    hit_tri find_intersect;
    find_intersect.point.x = 0;
    find_intersect.point.y = 0;
    find_intersect.point.z = 0;
    find_intersect.normal.x = 0;
    find_intersect.normal.y = 0;
    find_intersect.normal.z = 0;
    find_intersect.FLAG = 0;
    find_intersect.index = 0;

    vector camera;
    camera.x = 0;
    camera.y = 0;
    camera.z = 0;

    for (int i = 0; i < m.length; ++i)
    {
        t = tri_init(&m, i);
        
        find_intersect = planeIntersect(&t, &r);

        if ((find_intersect.FLAG) && (inTri(&t,&find_intersect.point))){
            find_intersect.FLAG = 1;
            hit_array[i] = 1;
            hit_dist[i] = distance(&find_intersect.point, &camera);

            

        }else{
            find_intersect.FLAG = 0;
            hit_array[i] = 0;
            hit_dist[i] = 100;
            
        }
    }

    for (int j = 0; j < m.length; ++j)
    {
        if (hit_array[j] == 1)
        {
            
            isHit = 1;
        }
    }

    if (isHit) //Checks if any triangle has been hit.
    {
        int min = find_minimum(hit_dist, m.length);
        //printf("min = %d\n", min);
        triangle result = tri_init(&m, min);
        find_intersect = planeIntersect(&result, &r);
        find_intersect.FLAG = 1;
        find_intersect.index = min;
    }

    return find_intersect;

}

/*Returns a ray in the direction of the reflected
ray given by the normal of the surface and the initial
ray. Takes as input the ray, the normal to the 
triangle, and a vector that represents the point
of intersection between the ray and the triangle*/
ray reflectedRay(ray *d, vector *n, vector *p){
    ray sent_ray = *d;
    sent_ray.dir.x = -sent_ray.dir.x;
    sent_ray.dir.y = -sent_ray.dir.y;
    sent_ray.dir.z = -sent_ray.dir.z;


    vector normal_vector = *n;
    vector point = *p;
    sent_ray.dir = vecNorm(&sent_ray.dir);
    normal_vector = vecNorm(&normal_vector);

    float dn = 2*(dotProduct(&sent_ray.dir, &normal_vector));
    vector c = vecScale(&normal_vector, &dn);
    ray result;
    result.dir = vecSub(&c, &sent_ray.dir);
    result.start = point;

    return result;
}

/*This function accumulates the light gathered
from all of the light sources.
It takes in a point, which is the point of intersection
between the ray and the triangle, and the normal of 
the triangle, and the vector of the direction of the 
ray hitting the triangle (used for specular highlights).
Currently, it just does this for one light source. It needs
to be able to loop.*/
float AccLightSource(vector *q, ray *v, triray *stl, int index){
    float ia = 30; //This needs to become global
    float color = ia;
    float gamma = 15;
    float ka = 1;
    ray view = *v;

    vector buffer; //This is the distance away from the triangle's
                   //surface that the ray should start so that the intersect
                   //is correctly calculated without ambiguity. 
    buffer.x = -view.dir.x * .01;
    buffer.y = -view.dir.y * .01;
    buffer.z = -view.dir.z * .01;

    //For loop goes here, to do all light sources
    ray r;
    r.start = vecSum(q, &buffer);
    vector rdir = vecSub(&light.point, &r.start);
    r.dir = rdir;
    r.dir = vecNorm(&r.dir);
    hit_tri w = Intersect(r, *stl);

    //This checks if the ray intersects
    //something before hitting a light source.

    if (w.FLAG == 0)
    { 
        float kd = .5; //Diffusion/reflection constant
         
        vector Lhat = r.dir;
                                       //light source.
        triangle normal_tri = tri_init(stl, index);
        vector Nhat = triangleNormal(&normal_tri);//Normal of triangle
        
        float light_intensity_diff = 1 / distance(q, &light.point) * light.diff_int; //Use point source light definition
                                                                                     //for distance dropout
        float diff_int =  dotProduct(&Lhat, &Nhat) * kd * light_intensity_diff;  //Diffusion Intensity
        float ks = .7;
        ray V = reflectedRay(&view, &Nhat, q);//Viewer ray
        V.dir = vecNorm(&V.dir);
        ray R = reflectedRay(&r, &Nhat, q);//Perfectly reflected light ray
        R.dir = vecNorm(&R.dir);

        view.dir = vecNorm(&view.dir);
        float RdotV = dotProduct(&view.dir, &R.dir);
        float light_intensity_spec = 1.0 / distance(q, &light.point) * light.spec_int; 
        float spec_int = pow(RdotV, gamma) * light_intensity_spec * ks;
        if (diff_int >=0)
        {
            color += fabs(diff_int);
        }
        if (spec_int > 0)
        {
            color += spec_int;
        }

    }
    color += ia*ka;
    //End the for loop

    return color;
}

float Trace(ray *r, int depth, triray *stl){
    float ia = 30; //This needs to become global
    
    if (depth >4) //Checks if maximum recursion depth is met
    {
        return ia;
    }
    hit_tri q = Intersect(*r, *stl);

    if (q.FLAG==0){
        
        return ia;
    }
    //This is the color of the pixel in intensity  for one 
    //color chanel (RGB)
    float color;

    color = AccLightSource(&q.point, r, stl, q.index);
    //Reflection and refraction recursion starts here
    return color;
}