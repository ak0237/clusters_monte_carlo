#include "../eqd.h"

void ic(double *phi){
        int i, j;
        for(i= 0; i< Nx; i++){
                for(j= 0; j< Ny; j++){
                        if(sqrt((i-Nx/2)*(i-Nx/2)+(j-Ny/2)*(j-Ny/2)) < R){
                                phi[i*Ny+j] = 1.0;
                        }else{
                                phi[i*Ny+j] = 0.0;
                        }
                }
        }
}
