/**Assignment 1*/
/**Fatoumatta Touray*/
/**C21354101*/

#define _CRT_SECURE_NO_WARNINGS 1
#define bool int
#define false 0
#define true (!false)

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Preprocessor Variable
#define SIZE 5//Maximum of 5 books in the library

//Structure template for data part of the linked list
struct review {
	char reviewerName[50]; //the name of the reviewer
	char reviewContent[200]; //the contents of the review
	int reviewStars;
	struct review* next; //a pointer to the next review in the linked list
};

//Stucture template for data part of the linked list of the book
struct book {
	//have to make this a size 10 in order to leave a space for the null character
	char identifier[10]; //have to make this a char because thr format is (XXXX-XXXX) which includes a hyphen
	char name[50]; //book name
	char author[50];//book author
	int publicationYr;//year book was published
	bool loanStatus;//whether book is loaned or not
	char cusName[50];//name of cus who loaned book
	int numOfLoans; //number of times a book has been loaned
	struct review* rev;

};


//Stucture template for one node
struct LinearNode {
	struct book* element;
	struct review* reviews;
	struct LinearNode* next;
};


// Function prototypes
void readFromFile(FILE*);
void saveToFile(FILE*);
void menuOptions();
void enter();
void addNewBook();
bool validateIdFormat(char*);
bool uniqueID(char*);
bool isEmpty();
void borrowBook();
void returnABook();
void deleteBook();
void viewAllBooks();
void viewABook();
void popularity();
void rateReviews();
void addReviews();
void viewReviews();


// Global Variables
struct LinearNode* front = NULL; //front of the list
struct LinearNode* last = NULL; //pointer to last node in the list - not used in this code


/**A library wishes to keep a record of the books that it has in stock. You need to
create a system in C that displays a menu which allows the following options to be
presented to the user:*/

/**************MAIN FUNCTION*******************/
void main() {
	/**To display the menu options use a if statement and call the options in the menu options
	call menuOptions() in the main*/

	FILE* fp;

	//The program should check to see if file book.dat exists on your drive
	fp = fopen("book.dat", "rb"); //open a text file for reading - this will give an error if no file exists

	/*If it doesn’t then a message should appear on the screen to indicate to
the user that a database of books doesn’t exist and so the user will need
to input the books.*/
	if (fp == NULL) {
		printf("ERROR - A database of books doesn't exist.\nBooks will need to be added.\n");
		enter();
	}
	else {
		readFromFile(fp);
		enter();
	}

	char option = ' '; //declared as a char incase user inputs a letter the program won't crash out
	

	while (option != '9') { //while loop keeps the user trapped until a valid menu option is chosen                                                                    
		system("cls"); //this clears the screen
		//keep displaying menu unless the want to exit the program 
		menuOptions();

		printf("\n\nEnter menu option you wish to carry out: "); //Ask the user which menu option they wish to proceed with
		scanf("%c", &option); //takes in the value of the menu option

		//switch statement to do menu because easier to read and more efficient than if-else statements
		switch (option)
		{
		case '1':
			enter(); //calls enter() method which clears the screen and has a getchar() so screen doesn't disappear straight away
			addNewBook(); //calls method that adds a book into the library - LinkedList
			break;
		case '2':
			enter();
			borrowBook(); //calls method that allows a book to be borrowed from the library
			break;
		case '3':
			enter();
			returnABook(); //calls method that allows a book to be returned if borrowed from the library
			break;
		case '4':
			enter();
			deleteBook(); //calls method that allows a book to be deleted from the library
			break;
		case '5':
			enter();
			viewAllBooks(); //calls method that allows all book to be displayed from the library 
			break;
		case '6':
			enter();
			viewABook(); //calls method that allows a specific book to be displayed from the library
			break;
		case '7':
			enter();
			popularity();  //calls method that displays the least and most popular books in the library
			break;
		case '8':
			enter();
			rateReviews();
			break;
		case '9':
			enter();//this is so the screen doesn't clear so fast
			system("cls"); //this clears the screen
			printf("Exiting Program");
			saveToFile(fp); //this calls the method that saves the elements from the ArrayList to the data file.
			enter();
			break;
		default:
			printf("Error - invalid menu option.\n"); //if anything other than 1,2,3,4,5,6,7,8 or 9 is inputted an error message will display
			break;
		}
	} 

}


//========================================================================================================================================

/*METHOD TO POPULATE THE LINKED LIST WITH DATA FROM BOOK.DAT FILE IF FOUND*/
void readFromFile(FILE *fp) {
	
	fp = fopen("book.dat", "rb"); //open a text file for reading - this will give an error if no file exists


		/*If the file does exist, then the books in the file should be copied into
	the linked list. A message should appear to say that the system has
	been populated with books from the data file*/
	struct book* aBook;
	struct LinearNode* aNode;

	/*This is for the first book*/
	//create space for new book
	aBook = (struct book*)malloc(sizeof(struct book)); //allocate space in memeory for a book

	//create space for a new node
	aNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));

	while (fread(aBook, sizeof(struct book), 1, fp) != NULL) {
		
		aNode->next = NULL;
		aNode->element = aBook;

		if (isEmpty()) { //if the list is empty the node will be the front and last element as it will be the only element in the list
			front = aNode;
			last = aNode;
		}
		else { //add the book to the end of the list.
			last->next = aNode;
			last = aNode;
		}

		/*This creates a new box for the next book that is going to be read and added back to the list from the file*/
		//create space for new book
		aBook = (struct book*)malloc(sizeof(struct book)); //allocate space in memeory for a book
		//create space for a new node
		aNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));

	}

	//print statement letting the user know that the book has been added.
	printf("Books from the data file have populated the system.\n");

	fclose(fp);
	
}

//========================================================================================================================================

void saveToFile(FILE* fp) {

	fp = fopen("book.dat", "wb");

	struct LinearNode* current = front;

	while (current != NULL) {
		fwrite(current->element, sizeof(struct book), 1, fp);
		
		current = current->next;
	}
	printf("\nThe system has populated the data file with books.\n");

	fclose(fp);
}

//========================================================================================================================================

/**This method holds a getchar() and tells the user to press enter to continue*/
void enter() {
	printf("\nPress enter to continue");
	getchar(); getchar(); //this is so that the user has time to read the print statements on the screen before they are cleared.
	system("cls"); //this clears the screen to remove the print statement
}

//========================================================================================================================================

/*This method displays the menu options and is called in the main*/
void menuOptions() {
	printf("\t\t-------MENU OPTIONS-------\n");
	printf("Please choose an menu option displayed below (1-9)");
	//1. Add a new book to the library
	printf("\n1. Add a new book to the library");
	//2. Allow a customer to borrow a book
	printf("\n2. Allow a customer to borrow a book");
	//3. Allow a customer to return a book
	printf("\n3. Allow a customer to return a book");
	//4. Delete an old book from the library stock
	printf("\n4. Delete an old book from the library stock");
	//5. View all books
	printf("\n5. View all books");
	//6. View a specific book
	printf("\n6. View a specific book");
	//7. View details of most popular and least popular books
	printf("\n7. View details of most popular and least popular books");
	//8. This should be an appropriate option that you provide
	printf("\n8. Record or View Reviews");
	//9. Exit the system
	printf("\n9. Exit the system");
}

//=========================================================================================================================

/**Assume that there is a maximum of 5 books in the library. An error
message will appear if the list is full. Ensure that all book identifiers
are unique and that the date of publication is not older than the year
2017.*/
void addNewBook() {
	
	printf("\t\tADDING A BOOK IN THE LIBRARY\n\n");

	struct book* aBook;
	struct LinearNode* aNode;

	//create space for new book
	aBook = (struct book*)malloc(sizeof(struct book)); //allocate space in memeory for a book

	//create space for a new node
	aNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));

	/**------------------------------MAX OF 5 BOOKS - CHECK IF LIBRARY IS FULL----------------------------*/

	//c doesn't have a method to check the size in the Linked List
	//so a way to count the amount of books in the list is to create an int variable called count iterate through the list
	//while the current book does not equal null it incremenents the variable count
	//if count equals 5 display a message saying the library is full and break the loop (displays menu again)
	int count = 0; //this keeps count of how many books is in the list
	struct LinearNode* numOfBooks = front; //point to the front element
	while (numOfBooks != NULL) {
		count++; //increment count until numOfBooks equals NULL (no more elements
		numOfBooks = numOfBooks->next; //move to the next element 
	}

	if (count == SIZE) //if count equals the SIZE which is 5 no more books can be added and the user will be sent back to the menu options
		printf("Library is full. A new book cannot be added.\nSorry for any inconviences this may cause.\nA book will need to be deleted in order to add a new book\n");
	else {

		/**------------------------------ASK USER TO INPUT DETAILS ABOUT BOOK----------------------------*/
		
		//Validating the book identifier - keep them trapped in a loop if the format is not correct
		//i.e validateIdFormat() method returns false;
		printf("Enter book identifier (XXXX-XXXX): ");
		scanf(" %[^\n]", aBook->identifier); 

		while (!validateIdFormat(aBook->identifier)) {
			//if the format of the id is not valid or the id already exists the user is trapped in a loop until both conditions are met
			printf("\nError - The format of the identifier is invalid\n"); //error message telling user the format is invalid will display if format is wrong
			
			printf("Enter book identifier (XXXX-XXXX): ");
			scanf(" %[^\n]", aBook->identifier); //takes in the id value if the format is wrong or id is not unique
		}

		// Check if the identifier is unique
		if (!isEmpty()) {
			
			while (!uniqueID(aBook->identifier)) {

				printf("\nA book with this identifer has been found. Enter a different identifier\n");

				printf("Enter book identifier (XXXX-XXXX): ");
				scanf(" %[^\n]", aBook->identifier); //takes in the id value if the format is wrong or id is not unique
			}
		}

		//Ask user to input the book name
		printf("Enter the book name: ");
		scanf(" %[^\n]", aBook->name);
		
		//%[^\n] allows strings with spaces, and scanf will read the entire line until the newline character.
		//this is the only way to input the string / scanf("%s", aBook->name); doesn't allow for me to type anything - it just shows up blank

		//Ask user to enter the name of the author
		printf("Enter the author of the book: ");
		scanf(" %[^\n]", aBook->author);

		//Ask user to enter publication year of the book
		printf("Enter year of publication: ");
			scanf("%d", &aBook->publicationYr);
			//Ensure that the date of publication is not older than 2017

			if (aBook->publicationYr > 2017) { //this will prompt the user to enter a year that not older than 2017
				printf("\nERROR - Date of publication cannot be older than 2017.\n");
				printf("Enter year of publication: ");
				scanf("%d", &aBook->publicationYr);
			}

		//Set book loaned to false because book is only being added and can't be loaned yet
		aBook->loanStatus = false;

		//Set customer name will be copied from the customer
		strcpy(aBook->cusName, " "); //strcpy - will copy the content of the customers name to cusName

		//Number of times book has been loaned - initialised to 0 because book is only being created and is new
		aBook->numOfLoans = 0;

		/**----------------------------ADDING THE BOOK TO THE LIST----------------------*/
		if (aNode == NULL)
			printf("ERROR - no space for the new node");
		else {
				aNode->next = NULL;
				aNode->element = aBook;

				if (isEmpty()) { //if the list is empty the node will be the front and last element as it will be the only element in the list
					front = aNode;
					last = aNode;
				}
				else { //add the book to the end of the list.
					last->next = aNode;
					last = aNode;
				}

				//print statement letting the user know that the book has been added.
				printf("\nThe book has been added to the library successfully.\n");
			}
	}
	enter();
}

//========================================================================================================================================

bool validateIdFormat(char *id) {

	//Have to check that the length of the book identifier is 9 characters long (8 numbers and a hyphen)
	if (strlen(id) != 9) 
		return false; //if the length of the book identifier is not 9 characters long flase is returned
	

	//Have to split the check into 3 parts:
	//1. First 4 digits
	for (int i = 0; i < 4; i++) { //i < 4 because characters are counted from 0 (0, 1, 2, 3, 4) - 5 characters 
		if (id[i] < '0' || id[i] > '9')
			return false; //this will stop the method here 
	}

	//2. The hyphen
	if (id[4] != '-')
		return false; //if the 4th character in the id is not a hyphen return false

	//3. Last 4 digits
	for (int i = 5; i < 9; i++) //if the characters between the 5th and 8th not a number between 0 and 9 return false
		if (id[i] < '0' || id[i] > '9')
			return false;

	//If all the conditions above are true return true - the book id is valid
	return true;
}

//========================================================================================================================================

/*This method is to check whether the book identifier is unique - i.e. the only one in the LinkedList*/
//using call by reference because I don't want to the change the identifier variable
bool uniqueID(char* id) {//the method takes in the id as a parameter 
	struct LinearNode* current = front; //current points to the first book in this list
	bool correct = true;
	
	//Iterate through the list and compare the book identifiers with the identifier
	while (current != NULL) { 
		if (strcmp(current->element->identifier, id) == 0) { //compare the id of the current node with the id passed in as a parameter from the addNewBook() method
			correct = false; //if both the ids are equal false is returned
		}
		current = current->next; //if it doesn't current is now the next element and the loop will keep going until current is null (no more) or id is not unique
	}

	return correct; //if id is unique i.e. not equal to the id of the current element true is returned
}	

//========================================================================================================================================

/*This method checks if the LinkedList is empty*/
bool isEmpty() {
	if (front == NULL)
		return true; //if it is empty true is returned
	else
		return false; //if not empty false is returned
}
//==========================================================================================================================================

/**Borrow a book - The identifier of the book is input. If the book is found and it’s not already borrowed by another customer, 
then the customer name is input and added to the book, also the status of the book is updated
and the value storing the number of times the book has been taken out
is updated by 1. If the book isn’t found or has already been borrowed
then appropriate error messages should be displayed.*/
void borrowBook() {

	printf("\t\tBORROWING A BOOK\n\n");

	char id[10];//variable that takes in the identifier of the book to be borrowed
	char name[50]; //variable that takes in the name of the customer that wishes to borrow the book.

	printf("Enter the identifier of the book that is wished to be borrowed: ");
	scanf("%s", id); //takes in the id

	while (!validateIdFormat(id)) { //validating the id format is correct
		//Ask the user to input the book identifier
		printf("Enter the identifier of the book that is wished to be borrowed: ");
		scanf("%s", &id); //takes in the id

		if (!validateIdFormat(id))
			printf("Error - the format of the book identifier inputted is incorrect.\n\n");
	}


	struct LinearNode* current = front;
	bool found = false;
	
	//Have to search through the Linked List and check if the book exists
	while (current != NULL) {
		if ((strcmp(id, current->element->identifier) == 0)) { //if the identifier of the current element taht the pointer is pointing to equals the id of the book the user entered
			printf("Book '%s' has been found in the library system\n", id);

			//Display the info of the book
			printf("\n\nBook Identifier: %s", current->element->identifier);
			printf("\nTitle: %s", current->element->name);
			printf("\nAuthor: %s", current->element->author);
			printf("\nPublication Year: %d", current->element->publicationYr);


			found = true; //if a match if found - found is true and message saying book has been found is displayed.

			//have to make sure that the book is not being loaned out
			if (current->element->loanStatus == true) { //if it is true book is being loaned so it can't be borrowed because when creating book it is set to false
				printf("Sorry the book '%s' is already being loaned out\n", id);
				enter();
				return; //this ends the function and brings the user back to the menu option
			}
			else {
				printf("\n\nPlease enter the name of the customer who wishes to borrow the book:");
				scanf(" %[^\n]", name);
				strcpy(current->element->cusName, name); //strcpy copies the name the user entered into the book under the customer name
				//current->element->cusName = name; - this gives me an error
				current->element->loanStatus = true; //if book is found and the loan status is false meaning it hasn't been borrowed set is so that is is now true 
				//book is now being borrowed
				current->element->numOfLoans++; //increment sthe number of times a book has been loaned 

				printf("\nBook '%s' has been borrowed by %s.\n", current->element->identifier, current->element->cusName); //displaying message to user syaing which and who is borrowing a boook
				enter();
				return; //this brings the user to the menu options
			}
		}

		current = current->next; //keeps iterating to see if a match between the id of current element and id user entered
	}
	//If the book doesn't exist i.e., can't be found display an error message
	//If loan status is true display an error message
	//If a book that matches the identifier is found and the loan status is false
	//change the status to true to indicate the book is now on loan
	//and increment the loan value count for that book

	if (!found) { //if book is not found - i.e. not in Linked List display error message
		printf("Book %s has not been found in the library system\n", id);
	}
	enter(); //so when the method is done executing it doesn't immediately display the menu
}

//========================================================================================================================================

/*Return a book
The identifier of the book and customer name are input. If the book is found and it has been borrowed by that customer then its status is
updated accordingly otherwise appropriate error messages are displayed.*/

void returnABook() {

	printf("\t\tRETURNING A BOOK TO THE LIBRARY\n\n");

	struct LinearNode* current = front;
	bool found = false;

	char id[20]; //variable that takes is id
	char custName[50]; //variable that takes in customers name

	while (!validateIdFormat(id)) { //this validates the format of the id - keeps user trapped until correct format is entered
		//Ask the user to input the book identifier
		printf("Please Enter the Identifier of the Book to be Return: "); 
		scanf(" %s", id); 

		if (!validateIdFormat(id)) 
			printf("Error - the format of the book identifier inputted is incorrect.\n\n"); 
	} 
	
	printf("Please Enter the Customer Name: ");
	scanf(" %[^\n]", custName); 

	if (isEmpty()) //no books in the library - LinkedList
		printf("\nError - There is No Books in the Library");
	else {
		while (!found && current != NULL) { //will terminate when book is found or no more elements to iterate to next
			//if (strcmp(id, current->element->identifier) == 0) {
			if ((strcmp(id, current->element->identifier) == 0)) { //if the id entered by user equals the if of the current element
				
				found = true; //book has been found
				//if (strcmp(custName, current->element->cusName) == 0) {
				if (strcmp(custName, current->element->cusName) == 0) { //then have to check if the name matches the cusName of the current element
					//if it does then loan status is set to false because book is not being borrowed anymore
					current->element->loanStatus = false;
					strcpy(current->element->cusName, ""); //the field that stores the customer name is now blank becuase it is not being borrowed anymore

					printf("\nBook with identifier %s has been successfully returned by %s", id, custName);
				}
				else //if the book id and the customer name don't match then a mesaage telling the user that the book is not borrowed by that person is displayed
					printf("\nError - Book with identifier %s has not been borrowed by %s", id, custName);
				
			}
			else //if id is not found current is now the next element
				current = current->next;
		}

		if (!found) //if the whole list has been travesered and an id is not found a message saying id is not in library is displayed
			printf("\nError - Book with identifier %s can't be found in library", id);
	}
	enter();
}

//========================================================================================================================================

/*Delete a specific book
This option is to remove old books from the library stock. The user will need to indicate which book they wish to delete by inputting a
book identifier. Note that only books older than 2010 can be deleted.*/
void deleteBook() {
	struct LinearNode* current = front;
	struct LinearNode* previous = NULL;
	bool found = false;

	printf("\t\tDELETING A BOOK IN THE LIBRARY\n\n");

	if (isEmpty()) //this displays a message telling the user that there is no books and brings them back to the menu option
		printf("\nERROR - There is currently no books to delete in the library");
	else {

		char id[10];
		printf("Please Enter the Identifier of the Book you wish to delete: ");
		scanf("%s", id); //takes in the id

		while (!validateIdFormat(id)) { //validate the format of the id and keep user trapped in a loop till correct format is entered
			if (!validateIdFormat(id))
				printf("\nError - Format of identifier entered in incorrect\n");

			printf("Please Enter the Identifier of the Book you wish to delete: ");
			scanf("%s", id); //takes in the id
		}

		current = previous = front; //both current and previous is set to the first element

		while (!found && current != NULL) {
			
			if ((strcmp(id, current->element->identifier) == 0)) {//if the id is found in the list then found is true
				found = true;
			}
			else {
				previous = current; //previous is now the element current is
				current = current->next; //and current is now the next element
			}
		}

		if (!found) { //if it is not found, a message informing the user is displayed
			printf("\nError - Book with identifier %s can't be found in library", id);
			getchar();
		}
		else { //if it is found 
			/*Books that are on loan cannot be deleted only books that aren't not on loan and are not older than 2010*/
			if (current->element->publicationYr < 2010) { //checks that the publication yr is older than 2010
				
				//if (current->element->publicationYr < 2010)
					printf("\nBook has been found but cannot be deleted as it is not older than 2010\n");
				
				getchar();
			}
			else if (current->element->loanStatus == true) {
				//if (current->element->loanStatus == true)
					printf("\nBook is currently on loan and cannot be deleted until it is returned\n");

				getchar();
			}
			else if (current == front) { //delete element if first in list
				front = front->next;
				free(current);
				printf("\nBook with identifier %s has been deleted from library.\n", id);
				getchar();
			}
			else if (current == last) { //delete element if last in list
				last = previous;
				last->next = NULL;
				free(current);
				printf("\nBook with identifier %s has been deleted from library.\n", id);
				getchar();
			}
			else { //delete element from middle of list
				previous->next = current->next;
				free(current);
				printf("\nBook with identifier %s has been deleted from library.\n", id);
				getchar();
			}
			
		}

	}
	enter();
}

//========================================================================================================================================

/**Method that displays all the books in the library (linked list)*/
void viewAllBooks() {
	
	struct LinearNode* current = front;;

	printf("\t\tVIEWING ALL BOOKS IN THE LIBRARY\n\n");

	if (isEmpty())
		printf("\nERROR - There is currently no books to view in the library");
	else {
		
		//printf("Book Identifier\tBook Name\tAuthor Name\tPublication year\tLoaned\tCustomer Name\tLoan Count\n");
		printf("----------------------------------------------------------------------------------------------------");
		while (current != NULL) {
			//printf("\n%s\t%s\t%s\t%d\t%d\t%s\t%d", current->element->identifier, current->element->name, current->element->author, current->element->publicationYr, current->element->loanStatus, current->element->cusName, current->element->numOfLoans);
			printf("\n\nBook Identifier: %s", current->element->identifier);
			printf("\nTitle: %s", current->element->name);
			printf("\nAuthor: %s", current->element->author);
			printf("\nPublication Year: %d", current->element->publicationYr);
			printf("\nLoan Status: %s", current->element->loanStatus ? "On Loan" : "Not On Loan");
			printf("\nCustomer Name: %s", current->element->cusName);
			printf("\nNumber of Times Book has been Loaned: %d", current->element->numOfLoans);

			current = current->next; //moves to the next element and prints it out
		}
		printf("\n");
	}

	enter();

}


/*Method to view a specific book by entering the book identifier.*/
void viewABook() {
	char id[10];

	printf("\t\tVIEW A BOOK IN THE LIBRARY\n\n");

	printf("Please Enter the Identifier of the Book you wish to view: ");
	scanf("%s", id);

	while (!validateIdFormat(id)) {
		if (!validateIdFormat(id))
			printf("\nError - Format of identifier entered in incorrect\n");

		printf("Please Enter the Identifier of the Book you wish to view: ");
		scanf("%s", id);
	}
	

	struct LinearNode* current = front;
	bool found = false;

	if (isEmpty())
		printf("\nERROR - There is currently no books to view in the library");
	else {
		while (current != NULL && !found) {
			if (strcmp(id, current->element->identifier) == 0) {
				found = true;
				printf("\n\nBook Identifier: %s", current->element->identifier);
				printf("\nTitle: %s", current->element->name);
				printf("\nAuthor: %s", current->element->author);
				printf("\nPublication Year: %d", current->element->publicationYr);
				printf("\nLoan Status: %s", current->element->loanStatus ? "On Loan" : "Not On Loan");
				printf("\nCustomer Name: %s", current->element->cusName);
				printf("\nNumber of Times Book has been Loaned: %d", current->element->numOfLoans);

			}
			current = current->next;
		}

		if (!found) {
			printf("\nError - Book with identifier %s can't be found in library", id);
		}
	}

	enter();
}

void popularity() {
	struct LinearNode* current = front;
	int maxLoans = 0; 
	int minLoans = 1000;
	char maxID[10]; 
	char maxTitle[50];
	char minID[10];
	char minTitle[50];

	printf("\t\tMOST AND LEAST POPULAR BOOKS IN THE LIBRARY\n\n");

	while (current != NULL) {
		if (current->element->numOfLoans > maxLoans) { //if the number of loans of the current element is greater than maxLoans set that as the maxLoans
			//keep iterating through the list until the last element is reached
			maxLoans = current->element->numOfLoans;
			strcpy(maxID, current->element->identifier); //this copies the book identifier from the current element into the maxID variable so it can be displayed
			strcpy(maxTitle, current->element->name); //this copies the book name from the current element into the maxTitle variable so it can be displayed
		}
		if (current->element->numOfLoans < minLoans) { //if the number of loans if the current element less than the value for minLoans
			minLoans = current->element->numOfLoans; //set the variable minLoan to the number of loans the current variable has.
			strcpy(minID, current->element->identifier); //this copies the book identifier from the current element into the minID variable so it can be displayed
			strcpy(minTitle, current->element->name); //this copies the book name from the current element into the minID variable so it can be displayed
		}
		current = current->next;
	}

	printf("Most Popular Book: %s - %s, Loaned %d Times\n", maxID, maxTitle, maxLoans);
	printf("Least Popular Book: %s - %s, Loaned %d Times\n", minID, minTitle, minLoans);

	enter();

}


//IDEA - Rate and reviews
void rateReviews() {
	printf("\t\tADD REVIEWS OR VIEW REVIEWS\n\n");
	//record a review that was left
	//reviews can only be made before the book has been returned

	char opt = ' '; //variable to take in menu option

	if (isEmpty()) //if there is no books in system display message
		printf("There is no books in the system");
	else {
		//menu options
		printf("1. Record a book review");
		printf("\n2. View Reviews\n\n");

		printf("Choose an option from below. (1 or 2): ");
		scanf("%c", &opt);


		switch (opt)
		{
		case '1':
			enter(); //calls enter() method which clears the screen and has a getchar() so screen doesn't disappear straight away
			addReviews(); //calls method that adds reviews
			break;
		case '2':
			enter();
			viewReviews(); //calls method that prints reviews
			break;
		default:
			printf("Error - invalid menu option.\n"); //if anything other than 1,2 or 3 is inputted an error message will display
			break;
		}
	}

	getchar();

}



void addReviews() {

	struct LinearNode* current = front;
	struct LinearNode* aNode;
	struct review* aReview;

	char bookId[10];

	//Ask the user to enter the book id
	printf("Enter book identifier (XXXX-XXXX): ");
	scanf(" %[^\n]", bookId);

	while (!validateIdFormat(bookId)) {
		//if the format of the id is not valid or the id already exists the user is trapped in a loop until both conditions are met
		printf("\nError - The format of the identifier is invalid\n"); //error message telling user the format is invalid will display if format is wrong

		printf("Enter book identifier (XXXX-XXXX): ");
		scanf(" %[^\n]", bookId); //takes in the id value if the format is wrong or id is not unique
	}

	
	while (current != NULL) { //loop through nodes until the book with the given identifier is found
		if (strcmp(current->element->identifier, bookId) == 0) {

			aNode = (struct LinearNode*)malloc(sizeof(struct LinearNode)); //to allocate memeory for a new node
			if (aNode == NULL) {
				printf("ERROR - no space for the new node");

			}
			else {
				aReview = (struct review*)malloc(sizeof(struct review)); //allocating memory for a new review struct
				if (aReview == NULL) {
					printf("ERROR - no space for the new node");
					free(aNode);
					return;
				}

				//Ask user to enter name of the reviewer, number of stars the reviewer rated and the reasons
				printf("Enter the name of the reviewer: ");
				scanf(" %[^\n]", aReview->reviewerName);

				printf("Enter the number of stars (1-5) for the review: ");
				scanf("%d", &aReview->reviewStars);

				printf("Enter the review content: ");
				scanf(" %[^\n]", aReview->reviewContent);


				aReview->next = NULL; //set the next review pointer to NULL since this is the last review
				
				// Add review to node's list of reviews
				if (current->reviews == NULL) {
					//the first review of the book is added to the linked list at the current node.
					current->reviews = aReview;
				}
				else {
					struct review* lastReview = current->reviews;
					while (lastReview->next != NULL) {
						//iterates the linked list of reviews for the book to find the last review in the list
						lastReview = lastReview->next;
					}
					lastReview->next = aReview;
				}
				
				//set up the new node to be added to the list
				aNode->element = current->element; //assigns the book information from the current node to the element field of the new node
				aNode->reviews = current->reviews; //assigns the reviews linked list from the current node to the reviews field of the new node. 
				aNode->next = NULL; //it is the last node in the list

				//add new node to the end of the list
				if (isEmpty()) { //if list is empty it is set as both the front and last 
					front = aNode;
					last = aNode;
				}
				else { //else it is added to the end
					last->next = aNode;
					last = aNode;
				}

				printf("Review has been added successfully for book %s!\n", bookId);
			}

			current = current->next; //move on to the next node
		}

		printf("ERROR - Book with an identifier of %s has not found\n", bookId);

	}
	enter();
}


void viewReviews() {

	printf("\t\tVIEWING REVIEWS FOR A BOOK\n\n");

	struct LinearNode* current = front;
	bool found = false;

	// Get book ID from user
	char bookId[10];
	printf("Enter the book identifier: ");
	scanf(" %[^\n]", bookId);

	while (!validateIdFormat(bookId)) { //validating the id format is correct
		printf("Error - the format of the book identifier inputted is incorrect.\n\n");

		//Ask the user to input the book identifier
		printf("Enter the identifier of the book that is wished to be borrowed: ");
		scanf(" %[^\n]", bookId); //takes in the id
	}



	// Search for book with given ID in linked list
	
	while (!found && current != NULL) {
		if (strcmp(bookId, current->element->identifier) == 0) {
			found = true;
			printf("Reviews for book %s:\n", bookId);
			if (current->element == NULL || current->element->rev == NULL) {
				printf("No reviews found for this book.\n");
			}
			else {
				struct review* currentReview = current->element->rev;
				while (currentReview != NULL) {
					printf("Review by %s:\n", currentReview->reviewerName);
					printf("%d stars\n", currentReview->reviewStars);
					printf("%s\n", currentReview->reviewContent);
					currentReview = currentReview->next;
				}
			}
			break;
		}
		current = current->next;
	}

	if(!found) {
		printf("ERROR - Book with identifier %s not found.\n", bookId);
	}

	enter();
}
