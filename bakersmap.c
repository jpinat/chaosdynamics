#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

void bakersmap(double * x, double * v, double x0, double v0, double b){
    x[0]=0.5;//0.5
    v[0]=2.0/(acos(0)*acos(0)*4);//2/(acos(0)*acos(0)*4)
    b=1.0/3.0;
    printf("x[0]=%f \t v[0]=%f \t b=%f \n",x[0],v[0],b);
    FILE*f;
    f=fopen("datosBaker.txt","wt");
    printf("%f \t %f \n",x[0],v[0]);
    fprintf(f,"%f \t %f \n",x[0],v[0]);
    if(f==NULL){
        printf("No se pudo abrir el fichero\n");
    }else{
        int i;
        for(i=1;i<N;i++){
            if(v[i-1]<=b){
                printf("v[i]<b \n");
                x[i]=b*x[i-1];
                v[i]=v[i-1]/b;
                printf("i=%d \n",i);
                printf("x[%d]=%f \t v[%d]=%f \n",i,x[i],i,v[i]);
                fprintf(f,"%f \t %f \n",x[i],v[i]);
            }else{
                printf("v[i]>b \n");
                x[i]=1.0+(1.0-b)*(x[i-1]-1.0);
                v[i]=1.0+((v[i-1]-1.0)/(1.0-b));
                printf("i=%d  \n",i);
                printf("valorx[i]=%f\n\n\n",1.0+(1.0-b)*(x[i-1]-1.0));
                printf("x[%d]=%f \t v[%d]=%f \n",i,x[i],i,v[i]);
                fprintf(f,"%f \t %f \n",x[i],v[i]);
            }
            //getchar();
        }
    }
    fclose(f);
}

void standardmap(double * x, double * v, double x0, double v0, double a){
    x[0]=0.0;
    v[0]=2.0/(acos(0)*acos(0)*4);//2/(acos(0)*acos(0)*4)
    a=0.0;
    printf("x[0]=%f \t v[0]=%f \t b=%f \n",x[0],v[0],a);
    FILE*f;
    f=fopen("datosStandardMap.txt","wt");
    printf("%f \t %f \n",x[0],v[0]);
    fprintf(f,"%f \t %f \n",x[0],v[0]);
    if(f==NULL){
        printf("No se pudo abrir el fichero\n");
    }else{
        int i;
        for(i=1;i<N;i++){
            x[i]=x[i-1]+v[i-1];
            v[i]=v[i-1]+a*sin(x[i-1]);
            printf("i=%d \n",i);
            printf("x[%d]=%f \t v[%d]=%f \n",i,x[i],i,v[i]);
            fprintf(f,"%f \t %f \n",x[i],v[i]);
        }
    }
    fclose(f);
}

main(){
    double x[N],v[N],b,a;
    x[0]=0.5;
    v[0]=2/(4*acos(0)*acos(0));
    b=1/5;
    //bakersmap(x,v,x[0],v[0],b);
    standardmap(x,v,x[0],v[0],a);
}
