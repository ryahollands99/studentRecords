#include <stdio.h>

#define FILE_NAME "studentRecords.bin"

typedef struct {
   int studentID;
   char studentName[10];
   char emailID[50];
   char courseID[5];
   char grade[2];
} Student;


void createFile(){

   Student student;
   FILE *file = fopen(FILE_NAME, "ab");

   printf("\nEnter Student ID: ");
   scanf("%d", &student.studentID);
   
   printf("\nEnter Student Name: ");
   scanf(" %s ", &student.studentID);

   printf("\nEnter Student Email: ");
   scanf("%s", &student.emailID);

   printf("\nEnter Course ID: ");
   scanf("%s", &student.courseID);

   printf("\nEnter Grade: ");
   scanf("%s", &student.grade);

   fwrite(&student, sizeof(Student), 1, file);
   fclose(file);
}

void displayRecord(){
   printf("\nThis is where you display the file\n");
}

void searchRecord(){
   printf("\nThis is where you search for records\n");
}

void editRecord(){
   printf("\nThis is where you edit the record\n");
}

void deleteRecord(){
   printf("\nThis is where you delete a record\n");
}

int main(){

   int choice = 1;

   printf("Main Menu\n");
   printf("1. Create the Binary File\n");
   printf("2. Display the contents of the file\n");
   printf("3. Seek a specific record\n");
   printf("4. Update the contents of a record\n");
   printf("5. Delete a record for the specific name\n");
   printf("6. Exit\n");

   
   while (choice != 0){
      printf("\nPlease Enter your choice .... ");
      scanf("%d", &choice);

      switch (choice){ 
         case 1:
            createFile();
	    break;
         case 2:
	    displayRecord();
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
	    choice = 0;
	    break;
      }
   }



   return 0;

}
