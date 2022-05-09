#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NormRANu (2.3283063671E-10F)
#define pi acos(-1)
#define a 1.0
#define tiempo 100.0
#define h 0.01

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran,ig1,ig2,ig3;
float random(void);
void ini_ran(int);

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

FILE *fout;

void mapeo(double *posicion, double *velocidad){
    double toroide;
    printf("%lf\t%lf\n",*posicion,*velocidad);
    if (((*posicion)+(*velocidad))<(2*pi) & ((*posicion)+(*velocidad))>0){
        (*posicion)=(*posicion)+(*velocidad);
        (*velocidad)=(*velocidad)+a*sin(*posicion);
    }
    else{
        if (((*posicion)+(*velocidad))>(2*pi)){
            toroide=(*posicion)+(*velocidad)-2*pi;
            while (toroide>(2*pi)){
                toroide=toroide-2*pi;
            }
            (*posicion)=toroide;
            (*velocidad)=(*velocidad)+a*sin(*posicion);
        }
        else{
            toroide=(*posicion)+(*velocidad);
            while (toroide<(-2*pi)){
                toroide=toroide+2*pi;
            }
            (*posicion)=2*pi+toroide;
            (*velocidad)=(*velocidad)+a*sin(*posicion);
        }
    }
    printf("%lf\t%lf\n\n",*posicion,*velocidad);
    //getchar();
}

int main(){
    double posicion, velocidad;
    int i, n;
    ini_ran(time(0));
    posicion=random();
    velocidad=random();
    printf("%lf\t%lf\n",posicion,velocidad);
    n=(int)(tiempo/h);
    printf("%d\n",n);
    getchar();
    fout=fopen("StandardMap.txt","wt");
    if ((fout=fopen("StandardMap.txt","wt"))==NULL){
        printf("Hubo un problema al abrir el arcivo\n");
    }
    else{
        fprintf(fout,"%lf\t%lf\n",posicion,velocidad);
        for (i=0;i<n;i++){
            mapeo(&posicion,&velocidad);
            fprintf(fout,"%lf\t%lf\n",posicion,velocidad);
        }
    }
    fclose(fout);
}
