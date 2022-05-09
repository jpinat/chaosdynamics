#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define NormRANu (2.3283063671E-10F)
#define pi 2*asin(1)
#define h 0.5
#define alfa 89 //en grados
#define a 0.972

FILE *fout;

extern float Random(void);

extern void ini_ran(int SEMILLA);

unsigned int irr[256];
unsigned char ind_ran,ig1,ig2,ig3;
unsigned int ir1;

float Random(void){
    float r;
    ig1=ind_ran-24;
    ig2=ind_ran-55;
    ig3=ind_ran-61;
    irr[ind_ran]=irr[ig1]+irr[ig2];
    ir1=(irr[ind_ran]^irr[ig3]);
    ind_ran++;
    r=ir1*NormRANu;
    return r;
}

void ini_ran(int SEMILLA){
    int INI,FACTOR,SUM,i;
    srand(SEMILLA);
    INI=SEMILLA;
    FACTOR=67397;
    SUM=7364893;
    for(i=0; i<256; i++){
        INI=(INI*FACTOR+SUM);
        irr[i]=INI;
    }
    ind_ran=ig1=ig2=ig3=0;
}

double radianes(double angulo){
double x;
x=angulo*2*pi/360.0;
return x;
}

int main(){

 double z, u, tiempo, aux;
    char nombreFichero[20];
    int i, j, nTrayectorias, nPasos;
    tiempo=1000;
    nPasos=(int)(tiempo/h);
    nTrayectorias=500;
    ini_ran((int)time(0));
    u=Random()*2-1;
    z=Random();
    for (i=0;i<nTrayectorias;i++){
        sprintf(nombreFichero,"DoubleSlope%d.txt",i);
        fout=fopen(nombreFichero,"wt");
        fprintf(fout,"%lf\t%lf\t%lf\n",0.0,u,z);
        for(j=0;j<nPasos;j++){
            aux=-z*(1+0.5*sin(radianes(4*alfa))*tan(radianes(alfa)))-u*u*0.5*sin(radianes(4*alfa))*(1.0/tan(radianes(alfa)))+u*sqrt(sqrt(z*z))*sin(radianes(4*alfa))+2*cos(radianes(alfa))*cos(radianes(alfa));
            while(aux>1){
                aux=aux-1;
                }
            while(aux<0){
                aux=aux+1;
                }
            u=-u+sqrt(sqrt(z*z))*tan(radianes(alfa))-sqrt(sqrt(aux*aux))*tan(radianes(alfa));
            z=aux;
            while(u>1){
                u=u-2;
                }
            while(u<-1){
                u=u+2;

            }
            fprintf(fout,"%lf\t%lf\t%lf\n",h*j+h,u,z);
}
        u=Random()*2-1;
        z=Random();
    }
 fclose(fout);
 return 0;
    }

