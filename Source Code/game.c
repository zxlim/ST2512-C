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

struct NodeStruct{

	char word[MAXWORD_LEN];

	struct NodeStruct * nextNode;

};

typedef struct NodeStruct Node;

void addNodeToList (Node* wordList, Node * newNode);
void debugPrintWordList (Node* wordList);
void freeWordList(Node* wordList);
Node * createNode(char * nextword);

dict * dictptr;

char * prompt_name(char * prompt_msg,char * newname) {
	printf("%s",prompt_msg);
	scanf("%s",newname);
	return newname;
}


Node * createNode(char * nextword) {

	Node* newNode = malloc(sizeof(Node));
	strcpy(newNode -> word, nextword);
	newNode -> nextNode = NULL;

	return newNode;
}


void addNodeToList(Node* wordList, Node * newNode) {

	Node* list = wordList;
	Node* tail = 0;
	
	while(list!= 0) {
		tail =  list;
		list = list -> nextNode;
	}	

	tail -> nextNode = newNode;	 
}

void debugPrintWordList(Node * wordList) {
	Node * list = wordList;

	while (list != NULL) {
		printf("\n [DEBUG] %s", list -> word);
		list = list -> nextNode;
	}

}

void freeWordList(Node* wordList) {

	Node* list = wordList;
	if (list == NULL) return;
	freeWordList(list -> nextNode);
}


int clean_stdin() {

	while (getchar() != '\n');

	return 1;
}

int get_word_element(char nextword[]){
	
	int index = nextword[0] - 'a';

	return index;
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
	printf("   [10 point]    a, e, i, o, u, l, n, s, t, r\n");
	printf("   [20 points]   d, g\n");
	printf("   [30 points]   b, c, m, p\n");
	printf("   [40 points]   f, h, v, w, y\n");
	printf("   [50 points]   k\n");
	printf("   [80 points]   j, x\n");
	printf("   [100 points]  q, z\n");
	printf("\n\n Scoring Penalties:\n\n");
	printf("  Doing the following actions will result in score reduction:\n");
	printf("   - Quitting the game midway (-500 points)\n");
	printf("   - Submitting an invalid word (-50 points)\n");
	printf("   - Submitting a word with uppercases:\n");
	printf("       + First time        (-50 points)\n");
	printf("       + Second time       (-100 points)\n");
	printf("       + Third time        (-200 points)\n");
	printf("       + Subsequent times  (-300 points)\n");
	printf("\n Press Enter to exit this help menu.\n ");
	scanf("%c", &dummy);
	system("clear");
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

int roundOption() {

	char dummy;
	int roundAmount;
	int roundchoice;
	int choicecorrect = 0;

	for (;;) {

		do {
			system("clear");
			printf("\n |====================================|\n");
			printf(" |  Welcome to The ChainyWords Game!  |\n");
			printf(" |====================================|\n");
			printf("                 2/2\n");
			printf("\n Number of Rounds\n");
			printf("\n 1. 25 Rounds");
			printf("\n 2. 60 Rounds");
			printf("\n 3. Endless Mode");
			printf("\n\n 4. Exit Game");
			printf("\n\n Selection (1-4): ");

		} while ((scanf("%d%c", &roundchoice, &dummy) != 2 || dummy != '\n') && clean_stdin());

		switch (roundchoice) {
			case 1:
			roundAmount = 26*2;
			choicecorrect = 1;
			break;
			case 2:
			roundAmount = 61*2;
			choicecorrect = 1;
			break;
			case 3:
			roundAmount = 0;
			choicecorrect = 1;
			break;
			case 4:
			roundAmount = -1;
			choicecorrect = 1;
			break;
			default:
			printf("\n Invalid choice. Please try again.\n");
			sleep(2);
		}

		if (choicecorrect == 1) {
			break;
		}

	}

	return roundAmount;
}


int scoringSystem(char nextword[], int totalupperconvert, int converted_lower_ok) {

	int nextword_length = strlen(nextword);
	int i = 0;
	int roundPoints = 0;

	system("clear");

	printf("\n\n\n");
	if (converted_lower_ok == 1) {
		if (totalupperconvert == 1) {

			printf("\n  \xF0\x9F\x98\xB1  The game has detected uppercase letter(s).\n");
			sleep(2);
			printf("\n\n  Luckily for you, the creators are kind\n  and have converted it for you.\n");
			sleep(2);
			printf("\n  But as the saying goes, if you're good at\n  something never do it for free. So there goes 50 points.\n");		
			sleep(3);

		} else if (totalupperconvert == 2) {

			printf("\n  \xF0\x9F\x98\xB1  Once again! You have entered uppercase letter(s).\n");
			sleep(2);
			printf("\n  We did it for you again but this time it's at double the cost.\n");
			sleep(3);

		} else if (totalupperconvert == 3) {

			printf("\n  \xF0\x9F\x98\x95  Really? Again? That's it!\n");
			sleep(2);
			printf("\n  Say goodbye to 200 points. That'll teach you a lesson.\n");
			sleep(3);

		} else if (totalupperconvert > 3) {

			printf("\n  \xF0\x9F\x98\x94  ....\n");
			sleep(1);
			printf("\n  We give up, say goodbye to 300 points. ");
			sleep(2);

		}
	}

	printf("\n\n  Points distribution for word '%s':\n\n", nextword);

	for (i = 0; i < nextword_length; i++) {

		char wordchar;
		wordchar = nextword[i];

		if (wordchar == 'a' || wordchar == 'e' || wordchar == 'i' || wordchar == 'o' || wordchar == 'u' || wordchar == 'l' || wordchar == 'n' || wordchar == 's' || wordchar == 't' || wordchar == 'r'){
			printf("  Letter \"%c\" gets 10 point!\n", wordchar);
			roundPoints += 10;
		} else if (wordchar == 'd' || wordchar == 'g') {
			printf("  Letter \"%c\" gets 20 points!\n", wordchar);	
			roundPoints += 20;
		} else if (wordchar == 'b' || wordchar == 'c' || wordchar == 'm' || wordchar == 'p' ) {
			printf("  Letter \"%c\" gets 30 points!\n", wordchar);
			roundPoints += 30;
		} else if (wordchar == 'f' || wordchar == 'h' || wordchar == 'v' || wordchar == 'w' 	|| wordchar == 'y') {
			printf("  Letter \"%c\" gets 40 points!\n", wordchar);
			roundPoints += 40;
		} else if (wordchar == 'k') {
			printf("  Letter \"%c\" gets 50 points!\n", wordchar);
			roundPoints += 50;
		} else if (wordchar == 'j' || wordchar == 'x') {
			printf("  Letter \"%c\" gets 80 points!\n", wordchar);
			roundPoints += 80;
		} else if (wordchar == 'q' || wordchar == 'z') {
			printf("  Letter \"%c\" gets 100 points!\n", wordchar);
			roundPoints += 100;
		}
	} //End of For loop

	printf("\n\n  Calculating score...\n");
	sleep(2);


	printf("\n  Total points: %d \n", roundPoints);
	sleep(2);

	if (converted_lower_ok == 1) {

		switch(totalupperconvert) {
			case 1:
			roundPoints -= 50;
			break;
			case 2:
			roundPoints -= 100;
			break;
			case 3:
			roundPoints -= 200;
			break;
			default:
			roundPoints -= 300;
			break;
		}

		printf("\n  Wait! Almost forgot the points you lost.\n");
		printf("\n  Calculating ACTUAL score...\n");
		sleep(2);
		printf("\n  Final points: %d \n", roundPoints);
		sleep(2);
	} 

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

int checkSpecialChar(char nextword[]) {

	int specialchar_not_ok = 0;
	int i;

	for (i = 0; i < strlen(nextword); i++) {
		if (!isalpha(nextword[i])) {
			specialchar_not_ok = 1;
			break;
		}
	}

	return specialchar_not_ok;
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


int convertUppertoLower(char nextword[]){

	//printf("\n [DEBUG] Converting uppercase to lowercase...");
	int i;

	for( i = 0; i <= strlen(nextword); i++ ) {
		if (isupper(nextword[i])) {
			nextword[i] = nextword[i] + 32;
		}
	}

	int converted_lower_ok = 1;
	//printf("\n [DEBUG] Conversion complete: %s", nextword);

	return converted_lower_ok;
}


int checkEndingING(char nextword[]) {

	int i;
	int nextword_ing_ok = 0;
	char lastthreechar[3];
	const char notallowed[] = "ing";

	for (i = 0; i < 3; i++) {
		lastthreechar[i] = nextword[strlen(nextword) - (3 - i)];
	}

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


int checkWordList(Node * wordList, char * nextword) {

	int usedword_not_ok;
	Node * list = wordList;

	while (list != 0) {
		if (strcmp(list -> word, nextword) == 0) {
			usedword_not_ok = 1;
			break;
		}

		list = list -> nextNode;
	}

	return usedword_not_ok;
}


int checkDictList(char nextword[1]) {

	wordNode * target_list;

	int nextword_indict_ok = 0;
	char firstchar[2];
	int index = 26;

	index = get_word_element(nextword);

	//printf("\n [DEBUG] index: %d\n", index);

	target_list = (*dictptr)[index];

	//Adding the first character of nextword to firstchar
	sprintf(firstchar, "%c" , nextword[0]); 
	firstchar[1] = '\0';

	//printf("\n [DEBUG] firstchar: %s\n", firstchar);

	wordNode * cur_ptr;

	cur_ptr = target_list;

	for(;;) {
		if (cur_ptr == NULL) {
			//Word does not exist
			nextword_indict_ok = 0;
			break;
		}
		if ( strcmp( cur_ptr -> word, nextword ) == 0 ){
			//Check word from dictionary 
			//If 0, word is in dictionary
			nextword_indict_ok = 1; 
			break;
		}

     	cur_ptr = cur_ptr->next; //Move on the next word
     }

     return nextword_indict_ok;
 }


 void playgame() {
 	int roundScore;
 	int validword = 0;
 	int round = 1;
 	int totalupperconvert = 0;
 	int roundamount = 501;
 	int forcequit = 0;
 	int player_scores[2]= {0,0};
 	char dummy;
 	char pname[2][MAXNAME_LEN];
 	char curword[MAXWORD_LEN];
 	char nextword[MAXWORD_LEN];

 	Node * wordList;

 	strcpy(curword, get_random_word(dictptr));
 	wordList = createNode(curword);

 	printf("\n |====================================|\n");
 	printf(" |  Welcome to The ChainyWords Game!  |\n");
 	printf(" |====================================|\n");
 	printf("                 1/2\n");
 	printf("\n Choose your names (Maximum 35 letters)\n");
 	strcpy(pname[0],prompt_name("\n Name of Player 1: ",pname[0]));
 	strcpy(pname[1],prompt_name(" Name of Player 2: ",pname[1]));

 	roundamount = roundOption();

 	if (roundamount == -1) {
 		return;
 	}

 	printf("\n Initializing game session...\n");

 	sleep(2);
 	system("clear");

 	for (;round != roundamount;) {

 		int invalidcount = 3;

 		//debugPrintWordList(wordList);

 		for (;;) {

 			printf("\n |====================================|\n");
 			printf(" |            Round   %4d            |\n", (round+1)/2);
 			printf(" |====================================|\n");
 			printf("\n %s's Score:   %3d\n %s's Score:   %3d\n", pname[0],player_scores[0],pname[1],player_scores[1]); 

 			if (roundScore > 0 && validword == 1 && strcmp(nextword,"h") != 0 && strcmp(nextword,"q") != 0) {
 				printf("\n %s have obtained %d points for the word \"%s\"\n", pname[round%2], roundScore, nextword);
 			}

 			printf("\n The current word is:\t%s\n\n", curword);

 			printf(" (Enter 'q' to quit the game or 'h' for the help menu)");
 			printf("\n %s, enter the next word: ", pname[(round+1)%2]);
 			scanf("%s%c", nextword, &dummy);

 			if (strcmp(nextword,"q") == 0) {
 				char confirmQuit[] = "n";
 				printf("\n Are you sure you want to quit the game?");
 				printf("\n 500 points will be deducted! (Y/n): ");
 				scanf("%s", confirmQuit);

 				if (strcmp(confirmQuit,"Y") == 0) {

 					printf("\n %s decided to quit the game.\n", pname[(round+1) % 2]);
 					printf("\n %s received a penalty of -500 points.\n", pname[(round+1) % 2]);
 					player_scores[(round+1) % 2] -= 500;
 					forcequit = 1;
 					break;

 				} else {

 					system("clear");
 					continue;
 				}
 			}

 			if (strcmp(nextword,"h") == 0) {

 				showhelpmenu();
 				continue;
 			}

 			if (strcmp(nextword,"h") != 0 && strcmp(nextword,"q") != 0) {

 				int converted_lower_ok = 0;
 				int nextword_length_ok = checkWordLength(nextword);
 				int specialchar_not_ok = checkSpecialChar(nextword);
 				int uppercase_not_ok = checkUppercase(nextword);

 				if (uppercase_not_ok != 0){
 					converted_lower_ok = convertUppertoLower(nextword);
 				}

 				int nextword_ing_ok = checkEndingING(nextword);
 				int nextword_firstlast_ok = matchFirstLastChar(curword, nextword);
 				int usedword_not_ok = checkWordList(wordList, nextword);
 				int nextword_indict_ok = checkDictList(nextword);

 				if ((nextword_length_ok == 1) && (specialchar_not_ok == 0) && (uppercase_not_ok == 0 || converted_lower_ok == 1) && (nextword_ing_ok == 1) && (nextword_firstlast_ok == 1) && (usedword_not_ok == 0) && (nextword_indict_ok == 1)){

 					if (converted_lower_ok == 1) {
 						totalupperconvert++;
 					}

 					roundScore = scoringSystem(nextword, totalupperconvert, converted_lower_ok);
 					player_scores[(round+1) % 2] += roundScore;

 					addNodeToList(wordList, createNode(nextword));

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
 					if (specialchar_not_ok == 1) {
 						printf("\n  -  The word contains numbers or special characters.");
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
 					if (nextword_indict_ok != 1) {
 						printf("\n  -  The word does not exist in the internal dictionary.");
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
 			}
		} //End of For Loop

		if (forcequit == 1) {
			break;
		}

	} // End of For Loop

	sleep(2);
	system("clear");

	printf("\n Final score at round %4d:\n",(round+1)/2);
	printf(" %s's Score:   %3d\n %s's Score:   %3d\n\n",pname[0],player_scores[0],pname[1],player_scores[1]);

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
	freeWordList(wordList);

}


void loadgame() {

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


int main() {

	char dummy;
	int option;
	int forcequit = 0;
	
	for (;;) {

		do {

			system("clear");
			printf("\n |====================================|\n");
			printf(" |  Welcome to The ChainyWords\xE2\x84\xA2 Game! |\n");
			printf(" |====================================|\n");
			printf(" |          By Gerald & Zhao          |\n");
			printf("\n               Main Menu\n\n");
			printf("\n             1. Play game");
			printf("\n             2. Help menu");
			printf("\n             3. Exit game\n\n");
			printf("            Selection (1-3): ");

		} while ((scanf("%d%c", &option, &dummy) != 2 || dummy != '\n') && clean_stdin());

		switch (option) {
			case 1:
			loadgame();
			exitmenu();
			forcequit = 1;
			break;
			case 2:
			showhelpmenu();
			continue;
			case 3:
			exitmenu();
			forcequit = 1;
			break;
			default:
			printf("\n\n  \xE2\x83\xA0 Invalid choice. Please try again.\n");
			sleep(2);
		}

		if (forcequit == 1) {
			break;
		}
	}

	return 0;
}