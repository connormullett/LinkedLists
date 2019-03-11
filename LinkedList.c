
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

struct Node *createNode(int data, struct Node *next);
struct Node *deleteNode(struct Node *node, struct Node *head);
struct Node *getLast(LinkedList *list);
struct Node *getPriorNode(struct Node *node, struct Node *head);
struct Node *searchNode(int value, LinkedList *list);
LinkedList *createList();
LinkedList *deleteFirstOccurence(int value, LinkedList *list);
LinkedList *insertNode(int value, LinkedList *list);
void printList(LinkedList *list);

int main() {

  printf("creating list ..\n");
  LinkedList *list = createList();

  printf("populating list ..\n");
  for (int i = 0; i < 10; ++i) {
    insertNode(i, list);
  }

  printf("list size = %d\n", list->size);
  printList(list);

  // seg fault here
  list = deleteFirstOccurence(3, list);
  printList(list);

  // delete function may not be reassigning last
  printf("inserting node with value = 1\n");
  insertNode(1, list);

  printList(list);

  printf("searching for node with value 2 .. \n");
  struct Node *searchedNode = searchNode(2, list);
  printf("searched node's data = %d\n", searchedNode->data);

  return 0;
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

LinkedList *deleteFirstOccurence(int value, LinkedList *list) {
  /*
  deletes the node that contains
  the first occurence of the value
  */
  struct Node *nodeToDelete = searchNode(value, list);

  if (nodeToDelete == NULL)
    return list;

  // if the node is not the tail, get the prior node
  if (nodeToDelete != list->tail)
    list->tail = getPriorNode(list->tail, list->head);
  else
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

  // CALLED FROM INSERTNODE
  struct Node *returnNode = malloc(sizeof(struct Node));

  returnNode->data = data;
  returnNode->next = next;

  return returnNode;
}

LinkedList *insertNode(int value, LinkedList *list) {
  // create the node
  struct Node *node = createNode(value, NULL);

  // verify the list isn't empty
  if (list->tail == NULL && list->head == NULL) {
    list->head = node;
    list->tail = node;
    ++(list->size);
    return list;
  }

  // get the tail
  struct Node *oldTail = list->tail;

  // assign the tail to the end of the list
  list->tail = node;

  // the last node points to the new node
  oldTail->next = node;

  // increase size of the list
  ++(list->size);

  return list;
}
