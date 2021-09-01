/**********************************
* Roy Chung
* CMSC401
* Project 2: C-Strings and Structs
* ---------------------------------
* Menu-driven employee database 
* application that has features to
* sort the employee database,
* display emplyee records, search
* for records, and delete records.
**********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"


int main ()
{
	struct DataBase* db;
	db = malloc(sizeof(struct DataBase));
	initialize (db);
	displayMenu (db);

	return 0;
}