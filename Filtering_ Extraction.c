#include"sets_operations.h"
#include"Trie_machine_abstract.h"
#include<string.h>

void help_travers_num(Trie_node* node , int* cpt ) {
    if (node == NULL){
        return;
    }
    if (node->is_end_of_word == true){
        (*cpt)++;
    }
    for (int j = 0 ; j < 26 ; j++){
        if (node->children[j] != NULL){
            help_travers_num(node->children[j] , cpt );
        }
    }
}

int num_of_words(Trie* A){
    if (A == NULL || A->Root == NULL){
        return 0;
    }
    int cpt = 0;
    help_travers_num(A->Root, &cpt);
    return cpt;
}
double calculateJaccard(Trie* a, Trie* b){
    Trie* unionn = union_a_b(a , b);
    Trie* inter = intersection(a , b);
    int n1 = num_of_words(inter);
    int n2 = num_of_words(unionn);
    if (n2 == 0){
        free_Trie(unionn);
        free_Trie(inter);
        return 0.0;
    }
    double result = (double)n1 / (double)n2;
    free_Trie(unionn);
    free_Trie(inter);
    return result;
    
}

void* remove_stopwords(Trie* trie){
   if (trie == NULL || trie->Root == NULL){
    return NULL;
   } 
   Trie_node* curr = trie->Root;
   const char *stopwords[] = {
            "the", "is", "at", "which", "a", "an", "and", "or", "but", "in", 
            "on", "to", "for", "with", "about", "as", "by", "of", "from", "that", "this"
        };
        int num_stopwords = sizeof(stopwords) / sizeof(stopwords[0]);
        for (int i = 0; i < num_stopwords; i++) {
            delete_word(trie, stopwords[i]);
        }
    
}


void* remove_conjunctions(Trie* trie){
   if (trie == NULL || trie->Root == NULL){
    return NULL;
   } 
   Trie_node* curr = trie->Root;
        const char *conjunctions[] = {
            "however", "therefore", "moreover", "thus", "hence", "nevertheless", 
            "furthermore", "although", "because", "since", "unless", "while"
        };
        int num_conjunctions = sizeof(conjunctions) / sizeof(conjunctions[0]);
        for (int i = 0; i < num_conjunctions; i++) {
            delete_word(trie, conjunctions[i]);
        }
    
    
}

void* remove_pronouns(Trie* trie){
   if (trie == NULL || trie->Root == NULL){
    return NULL;
   } 
   Trie_node* curr = trie->Root;
        const char *pronouns[] = {
            "he", "she", "they", "it", "i", "we", "you", "me", "him", "her", 
            "us", "them", "my", "your", "his", "their", "its", "our", "mine", 
            "yours", "hers", "theirs", "ours"
        };
        int num_pronouns = sizeof(pronouns) / sizeof(pronouns[0]);
        for (int i = 0; i < num_pronouns; i++) {
            delete_word(trie, pronouns[i]);
        }
    
}

int check_similarity(Trie* a ,Trie* b){
    if (a == NULL || a->Root == NULL || b == NULL || b->Root == NULL ) {
        return 0;
    }
    remove_conjunctions(a);
    remove_pronouns(a);
    remove_stopwords(a);
    remove_conjunctions(b);
    remove_pronouns(b);
    remove_stopwords(b);
    return calculateJaccard(a , b);
    
}

char* topic(Trie* trie){
    if (trie == NULL || trie->Root == NULL){
    return NULL;
   } 
    remove_conjunctions(trie);
    remove_pronouns(trie);
    remove_stopwords(trie);
    return most_common_roots(trie);
}

Trie_node* go_to(Trie* trie , char* root){
    if(trie== NULL || trie->Root == NULL){
        return NULL;
    }
    Trie_node* curr = trie->Root;
    int index;
    int size = strlen(root);
    for (int i = 0 ; i< size ; i++ ){
        index = root[i] - 'a';
        if (curr->children[index] == NULL){
            return NULL;
        }
        else {
            curr = curr->children[index];
        }
    }
    return curr;
}

void help_travers_2(Trie_node* node , char*word , int i , char** res ,int* k) {
    if (node == NULL){
        return;
    }
    word[i] = '\0';
    if (node->is_end_of_word == true){
        res[(*k)++] = strdup(word);
    }
    for (int j = 0 ; j < 26 ; j++){
        if (node->children[j] != NULL){
            word[i] = 'a'+j;
            help_travers_2(node->children[j] , word , i+1 , res , k);
        }
    }
}

char** words_start_with(Trie* trie , char* s ){
    char** words = malloc(sizeof(char*) * 100);
    if(trie== NULL || trie->Root == NULL){
        free(words);
        return NULL;
    }
    Trie_node* node = go_to(trie, s);
    if (node == NULL) {
        free(words);
        return NULL; 
    }
    int k = 0;
    char word[256];
    strcpy(word, s); 
    int size = strlen(s);    
    help_travers_2(node, word ,size , words , &k);
    return words;

}

void helper_count(Trie_node* node , int* cpt){
    if (node == NULL){
        return;
    }
    for (int i = 0 ; i <26 ; i++){
        if(node->children[i]!= NULL){
            helper_count(node->children[i] , cpt) ;
        }
    }
    if (node->is_end_of_word){
        (*cpt)++;
    }
}

int countPrefixMatches(Trie* trie , char prefix){
     if(trie== NULL || trie->Root == NULL){
        return NULL;
    }
    Trie_node* node = go_to(trie, prefix);
    if (node == NULL) {
        return NULL; 
    }
    int cpt = 0;
    helper_count(node , &cpt);
    return cpt;
}