#include<stdio.h>
#include<stdlib.h>

void insertS(int* A, int n){
        int i,j,len;
        len = n;

        for(j=1;j<len;j++){
                int key = *(A + j);
                i = j-1;
                while(i >= 0 && *(A+i) > key){
                        *(A + i + 1) = *(A+i);
                        i--;
                }
                *(A+i+1) = key;
        }

}


