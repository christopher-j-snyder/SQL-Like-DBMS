/* Christopher Snyder
   ICSI402 Programming Project 3
   CS146375			*/

#include "structs.h"
int main(int argc, char * argv[]){

//Helper function to kill the program and print an error message to be used in error checking
void die(char * message)
{
	fprintf(stderr, message);
	fflush(stderr);
	exit(1);
}

//Declaring file pointers to be used in the program
FILE *configFile;
FILE *queryFile;

//Standard error checking for number of command line arguments
if(argc != 3)
	die("Incorrect number of command line arguments. Exiting...\n");

if((configFile = fopen(argv[1], "r")) == NULL)
	die("Could not open config file. Exiting...\n");

if((queryFile = fopen(argv[2], "r")) == NULL)
	die("Could not open query file. Exiting...\n");

//Create a database pointer
struct database * newDatabase;

//Call initialize on the database and pass it the config file
newDatabase = (struct database *) initialize(configFile);

//Run queries on our database located in the query file
runQueries(newDatabase, queryFile);


return 0;
}
