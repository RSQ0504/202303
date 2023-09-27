#include <stdio.h>
#include "list.h"
int list_count = 0; 
int node_count = 0;
List list_pool[LIST_MAX_NUM_HEADS];
Node node_pool[LIST_MAX_NUM_HEADS * LIST_MAX_NUM_NODES];
//TODO
List* List_create(){
    int list_index = list_count;
    if (list_index >= LIST_MAX_NUM_HEADS){
        return NULL;
    }
    list_count ++;

    List* new_list =  &(list_pool[list_index]);

    new_list->first = NULL;
    new_list->last = NULL;
    new_list->curr = NULL;

    new_list->is_empty = true;
    new_list->curr_node_state = LIST_OOB_START;
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
        pList->curr = NULL;
        pList->curr_node_state = LIST_OOB_START;
        return NULL;
    }else{
        pList->curr = pList->first;
        pList->curr_node_state = IN_LIST;
        return pList->curr->item;
    }
}


void* List_last(List* pList){
    //assert(pList != NULL);
    if (pList->is_empty == true){
        pList->curr = NULL;
        pList->curr_node_state = LIST_OOB_START;
        return NULL;
    }else{
        pList->curr = pList->last;
        pList->curr_node_state = IN_LIST;
        return pList->curr->item;
    }
}

void* List_next(List* pList){
    if (pList->curr==NULL){
        if(pList->curr_node_state==LIST_OOB_START){
            pList->curr = pList->first;
            pList->curr_node_state = IN_LIST;
            return pList->curr->item;
        }else if(pList->curr_node_state==LIST_OOB_END){
            return NULL;
        }
    }
    Node* next = pList->curr->next;
    if (next == NULL){
        pList->curr = NULL;
        pList->curr_node_state = LIST_OOB_END;
        return NULL;
    }else{
        pList->curr = next;
        pList->curr_node_state = IN_LIST;
        return pList->curr->item;
    }
}

void* List_prev(List* pList){
    if (pList->curr==NULL){
        if(pList->curr_node_state==LIST_OOB_START){
            return NULL;
        }else if(pList->curr_node_state==LIST_OOB_END){
            pList->curr = pList->last;
            pList->curr_node_state = IN_LIST;
            return pList->curr->item;
        }
    }
    Node* prev = pList->curr->prev;
    if (prev == NULL){
        pList->curr = NULL;
        pList->curr_node_state = LIST_OOB_START;
        return NULL;
    }else{
        pList->curr = prev;
        pList->curr_node_state = IN_LIST;
        return pList->curr->item;
    }
}


void* List_curr(List* pList){
    //assert(pList != NULL);
    if (pList->curr==NULL){
        return NULL;
    }
    return pList->curr->item;
}

int List_insert_after(List* pList, void* pItem){
    if (pList->curr_node_num == LIST_MAX_NUM_NODES||node_count==LIST_MAX_NUM_HEADS * LIST_MAX_NUM_NODES){
        return -1;
    }

    Node* new_node = &(node_pool[node_count]);
    new_node->item = pItem;
    new_node->prev = NULL;
    new_node->next = NULL;
    
    node_count++;
    pList->curr_node_num ++;

    int state = pList->curr_node_state;
    if (state==LIST_OOB_START){
        if (pList->first == NULL){
            pList->first = new_node;
            pList->is_empty = false;
        }else{
            new_node->next = pList->first;
            pList->first->prev = new_node;
            pList->first = new_node;
        }
    }else if (state==LIST_OOB_END){
        if (pList->last == NULL&&pList->curr_node_num==2){
            pList->last->prev = pList->first;
            pList->first->next = pList->last;
            pList->last = new_node;
            pList->is_empty = false;
        }else{
            new_node->prev = pList->last;
            pList->last->next = new_node;
            pList->last = new_node;
        }
    }else{
        new_node->next =  pList->curr->next;
        if (new_node->next!=NULL){
            new_node->next->prev = new_node;
        }
        new_node->prev = pList->curr;
        pList->curr->next = new_node;
        if (pList->curr_node_num==2||pList->curr == pList->last){
            pList->last = new_node;
        }
    }
    pList->curr_node_state = IN_LIST;
    pList->curr = new_node;
    return 0;
}

int List_insert_before(List* pList, void* pItem){
    if (pList->curr_node_num == LIST_MAX_NUM_NODES||node_count==LIST_MAX_NUM_HEADS * LIST_MAX_NUM_NODES){
        return -1;
    }

    Node* new_node = &(node_pool[node_count]);
    new_node->item = pItem;
    new_node->prev = NULL;
    new_node->next = NULL;
    
    node_count++;
    pList->curr_node_num ++;

    int state = pList->curr_node_state;
    if (state==LIST_OOB_START){
        if (pList->first == NULL){
            pList->first = new_node;
            pList->is_empty = false;
        }else{
            new_node->next = pList->first;
            pList->first->prev = new_node;
            pList->first = new_node;
        }
    }else if (state==LIST_OOB_END){
        if (pList->last == NULL&&pList->curr_node_num==2){
            pList->last->prev = pList->first;
            pList->first->next = pList->last;
            pList->last = new_node;
            pList->is_empty = false;
        }else{
            new_node->prev = pList->last;
            pList->last->next = new_node;
            pList->last = new_node;
        }
    }else{
        new_node->next = pList->curr;
        new_node->prev = pList->curr->prev;
        if (new_node->prev != NULL){
            new_node->prev->next = new_node;
        }
        pList->curr->prev = new_node;
        if (pList->curr == pList->first){
            pList->first = new_node;
        }
    }
    pList->curr_node_state = IN_LIST;
    pList->curr = new_node;
    return 0;
}

int List_append(List* pList, void* pItem){
    List_last(pList);
    return List_insert_after(pList,pItem);
}

int List_prepend(List* pList, void* pItem){
    List_first(pList);
    return List_insert_before(pList,pItem);
}

void* List_remove(List* pList){
    if(pList->curr_node_state==LIST_OOB_START||pList->curr_node_state==LIST_OOB_END){
        return NULL;
    }
    Node* curr_n = pList->curr;
    void* item = curr_n->item;
    if (curr_n == pList->first){
        pList->curr_node_num --;
        if (pList->curr_node_num == 0){
            pList->first = NULL;
            pList->last = NULL;
            pList->is_empty = true;
            pList->curr = NULL;
            pList->curr_node_state = LIST_OOB_START;
        }else if(pList->curr_node_num == 1){
            pList->first = curr_n->next;
            pList->first->prev = NULL;
            pList->curr = pList->first;
            if (pList->first == pList->last){
                pList->last = NULL;
            }
        }else{
            pList->first = curr_n->next;
            pList->first->prev = NULL;
            pList->curr = pList->first;
        }
    }else if (curr_n == pList->last){
        pList->last = curr_n->prev;
        pList->last->next = NULL;
        pList->curr = NULL;
        pList->curr_node_state = LIST_OOB_END;
        pList->curr_node_num --;
    }else{
        curr_n->prev->next = curr_n->next;
        curr_n->next->prev = curr_n->prev;
        pList->curr = curr_n->next;
        pList->curr_node_num --;
    }
    node_count--;
    //realesing the last node
    Node* releasing_node = &(node_pool[node_count]);
    curr_n->item = releasing_node->item;
    curr_n->next = releasing_node->next;
    curr_n->prev = releasing_node->prev;
    if (releasing_node->prev!=NULL){
        releasing_node->prev->next = curr_n;
    }
    if (releasing_node->next!=NULL){
        releasing_node->next->prev = curr_n;
    }
    releasing_node->prev=NULL;
    releasing_node->item=NULL;
    releasing_node->next=NULL;
    return item;
}

void* List_trim(List* pList){
    if (pList->is_empty == true){
        return NULL;
    }
    List_last(pList);
    void* item = List_remove(pList);
    pList->curr = pList->last;
    return item;
}

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
