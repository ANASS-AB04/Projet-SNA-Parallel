#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Produit matrice-vecteur : y = A*x  (A de taille N*N, stockée ligne par ligne)
void prod_mat_vec(int N, double *A, double *x, double *y)
{
    for (int i=0; i<N; i++){
        y[i]=0.0;
        for (int j=0; j<N; j++){
            y[i]+=A[i*N+j]*x[j];
        }
    }
}

// Produit matrice transposée-vecteur : y = A^T*x
void prod_matT_vec(int N, double *A, double *x, double *y)
{
    for (int i=0; i<N; i++){
        y[i]=0.0;
        for (int j=0; j<N; j++){
            y[i]+=A[j*N+i]*x[j];
        }
    }
}

// Produit scalaire : (a, b)
double prod_scal(int N, double *a, double *b)
{
    double s=0.0;
    for (int k=0; k<N; k++){
        s+=a[k]*b[k];
    }
    return s;
}

// Gradient biconjugué : résout A*x = b
// x : initialisation en entrée, solution en sortie
// Retour : nombre d'itérations, ou -1 si pas de convergence
int bicg(int N, double *A, double *b, double *x, double tol, int itmax)
{
    double *r, *rt, *p, *pt, *q, *qt;
    double rho, rho_new, alpha, beta, norm_b;
    int it;

    norm_b=sqrt(prod_scal(N, b, b));
    if (norm_b==0.0){
        for (int k=0; k<N; k++) x[k]=0.0;
        return 0;
    }

    r =(double *)malloc(N*sizeof(double));
    rt=(double *)malloc(N*sizeof(double));
    p =(double *)malloc(N*sizeof(double));
    pt=(double *)malloc(N*sizeof(double));
    q =(double *)malloc(N*sizeof(double));
    qt=(double *)malloc(N*sizeof(double));

    // r = b - A*x ;  r~ = r ;  p = r ;  p~ = r~
    prod_mat_vec(N, A, x, q);
    for (int k=0; k<N; k++){
        r[k] =b[k]-q[k];
        rt[k]=r[k];
        p[k] =r[k];
        pt[k]=rt[k];
    }
    rho=prod_scal(N, rt, r);

    it=0;
    while (sqrt(prod_scal(N, r, r))>tol*norm_b && it<itmax){
        prod_mat_vec(N, A, p, q);      // q  = A*p
        prod_matT_vec(N, A, pt, qt);   // q~ = A^T*p~

        alpha=rho/prod_scal(N, pt, q);

        for (int k=0; k<N; k++){
            x[k] +=alpha*p[k];
            r[k] -=alpha*q[k];
            rt[k]-=alpha*qt[k];
        }

        rho_new=prod_scal(N, rt, r);
        beta=rho_new/rho;
        rho=rho_new;

        for (int k=0; k<N; k++){
            p[k] =r[k] +beta*p[k];
            pt[k]=rt[k]+beta*pt[k];
        }
        it++;
    }

    if (sqrt(prod_scal(N, r, r))>tol*norm_b){
        printf("BiCG : pas de convergence après %d itérations\n", it);
        it=-1;
    }

    free(r); free(rt); free(p); free(pt); free(q); free(qt);
    return it;
}


int main(int argc, char **argv)
{
    // paramètres :
    int n, n_squared;
    double Lx, Ly, dx, dy,D,x,y;
    double *g, *h, *u, *f, *u_exact;

    n=10;
    n_squared=n*n;
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

    // Schéma de résolution différences finis centrées;

    double *A;
    A=(double *)malloc(n_squared*n_squared*sizeof(double));
    double alpha;
    alpha=2.0/(dx*dx)+2.0/(dy*dy);

    for (int k=0; k<n_squared; k++){
        int ix=k/n, iy=k%n;            // u[ix*n+iy] : ix suit x, iy suit y
        for (int l=0; l<n_squared; l++) A[k*n_squared+l]=0.0;
        if (ix==0 || ix==n-1 || iy==0 || iy==n-1){   // point de bord
            A[k*n_squared+k]=1.0;
            f[k]=u_exact[k];                         // valeur imposée au bord
        } else {
            A[k*n_squared+k]=alpha;
            A[k*n_squared+k-1]=-1.0/(dy*dy);         // voisin iy-1
            A[k*n_squared+k+1]=-1.0/(dy*dy);         // voisin iy+1
            A[k*n_squared+k-n]=-1.0/(dx*dx);         // voisin ix-1
            A[k*n_squared+k+n]=-1.0/(dx*dx);         // voisin ix+1
        }
    }

    int itmax=1000;
    double tol=1e-8;

    bicg(n_squared, A, f, u, tol, itmax);

    // Vérification de la solution exacte
    double error=0.0;
    for(int i=0; i<n_squared; i++){
        if (fabs(u[i]-u_exact[i])>error) error=fabs(u[i]-u_exact[i]);
    }
    printf("Erreur max : %e\n", error);






    return 0;
}