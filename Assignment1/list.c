#include <stdio.h>
#include "list.h"
int list_count = 0; 
int node_count = 0;
List list_pool[LIST_MAX_NUM_HEADS];
Node OOB_node_pool[LIST_MAX_NUM_HEADS];
Node node_pool[LIST_MAX_NUM_HEADS * LIST_MAX_NUM_NODES];
//TODO
List* List_create(){
    int list_index = list_count;
    int node_index = node_count;
    if (list_index >= LIST_MAX_NUM_HEADS || node_index>=LIST_MAX_NUM_HEADS*LIST_MAX_NUM_NODES){
        return NULL;
    }
    list_count ++;
    node_count ++;

    List* new_list =  &(list_pool[list_index]);
    Node* new_node = &(node_pool[node_index]);
    Node* OOB_node = &(OOB_node_pool[list_index]);

    new_list->first = new_node;
    new_list->last = new_node;
    new_list->curr = OOB_node;
    //set curr as before of head
    new_list->first->prev = OOB_node;
    new_list->first->next = NULL;
    new_list->first->item = NULL;
    
    new_list->curr->prev = NULL;
    new_list->curr->next = new_node;
    new_list->curr->item = NULL;

    new_list->is_using = true;
    new_list->is_empty = true;
    new_list->curr_node_num = 0;
    return new_list;
}


int List_count(List* pList){
    //assert(pList != NULL);
    return pList->curr_node_num;
}


void* List_first(List* pList){
    //assert(pList != NULL);
    if (pList->is_empty == true){
        pList->curr->item = NULL;
        return NULL;
    }else{
        pList->curr = pList->first;
        return pList->curr->item;
    }
}


void* List_last(List* pList){
    //assert(pList != NULL);
    if (pList->is_empty == true){
        pList->curr->item = NULL;
        return NULL;
    }else{
        pList->curr = pList->last;
        return pList->curr->item;
    }
}

void* List_next(List* pList){
    Node* next = pList->curr->next;
    if (next == NULL){
        pList->curr->item = NULL;
        pList->curr->prev = pList->last;
        pList->curr->next = NULL;
        return NULL;
    }else{
        pList->curr = next;
        return pList->curr->item;
    }
}

void* List_prev(List* pList){
    Node* prev = pList->curr->prev;
    if (prev == NULL){
        pList->curr->item = NULL;
        pList->curr->prev = NULL;
        pList->curr->next = pList->first;
        return NULL;
    }else{
        pList->curr = prev;
        return pList->curr->item;
    }
}


void* List_curr(List* pList){
    //assert(pList != NULL);
    return pList->curr->item;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem);

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem);

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem);

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem);

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList);

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList);

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2);

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn);

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg);
