#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define bool  char
#define False 0
#define True  1
#define x     0
#define y     1

struct linha{
    int sardaA;
    int sardaB;
    float dist;
};

float dist(float* sardaA, float* sardaB);
int ordena(float** arestas, struct linha* ordem, int numSardas);

int main(int argc, char** argv) {
    
    int i, j, numSardas, numLinhas;
    float totalDist;
    
    scanf("%d", &numSardas);
    
    if(numSardas < 1){
        printf("%f\n", 0);
        return (EXIT_SUCCESS);
    }
    
    float  sardas[numSardas][2];
    float  **arestas;
    struct linha ordem[numSardas * numSardas];
    bool   conectadas[numSardas];
    
    arestas = (float**) malloc(numSardas * sizeof(float*));
    for(i = 0; i < numSardas; i++){
        arestas[i] = (float*) malloc(numSardas * sizeof(float));
    }
    
    for(i = 0; i < numSardas; i++){
        scanf("%f %f", &sardas[i][x], &sardas[i][y]);
    }
    
    for(i = 0; i < numSardas; i++){
        for(j = i+1; j < numSardas; j++){
            arestas[i][j] = dist(sardas[i], sardas[j]);
        }
    }
    
    for(i = 0; i < numSardas; i++){
        conectadas[i] = False;
    }
    
    numLinhas = ordena(arestas, ordem, numSardas);
    
    conectadas[ordem[0].sardaA] = True;
    conectadas[ordem[0].sardaB] = True;
    totalDist = ordem[0].dist;
    
    for(i = 1; i < numLinhas; i++){
        if((conectadas[ordem[i].sardaA] && !conectadas[ordem[i].sardaB]) ||
           (conectadas[ordem[i].sardaB] && !conectadas[ordem[i].sardaA])){
            conectadas[ordem[i].sardaA] = True;
            conectadas[ordem[i].sardaB] = True;
            totalDist += ordem[i].dist;
        }
    }
    printf("%f\n", totalDist);
    return (EXIT_SUCCESS);
}

float dist(float* sardaA, float* sardaB){
    
    return sqrt(pow((sardaA[x] - sardaB[x]), 2) +
                pow((sardaA[y] - sardaB[y]), 2));
    
}

int ordena(float** arestas, struct linha* ordem, int numSardas){
    
    int a, i, j, k;
    
    a = 0;
    
    ordem[a].dist = arestas[0][1];
    ordem[a].sardaA = 0;
    ordem[a].sardaB = 1;
    
    for(i = 0; i < numSardas; i++){
        for(j = i+1; j < numSardas; j++){
            if(i != 0 || j != 1){ // aresta[0][1] ja ta no vetor
                for(k = a; k >= 0; k--){
                    if(arestas[i][j] >= ordem[k].dist){
                        break;
                    }
                    else{
                        ordem[k+1].dist = ordem[k].dist;
                        ordem[k+1].sardaA = ordem[k].sardaA;
                        ordem[k+1].sardaB = ordem[k].sardaB;
                    }
                }
                ordem[k+1].dist = arestas[i][j];
                ordem[k+1].sardaA = i;
                ordem[k+1].sardaB = j;
                a++;
            }
        }
    }
    return a;
}
