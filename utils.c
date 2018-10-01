/*
Authors:
    John Lahut
    James Bohrer
    Jason Deacutis 
Date: 9.30.2018
Filename: utils.c
Purpose: General purpose utility functions that may be used across programs.
Project: CSI402 Final Project
*/

#include <stdlib.h>

#include "header.h"

int random_range(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

void print_flight(Flight flight) {
    printf("Flight Code: %s | Origin Airport: %s | Destination Airport: %s | Departure Date: %s\n",
        flight.f_code, flight.origin, flight.dest, flight.timestamp);
}