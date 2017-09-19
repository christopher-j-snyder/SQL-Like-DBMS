/* Christopher Snyder
   ICSI402 Programming Project 3
   CS146375			*/

#include "structs.h"
//Function to print the number of rows in a given table
void numRows(struct database * db, FILE * qFile)
{
	int i;
	int flag = 0;
	char tableName[16];
	fscanf(qFile, "%s", tableName);

	//For every table
	for(i = 0; i< db->numTables; i++)
	{
		//If the table exists, print the num of rows
		if(strcmp(db->tableArray[i]->name, tableName) == 0)
		{
			flag = 1;
			printf("%d\n", db->tableArray[i]->numrows);
			fflush(stdout);
		}	
	}
	
//If flag is 0, the table was never found. Produce a suitable message and exit.
if(flag == 0)
{
	printf("ERROR: Invalid relation: %s\n",tableName);
	fflush(stdout);
}

return;
}
