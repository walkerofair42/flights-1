#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define TABLE_SIZE  50  // 16
#define ARRAY_SIZE  1
#define MAX_FILE_LEN (MAX_AIRLINE_CODE + 4)

// to hold (Filename, Count) pairs
struct file_tuple {
    char *filename;
    int hits;
} typedef FileTuple;

// to hold a list of (Filename, Count) pairs
// dynamic
struct string_array {
    FileTuple *data;
    int capacity;
    int size;
} typedef StringArr;

// hash table keys, key is airport, value is string array of filenames
struct airport_key {
    StringArr filenames;
    char airport[MAX_AIRLINE_CODE];
} typedef Key;

// hash table
struct airport_table {
    Key *table[TABLE_SIZE];
} typedef AirportTable;

void sort_airports();
void sort_hits();

AirportTable table;

/*
@purpose: 		initializes a string array
@args:	  		arr: array to be initialized
@assumptions: 	arr has been declared 
*/
void init_str_arr(StringArr* arr){
    arr->capacity = ARRAY_SIZE;
    arr->size = 0;
    arr->data = (FileTuple*) malloc(ARRAY_SIZE * sizeof(FileTuple));
}

/*
@purpose: 		initializes the hash table 
*/
void init_table() {
    for (int i=0; i<TABLE_SIZE; i++) {
        table.table[i] = (Key*) malloc(sizeof(Key));
        strcpy(table.table[i]->airport, "-");
        init_str_arr(&table.table[i]->filenames);
    }
}

/*
@purpose: 		adds a file to the array, increments hit counter if found
@args:	  		char* filename: filename to add/search 
                StringArr *arr: array to add file tuple to
@assumptions: 	filename does not exceed max file length, arr has been initialized
*/
void add_file(char* filename, StringArr *arr) {

    // grow array if needed
    if (arr->size >= arr->capacity) {
        arr->capacity = arr->capacity*2;
        arr->data = realloc(arr->data, sizeof(FileTuple) * arr->capacity);
    }

    // look in array to see if file is already there
    // if found, increment counter, return
    for (int i=0; i<arr->size; i++) {
        if (strcmp(arr->data[i].filename, filename) == 0) {
            arr->data[i].hits++;
            // printf("Found %s in entry!\n", arr->data[i].filename);
            return;
        }
    }

    // not found, add to array, set hits to 1
    arr->data[arr->size].filename = (char*) malloc(MAX_FILE_LEN);
    arr->data[arr->size].hits = 1;
    strcpy(arr->data[arr->size++].filename, filename);
}

// algorithm from: http://www.cse.yorku.ca/~oz/hash.html
// weird parenthesis needed to silence GCC warning
unsigned long airport_hash(char *str){
    unsigned long hash = 5831;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash % TABLE_SIZE;
}

void print_table() {
    for(int i=0; i<TABLE_SIZE; i++) {
        printf("[%2d] Airport: %5s\n", i, table.table[i]->airport);
        for (int j=0; j<table.table[i]->filenames.size; j++) {
            printf("\t%-6s %2d\n", table.table[i]->filenames.data[j].filename, table.table[i]->filenames.data[j].hits);
        }
    }
}

void validate_key(unsigned long *key, char *airport) {
    
    unsigned long temp = *key+1;
        bool success = false;


        while (temp != *key) {
            if (temp >= TABLE_SIZE)
                temp = 0;
            
            if(strcmp(table.table[temp]->airport, "-") == 0){
                printf("\tnew key for %s is %lu, old was %lu.\n", airport, temp, *key);
                *key = temp;
                success = true;
                break;
            }
            temp++;
        }

        if (!success) {
            printf(">indexer: FATAL: Hash is full. New Airport: %s\n", airport);
            print_table();
            exit(EXIT_FAILURE);
        }

}

void add_airport(char* airport, char* filename) {
    unsigned long key = airport_hash(airport);

    // printf("%s\n", table.table[key]->airport);

    if (strcmp(table.table[key]->airport, airport) != 0 && strcmp(table.table[key]->airport, "-") != 0) {
        printf(">>indexer err: Attempting to insert: %s but %s already is here!\n", airport, table.table[key]->airport);
        validate_key(&key, airport);
    }

    strcpy(table.table[key]->airport, airport);
    add_file(filename, &table.table[key]->filenames);
}

void read_files(char* filename) {
    FILE *fp = fopen(filename, "r");
    Flight f;

    printf(">>indexer: indexing %s\n", filename);

    if (fp == NULL) {
        perror(">>indexer err");
        return;
    }

    while(!feof(fp)) {
        fscanf(fp, "%s %s %s %[^\n]", f.f_code, f.origin, f.dest, f.timestamp);

        if (!feof(fp)) {
            print_flight(f);
            add_airport(f.origin, filename); add_airport(f.dest, filename);
        }
    }
    fclose(fp);
}

void write_file(char* filename) {

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror(">>indexer err");
        return;
    }

    // sort_airports();
    sort_hits();

    for (int i=0; i<TABLE_SIZE; i++) {
        if(table.table[i]->filenames.size != 0) {
            fprintf(fp, "<list> %s\n\t", table.table[i]->airport);
            for (int j=0; j<table.table[i]->filenames.size; j++) {
                fprintf(fp, "%s %d ", table.table[i]->filenames.data[j].filename,
                                      table.table[i]->filenames.data[j].hits);
            }
            fprintf(fp, "\n</list>\n");
        }
    }
    fclose(fp);

}

int airport_cmp(const void *a, const void *b) {
    Key left = *(Key*)a;
    Key right = *(Key*)b;

    printf("%s %s\n",left.airport, right.airport);

    return(strcmp(left.airport, right.airport));
}

int hit_cmp(const void *a, const void *b) {
    FileTuple *left = (FileTuple*)a;
    FileTuple *right = (FileTuple*)b;

    return (left->hits >= right->hits) ? -1 : 1;
}

void sort_airports() {
    qsort(*table.table, TABLE_SIZE, sizeof(Key*), airport_cmp);
}

void sort_hits() {
    for (int i=0; i<TABLE_SIZE; i++) {
        qsort(table.table[i]->filenames.data, table.table[i]->filenames.size, sizeof(FileTuple), hit_cmp);
    }

}