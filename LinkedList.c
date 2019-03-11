
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* given a head node write a function that counts
 * how many nodes are in the linked list */

struct Node {
  int data;
  struct Node *next;
};

typedef struct {
  int size;
  struct Node *head;
  struct Node *tail;
} LinkedList;

struct Node *getLast(LinkedList *list);
struct Node *createNode(int data, struct Node *next);
LinkedList *insertNode(int value, LinkedList *list);
struct Node *searchNode(int value, LinkedList *list);
LinkedList *deleteFirstOccurence(int value, LinkedList *list);
struct Node *deleteNode(struct Node *node, struct Node *head);
struct Node *getPriorNode(struct Node *node, struct Node *head);

LinkedList *createList();

void printList(LinkedList *list);

int main() {

  LinkedList *list = createList();

  for (int i = 0; i < 5; ++i) {
    insertNode(i, list);
  }

  printf("list size = %d\n", list->size);
  printList(list);

  // seg fault here
  list = deleteFirstOccurence(3, list);
  printf("deleting 3 .. \n");
  printList(list);

  list = deleteFirstOccurence(5, list);
  printf("deleting 5 .. \n");
  printList(list);

  return 0;
}

LinkedList *deleteFirstOccurence(int value, LinkedList *list) {
  /*
  deletes the node that contains
  the first occurence of the value
  */
  struct Node *nodeToDelete = searchNode(value, list);

  if (nodeToDelete == NULL)
    return list;

  if (nodeToDelete != list->tail)
    list->tail = getPriorNode(list->tail, list->head);

  list->head = deleteNode(nodeToDelete, list->head);
  --(list->size);
  return list;
}

struct Node *getPriorNode(struct Node *node, struct Node *head) {
  if (head == NULL || node == NULL || head == node) {
    return NULL;
  }

  if (head->next == node) {
    return head;
  }
  return getPriorNode(node, head->next);
}

struct Node *searchNode(int value, LinkedList *list) {
  /*
  searches for a node given a value
  and a list to search through
  */
  struct Node *temp = list->head;
  while (temp != NULL) {
    if ((*temp).data == value) {
      return temp;
    }

    temp = temp->next;
  }

  return NULL;
}

LinkedList *createList() {
  /*
  allocats a list pointer the size of LinkedList
  with list->size equalling 0, and head and tail are Null
  */
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void deleteList(LinkedList *list) {
  /*
  Deletes all nodes in the list
  then frees the memory allocated to the list given
  */
  while (list->head != NULL) {
    list->head = deleteNode(list->head, list->head);
  }

  free(list);
}

struct Node *deleteNode(struct Node *node, struct Node *head) {
  if (head == NULL)
    return NULL;

  if (head == node) {
    struct Node *nextNode = head->next;
    free(head);
    return nextNode;
  }

  struct Node *priorNode = getPriorNode(node, head);
  priorNode->next = node->next;
  free(node);
  return head;
}

void printList(LinkedList *list) {
  struct Node *temp = list->head;
  for (int i = 0; i < list->size; ++i) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

struct Node *createNode(int data, struct Node *next) {

  struct Node *returnNode = malloc(sizeof(struct Node));

  returnNode->data = data;
  returnNode->next = next;

  return returnNode;
}

LinkedList *insertNode(int value, LinkedList *list) {

  struct Node *node = createNode(value, NULL);

  // if the head and tail are null,
  // then the list is empty, assign head/tail to node
  if (list->tail == NULL && list->head == NULL) {
    list->head = node;
    list->tail = node;
    ++(list->size);
    return list;
  }

  struct Node *lastNode = list->tail;

  // if the head is null then its an empty list
  if (list->head == NULL) {
    list->head = node;
  }

  // assign the tail to the end of the list
  list->tail = node;

  lastNode->next = node;

  ++(list->size);

  return list;
}
