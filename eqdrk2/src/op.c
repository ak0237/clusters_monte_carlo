#include "../eqd.h"

void op(int t, double *phi){
        int i, j;
        FILE *file;
        char name[100];
        sprintf(name, "dat/phi-%d.dat", t);
        file = fopen(name, "w");
        for(i= 0; i< Nx; i++){
                for(j= 0; j< Ny; j++){
                        fprintf(file, "%g ", phi[i*Ny+j]);
                }
                fprintf(file, "\n");
        }
        fclose(file);
}
