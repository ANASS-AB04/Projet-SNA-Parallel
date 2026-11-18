#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char **argv)
{
    // paramètres :
    int n;
    double Lx, Ly, dx, dy,D,x,y;
    double *g, *h, *u, *f, *u_exact;

    n=50;
    Lx=1.0;
    Ly=1.0;
    dx=Lx/(n-1);
    dy=Ly/(n-1);
    D=1.0;


    h=(double *)malloc(n*n*sizeof(double));
    g=(double *)malloc(n*n*sizeof(double));
    u=(double *)malloc(n*n*sizeof(double));
    f=(double *)malloc(n*n*sizeof(double));
    u_exact=(double *)malloc(n*n*sizeof(double));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            x=i*dx;
            y=j*dy;
            h[i*n+j]=0.0;
            g[i*n+j]=0.0;
            u[i*n+j]=0.0;
            f[i*n+j]=2*(x-x*x+y-y*y);
            u_exact[i*n+j]=-(pow(x, 3)/3.0-pow(x,4)/6.0+pow(y,3)/3.0-pow(y,4)/6.0);
        }
    }

    





    return 0;
}