/*
 *Name: Ryan Hollands
 * Student ID: T00605613
 * Class: Comp 2131
 * Assignment: 2
 * */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "studentRecords.bin"

//design the student record structure
typedef struct {
   int studentID;
   char studentName[50];
   char emailID[50];
   char courseID[5];
   char grade[4];
} Student;

// Helper function to open a file with error checking
FILE* openFile(const char* filename, const char* mode){
  
   FILE* file = fopen(filename, mode);
  
   //Check if the file opened, if not then print error
   if (!file){
      printf("Error opening file %s!\n", filename);
      exit(1);
   }
   return file;
}

//Helper function to close a file
void closeFile(FILE* file){
   fclose(file);
}


//accepts input from the user and write the user input into a binary file
void addRecord(FILE *file){

  
   Student student;

   printf("\nEnter Student ID: ");
   scanf("%d", &student.studentID);
   
   printf("\nEnter Student Name: ");
   scanf(" %[^\n]", student.studentName); //reads name with spaces

   printf("\nEnter Student Email: ");
   scanf("%s", student.emailID);

   printf("\nEnter Course ID: ");
   scanf("%4s", student.courseID);

   printf("\nEnter Grade: ");
   scanf(" %3s", student.grade);

   //write to the binary file the new student record
   fwrite(&student, sizeof(Student), 1, file);
}


//creates the file by calling the openFile helper and the addRecord function
void createFile(){
   Student student;

   FILE *file = openFile(FILE_NAME, "ab");

   addRecord(file);
   closeFile(file);

}


//displays each individual record
void displayStudentRecord(Student student){
   printf("\t%-10d %-20s %-30s %-10s %-5s\n", student.studentID, student.studentName, student.emailID, student.courseID, student.grade);
}


//Read from the binary file and display the contents of the file
void displayFile(){
   Student student;
   FILE *file = openFile(FILE_NAME, "rb"); // open file in read binary mode
 
   //create the header  
   printf("\n\t%-10s %-20s %-30s %-10s %-5s\n", "ID", "Name", "Email", "Course ID", "Grade");
   
   //print each student's record
   while (fread(&student, sizeof(Student), 1, file)){
      displayStudentRecord(student);
   }

   closeFile(file);

}


//Seek and list a specific record
void searchRecord(){

   int foundID; //variable to hold Student ID the user wants to search for
   Student student;


   FILE *file = openFile(FILE_NAME, "rb"); 

   //Get the student ID to search the file for
   printf("Enter student ID to find: ");
   scanf("%d", &foundID);

   //check each student record if the student ID matches the given ID
   while (fread(&student, sizeof(Student), 1, file)){
      //if the student ID in the record matches, print the student record
      if(student.studentID == foundID){
         printf("Record with Student ID %d found.\n", foundID);
	 displayStudentRecord(student);
	 break;
      }	
   }

   closeFile(file);

}

//Updates the content of a specfic file
void editRecord(){

   int editID; //variable to hold input from user
   Student student;
   int found = 0; //flag to indicate if record is found

   FILE *file = openFile(FILE_NAME, "rb"); 
   FILE *tempFile = openFile("temp.bin", "wb"); //temporary file to store student records as they are searched

   //Get the Student ID to searh the file for
   printf("\nEnter the Student ID to edit: \n");
   scanf("%d", &editID);


   //search each student record for the given Student ID
   while (fread(&student, sizeof(Student), 1, file)){
      /*if the student ID matches the ID inputted, then display the record and call the addRecord to enter 
        the new updated record into the temporary file  */
      if (student.studentID == editID){
         found = 1;
	 printf("Record with Student ID %d found: \n", editID);
	 displayStudentRecord(student);
         addRecord(tempFile);	 
      }else{
         //if the Student ID does not match the ID inputted, then write the student record to the temporary file
         fwrite(&student, sizeof(Student), 1, tempFile);
      }

   }

   closeFile(file);
   closeFile(tempFile);

   //if the student record was found, then delete the binary file and rename the temporary file with the file name
   if (found == 1){
      remove(FILE_NAME);
      rename("temp.bin", FILE_NAME);
   
   }else{
     //delete record if no student record was found with the inputted Student ID
      remove("temp.bin");
      printf("Record with Student ID %d not found.\n", editID);
   }

}

//deletes a student record for a specific name
void deleteRecord(){
   char deleteName[50];
   Student student;
   int found = 0; //flag to indicate if record is found

   FILE *file = openFile(FILE_NAME, "rb");
   FILE *tempFile = openFile("temp.bin", "wb"); // temporary file to store the student records as they are searched
   
   //get Student Name to search for
   printf("Enter Name to delete: ");
   scanf(" %[^\n]", &deleteName); //reads name with space

   //search each student record for the Student Name
   while (fread(&student, sizeof(Student), 1, file)){
      //if student name is found, then print it is found and change flag to 1;  
      if (strcmp(student.studentName,deleteName) == 0){
        printf("Record with Student Name %s deleted.\n", deleteName);
	found = 1;
      } else {
         fwrite(&student, sizeof(Student), 1, tempFile); //write non-matching Student record to temporary file

      }
   }

   closeFile(file);
   closeFile(tempFile);

   //Check if the student record is found
   if(found == 1){
      remove(FILE_NAME); //remove original file
      rename("temp.bin", FILE_NAME); //rename temporary file to original file
   } else {
      printf("No record found with Student Name %s.\n", &deleteName);
      remove("temp.bin"); //remove temp file if no record is deleted;
   }
}

int main(){

   char choice;

   //User Menu	
   printf("Main Menu\n");
   printf("1. Create the Binary File\n");
   printf("2. Display the contents of the file\n");
   printf("3. Seek a specific record\n");
   printf("4. Update the contents of a record\n");
   printf("5. Delete a record for the specific name\n");
   printf("6. Exit\n");

   //continue looping until user exits
   while (choice != '0'){
      
      printf("\nPlease Enter your choice .... ");
      scanf(" %c", &choice);

      //check if the input is a digit and not a letter
      if (isdigit(choice)){
         int menuChoice = choice - '0'; // convert from character to integer
	 
	 //action the user's choice
         switch (menuChoice){ 
            case 1:
               createFile();
	       break;
            case 2:
	       displayFile();
	       break;
            case 3:
	       searchRecord();
	       break;
	    case 4:
	       editRecord();
	       break;
	    case 5:
	       deleteRecord();
	       break;
	    case 6:
	       choice = '0'; //break the while loop
	       break;
	    default: 
	       printf("Choice unknown. Program will exit"); //response to invalid menu selection
	       break;
	  
        }
      }
 }


   return 0;

}
