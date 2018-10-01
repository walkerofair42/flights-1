/*
Authors:
    John Lahut
    James Bohrer
    Jason Deacutis 
Date: 9.30.2018
Filename: fileconverter.c
Purpose: Given a binary file of flight data, create .txt files for each airline, and           store them in appropriate directories. Also can generate the binary files             for testing purposes
Project: CSI402 Final Project
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "header.h" 

void add_zero_buffer(char*, int);

/* 
@purpose: given a filename, directory, and flight array convert the binary file and             store the flights 
@args:
    char *filename: name of binary file
    char *directory: valid existing directory to write the generated txt files to
    Flight arr[]: data structure to store the parsed flights

**
@todo: 
    - entire file structure side of things
    - probably dont need to return array of flights, but useful for testing
    - probably needs a lot more error checking
**
*/
void convert(char* filename, char* directory, Flight arr[]) {

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error loading file.\n");
        exit(EXIT_FAILURE);
    }

    // declare character array to store the flight data, binary data was stored as chars
    // the size of the incoming data should be same size of our structure
    char data[FLIGHT_SIZE];
    int counter = 0;

    // while there is data to read, store into data
    while(fread(&data, sizeof(data), 1, fp)) {
        Flight f;

        // counters for each field in the structure
        int cursor = 0;
        int f_code_c = 0;
        int origin_c = 0;
        int dest_c = 0;
        int timestamp_c = 0;

        // add null characters to terminate the string fields
        f.origin[3] = '\0';
        f.dest[3] = '\0';
        f.timestamp[16] = '\0';
        f.f_code[4] = '\0';


        // for each line of data, loop through each character
        // if there is a space, we know we are in a new field (except for timestamp)
        // cursor = 0 : flight code data
        // cursor = 1 : origin airport data
        // cursor = 2: destination airport data
        // cursor > 2: timestamp data, will contain spaces
        for(int i=0; i<strlen(data); i++) {

            // increment cursor if space is encountered
            if (data[i] == ' ') {
                cursor = cursor + 1;

                // if we are in timestamp segment, append the space, else ignore
                if (cursor > 3) {
                    f.timestamp[timestamp_c] = data[i];
                    timestamp_c++;
                }
            }

            // for each segment, append the appropriate data
            else {
                if (cursor == 0) {
                    f.f_code[f_code_c] = data[i];
                    f_code_c ++;
                }
                else if (cursor == 1) {
                    f.origin[origin_c] = data[i];
                    origin_c++;
                }
                else if (cursor == 2) {
                    f.dest[dest_c] = data[i];
                    dest_c++;
                }
                else {
                    f.timestamp[timestamp_c] = data[i];
                    timestamp_c++;
                }
            }
        }
        arr[counter] = f;
        counter++;
    }
    fclose(fp);
}

void generate_file(char filename[], int count) {

    const char *sample_airports[10] = {"AAA", "BBB", "CCC", "DDD", "EEE", "FFF", "GGG", "HHH", "III", "JJJ"};
    const char *sample_airlines[10] = {"ZZ", "YY", "XX", "WW", "VV", "UU", "TT", "SS", "RR", "QQ"};

    FILE *fp;
    FILE *fp_bin;

    fp = fopen(filename, "w");
    fp_bin = fopen("output.bin", "w");

    for (int i=0; i<count; i++){

        const char *dest = sample_airports[random_range(0, 9)];
        const char *dep = sample_airports[random_range(0, 9)];
        const char *airline = sample_airlines[random_range(0, 9)];
        char flight_code[3];
        char timestamp[17];
        char flight_data[31];
        sprintf(flight_code, "%d" ,random_range(0, 9));
        add_zero_buffer(flight_code, 2);

        char year[5];
        char month[3];
        char day[3];
        char hour[3];
        char min[3];
        sprintf(year, "%d", random_range(2000, 2018));
        sprintf(month, "%d", random_range(1, 12));
        add_zero_buffer(month, 2);
        sprintf(day, "%d", random_range(1, 31));
        add_zero_buffer(day, 2);
        sprintf(hour, "%d", random_range(1, 24));
        add_zero_buffer(hour, 2);
        sprintf(min, "%d", random_range(1, 59));
        add_zero_buffer(min, 2);

        sprintf(timestamp, "%s-%s-%s %s:%s", year, month, day, hour, min);

        

        sprintf(flight_data, "%s%s %s %s %s", airline, flight_code, dep, dest, timestamp);
        fprintf(fp, "%s\n", flight_data);
        fwrite((const void*)flight_data, sizeof(flight_data), 1, fp_bin);
    }

    fclose(fp);
    fclose(fp_bin);
}


void add_zero_buffer(char* str, int buff) {
    if (strlen(str) < buff){
            char temp = str[0];
            str[0] = '0';
            str[1] = temp;
        }
}