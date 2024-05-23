#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "func.h"

void OrdenaDigitos( int **A, int n, int posicao){

    long B[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int digito;

    for (int i = 0; i <= n-1;i++ ){
        digito = A[i][0]/posicao;
        digito = digito % 10;
        B[digito] = B[digito] + 1;

    }
    for (int i = 1; i<=9; i++){
        B[i] = B[i] + B[i-1];
    }

    //inicialização e alocação de memoria para C 
    int **C;
    C = malloc (n * sizeof (int*));

    for (int i=0; i < n; i++){
        C[i] = malloc (2 * sizeof (int)) ;
        
    }
    int u = 0;

    //numero significativo
    for (int i=n-1; i >= 0; i--){
        digito = A[i][0]/posicao;
        digito = digito % 10;
        B[digito] = B[digito] - 1;
        C[B[digito]][0] = A[i][0];
        C[B[digito]][1] = A[i][1];
    
    }

    //ordenação apropriada de A
    for (int i = 0; i<= n-1; i++){
        A[i][0] = C[i][0];
        A[i][1] = C[i][1];
        
    }

    //liberação de memória
    for (int i=0; i < n; i++){
        free (C[i]) ;
        
        
    }
    free (C);


}

void OrdenaNumeros(int **A, int n){

    int posicao = 1;

    //encontrar maior elemento
    int maior = A[0][0];
    for (int i = 0; i <= n-1; i++){
        if (maior < A[i][0]){
            maior = A[i][0];
        }
    }

    //chamada de OrdenaDigitos e mudança da posição considerada
    while (maior/posicao > 0){
        OrdenaDigitos(A, n, posicao);
        posicao = posicao*10;
    }

}


void ContagemIntersecoes(char arq_A[], char arq_B[], int nA, int nB, char arq_saida[]){
    FILE *arqinA;
    FILE *arqinB;
    FILE *arqoutcont;
    
    arqinA=fopen(arq_A,"r");
    arqinB=fopen(arq_B,"rt");
    
    int **A, **B, contagens[nA];

    // aloca um vetor de n* ponteiros para linhas
    A = malloc (nA * sizeof (int*));
    B = malloc (nB * sizeof (int*));
    // aloca cada uma das linhas (vetores de 2 inteiros)
    for (int i=0; i < nA; i++){
        A[i] = malloc (2 * sizeof (int)) ;
        
    }

    for (int i=0; i < nB; i++){
        
        B[i] = malloc (2 * sizeof (int)) ;
    }

    // vetor contagens com zeros
    for (int i =0; i<=nA-1; i++){
        contagens[i] = 0;
    }
    
    //leitura dos arquivos e anexamento nas matrizes
    for (int i = 0; i<=nA-1; i++){
        fscanf(arqinA,"%d,%d", &A[i][0], &A[i][1]);
    }
    for (int i = 0; i<=nB-1; i++){
        fscanf(arqinB,"%d,%d", &B[i][0], &B[i][1]);
    }
    
    //ordenação das matrizes A e B
    OrdenaNumeros(A, nA);
    OrdenaNumeros(B, nB);
    
    
    
    int primeiro_iB = 0;
    
    //verificação de onde há cada intersessão de cada intervalo
    for ( int iA = 0; iA <= nA-1; iA++){
        for (int iB = primeiro_iB; iB <= nB-1; iB++){
            if(A[iA][1] < B[iB][0] || A[iA][0] > B[iB][1]){
                if(contagens[iA] == 0){
                    primeiro_iB = iB;
                }
            }
            else {
                contagens[iA] = contagens[iA]+1;
            }
        }
    }

    //escrita no arquivo saida
    arqoutcont=fopen(arq_saida,"wt");
    for (int i =0; i<=nA-1; i++){
        fprintf(arqoutcont, "%d\n", contagens[i]);
    }
    
    //fecha arquivos usados
    fclose(arqinA);
    fclose(arqinB);
    fclose(arqoutcont);
}

void CtrlF(char arquivo_texto[], char arquivo_trecho[], char arquivo_saida[]){
    
    //preparação dos arquivos
    FILE *arq_txt;
    FILE *arq_tre;
    FILE *aux;
    FILE *arq_sai;

    arq_txt = fopen(arquivo_texto, "rt");
    arq_tre = fopen(arquivo_trecho, "rt");
    aux = fopen(arquivo_trecho, "rt");
    arq_sai = fopen(arquivo_saida, "wt");

    
    // descobrir o numeros de caracteres para alocar o texto
    char *texto;
    int h = 0;
    while (!feof(arq_txt)){
        char p;
        fscanf(arq_txt, "%c", &p);
        h++;
    }
    
    //alocação de memoria para texto
    texto = (char *)malloc((h+1) * sizeof(char));

    rewind (arq_txt);

    //leitura do arquivo e anexação dos caracteres em vetor texto 
    fscanf(arq_txt, "%s", texto);

    //alocação de memoria inicial para trecho
    char *trecho;
    trecho = (char *)malloc((100) * sizeof(char));

    rewind (arq_txt);
    int t = 0;
    while (!feof(arq_tre)){

        // descobrir o numeros de caracteres de cada trecho
        int h = 0;
        while (!feof(aux)){
            char p;
        
            fscanf(aux, "%c", &p);
            if (p == '\n'){
                if( h == 0){
                    t = 1;
                    continue;
                }
                break;
            }
            h++;

        }

        //usar o numero descoberto para realocar memoria se necessario
        if (h>100){
            
            trecho = realloc(trecho, h+1);
            
        }

        //flag caso tenha uma linha vazia do arquivo
        if (t == 1){
            char p;
            fscanf(arq_tre, "%c", &p);
            fscanf(arq_tre, "%s", trecho);
        }

        //anexação dos caracteres no vetor, para linha normal   
        else{
            fscanf(arq_tre, "%s", trecho); 
        }
        
        //encontrar aonde está o inicio e o fim dos trechos no texto 
        int i = 0;
        while(texto[i] != '\0'){
            int j = 0;
            while((trecho[j] != '\0') && (texto[i+j] == trecho[j])){
                j++;
                
            }
            if(trecho[j] == '\0'){
                fprintf(arq_sai,"%d,%d\n", i, (i+j-1) );

                //break;
            } 
            i++;
            
        }
    }

    //fechamento de arquivos
    fclose(arq_txt);
    fclose(arq_tre);
    fclose(aux);
    fclose(arq_sai);

    //liberação de memoria usada nos vetores
    free (trecho);
    free (texto);
}

void ContagemLeituras (char arquivo_genoma[], char arquivo_pos_genes[], char arquivo_fragmentos[], char arquivos_pos_fragmentos[], int n_genes, int n_fragmentos, char arquivo_saida[]){

    //chamada das funções    
    CtrlF(arquivo_genoma, arquivo_fragmentos, arquivos_pos_fragmentos);
    ContagemIntersecoes(arquivo_pos_genes, arquivos_pos_fragmentos, n_genes, n_fragmentos, arquivo_saida);
}
