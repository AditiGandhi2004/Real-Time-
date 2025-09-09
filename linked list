Let us assume the following sequence of input
7,7,5,2,5,2,8,5,6,8,8,7,4,4,7,2,3,8,9,3,2,9,7,8,3
Count the number of occurrences of each digit (as per increasing order of given digit) and
store those numbers in a new array. The result (intermediate output sequence) of this
process looks like 4,3,2,3,1,5,5,2 – Counted Values – 8 numbers
Means digit 2 occurs 4 times, digit 3 occurs 3 times, digit 4 occurs 2 times, digit 5
occurs 3 times, digit 6 occurs 1 time, digit 7 occurs 5 times, digit 8 occurs 5 times,
and digit 9 occurs 2 times.
Now create a doubly linked list with 8 nodes. As we have got 8 counted values from
the received inputs. Traverse from first node to last node and from last
node to first node print the data values.
4->3->2->3->1->5->5->2
2->5->5->1->3->2->3->4
Also test your logic for other input sequence which is similar to the given pattern.
Using doubly linked list delete the node by getting the position and print the
remaining values after deletion. Implement singly linked list for same input sequence
given



#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}


void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void displayForward(Node* head) {
    while (head) {
        printf("%d ", head->data);
        if (head->next) printf("-> ");
        head = head->next;
    }
    printf("\n");
}


void displayBackward(Node* head) {
    if (!head) return;
    while (head->next) head = head->next;
    while (head) {
        printf("%d ", head->data);
        if (head->prev) printf("-> ");
        head = head->prev;
    }
    printf("\n");
}


void deleteAtPosition(Node** head, int pos) {
    if (*head == NULL) return;
    Node* temp = *head;
    int i = 1;
    while (temp && i < pos) {
        temp = temp->next;
        i++;
    }
    if (!temp) return;
    if (temp->prev) temp->prev->next = temp->next;
    else *head = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    free(temp);
}

typedef struct SNode {
    int data;
    struct SNode *next;
} SNode;

SNode* createSNode(int data) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertEndSLL(SNode** head, int data) {
    SNode* newNode = createSNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    SNode* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}


void displaySLL(SNode* head) {
    while (head) {
        printf("%d ", head->data);
        if (head->next) printf("-> ");
        head = head->next;
    }
    printf("-> NULL\n");
}

int main() {
    int arr[] = {4,3,2,3,1,5,5,2};
    int n = 8;

    Node* dll = NULL;
    SNode* sll = NULL;

    for (int i=0; i<n; i++) {
        insertEnd(&dll, arr[i]);
        insertEndSLL(&sll, arr[i]);
    }

    printf("Forward DLL: ");
    displayForward(dll);
    printf("Backward DLL: ");
    displayBackward(dll);

    deleteAtPosition(&dll, 3); 

    printf("DLL after deletion: ");
    displayForward(dll);

    printf("SLL: ");
    displaySLL(sll);

    return 0;
}
