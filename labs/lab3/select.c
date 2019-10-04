#include <stdio.h>
#include <stdlib.h>

void insertS(int* A, int n);               

int main(int argc, char *argv[]){
        int i, n;
	int *arr;

	printf("how many elements do you want?\n");
        scanf("%d", &n);

	arr = (int *) malloc(n * sizeof(int));

	for(i=0;i<n;i++){
		printf("give me an number\n");
		scanf("%d", &arr[i]);
	}
	
	printf("unsorted arrary\n");
	for(i=0;i<n;i++){
                printf("%d, ", arr[i]);
        }

	printf("\n sorted array \n");
	insertS(arr, n);

return 0;
}


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

        for(i=0;i<len;i++){
                printf("%d ", *(A+i));
        }
}

