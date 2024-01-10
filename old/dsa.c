// Singly linked list

#include <stdio.h>
#include <stdlib.h>

struct Node *head = NULL;
struct Node *tail = NULL;

struct Node
{
    int data;
    struct Node *next;
};

int listLength()
{
    int count = 0;
    struct Node *current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

void printList()
{
    struct Node *current = head;

    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
}

void pushAtHead(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;

    if (listLength(head) < 1)
    {
        head = newNode;
        tail = head;
        return;
    }

    newNode->next = head;
    head = newNode;
}

void pushAtTail(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;

    if (listLength() < 1)
    {
        head = newNode;
        tail = head;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void pushAtParticular(int pushAfter, int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;

    struct Node *current = head;
    while (current != NULL)
    {
        if (current->data == pushAfter)
        {
            newNode->next = current->next;
            current->next = newNode;

            return;
        }

        current = current->next;
    }
}

void popHead()
{
    if (listLength() < 1)
    {
        return;
    }

    head = head->next;
}

void popTail()
{
    if (listLength() <= 1)
    {
        return;
    }

    struct Node *current = head;
    struct Node *prev = NULL;
    int loopFlag = 1;
    while (loopFlag == 1)
    {
        if (current->next == NULL)
        {
            prev->next = NULL;
            tail = prev;
            loopFlag = -1;

            break;
        }

        prev = current;
        current = current->next;
    }
}

void removeAtParticular(int data)
{
    if (listLength() < 1)
    {
        return;
    }

    struct Node *current = head;
    struct Node *prev = NULL;

    int loopFlag = 1;
    while (loopFlag == 1)
    {
        if (current->data == data)
        {
            prev->next = current->next;
            free(current);
            loopFlag = -1;

            break;
        }

        prev = current;
        current = current->next;
    }
}

int main()
{
    pushAtHead(4);

    pushAtTail(2);

    pushAtParticular(4, 3);

    printList();

    printf("\n");

    popHead();

    printList();

    popTail();

    removeAtParticular(3);

    printList();

    return 0;
}

// Doubly linked list

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head = NULL;
struct Node *tail = NULL;

int listLength()
{
    int count = 0;
    struct Node *current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

void printList()
{
    struct Node *current = head;

    while (current != NULL)
    {
        printf("%d", current->data);

        current = current->next;
    }
}

void printReverseList()
{
    struct Node *current = tail;

    while (current != NULL)
    {
        printf("%d", current->data);

        current = current->prev;
    }
}

void pushAtHead(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (listLength() < 1)
    {
        head = newNode;
        tail = head;

        return;
    }

    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void pushAtTail(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (listLength() < 1)
    {
        head = newNode;
        tail = head;

        return;
    }

    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

int main()
{
    pushAtHead(1);
    pushAtHead(2);
    pushAtHead(3);
    pushAtTail(4);

    printList();
}

// Circular linked list

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;

int listLength()
{
    if (head == NULL)
    {
        return 0;
    }

    int count = 0;
    struct Node *current = head;

    do
    {
        count++;
        current = current->next;
    } while (current != head);

    return count;
}

void printList()
{
    if (head != NULL && head == tail)
    {
        printf("%d", head->data);

        return;
    }

    struct Node *current = head;

    do
    {
        printf("%d", current->data);
        current = current->next;
    } while (current != head);
}

void push(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;

    if (listLength() < 1)
    {
        head = newNode;
        newNode->next = head;
        tail = head;

        return;
    }

    tail->next = newNode;
    newNode->next = head;
    tail = newNode;
}

int main()
{
    push(1);
    push(2);
    push(3);

    printf("list length: %d\n", listLength());
    printList();
}

// Stack
// Stack is basically linked list with LIFO, push and pop is done on head

// Queue
// Queue is also linked list with FIFO, push is done at end and pop is done at head

// Priority queue
// Node is inserted at a place based on priority in queue