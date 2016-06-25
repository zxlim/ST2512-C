/*
** Diploma in Infocomm Security Management, ST2512 Programming in Security
** C Programming Assignment, Done by:
** Lim Zhao Xiang (P1529559), DISM/FT/2A/01
** Gerald Peh Wei Xiang (P1445972), DISM/FT/2A/01
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "util.c"
#define MAXNAME_LEN 35
dict * dictptr;

char * prompt_name(char * prompt_msg,char * newname){
	printf("%s",prompt_msg);
	scanf(" %s",newname);
 	return newname;
}
void showhelpmenu() {
	char dummy;
	char dumdum[80];
	printf("\n\nWelcome to the help menu\n\n");
	printf("\n\nThis is a two players game.\n\n");
	printf("  The game begins by showing the players a  randomly picked word\n");
	printf("  The two players will take turns to enter a new word to replace the current word according to the game rules.\n");
	printf("  Repeat the above process to earn scores from the game.\n");
	printf("  The game will be terminated when one of the players has chosen to quit or entered an unacceptable word\n");
	printf("\nAcceptance Rules for a new word:\n\n");
	printf("  .The minimum length of the word is 6 letters\n");
	printf("  .It is listed in the internal dictionary.\n");
	printf("  .It has not been entered at the same play session.\n");
	printf("  .The new word must begin with the last letter of the current word\n");
	printf("  .It cannot be ended with -ing-. \n");
	printf("\nScoring Rules:\n\n");
    printf("  Each letter in the new word earns points based on the following point values:\n");
	printf("  \n"); 
	printf("  (1 point)-a, e, i, o, u, l, n, s, t, r.\n");
	printf("  (2 points)-d, g.\n");
	printf("  (3 points)-b, c, m, p.\n");
	printf("  (4 points)-f, h, v, w, y.\n");
	printf("  (5 points)-k.\n");
	printf("  (8 points)- j, x.\n");
	printf("  (10 points)-q, z.\n");
	printf("\nPress <Enter Key> to exit help\n");
	scanf("%c%c",&dummy,&dummy);
}
void playgame() {
	int round = 1;
	int player_scores[2]= {0,0};
	char * quitGame;
	char pname[2][MAXNAME_LEN];
	char curword[MAXWORD_LEN];
	char nextword[MAXWORD_LEN];

	printf("+-----------------------------+\n");
	printf("|Welcome to ST2512 playground!|\n");
	printf("+-----------------------------+\n");
	strcpy(pname[0],prompt_name("Player1 Name Please=>",pname[0]));
	strcpy(pname[1],prompt_name("Player2 Name Please=>",pname[1]));
    strcpy(curword, get_random_word(dictptr));
		
	for(;;) {
		printf("\n\nround %4d: %s scores : %3d %s scores : %3d\n",round, pname[0],player_scores[0],pname[1],player_scores[1]); 

		printf("current word is %s. \n\n",curword); 

		printf("%s , please enter the next word (or 'h' for help ,  'q' to quit)=>",pname[(round+1)%2]); 
		scanf(" %s", nextword); 
		if (strcmp(nextword,"q")==0) {
			printf("Are you sure you want to quit the game? (Y/n):");
			scanf(" %s", quitGame);
			if (quitGame == "Y") {
				printf("\nQuitting game...\n");
				break;
			}
			continue;
		}
		if (strcmp(nextword,"h")==0) {
			showhelpmenu();
			continue;
		}
		/* fill in your code to complete the program */

   		/*											 */
	} /* end for loop */
	printf("\n\nFinal score at round %4d:\n",round);
	printf("%s scores : %3d %s scores : %3d\n\n",pname[0],player_scores[0],pname[1],player_scores[1]); 
}

int main() {
	int i = 0;

  	srand(time(NULL));  /* initializing randomizer */

	dictptr=get_new_dict();
	load_words_to_dict(dictptr, "wordlist.txt");
	playgame();	
    /* free all dynamically allocated memories */	
	free_dict_mem(dictptr) ; 
}
