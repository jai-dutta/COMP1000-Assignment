#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<stdio.h>
#include <stdlib.h>

/** List Node Struct */
typedef struct ListNode {
    void* value;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

/* Linked List Struct */
typedef struct {
    int count;
    ListNode* head;
    ListNode* tail;
} LinkedList;

/* Function Pointer for Printing */
typedef void (*listFunc)(void* data);

/* Forward Declarations */
void print_int(void *data);
void print_string(void *data);
LinkedList* create_linked_list();
void insert_start(LinkedList* ll, void* data);
void* remove_start(LinkedList* ll);
void insert_last(LinkedList* ll, void* data);
void* remove_last(LinkedList* ll);
void print_linked_list(LinkedList* ll, listFunc funcPtr);
void free_linked_list(LinkedList* ll, listFunc funcPtr);
#endif
