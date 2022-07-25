// Deandre Mylove or just Dre
// CS 446 homework 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// Function Prototypes
int ls_sim(struct dirent *);
int ls_sim_verbose(struct dirent *);
int error_msg();
void an_attempt_at_formatting_ls_verbose();


/*
name: main
type: int
arguments: int argc
function: checks arguments and checks commands that are possible based on the number of arguments
          if command matches one of the commands i have implemented. if a match is found main will 
          call function associated with that command
returns:  0 if successful, 1 if error
*/
int main(int argc,char* argv[])
{
    struct dirent *pDirent;
    DIR *pDir; 

    if (argc == 1)              // if argc == 1 the user didnt enter any commands 
    {
        return error_msg();     // error message returns 1, which is then retuned from main
    }

    if (argc > 4)               // if argc greater than 4 the user entered too many commands
    {
        return error_msg();
    }

    // Checks first argument for "ls" if strmcp returns false, prints error with valid commands. 
    if (argc == 2)
    {
        if (strcmp(argv[1], "ls") != 0)     // if the second argument is not ls the user did not follow the boot directions
        {
            return error_msg();        
        }
        else
        {
            pDir = opendir(".");                        // "." represents current directory
            pDirent = readdir(pDir);                    // opening current directory 
            while ((pDirent = readdir(pDir)) != NULL)   // setting parameters for the loop
            {
                ls_sim(pDirent);                        // calling function to handle "ls" command
            }  
        }
    }

    if (argc == 3)
    {
        if (strcmp(argv[2], "-l") != 0)   
        {
            pDir = opendir(argv[2]);                  // opening directory with path name provided
        
            if (pDir != NULL)                         // checking if the file path exists
            {
                pDirent = readdir(pDir);                    // opening current directory 
                while ((pDirent = readdir(pDir)) != NULL)   // setting parameters for the loop
                {
                    ls_sim(pDirent);                        // calling function to handle "ls" command
                }                      // opening path if it exists
            }
            else
            {
                return error_msg();                  // displaying error message if path doesnt exist
            }
        }
        else if((strcmp(argv[2], "-l") == 0))       // checking if argument is -l, only if argument is not path
        {
            pDir = opendir("."); 
            pDirent = readdir(pDir);                // opening currint directory 
            an_attempt_at_formatting_ls_verbose();
            while ((pDirent = readdir(pDir)) != NULL)   // setting parameters for the loop
            {
                ls_sim_verbose(pDirent); 
            }  
        }
        else
        {
            return error_msg();
        }
    }
  

    if (argc == 4)      // if there are 4 arguments the last argument should be path
    {
        if (strcmp(argv[2], "-l") != 0)   
        {
            pDir = opendir(argv[3]);                    // opening directory with path name provided
        
            if (pDir != NULL)                           // checking if the file path exists
            {
                pDirent = readdir(pDir);                // opening currint directory 
                an_attempt_at_formatting_ls_verbose();
                while ((pDirent = readdir(pDir)) != NULL)   // setting parameters for the loop
                {
                    ls_sim_verbose(pDirent); 
                }            
            }
            else
            {
                return error_msg();                    // displaying error message if path doesnt exist
            }
        }
    }
   
    return 0;       // should only return 0 if this program runs sucessfully
}
 
/*
name: ls_sim
type: int
arguments: struct dirent *pDirent
function: if File name is null the function will print error message and return 1
          if successful all files will be printed in the working directory
          to print all files the function is called from a loop in main.
returns:  0 if successful, 1 if error
*/
int ls_sim(struct dirent *pDirent)
{
    if (pDirent->d_name == NULL)
    {
        error_msg();
        return 1;
    }
    else
    {
        printf ("[%s]\n", pDirent->d_name);
        return 0;
    }   
   
}

/*
name: ls_sim_verbose
type: int
arguments: struct dirent *pDirent
function: function prints file name-inode size- links
          i have up on trying to get mode_t to work and i ve up 
returns:  0 if successful, 1 if error
*/
int ls_sim_verbose(struct dirent *pDirent)
{
    char buffer[100];
    struct stat filestat;
    mode_t mode;                        // i gave up on getting this to work 
    strcpy(buffer, "./"); 
    strcpy(buffer, pDirent->d_name);

    if (stat(buffer, &filestat) == -1)
    {
        return error_msg();
    }
    else
    {
        printf ("[%s]\t\t", pDirent->d_name);
        printf ("[%zu]\t", filestat.st_ino);
        printf ("[%zu]\t", filestat.st_size);
        printf ("[%zu]\n", filestat.st_nlink);
    }

    return 0;
}

/*
name: error_msg
type:int
arguments: none
function: prints error message 
returns: always returns 1 to warn of disaster
*/
int error_msg()
{
    printf("An error has occurred. Options are: \n");
    printf("ls \nls -l \nls <path> \nls -l <path>\n");
    
    return 1;
}

/*
name: an_attempt_at_formatting_ls_verbose
type:void
arguments: none
function: This is a formatter to make columns for output. its kinda horrible
returns:  void
*/
void an_attempt_at_formatting_ls_verbose()
{
    printf("File Name \t Inode \t\t Size(B) \t Links \t\n");
    printf("----------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------\n");

}