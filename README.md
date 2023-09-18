# Library-Management

A library wishes to keep a record of the books that it has in stock. You need to create a system in C that displays a menu which allows the following options to be presented to the user:
  1. Adds a book into the library
  2. Borrow a book
  3. Return a book
  4. Delete a book
  5. View all books
  6. View a specific book
  7. Least and most popular book
  8. Leave and view reviews
  9. Exit the program
The program should check to see if file book.dat exists on your drive, a message should appear on the screen to indicate to the user that a database of books doesn’t exist and so the user will need to input the books
Books should be populated to a linked list and each book id should be validated and made sure it is unique

Assume that there is a maximum of 5 books in the library. An error message will appear if the list is full. Ensure that all book identifiers are unique and that the date of publication is not older than the year 2017

If the book is found and it’s not already borrowed by another customer, then the customer name is input and added to the book, also the status of the book is updated and the value storing the number of times the book has been taken out is updated by 1. If the book isn’t found or has already been borrowed then appropriate error messages should be displayed.

The identifier of the book and customer name are input. If the book is found and it has been borrowed by that customer then its status is updated accordingly otherwise appropriate error messages are displayed if the whole list has been travesered and an id is not found a message saying id is not in library is displayed.

To delete books user will need to indicate which book they wish to delete by inputting a book identifier. Note that only books older than 2010 can be deleted.
