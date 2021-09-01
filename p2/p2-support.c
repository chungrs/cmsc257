/**********************************
* Roy Chung
* CMSC257
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


void initialize (struct DataBase *db)
{
	db->emp = malloc(sizeof(struct Employee)*dbSIZE);//allocate memory for 100 employees
	db->total = 0;

	createRecord ("00306", "Wei", "Martin", "wm@aol.com", 98999.99, db);
	createRecord ("00307", "Mitch", "Martinez", "mitch@aol.com", 78999.88, db);
	createRecord ("00408", "David", "Boyle", "db@aol.com", 100000.01, db);
	createRecord ("00204", "Christine", "Bluer", "cb@aol.com", 40009.99, db);
	createRecord ("00305", "Stephen", "Black", "sb@aol.com", 8500.01, db);
	createRecord ("00409", "Chris", "Boyle", "cb@aol.com", 200000.01, db);
	createRecord ("00101", "Paula", "Brown", "pb@aol.com", 1000.37, db);
	createRecord ("00102", "Paul", "Green", "pg@aol.com", 2700.45, db);
	createRecord ("00203", "Chris", "Reddy", "cr@aol.com", 2304.67, db);
}

void displayMenu (struct DataBase *db)
{
	int i;
	char id[idSIZE], last_name[nameSIZE];
	int exit_flag = 0;

	while (exit_flag == 0)
	{

		printf("**************************************************************\n");
		printf("****** USERNAME Employee Database - Total Employees: %3d *****\n", db->total);
		printf("**************************************************************\n\n");

		printf("Choose one of the menu options below:\n");
		printf("1. Sort with ID\n");
		printf("2. Display all employees\n");
		printf("3. Search employee by ID\n");
		printf("4. Search employee by last name\n");
		printf("5. Delete employee by ID\n");
		printf("6. Delete employee by last name\n");
		printf("7. Exit\n");
	
		if(scanf("%d",&i)<=0){
			printf("Enter only an integer\n");
			exit(0);
		} else {
			switch(i)
			{
				case 1:
					sort(db);
					printf("\n");
					break;

				case 2:
					printDatabase(db);
					printf("\n");
					break;

				case 3:
					printf("Enter the ID you are looking for\n");
					scanf("%s", id);
					searchID(id, db);
					printf("\n");
					break;

				case 4: 
					printf("Enter the Last Name you are looking for\n");
					scanf("%s", last_name);
					searchName(last_name, db);
					printf("\n");
					break;

				case 5:
					printf("Enter the ID you are looking for\n");
					scanf("%s", id);
					deleteID(id, db);
					printf("\n");
					break;

				case 6: 
					printf("Enter the Last Name you are looking for\n");
					scanf("%s", last_name);
					deleteName(last_name, db);
					printf("\n");
					break;

				case 7:
					exit_flag = 1;
					printf("Bye!\n");
					quit(db);
					break;

				default:    printf("Invalid option\n");
			}
		}
	}
	return;
}

void createRecord (char *ID, char *first_name, char *last_name, char *email, double salary, struct DataBase *db)
{
	strcpy(db->emp[db->total].ID, ID);
	strcpy(db->emp[db->total].first_name, first_name);
	strcpy(db->emp[db->total].last_name, last_name);
	strcpy(db->emp[db->total].email, email);
	db->emp[db->total].salary = salary;
	db->total++;
	return;
}

void sort (struct DataBase *db)
{
	int n = db->total;
	int i, j;
	struct Employee temp;
	for (i = 0; i < n-1; i++)
	{
		for (j = 0; j < n-i-1; j++)
		{
			if (strcmp(db->emp[j].ID, db->emp[j+1].ID) > 0)
			{
				temp = db->emp[j];
				db->emp[j] = db->emp[j+1];
				db->emp[j+1] = temp;
			}
		}
           
	}
	return;
}

void printEmployee (int num, struct Employee emp)
{
	char full_name[fullnameSIZE];
	strcpy(full_name, emp.first_name);
	strcat(full_name, " ");
	strcat(full_name, emp.last_name);
	printf("%-3d %5s %-20s %-20s $%9.2f\n", num, emp.ID, full_name, emp.email, emp.salary);
	//free(full_name);

	return;
}

void printDatabase (struct DataBase *db)
{
	int i;
	printf("No. EmpID Employee Name        Email                Salary    \n");
	printf("--- ----- -------------------- -------------------- ----------\n");

	for (i = 0; i < db->total; i++)
	{
		printEmployee(i, db->emp[i]);
	}
	
	return;
}

void searchID (char *ID, struct DataBase *db)
{
	int i;
	printf("No. EmpID Employee Name        Email                Salary    \n");
	printf("--- ----- -------------------- -------------------- ----------\n");

	for (i = 0; i < db->total; i++)
	{
		if (strcmp(ID, db->emp[i].ID) == 0)
			printEmployee(i, db->emp[i]);
	}

	return;
}

void searchName (char *last_name, struct DataBase *db)
{
	int i;
	printf("No. EmpID Employee Name        Email                Salary    \n");
	printf("--- ----- -------------------- -------------------- ----------\n");

	for (i = 0; i < db->total; i++)
	{
		if (strcmp(last_name, db->emp[i].last_name) == 0)
			printEmployee(i, db->emp[i]);
	}

	return;
}

void deleteID (char *ID, struct DataBase *db)
{
	int i = 0, found = 0;

	while (i < db->total && found == 0)
	{
		if (strcmp(ID, db->emp[i].ID) == 0)
		{
			found = 1;
			i--;
		}
		i++;
	}

	if (found == 1)
	{
		printf("No. EmpID Employee Name        Email                Salary    \n");
		printf("--- ----- -------------------- -------------------- ----------\n");
		printEmployee(i, db->emp[i]);

		for (/*use existing i value*/; i < db -> total; i++)
		{
			db->emp[i] = db->emp[i+1];
		}

		db->total--;
	}

	return;
}

void deleteName (char *last_name, struct DataBase *db)
{
	int i = 0, found = 0;

	while (i < db->total && found == 0)
	{
		if (strcmp(last_name, db->emp[i].last_name) == 0)
		{
			found = 1;
			i--;
		}
		i++;
	}

	if (found == 1)
	{
		printf("No. EmpID Employee Name        Email                Salary    \n");
		printf("--- ----- -------------------- -------------------- ----------\n");
		printEmployee(i, db->emp[i]);
		for (/*use existing i value*/; i < db -> total; i++)
		{
			db->emp[i] = db->emp[i+1];
		}

		db->total--;
	}

	return;
}

void quit (struct DataBase *db)
{
	free(db->emp);
	free(db);
	return;
}