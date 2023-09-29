#include <stdio.h>
#include "list.h"


bool first_setup = true;
List list_pool[LIST_MAX_NUM_HEADS];
List* current_using_list;
Node node_pool[LIST_MAX_NUM_NODES];
Node* current_using_node;
//TODO
List* List_create(){
    if (first_setup){
        first_setup = false;
        current_using_list = &(list_pool[0]);
        current_using_node = &(node_pool[0]);

        for (int i = 1;i<LIST_MAX_NUM_HEADS;i++){
            list_pool[i-1].next_list = &(list_pool[i]);
        }
        list_pool[LIST_MAX_NUM_HEADS-1].next_list = NULL;

        for (int i = 1;i<LIST_MAX_NUM_NODES;i++){
            node_pool[i-1].next_node = &(node_pool[i]);
        }
        node_pool[LIST_MAX_NUM_NODES-1].next_node = NULL;
    }

    if (current_using_list == NULL){
        return NULL;
    }
    List* new_list =  current_using_list;
    current_using_list = current_using_list->next_list;

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
        if (pList->last!=NULL){
            pList->curr = pList->last;
        }else{
            pList->curr = pList->first;
        }
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
    if (current_using_node==NULL){
        return -1;
    }

    Node* new_node = current_using_node;
    new_node->item = pItem;
    new_node->prev = NULL;
    new_node->next = NULL;
    
    current_using_node = current_using_node->next_node;
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
    if (current_using_node==NULL){
        return -1;
    }

    Node* new_node = current_using_node;
    new_node->item = pItem;
    new_node->prev = NULL;
    new_node->next = NULL;
    
    current_using_node = current_using_node->next_node;
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
        if (pList->curr_node_num == 1){
            pList->first = NULL;
            pList->last = NULL;
            pList->is_empty = true;
            pList->curr = NULL;
            pList->curr_node_state = LIST_OOB_START;
        }else if(pList->curr_node_num == 2){
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
        if(pList->last == pList->first){
            pList->last = NULL;
        }
    }else{
        curr_n->prev->next = curr_n->next;
        curr_n->next->prev = curr_n->prev;
        pList->curr = curr_n->next;
    }
    pList->curr_node_num --;

    //put back to pull
    curr_n->prev=NULL;
    curr_n->item=NULL;
    curr_n->next=NULL;
    if(current_using_node!=NULL){
        curr_n->next_node = current_using_node->next_node;
        current_using_node->next_node = curr_n;
    }else{
        curr_n->next_node = NULL;
        current_using_node = curr_n;
    }
    return item;
}

void* List_trim(List* pList){
    if (pList->is_empty == true){
        return NULL;
    }
    List_last(pList);
    void* item = List_remove(pList);
    pList->curr = pList->last;
    pList->curr_node_state = IN_LIST;
    return item;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    if (pList1->curr_node_num>=2&&pList2->curr_node_num>=2){
        pList1->last->next = pList2->first;
        pList2->first->prev = pList1->last;
        pList1->last = pList2->last;
    }else if (pList1->curr_node_num>=2&&pList2->curr_node_num==1){
        pList1->last->next = pList2->first;
        pList2->first->prev = pList1->last;
        pList1->last = pList2->first;
    }else if (pList1->curr_node_num==1&&pList2->curr_node_num==1){
        pList1->first->next = pList2->first;
        pList2->first->prev = pList1->first;
        pList1->last = pList2->first;
    }else if (pList1->curr_node_num==0){
        pList1->first = pList2->first;
        pList1->last = pList2->last;
    }
    pList1->curr_node_num = pList1->curr_node_num + pList2->curr_node_num;
    if (pList1->curr_node_num>0){
        pList1->is_empty=false;
    }
    if (pList1->curr_node_state==LIST_OOB_END&&pList2->first!=NULL&&pList1->first!=NULL){
        pList1->curr = pList2->first;
        pList1->curr_node_state = IN_LIST;
    }
    pList2->curr = NULL;
    pList2->curr_node_num = 0;
    pList2->curr_node_state = LIST_OOB_START;
    pList2->first = NULL;
    pList2->is_empty = true;
    pList2->last = NULL;
    if (current_using_list!=NULL){
        pList2->next_list = current_using_list->next_list;
        current_using_list->next_list = pList2;
    }else{
        pList2->next_list = NULL;
        current_using_list = pList2;
    }
}


typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn){
    List_first(pList);
    while (pList->curr!=NULL){
        (*pItemFreeFn)(List_remove(pList));
    }
    pList->curr = NULL;
    pList->curr_node_num = 0;
    pList->curr_node_state = LIST_OOB_START;
    pList->first = NULL;
    pList->is_empty = true;
    pList->last = NULL;
    if (current_using_list!=NULL){
        pList->next_list = current_using_list->next_list;
        current_using_list->next_list = pList;
    }else{
        pList->next_list = NULL;
        current_using_list = pList;
    }
}


typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    Node* current_node = pList->curr;
    if (pList->curr_node_state==LIST_OOB_START){
        current_node = pList->first;
    }
    while (current_node != NULL) {
        if ((*pComparator)(current_node->item, pComparisonArg)) {
            pList->curr = current_node;
            return current_node->item;
        }
        current_node = current_node->next;
    }
    
    pList->curr = NULL;
    pList->curr_node_state = LIST_OOB_END;
    return NULL;
}
