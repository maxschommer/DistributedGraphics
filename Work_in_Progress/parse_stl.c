#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h> 

float numbers[25][3][3];

//parses a file line by line and adds points to 3d array if line contains the string "vertex"
int search_for_vertex(char *fname) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];

	if((fp = fopen(fname, "r")) == NULL) {
		return(-1);
	}

	int i = 0;
	int j = 0;

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, "vertex")) != NULL) {
			//printf("A match found on line: %d\n", line_num);
			//printf("\n%s\n", temp);

			char g[10];
			if (sscanf(temp,"%s %f %f %f",g, &numbers[i][j][0], &numbers[i][j][1], &numbers[i][j][2])){
				//printf("%f %f %f\n", numbers[i][j][0], numbers[i][j][1], numbers[i][j][2]);
				j++;
				if (j==3){
					i++;
					//printf("\n");
					j=0;
				}
			};

			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	//Close the file
	fclose(fp);

   	return(0);
}

int main(int argc, char *argv[]) {
	int result, errno;

	//Use system("cls") on windows
	//Use system("clear") on Unix/Linux
	system("clear");

	result = search_for_vertex(argv[1]);
	if(result == -1) {
		perror("Error");
		printf("Error number = %d\n", errno);
		exit(1);
	}

	//prints out content of 3d array
	int i,j;
	for (i=0;i<12;i++){
		for(j=0;j<3;j++){
			printf("%f %f %f\n", numbers[i][j][0], numbers[i][j][1], numbers[i][j][2]);
		}
		printf("%d\n",i);
	}

	return(0);
}