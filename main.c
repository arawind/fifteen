#include<stdio.h>
#include<stdlib.h>
void printTable(int **, int);
void init(int **, int);
main(){
    int n;
    int **a; 
    //get n
    n=4;
    a =(int **) malloc(n*sizeof(int));
    init(a,n);
    printTable(a,n);
}
void init(int **a, int n){
    int i,j,k;
    k=1;
    for(i=0;i<n;i++){
        a[i]=(int *)malloc(n*sizeof(int));
        for(j=0;j<n;j++){
            a[i][j]=k;
            k=(k+1)%(n*n);
        }
    }
}
void printTable(int **a,int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("\t%2d",a[i][j]);    
        }
        printf("\n");
    }
}
