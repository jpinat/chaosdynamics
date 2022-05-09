#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NormRANu (2.3283063671E-10F)
#define pi acos(-1)
#define l0 1.000000
#define omega0 1.0
#define g 0.07
#define q g/(omega0*omega0*l0)
#define epsilon 0.195
#define tiempo 10000.0
#define h 0.01
#define nTrayectorias 100
#define intervalo 0.001

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
FILE *fEnergia;

void funcion(double *vector){
    double vectorViejo[4];
    int i;
    for (i=0;i<4;i++){
        vectorViejo[i]=vector[i];
    }
    vector[0]=vectorViejo[2];
    vector[1]=vectorViejo[3];
    vector[2]=vectorViejo[0]*vectorViejo[3]*vectorViejo[3]-(vectorViejo[0]-1)+q*cos(vectorViejo[1]);
    vector[3]=-2*vectorViejo[2]*vectorViejo[3]/vectorViejo[0]-q*sin(vectorViejo[1])/vectorViejo[0];
}

double energia(double *vector){
    double valorEnergia, lPunto, phiPunto, l, phi;
    l=vector[0];
    phi=vector[1];
    lPunto=vector[2];
    phiPunto=vector[3];
    valorEnergia=lPunto*lPunto/2.0+l*l*phiPunto*phiPunto/2.0-q*l*cos(phi)+(l-1.0)*(l-1.0)/2.0;
    return valorEnergia;
}

void mapeo(double *vector){
    double k1[4], k2[4], k3[4], k4[4];
    int i;
    for (i=0;i<4;i++){
        k1[i]=vector[i];
    }
    funcion(k1);
    for (i=0;i<4;i++){
        k1[i]=k1[i]*h;
    }
    for (i=0;i<4;i++){
        k2[i]=vector[i]+k1[i]/2;
    }
    funcion(k2);
    for (i=0;i<4;i++){
        k2[i]=k2[i]*h;
    }
    for (i=0;i<4;i++){
        k3[i]=vector[i]+k2[i]/2;
    }
    funcion(k3);
    for (i=0;i<4;i++){
        k3[i]=k3[i]*h;
    }
    for (i=0;i<4;i++){
        k4[i]=vector[i]+k3[i];
    }
    funcion(k4);
    for (i=0;i<4;i++){
        k4[i]=k4[i]*h;
    }
    for (i=0;i<4;i++){
        vector[i]=vector[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
    }
    //printf("Caso random\t%lf\n",vector[1]);
    if ((vector[1])>pi){
        while ((vector[1])>pi){
            vector[1]=vector[1]-2*pi;
            //printf("Caso 1\t%lf\n",vector[1]);
            //getchar();
        }
    }
    else if ((vector[1])<(-pi)){
        while ((vector[1])<(-pi)){
            vector[1]+=2*pi;
        }
    }
    //getchar();
}

void generaTrayectoriasPhiPhiPunto(double *vector){
    double comprobacion, valorEnergia;
    int i, j, n;
    n=(int)(tiempo/h);
    char nombreFichero[20];
    for (j=0;j<nTrayectorias;j++){
        sprintf(nombreFichero,"Trayectoria%d.txt",j);
        fout=fopen(nombreFichero,"wt");
        sprintf(nombreFichero,"Energia%d.txt",j);
        fEnergia=fopen(nombreFichero,"wt");
        vector[0]=random();
        vector[1]=random();
        vector[2]=random();
        comprobacion=2.0/(vector[0]*vector[0])*(epsilon-vector[2]*vector[2]/2.0-(vector[0]-1.0)*(vector[0]-1.0)/2.0+q*vector[0]*cos(vector[1]));
        while (comprobacion<0){
            vector[0]=random();
            vector[1]=random();
            vector[2]=random();
            comprobacion=2.0/(vector[0]*vector[0])*(epsilon-vector[2]*vector[2]/2.0-(vector[0]-1.0)*(vector[0]-1.0)/2.0+q*vector[0]*cos(vector[1]));
        }
        vector[3]=sqrt(comprobacion);
        valorEnergia=energia(vector);
        printf("Trayectoria %d\tEnergia %lf\n",j,valorEnergia);
        for (i=0;i<n;i++){
            mapeo(vector);
            valorEnergia=energia(vector);
            if ((vector[0])<(l0+intervalo) && (vector[0])>(l0-intervalo) && (vector[2])>0.0){
            //if ((vector[0])==l0){
                fprintf(fout,"%lf\t%lf\n",vector[1],vector[3]);
            }
            fprintf(fEnergia,"%d\t%lf\n",i,valorEnergia);
        }
        fclose(fout);
        fclose(fEnergia);
    }
}

void generaTrayectoriasEleElePunto(double *vector){
    double comprobacion, valorEnergia;
    int i, j, n;
    n=(int)(tiempo/h);
    char nombreFichero[20];
    for (j=0;j<nTrayectorias;j++){
        sprintf(nombreFichero,"Trayectoria%d.txt",j);
        fout=fopen(nombreFichero,"wt");
        sprintf(nombreFichero,"Energia%d.txt",j);
        fEnergia=fopen(nombreFichero,"wt");
        vector[0]=random();
        vector[1]=random();
        vector[2]=random();
        comprobacion=2.0/(vector[0]*vector[0])*(epsilon-vector[2]*vector[2]/2.0-(vector[0]-1.0)*(vector[0]-1.0)/2.0+q*vector[0]*cos(vector[1]));
        while (comprobacion<0){
            vector[0]=random();
            vector[1]=random();
            vector[2]=random();
            comprobacion=2.0/(vector[0]*vector[0])*(epsilon-vector[2]*vector[2]/2.0-(vector[0]-1.0)*(vector[0]-1.0)/2.0+q*vector[0]*cos(vector[1]));
        }
        vector[3]=sqrt(comprobacion);
        valorEnergia=energia(vector);
        printf("Trayectoria %d\tEnergia %lf\n",j,valorEnergia);
        for (i=0;i<n;i++){
            mapeo(vector);
            valorEnergia=energia(vector);
            if ((vector[1])<(0.0+intervalo) && (vector[1])>(0.0-intervalo) && (vector[3])>0.0){
            //if ((vector[0])==l0){
                fprintf(fout,"%lf\t%lf\n",vector[0],vector[2]);
            }
            fprintf(fEnergia,"%d\t%lf\n",i,valorEnergia);
        }
        fclose(fout);
        fclose(fEnergia);
    }
}

int main(){
    double vector[4];
    ini_ran(time(0));
    vector[0]=0.0;
    vector[1]=0.0;
    vector[2]=0.0;
    vector[3]=0.0;
    //generaTrayectoriasPhiPhiPunto(vector);
    generaTrayectoriasEleElePunto(vector);
}
    /*FILE *k;
    k=fopen("OrdenaSpringPendulum.txt","wt");
    fprintf(k,"unset key \n plot for[i=0:%d] 'Trayectoria'.i.'.txt' using 1:2 with dots",nTrayectorias-1);
    fclose(k);*/


/*int main(){
    double vector[4];
    int i;
    double valorEnergia;
    ini_ran(time(0));
    vector[0]=random();
    vector[1]=random();
    vector[2]=random();
    vector[3]=random();
    printf("%lf\t%lf\t%lf\t%lf\n",vector[0],vector[1],vector[2],vector[3]);
    valorEnergia=energia(vector);
    printf("Energia\t%lf\n",valorEnergia);
    fout=fopen("Energia.txt","wt");
    for (i=0;i<1000;i++){
        mapeo(vector);
        valorEnergia=energia(vector);
        printf("Energia\t%lf\n",valorEnergia);
        fprintf(fout,"%d\t%lf\n",i,valorEnergia);
        //getchar();
    }
    printf("%lf\t%lf\t%lf\t%lf\n",vector[0],vector[1],vector[2],vector[3]);
    fclose(fout);
}*/
