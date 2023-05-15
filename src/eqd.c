#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 100
#define Ny 100
#define R 25
#define tf 100.0
#define dt 0.1
#define NF 500
#define D 1.2

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



#define r (tf/(NF-1))



int main(int argc, char **argv){
	printf("oi");
	int i, j, l= 0;
	double t= 0.0, k_1, k_2, k_3, k_4;
	double a0= r; 
	double *phi, *p_t;
	phi = (double *) 	calloc(Nx*Ny, sizeof(double));
	

	ic(phi);
	op(l++, phi);

	while(t < tf){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				// p_t[i*Ny+j] = phi[i*Ny+j] + 0.5*dt*D*(phi[((i+1)%Nx)*Ny+j] + phi[((i-1+Nx)%Nx)*Ny+j] + phi[i*Ny+(j+1)%Ny] + phi[i*Ny+(j-1+Ny)%Ny] - 4.0*phi[i*Ny+j]);

                k_1 = D * (phi[((i+1)%Nx)*Ny+j] + phi[((i-1+Nx)%Nx)*Ny+j] + phi[i*Ny+(j+1)%Ny] + phi[i*Ny+(j-1+Ny)%Ny] - 4.0*phi[i*Ny+j]);

                k_2 = D * (phi[((i+1)%Nx)*Ny+j] + phi[((i-1+Nx)%Nx)*Ny+j] + 0.5*dt + phi[i*Ny+(j+1)%Ny] + phi[i*Ny+(j-1+Ny)%Ny] + 0.5*dt*k_1 - 4.0*phi[i*Ny+j]);

                k_3 = D * (phi[((i+1)%Nx)*Ny+j] + phi[((i-1+Nx)%Nx)*Ny+j] + 0.5*dt + phi[i*Ny+(j+1)%Ny] + phi[i*Ny+(j-1+Ny)%Ny] + 0.5*dt*k_2 - 4.0*phi[i*Ny+j]);

                k_4 = D * (phi[((i+1)%Nx)*Ny+j] + phi[((i-1+Nx)%Nx)*Ny+j] + 0.5*dt + phi[i*Ny+(j+1)%Ny] + phi[i*Ny+(j-1+Ny)%Ny] + dt*k_3 - 4.0*phi[i*Ny+j]);

                phi[(i)*Ny+j] = phi[i*Ny+j] + (dt/6) * (k_1 + 2*k_2 + 2*k_3 + k_4);

			}
		}
		t+= dt;
		if(a0 <= t){
			op(l++, phi);
			a0+= r;
		}
	}
	free(phi);
	return 0;
}