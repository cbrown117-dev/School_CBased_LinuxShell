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
        printf("%d\t%d\t%s\t%s\t%s\t%lf\t%lf\t%s\t%f\n",items.id,items.host_id,items.host_name,items.neighbourhood_group,items.neighbourhood,items.latitude,items.longitude,
        items.room_type,items.price);
}


int main(int argc, char **argv){
    int i, count;
    int LINESIZE = 1024;
    char line[LINESIZE];
    struct listing list_items[22555];

    FILE *fp = fopen(argv[1], "r");

    count = 0;
    while (fgets(line, LINESIZE, fp) != NULL){
       list_items[count++] = getfields(line);
    }

    printf("id\thost_id\thost_name\tneighbourhood_group\tneighbourhood\tlatitude\tlongitude\troom_type\tprice\n");
    for (i=0; i<count; i++)
       displayStruct(list_items[i]);

    fclose(fp);

return 0;
}

