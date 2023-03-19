#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"


typedef struct AdptArray_{
    PElement* pelementArray; //implement with malloc, need to be free 
    int size;   //hold length of array
    COPY_FUNC copy_func; //copy element
    DEL_FUNC del_func; //del element
    PRINT_FUNC print_func; //print element

}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func,PRINT_FUNC print_func){
    
    PAdptArray myADT = (PAdptArray )malloc(sizeof(AdptArray));
    if(!myADT){
        printf("no space in Heap\n");
        return NULL;
    }
    myADT->pelementArray = NULL;
    myADT->copy_func = copy_func;
    myADT->del_func = del_func;
    myADT->print_func = print_func;
    myADT->size = 0;
    return myADT;
}

void DeleteAdptArray(PAdptArray myADT){
    if(!myADT){
        return;
    }
    if(!(myADT->pelementArray)){ //check if have elements
        free(myADT);
        myADT=NULL;
        return;
    }//else:
    for(size_t i = 0; i < (myADT->size); i++){//free all elements in the array
        if((myADT->pelementArray)[i]){
            (myADT->del_func)((myADT->pelementArray)[i]);
            (myADT->pelementArray)[i]=NULL;
        }
    }

    free(myADT->pelementArray);
    myADT->pelementArray=NULL;
    free(myADT);
    myADT=NULL;
    return;
}

Result SetAdptArrayAt(PAdptArray myADT, int index, PElement element){
    if(!myADT){
        return FAIL;
    }
    else if(((myADT->size)<=index)){ //need to change the array
        
        PElement newElement = (myADT->copy_func)(element); //the element to add

        PElement * newArr = (PElement*)malloc((index+1)*sizeof(PElement)); //new array
        if(!newArr){
            return FAIL;
        }
        int i;
        for(i = 0; i < (myADT->size); i++){ //fill the new array with all the old element
            newArr[i]=(myADT->pelementArray)[i];
        }
        while(i<index){//initilize all the empty location in the array into NULL
            newArr[i]=NULL;
            i++;
        }
        newArr[index]=newElement;//add the new element

        free(myADT->pelementArray);//free old array

        myADT->pelementArray=newArr; //add new array
        myADT->size=index+1;
        return SUCCESS;
    }
    else{
        PElement newElement = (myADT->copy_func)(element); //the element to add
        
        if((myADT->pelementArray)[index]){//the index is not empty
            
            (myADT->del_func)((myADT->pelementArray)[index]);//release the old element
            
        }
        (myADT->pelementArray)[index]=newElement;//add new element
        return SUCCESS;
    }
}

PElement GetAdptArrayAt(PAdptArray myADT, int index){
    if(!myADT){
        return NULL;
    }
    if(!(myADT->pelementArray)){
        return NULL;
    }
    if((myADT->size) <= index){
        return NULL;
    }
    if(!(myADT->pelementArray)[index]){
        return NULL;
    }
    PElement copyElement = (myADT->copy_func)((myADT->pelementArray)[index]);
    return copyElement;

}
int GetAdptArraySize(PAdptArray myADT){
    if(!myADT){
        return -1;
    }
    return myADT->size;
}

void PrintDB(PAdptArray myADT){
    if(!myADT){
        return;
    }
    for(size_t i = 0 ; i < (myADT->size); i++){
        if((myADT->pelementArray)[i]){
           (myADT->print_func)((myADT->pelementArray)[i]); 
        }
    }

}