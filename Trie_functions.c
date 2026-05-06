#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Trie_node{
    struct Trie_node* children[26];
    bool is_end_of_word;
}Trie_node;

typedef struct Trie{
    Trie_node* Root;
}Trie;


Trie* create_trie(){
    Trie* trie = malloc(sizeof(Trie));
    trie->Root = create_trie_node();
    return trie;
}
void prep_trie_node(Trie_node* node){
    node->is_end_of_word = 0;
    for (int i = 0 ; i<26 ; i++) {
        node->children[i] = NULL;
    }
}
Trie_node* create_trie_node(){
    Trie_node* node = malloc(sizeof(Trie_node));
    prep_trie_node(node);
    return node;
}

void insert(Trie* trie ,char* s){
    if (!(trie->Root) || !(*s)) {
        return ;
    }
    Trie_node* root = trie->Root;
    Trie_node* curr = root;
    int size = strlen(*s);
    int index;
    for (int i = 0 ; i<size ; i++){
        index = s[i]-'a';
        if (curr->children[index] == NULL){
            Trie_node* node = create_trie_node();
            curr->children[index] = node;
        }
        curr = curr->children[index];
    }
    curr->is_end_of_word = true;
    return;
}

bool search (Trie* trie , char* s){
    if (!(trie->Root) || !(*s)) {
        return false;
    }
    Trie_node* root = trie->Root;
    Trie_node* curr = root;
    int size = strlen(*s);
    int index;
    for (int i = 0 ; i<size ; i++){
        index = s[i]-'a';
        if (curr->children[index] == NULL){
            return false;
        }
        curr = curr->children[index];
        }
        if (curr->is_end_of_word == true){
            return true;
        }
        return false;
}

bool has_children(Trie_node* node){
    if (node == NULL){
        return false;
    }
    for (int i = 0 ; i<26 ;i++){
        if (node->children[i]!= NULL) {
            return true;
        }
    }
    return false;
}

Trie_node* help_delete_word(Trie_node* root, char* s, int i) {
    if (!root) return NULL;

    if (s[i] == '\0') {
        if (root->is_end_of_word) {
            root->is_end_of_word = false;
        }

        if (!has_children(root)) {
            free(root);
            return NULL; 
        }
        return root;
    }

    int index = s[i] - 'a';
    root->children[index] = help_delete_word(root->children[index], s, i + 1);

    
    if (!has_children(root) && !root->is_end_of_word) {
        free(root);
        return NULL;
    }

    return root;
}

void delete_word(Trie_node** root, char* s) {
    *root = help_delete_word(*root, s, 0);
}

void help_free_trie(Trie_node* node){
    if (node == NULL){
        return;
    }
    for (int i = 0 ; i<26 ; i++) {
        if (node->children[i] != NULL) {
            help_free_trie(node->children[i]);
        }    }
    free(node);
    return;

}

void free_Trie(Trie* trie){
    if (trie == NULL || !trie->Root){
        return;
    }
    help_free_trie(trie->Root);
    free(trie);
    return;
}


bool start_with (Trie* trie , char* s){
    if (trie == NULL || trie->Root == NULL || s == NULL) {
        return false;
    }
    Trie_node* curr = trie->Root;
    int index ;
    for (int i = 0 ; s[i] != '\0' ; i++)
    {
        index = s[i] - 'a';
        if (curr->children[index] == NULL){
            return false;
        }
        curr = curr->children[index];

    }
    return true;
}


void help_travers_most_common(Trie_node* node1 , char*word , int i , char** res ,int* k) {
    if (node1 == NULL ){
        return ;
    }
    word[i] = '\0';
    if ((node1->is_end_of_word == true) ){
        res[(*k)++] = strdup(word);
        return;
    }
    for (int j = 0 ; j < 26 ; j++){
        if ((node1->children[j] != NULL)){
            word[i] = 'a'+j;
            help_travers_most_common(node1->children[j] , word , i+1 , res , k);
        }
    }
}

char* most_common_roots(Trie* trie){
    if (trie == NULL || trie->Root == NULL ) {
        return NULL;
    }
    Trie_node* curr = trie->Root;
    char* words [1000];
    char word[100];
    help_travers_most_common(curr , word , 0 , words , 0);
}


void help_print_words(Trie_node* root , char* word , int j){
    if(root == NULL){
        return;
    }
    word[j]='\0';
    if(root->is_end_of_word){
    printf(" %s " , word);
    }
    for (int i = 0 ; i < 26 ; i++){
        if (root->children[i] != NULL){
            word[j] = 'a'+i;
            help_print_words(root->children[i] , word , j+1);
        }
    }

}
void print_words(Trie* trie) {
    if(trie == NULL || trie->Root == NULL){
        return;
    }
    char word[100];
    printf("{ ");
    help_print_words(trie->Root , word ,0);
    printf(" }");
}
