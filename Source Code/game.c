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
#include <unistd.h>
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
	printf("\n|====================================|\n");
	printf("|   The ChainyWords Game Help Menu   |\n");
	printf("|====================================|\n");
	printf("\n\nThis is a two players game.\n\n");
	printf("  The game begins by showing the players a randomly picked word.\n");
	printf("  The two players will take turns to enter a new word to replace the current word according to the game rules stated here.\n");
	printf("  Repeat the above process to increase your game score.\n");
	printf("  The game will be terminated when one of the players has chosen to quit or entered an unaccepted word.\n");
	printf("\n\nAcceptance rules for a new word:\n\n");
	printf("  - The minimum length of the word is 6 letters.\n");
	printf("  - It must be listed in the game's internal dictionary.\n");
	printf("  - It has not been entered during the current game session.\n");
	printf("  - The new word must begin with the last letter of the current word.\n");
	printf("  - It cannot end with -ing.\n");
	printf("\n\nScoring Rules:\n\n");
	printf("  Each letter in the new word earns you scores based on the following:\n");
	printf("  \n"); 
	printf("  (1 point)   a, e, i, o, u, l, n, s, t, r\n");
	printf("  (2 points)  d, g\n");
	printf("  (3 points)  b, c, m, p\n");
	printf("  (4 points)  f, h, v, w, y\n");
	printf("  (5 points)  k\n");
	printf("  (8 points)  j, x\n");
	printf("  (10 points) q, z\n");
	printf("\n\nScoring Penalties:\n\n");
	printf(" Doing the following actions will result in score reduction:\n");
	printf("  - Quitting the game midway (-100 points)\n");
	printf("  - Submitting an unaccepted word (-50 points)\n");
	printf("\nPress Enter to exit this help menu.\n");
	scanf("%c%c",&dummy,&dummy);
	system("clear");
}

void playgame() {
	int round = 1;
	int player_scores[2]= {0,0};
	char dummy;
	char lastchar[2];
	char firstchar[2];
	char pname[2][MAXNAME_LEN];
	char curword[MAXWORD_LEN];
	char nextword[MAXWORD_LEN];

	strcpy(curword, get_random_word(dictptr));
	wordNode* wordList = get_new_node(curword);

	printf("\n|====================================|\n");
	printf("|  Welcome to The ChainyWords Game!  |\n");
	printf("|====================================|\n");
	printf("\nChoose your names (Maximum 35 letters)\n");
	strcpy(pname[0],prompt_name("Name of Player 1: ",pname[0]));
	strcpy(pname[1],prompt_name("\nName of Player 2: ",pname[1]));

	printf("\nInitializing game session...\n");

	sleep(2);
	system("clear");

	for (;;round++) {
		printf("\n\nRound %4d:\n%s's Score:\t%3d\n%s's Score:\t%3d\n", (round+1)/2, pname[0],player_scores[0],pname[1],player_scores[1]); 


		printf("The current word is:\t%s\n\n", curword);

		printf("(Enter 'q' to quit the game or 'h' for the help menu)\n%s, enter the next word: ", pname[(round+1)%2]); 
		scanf("%s", nextword);

		if (strcmp(nextword,"q") == 0) {
			char confirmQuit[1];
			printf("\nAre you sure you want to quit the game?\n100 points will be deducted! (y/n): ");
			scanf("%s%c", confirmQuit, &dummy);
			if (strcmp(confirmQuit,"y") == 0) {
				player_scores[(round+1) % 2] -= 100;
				printf("\n%s decided to quit the game.", pname[(round+1) % 2]);
				freeNodesMem(wordList);
				break;
			}
			continue;
		}

		if (strcmp(nextword,"h") == 0) {
			showhelpmenu();
			continue;
		}

		// Code below this comment line to complete the program

		//Check for "ing" in new word
		const char notallowed[] = "ing";

		if (strstr(nextword, notallowed) != NULL) {
			printf("\nSorry, the word %s ends with -ing, which is not accepted!\n", nextword);
			player_scores[(round+1) % 2] -= 50;
			printf("\n%s received a penalty of -50 points", pname[(round+1) % 2]);
			freeNodesMem(wordList);
			break;
		}

		// Compare last letter of current word and first letter of new word
		sprintf(lastchar, "%c" , curword[strlen(curword)-1]);
		lastchar[2] = '\0';

		sprintf(firstchar, "%c" , nextword[0]);
		firstchar[2] = '\0';

		//printf("\n%s\n", lastchar); //DEBUG USE
		//printf("\n%s\n", firstchar); //DEBUG USE

		if (strcmp(lastchar,firstchar) == 0) {
			add_node_to_list(wordList, get_new_node(nextword));
			strcpy(curword, nextword);
			continue;
		} else {
			printf("Oops, %s entered an invalid word!", pname[(round+1) % 2]);
			player_scores[(round+1) % 2] -= 50;
			printf("\n%s received a penalty of -50 points", pname[(round+1) % 2]);
			freeNodesMem(wordList);
			break;
		}
	} // End of For Loop
	
	printf("\n\n\nFinal score at round %4d:\n",(round+1)/2);
	printf("%s's Score:\t%3d\n%s's Score:\t%3d\n\n",pname[0],player_scores[0],pname[1],player_scores[1]);

	if (player_scores[0] > player_scores[1]) {
		printf("%s wins %s with %3d point difference! Congratulations!\n", pname[0], pname[1], (player_scores[0]-player_scores[1]));
	} else {
		printf("%s wins %s with %3d point difference! Congratulations!\n", pname[1], pname[0], (player_scores[1]-player_scores[0]));
	}

}

int main() {

	char again[1];

	system("clear");

	printf("\n|====================================|\n");
	printf("|  Welcome to The ChainyWords Game!  |\n");
	printf("|====================================|\n");

	// Loops the game until the player wishes to stop playing
	for (;;) {
		int i = 0;

		printf("\nLoading game...\n\n\n");

  		srand(time(NULL));  // Initialize randomizer
  		dictptr=get_new_dict();
  		load_words_to_dict(dictptr, "wordlist.txt");

  		system("clear");
  		playgame();

  		// Free all dynamically allocated memory
  		free_dict_mem(dictptr);

  		printf("Do you wish to play again? (y/n): ");
  		scanf("%s", again);

  		if (strcmp(again,"n") == 0) {
  			system("clear");
  			printf("\n\n|============================================|\n");
  			printf("|  Thanks for playing The ChainyWords Game!  |\n");
  			printf("|============================================|\n");
  			printf("\nExiting game...\n\n");
  			sleep(3);
  			system("clear");
  			break;
  		}
  	}
  }
