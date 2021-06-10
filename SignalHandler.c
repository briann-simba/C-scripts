// A C program to illustrate 
// user-defined signal handling
#include<stdio.h>
#include<signal.h>
  
//The function to print the caught signal
void handle_sigint(int sig)
{
    printf("We have caught signal %d\n", sig);
}

int main()
{
    // To test this function, press ctrl+c after running the program
    signal(SIGINT, handle_sigint);
    while (1) ;
    return 0;
}
