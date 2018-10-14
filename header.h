#include <stdbool.h>
#include <stdio.h>

#define MAX_FLIGHT_CODE 7
#define MAX_AIRLINE_CODE 4
#define DATE_SIZE 20
#define FLIGHT_SIZE MAX_FLIGHT_CODE + (2*MAX_AIRLINE_CODE) + DATE_SIZE
#define OUTPUT_FEXT ".txt"



/*****  Structure Definitions  *****/
struct flight {
	char f_code[MAX_FLIGHT_CODE];
	char origin[MAX_AIRLINE_CODE];
	char dest[MAX_AIRLINE_CODE];
	char timestamp[DATE_SIZE];
} typedef Flight;

struct node {
    struct flight f;
    struct node *next;
	struct node *prev;
	//int size;
} typedef node;

struct sentinel {
	node *head;
	node *currPos;
	int key;
} typedef *Sentinel;


/*****  Typing Definitions  *****/


/*****  fileconverter.c Prototypes  *****/

void generate_file(const char[], int);
void convert(char*, Sentinel);
char* convertBinaryStringFile(const char*);
Flight flightFromStr(char*);
void createFiles(Sentinel, char*);

/*****  list.c Prototypes  *****/
void push(Flight, Sentinel);
node* new(Flight);
int numFlights();
Sentinel newList();
void swap(node*, node*, Sentinel);
void printReverse(Sentinel);

/*****  hash.c Prototypes  *****/
void insert(Flight);
Flight retrieve(char*);
int hash(Flight);
void expand();

/*****  indexer.c Prototypes  *****/

/*****  srchindx.c Prototypes  *****/

/*****  create.c Prototypes  *****/

/*****  utils.c Prototypes  *****/
void print_flight(Flight);
int random_range(int, int);
char* strToBinStr(char*);
char* binStrToStr(char*);
void printFlights(Sentinel);
void getFlightCode(Flight, char[]);