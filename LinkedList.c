
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* given a head node write a function that counts
 * how many nodes are in the linked list */


struct Node {
    int data;
    struct Node* next;
};

typedef struct {
    int size;
    struct Node* head;
    struct Node* tail;
} LinkedList;

struct Node* getLast(LinkedList* list);
struct Node* createNode(int data, struct Node* next);
LinkedList* insertNode(int value, LinkedList* list);
struct Node* searchNode(int value, LinkedList* list);
LinkedList* deleteFirstOccurence(int value, LinkedList* list);
struct Node* deleteNode(struct Node* node, struct Node* head);
struct Node* getPriorNode(struct Node* node, struct Node* head);

LinkedList* createList();

void printList(LinkedList* list);

int main(){

    LinkedList* list = createList();

    for(int i = 1; i < 5; ++i){
        insertNode(i, list);
    }

    printf("%d\n", list->size);

    list = deleteFirstOccurence(5, list);
    printList(list);

    return 0;
}

/*
allocats a list pointer the size of LinkedList
with list->size equalling 0, and head and tail are Null
*/
LinkedList* createList(){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/*
Deletes all nodes in the list
then frees the memory allocated to the list given
*/
void deleteList(LinkedList* list){
    while(list->head != NULL){
        list->head = deleteNode(list->head, list->head);
    }

    free(list);
}

LinkedList* deleteFirstOccurence(int value, LinkedList* list){
    struct Node* nodeToDelete = searchNode(value, list);

    if(nodeToDelete != list->tail){
        list->tail = getPriorNode(list->tail, list->head);
    }

    list->head = deleteNode(nodeToDelete, list->head);
    (list->size)--;
    return list;
}


struct Node* deleteNode(struct Node* node, struct Node* head){
    if(head == NULL) return NULL;

    if(head == node){
        struct Node* nextNode = head->next;
        free(head);
        return nextNode;
    }

    struct Node* priorNode = getPriorNode(node, head);
    priorNode->next = node->next;
    free(node);
    return head;
}

struct Node* getPriorNode(struct Node* node, struct Node* head){
    if(head == NULL || node == NULL || head == node) return NULL;

    if(head->next == node) return head;

    return getPriorNode(node, head->next);
}

struct Node* searchNode(int value, LinkedList* list){
    struct Node* temp = list->head;
    while(temp != NULL){
        if((*temp).data == value){
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

void printList(LinkedList* list){
    struct Node* temp = list->head;
    for(int i = 0; i < list->size; ++i){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


struct Node* createNode(int data, struct Node* next){

    struct Node* returnNode = malloc(sizeof(struct Node));

    returnNode->data = data;
    returnNode->next = next;

    return returnNode;
}

LinkedList* insertNode(int value, LinkedList* list){

    struct Node* node = createNode(value, NULL);

    struct Node* lastNode = getLast(list);

    if(list->head == NULL) list->head = node;

    list->tail = node;

    lastNode->next = node;

    (list->size)++;

    return list;
}

struct Node* getLast(LinkedList* list){
    return list->tail;
}
