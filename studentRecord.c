#include <stdio.h>
#include <stdlib.h>


#define FILE_NAME "studentRecords.bin"

//create a student structure
typedef struct {
   int studentID;
   char studentName[50];
   char emailID[50];
   char courseID[5];
   char grade[2];
} Student;


FILE openFile(){

   //open a binary file that can be amended
   FILE *file = fopen(FILE_NAME, "ab");
   if (!file){
      printf("Error opening file!\n");
   }
   return *file;

 }

Student createRecord(){


   Student student;

   printf("\nEnter Student ID: ");
   scanf("%d", &student.studentID);
   
   //fgets(&student.studentID, stdin);
   printf("\nEnter Student Name: ");
   scanf(" %[^\n]", student.studentName);

   printf("\nEnter Student Email: ");
   scanf(" %[^\n]", student.emailID);
  

   printf("\nEnter Course ID: ");
   scanf("%s", &student.courseID);

   printf("\nEnter Grade: ");
   scanf("%s", &student.grade);

   return student;
   


}

void displayRecord(){

   Student student;
   //open file in read binary
   FILE *file = openFile();

   printf("\n%-10s %-20s %-30s %-10s %-5s\n", "ID", "Name", "Email", "Course", "Grade");
   printf("--------------------------------------------------------------------------------");
   while (fread(&student, sizeof(Student), 1, file)){
      printf("\n%-10d %-20s %-30s %-10s %-5s\n", student.studentID, student.studentName, student.emailID, student.courseID, student.grade);
   
   }
   fclose(file);
}

void searchRecord(){

   int searchID;
   Student student;
   int recordFound = 0;

 //  FILE *file = fopen(FILE_NAME, "rb");
   FILE *file = openFile();


   printf("Enter Student ID to search:  ");
   scanf("%d", &searchID);

   while (fread(&student, sizeof(Student), 1, file)){
      if (student.studentID == searchID){
        printf("\n%-10d %-20s %-30s %-10s %-5s\n", student.studentID, student.studentName, student.emailID, student.courseID, student.grade);
	recordFound = 1;
	break;
      }
   }

   if (recordFound == 0){
      printf("\nNo record found with Student ID %d.\n", searchID);
   
   }

   fclose(file);
}

void editRecord(){
   
   int editID;
   Student student;
   int found = 0;

   FILE *file = fopen(FILE_NAME, "rb");
   FILE *tempFile = fopen("temp.bin", "wb");

   printf("Enter Student ID to edit: ");
   scanf("%d", &editID);


   while (fread(&student, sizeof(Student), 1, file)){
      if (student.studentID == editID){
         found = 1;
      }else{
         fwrite(&student, sizeof(Student), 1, tempFile);
      }
   
   }

   if (found == 1){
      remove(FILE_NAME);
      rename("temp.bin");
   }
	
   printf("\nThis is where you edit the record\n");
}

void deleteRecord(){
   
   int deleteID;
   Student student;
   int found = 0;

   FILE *file = fopen(FILE_NAME, "rb");
   FILE *tempFile = fopen("temp.bin", "wb");

   printf("Enter Student ID to delete: ");
   scanf("%d", &deleteID);

   while (fread(&student, sizeof(Student), 1, file)){
      if (student.studentID == deleteID){
         printf("Record with Student ID %d deleted.\n", deleteID);
	 found = 1;
      } else{
         fwrite(&student, sizeof(Student), 1, tempFile);
      }
   }

   if (found == 1){
      remove(FILE_NAME);
      rename("temp.bin", FILE_NAME);
   } else {
      printf("No record found with Student ID %d.\n");
      remove("temp.bin");
   }
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
