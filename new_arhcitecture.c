#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef struct Trie_node{
    struct Trie_node* children[30];
    bool is_end_of_sentence;
    int order;
}Trie_node;

typedef struct Trie{
    Trie_node* Root;
}Trie;

void prep_trie_node(Trie_node* node){
    node->is_end_of_sentence = false;
    node->order = 0;
    for (int i = 0 ; i<30 ; i++) {
        node->children[i] = NULL;
    }
}


Trie_node* create_trie_node(){
    Trie_node* node = malloc(sizeof(Trie_node));
    prep_trie_node(node);
    return node;
}

Trie* create_trie(){
    Trie* trie = malloc(sizeof(Trie));
    trie->Root = create_trie_node();
    return trie;
}

int get_index(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a'; 
    if (c == ' ') return 26;
    if (c == ',') return 27;
    if (c == ';') return 28;
    if (c == ':') return 29;
    return -1; 
}

void insert(Trie* trie ,char* s , int order){
    if (!(trie->Root) || !(*s)) {
        return ;
    }
    Trie_node* root = trie->Root;
    Trie_node* curr = root;
    int size = strlen(*s);
    int index;
    for (int i = 0 ; i<size ; i++){
        index =get_index(s[i]);
        if (curr->children[index] == NULL){
            Trie_node* node = create_trie_node();
            curr->children[index] = node;
        }
        curr = curr->children[index];
    }
    curr->is_end_of_sentence = true;
    curr->order = order;
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
        index = get_index(s[i]);
        if (curr->children[index] == NULL){
            return false;
        }
        curr = curr->children[index];
        }
    if (curr->is_end_of_sentence == true){
            return true;
        }
    return false;
}

bool has_children(Trie_node* node){
    if (node == NULL){
        return false;
    }
    for (int i = 0 ; i<30 ;i++){
        if (node->children[i]!= NULL) {
            return true;
        }
    }
    return false;
}

Trie_node* help_delete_sentence(Trie_node* root, char* s, int i) {
    if (!root) return NULL;

    if (s[i] == '\0') {
        if (root->is_end_of_sentence) {
            root->is_end_of_sentence = false;
        }

        if (!has_children(root)) {
            free(root);
            return NULL; 
        }
        return root;
    }

    int index = get_index(s[i]);
    root->children[index] = help_delete_sentence(root->children[index], s, i + 1);

    if (!has_children(root) && !root->is_end_of_sentence) {
        free(root);
        return NULL;
    }

    return root;
}

void delete_sentence(Trie_node** root, char* s) {
    *root = help_delete_sentence(*root, s, 0);
}

void help_free_trie(Trie_node* node){
    if (node == NULL){
        return;
    }
    for (int i = 0 ; i<30 ; i++) {
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
        index = get_index(s[i]);
        if (curr->children[index] == NULL){
            return false;
        }
        curr = curr->children[index];

    }
    return true;
}



void help_print_sentence(Trie_node* root , char* sentence , int j){
    if(root == NULL){
        return;
    }
    if(root->is_end_of_sentence){
    sentence[j]='\0';
    printf(" %s " , sentence);
    }
    for (int i = 0 ; i < 30 ; i++){
        if (root->children[i] != NULL){
            if( 0<= i && i< 26 ) {
                sentence[j] = 'a'+i;
            }
            else if (i == 26){
                sentence[j] = ' ';
            }
            else if( i == 27){
                sentence[j] = ',';
            }
            else if (i == 28){
                sentence[j] = ';';
            }
            else if (i == 29){
                sentence[j] = ':';
            }
            help_print_sentence(root->children[i] , sentence , j+1);
        }
    }

}
void print_sentences(Trie* trie) {
    if(trie == NULL || trie->Root == NULL){
        return;
    }
    char sentence[1000];
    printf("{ ");
    help_print_sentence(trie->Root , sentence ,0);
    printf(" }");
}



// ------------------------------ sets_operations ---------------------------- //



void help_travers(Trie_node* node , char*sentence , int i , char** res ,int* k) {
    if (node == NULL){
        return;
    }
    if (node->is_end_of_sentence == true){
        sentence[i] = '\0';
        res[(*k)++] = strdup(sentence);
    }
    for (int j = 0 ; j < 30 ; j++){
        if (node->children[j] != NULL){
          if( 0<= i && i< 26 ) {
                sentence[j] = 'a'+i;
            }
            else if (i == 26){
                sentence[j] = ' ';
            }
            else if( i == 27){
                sentence[j] = ',';
            }
            else if (i == 28){
                sentence[j] = ';';
            }
            else if (i == 29){
                sentence[j] = ':';
            }
            help_travers(node->children[j] , sentence , i+1 , res , k);
        }
    }
}

char** travers_Trie(Trie* trie , int* k ) {
    if (trie == NULL || trie->Root == NULL){
        return NULL;
    }
    char** res = malloc(100000 * sizeof(char*));
    char sentence[1000];
    help_travers(trie->Root , sentence , 0 , res , k);
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
        insert(new_trie , list1[i] , i);
        free(list1[i]);
    }
    free(list1);
    for (int i = 0 ; i<k2 ;i++ ){
        insert(new_trie , list2[i] , i+k1);
        free(list2[i]);
    }
    free(list2);


    return new_trie;  
} 



void help_travers_inter(Trie_node* node1 , Trie_node* node2 , char*sentence , int i , char** res ,int* k) {
    if (node1 == NULL || node2 == NULL){
        return ;
    }
    if ((node1->is_end_of_sentence == true) && (node2->is_end_of_sentence == true) && (node1->order == node2->order)){
        sentence[i] = '\0';
        res[(*k)++] = strdup(sentence);
    }
    for (int j = 0 ; j < 30 ; j++){
        if ((node1->children[j] != NULL)&& (node2->children[j] != NULL)){
            if( 0<= i && i< 26 ) {
                sentence[j] = 'a'+i;
            }
            else if (i == 26){
                sentence[j] = ' ';
            }
            else if( i == 27){
                sentence[j] = ',';
            }
            else if (i == 28){
                sentence[j] = ';';
            }
            else if (i == 29){
                sentence[j] = ':';
            }
            help_travers_inter(node1->children[j] , node2->children[j], sentence , i+1 , res , k);
        }
    }
}

char** travers_Trie_inter(Trie* trie1 ,Trie* trie2 , int* k ) {
    if (trie1 == NULL || trie1->Root == NULL || trie2 == NULL  || trie2->Root == NULL){
        return NULL;
    }
    char** res = malloc(100000 * sizeof(char*));
    char sentence[100];
    help_travers_inter(trie1->Root , trie2->Root , sentence , 0 , res , k);
    return res;
}


Trie* intersection(Trie* t1, Trie* t2)
{
    Trie* new_trie = create_trie();
    int k1 = 0;
    char** list = travers_Trie_inter(t1 ,t2 , &k1);
    if (list != NULL){
    for (int i = 0 ; i<k1 ;i++ ){
        insert(new_trie , list[i] , i);
        free(list[i]);
    } 
}
    free(list);
    return new_trie;

}


void help_travers_diff(Trie* trie,Trie_node* node1 , Trie* b, char*sentence , int i , int*cpt) {
    if (node1 == NULL){
        return ;
    }
    if ((node1->is_end_of_sentence == true)){
        if (!search(b , sentence)) {
            sentence[i] = '\0';
            insert(trie,sentence , *cpt);
            (*cpt)++;
        }
    }
    for (int j = 0 ; j < 30 ; j++){
        if (node1->children[j] != NULL){
            if( 0<= i && i< 26 ) {
                sentence[j] = 'a'+i;
            }
            else if (i == 26){
                sentence[j] = ' ';
            }
            else if( i == 27){
                sentence[j] = ',';
            }
            else if (i == 28){
                sentence[j] = ';';
            }
            else if (i == 29){
                sentence[j] = ':';
            }
            help_travers_diff( trie,node1->children[j] , b, sentence , i+1 , cpt );
        }
    }
}



Trie* differance(Trie* t1, Trie* t2)
{
    if (t1 == NULL || t1->Root == NULL) return create_trie();
    Trie* new_trie = create_trie();
    char sentence [1000];
    int cpt = 0;
    help_travers_diff(new_trie , t1->Root , t2 ,sentence , 0 , &cpt);
    return new_trie;
}



void help_travers_copy(Trie* trie,Trie_node* node , char*sentence , int i , int* cpt ) {
    if (node == NULL){
        return;
    }
    if (node->is_end_of_sentence == true){
        sentence[i] = '\0';
        insert(trie , sentence , *cpt) ;
        (*cpt)++;
    }
    for (int j = 0 ; j < 30 ; j++){
        if (node->children[j] != NULL){
            if( 0<= i && i< 26 ) {
                sentence[j] = 'a'+i;
            }
            else if (i == 26){
                sentence[j] = ' ';
            }
            else if( i == 27){
                sentence[j] = ',';
            }
            else if (i == 28){
                sentence[j] = ';';
            }
            else if (i == 29){
                sentence[j] = ':';
            }
            help_travers_copy(trie,node->children[j] , sentence , i+1 , cpt );
        }
    }
}

Trie* copy_trie(Trie* trie){
    if (trie == NULL || trie->Root == NULL) return create_trie();
    Trie* new_trie = create_trie();
    char sentence [1000];
    int cpt = 0;
    help_travers_copy(new_trie , trie->Root , sentence, 0 , &cpt);
    return new_trie;
}


// -------------------- Filtering_ Extraction ------------------ //


void help_travers_num(Trie_node* node , int* cpt ) {
    if (node == NULL){
        return;
    }
    if (node->is_end_of_sentence == true){
        (*cpt)++;
    }
    for (int j = 0 ; j < 30 ; j++){
        if (node->children[j] != NULL){
            help_travers_num(node->children[j] , cpt );
        }
    }
}

int num_of_sentences(Trie* A){
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
    int n1 = num_of_sentences(inter);
    int n2 = num_of_sentences(unionn);
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



Trie_node* go_to(Trie* trie , char* root){
    if(trie== NULL || trie->Root == NULL){
        return NULL;
    }
    Trie_node* curr = trie->Root;
    int index;
    int size = strlen(root);
    for (int i = 0 ; i< size ; i++ ){
        index = get_index(root[i]);
        if (curr->children[index] == NULL){
            return NULL;
        }
        else {
            curr = curr->children[index];
        }
    }
    return curr;
}

void help_travers_2(Trie_node* node , char*sentence , int i , char** res ,int* k) {
    if (node == NULL){
        return;
    }
    if (node->is_end_of_sentence == true){
        sentence[i] = '\0';
        res[(*k)++] = strdup(sentence);
    }
    for (int j = 0 ; j < 30 ; j++){
        if (node->children[j] != NULL){
            if( 0<= i && i< 26 ) {
                sentence[j] = 'a'+i;
            }
            else if (i == 26){
                sentence[j] = ' ';
            }
            else if( i == 27){
                sentence[j] = ',';
            }
            else if (i == 28){
                sentence[j] = ';';
            }
            else if (i == 29){
                sentence[j] = ':';
            }
            help_travers_2(node->children[j] , sentence , i+1 , res , k);
        }
    }
}

char** sentences_start_with(Trie* trie , char* s ){
    char** words = malloc(sizeof(char*) * 10000);
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
    char sentence[1000];
    strcpy(sentence, s); 
    int size = strlen(s);    
    help_travers_2(node, sentence ,size , words , &k);
    return words;

}

void helper_count(Trie_node* node , int* cpt){
    if (node == NULL){
        return;
    }
    for (int i = 0 ; i <30 ; i++){
        if(node->children[i]!= NULL){
            helper_count(node->children[i] , cpt) ;
        }
    }
    if (node->is_end_of_sentence){
        (*cpt)++;
    }
}

int countPrefixMatches(Trie* trie , char prefix){
     if(trie== NULL || trie->Root == NULL){
        return NULL;
    }
    Trie_node* node = go_to(trie, prefix);
    if (node == NULL) {
        return 0; 
    }
    int cpt = 1;
    helper_count(node , &cpt);
    return cpt;
}




// ------------------- file_structure ------------------- //





typedef struct file_node {
    Trie* paragraph;
    file_node* next;
    file_node* prev;
    
}file_node;

typedef struct file
{
    file_node* head;
    file_node* tail;
}file;


void prep_file_node(file_node* node){
    node->paragraph = create_trie();
    node->next = node->prev = NULL;
}

file_node* creat_file_node(){
    file_node* node =  malloc(sizeof(file_node));
    prep_file_node(node);
    return node;
}
file* creat_paragraph(){
    file* file = malloc(sizeof(file));
    file->head = file->tail = NULL;
    return file;
}

void fill_file(file* file , char* text , int s){
    if (file == NULL || text == NULL){
        return;
    }
    char sentence[1000];
    int j = 0;
    if (file->head == NULL){
    file->head = file->tail = creat_file_node();
}
    int order = 0;
    file_node* node = file->tail;
    for(int i = 0 ; i<s ; i++){
        if (text [i] == '.'){
            sentence[j] = '\0';
            insert(node->paragraph , strdup(sentence) , order++);
            j = 0;
        }
        else  if (text [i] == '\n'){
            sentence[j] = '\0';
            insert(node->paragraph , strdup(sentence) , order++);
            file_node* temp = creat_file_node();
            node->next = temp;
            temp->prev = node;
            node = node->next;
            j = 0;
        }

        else {
            sentence[j] = text[i];
            j++;
        }
    }
}