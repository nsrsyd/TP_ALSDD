#include"Trie_machine_abstract.h"

void help_travers(Trie_node* node , char*word , int i , char** res ,int* k) {
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
            help_travers(node->children[j] , word , i+1 , res , k);
        }
    }
}

char** travers_Trie(Trie* trie , int* k ) {
    if (trie == NULL || trie->Root == NULL){
        return NULL;
    }
    char** res = malloc(100000 * sizeof(char*));
    char word[100];
    help_travers(trie->Root , word , 0 , res , k);
    return res;
}

Trie* union_a_b(Trie* t1, Trie* t2)
{
    Trie* new_trie = create_trie();
    int k1 = 0;
    int k2 = 0;
    char** list1 = travers_Trie(t1 , &k1);
    char** list2 = travers_Trie(t2 , &k2);
    for (int i = 0 ; i<k1 ;i++ ){
        insert(new_trie , list1[i]);
        free(list1[i]);
    }
    free(list1);
    for (int i = 0 ; i<k2 ;i++ ){
        insert(new_trie , list2[i]);
        free(list2[i]);
    }
    free(list2);


    return new_trie;  
} 


void help_travers_inter(Trie_node* node1 , Trie_node* node2 , char*word , int i , char** res ,int* k) {
    if (node1 == NULL || node2 == NULL){
        return ;
    }
    word[i] = '\0';
    if ((node1->is_end_of_word == true) && (node2->is_end_of_word == true)){
        res[(*k)++] = strdup(word);
    }
    for (int j = 0 ; j < 26 ; j++){
        if ((node1->children[j] != NULL)&& (node2->children[j] != NULL)){
            word[i] = 'a'+j;
            help_travers_inter(node1->children[j] , node2->children[j], word , i+1 , res , k);
        }
    }
}

char** travers_Trie_inter(Trie* trie1 ,Trie* trie2 , int* k ) {
    if (trie1 == NULL || trie1->Root == NULL || trie2 == NULL  || trie2->Root == NULL){
        return NULL;
    }
    char** res = malloc(100000 * sizeof(char*));
    char word[100];
    help_travers_inter(trie1->Root , trie2->Root , word , 0 , res , k);
    return res;
}


Trie* intersection(Trie* t1, Trie* t2)
{
    Trie* new_trie = create_trie();
    int k1 = 0;
    char** list = travers_Trie_inter(t1 ,t2 , &k1);
    if (list != NULL){
    for (int i = 0 ; i<k1 ;i++ ){
        insert(new_trie , list[i]);
        free(list[i]);
    } 
}
    free(list);
    return new_trie;

}




void help_travers_diff(Trie* trie,Trie_node* node1 , Trie* b, char*word , int i ) {
    if (node1 == NULL){
        return ;
    }
    word[i] = '\0';
    if ((node1->is_end_of_word == true)){
        if (!search(b , word)) {
            insert(trie,word);
        }
    }
    for (int j = 0 ; j < 26 ; j++){
        if (node1->children[j] != NULL){
            word[i] = 'a'+j;
            help_travers_diff( trie,node1->children[j] , b, word , i+1 );
        }
    }
}



Trie* differance(Trie* t1, Trie* t2)
{
    if (t1 == NULL || t1->Root == NULL) return create_trie();
    Trie* new_trie = create_trie();
    char word [100];
    help_travers_diff(new_trie , t1->Root , t2 ,word , 0);
    return new_trie;

}



void help_travers_copy(Trie* trie,Trie_node* node , char*word , int i ) {
    if (node == NULL){
        return;
    }
    word[i] = '\0';
    if (node->is_end_of_word == true){
        insert(trie , word);
    }
    for (int j = 0 ; j < 26 ; j++){
        if (node->children[j] != NULL){
            word[i] = 'a'+j;
            help_travers_copy(trie,node->children[j] , word , i+1 );
        }
    }
}

Trie* copy_trie(Trie* trie){
    if (trie == NULL || trie->Root == NULL) return create_trie();
    Trie* new_trie = create_trie();
    char word [100];
    help_travers_copy(new_trie , trie->Root , word , 0);
    return new_trie;
}
