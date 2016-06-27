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
#include <ctype.h>
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
	system("clear");
	printf("\n |====================================|\n");
	printf(" |   The ChainyWords Game Help Menu   |\n");
	printf(" |====================================|\n");
	printf("\n\n This is a two-player game.\n\n");
	printf(" The game begins by showing the players a randomly picked word.\n\n");
	printf(" The two players will take turns to enter a new word to replace the");
	printf("\n current word according to the game rules stated below.\n\n");
	printf(" Repeat the process and increase your game score!\n\n");
	printf(" A game session will end when one of the players has chosen to");
	printf("\n quit or have entered an invalid word 3 times in a row.\n\n");
	printf("\n\n Acceptance rules for a new word:\n\n");
	printf("   - The minimum length of the word is 6 letters.\n");
	printf("   - The maximum length of the word is 35 letters.\n");
	printf("   - The word must be in the game's internal dictionary.\n");
	printf("   - The word must not have been entered during the current game session.\n");
	printf("   - The word must begin with the last letter of the current word.\n");
	printf("   - The word must not contain any uppercase, numbers or special characters.\n");
	printf("   - The word cannot end with 'ing'.\n");
	printf("\n\n Scoring Rules:\n\n");
	printf("   Each letter in the new word earns you scores based on the following:\n");
	printf("   \n"); 
	printf("   (1 point)   a, e, i, o, u, l, n, s, t, r\n");
	printf("   (2 points)  d, g\n");
	printf("   (3 points)  b, c, m, p\n");
	printf("   (4 points)  f, h, v, w, y\n");
	printf("   (5 points)  k\n");
	printf("   (8 points)  j, x\n");
	printf("   (10 points) q, z\n");
	printf("\n\n Scoring Penalties:\n\n");
	printf("  Doing the following actions will result in score reduction:\n");
	printf("   - Quitting the game midway (-100 points)\n");
	printf("   - Submitting an invalid word (-50 points)\n");
	printf("\n Press Enter to exit this help menu.\n ");
	scanf("%c", &dummy);
	system("clear");
}


void debugPrintLinkedList(wordNode * linkedList) {
	wordNode * list = linkedList;

	while (list != NULL) {
		printf("\n [DEBUG] %s", list -> word);
		list = list -> next;
	}

}


int scoringSystem(char nextword[]) {

	int nextword_length = strlen(nextword);
	int x = 0;
	int roundPoints = 0;

	for (x = 0; x < nextword_length; x++) {

		char wordchar;
		wordchar = nextword[x];

		if (wordchar == 'a' || wordchar == 'e' || wordchar == 'i' || wordchar == 'o' || wordchar == 'u' || wordchar == 'l' || wordchar == 'n' || wordchar == 's' || wordchar == 't' || wordchar == 'r'){
			printf(" Letter \"%c\" was 1 point!\n", wordchar);
			roundPoints += 1;
		} else if (wordchar == 'd' || wordchar == 'g') {
			printf(" Letter \"%c\" was 2 points!\n", wordchar);	
			roundPoints += 2;
		} else if (wordchar == 'b' || wordchar == 'c' || wordchar == 'm' || wordchar == 'p' ) {
			printf(" Letter \"%c\" was 3 points!\n", wordchar);
			roundPoints += 3;
		} else if (wordchar == 'f' || wordchar == 'h' || wordchar == 'v' || wordchar == 'w' 	|| wordchar == 'y') {
			printf(" Letter \"%c\" was 4 points!\n", wordchar);
			roundPoints += 4;
		} else if (wordchar == 'k') {
			printf(" Letter \"%c\" was 5 points!\n", wordchar);
			roundPoints += 5;
		} else if (wordchar == 'j' || wordchar == 'x') {
			printf(" Letter \"%c\" was 8 points!\n", wordchar);
			roundPoints += 8;
		} else if (wordchar == 'q' || wordchar == 'z') {
			printf(" Letter \"%c\" was 10 points!\n", wordchar);
			roundPoints += 10;
		} else {
			printf("\n You did not input an alphabet! \"%c\" is not an alphabet!\n\n", wordchar);	
		}
	} //End of FOR loop

	return roundPoints;
}


int checkWordLength(char nextword[]) {

	int nextword_length_ok = 0;
	int nextword_length = strlen(nextword);

	if (MINWORD_LEN <= nextword_length) {
		nextword_length_ok = 1;
	}

	return nextword_length_ok;
}


int checkUppercase(char nextword[]) {

	int uppercase_not_ok = 0;
	int i;

	for (i = 0; i < strlen(nextword); i++) {
		if (isupper(nextword[i])) {
			uppercase_not_ok = 1;
			break;
		}
	}

	return uppercase_not_ok;
}


int checkEndingING(char nextword[]) {

	int i;
	int nextword_ing_ok = 0;
	char lastthreechar[4];
	const char notallowed[] = "ing";

	for (i = 0; i < 3; i++) {
		lastthreechar[i] = nextword[strlen(nextword) - (3 - i)];
	}

	lastthreechar[4] = '\0';

	if ((strcmp(lastthreechar, notallowed) != 0)) {
		nextword_ing_ok = 1;
	}

	return nextword_ing_ok;
}


int matchFirstLastChar(char curword[], char nextword[]) {

	int nextword_firstlast_ok = 0;
	char lastchar[2];
	char firstchar[2];

	sprintf(lastchar, "%c" , curword[strlen(curword)-1]);
	lastchar[1] = '\0';

	sprintf(firstchar, "%c" , nextword[0]);
	firstchar[1] = '\0';

	if (strcmp(lastchar,firstchar) == 0) {
		nextword_firstlast_ok = 1;
	}

	return nextword_firstlast_ok;
}


int checkWordList(wordNode * wordList, char * nextword) {

	int usedword_not_ok;
	wordNode* list = wordList;

	while (list != 0) {
		if (strcmp(list -> word, nextword) == 0) {
			usedword_not_ok = 1;
			break;
		}

		list = list -> next;
	}

	return usedword_not_ok;
}


int checkDictList(char nextword[]) {

	int nextword_indict_ok = 0;

	//if (strcmp(nextword, dictptr) == 0) {
		//nextword_indict_ok = 1;
	//}

	return nextword_indict_ok;
}


void playgame() {
	int roundScore;
	int validword = 0;
	int round = 1;
	int forcequit = 0;
	int player_scores[2]= {0,0};
	char dummy;
	char pname[2][MAXNAME_LEN];
	char curword[MAXWORD_LEN];
	char nextword[MAXWORD_LEN];
	wordNode * wordList;

	strcpy(curword, get_random_word(dictptr));
	wordList = get_new_node(curword);

	printf("\n |====================================|\n");
	printf(" |  Welcome to The ChainyWords Game!  |\n");
	printf(" |====================================|\n");
	printf("\n Choose your names (Maximum 35 letters)\n");
	strcpy(pname[0],prompt_name("\n Name of Player 1: ",pname[0]));
	strcpy(pname[1],prompt_name(" Name of Player 2: ",pname[1]));

	printf("\n Initializing game session...\n");

	sleep(2);
	system("clear");

	for (;;) {

		int invalidcount = 3;

		debugPrintLinkedList(wordList);

		for (;;) {

			printf("\n |====================================|\n");
			printf(" |            Round   %4d            |\n", (round+1)/2);
			printf(" |====================================|\n");
			printf("\n %s's Score:\t%3d\n %s's Score:\t%3d\n", pname[0],player_scores[0],pname[1],player_scores[1]); 

			if (roundScore > 0 && validword == 1 && strcmp(nextword,"h") != 0 && strcmp(nextword,"q") != 0) {
				printf("\n You have obtained %i points for the word \"%s\"\n", roundScore, nextword);
			}

			printf("\n The current word is:\t%s\n\n", curword);

			printf(" (Enter 'q' to quit the game or 'h' for the help menu)");
			printf("\n %s, enter the next word: ", pname[(round+1)%2]);
			scanf("%s%c", nextword, &dummy);

			if (strcmp(nextword,"q") == 0) {
				char confirmQuit[1];
				printf("\n Are you sure you want to quit the game?");
				printf("\n 100 points will be deducted! (Y/n): ");
				scanf("%s%c", confirmQuit, &dummy);

				if (strcmp(confirmQuit,"Y") == 0) {

					printf("\n %s decided to quit the game.\n", pname[(round+1) % 2]);
					printf("\n %s received a penalty of -100 points.\n", pname[(round+1) % 2]);
					player_scores[(round+1) % 2] -= 100;
					forcequit = 1;
					break;

				} else {

					system("clear");
					continue;

				}
			}

			if (strcmp(nextword,"h") == 0) {
				system("clear");
				showhelpmenu();
				continue;
			}
			
			int nextword_length_ok = checkWordLength(nextword);
			int uppercase_not_ok = checkUppercase(nextword);
			int nextword_ing_ok = checkEndingING(nextword);
			int nextword_firstlast_ok = matchFirstLastChar(curword, nextword);
			int usedword_not_ok = checkWordList(wordList, nextword);
			
			if ((nextword_length_ok == 1) && (uppercase_not_ok == 0) && (nextword_ing_ok == 1) && (nextword_firstlast_ok == 1) && (usedword_not_ok == 0)){

				roundScore = scoringSystem(nextword);
				player_scores[(round+1) % 2] += roundScore;

				add_node_to_list(wordList, get_new_node(nextword));

				strcpy(curword, nextword);
				
				validword = 1;

				round++;

				system("clear");

				break;

			} else {

				system("clear");
				validword = 0;
				printf("\n Oops, '%s' is an invalid word!\n", nextword);

				if (nextword_length_ok != 1) {
					printf("\n  -  The word is too short.");
				}
				if (uppercase_not_ok == 1) {
					printf("\n  -  The new word contains uppercase characters.");
				}
				if (nextword_ing_ok != 1) {
					printf("\n  -  The word is ends with 'ing', which is not allowed.");
				}
				if (nextword_firstlast_ok != 1) {
					printf("\n  -  The last letter of the previous word did not");
					printf("\n     match the first letter of the new word.");
				}
				if (usedword_not_ok == 1) {
					printf("\n  -  The new word has already been used before for");
					printf("\n     this game session.");
				}

				printf("\n\n [!] %s received a penalty of -50 points.", pname[(round+1) % 2]);
				player_scores[(round+1) % 2] -= 50;

				if (invalidcount > 1) {
					printf("\n [!] %s, you have %d tries left for this turn.\n", pname[(round+1) % 2], invalidcount);
					invalidcount--;
				} else if (invalidcount == 1) {
					printf("\n [!] %s, you have 1 try left for this turn.\n", pname[(round+1) % 2]);
					invalidcount--;
				} else {
					printf("\n   %s entered 3 invalid words in a row and the game is over!\n", pname[(round+1) % 2]);
					forcequit = 1;
					break;
				}

			}
		} //End of For Loop

		if (forcequit == 1) {
			break;
		}

	} // End of For Loop

	sleep(2);
	system("clear");

	printf("\n Final score at round %4d:\n",(round+1)/2);
	printf(" %s's Score:\t%3d\n %s's Score:\t%3d\n\n",pname[0],player_scores[0],pname[1],player_scores[1]);

	if (player_scores[0] > player_scores[1]) {
		printf("\n |====================================|\n");
		printf(" |   We got a ChainyWords winner!!!   |\n");
		printf(" |====================================|\n");
		printf("\n %s wins %s with a %3d point difference! Congratulations!\n", pname[0], pname[1], (player_scores[0]-player_scores[1]));
	} else if (player_scores[1] > player_scores[0]) {
		printf("\n |====================================|\n");
		printf(" |   We got a ChainyWords winner!!!   |\n");
		printf(" |====================================|\n");
		printf("\n %s wins %s with a %3d point difference! Congratulations!\n", pname[1], pname[0], (player_scores[1]-player_scores[0]));
	} else {
		printf("\n |====================================|\n");
		printf(" |     Two ChainyWords winners!!      |\n");
		printf(" |====================================|\n");
		printf("\n Woah! Both %s and %s have the same score! It's a tie!\n", pname[0], pname[1]);
	}

	//Free node memory
	freeNodesMem(wordList);

}


void optionone() {

	char again[1];

	// Loops the game until the player wishes to stop playing
	for (;;) {

		printf("\n             Loading game...\n\n\n");

		// Initialize randomizer and get dictionary
		srand(time(NULL));
		dictptr=get_new_dict();
		load_words_to_dict(dictptr, "wordlist.txt");

		system("clear");
		playgame();

  		// Free all dynamically allocated memory
		free_dict_mem(dictptr);

		printf("\n Do you wish to play again? (y/n): ");
		scanf("%s", again);

		if (strcmp(again,"n") == 0) {
			break;
		}
	}
}


void exitmenu() {

	system("clear");
	printf("\n\n |============================================|\n");
	printf(" |  Thanks for playing The ChainyWords Game!  |\n");
	printf(" |============================================|\n");
	printf("\n                Exiting game...\n\n");
	sleep(2);
	system("clear");
}


int main() {

	int option = 1;
	system("clear");

	for (;;) {
		printf("\n |====================================|\n");
		printf(" |  Welcome to The ChainyWords Game!  |\n");
		printf(" |====================================|\n");
		printf(" |          By Gerald & Zhao          |\n");
		printf("\n               Main Menu\n\n");
		printf("\n             1. Play game");
		printf("\n             2. Help menu");
		printf("\n             3. Exit game\n\n");
		printf("            Selection (1-3): ");
		scanf("%d", &option);

		if (option == 1) {
			optionone();
			exitmenu();
			break;
		} else if (option == 2) {
			showhelpmenu();
			continue;
		} else {
			exitmenu();
			break;
		}
		system("clear");
	}

	return 0;
}