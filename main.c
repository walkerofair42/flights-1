/*
Authors:
	John Lahut
	James Bohrer
	Jason Deacutis
Date: 9.30.2018
Filename: utils.c
Purpose: Main entry point of program.
Project: CSI402 Final Project
*/

#include <string.h>
#include "header.h"


int main(int argc, char* argv[]) {

	FlightArray flightArray;
	init_array(&flightArray);

	convert("test.bin", &flightArray);
	sort(&flightArray);
	createFiles(&flightArray, "");
	
	printf("Capacity: %d Size: %d\n", flightArray.capacity, flightArray.size);
	destroy(&flightArray);
}