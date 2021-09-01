#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 11
#define emailSIZE 21
#define fullnameSIZE 21
//add other define Macros

struct Employee
{
    char ID[idSIZE];
    char first_name[nameSIZE];
    char last_name[nameSIZE];
    char email[emailSIZE];
    double salary;
    //add other struct members below
};

struct DataBase
{
    struct Employee* emp;
    int total;
};
    

/////////////////////////////////////////////////////////////////////////////////////
// Function     : initialize
// Description  : Initializes the database for CMSC257 project #2 by manually entering // the records using createRecord function
// Inputs       : struct DataBase * - pointer to the database    
// Outputs      : void
void initialize (struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : createRecord
// Description  : Creates a record of an employee in the database
// Inputs       : String ID - Employee ID number, String last_name - employee last name, String email - empoyee email, double salary - employee salary, struct DataBase *db - pointer to the database
// Outputs      : void
void createRecord (char *ID, char *first_name, char *last_name, char *email, double salary, struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : displayMenu
// Description  : Prints header with number of employees in the database and displays user options
// Inputs       : struct DataBase *db - pointer to the database
// Outputs      : void
void displayMenu (struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : sort
// Description  : Sorts the order of employees in the database by ID number
// Inputs       : struct DataBase *db - pointer to the database
// Outputs      : void
void sort (struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : printEmployee
// Description  : prints the information of a given employee
// Inputs       : struct Employee emp - employee
// Outputs      : void
void printEmployee (int num, struct Employee emp);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : printDatabase
// Description  : Prints the entire database of employees in the proper format
// Inputs       : struct DataBase *db - pointer to the database
// Outputs      : void
void printDatabase (struct DataBase *db);


/////////////////////////////////////////////////////////////////////////////////////
// Function     : displayMenu
// Description  : Searches for employee by ID number and prints matches
// Inputs       : String ID - ID to look up, struct DataBase *db - pointer to the database
// Outputs      : void
void searchID (char *ID, struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : searchName
// Description  : Searches for employee by last name and prints matches
// Inputs       : String last_name - last name to look up, struct DataBase *db - pointer to the database
// Outputs      : void
void searchName (char *last_name, struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : deleteeID
// Description  : Searches for employee by ID number and deletes first match found
// Inputs       : String ID - ID to look up, struct DataBase *db - pointer to the database
// Outputs      : void
void deleteID (char *ID, struct DataBase *db);


/////////////////////////////////////////////////////////////////////////////////////
// Function     : deleteID
// Description  : Searches for employee by last name and deletes first match found
// Inputs       : String last_name - last to look up, struct DataBase *db - pointer to the database
// Outputs      : void
void deleteName (char *last_name, struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : quit
// Description  : clears database and frees memory
// Inputs       : struct DataBase *db - pointer to the database
// Outputs      : void
void quit (struct DataBase *db);