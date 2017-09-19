/* Christopher Snyder
   ICSI402 Programming Project 3
   CS146375			*/

#include "structs.h"

//Function to run a select statement on our relational database.
//Select takes in a table, column, comparison operator, and a value, and returns every row that satisfies that given condition
void select(struct database * db, FILE * qFile)
{


int i;
int j;
int k;
int m;
int flag = 0;
int tflag = 0;	
int cflag = 0;
char tableName[16];
char col[25];
char cmp[1];
char val[25];
char type[3] = "hey";
char strs[3] = "str";
int intval;
int fflag = 0;

//Read in tablename, column name, and comparison operator
fscanf(qFile, "%s %s %s", tableName, col, cmp);

//For loop to get the columns type to be used for error checking
//For every table in the database
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		tflag = 1;
		//printf("num rows is %d\n",db->tableArray[i]->numrows);

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{

				//If the attribute we are looking for exists, copy its type
				if(strcmp(db->tableArray[i]->rowArray[j]->attrArray[k]->name, col) == 0)
				{
					//printf("col name is %s\n", db->tableArray[i]->rowArray[j]->attrArray[k]->name);
					flag = 1;
					strcpy(type, db->tableArray[i]->rowArray[j]->attrArray[k]->type);
					//printf("Select loop type is %s\n", type);	
					//printf("Db loop type is %s\n", db->tableArray[i]->rowArray[j]->attrArray[k]->type);
						
				}
			}
		}
	}
}

//If tflag is 0, our table was never found, throw an error
if(tflag == 0)
{
	printf("ERROR: Invalid relation: %s\n",tableName);
	fflush(stdout);
}

//If flag is 0 our column was never found, throw an error
else if(flag == 0)
{
	printf("ERROR: Invalid attribute: %s\n", col);
	fflush(stdout);
}

//if the col is of type str
if(strcmp(type, "str") == 0)
{
	//If there is an error reading it in, the user entered a col of type str but put an int as the value. Throw an error.
	if(fscanf(qFile, "%s", val) == 0)
	{
		
		printf("Error: Wrong type of value for attribute %s\n", col);
		fflush(stdout);
		cflag = 1;
	}

	//Strip the " from the query file since none of the strings in the database have any "
	char * newval = (char *) malloc(sizeof(strlen(val))); 
	newval = strtok(val, "\"");
	strcpy(val, newval);
	//printf("string is %s\n", val);

	//If the comparison operator is not == or != then we throw an error because these are the only two operators a str type can handle
	if(strcmp(cmp, "==") != 0 && strcmp(cmp, "!=") !=0)
	{
		//printf("val is %s\n",val);
		puts("Invalid comparison operator when using type str");
		fflush(stdout);
		cflag = 1;
	}
}

//if the col is of type int
if(strcmp(type, "int") == 0)
{
	//If there is an error reading it in, the user entered a col of type int but put a str as the value. Throw an error.
	if(fscanf(qFile, "%d", &intval) == 0)
	{
		printf("Error: Wrong type of value for attribute %s\n", col);
		fflush(stdout);
		cflag = 1;
	}
}

//If the following three flags are correct, our select statement has absolutely no errors, and we can proceed to print out the desired information
if(cflag == 0 && tflag == 1 && flag == 1)
{

//If the type is string use the following loop
if(strcmp(type, "str") == 0)
{

//If the comparison operator is ==
if(strcmp(cmp, "==") == 0)
{
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{
					//If the column exists and the attribute is in that column, print that row
					if(strcmp(rows[j]->attrArray[k]->strVal, val) == 0)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							//printf("Type is %s\n", rows[j]->attrArray[m]->type);

							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							else
								printf("%d\t", rows[j]->attrArray[m]->intVal);	
						}
						puts("\n");
					}
					
				}
			}
		}
	}
}

}// end ==

//if the query contains !=
if(strcmp(cmp, "!=") == 0)
{

for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{
					//If the column exists and the attribute is in that column, print that row
					if(strcmp(rows[j]->attrArray[k]->strVal, val) != 0)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
							{
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							}
							else
							{
								printf("%d\t", rows[j]->attrArray[m]->intVal);
							}
						}
						puts("\n");
					}
				}
			}
		}
	}
}

}//end !=
}//end string select operations

//else indicates the type was not a str and is instead an int, so do int operations
else
{

//If the query contains ==
if(strcmp(cmp, "==") == 0)
{
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{
					//If the column exists and the attribute is in that column, print that row
					if(rows[j]->attrArray[k]->intVal == intval)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
							{
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							}
							else
							{
								printf("%d\t", rows[j]->attrArray[m]->intVal);
							}
						}
						puts("\n");
					}
				}
			}
		}
	}
}

}// end ==

//If the query contains !=
if(strcmp(cmp, "!=") == 0)
{
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{
					//If the column exists and the attribute is in that column, print that row
					if(rows[j]->attrArray[k]->intVal != intval)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
							{
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							}
							else
							{
								printf("%d\t", rows[j]->attrArray[m]->intVal);
							}
						}
						puts("\n");
					}
				}
			}
		}
	}
}

}

if(strcmp(cmp, "<=") == 0)
{
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{
					//If the column exists and the attribute is in that column, print that row
					if(rows[j]->attrArray[k]->intVal <= intval)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
							{
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							}
							else
							{
								printf("%d\t", rows[j]->attrArray[m]->intVal);
							}
						}
						puts("\n");
					}
				}
			}
		}
	}
}

}

//If the query contains >= 
if(strcmp(cmp, ">=") == 0)
{
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{		
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{
					//If the column exists and the attribute is in that column, print that row
					if(rows[j]->attrArray[k]->intVal >= intval)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
							{
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							}
							else
							{
								printf("%d\t", rows[j]->attrArray[m]->intVal);
							}
						}	
						puts("\n");
					}
				}
			}
		}
	}
}

}

if(strcmp(cmp, ">") == 0)
{
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{

					//If the column exists and the attribute is in that column, print that row
					if(rows[j]->attrArray[k]->intVal > intval)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
							{
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							}
							else
							{
								printf("%d\t", rows[j]->attrArray[m]->intVal);
							}
						}
						puts("\n");
					}
				}
			}
		}
	}
}

}

//If the query contains <
if(strcmp(cmp, "<") == 0)
{
for(i = 0; i< db->numTables; i++)
{
	//If the table exists
	if(strcmp(db->tableArray[i]->name, tableName) == 0)
	{
		//Alias the row array for readability
		struct row ** rows = db->tableArray[i]->rowArray;

		//For every row
		for(j = 0; j < db->tableArray[i]->numrows; j++)
		{
			//For every column
			for(k = 0; k < db->tableArray[i]->numcols;k++)
			{
				//If the column exists
				if(strcmp(rows[j]->attrArray[k]->name, col) == 0)
				{
					//If the column exists and the attribute is in that column, print that row
					if(rows[j]->attrArray[k]->intVal < intval)
					{
						fflag = 1;
						for(m = 0; m < db->tableArray[i]->numcols; m++)
						{
							if(strcmp(rows[j]->attrArray[m]->type, "str") == 0)
							{
								printf("%s\t", rows[j]->attrArray[m]->strVal);
							}
							else
							{
								printf("%d\t", rows[j]->attrArray[m]->intVal);
							}
						}
						puts("\n");
					}
				}
			}
		}
	}
}

}

}//end else

}

//If the clfag is 0, no comparison operator errors were found.
//If tflag is 1, the table WAS found in the database
//If flag is 1, the column WAS found in the database
//If fflag is 0, no entries in the database satsified the given condition, so let the user know.
if(cflag == 0 && tflag == 1 && flag == 1 && fflag == 0)
	puts("No tuples satisfy the given condition");

return;
}
