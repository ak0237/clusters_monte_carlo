#include "../eqd.h"

#define r (tf/(NF-1))



int main(int argc, char **argv){
	printf("oi");
	int i, j, l= 0;
	double t= 0.0;
	double a0= r; 
	double *phi, *k_1, *k_2, *k_3, *k_4;
	phi = (double *) 	calloc(Nx*Ny, sizeof(double));
    k_1 = (double *) 	calloc(Nx*Ny, sizeof(double)); 
    k_2 = (double *) 	calloc(Nx*Ny, sizeof(double)); 
    k_3 = (double *) 	calloc(Nx*Ny, sizeof(double)); 
    k_4 = (double *) 	calloc(Nx*Ny, sizeof(double));
	

	ic(phi);
	op(l++, phi);

	while(t < tf){
		
        for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){

                k_1[(i)*Ny+j] = D * (phi[((i+1)%Nx)*Ny+j] + phi[((i-1+Nx)%Nx)*Ny+j] + phi[i*Ny+(j+1)%Ny] + phi[i*Ny+(j-1+Ny)%Ny] - 4.0*phi[i*Ny+j]);

			}
		}
        for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){

                k_2[(i)*Ny+j] = D * (phi[((i+1)%Nx)*Ny+j] + 0.5*dt*k_1[((i+1)%Nx)*Ny+j]  + phi[((i-1+Nx)%Nx)*Ny+j] + 0.5*dt*k_1[((i-1+Nx)%Nx)*Ny+j]  + phi[i*Ny+(j+1)%Ny]  + 0.5*dt*k_1[i*Ny+(j+1)%Ny]  + phi[i*Ny+(j-1+Ny)%Ny] + 0.5*dt*k_1[i*Ny+(j-1+Ny)%Ny] - 4.0*(phi[i*Ny+j] + 0.5*dt*k_1[i*Ny+j]));


			}
		} 
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){

                k_3[(i)*Ny+j] = D * (phi[((i+1)%Nx)*Ny+j] + 0.5*dt*k_2[((i+1)%Nx)*Ny+j]  + phi[((i-1+Nx)%Nx)*Ny+j] + 0.5*dt*k_2[((i-1+Nx)%Nx)*Ny+j]  + phi[i*Ny+(j+1)%Ny]  + 0.5*dt*k_2[i*Ny+(j+1)%Ny]  + phi[i*Ny+(j-1+Ny)%Ny] + 0.5*dt*k_2[i*Ny+(j-1+Ny)%Ny] - (4.0*phi[i*Ny+j] + 0.5*dt*k_2[i*Ny+j]));


			}
		}
        for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){

                k_4[(i)*Ny+j] =D * (phi[((i+1)%Nx)*Ny+j] + dt*k_3[((i+1)%Nx)*Ny+j]  + phi[((i-1+Nx)%Nx)*Ny+j] + dt*k_3[((i-1+Nx)%Nx)*Ny+j]  + phi[i*Ny+(j+1)%Ny]  + dt*k_3[i*Ny+(j+1)%Ny]  + phi[i*Ny+(j-1+Ny)%Ny] + dt*k_3[i*Ny+(j-1+Ny)%Ny] - 4.0*(phi[i*Ny+j] + dt*k_3[i*Ny+j]));

                phi[(i)*Ny+j] = phi[i*Ny+j] + (dt/6.0) * (k_1[i*Ny+j] + 2.0*k_2[i*Ny+j] + 2.0*k_3[i*Ny+j] + k_4[i*Ny+j]);

			}
		}
        
		t+= dt;
		if(a0 <= t){
			op(l++, phi);
			a0+= r;
		}
	}
	free(phi);
    free(k_1);
    free(k_2);
    free(k_3);
    free(k_4);
	return 0;
}
