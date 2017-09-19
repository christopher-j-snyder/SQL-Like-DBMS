/* Christopher Snyder
   ICSI402 Programming Project 3
   CS146375			*/

#include "structs.h"
int querynum = 1;

//Function to continually run queries from the given query file until we reach the "stop" query
void runQueries(struct database * db, FILE * qFile)
{
	char query[256] = "go";
	
//While we have not encountered "stop" continue to read in and run queries
while(strcmp(query, "stop") != 0)
{

	//printf("Query Number: %d\n", querynum);	
	//querynum++;

	fscanf(qFile, "%s", query);
	//printf("Query is %s\n", query);

	//If the query is any of the following, run that respective query

	if(strcmp(query, "colStat") ==0)
		colStat(db, qFile);

	if(strcmp(query, "numCols") == 0)
		numCols(db, qFile);

	if(strcmp(query, "numRows") == 0)
		numRows(db, qFile);

	if(strcmp(query, "project") == 0)
		project(db, qFile);

	if(strcmp(query, "rowStat") == 0)
		rowStat(db, qFile);

	if(strcmp(query, "select") == 0)
		select(db, qFile);

puts("\n");
}


}
