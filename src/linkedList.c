#include "linkedList.h"
#include<stdio.h>
#include<stdlib.h>


/*
 * Doubly-linked, doubly-ended Linked List. 
 *      Author: Jai Dutta
 *      Student ID: 22073372
 *      Unit: COMP1000 - Unix and C Programming
 */


/* Utility functions for freeing various types of data (none used in this assignment, free_map in map.c is used instead.) */
void print_int(void *data) {
    printf("%d\n", *(int*)data);
}

void print_string(void *data) {
    printf("%s\n", (char*)data);
}

void free_node(void *data) {
    free(data);
}

void free_2d_array(int **data, int rows) {
    int i;
    for(i = 0; i<rows;i++) {
        free(data[i]);
    }
    free(data);
    data = NULL;
}

/* Allocate and initialise linkedlist struct values */
LinkedList* create_linked_list(void) {
    LinkedList* linked_list = (LinkedList *)malloc(sizeof(LinkedList));
    linked_list->count = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;

    return linked_list;
}
/* Insert a node at the start of the Linked List */
void insert_start(LinkedList* ll, void* data) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->value = data;

    /*if list is empty*/
    if(ll->count == 0) {
        new_node->next = NULL;
        new_node->prev = NULL;
        ll->head = new_node;
        ll->tail = new_node;
    }
    /*if list is not empty*/
    else {
        new_node->next = ll->head;
        ll->head->prev = new_node;
        ll->head = new_node;
        ll->head->prev = NULL;
    }
    ll->count++;
}
/**/
/* Remove and return a node at the start of the linked list. */
void* remove_start(LinkedList* ll) {
    ListNode* removed_node = ll->head;
    void* retval;
    if(ll->count == 0) {
        return NULL;
    }
    if(ll->count == 1) {
        retval = ll->head->value;
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
        ll->count = 0;
        return retval;
    }
    retval = ll->head->value;
    ll->head = ll->head->next;
    ll->head->prev = NULL;
    ll->count--;

    free(removed_node);

    return retval;
}

/* Insert a node at the tail of the linked list. */
void insert_last(LinkedList* ll, void* data) {
    ListNode* new_node;

    /* If count is 0, then just use the insert start function. */
    if(ll->count == 0) {
        insert_start(ll, data);
        return;
    } 

    new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->value = data;
    new_node->next = NULL;

    ll->tail->next = new_node;
    new_node->prev = ll->tail;
    ll->tail = new_node;

    ll->count++;
}

/* Remove and return a node at the tail of the linked list. */
void* remove_last(LinkedList* ll) {
    ListNode* removed_node;
    void* retval;

    if(ll->count == 0) {
        return NULL;
    }
    if(ll->count == 1) {
        retval = ll->head->value;
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
        ll->count = 0;
        return retval;
    }

    removed_node = ll->tail;
    ll->tail = ll->tail->prev;
    ll->tail->next = NULL;

    retval = removed_node->value;
    free(removed_node);
    removed_node = NULL;
    ll->count--;

    return retval;
}

/* Print each node in the Linked List (not used in this assignment) */
void print_linked_list(LinkedList* ll, listFunc funcPtr) {
    ListNode* current = ll->head;
    printf("LinkedList count: %d \n", ll->count);
    while(current != NULL) {
        funcPtr(current->value);
        current = current->next;
    }
}

/* Free the linked list using a function pointer to the appropriate freeing function */
void free_linked_list(LinkedList* ll, listFunc funcPtr) {
    ListNode* current = ll->head;
    ListNode* next_node;
    while(current != NULL) {
        next_node = current->next;
        funcPtr(current->value);
        free(current);
        current = next_node;
    }
    free(ll);
}
