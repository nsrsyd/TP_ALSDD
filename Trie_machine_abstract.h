#include"Trie_functions.c"
Trie* create_trie();   
void prep_trie_node(Trie_node* node);
Trie_node* create_trie_node();
void insert(Trie* trie ,char* s);
bool search (Trie* trie , char* s);
bool has_children(Trie_node* node);
Trie_node* help_delete_word(Trie_node* root, char* s, int i);
void delete_word(Trie_node** root, char* s);
void help_free_trie(Trie_node* node);
void free_Trie(Trie* trie);
bool start_with (Trie* trie , char* s);
void help_travers_most_common(Trie_node* node1 , char*word , int i , char** res ,int* k);
char* most_common_roots(Trie* trie);
