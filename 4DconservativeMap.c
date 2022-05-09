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
    double ro,betax,betay,cx,cy,sx,sy,qx,qy,h,x,y,auxx,auxy,auxxx,auxyy;
    int i,j,numTray,numSteps;
    qx=0.21;
    qy=0.24;
    //betax=1.0/qx;
    //betay=1.0/qy;
    betax=0.4;
    betay=0.4;
    h=0.1;
    numTray=100;
    numSteps=1000;
    x=Random()*1.6-0.8;//Y vemos x pertenece a [-0.5:2.0]
    y=Random()*(6*10^-4)-(3*10^-4);//Y vemos y pertenece a [-2.5:1.0]
    //x=-0.0049;
    //y=0.0001;
    for(i=0;i<numTray;i++){
        sprintf(nombreFichero,"4dConservativeMap%d.txt",i);
        FILE*f;
        f=fopen(nombreFichero,"wt");
        fprintf(f,"%f \t %f \t %f \n",0.0,x,y);
        auxx=-0.0049;
        auxxx=-0.5329;
        auxy=0.0;
        auxyy=0.0;
        for(j=0;j<numSteps;j++){

            auxx=x;
            auxy=y;

            cx=cos(2*pi*qx);
            cy=cos(2*pi*qy);
            sx=sin(2*pi*qx);
            sy=sin(2*pi*qy);
            ro=(betax*sx)/(betay*sy);

            x=(2*cx*auxx)-(auxxx)-(ro*auxx*auxx)+(auxy*auxy);
            // !!!!!POSIBLE FALLO, NO SÉ SI LA tau ESTÁ EN RADIANES Y DEBERÍA EN SENO Y COSENO
            while(x>0.8){
                x+=-2*0.8;
                }
            while(x<-0.8){
                x+=2*0.8;
                }

            y=(2*cy*auxy)-(auxyy)+(2*auxy*auxx);
            while(y>0.0003){
                y+=-2*(0.0003);
                }
            while(y<-0.0003){
                y+=2*(0.0003);
                }


            fprintf(f,"%d \t %f \t %f \t %f \n",i,h*j+h,auxx,x);
            //printf("Trayectoria %d \n Iteracion %d \n x=%f \t v=%f \n \n \n",i,j,x,v);
            //getchar();
        }
        x=Random()*1.6-0.8;
        y=Random()*(6*10^-4)-(3*10^-4);
        auxxx=auxx;
        auxyy=auxy;
        fclose(f);
        printf("\n trayectoria %d completada \n",i);
    }
    FILE*k;
    k=fopen("order4dConservativeMap.txt","wt");
    fprintf(k,"unset key \n set xlabel 'xn' \n set ylabel 'xn+1' \n plot for[i=0:%d] '4dConservativeMap'.i.'.txt' using 3:4 with dots",numTray-1);
    fclose(k);
}
