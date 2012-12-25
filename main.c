#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
typedef struct {
    int x,y;
}vector;
typedef struct{
    int n,w,s,e;
    vector vn,vw,vs,ve,vm;
}neighbours;
void printTable(int **, int);
void init(int **, int);
void play(int **, int);
void move(int **, int, vector, vector);
void shuffle(int **, int, int);
vector position(int **, int, int);
neighbours getNeighbours(int **, int, int); 
int checkSol(int **, int);
void main(){
    int n;
    int **a; 
    //get n
    n=4;
    a =(int **) malloc(n*sizeof(int));
    init(a,n);
    shuffle(a,n,500);
    printTable(a,n);
    play(a,n); 
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
void play(int **a, int n){
    int input=1,scanCheck=1,i,moves=0;
    bool check;
    vector v1,v2;
    neighbours zero;
    while(scanCheck!=EOF){
        scanCheck = scanf("%d",&input);
       
        if(scanCheck==EOF){
            exit(0);
        }
         if(scanCheck){
            //printf("Enter valid value\n");
            //scanCheck=1;
           // continue;
        
        check=true;
        //zpos=position(a,n,0);
        //inpos=position(a,n,input);
        zero = getNeighbours(a,n,0);

//        printf("%d %d %d %d \n",zero.n,zero.e,zero.w,zero.s);
        if(zero.n==input){
            //north
            v1=zero.vn;
        }
        else if(zero.w==input){
            //west
            v1=zero.vw;
        }
        else if(zero.s==input){
            //south
            v1=zero.vs;
        }
        else if(zero.e==input){
            //east
            v1=zero.ve;
        }
        else{
            check=false;
            v1 = position(a,n,input);
            vector getV2(neighbours zero, int *i, vector v1){
                vector v2;
                if(v1.x == zero.vm.x){
                    if(v1.y<zero.vm.y)
                        v2 = zero.vw; //north
                    if(v1.y>zero.vm.y)
                        v2 = zero.ve; //south
                    *i = v1.y-zero.vm.y;
                    *i = (*i>0)?(*i):-(*i);
                }
           
                else if(v1.y == zero.vm.y){
                    if(v1.x<zero.vm.x)
                        v2 = zero.vn; //east
                    if(v1.x>zero.vm.x)
                        v2 = zero.vs; //west
                    *i = v1.x - zero.vm.x;
                    *i = (*i>0)?(*i):-(*i);

                }
                return v2;
            }
            v2=getV2(zero, &i, v1);
            if(i){
                while(i!=1){
                    //printf("%d\n",i);
                    move(a,n,v2,zero.vm);
                    zero = getNeighbours(a,n,0);
                    v2=getV2(zero, &i, v1);
                    //printTable(a,n);
                    //i--;
                }
                check=true;
            }

        }
        if(check)
        {
            move(a,n,v1,zero.vm);
            moves++;
            printTable(a,n);
            if(checkSol(a,n)){
                printf("\nYou win!\n");
                exit(0);
            }
        }
        else
        {
            printf("Cannot move %d\n",input);
        }
         }

    }
}
void move(int **a, int n, vector v1, vector v2){
    int i1,j1,i2,j2;
    //v2 is zero's position
    i1=v1.x;
    j1=v1.y;
    i2=v2.x;
    j2=v2.y;
    a[i2][j2]=a[i1][j1];
    a[i1][j1]=0;
}
vector position(int **a, int n, int what){
    vector where;
    int i,j;
    bool brk=false;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(a[i][j]==what){
                where.x=i;
                where.y=j;
                brk=true;
                break;
            }
        }
        if(brk)
            break;
    }
    return where;
}
neighbours getNeighbours(int **a, int n, int what){
    neighbours n1;
    vector zero;
    zero = position(a,n,what);
    n1.vm.x = zero.x;
    n1.vm.y = zero.y;
    if(zero.y - 1>=0){
        n1.w = a[zero.x][zero.y -1];
        n1.vw.x = zero.x;
        n1.vw.y = zero.y -1;
    }
    else{
        n1.w=-1;
        n1.vw.x=-1;
        n1.vw.y=-1;
    }
    if(zero.y + 1 <n){
        n1.e = a[zero.x][zero.y +1];
        n1.ve.x = zero.x;
        n1.ve.y = zero.y +1;
    }
    else{
        n1.e = -1;
        n1.ve.x = -1;
        n1.ve.y = -1;
    }
    if(zero.x -1 >=0){
        n1.n = a[zero.x -1][zero.y];
        n1.vn.x = zero.x -1;
        n1.vn.y = zero.y;
    }
    else{
        n1.n = -1;
        n1.vn.x = -1;
        n1.vn.y = -1;
    }
    if(zero.x +1 <n){
        n1.s = a[zero.x +1][zero.y];
        n1.vs.x = zero.x +1;
        n1.vs.y = zero.y;
    }
    else{
        n1.s = -1;
        n1.vs.x = -1;
        n1.vs.y = -1;
    }
    
    return n1;
}
void shuffle(int **a, int n, int times){
    int i,last;
    vector pos;
    neighbours zero;
    last = 0;
    srand(time(NULL));
    vector randPos(neighbours z, int last){
        int rand1;
        rand1=rand()%4 + 1;
        switch(rand1){
            case 1:
                if(z.n!=last&&z.n!=-1)
                    return z.vn;
                else
                    return randPos(z,last);
                break;
            case 2:
                if(z.e!=last&&z.e!=-1)
                    return z.ve;
                else
                    return randPos(z,last);
                break;
            case 3:
                if(z.w!=last&&z.w!=-1)
                    return z.vw;
                else
                    return randPos(z,last);
                break;
            case 4:
                if(z.s!=last&&z.s!=-1)
                    return z.vs;
                else
                    return randPos(z,last);
            default:
                return randPos(z,last);        
        }

    }
    for(i=0;i<times;i++){
        zero = getNeighbours(a, n, 0);
        pos = randPos(zero,last);        
        if(pos.x==zero.vn.x && pos.y == zero.vn.y)
            last=zero.n;
        else if(pos.x==zero.ve.x && pos.y==zero.ve.y)
            last=zero.e;
        else if(pos.x==zero.vw.x && pos.y==zero.vw.y)
            last=zero.w;
        else if(pos.x==zero.vs.x && pos.y == zero.vs.y)
            last=zero.s;
        move(a, n, pos, zero.vm);
    }
    
}
int checkSol(int **a, int n){
    int i,j,k;
    k=1;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(a[i][j]!=k)
                return 0;
            else
                k = (k+1)%(n*n);
        }
    }
    return 1;
}
