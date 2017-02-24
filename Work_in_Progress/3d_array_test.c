#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

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

int main(void)
{
    float ***data;
    size_t xlen = 10;
    size_t ylen = 100;
    size_t zlen = 300;
    size_t i, j, k;

    srand((unsigned int)time(NULL));
    if ((data = alloc_data(xlen, ylen, zlen)) == NULL)
        return EXIT_FAILURE;

    for (i=0; i < xlen; ++i)
        for (j=0; j < ylen; ++j)
            for (k=0; k < zlen; ++k)
                data[i][j][k] = 20.0;

    printf("%f\n", data[1][2][1]);
    free_data(data, xlen, ylen);
    return EXIT_SUCCESS;
}