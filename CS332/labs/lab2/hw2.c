#include<stdio.h>

void selectS(int *arr, int n){
	int i, currLoc, temp;

	for(i=1;i<n;i++){
		currLoc = i;
		while(currLoc > 0 && arr[currLoc-1] > arr[currLoc]){
			temp = arr[currLoc-1];
			arr[currLoc] = arr[currLoc-1];
			arr[currLoc-1] = temp;
			currLoc--;
		}
	}
	

	for(i=0;i<n;i++){
		printf("%d \n", arr[i]);
	}

}

int main(){
	int n, i;

	printf("How many elements do you want?\n");
	scanf("%d", &n);

	int arr[n];

	for(i = 0; i<n;i++){
		printf("give a number\n");
		scanf("%d", &arr[i]);
	}

	printf("\n\n");
	selectS(arr, n);

return 0;
}
