#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Trie_node{
    char* arr[26];
    int is_end_of_word;

}Trie_node;