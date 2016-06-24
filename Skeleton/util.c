/* source file: util.c
	author: 	Karl
	date: 		May 2016
	purpose:	Provide a set of utility functions for ST2512 Assignment 1
	dependence/assumption
	file: util.h
	file: wordlist.txt

	last update 27/May/2016 - fixing a bug found at add_node to add_node_to_list()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

int get_list_size(wordNode * thisList) {
	int size = 0;
	while (thisList != NULL) {
		size++;
     	thisList = thisList->next;
	}
	return size;
}
char * get_nth_word_from_list(wordNode * thisList, int nth) {
	int i ;
	wordNode * cur_ptr;
	cur_ptr=thisList;
	for(i=0; i<nth; i++) {
		if (cur_ptr == NULL) {
			// serious problem
			exit(-1);
		}
     	cur_ptr = cur_ptr->next;
	}
  	// cur_ptr should point to the correct node now.  
	if (cur_ptr == NULL) {
		// serious problem
		exit(-1);
	}
	return cur_ptr->word;
}
char * get_random_word(dict * this_dict) {
/* 
	this_dict is an array of  wordNode * (wordNode list) 
	get_random_word() will 
	   firstly pick a random wordNode * from the this_dict array	
	   secondly pick a random wordNode from this target wordNode list.
       finally return the 'word' of the selected wordNode.
	
*/
    wordNode * target_list;
	int index, wordcount;
    char * word_found;
	srand(time(NULL));  /* initializing randomizer */
	index = rand() % 26 ; // randomly choose one of the lists
	target_list = (*this_dict)[index];
    // assumption , target_list is not  NULL
	wordcount = get_list_size(target_list);
    if (wordcount == 0) {
		printf("Invalid dictionary has been used to invoke get_random_word()\n");  
		exit(-1);
	}	
	do {
    	index = rand() % wordcount; // pick a random position
		word_found = get_nth_word_from_list(target_list, index);	
	} while (strlen(word_found) < MINWORD_LEN) ; 
	// cannot accept a shorter word , loop back to get another one. 
    return word_found;
}
dict * get_new_dict() {
   /* using malloc to create a new dictionary, and return its pointer to the caller */
   dict *  new_dict_ptr;
   int i;
   new_dict_ptr = (dict *) malloc(sizeof(dict));
   // make sure all the 26 emlements are null at this point.
   for (i =0 ; i< 26; i++ ) {
     (*new_dict_ptr)[i]=(wordNode *)NULL;
   }
 
   return new_dict_ptr;    
	
}
wordNode * get_new_node(char * new_word){
	wordNode * newNode;
	newNode = (wordNode *)malloc( sizeof(wordNode));
    strcpy(newNode->word,new_word);
    newNode->next = NULL;
	return newNode;
}

wordNode * add_node_to_list(wordNode * thisList, wordNode * thisNode){
    /* assumption: 
       1. thisList points to a list of wordNode. 
       2. thisList contains at least one node.
	   3. The word in thisNode is not yet existing in thisList. 
 	*/ 
    // add thisNode to thisList according to the alphabetical order
    wordNode * cur_ptr, * prev_ptr ; // current and previous working pointer
    prev_ptr = NULL;  // initial position.
    cur_ptr = thisList;  // initial position.
    for(;;) {
      if ( strcmp(thisNode->word,cur_ptr->word) < 0 ) {
		/* we need to insert the word now */ 
        thisNode->next = cur_ptr;
		if (prev_ptr == NULL) {
		   // special case, the newword has inserted at the beginning of the list
		   // return thisNode to make it become the 1st node of the list
		   return thisNode;
		} else {
        	prev_ptr->next = thisNode;
		}
        break; // exit from the loop
      }
	  if (cur_ptr->next == NULL) {
		// There is no more node in thisList, just append thisNode to the end. 
        cur_ptr->next = thisNode; 
		break; // exit from the loop too.
	  }
      // let try the next node, update both prev_ptr and cur_ptr accordingly
	  prev_ptr = cur_ptr;
      cur_ptr = cur_ptr->next;
	} // end for
    // reaching here means the job is done.
	// just return back the original list pointer
	return thisList;
}
void add_node_to_dict(dict * thisdict,wordNode * thisnode){
	// add the new wordNode to one of the wordNodeLists 
	// according to the 1st letter ('a' to 'z') value.
	wordNode * thisHeadPtr;
	int index;
    /* find the correct entry element first*/
    #ifdef DEBUG
       printf("Adding %s to dict\n", thisnode->word);
  	#endif 
    char firstch = thisnode->word[0]; // get the 1st letter
    index = firstch - 'a'; 			  // compute the array index
    thisHeadPtr = (*thisdict)[index]; 
    // take care a special case, when this entry is NULL
    if (thisHeadPtr == NULL) {
		// let this node becomes the 1st Node of the list
		(*thisdict)[index] = thisnode;
    }else{
		(*thisdict)[index] = add_node_to_list(thisHeadPtr,thisnode);
	}

    
}
void load_words_to_dict(dict * thisdict, char * dictfile){
  // reading out all the words from the file (based on the given filename - dictfile
  // assumption : each line contains only one word
  // the word will be added to one of the wordNode lists ('a' to 'z') according.
  FILE * fp;
  char new_word[MAXWORD_LEN];
  wordNode * thisnode;
  fp = fopen(dictfile,"r"); // read mode
	if (fp == NULL) {
		printf("Fatal Error! dictionary file not found. System Halted\n");
		exit(-1);
	}
	while (fscanf(fp,"%s",new_word) != EOF) {
		#ifdef DEBUG
			printf("%s\n",new_word);
		#endif
		// create a new wordnode and add it to the dictionary accordingly.
		thisnode = get_new_node(new_word);
	    add_node_to_dict(thisdict,thisnode);
	}
	fclose(fp);
	return; 

}
void freeNodesMem(wordNode * onelist_ptr) {
	/* use free() to release all the previously mallocated memory */
	int counter=0;
	wordNode * workptr;
	wordNode * toDeleteptr;

	workptr = onelist_ptr;
	while (workptr != NULL) {
		toDeleteptr = workptr;
		workptr = workptr->next;
		/* now can delete */
		free(toDeleteptr);	
		counter++;
	}	
	#ifdef DEBUG
		printf("%d Nodes has been released !\n",counter);
	#endif
}
void free_dict_mem(dict * this_dict) {
  /* Release all the mallocated memory of the 26  wordNode lists */
	int i;
    for (i=0;i<26;i++) {
		freeNodesMem((* this_dict)[i]); 
	}
}

