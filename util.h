/* common header file for assignment 1 */
#define MAXWORD_LEN  35
#define MINWORD_LEN  6
typedef struct node{
	char word[MAXWORD_LEN] ; 
	struct node *  next;
} wordNode;
typedef wordNode * dict[26];  // an array of wordNode pointers (26 elements for 'a' to 'z'

/* util functions prototypes */
dict * get_new_dict();
void load_words_to_dict(dict * thisdict, char * filename);
void freeNodesMem(wordNode * onelist_ptr);
void free_dict_mem(dict * thisdict);
wordNode * get_new_node(char * new_word);
wordNode * add_node_to_list(wordNode * thisList, wordNode * thisNode);
void add_node_to_dict(dict * thisdict,wordNode * thisnode);
char * get_random_word(dict * this_dict);
char * get_nth_word_from_list(wordNode * thisList, int nth);
int get_list_size(wordNode * thisList);

