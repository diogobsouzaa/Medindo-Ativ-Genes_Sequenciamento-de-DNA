#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "func.h"

#include <time.h>

void main(){
    FILE  *posfrag;
    
    //nome dos arquivos que serão usados
    char texto[] = "genoma_grande.txt";
    char trecho[] = "fragmentos_grande.txt";
    char posfragmentos[] = "pos_fragmentos.csv";
    
    //chamada de função
    CtrlF(texto, trecho, posfragmentos);

    posfrag = fopen("pos_fragmentos.csv", "rt");

    //descobrindo o tamanho de pos_fragmentos
    int nf = -2;
    while(!feof(posfrag)){
        int v[2];
        fscanf(posfrag, "%d,%d", &v[0], &v[1]);
        nf++;
    }

    fclose (posfrag);

    //nome dos arquivos e numeros para a função ContagemIntersecoes
    char posgenes[] = "pos_genes_grande.csv";
    int n_genes = 10000;
    int n_fragmentos = nf;
    char arquivosaida[] = "arquivosaida.txt";

    ContagemIntersecoes(posgenes, posfragmentos, n_genes, n_fragmentos, arquivosaida);
}