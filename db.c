/* A simple database */
#include <stdio.h>
#include <string.h>
#include "readfile.h"
int main (int argc , char *argv[])
  {
    char * filename = argv[1];
    
    printf("%s" , filename);
    FILE *f = fopen(filename, "r+");/*opening the file in read and write mode*/
    if (f != NULL)
     {	
       readfile(f); /*passes this pointer to the readfromfle function*/
       process_request(f); /*passes this pointer to the process_request function*/
     }
    else
     {
      	printf("Error opening file\n");
     }  
   }

	

