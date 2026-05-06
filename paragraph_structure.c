#include"sets_operations.h"
#include"Trie_machine_abstract.h"

typedef struct paragraph_node {
    Trie* sentence;
    paragraph_node* next;
    paragraph_node* prev;
    
}paragraph_node;

typedef struct paragraph
{
    paragraph_node* head;
    paragraph_node* tail;
}paragraph;


void prep_paragraph_node(paragraph_node* node){
    node->sentence = create_trie();
    node->next = node->prev = NULL;
}

paragraph_node* creat_paragraph_node(){
    paragraph_node* node =  malloc(sizeof(paragraph_node));
    prep_paragraph_node(node);
    return node;
}
paragraph* creat_paragraph(){
    paragraph* par = malloc(sizeof(paragraph));
    par->head = par->tail = NULL;
    return par;
}

void fill_paragraph(paragraph* par , char* text , int s){
    if (par == NULL || text == NULL){
        return;
    }
    char word[1000];
    int j = 0;
    if (par->head == NULL){
    par->head = par->tail = creat_paragraph_node();
}
      paragraph_node* node = par->tail;
    for(int i = 0 ; i<s ; i++){
        if (text [i] == ' '){
            word[j] = '\0';
            insert(node->sentence , strdup(word));
            j = 0;
        }
        else  if (text [i] == '.'){
            word[j] = '\0';
            insert(node->sentence , word);
            paragraph_node* temp = creat_paragraph_node();
            node->next = temp;
            temp->prev = node;
            node = node->next;
            j = 0;
        }

        else {
            word[j] = text[i];
            j++;
        }
    }
}
