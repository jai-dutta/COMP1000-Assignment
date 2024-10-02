#include "linkedList.h"


/*
 * Doubly-linked, doubly-ended Linked List. 
 *      Author: Jai Dutta
 *      Unit: COMP1000 - Unix and C Programming
 */

void print_int(void *data) {
    printf("%d\n", *(int*)data);
}

void print_string(void *data) {
    printf("%s\n", (char*)data);
}

void free_node(void *data) {
    free(data);
}

LinkedList* create_linked_list() {
    LinkedList* linked_list = (LinkedList *)malloc(sizeof(LinkedList));
    linked_list->count = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;

    return linked_list;
}

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

void* remove_start(LinkedList* ll) {
    ListNode* removed_node = ll->head;
    void* retval;
    if(ll->count == 0) {
        printf("Linked List is empty. Cannot remove start.");
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

    ll->head = ll->head->next;
    ll->head->prev = NULL;
    ll->count--;

    retval = removed_node->value;
    
    free(removed_node);
    removed_node = NULL;

    return retval;
}

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

void* remove_last(LinkedList* ll) {
    ListNode* removed_node;
    void* retval;

    if(ll->count == 0) {
        printf("Linked List is empty. Cannot remove last.");
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
//! PROBS NOT NEEDED x
/* 
void print_linked_list(LinkedList* ll, listFunc funcPtr) {
    ListNode* current = ll->head;
    printf("LinkedList count: %d \n", ll->count);
    while(current != NULL) {
        funcPtr(current->value);
        current = current->next;
    }
}*/

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
