#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prompt.h"
#define MAX_DEPARTMENT_LENGTH 6
#define MAX_COURSE_NUMBER_LENGTH 5
#define MAX_COURSE_LOCATION_LENGTH 12
#define MAX_NO_CLASSES 100
#define MAX_LINE_LENGTH 100
struct class
 {
   char department [MAX_DEPARTMENT_LENGTH];
   char number [MAX_COURSE_NUMBER_LENGTH];
   char location [MAX_COURSE_LOCATION_LENGTH];
   
 };

void readfile(FILE *f);/*A function prototype*/
void process_request(FILE *f);

static struct class* classes[MAX_NO_CLASSES]; /*An array that holds pointer to 100 struct classes*/
static int no_of_classes; /*The no classes in the file*/

void  readfile(FILE *f)
  {	
    int i = 0;
    fscanf(f , "%d" , &no_of_classes); /* Reading the first-line which is an int*/
    	
      /*This will move the file pointer to nextline */
    char pseudo[MAX_LINE_LENGTH];
    fgets(pseudo  , MAX_LINE_LENGTH , f);
    char line[MAX_LINE_LENGTH]; /*Stores a new class from the file*/
    
      while (i < no_of_classes)
      {
        fgets(line , MAX_LINE_LENGTH , f);
	classes[i] = (struct class*) malloc(sizeof(struct class)); /*Dynamically creating memory for structs*/
  	strcpy(classes[i] -> department , strtok(line , ":"));
	strcpy(classes[i] -> number , strtok(NULL , ":"));
	strcpy(classes[i] -> location , strtok(NULL , ":"));
	i++;
       }
    }    

void process_request(FILE *f)
  {
    		
    int init_classes = no_of_classes;
    
    int val; /* val controls the execution of switch statement*/ 
    char input[MAX_LINE_LENGTH]; 
    char value[MAX_LINE_LENGTH];
    
    while (1) /*Loops repeatedly until the user wants to exit*/
      {	
        display_prompt(); /*A call to the display_prompt function from the displayprompt module*/
	fgets(input , MAX_LINE_LENGTH, stdin); /*gets input from the user and checks with the below conditions*/
	
	if (strcmp(input , "list\n") == 0)
	  {
       	    val = 1;
	  }
	else if (strcmp(input , "add\n") == 0)
	  {
            val = 2;
	  }
	else if (strstr(input , "remove") != NULL)
	  {
	    val = 3;
	  }
	else if (strcmp(input , "exit\n") == 0)
	  {
	    val = 4;
	  } 
	else
	  {
	    val = 5;
	  }
	 
	switch(val)
	 {
           case 1: /*Lists the structs*/
	     {	
		int l;		
		for(l = 0; l < no_of_classes; l++)
		  {
		    printf("%d%s%s%s%s%s\n", (l+1), ":", classes[l] -> department, classes[l] -> number, "-", classes[l]-> location);
		  }
	      }
	   
	     break;

	   case 2: /*Adds a new struct*/
	     {  
		classes[no_of_classes] = (struct class*) malloc(sizeof(struct class)); /*creating a space for additional struct*/
		
		printf("Enter department:\n");
		fgets(value , MAX_DEPARTMENT_LENGTH , stdin);
		value[strlen(value) - 1] = '\0';
		strcpy(classes[no_of_classes] -> department , value);		

		printf("Enter no. of class:\n");
		fgets(value , MAX_COURSE_NUMBER_LENGTH , stdin);
		value[strlen(value) - 1] = '\0';
		strcpy(classes[no_of_classes] -> number , value);		


		printf("Enter location:\n");
		fgets(value , MAX_COURSE_LOCATION_LENGTH , stdin);
		value[strlen(value) - 1] = '\0';
		strcpy(classes[no_of_classes] -> location , value);		
	
		no_of_classes++;
	      }
		
	    break;	

	    case 3: /*Removes the struct*/
	       {	
		  char substring [MAX_LINE_LENGTH];		
		  strtok(input , " \n");
		  strcpy(substring , strtok (NULL , " \n")); /*the substring is the substring to be checked*/
		  printf("%s\n" , substring);
		  int j;
		  int k;
		  for (j = 0 ; j < no_of_classes ; j++) /*substring is checked for all fields of each class below*/
		    {			
			if ((strstr(classes[j] -> department , substring) != NULL) || (strstr(classes[j] -> number , substring) != NULL))
			  {
			    free(classes[j]);
			     for(k = j ; k < no_of_classes - 1; k++)
			      {  
				classes[k] = classes[k + 1]; /*Replacing the pointers*/
		  	      }
			    
			    no_of_classes--; /*no_of_snippets decrease*/
			    if (j > 0)
			     {
			      --j; 
			     }
			   }
		      }
		  }
			
	      break;	
	      
	      case 4: /*Writes the modified struct count and new Struct back to the file*/
	         {
                   if(no_of_classes != init_classes) /*There was a change in the number of classes*/
		    {
  	 	      fseek(f, 0, SEEK_SET); /*Setting the pointer to begining of the file just to be sure*/
		      int i;
		      fprintf(f , "%d\n" , no_of_classes); /*If there is a change in the number of classes then writing to the file*/
		      for (i = 0; i < no_of_classes; i++)
		       {
		         fprintf(f , "%s:%s:%s\n" , classes[i] -> department , classes[i] -> number, 
					classes[i] -> location);
		       } 
		     }
			
 		    exit(0);
	          }  	
	   
	      default: /*handles the case for wrong input*/
		printf("Input mismatch with the prompt!! Try again.");
		
	  }
	}
  
}
