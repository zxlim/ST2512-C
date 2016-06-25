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
#define MAXNAME_LEN 35

dict * dictptr;

char * prompt_name(char * prompt_msg,char * newname){
	printf("%s",prompt_msg);
	scanf("%s",newname);
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
	printf("\nPress Enter to exit this help menu.\n");
	scanf("%c%c",&dummy,&dummy);
}

void playgame() {
	int round = 1;
	int player_scores[2]= {0,0};
	char pname[2][MAXNAME_LEN];
	char curword[MAXWORD_LEN];
	char nextword[MAXWORD_LEN];

	strcpy(curword, get_random_word(dictptr));
	//wordNode* wordList = get_new_node(curword);

	printf("Choose your names (Maximum 35 letters)\n");
	strcpy(pname[0],prompt_name("Name of Player 1: ",pname[0]));
	strcpy(pname[1],prompt_name("Name of Player 2: ",pname[1]));

	for (;;) {
		printf("\n\nRound %4d:\n%s's Score:\t%3d\n%s's Score:\t%3d\n", round, pname[0],player_scores[0],pname[1],player_scores[1]); 


		printf("The current word is:\t%s\n\n", curword); 

		printf("(Enter 'q' to quit the game or 'h' for the help menu)\n%s, enter the next word: ", pname[(round+1)%2]); 
		scanf("%s", nextword);

		if (strcmp(nextword,"q") == 0) {
			char confirmQuit[1];
			printf("\nAre you sure you want to quit the game?\n50 points will be deducted! (y/n): ");
			scanf("%s", confirmQuit);
			if (strcmp(confirmQuit,"y") == 0) {
				player_scores[(round+1) % 2] -= 50;
				printf("\n%s decided to quit the game.", pname[(round+1) % 2]);
				//freeNodesMem(wordList);
				break;
			}
			continue;
		}

		if (strcmp(nextword,"h") == 0) {
			showhelpmenu();
			continue;
		}

		// Code below this comment line to complete the program

		/* Compare last letter of current word and first letter of next word (STILL FIGURING OUT HOW -zx)
		char lastchar[1];
		char firstchar[1];

		lastchar[0] = curword[strlen(curword)-1];
		printf("\n%s\n", lastchar); //DEBUG
		firstchar[0] = nextword[0];
		printf("\n%s\n", firstchar); //DEBUG

		if (strcmp(lastchar,firstchar) == 0) {
			//add_node_to_list(wordList, get_new_node(nextword));
			continue;
		} else {
			printf("Oops, %s entered an invalid word!", pname[(round+1) % 2]);
			//freeNodesMem(wordList);
			break;
		}*/

	} // End of For Loop
	
	printf("\n\n\nFinal score at round %4d:\n",round);
	printf("%s's Score:\t%3d\n%s's Score:\t%3d\n\n",pname[0],player_scores[0],pname[1],player_scores[1]);

	if (player_scores[0] > player_scores[1]) {
		printf("%s wins %s with %3d point difference! Congratulations!\n", pname[0], pname[1], (player_scores[0]-player_scores[1]));
	} else {
		printf("%s wins %s with %3d point difference! Congratulations!\n", pname[1], pname[0], (player_scores[1]-player_scores[0]));
	}

}

int main() {

	char again[1];

	printf("\n|====================================|\n");
	printf("|  Welcome to the ChainyWords Game!  |\n");
	printf("|====================================|\n");

	// Loops the game until the player wishes to stop playing
	for (;;) {
		int i = 0;

		printf("\nLoading game...\n\n\n");

  		srand(time(NULL));  // Initialize randomizer
  		dictptr=get_new_dict();
  		load_words_to_dict(dictptr, "wordlist.txt");

  		playgame();

  		// Free all dynamically allocated memory
  		free_dict_mem(dictptr);

  		printf("Do you wish to play again? (y/n): ");
  		scanf("%s", again);

  		if (strcmp(again,"n") == 0) {
  			printf("\nThanks for playing ChainyWords!\n\n");
  			printf("Exiting game...\n\n");
  			break;
  		}
  	}
  }
