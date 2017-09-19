/* Christopher Snyder
   ICSI402 Programming Project 3
   CS146375			*/

#include "structs.h"

void project(struct database * db, FILE * qFile)
{
	int i;
	int j;
	int k;
	int m;
	int flag = 0;
	int tflag = 0;
	char tableName[16];
	char col[25];
	char strArray[100][50];
	long int intArray[500];
	int num = 0;
	int b;
	int found = 0;
	int sflag = 0;
		
	
	

	fscanf(qFile, "%s %s", tableName, col);
	
	//For every table
	for(i = 0; i< db->numTables; i++)
	{
		//If the table exists
		if(strcmp(db->tableArray[i]->name, tableName) == 0)
		{
	
			tflag = 1;
			//Alias the row array for readability
			struct row ** rows = db->tableArray[i]->rowArray;

			//For every row
			for(j = 0; j < db->tableArray[i]->numrows; j++)
			{
				//For every column
				for(k = 0; k < db->tableArray[i]->numcols; k++)
				{
					//puts("hello");
					fflush(stdout);
					//If the attribute exists, decide if it is str or int thing put it into 
					if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
					{
						flag = 1;

						if(strcmp(rows[j]->attrArray[k]->type, "str") == 0)
						{
							sflag = 1;
							found = 0;
							//printf("%s\n", rows[j]->attrArray[k]->strVal);
							for(b = 0; b < num; b++)
							{
								if(strcmp(strArray[b],rows[j]->attrArray[k]->strVal) == 0)
									found = 1;		
							}
							if(found == 0)
							{
								strcpy(strArray[b], rows[j]->attrArray[k]->strVal);
								num++;
							}
							
						}	
						else
						{
							found = 0;
							//printf("val is %d\n", rows[j]->attrArray[k]->intVal);
							for(b = 0; b < num; b++)
							{
								if(intArray[b] == rows[j]->attrArray[k]->intVal)
									found = 1;
							}
							if(found == 0)
							{
								intArray[b] = rows[j]->attrArray[k]->intVal;
								num++;
							}
						}
					}

				}
			}
		}
	}

	//If flag is 0, our attribute was never found, so throw an appropriate error
	if(flag == 0)
	{
		printf("ERROR: Invalid attribute: %s\n",col);
		fflush(stdout);
	}
	
	//If tflag is 0, our table was never found, throw the appropriate error
	if(tflag == 0)
	{
		printf("ERROR: Invalid relation: %s",tableName);
		fflush(stdout);
	}

	if(tflag == 1 && flag == 1 && sflag == 0)
	{
		for(b=0;b<num;b++)
			printf("%d\n", intArray[b]);

	}
	
	if(tflag == 1 && flag == 1 && sflag == 1)
	{
		for(b=0;b<num;b++)
			printf("%s\n", strArray[b]);
	}

	return;
}
