#include"insert.h"

#include<stdio.h>
#include<stdlib.h>

int binary(int *arr, int n, int x);
void printArr(int *arr, int n);

int main(){
	int i,n;
	int *arr;

	printf("how many elements do you want?\n");
	scanf("%d", &n);

	arr = (int *) malloc(n * sizeof(int));

	//scan in elements
	for(i =0; i< n;i++){
		printf("enter a number\n");
		scanf("%d", &arr[i]);
	}
	printf("\n");

	printArr(arr, n);
	insertS(arr, n);
	printf("\n");
	
	printf("Out of your numbers what do you want to find?\n");
	int x; 
	scanf("%d", &x);

	if(binary(arr, n, x) == -1){ printf("That number is not in the array\n");}
	int y = binary(arr,n,x);

	printf("%d is the number element it is\n");
	printf("that number is %d", arr[y]);
			

return 0;
}

void printArr(int *arr, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d, ", arr[i]);
	}
}

int binary(int *arr, int n, int x){

    int start, last, mid = 0;
    last = n;

    while(start <= last){
	mid = (start + last) / 2;
	if(arr[mid] < x){
		start = mid + 1;
	}
	else if(arr[mid] > x){
		last = mid -1;
	}
	else {
		return mid;
	}
    }
return -1; 
}

