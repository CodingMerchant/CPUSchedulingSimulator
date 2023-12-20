#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *inp_fptr;
FILE *out_fptr;
char myString[100];
char *sc_method[]={"NONE","FCFS","SJF","PS","RRS"};
char *mode[]={"OFF", "ON"};
int option_choice;
int sch_choice;
int mode_option;
int time_quan;

char method_choice[] = "NONE";
char mode_choice[] = "OFF";
/*void PrintFile(const char *Filepath){      
        // Open a file in read mode
        inp_fptr = fopen(Filepath, "r");
        // Store the content of the file

        while(fgets(myString, 100, inp_fptr)){
        // Print the file content
        printf("%s", myString);
        }
        fclose(inp_fptr);
}

void AppendFile(const char *OutputPath){
        
      //Open a file in append mode
      out_fptr =  fopen(OutputPath, "a");
      
      //Prints the last line in myString to the output file
      fprintf(out_fptr, myString);

        //Close the file
        fclose(out_fptr);
}
*/

void menu(){
   printf("\nCPU SCHEDULER SIMULATOR\n\n");
      printf("1  |  SCHEDULING METHOD (%s)\n",method_choice);
      printf("2  |  PREEMPTIVE MODE (%s)\n",mode_choice);
      printf("3  |  SHOW RESULT\n");
      printf("4  |  END PROGRAM\n\n");
      printf("OPTION >> ");
      scanf("%d", &option_choice);     //getting the option as an integer from the user

      switch(option_choice){
         case 1:
            printf("\nSCHEDULING METHOD\n");
            printf("----Please select what scheduling method you wish to implement----\n\n");
            printf("1  |  NONE\n");
            printf("2  |  First Come First Serve\n");
            printf("3  |  Shortest Job First\n");
            printf("4  |  Priority Scheduling\n");
            printf("5  |  Round Robin Scheduling\n\n");
            printf("OPTION >> ");
            scanf("%d", &sch_choice);     

            switch(sch_choice){
               case 1:
                  strcpy(method_choice,sc_method[0]);       //updating the value of method_choice to the selected choice of the user
                  printf("%s", method_choice);
                  printf("\nNo scheduling method was selected\n\n");
                  menu();                                   //rerunning the menu so the user can continue execution of the program
                  break;

               case 2:
                  strcpy(method_choice,sc_method[1]);
                  printf("%s", method_choice);
                  printf("\nFirst come first serve was selected\n\n");
                  menu();
                  break;

               case 3:
                  strcpy(method_choice,sc_method[2]);
                  printf("%s", method_choice);
                  printf("\nShortest job first was selected\n\n");
                  menu();
                  break;

               case 4:
                  strcpy(method_choice,sc_method[3]);
                  printf("%s", method_choice);
                  printf("\nPriority scheduling method was selected\n\n");
                  menu();
                  break;

               case 5:
                  printf("Please enter the time quantum: ");
                  scanf("%d", &time_quan);
                  strcpy(method_choice,sc_method[4]);
                  printf("%s", method_choice);
                  printf("\nRound robin scheduling was selected with time quantum as %d\n",time_quan);
                  menu();
                  break;

               default:
                  printf("Please select the correct option");
                  printf("\n");
            }
            break;

         case 2: 
            printf("\nPREEMPTIVE MODE\n\n");
            printf("1  |  OFF\n");
            printf("2  |  ON\n\n");
            printf("OPTION >> ");
            scanf("%d", &mode_option);

            switch (mode_option){
               case 1:
                  strcpy(mode_choice,mode[0]);
                  printf("%s", mode_choice);
                  printf("\nPreemptive mode is turned OFF\n\n");
                  menu();
                  break;

               case 2:
                  strcpy(mode_choice,mode[1]);
                  printf("%s", mode_choice);
                  printf("\nPreemptive mode is turned ON\n\n");
                  menu();
                  break;

               default:
                  printf("Please put in the correct option");
                  printf("\n");
            }
            break;

         case 3:
            printf("Show result was selected");
            printf("\n");
            menu();
            break;

         case 4:
            printf("\nProgram ended\n");
            exit(0);
            break;

            default:
            printf("Please select the correct option");
            printf("\n");
      }

}
int main()
{
   menu();

   exit(0);
}
