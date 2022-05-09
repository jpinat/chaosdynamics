#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define NormRANu (2.3283063671E-10F)
#define pi 2*asin(1)
#define h 0.1
#define a 3

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

main(){

 double x, v, tiempo;
    char nombreFichero[20];
    int i, j, nTrayectorias, nPasos;
    tiempo=1000;
    nPasos=(int)(tiempo/h);
    nTrayectorias=30;
    ini_ran((int)time(0));
    v=Random()*2*pi-pi;
    x=Random()*2*pi-pi;
    for (i=0;i<nTrayectorias;i++){
        sprintf(nombreFichero,"StandardMap%d.txt",i);
        fout=fopen(nombreFichero,"wt");
        fprintf(fout,"%lf\t%lf\t%lf\n",0.0,x,v);
        for(j=0;j<nPasos;j++){
            x=x+v;
            while(x>pi){
                x=x-2*pi;
                }
            while(x<-pi){
                x=x+2*pi;
                }
            v=v+a*sin(x);
            while(v>pi){
                v=v-2*pi;
                }
            while(v<-pi){
                v=v+2*pi;
            }
            fprintf(fout,"%lf\t%lf\t%lf\n",h*j+h,x,v);
}
        x=Random()*2*pi-pi;
        v=Random()*2*pi-pi;
    }
 fclose(fout);
 return 0;
    }
