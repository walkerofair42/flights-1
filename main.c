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

	// generate_file("output.txt", num_flights);
	// convert("output.bin", "", flights);
	// convert("test.bin", flights);

	Sentinel flightList = newList();

	convert("test.bin", flightList);
	// printFlights(flightList);
	createFiles(flightList, "");

	// char code[5];

	// getFlightCode(flightList->head->next->f, code);
	// printf("%s\n", code);
	// printf("Number of flights in file: %d\n", (flightList->key));
	// printf("\n");
	// printReverse(flightList);

	// node *n1 = flightList->head->next;
	// node *n2 = n1->next->next;

	// swap(n1, n2, flightList);
	// printf("\n");
	// printFlights(flightList);

	// convertBinaryStringFile("test.bin", flights, num_flights);

	//printf("\n\nStrToBin: %s\n", strToBinStr("Test"));
	//printf("BinToStr: %s\n", binStrToStr(strToBin("Test")));
}