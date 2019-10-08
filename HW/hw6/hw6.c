#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct listing {
  int id, host_id, minimum_nights,
  number_of_reviews,
  calculated_host_listings_count,
  availability_365;
  char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
  float latitude, longitude, price;
};

struct listing getfields(char* line){
   struct listing item;

   item.id = atoi(strtok(line, ","));
   item.host_id = atoi(strtok(NULL, ","));
   item.host_name = strdup(strtok(NULL, ","));
   item.neighbourhood_group = strdup(strtok(NULL, ","));
   item.neighbourhood = strdup(strtok(NULL, ","));
   item.latitude = atof(strtok(NULL, ","));
   item.longitude = atof(strtok(NULL, ","));
   item.room_type = strdup(strtok(NULL, ","));
   item.price = atof(strtok(NULL, ","));
   item.minimum_nights = atoi(strtok(NULL, ","));
   item.number_of_reviews = atoi(strtok(NULL, ","));
   item.calculated_host_listings_count = atoi(strtok(NULL, ","));
   item.availability_365 = atoi(strtok(NULL, ","));

   return item;
}

void displayStruct(struct listing items){
        printf("%d\t%d\t%s\t%s\t%s\t%lf\t%lf\t%s\t%f\n",items.id,items.host_id,items.host_name,items.neighbourhood_group,items.neighbourhood,items.latitude,
                                                        items.longitude,items.room_type,items.price);
}

void sortHost(struct listing item[22555], int len){
        int i,j;

        for(j=1;j<len;j++){
                char key[50];
                strcpy(key, item[j].host_name);
                i = j-1;
                while(i >= 0 && (strcmp(item[i].host_name,key) > 0) ){
                        strcpy(item[i+1].host_name,item[i].host_name);
                        i--;
                }
                strcpy(item[i+1].host_name, key);
        }
}

void sortPrice(struct listing item[22555], int len){
        int i,j;
        for(j=1;j<len;j++){
                float key;
                key = item[j].price;
                i = j-1;
                while(i >= 0 && (item[i].price > 0)){
                        item[i+1].price = item[i].price;
                        i--;
                }
                item[i+1].price = key;
        }
}

int main(int argc, char **argv){
    int i, count;
    int LINESIZE = 1024;
    char line[LINESIZE];
    struct listing list_items[22555];

    FILE *fp = fopen(argv[1], "r");
    FILE *fp1 = fopen(argv[2], "w");

    count = 0;
    while (fgets(line, LINESIZE, fp) != NULL){
       list_items[count++] = getfields(line);
    }

    printf("printing list with sorted hosts names\n");
    sortHost(list_items, 22555);

    printf("id\thost_id\thost_name\tneighbourhood_group\tneighbourhood\tlatitude\tlongitude\troom_type\tprice\n");
    for (i=0; i<count; i++)
       displayStruct(list_items[i]);

    printf("soring via price now\n");
    sortPrice(list_items, 22555);

    for(i=0;i<count;i++){
        displayStruct(list_items[i]);
    }

    i = 0;
    while(i != count){
        fputs(list_items[i].host_name, fp1);
        fprintf(fp1, "%f", list_items[i].price);
    }

    fclose(fp);

return 0;
}
