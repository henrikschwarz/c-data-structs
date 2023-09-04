#include <stdio.h>
#include <stdlib.h>

// DEFINE DATA STRUCTURE
struct linked_item {
    struct linked_item* prev;
    struct linked_item* next;
    int value;
};

typedef struct linked_item item_t;

// IMPLEMENT FUNCTIONS

item_t* create_item(int value) {
    item_t* newItem = malloc(sizeof(item_t));
    if (value) {
        newItem->value = value;
    }
    return newItem;
}

item_t* find_end(item_t* first) {
    if (!first) {
        return NULL;
    }

    while (first->next) {
        first = first->next;
    }
    return first; 
}

int append(item_t* list, item_t* new) {
    item_t* last = find_end(list);
    if (!last) {
        return -1;
    }
    last->next = new;
    new->prev = last;

    return 0;
}

int delete(item_t* list, int index) {
    int i = 0;
    if (index != 0) {
        while (i != index) {
            list = list->next;
            if (list == NULL) {
                return -1;
            }
            i++;
        }
    }
    item_t* temp = &(*list);
    *list = *list->next;
    return 0;
}


int length(item_t* list) {
    if (!list) {
        return 0;
    }

    int l = 1;
    while (list->next) {
        l++;
        list = list->next;
    }
    return l;
}

void print_list(item_t* list){
    if (list){
        do {
            printf("%d\n", list->value);
            list = list->next;
        } while (list->next);
    }
}

void cleanup_list(item_t* list) {
    if (!list) return;

    while (list->next) {
        delete(list, 0);
    }
}

int main () {
    item_t* list = create_item(0);
    for (int i = 1; i < 10; i++){
        item_t* new_item = create_item(i);
        int result = append(list, new_item);
        if (result < 0) {
            printf("Error in appending %d.\n", i);
            return -1;
        }
    }

    printf("length is %d\n", length(list));
    delete(list, 2);
    delete(list, 0);
    delete(list, 4);
    printf("length is %d\n", length(list));
    print_list(list);
    cleanup_list(list);
}

