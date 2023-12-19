#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
   char *sc_method[]={"NONE","FCFS","SJF","PS","RRS"};
   char *mode[]={"OFF", "ON"};
   int option_choice;
   int sch_choice;
   int mode_option;

   char method_choice[] = "NONE";
   char mode_choice[] = "OFF";

      printf("CPU SCHEDULER SIMULATOR\n\n");
      printf("1  |  SCHEDULING METHOD (%s)\n",method_choice);
      printf("2  |  PREEMPTIVE MODE (%s)\n",mode_choice);
      printf("3  |  SHOW RESULT\n");
      printf("4  |  END PROGRAM\n\n");
      printf("OPTION >> ");
      scanf("%d", &option_choice);

      switch(option_choice){
         case 1:
            printf("SCHEDULING METHOD\n\n");
            printf("1  |  NONE\n");
            printf("2  |  First Come First Serve\n");
            printf("3  |  Shortest Job First\n");
            printf("4  |  Priority Scheduling\n");
            printf("5  |  Round Robin Scheduling\n\n");
            printf("OPTION >> ");
            scanf("%d", &sch_choice);

            switch(sch_choice){
               case 1:
                  strcpy(method_choice,sc_method[0]);
                  printf("%s", method_choice);
                  break;

               case 2:
                  strcpy(method_choice,sc_method[1]);
                  printf("%s", method_choice);
                  break;

               case 3:
                  strcpy(method_choice,sc_method[2]);
                  printf("%s", method_choice);
                  break;

               case 4:
                  strcpy(method_choice,sc_method[3]);
                  printf("%s", method_choice);
                  break;

               case 5:
                  strcpy(method_choice,sc_method[4]);
                  printf("%s", method_choice);
                  break;

               default:
                  printf("Please select the correct option");
            }
            break;

         case 2: 
            printf("PREEMPTIVE MODE\n\n");
            printf("1  |  OFF\n");
            printf("2  |  ON\n\n");
            printf("OPTION >> ");
            scanf("%d", &mode_option);

            switch (mode_option){
               case 1:
                  strcpy(mode_choice,mode[0]);
                  printf("%s", mode_choice);
                  break;

               case 2:
                  strcpy(mode_choice,mode[1]);
                  printf("%s", mode_choice);
                  break;

               default:
                  printf("Please put in the correct option");
               break;
            
            }
            
            break;

         case 3:
            printf("Show result was selected");
            break;

         case 4:
            printf("End program was selected");
            break;

            default:
            printf("Please select the correct option");
            break;
      }




        exit(0);
}
