#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

#define         BUFFSIZE 10000
#define         ARR 10000

void insertS(char A[ARR][50], int len);
int binary(char arr[ARR][50], int n, char x[50]);
int findLen(char arr[ARR][50], int n, int ans);

int main(int argc, char **argv){

        int readIn, writeO;
        long int n;
        int i, j=0, place=0, change=0, l=0, m=0;
        char buf[BUFFSIZE];
        char tempstr[100];
        char strings[ARR][50];

        readIn = open(argv[1], O_RDONLY);
        writeO = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0700);

        if (readIn == -1 || writeO == -1){
                printf("Error with file open\n");
                exit (-1);
        }

        while ((n = read(readIn, buf, BUFFSIZE)) > 0){
                for(i=0;i<strlen(buf);i++){
                        tempstr[place] = buf[i];
                        if(buf[i] == ' ' || buf[i] == '\0' || buf[i] == '\n'){
                                for(m=0;m<strlen(tempstr);m++){
                                        if(tempstr[m] != '\n'){
                                                strings[j][m] = tempstr[m];
                                        }
                                }
                                j++;
                                change=1;
                        }
                        if(change == 1){ place = 0; change=0;}
                        else place++;
                }

                insertS(strings, j);

                char search[20];
                printf("what name would you like to search?\n");
                scanf("%s", search);

                int ans = binary(strings, j, search);

                if(ans == -1) { printf("your name is not in the list\n"); exit(1); }
                else{ printf("found %s in the list\n", strings[ans]); }

                for(i=0;i<j;i++){
                        strcat(strings[i], "\n");
                }

                for(i=0;i<j;i++){
                        if (write(writeO, strings[i], strlen(strings[i])) != strlen(strings[i])){
                                printf("Error writing to output file\n");
                                exit (-1);
                        }
                }

                printf("that name will be replaced by what?\n");
                char replace[15];
                scanf("%s", replace);
                int maxlen = findLen(strings, j, ans);

                lseek(writeO, 0, 0);
                lseek(writeO, maxlen, SEEK_CUR);
                write(writeO, replace, strlen(replace));
        }

        if (n < 0){
                printf("Error reading input file\n");
                exit (-1);
        }

        close(readIn);
        close(writeO);

return 0;
}

void insertS(char A[ARR][50], int len){
        int i,j;

        for(j=1;j<len;j++){
                char key[50];
                strcpy(key, A[j]);
                i = j-1;
                while(i >= 0 && (strcmp(A[i],key) > 0) ){
                        strcpy(A[i+1], A[i]);
                        i--;
                }

                strcpy(A[i+1], key);
        }

        for(i=0;i<len;i++){
                printf("printing names %d: %s \n", i, A[i]);
        }

}

int binary(char arr[ARR][50], int n, char x[20]){                                                                                                                       
        int start = 0, last=n, mid = 0;
        while(start <= last){
                mid = (start + last) / 2;
                if( strcmp(arr[mid], x)==0){
                        return mid;
                }
                else if(strcmp(arr[mid], x) > 0){
                        last = mid -1;
                }
                else {
                        start = mid + 1;
                }
        }

return -1;
}

int findLen(char arr[ARR][50], int n, int ans){
        int maxlen = 0, i, j;

        for(i=0;i<n;i++){
                if(i == ans){ return maxlen; }
                maxlen += strlen(arr[i]);
        }

return maxlen;
}

