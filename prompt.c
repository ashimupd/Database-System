/*This module is responsible to get the input from the user*/
#include <stdio.h>
void display_prompt();



void display_prompt() /*gets a line from the user, stores it in array, and makes the entire line a string*/
{
  
  printf("\n1.Type \"list\"to list all the structs\n2.Type \"add\" to add a struct\n");
  printf("3.Type \"remove\" and a string to remove all the struct that contains the string as a substring\n");
  printf("4.Type \"exit\" to terminate the program\n");
      
}


  
