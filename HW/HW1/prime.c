#include<stdio.h>

int findPrime(int givenNum){
	int i, prime = 0;	

	if(givenNum % 2 == 0) prime = 0;
	else{
		for(i = 3; i<givenNum; i++){
		        if(givenNum % i == 0){
				prime = 0;
			}
			else prime =1;

                }
        }

return prime;
}

int main(int argc, char **argv){
	int num;
        printf("Enter a number to see if it is prime\n");
	scanf("%d", &num);

	int ans = findPrime(num);

	if(ans == 0) printf("%d is not a prime number", num);
	else printf("%d is prime", num);

return 0;

}

