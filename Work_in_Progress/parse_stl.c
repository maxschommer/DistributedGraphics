#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <time.h>

typedef struct 
{
	int length;
	float*** triangles;
}triray;

//http://stackoverflow.com/questions/2306172/malloc-a-3-dimensional-array-in-c
void free_data(float ***data, size_t xlen, size_t ylen)
{
    size_t i, j;

    for (i=0; i < xlen; ++i) {
        if (data[i] != NULL) {
            for (j=0; j < ylen; ++j)
                free(data[i][j]);
            free(data[i]);
        }
    }
    free(data);
}

//http://stackoverflow.com/questions/2306172/malloc-a-3-dimensional-array-in-c
float ***alloc_data(size_t xlen, size_t ylen, size_t zlen)
{
    float ***p;
    size_t i, j;

    if ((p = malloc(xlen * sizeof *p)) == NULL) {
        perror("malloc 1");
        return NULL;
    }

    for (i=0; i < xlen; ++i)
        p[i] = NULL;

    for (i=0; i < xlen; ++i)
        if ((p[i] = malloc(ylen * sizeof *p[i])) == NULL) {
            perror("malloc 2");
            free_data(p, xlen, ylen);
            return NULL;
        }

    for (i=0; i < xlen; ++i)
        for (j=0; j < ylen; ++j)
            p[i][j] = NULL;

    for (i=0; i < xlen; ++i)
        for (j=0; j < ylen; ++j)
            if ((p[i][j] = malloc(zlen * sizeof *p[i][j])) == NULL) {
                perror("malloc 3");
                free_data(p, xlen, ylen);
                return NULL;
            }
    return p;
}

//parses a file line by line and adds points to 3d array if line contains the string "vertex"
triray search_for_vertex(char *fname) {
	FILE *fp;
	int line_num = 1;
	int num_of_lines = 0;
	int find_result = 0;
	char temp[512];

	int ch = 0;
	int number_of_lines = 0;

	fp = fopen(fname, "r");

	//iterate once through the file to find number of lines
	while(fgets(temp, 512, fp) != NULL) {
		if((((strstr(temp, "vertex")) != NULL) | ((strstr(temp, "normal")) != NULL))){
			number_of_lines++;
		}
		ch++;
	}

	//close and open the file again for the 2nd loop
	fclose(fp);
	fp = fopen(fname, "r");


	int i = 0;
	int j = 0;

	float*** numbers;
	size_t xlen = (number_of_lines/4);
    size_t ylen = 4;
    size_t zlen = 3;

    //allocate data
    numbers = alloc_data(xlen, ylen, zlen);

    //assign values to the 3d arary called numbers
	while(fgets(temp, 512, fp) != NULL) {
		if(((strstr(temp, "vertex")) != NULL)){
			num_of_lines++;

			char g[10];

			sscanf(temp,"%s %f %f %f",g, &numbers[i][j][0], &numbers[i][j][1], &numbers[i][j][2]);
			// printf("%s\n", temp);
			// printf("%f %f %f\n", numbers[i][j][0], numbers[i][j][1], numbers[i][j][2]);
				j++;
				if (j==4){
					i++;
					//printf("\n");
					j=0;

				}

			find_result++;

		}else if (((strstr(temp, "facet normal")) != NULL))
		{
			num_of_lines++;

			char g[40];
			char d[10];

			sscanf(temp,"%s %s %f %f %f",g, d, &numbers[i][j][0], &numbers[i][j][1], &numbers[i][j][2]);
			
				j++;
				if (j==4){
					i++;
					//printf("\n");
					j=0;

				}

			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	//Close the file
	fclose(fp);

	triray object;
	object.triangles = numbers;
	object.length = xlen;
	printf("%d\n",object.length);

   	return(object);
}

// int main(int argc, char *argv[]) {
// 	float*** result;
// 	int errno;

// 	//Use system("cls") on windows
// 	//Use system("clear") on Unix/Linux
// 	system("clear");

// 	result = search_for_vertex(argv[1]);

// 	//prints out content of 3d array
// 	// int i,j;
// 	// for (i=0;i<96;i++){
// 	// 	for(j=0;j<3;j++){
// 	// 		printf("%f %f %f\n", result[i][j][0], result[i][j][1], result[i][j][2]);
// 	// 	}
// 	// 	printf("%d\n",i);
// 	// }

// 	return(0);
// }
