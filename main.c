#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulator.h"

int NUM_MEMS = 512;

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "Usage: %s <processors> <u|n>\n", argv[0]);
        exit(1);
    }
    int procs = atoi(argv[1]);
    if(procs < 1){
        fprintf(stderr, "The number of processors must be a positive "
                "integer.\n");
        exit(1);
    }
    char dist = argv[2][0];
    if(dist != 'u' && dist != 'n'){
        fprintf(stderr, "The distribution must be 'u' or 'n' (uniform or "
                "normal).\n");
        exit(1);
    }
    /*
     ** Init seed for random numbers
     */
    srand(time(0));

    /*
    ** Run simulation
    */
    double avg_access_time[NUM_MEMS];
    simulate(avg_access_time, NUM_MEMS, procs, dist);

    /*
    ** Print results
    */
    // for(int i=0; i<NUM_MEMS; i++){
    //     printf("%.4f\n",avg_access_time[i]);
    // }
    char filename[20];
    snprintf(filename, sizeof(filename), "output/%d_%c.txt", procs, dist);
    FILE *output_file = fopen(filename, "w");
    if(output_file == NULL){
        fprintf(stderr, "Error: Could not open file for writing.\n");
        exit(1);
    }
    for(int i = 0; i < NUM_MEMS; i++){
        fprintf(output_file, "%.4f\n", avg_access_time[i]);
    }
    fclose(output_file);
    return 0;
}
