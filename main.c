/* 
 * File:   main.c
 * Author: adam
 *
 * Created on February 5, 2015, 5:12 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 
 */
int readfile(char *filename, char *mode, double *data) {
    int arraysize = 0;
    FILE *input = fopen(filename, mode);
    if (input == NULL) {
        printf("Error: unable to open file\n");
        // exit(EXIT_FAILURE);
    }
    int i = 0;
    int j = 0;
    fscanf(input, "%d", &arraysize);
    for (j = 0; j < arraysize; j++) {

        fscanf(input, "%lf", &data[j]);


    }



    fclose(input);

    return arraysize;

}

double calculateMean(int* array, int length) {
    double mean = 0;
    int i = 0;
    for (i = 0; i < length; i++) {

        mean += array[i];

    }
    mean = mean / length;
    return mean;

}

int calculateMode(int length, int* array) {

    int mode = 0;
    int maxCount = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < length; i++) {
        int count = 0;
        for (j = 0; j < length; j++) {

            if (array[i] == array[j]) {

                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mode = array[i];
        }

    }
    return mode;

}

int calculateMedian(int length, int* array) {
    int middle = length / 2;


    //  sort(&array,length);
    float temp;
    int i, j;
    // the following two loops sort the array x in ascending order
    for (i = 0; i < length - 1; i++) {
        for (j = i + 1; j < length; j++) {
            if (array[j] < array[i]) {
                // swap elements
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    if (length % 2 == 0)
        //if there is an even number of elements return mean of the middle two
    {
        return ((array[middle] + array[middle + 1]) / 2);
    }
    return array[middle];




}

double calculateStandardDeviation(int length, int* array) {
    double mean = calculateMean(array, length);
    double sum = 0;

    int i = 0;
    for (i = 0; i < length; i++) {

        sum += (array[i] - mean)*(array[i] - mean);
    }

    return sqrt(sum / length);
}

void histogram(int length, int* array) {
    int i = 0;

    int j = 0;
    for (i = 1; i < 11; i++) {
        printf("\n%d: ", i);
        for (j = 0; j < length; j++) {
            if (i == array[j]) {
                printf("*");
            }
        }

    }


}

int main(int argc, char** argv) {

    char* h = "dataset1.txt";
    char* e = "dataset2.txt";
    char* modes = "r";
    int n, i, *ptr;
    FILE *input = fopen(h, modes);
    if (input == NULL) {
        printf("Error: unable to open file\n");
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d", &n);
    ptr = (int*) malloc(n * sizeof (int));
    if (ptr == NULL) {
        printf("memory not allocated");
        exit(0);
    }
    for (i = 0; i < n; i++) {
        fscanf(input, "%d", ptr + i);

    }
    printf("STATISTICAL REPORT\n====================\n");
    printf("mean: %f", calculateMean(ptr, n)); //function to calculate mean
    printf("\nmode: %d", calculateMode(n, ptr));

    printf("\nStandard Deviation: %f", calculateStandardDeviation(n, ptr), "\n");
    printf("\nMedian: %d", calculateMedian(n, ptr), "\n");
    histogram(n, ptr);

    input = fopen(e, modes);
    if (input == NULL) {
        printf("Error: unable to open file\n");
        exit(1);
    }
    fscanf(input, "%d", &n);
    ptr = (int*) malloc(n * sizeof (int));
    if (ptr == NULL) {
        printf("memory not allocated");
        exit(0);
    }
    for (i = 0; i < n; i++) {
        fscanf(input, "%d", ptr + i);

    }
    FILE *f = fopen("statsreport.txt","w");
    if(f==NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f,"=========Statistical Report=======\r\n",1);
    fprintf(f,"\r\n========DATASET 2=============");

    fprintf(f,"\r\nmean: %f", calculateMean(ptr, n)); //function to calculate mean
    fprintf(f,"\r\nmode: %d", calculateMode(n, ptr));

    fprintf(f,"\r\nStandard Deviation: %f", calculateStandardDeviation(n, ptr), "\n");
    fprintf(f,"\r\nMedian: %d", calculateMedian(n, ptr), "\n");
    histogram(n, ptr);
    printf("\n");
    
  
    fclose(f);



    return (EXIT_SUCCESS);
}



