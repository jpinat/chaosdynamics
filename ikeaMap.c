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
    u=1.0;
    R=1.0;
    h=0.1;
    numTray=300;//100
    numSteps=500;//1000
    //x=Random()*2.5-0.5;//Y vemos x pertenece a [-0.5:2.0]
    //y=Random()*3.5-2.5;//Y vemos y pertenece a [-2.5:1.0]
    if(u<0.9){
        x1=0.5;
        x2=2.0;
        y1=-2.5;
        y2=1.0;
    }else{
        x1=-12.0;
        x2=12.0;
        y1=-8.5;
        y2=8.5;
    }
    x=Random()*(x2-x1)+x1;
    y=Random()*(y2-y1)+y1;
    for(i=0;i<numTray;i++){
        sprintf(nombreFichero,"ikeaMap%d.txt",i);
        FILE*f;
        f=fopen(nombreFichero,"wt");
        fprintf(f,"%f \t %f \t %f \n",0.0,x,y);
        for(j=0;j<numSteps;j++){

            auxx=x;
            auxy=y;
            tau=C1-(C2/(1+(auxx*auxx)+(auxy*auxy)));

            x = R + u*( auxx*cos(tau)- auxy*sin(tau));
            // !!!!!POSIBLE FALLO, NO SÉ SI LA tau ESTÁ EN RADIANES Y DEBERÍA EN SENO Y COSENO
            while(x>x2){
                x+=-2*x2;
                //printf("x=%f \n",x);
                //getchar();
                }
            while(x<x1){
                x+=2*(-x1);
                //printf("x=%f \n ",x);
                //getchar();
                }

            y = u*( auxx*sin(tau)+ auxy*cos(tau));
            while(y>y2){
                y+=-2*y2;
                //printf("y=%f \n",y);
                //getchar();
                }
            while(y<y1){
                y+=2*(-y1);
                //printf("y=%f \n",y);
                //getchar();
                }


            fprintf(f,"%d \t %f \t %f \t %f \n",i,h*j+h,x,y);
            //printf("Trayectoria %d \n Iteracion %d \n x=%f \t v=%f \n \n \n",i,j,x,v);
            //getchar();
        }
        x=Random()*(x2-x1)+x1;
        y=Random()*(y2-y1)+y1;
        fclose(f);
        printf("\n trayectoria %d completada \n",i);
    }
    FILE*k;
    k=fopen("orderIkeaMap.txt","wt");
    fprintf(k,"unset key \n plot for[i=0:%d] 'ikeaMap'.i.'.txt' using 3:4 with dots",numTray-1);
    fclose(k);
}
