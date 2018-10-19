//
//  driver.c
//
//
//  Created by Mr Kevin on 10/10/18.
//

#include <stdio.h>
#include "stack.h"
#include  <string.h>
#include <stdbool.h>

char *checkingString (FILE **open, char read);
void  checkTag (stackADT storeStack, char *string );
void printRemainding(stackADT storeStack);

int main (int  argc, char *argv[]){
    int i ;
    char read;
    stackADT storeStack; // make new stack
    storeStack = NewStack();
    FILE * open;
    if ( argc< 2){
        printf("Error command line\n" );
        exit(1);
    }
    open = fopen (argv[1], "r");
    
    
    
    if (open == NULL ){
        printf(" Error opening file \n" );
        exit(0);
    }
    char *string;
    
    while (fscanf(open,"%c", &read)==1){
        string = checkingString(&open, read);//String will be assign string insde <....>
            if ( string != NULL)             // get rid of all the NUll
                checkTag (storeStack, string);
        }
    
    printf(" YES, all the tags are nested correctly.\n" ); // if the function make it all the the way to this point
    free (string);
}


void checkTag (stackADT storeStack, char *string){
    int len = strlen(string);
    char *pop = strchr(string,'/'); // occurance forward
    char *ignore = strpbrk(string,"!");  // Match character and then pop
    int count, count1 = 0;
    //  char *ignore1 = strrchr ( string, '/'); // checking character backward
    
    if (string[0] == '/'){
        // printf(" \t\tHere:%s\n", pop);
        if ( StackIsEmpty(storeStack)){
            Error("\nPop of an empty stack");
        }
        char * temp, *temp2;
        temp = Pop(storeStack);
        temp2 = strchr (temp,' ');      // replace space with \0 which ignore that entire string
        if(temp2)
            *temp2 = '\0';
        if(strcmp(string + 1,temp) != 0){
            printf("\nNO, the tag <%s> and <%s> violates the proper nesting!\n", string, temp );
            printRemainding(storeStack);
            exit(1);
        }
        else{
            
        }
    }
    if ( string[len-1] == '/'){ // ignore if it's single sided
        return;
    }
    
    else if ( StackIsFull(storeStack))
        printf(" Stack is Full\n");
    else if ( string[0] != '/') {       // check only condition that ignore the /
        Push(storeStack, string);
    }
}

void printRemainding (stackADT storeStack){
    
    if ( StackIsEmpty(storeStack)){
        return;
    }
    while ( !StackIsEmpty(storeStack)){
        printf("<%s>\n", Pop(storeStack));      // printing remaining in the stack
    }
}


char *checkingString  (FILE **open, char read){
    
    
    //  compare until this < then store everything inside <...>
    if ( read == '<'){
        char *store = (char*)malloc (250 *sizeof(char));    // register memory block
        int len = strlen (store);
        
        if ( store == NULL){    // checking
            exit(1);
        }
        fscanf(*open,"%[^>]", store);      // <---This thing is cool.
        
        if ( strpbrk ( store, "!--")){      // catching Comment string
            
            if  (store [len -1] == '>' && store [len-2] != '-' && store[len-3] != '-' ) {   // avoiding ...-->
                
                return NULL;
            }
        }
        return store;       // if none of the case, return those string
        free(store);
    }
    
    return NULL;
}














