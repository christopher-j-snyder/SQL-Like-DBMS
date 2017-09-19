/* Christopher Snyder
   ICSI402 Programming Project 3
   CS146375			*/

#include "structs.h"
//Function to print an attributes type and size 
void colStat(struct database * db, FILE * qFile)
{
int i;	
int j;
int k;
int flag = 0;
int tflag = 0;
char tableName[16];
char col[25];

//Grab the table name & column name for the query from the query file
fscanf(qFile, "%s %s", tableName, col);

//For every table in the database
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		tflag = 1;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the attribute we are looking for exists, print out its type and size
				if(strcmp(db->tableArray[i]->rowArray[j]->attrArray[k]->name, col) == 0 && flag == 0)
				{
					flag = 1;
					printf("Attribute type: %s\n",db->tableArray[i]->rowArray[j]->attrArray[k]->type);
					printf("Attribute length: %d\n",db->tableArray[i]->rowArray[j]->attrArray[k]->size);
					fflush(stdout);
				}
			}
		}
	}
}

//If flag is 0 our column was never found, throw an error
if(flag == 0)
{
	printf("ERROR: Invalid attribute: %s\n", col);
	fflush(stdout);
}

//If tflag is 0, our table was never found, throw an error
if(tflag == 0)
{
	printf("ERROR: Invalid relation: %s\n",tableName);
	fflush(stdout);
}
return;

}
