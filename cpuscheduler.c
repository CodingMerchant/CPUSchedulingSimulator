#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

FILE *inp_fptr;
FILE *out_fptr;
char myString[10];
char *sc_method[]={"NONE","FCFS","SJF","PS","RRS"};      //initiating a string array to hold scheduling methods
char *mode[]={"OFF", "ON"};
char *inp_data;
char *token;
int menu_option;
int sch_choice;
int mode_option;
int time_quan;
int size;
int bur;
int arr;
int prior;
int p_id = 0;
int wait_time = 0;
float total_wait_time = 0.0;
float avg_wait_time = 0.0;
int bur_wait = 0;
int i;

char method_choice[] = "NONE";
char mode_choice[] = "OFF";

void split_arr(char *myString){
      // Returns first token 
      token = strtok(myString, ":"); 

      size=atoi(token);
      int signal[size];
      i=0;

      // Keep reading tokens while one of the delimiters still present in myString[]. 
      while (token != NULL) 
      { 
         token = strtok(NULL, ":"); 
         if(token !=NULL){
         signal[i]=atoi(token);
         i=i+1;
         }
      } 

      bur = size;
      arr = signal[0];
      prior = signal[1];

}

void FCFS_sch(const char *InputPath, const char *OutputPath){

   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for FCFS

      // Open a file in read mode
      inp_fptr = fopen(InputPath, "r");
      // Store the content of the file
      out_fptr =  fopen(OutputPath, "a");
      printf("Scheduling Method: First Come First Serve - Non Preemptive\n");
      fprintf(out_fptr, "\nScheduling Method: First Come First Serve - Non Preemptive\n");
      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");
      while(fgets(myString, 10, inp_fptr)){ //Loop through the input file
      // Print the file content
      split_arr(myString);
      arr=0; //Arrival time not needed
      prior=0; //Priority not needed

      wait_time = bur_wait + wait_time; //Calculating the wait time for current process

      printf("\nP%d: %d ms", p_id+1,wait_time); //Printing the process names(p1, p2, p3) with wait times
      fprintf(out_fptr, "\nP%d: %d ms", p_id+1,wait_time);


      total_wait_time = total_wait_time + wait_time;

      //printf("\n%d | %d | %d", bur,arr,prior);
      bur_wait = bur; //setting bur_wait to hold value of current process to calculate wait time of next process
      p_id++;
      //fprintf(out_fptr,"%s", myString);
      }

      avg_wait_time = total_wait_time/p_id;
      printf("\nAverage Wait Time: %.2f ms\n", avg_wait_time);
      fprintf(out_fptr, "\nAverage Wait Time: %.2f ms\n", avg_wait_time);

      //fprintf(out_fptr, "\n");
      fclose(inp_fptr);
      fclose(out_fptr);
   } else{
      //Run code for preemptive mode for FCFS
      printf("First Come First Serve does not support Preemptive mode.\n");
   }
}

void SJF_sch(const char *InputPath, const char *OutputPath){
   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for SJF
      printf("Shortest Job First Non Preemptive Code segment");
   } else{
      //Run code for preemptive mode for SJF
      printf("Shortest Job First Preemptive Code segment");
   }
}

void PS_sch(const char *InputPath, const char *OutputPath){
   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for PS
      printf("Priority scheduling Non Preemptive Code segment");
   } else{
      //Run code for preemptive mode for PS
      printf("Priority scheduling Preemptive Code segment");
   }
}

void RRS_sch(const char *InputPath, const char *OutputPath, int time_quan){
   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for RRS
      printf("Round Robin scheduling Non Preemptive Code segment");
   } else{
      //Run code for preemptive mode for RRS
      printf("Round Robin scheduling Preemptive Code segment");
   }
}


void PrintFile(const char *InputPath, const char *OutputPath){      
        // Open a file in read mode
        inp_fptr = fopen(InputPath, "r");
        // Store the content of the file
        out_fptr =  fopen(OutputPath, "a");

        while(fgets(myString, 10, inp_fptr)){
        // Print the file content
        printf("%s", myString);
      
        fprintf(out_fptr,"%s", myString);
   
        }
        fprintf(out_fptr, "\n");

        fclose(inp_fptr);
        fclose(out_fptr);
}

void menu(const char *InpPath, const char *OutPath){
   printf("\nCPU SCHEDULER SIMULATOR\n\n");
   printf("1  |  SCHEDULING METHOD (%s)\n",method_choice);
   printf("2  |  PREEMPTIVE MODE (%s)\n",mode_choice);
   printf("3  |  SHOW RESULT\n");
   printf("4  |  END PROGRAM\n\n");
   printf("OPTION >> ");
   scanf("%d", &menu_option);     //getting the menu option as an integer from the user

   if(menu_option == 1){
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
               printf("\nNo scheduling method was selected\n\n");
               menu(InpPath,OutPath);                                   //rerunning the menu so the user can continue execution of the program
               break;
            case 2:
               strcpy(method_choice,sc_method[1]);               
               printf("\nFirst come first serve was selected\n\n");
               menu(InpPath,OutPath);
               break;
            case 3:
               strcpy(method_choice,sc_method[2]);                  
               printf("\nShortest job first was selected\n\n");
               menu(InpPath,OutPath);
               break;
            case 4:
               strcpy(method_choice,sc_method[3]);
               printf("\nPriority scheduling method was selected\n\n");
               menu(InpPath,OutPath);
               break;
            case 5:
               printf("Please enter the time quantum: ");
               scanf("%d", &time_quan);
               strcpy(method_choice,sc_method[4]);
               printf("\nRound robin scheduling was selected with time quantum as %d\n",time_quan);
               menu(InpPath,OutPath);
               break;
            
            default:
               printf("Please put in the correct option");
               printf("\n");
               exit(0);
         }
      } else if(menu_option == 2){
         printf("\nPREEMPTIVE MODE\n\n");
         printf("1  |  OFF\n");
         printf("2  |  ON\n\n");
         printf("OPTION >> ");
         scanf("%d", &mode_option);
         if(mode_option == 1){
            //case 1:
               strcpy(mode_choice,mode[0]);
               printf("\nPreemptive mode is turned OFF\n\n");
               menu(InpPath,OutPath);
               //break;
         } else if(mode_option == 2){
            //case 2:
               strcpy(mode_choice,mode[1]);
               printf("\nPreemptive mode is turned ON\n\n");
               menu(InpPath,OutPath);
               //break;
         } else{
            //default:
               printf("Please put in the correct option");
               printf("\n");
               exit(0);
            }
         } else if(menu_option == 3){ //if show result is selected

            //Check which scheduling method and preemptive mode was selected
            if(strcmp(method_choice, "NONE") == 0){ //if no scheduling mode was selected
               printf("Please select a scheduling method before showing result\n");
               menu(InpPath,OutPath);
            } else if(strcmp(method_choice, "FCFS") == 0){
                  FCFS_sch(InpPath, OutPath);                  
            } else if(strcmp(method_choice, "SJF") == 0){
                  SJF_sch(InpPath, OutPath);
            } else if(strcmp(method_choice, "PS") == 0){
                  PS_sch(InpPath, OutPath);
            } else if(strcmp(method_choice, "RRS") == 0){
                  RRS_sch(InpPath, OutPath, time_quan);
            } else{
                  printf("Error while creating Scheduling method");
            }
            menu(InpPath,OutPath);

      } else if(menu_option == 4){
            printf("Do you want to end the program? (y/n): ");
            char exit_option;
            
            scanf(" %c", &exit_option);  
            if(exit_option == 'y' || exit_option == 'Y') {
               //Print the content of Output.txt to the screen here
               printf("\nProgram ended\n");
               exit(0);
            } else if (exit_option == 'n' || exit_option == 'N'){
               menu(InpPath,OutPath);
            } else{
               printf("\nPlease input the correct option\n");
               menu(InpPath,OutPath);
            }
      } else{
            printf("Please select the correct option");
            printf("\n");
            exit(0);
      }
}
int main(int argc, char *argv[]) 
//argc is the number of arguments, 1 by default if no arguments are passed
//argv is a pointer to an array of strings
{

   char *InputPath; //String to hold the Input file argument from command line
   char *OutputPath; //String to hold the Outut file argument from command line
   int opt;

   while ((opt = getopt(argc, argv, "fo:")) != -1) { //allowing f and o as options requiring arguments
        switch (opt) {
        case 'f':
            InputPath = argv[2]; // initializing the argument in front of -f as InputPath
            break;

        case 'o':
            OutputPath = argv[4]; // initializing the argument in front of -o as OutputPath
            break;

        default: // What to do when an unknown argument is used
            fprintf(stderr, "Please input the correct arguments\n");
            exit(EXIT_FAILURE);
        }
   }
   menu(InputPath,OutputPath);  //run the menu using the InputPath and OutputPath gotten as argument from user

   exit(0);
}

