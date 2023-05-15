#include "../eqd.h"

#define r (tf/(NF-1))

void ic(double *);
void op(int, double *);

int main(int argc, char **argv){
	int i, j, l= 0;
	double t= 0.0;
	double a0= r; 
	double *phi, *p_t;
	phi = (double *) 	calloc(Nx*Ny, sizeof(double));
	p_t = (double *) 	calloc(Nx*Ny, sizeof(double));
	ic(phi);
	op(l++, phi);
	while(t < tf){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				p_t[i*Ny+j] = phi[i*Ny+j] + 0.5*dt*D*(phi[((i+1)%Nx)*Ny+j] + phi[((i-1+Nx)%Nx)*Ny+j] + phi[i*Ny+(j+1)%Ny] + phi[i*Ny+(j-1+Ny)%Ny] - 4.0*phi[i*Ny+j]);
			}
		}
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				phi[i*Ny+j]+= dt*D*(p_t[((i+1)%Nx)*Ny+j] + p_t[((i-1+Nx)%Nx)*Ny+j] + p_t[i*Ny+(j+1)%Ny] + p_t[i*Ny+(j-1+Ny)%Ny] - 4.0*p_t[i*Ny+j]);
			}
		}
		t+= dt;
		if(a0 <= t){
			op(l++, phi);
			a0+= r;
		}
	}
	free(p_t);
	free(phi);
	return 0;
}
