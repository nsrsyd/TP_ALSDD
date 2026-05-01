#include"sets_operations.c"
void help_travers(Trie_node* node , char*word , int i , char** res ,int* k) ;
char** travers_Trie(Trie* trie , int* k );
Trie* union_a_b(Trie* t1, Trie* t2);
void help_travers_inter(Trie_node* node1 , Trie_node* node2 , char*word , int i , char** res ,int* k);
char** travers_Trie_inter(Trie* trie1 ,Trie* trie2 , int* k );
Trie* intersection(Trie* t1, Trie* t2);
void help_travers_diff(Trie* trie,Trie_node* node1 , Trie* b, char*word , int i );
Trie* difference(Trie* t1, Trie* t2);
void help_travers_copy(Trie* trie,Trie_node* node , char*word , int i ) ;
Trie* copy_trie(Trie* trie);