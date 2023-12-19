#include <stdio.h>
#include <stdlib.h>

FILE *fptr;
FILE *fptr2;
char myString[100];
/*void PrintFile(const char *Filepath){
         

        // Open a file in read mode
        fptr = fopen(Filepath, "r");
        // Store the content of the file

        while(fgets(myString, 100, fptr)){
        // Print the file content
        printf("%s", myString);
        }
        fclose(fptr);
}

void AppendFile(const char *OutputPath){
        
      //Open a file in append mode
      fptr2 =  fopen(OutputPath, "a");
      
      //Prints the last line in myString to the output file
      fprintf(fptr2, myString);

        //Close the file
        fclose(fptr2);
}
*/
int main()
{
   char sc_method[]={'NONE','FCFS','SJF','PS','RRS'};
   char mode[]={'ON', 'OFF'};

   char method_choice[] = "NONE";
   char mode_choice[] = "OFF";

      printf("CPU SCHEDULER SIMULATOR\n\n");
      printf("1  |  SCHEDULING METHOD (%s)\n",method_choice);
      printf("2  |  PREEMPTIVE MODE (%s)\n",mode_choice);
      printf("3  |  SHOW RESULT\n");
      printf("4  |  END PROGRAM\n\n");
      printf("OPTION >> ");




        exit(0);
}
