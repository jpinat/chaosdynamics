#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define NormRANu (2.3283063671E-10F)
#define pi 2*asin(1)
//#define h 0.1
//#define a 3

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
    ini_ran((int)time(0));
    char nombreFichero[20];
    double C1,C2,u,R,tau,h,x,y,auxx,auxy,x1,x2,y1,y2;
    int i,j,numTray,numSteps;
    C1=0.4;
    C2=6.0;
    u=1.10; //u=1.00 unica fase preserving map, u>=0.6 atractor caótico, parámetro adimensional
    R=1.0;
    h=0.1;
    numTray=300;//100
    numSteps=1000;//1000
    //x=Random()*2.5-0.5;//Y vemos x pertenece a [-0.5:2.0]
    //y=Random()*3.5-2.5;//Y vemos y pertenece a [-2.5:1.0]
    if(u<1.0){
        x1=-0.5;
        x2=2.0;
        y1=-2.5;
        y2=1.0;
    }else{
        x1=-8.0;
        x2=8.5;
        y1=-4.0;
        y2=12.0;
    }
    x=Random()*(x2-x1)+x1;
    y=Random()*(y2-y1)+y1;
    for(i=0;i<numTray;i++){
        sprintf(nombreFichero,"ikeaMap%d.txt",i);
        FILE*f;
        f=fopen(nombreFichero,"wt");
        fprintf(f,"%lf\t%lf\n",x,y);
        for(j=0;j<numSteps;j++){

            auxx=x;
            auxy=y;
            tau=C1-(C2/(1+(auxx*auxx)+(auxy*auxy)));

            x = R + u*( auxx*cos(tau)- auxy*sin(tau));

            while(x>x2){
                x=x-(x2-x1);
                //printf("x=%f \n",x);
                //getchar();
                }
            while(x<x1){
                x=x+(x2-x1);
                //printf("x=%f \n ",x);
                //getchar();
                }

            y = u*( auxx*sin(tau)+ auxy*cos(tau));
            while(y>y2){
                y=y-(y2-y1);
                //printf("y=%f \n",y);
                //getchar();
                }
            while(y<y1){
                y=y+(y2-y1);
                //printf("y=%f \n",y);
                //getchar();
                }


            fprintf(f,"%lf\t%lf\n",x,y);
            //printf("Trayectoria %d \n Iteracion %d \n x=%f \t v=%f \n \n \n",i,j,x,v);
            //getchar();
        }
        x=Random()*(x2-x1)+x1;
        y=Random()*(y2-y1)+y1;
        fclose(f);
        //printf("\n trayectoria %d completada \n",i);
    }
    return 0;
}
