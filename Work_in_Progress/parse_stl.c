#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h> 


int Search_in_File(char *fname) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];

	if((fp = fopen(fname, "r")) == NULL) {
		return(-1);
	}

	// float numbers[12][3][3];
	// int i,j,k;

	// for (i=0;i<12;i++){
	// 	for (j=0;j<3;j++){
	// 		for(k=0;k<3;k++){

	// 		}
	// 	}
	// }

	int i = 0;
	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, "vertex")) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);

			float numbers[12][3];
			char g[10];
			if (sscanf(temp,"%s %f %f %f",g, &numbers[i][0], &numbers[i][1], &numbers[i][2])){
				printf("%f %f %f\n", numbers[i][0], numbers[i][1], numbers[i][2]);
				i++;
			};
			//printf("%f %f %f\n", numbers[0], numbers[1], numbers[2]);

			find_result++;
		}
		line_num++;
	}


	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	//Close the file if still open.
	if(fp) {
		fclose(fp);
	}
   	return(0);
}

int main(int argc, char *argv[]) {
	int result, errno;

	//Use system("cls") on windows
	//Use system("clear") on Unix/Linux
	system("clear");

	result = Search_in_File(argv[1]);
	if(result == -1) {
		perror("Error");
		printf("Error number = %d\n", errno);
		exit(1);
	}
	return(0);
}