/*
Authors:
	John Lahut
	James Bohrer
	Jason Deacutis
Date: 9.09.2018
Filename: list.c
Purpose: Create a singly linked list to store flight data. keeps track of number
         of flights. 
         Uses a "sentinel" struct that points to the head of the list. this is so
         we can use the linked list while reading in from file as well as chaining
         for the hash table (to be implemented)
Project: CSI402 Final Project
*/

#include <stdlib.h>

#include "header.h"


/*
@purpose: 		add a Flight to the list
@args:	  		f is a valid Flight
@assumptions: 	f,s have been instantiated
*/
void push(Flight f, Sentinel s) {
    if (s->head == NULL) {
        s->head = new(f);
        s->currPos = s->head;
    }
    else {
        s->currPos->next = new(f);
        s->currPos = s->currPos->next;
    }
    s->key++;
}

/*
@purpose: 		return a new allocated node
@args:	  		f is a valid Flight
*/
node* new(Flight f) {
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        perror("linked list mem error");
        exit(EXIT_FAILURE);
    }
    n->f = f;
    n->next = NULL;
    return n;
}

/*
@purpose: 		return number of flights
@args:	  		s is a valid sentinel
@assumptions: 	s has at least one element in it
*/
int numFlights(Sentinel s) {
    return s->key;
}

/*
@purpose: 		returns a new sentinel to the caller
*/
Sentinel newList() {
    Sentinel s = (Sentinel)malloc(sizeof(struct sentinel));
    s->currPos = NULL;
    s->head = NULL;
    s->key = 0;
    return s;
}