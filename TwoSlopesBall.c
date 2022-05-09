#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NormRANu (2.3283063671E-10F)
#define pi acos(-1)
#define alpha 73.0*2.0*pi/360.0
#define tiempo 100.0
#define h 0.01
#define numeroTrayectorias 100

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran,ig1,ig2,ig3;
float random(void);
void ini_ran(int);

FILE *fout;

float random(void){ //Esta es la función que genera un número aleatorio de alta calidad.
    float r; //Este es el número aleatorio que nos va a devolver.
    ig1=ind_ran-24;
    ig2=ind_ran-55;
    ig3=ind_ran-61;
    irr[ind_ran]=irr[ig1]+irr[ig2];
    ir1=(irr[ind_ran]^irr[ig3]);
    ind_ran++;
    r=ir1*NormRANu;
    //printf("r=%l\n",r);
    return r;
}

void ini_ran(int semilla){
    int inicial, factor, suma, i;
    srand(semilla); //Establece el número (semilla) que le pasamos a la función como semilla en la generación de números aleatorios.
    inicial=semilla;
    factor=67397; //Se establece un valor para el factor por el cual vamos a ir multiplicando los números (con el fin de generar aleatorios).
    suma=7364893; //Este valor lo vamos a sumar siempre para generar el número aleatorio.
    for(i=0;i<256;i++){
        inicial=(inicial*factor+suma);
        irr[i]=inicial;
    }
    ind_ran=ig1=ig2=ig3=0;
}

void mapeo(double *u, double *z){
    double b, zVieja;
    //printf("%lf\t%lf\n",*u,*z);
    zVieja=(*z);
    b=2*sqrt(*z)*tan(alpha)-sqrt(1-(*z));
    if ((*u)>=b){
        (*u)+=-2*sqrt(*z)*tan(alpha);
        //printf("Caso 1\n");
    }
    else{
        (*z)=-(*z)*(1+sin(4*alpha)*tan(alpha)/2)-(*u)*(*u)*sin(4*alpha)/(2*tan(alpha))+(*u)*sqrt(*z)*sin(4*alpha)+2*cos(alpha)*cos(alpha);
        (*u)=-(*u)+sqrt(zVieja)*tan(alpha)-sqrt(*z)*tan(alpha);
        //printf("Caso 2\n");
    }
    //printf("%lf\t%lf\n\n",*u,*z);
    //getchar();
}

int main(){
    int i, n, j;
    double u, z;
    char nombreFichero[20];
    ini_ran(time(0));
    n=(int)(tiempo/h);
    for (j=0;j<numeroTrayectorias;j++){
        sprintf(nombreFichero,"Trayectoria%d.txt",j);
        u=random();
        z=random();
        fout=fopen(nombreFichero,"wt");
        fprintf(fout,"%lf\t%lf\n",u,z);
        for (i=0;i<n;i++){
            mapeo(&u,&z);
            fprintf(fout,"%lf\t%lf\n",u,z);
        }
        fclose(fout);
    }
}
