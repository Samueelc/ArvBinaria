/*
    Entradas: largura - comprimento - espessura(?) 

    Saídas: área projetada, circularidade, esfericidade, perímetro, volume
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>



struct arv{
float ap, circ, esf, p, vol, id;
struct arv * fesq;
struct arv * fdir;
};typedef struct arv * parv;

float area (float x, float y, float z){
   float area = 3.14159265358979323846*x*y;
   return area;
}

float circularidade(float x, float y, float z){
    float circ = (y/x)*100;
    return circ;
}

float esfericidade (float x, float y, float z){
   float esf = (pow((x*y*z), 1.0/3)*100);
   return esf;
}

float perimetro (float x, float y, float z){
    float p=2*3.14159265358979323846*((x+2)/2);
    return p; 
}


float volume (float x, float y, float z){
    float vol = (4/3*3.14159265358979323846)*x*y*z;
    return vol;
}

parv getnode(){
parv p;
p=(parv)malloc(sizeof(struct arv));
return p;
}

parv criararv (float vol,float x, float  y, float z, float id){
parv p;
p=getnode();
p->vol = vol;
p->ap=area(x, y, z);
p->circ = circularidade(x, y , z);
p->esf = esfericidade(x, y, z);
p->p = perimetro(x, y, z);
p->id = id;
p->fesq=NULL;
p->fdir=NULL;
}

parv criararv_raiz (float x, float  y, float z, float id){
parv p;
p=getnode();
p->ap=area(x, y, z);
p->circ = circularidade(x, y , z);
p->esf = esfericidade(x, y, z);
p->p = perimetro(x, y, z);
p->vol = volume(x, y, z);
p->id = id;
p->fesq=NULL;
p->fdir=NULL;
}



void criarfilhosesq(parv p , float vol, float x, float y , float z, float id){

    parv f;
    f=criararv(vol, x, y, z, id);
    p->fesq=f;
}

void criarfilhodir(parv p , float vol, float x, float y , float z, float id){
    parv f;
    f=criararv(vol, x, y, z, id);
    p->fdir=f;
}

int carregarv_ap(parv p, float x, float y, float z, float id){
 float vol;
  vol = volume(x,y,z);
  
  if(x<p->vol){
      if(p->fesq==NULL){      	 
          criarfilhosesq(p, vol, x, y, z, id);
      }else{
          carregarv_ap(p->fesq, x, y, z, id);
      }
  }else{
      if(p->fdir==NULL){
          criarfilhodir(p, vol, x, y, z, id);
      }else{
          carregarv_ap(p->fdir, x, y, z, id);
      }
  }
  
}

void imprimir(parv p){
    if(p != NULL){
        imprimir(p->fesq);
        printf("\nSOJA(%.1f) ->  |Volume = %.4f   |Circularidade = %.4f   |Esfericidade = %.4f   |Perimetro = %.4f   |Area projetada = %.4f   \n", p->id, p->vol, p->circ, p->esf, p->p, p->ap);
        imprimir(p->fdir);
    }

}
	

int main(){
    parv p;

    char url[]="soja.txt";
    float n1, n2, n3, id;
    FILE *arq;
    arq = fopen(url, "r");
    p=criararv_raiz(10, 20, 20, 0);//         RAIZ PRINCIPAL!!!!
        if(arq == NULL)
          printf("Erro, nao foi possivel abrir o arquivo\n");
        else
        while( (fscanf(arq,"%f %f %f %f \n",&id,  &n1, &n2, &n3))!=EOF )
            carregarv_ap(p,n1, n2, n3, id);
 
    fclose(arq);

    imprimir(p);
 
}

