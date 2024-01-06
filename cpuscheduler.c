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

int t;
int linecnt=0;

typedef struct list {
    char *string;
    struct list *next;
}LIST;

typedef struct bur_list {
    int pid;
    int bur;
    int arr;
    int prior;
    struct bur_list *next;
}BUR_LIST;

char method_choice[] = "NONE";
char mode_choice[] = "OFF";



void split_arr(LIST *current){

      // Returns first token 
      token = strtok(current->string, ":"); 

      size=atoi(token);
      int signal[size];
      t=0;

      // Keep reading tokens while one of the delimiters still present in token. 
      while (token != NULL) 
      { 
         token = strtok(NULL, ":"); 
         if(token !=NULL){
         signal[t]=atoi(token);
         t=t+1;
         }
      } 

      //save the Burst, ArrivalTime and Priority to variables
      bur = size;
      arr = signal[0];
      prior = signal[1];

}

void moveToFront(struct bur_list** head_ref) 
{ 
    /* If linked list is empty, or it contains only one 
      node, then nothing needs to be done, simply return */
    if (*head_ref == NULL || (*head_ref)->next == NULL) 
        return; 
  
    /* Initialize second last and last pointers */
    struct bur_list* secLast = NULL; 
    struct bur_list* last = *head_ref; 
  
    /*After this loop secLast contains address of second 
    last node and last contains address of last node in 
    Linked List */
    while (last->next != NULL) { 
        secLast = last; 
        last = last->next; 
    } 
  
    /* Set the next of second last as NULL */
    secLast->next = NULL; 
  
    /* Set next of last as head node */
    last->next = *head_ref; 
  
    /* Change the head pointer to point to last node now */
    *head_ref = last; 
} 

int bubbleSortbur(struct bur_list** head, int linecnt)
{
    struct bur_list** h;
    int i, j, swapped;
 
    //Performing bubble Sort to arrange linked list from smallest to biggest  
    for (i = 0; i <= linecnt; i++) {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < linecnt - i - 1; j++) {
 
            struct bur_list* p1 = *h;
            struct bur_list* p2 = p1->next;
 
            if (p1->bur > p2->bur) {
 
               struct bur_list* tmp = p2->next;
               p2->next = p1;
               p1->next = tmp;
               *h = p2;
               swapped = 1;
            }
 
            h = &(*h)->next;
        }
 
        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
}

int bubbleSortarr(struct bur_list** head, int linecnt)
{
    struct bur_list** h;
    int i, j, swapped;
 
    //Performing bubble Sort to arrange linked list from smallest to biggest  
    for (i = 0; i <= linecnt; i++) {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < linecnt - i - 1; j++) {
 
            struct bur_list* p1 = *h;
            struct bur_list* p2 = p1->next;
 
            if (p1->arr > p2->arr) {
 
               struct bur_list* tmp = p2->next;
               p2->next = p1;
               p1->next = tmp;
               *h = p2;
               swapped = 1;
            }
 
            h = &(*h)->next;
        }
 
        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
}

int bubbleSortpid(struct bur_list** head, int linecnt)
{
    struct bur_list** h;
    int i, j, swapped;
 
    //Performing bubble Sort to arrange linked list from smallest to biggest  
    for (i = 0; i <= linecnt; i++) {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < linecnt - i - 1; j++) {
 
            struct bur_list* p1 = *h;
            struct bur_list* p2 = p1->next;
 
            if (p1->pid > p2->pid) {
 
               struct bur_list* tmp = p2->next;
               p2->next = p1;
               p1->next = tmp;
               *h = p2;
               swapped = 1;
            }
 
            h = &(*h)->next;
        }
 
        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
}


void FCFS_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath){
   int wait_time = 0;
   int bur_wait = 0;
   float total_wait_time = 0.0;
   float avg_wait_time = 0.0;
   int p_id=0;

   out_fptr =  fopen(OutputPath, "a");

   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for FCFS
      
      printf("Scheduling Method: First Come First Serve - Non Preemptive\n");
      fprintf(out_fptr, "\nScheduling Method: First Come First Serve - Non Preemptive\n");

      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");

      //First sorting by PID to rearrange the list to it's original form
      bubbleSortpid(&head, linecnt);

      //Then sorting by arrival time to always protect the accuracy of the simulator
      bubbleSortarr(&head,linecnt);

    //performing FCFS on each process
      for(current = head; current ; current=current->next){
         wait_time = bur_wait + wait_time; //Calculating the wait time for current process

         printf("\nP%d: %d ms", p_id+1,wait_time); //Printing the process names(p1, p2, p3) with wait times
         fprintf(out_fptr, "\nP%d: %d ms", p_id+1,wait_time);


         total_wait_time = total_wait_time + wait_time;

         //printf("\n%d | %d | %d", bur,arr,prior);
         bur_wait = current->bur; //setting bur_wait to hold value of current process to calculate wait time of next process
         p_id++;
      }

      avg_wait_time = total_wait_time/p_id;
      printf("\nAverage Wait Time: %.2f ms\n", avg_wait_time);
      fprintf(out_fptr, "\nAverage Wait Time: %.2f ms\n", avg_wait_time);
      fclose(out_fptr);

   } else{
      //Run code for preemptive mode for FCFS
      printf("First Come First Serve does not support Preemptive mode.\n");
   }
}


void SJF_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath){
   int p_id = 0;
   int p_count=0;
   int wait_time = 0;
   int pwait_time = 0;
   int arr_wait = 0;
   int bur_wait = 0;
   float total_wait_time = 0.0;
   float avg_wait_time = 0.0;
   out_fptr =  fopen(OutputPath, "a");

   if (strcmp(mode_choice, "OFF") == 0){

      printf("Scheduling Method: Shortest Job First - Non Preemptive\n");
      fprintf(out_fptr, "\nScheduling Method: Shortest Job First - Non Preemptive\n");

      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");
      //Run code for none preemptive mode for SJF

      //perform sorting operation
      bubbleSortpid(&head, linecnt);

      bubbleSortbur(&head, linecnt);
      printf("\n");

      //After sorting from lowest burst to highest burst
      for(current = head; current ; current=current->next){
      
      //To move the exception burst at arrival time 0 to the start of the list
      if(current->arr == 0){
         moveToFront(&head);
      }
      }

      //After Arrival Condition met
      for(current = head; current ; current=current->next){
      
      //Calculating wait times      
      wait_time = (bur_wait + wait_time); //Calculating the wait time for current process
      
      pwait_time = wait_time - current->arr; //Calculating the wait time with respect to the arrival time

      printf("\nP%d: %d ms", current->pid+1,pwait_time); //Printing the process names with wait times
      fprintf(out_fptr, "\nP%d: %d ms", current->pid+1,pwait_time);

      total_wait_time = total_wait_time + pwait_time;

      bur_wait = current->bur; //setting bur_wait to hold value of current process to calculate wait time of next process
      p_count++; //counting the number of processes
      }

      avg_wait_time = total_wait_time/p_count; 
      printf("\nAverage Wait Time: %.2f ms\n", avg_wait_time);
      fprintf(out_fptr, "\nAverage Wait Time: %.2f ms\n", avg_wait_time);

      printf("\nShortest Job First Non Preemptive Code segment");
      fclose(out_fptr);
   } else{
      //Run code for preemptive mode for SJF
      printf("Shortest Job First Preemptive Code segment");
   }
   }

void PS_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath){
   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for PS
      printf("Priority scheduling Non Preemptive Code segment");
   } else{
      //Run code for preemptive mode for PS
      printf("Priority scheduling Preemptive Code segment");
   }
}

void RRS_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath, int time_quan){
   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for RRS
      printf("Round Robin scheduling Non Preemptive Code segment");
   } else{
      //Run code for preemptive mode for RRS
      printf("Round Robin scheduling Preemptive Code segment");
   }
}

void menu(BUR_LIST *current, BUR_LIST *head, const char *OutPath){
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
               menu(current, head, OutPath);                                   //rerunning the menu so the user can continue execution of the program
               break;
            case 2:
               strcpy(method_choice,sc_method[1]);               
               printf("\nFirst come first serve was selected\n\n");
               menu(current, head, OutPath);
               break;
            case 3:
               strcpy(method_choice,sc_method[2]);                  
               printf("\nShortest job first was selected\n\n");
               menu(current, head, OutPath);
               break;
            case 4:
               strcpy(method_choice,sc_method[3]);
               printf("\nPriority scheduling method was selected\n\n");
               menu(current, head, OutPath);
               break;
            case 5:
               printf("Please enter the time quantum: ");
               scanf("%d", &time_quan);
               strcpy(method_choice,sc_method[4]);
               printf("\nRound robin scheduling was selected with time quantum as %d\n",time_quan);
               menu(current, head, OutPath);
               break;
            
            default:
               printf("Please put in the correct option");
               printf("\n");
               exit(1);
         }
      } else if(menu_option == 2){
         printf("\nPREEMPTIVE MODE\n\n");
         printf("1  |  OFF\n");
         printf("2  |  ON\n\n");
         printf("OPTION >> ");
         scanf("%d", &mode_option);

         if(mode_option == 1){            
               strcpy(mode_choice,mode[0]);
               printf("\nPreemptive mode is turned OFF\n\n");
               menu(current, head, OutPath);               
         } else if(mode_option == 2){            
               strcpy(mode_choice,mode[1]);
               printf("\nPreemptive mode is turned ON\n\n");
               menu(current, head, OutPath);
               
         } else{
               printf("Please put in the correct option");
               printf("\n");
               exit(1);
            }
         } else if(menu_option == 3){ //if show result is selected

            //Check which scheduling method and preemptive mode was selected
            if(strcmp(method_choice, "NONE") == 0){ //if no scheduling mode was selected
               printf("Please select a scheduling method before showing result\n");
               menu(current, head, OutPath);
            } else if(strcmp(method_choice, "FCFS") == 0){
                  FCFS_sch(current, head, OutPath);                  
            } else if(strcmp(method_choice, "SJF") == 0){
                  SJF_sch(current, head, OutPath);
            } else if(strcmp(method_choice, "PS") == 0){
                  PS_sch(current, head, OutPath);
            } else if(strcmp(method_choice, "RRS") == 0){
                  RRS_sch(current, head, OutPath, time_quan);
            } else{
                  printf("Error while creating Scheduling method");
            }
            menu(current, head, OutPath);

      } else if(menu_option == 4){
            printf("Do you want to end the program? (y/n): ");
            char exit_option;
            
            scanf(" %c", &exit_option);  
            if(exit_option == 'y' || exit_option == 'Y') {
               //Print the content of Output.txt to the screen here
               printf("\nProgram ended\n");
               exit(1);
            } else if (exit_option == 'n' || exit_option == 'N'){
               menu(current, head, OutPath);
            } else{
               printf("\nPlease input the correct option\n");
               menu(current, head, OutPath);
            }
      } else{
            fprintf(stderr, "Please select the correct option\n");
            exit(1);
         
      }
}
int main(int argc, char *argv[]) 
//argc is the number of arguments, 1 by default if no arguments are passed
//argv is a pointer to an array of strings
{

   LIST *current1, *head1;
   head1 = current1 = NULL;
   char *InputPath; //String to hold the Input file argument from command line
   char *OutputPath; //String to hold the Outut file argument from command line
   int opt;

   if (argc > 1){
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

   // Open a file in read mode
   inp_fptr = fopen(InputPath, "r");

   while(fgets(myString, sizeof(myString), inp_fptr)){ //Loop through the input file
       LIST *node = malloc(sizeof(LIST));
        node->string = strdup(myString);//note : strdup is not standard function
        node->next =NULL;
        if(head1 == NULL){
            current1 = head1 = node;
        } else {
            current1 = current1->next = node;
        }
        linecnt++;
    }
   fclose(inp_fptr);

   //initializing current and head for second Linked List
   BUR_LIST *current, *head;
   head = current = NULL;
   int p_id=0;

   //Looping through each node of the original linked list to split and save the integer values to a new linked list
   for(current1 = head1; current1 ; current1=current1->next){ 
         split_arr(current1);
         
         BUR_LIST *node = malloc(sizeof(BUR_LIST));
         node->bur = bur;
         node->arr = arr;
         node->prior = prior;
         node->pid = p_id;

         node->next =NULL;
        if(head == NULL){
            current = head = node;
        } else {
            current = current->next = node;
        }
      p_id++;
      }

   
   menu(current,head,OutputPath);  //run the menu using the InputPath and OutputPath gotten as argument from user
   } else{
      fprintf(stderr, "Please input the arguments needed to run this program\n");
      exit(EXIT_FAILURE);
   }
   exit(0);
}

