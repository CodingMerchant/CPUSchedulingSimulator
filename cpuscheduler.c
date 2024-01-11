#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

FILE *inp_fptr;
FILE *out_fptr;
char myString[100];

char method_choice[] = "NONE";
char mode_choice[] = "OFF";
int time_quan=0;
int bur;
int arr;
int prior;


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
    int rem_time;
    struct bur_list *next;
}BUR_LIST;

typedef struct temp_list {
    int pid;
    int bur;
    int arr;
    int prior;
    int rem_time;
    struct temp_list *next;
}TEMP_LIST;



void split_arr(LIST *current){

      char *token;
      int t;
      int size;
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


int bubbleSortarr(struct temp_list** head, int linecnt)
{
   struct temp_list** h;
    int i, j, swapped;
 
    //Performing bubble Sort to arrange linked list according to arrival time
    for (i = 0; i <= linecnt; i++) {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < linecnt - i - 1; j++) {
 
            struct temp_list* p1 = *h;
            struct temp_list* p2 = p1->next;
 
            if (p1->arr > p2->arr) { //Check if current arrival time is smaller than next
 
               struct temp_list* tmp = p2->next;
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

int bubbleSortprior(struct bur_list** head, int linecnt)
{
    struct bur_list** h;
    int i, j, swapped;
 
    //Performing bubble Sort to arrange linked list according to priority
    for (i = 0; i <= linecnt; i++) {
 
        h = head;
        swapped = 0;
        for (j = 0; j < linecnt - i - 1; j++) {
 
            struct bur_list* p1 = *h;
            struct bur_list* p2 = p1->next;
 
            if (p1->prior > p2->prior) {
 
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

void deleteListContent(TEMP_LIST *temphead) {
    TEMP_LIST *tempcurrent = temphead;
    TEMP_LIST *next;

    while (tempcurrent!= NULL) {
        next = tempcurrent->next;
        free(tempcurrent);
        tempcurrent = next;
    }

    // Set the head to NULL to indicate an empty list
    temphead = NULL;
}

   
void FCFS_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath){
   int wait_time = 0;
   int pwait_time = 0;
   int comp_time = 0;
   int turn_around_time = 0;
   float total_wait_time = 0.0;
   float avg_wait_time = 0.0;   
   int p_count=0;

   out_fptr =  fopen(OutputPath, "a");

   //Using Temporary list so main linked list data is preserved
      TEMP_LIST *tempcurrent, *temphead, *node;
          temphead = tempcurrent = NULL;
         int p_id = 0;

         for(current = head; current ; current=current->next){ 
         
         node = malloc(sizeof(TEMP_LIST));
         node->bur = current->bur;
         node->arr = current->arr;
         node->prior = current->prior;
         node->rem_time = current->rem_time;
         node->pid = p_id;

         node->next =NULL;
        if(temphead == NULL){
            tempcurrent = temphead = node;
        } else {
            tempcurrent = tempcurrent->next = node;
        }
        p_id++;
         }


   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for FCFS
      
      printf("\nScheduling Method: First Come First Serve - Non Preemptive\n");
      fprintf(out_fptr, "\nScheduling Method: First Come First Serve - Non Preemptive\n");

      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");

      
        //Sorting with respect to arrival time
        bubbleSortarr(&temphead,linecnt);

      //performing FCFS on each process
       tempcurrent = temphead;
        while (tempcurrent != NULL)
        {
            TEMP_LIST *arrivedJob = NULL;
            TEMP_LIST *tmp = tempcurrent;

            // Find the process that has arrived
            while (tmp != NULL)
            {
               if(tmp->arr <= comp_time){
                if (arrivedJob == NULL)
                {
                    arrivedJob = tmp;
                }
                
                }
                tmp = tmp->next;
            }

            if (arrivedJob != NULL)
            {
               //calculating process wait time
               comp_time = comp_time + arrivedJob->bur;
               turn_around_time = comp_time - arrivedJob->arr;
               pwait_time = turn_around_time - arrivedJob->bur;

                printf("\nP%d : %d ms", arrivedJob->pid+1, pwait_time);
                fprintf(out_fptr, "\nP%d : %d ms", arrivedJob->pid+1, pwait_time);
                total_wait_time += pwait_time;
                p_count++;

                // Remove the selected process from the list
                if (tempcurrent == arrivedJob)
                {
                    tempcurrent = tempcurrent->next;
                }
                else
                {
                    TEMP_LIST *prev = tempcurrent;
                    while (prev->next != arrivedJob)
                    {
                        prev = prev->next;
                    }
                    prev->next = arrivedJob->next;
                }
            }
            else
            {
                // No process has arrived yet, move to the next one
                comp_time = tempcurrent->arr;
            }
        }       

        avg_wait_time = total_wait_time / p_count;
        printf("\nAverage waiting time: %.2f ms\n", avg_wait_time);
        fprintf(out_fptr, "\nAverage waiting time: %.2f ms\n", avg_wait_time);
        fclose(out_fptr);
        deleteListContent(temphead);

   } else{
      //Run code for preemptive mode for FCFS
      
      printf("\nScheduling Method: First Come First Serve - Preemptive\n");
      fprintf(out_fptr, "\nScheduling Method: First Come First Serve - Preemptive\n");

      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");

      //Sorting with respect to arrival time
        bubbleSortarr(&temphead,linecnt);

      //performing FCFS on each process
       tempcurrent = temphead;
        while (tempcurrent != NULL)
        {
            TEMP_LIST *arrivedJob = NULL;
            TEMP_LIST *tmp = tempcurrent;

            // Find the process that has arrived
            while (tmp != NULL)
            {
               if(tmp->arr <= comp_time){
                if (arrivedJob == NULL)
                {
                    arrivedJob = tmp;
                }
                
                }
                tmp = tmp->next;
            }

            if (arrivedJob != NULL)
            {
               //calculating process wait time
               comp_time = comp_time + arrivedJob->bur;
               turn_around_time = comp_time - arrivedJob->arr;
               pwait_time = turn_around_time - arrivedJob->bur;

                printf("\nP%d : %d ms", arrivedJob->pid+1, pwait_time);
                fprintf(out_fptr, "\nP%d : %d ms", arrivedJob->pid+1, pwait_time);
                total_wait_time += pwait_time;
                p_count++;

                // Remove the selected process from the list
                if (tempcurrent == arrivedJob)
                {
                    tempcurrent = tempcurrent->next;
                }
                else
                {
                    TEMP_LIST *prev = tempcurrent;
                    while (prev->next != arrivedJob)
                    {
                        prev = prev->next;
                    }
                    prev->next = arrivedJob->next;
                }
            }
            else
            {
                // No process has arrived yet, move to the next one
                comp_time = tempcurrent->arr;
            }
        }       

        avg_wait_time = total_wait_time / p_count;
        printf("\nAverage waiting time: %.2f ms\n", avg_wait_time);
        fprintf(out_fptr, "\nAverage waiting time: %.2f ms\n", avg_wait_time);
        fclose(out_fptr);
        deleteListContent(temphead);

   }
}

void SJF_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath)
{
   int wait_time = 0;
   int pwait_time = 0;
   int comp_time = 0;
   int turn_around_time = 0;
   float total_wait_time = 0.0;
   float avg_wait_time = 0.0;   
   int p_count=0;

        out_fptr =  fopen(OutputPath, "a");
        TEMP_LIST *tempcurrent, *temphead, *node;
         temphead = tempcurrent = NULL;
         int p_id = 0;

         for(current = head; current ; current=current->next){ 
         
         node = malloc(sizeof(TEMP_LIST));
         node->bur = current->bur;
         node->arr = current->arr;
         node->prior = current->prior;
         node->rem_time = current->rem_time;
         node->pid = p_id;

         node->next =NULL;
        if(temphead == NULL){
            tempcurrent = temphead = node;
        } else {
            tempcurrent = tempcurrent->next = node;
        }
        p_id++;
         }


        if (strcmp(mode_choice, "OFF") == 0){

        //Sorting with respect to arrival time
        bubbleSortarr(&temphead,linecnt);
        
        printf("\nScheduling method: Shortest Job First. Non-Preemptive\n");
        printf("Process waiting times:");
        fprintf(out_fptr, "\nScheduling method: Shortest Job First. Non-Preemptive\n");
        fprintf(out_fptr, "Process waiting times:");
        
         tempcurrent = temphead;         
        while (tempcurrent != NULL)
        {
            TEMP_LIST *shortestJob = NULL;
            TEMP_LIST *tmp = tempcurrent;

            // Find the process with the shortest burst time that has arrived
            while (tmp != NULL)
            {
               if(tmp->arr <= comp_time){
                if (shortestJob == NULL || tmp->bur < shortestJob->bur)
                {
                    shortestJob = tmp;
                }
                }
                tmp = tmp->next;
            
            }

            if (shortestJob != NULL)
            {
               //calculating completion time
               comp_time = comp_time + shortestJob->bur;
               turn_around_time = comp_time - shortestJob->arr;
               pwait_time = turn_around_time - shortestJob->bur;

                printf("\nP%d : %d ms", shortestJob->pid+1, pwait_time);
                fprintf(out_fptr, "\nP%d : %d ms", shortestJob->pid+1, pwait_time);
                total_wait_time += pwait_time;
                p_count++;              

                // Remove the selected process from the list
                if (tempcurrent == shortestJob)
                {
                    tempcurrent = tempcurrent->next;
                }
                else
                {
                    TEMP_LIST *prev = tempcurrent;
                    while (prev->next != shortestJob)
                    {
                        prev = prev->next;
                    }
                    prev->next = shortestJob->next;
                }
            }
            else
            {
                // No process has arrived yet, move to the next one
                comp_time = tempcurrent->arr;
            }
        }

        avg_wait_time = total_wait_time / p_count;
        printf("\nAverage waiting time: %.2f ms\n", avg_wait_time);
        fprintf(out_fptr, "\nAverage waiting time: %.2f ms\n", avg_wait_time);

        deleteListContent(temphead);
        
   } else{
         printf("Shortest Job First Preemptive Code Segment");
   }
   fclose(out_fptr);
}

void PS_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath){
   int wait_time = 0;
   int pwait_time = 0;
   int comp_time = 0;
   int turn_around_time = 0;
   float total_wait_time = 0.0;
   float avg_wait_time = 0.0;   
   int p_count=0;

      out_fptr =  fopen(OutputPath, "a");
      TEMP_LIST *tempcurrent, *temphead, *node;
          temphead = tempcurrent = NULL;
         int p_id = 0;

         for(current = head; current ; current=current->next){ 
         
         node = malloc(sizeof(TEMP_LIST));
         node->bur = current->bur;
         node->arr = current->arr;
         node->prior = current->prior;
         node->rem_time = current->rem_time;
         node->pid = p_id;

         node->next =NULL;
        if(temphead == NULL){
            tempcurrent = temphead = node;
        } else {
            tempcurrent = tempcurrent->next = node;
        }
        p_id++;
         }

      if (strcmp(mode_choice, "OFF") == 0){
      printf("\nScheduling Method: Priority Scheduling - Non Preemptive\n");
      fprintf(out_fptr, "\nScheduling Method: Priority Scheduling - Non Preemptive\n");

      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");

      
        //Sorting with respect to arrival time
        bubbleSortarr(&temphead,linecnt);
        
        tempcurrent = temphead;
        while (tempcurrent != NULL)
        {
            TEMP_LIST *arrivedJob = NULL;
            TEMP_LIST *tmp = tempcurrent;

            // Find the process with the most priority time that has arrived
            while (tmp != NULL && tmp->arr <= comp_time)
            {
                if (arrivedJob == NULL || tmp->prior < arrivedJob->prior)
                {
                    arrivedJob = tmp;
                }
                tmp = tmp->next;
            }

            if (arrivedJob != NULL)
            {
               //calculating completion time
               comp_time = comp_time + arrivedJob->bur;
               turn_around_time = comp_time - arrivedJob->arr;
               pwait_time = turn_around_time - arrivedJob->bur;

                printf("\nP%d : %d ms", arrivedJob->pid+1, pwait_time);
                fprintf(out_fptr, "\nP%d : %d ms", arrivedJob->pid+1, pwait_time);
                total_wait_time = total_wait_time + pwait_time;
                p_count++;

                // Remove the selected process from the list
                if (tempcurrent == arrivedJob)
                {
                    tempcurrent = tempcurrent->next;
                }
                else
                {
                    TEMP_LIST *prev = tempcurrent;
                    while (prev->next != arrivedJob)
                    {
                        prev = prev->next;
                    }
                    prev->next = arrivedJob->next;
                }
            }
            else
            {
                // No process has arrived yet, move to the next one
                comp_time = tempcurrent->arr;
            }
        }
        

        avg_wait_time = total_wait_time / p_count;
        printf("\nAverage waiting time: %.2f ms\n", avg_wait_time);
        fprintf(out_fptr, "\nAverage waiting time: %.2f ms\n", avg_wait_time);
        deleteListContent(temphead);

   } else{
         printf("Priority Scheduling Preemptive Code Segment");

   }
   fclose(out_fptr);
}

void RRS_sch(BUR_LIST *current, BUR_LIST *head, const char *OutputPath){
   int wait_time = 0;
   int pwait_time = 0;
   int comp_time=0;
   int turn_around_time = 0;
   float total_wait_time = 0.0;
   float avg_wait_time = 0.0;
   int flag = 0;   
   int p_count=0;
   int rem_process=0;

   out_fptr =  fopen(OutputPath, "a");

   TEMP_LIST *tempcurrent, *temphead, *node;
          temphead = tempcurrent = NULL;
         int p_id = 0;

         for(current = head; current ; current=current->next){ 
         
         node = malloc(sizeof(TEMP_LIST));
         node->bur = current->bur;
         node->arr = current->arr;
         node->prior = current->prior;
         node->rem_time = current->rem_time;
         node->pid = p_id;

         node->next =NULL;
        if(temphead == NULL){
            tempcurrent = temphead = node;
        } else {
            tempcurrent = tempcurrent->next = node;
        }
        p_id++;
         }


   if (strcmp(mode_choice, "OFF") == 0){
      //Run code for none preemptive mode for RRS

      printf("\nScheduling Method: Round Robin Scheduling - NonPreemptive - Time Quantum = %d\n",time_quan);
      fprintf(out_fptr, "\nScheduling Method: Round Robin Scheduling - NonPreemptive - Time Quantum = %d\n",time_quan);

      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");

      //Then sorting by arrival time for Round Robin Scheduling
      
        //Sorting with respect to arrival time
        bubbleSortarr(&temphead,linecnt);

      //initializing number of remaining processes to be the current number of processes
      rem_process = linecnt;

         while(rem_process!=0){
         for(tempcurrent=temphead; tempcurrent; tempcurrent->next){
            
         if(tempcurrent->rem_time <= time_quan && tempcurrent->rem_time > 0){   //if the remaining time of current process is less than the time quantum and greater than 0
            comp_time +=tempcurrent->rem_time;
            tempcurrent->rem_time = 0;
            flag = 1;
         } else if(tempcurrent->rem_time > 0) { //if remaining time is only greater than 0 and still needs execution
            tempcurrent->rem_time -= time_quan;
            comp_time += time_quan;
         } 
         
         if(tempcurrent->rem_time == 0 && flag ==1){   //If process has truely ended
            rem_process--;
            turn_around_time = comp_time - tempcurrent->arr;
            pwait_time = turn_around_time - tempcurrent->bur; //Calculate process wait time

            printf("\nP%d : %d ms", tempcurrent->pid+1, pwait_time);
            fprintf(out_fptr, "\nP%d : %d ms", tempcurrent->pid+1, pwait_time);

            total_wait_time+= pwait_time;
            
            flag = 0;
            p_count++;
         }
         else{           
            tempcurrent = tempcurrent->next; 
         }
                
         }
         
      }

      avg_wait_time = total_wait_time / p_count;
      printf("\nAverage waiting time: %.2f ms\n", avg_wait_time);
      fprintf(out_fptr, "\nAverage waiting time: %.2f ms\n", avg_wait_time);
      deleteListContent(temphead);

   } else{
      //Run code for preemptive mode for RRS

      printf("\nScheduling Method: Round Robin Scheduling - Preemptive - Time Quantum = %d\n",time_quan);
      fprintf(out_fptr, "\nScheduling Method: Round Robin Scheduling - Preemptive - Time Quantum = %d\n",time_quan);

      printf("Process Waiting Times:");
      fprintf(out_fptr, "Process Waiting Times:");

       //Sorting with respect to arrival time
        bubbleSortarr(&temphead,linecnt);

      //initializing number of remaining processes to be the current number of processes
      rem_process = linecnt;

         while(rem_process!=0){
         for(tempcurrent=temphead; tempcurrent; tempcurrent->next){
            
         if(tempcurrent->rem_time <= time_quan && tempcurrent->rem_time > 0){   //if the remaining time of current process is less than the time quantum and greater than 0
            comp_time +=tempcurrent->rem_time;
            tempcurrent->rem_time = 0;
            flag = 1;
         } else if(tempcurrent->rem_time > 0) { //if remaining time is only greater than 0 and still needs execution
            tempcurrent->rem_time -= time_quan;
            comp_time += time_quan;
         } 
         
         if(tempcurrent->rem_time == 0 && flag ==1){   //If process has truely ended
            rem_process--;
            turn_around_time = comp_time - tempcurrent->arr;
            pwait_time = turn_around_time - tempcurrent->bur; //Calculate process wait time

            printf("\nP%d : %d ms", tempcurrent->pid+1, pwait_time);
            fprintf(out_fptr, "\nP%d : %d ms", tempcurrent->pid+1, pwait_time);

            total_wait_time+= pwait_time;
            
            flag = 0;
            p_count++;
         }
         else{           
            tempcurrent = tempcurrent->next; 
         }
                
         }
         
      }

      avg_wait_time = total_wait_time / p_count;
      printf("\nAverage waiting time: %.2f ms\n", avg_wait_time);
      fprintf(out_fptr, "\nAverage waiting time: %.2f ms\n", avg_wait_time);
      deleteListContent(temphead);
   }
   fclose(out_fptr);
}

void menu(BUR_LIST *current, BUR_LIST *head, const char *OutPath){
   char *sc_method[]={"NONE","FCFS","SJF","PS","RRS"};      //initiating a string array to hold scheduling methods
   char *mode[]={"OFF", "ON"};
   char *inp_data;

   int menu_option;
   int sch_choice;
   int mode_option;
   

   printf("\nCPU SCHEDULER SIMULATOR\n\n");
   printf("1  |  SCHEDULING METHOD (%s)\n",method_choice);
   printf("2  |  PREEMPTIVE MODE (%s)\n",mode_choice);
   printf("3  |  SHOW RESULT\n");
   printf("4  |  END PROGRAM\n\n");
   printf("OPTION >> ");
   scanf("%d", &menu_option);     //getting the menu option as an integer from the user

   int time_q;
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
               scanf("%d", &time_q);
               strcpy(method_choice,sc_method[4]);
               printf("\nRound robin scheduling was selected with time quantum as %d\n",time_q);
               time_quan=time_q;
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
                  //SJF_sch(current, head, OutPath);
                  SJF_sch(current, head, OutPath);
            } else if(strcmp(method_choice, "PS") == 0){
                  PS_sch(current, head, OutPath);
            } else if(strcmp(method_choice, "RRS") == 0){
                  RRS_sch(current, head, OutPath);
            } else{
                  printf("Error while creating Scheduling method");
            }
            menu(current, head, OutPath);

      } else if(menu_option == 4){            
               //Print the content of Output.txt to the screen here
               inp_fptr = fopen(OutPath, "r");

               while(fgets(myString, sizeof(myString), inp_fptr)){
                  printf("%s", myString);

               }
               fclose(inp_fptr);

               printf("\nProgram ended\n");
               exit(1);            
            
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
         node->rem_time = bur;

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

