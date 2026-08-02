/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

struct Node
{
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class CircularSinglyLinkedList
{
private:
    Node *head;
    Node *tail;
    int length;

public:
    CircularSinglyLinkedList()
    {
        head = tail = nullptr;
        length = 0;
    }

    ~CircularSinglyLinkedList()
    {
        Node *current = head;

        for (int i = 1; i <= length; i++)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = tail = nullptr;
        length = 0;
    }

    bool insertAtBeginning(int value)
    {
        /*
            If head == nullptr then head = tail = newNode and point tail->next to head
            For other cases, point newNode->next to head and then head = newNode
        */

        cout << "Inserted: " << value << " at beginning\n";

        Node *newNode = new Node(value);

        if (head == nullptr)
        {
            head = tail = newNode;
            tail->next = head;

            length++;

            return true;
        }

        newNode->next = head;
        head = newNode;
        tail->next = head;

        length++;

        return true;
    }

    bool insertAtEnd(int value)
    {
        /*
            If head == nullptr then call insertAtBeginning
            For other cases, point tail->next to newNode and then tail = newNode
        */

        if (head == nullptr)
        {
            return insertAtBeginning(value);
        }

        Node *newNode = new Node(value);

        tail->next = newNode;
        newNode->next = head;
        tail = newNode;

        length++;

        return true;
    }

    bool insertAtPosition(int position, int value)
    {
        /*
            Validate position, 0 < position <= length + 1
            If head == nullptr then call insertAtBeginning
            If length == 1 then call insertAtBeginning
            If position == length then call insertAtEnd
            For other cases, loop till the previous position, then create newNode with newNode->next to currentNode->next, point currentNode->next to newNode
        */

        if (position < 1 || position > length + 1)
        {
            cout << "Invalid position: " << position << "\n";
            return false;
        }

        if (position == 1)
        {
            return insertAtBeginning(value);
        }

        if (position == length + 1)
        {
            return insertAtEnd(value);
        }

        Node *currentNode = head;

        for (int i = 2; i < position; i++)
        {
            currentNode = currentNode->next;
        }

        Node *newNode = new Node(value);
        newNode->next = currentNode->next;
        currentNode->next = newNode;

        length++;

        cout << "Inserted: " << value << " at position: " << position << "\n";

        return true;
    }

    bool removeAtPosition(int position)
    {
        /*
            Validate position, 0 < position <= length
            If head == nullptr, return false
            If position == 1
                If length == 1, then delete head and head = tail = nullptr
                If position == 1 and length > 1, then store head->next in secondNode and delete head, and then head = secondNode
            For other cases, loop till the previous node of position, store nodeToBeDelete = currentNode->next and point currentNode->next to nodeToBeDeleted->next
        */

        if (position < 1 || position > length)
        {
            cout << "Invalid position: " << position << "\n";

            return false;
        }

        if (head == nullptr)
        {
            return false;
        }

        if (position == 1)
        {
            if (length == 1)
            {
                delete head;
                head = tail = nullptr;
            }
            else
            {
                Node *secondNode = head->next;
                delete head;
                head = secondNode;
                tail->next = head;
            }

            length--;
            return true;
        }

        Node *current = head;

        for (int i = 2; i < position; i++)
        {
            current = current->next;
        }

        Node *nodeToBeDeleted = current->next;

        current->next = nodeToBeDeleted->next;

        if (nodeToBeDeleted == tail)
            tail = current;

        delete nodeToBeDeleted;

        length--;

        cout << "Removed at position: " << position << "\n";

        return true;
    }

    bool removeByValue(int value)
    {
        /*
            If list length == 0, return immediately
            If list length == 1 and value found at first, head = tail = nullptr
            For the rest, loop the whole list using while loop, remove the node when found
                If list length != 1 and value is found at last node, point secondLastNode to head, then delete tail and tail = secondLastNode
                For other positions, store nodeToBeDelete = currentNode->next and point currentNode->next to nodeToBeDeleted->next
        */

        if (head == nullptr)
        {
            return false;
        }

        if (value == head->data)
        {

            if (length == 1)
            {
                delete head;
                head = tail = nullptr;
            }
            else
            {
                Node *newHead = head->next;
                delete head;
                head = newHead;
                tail->next = head;
            }

            length--;

            cout << "Deleted: " << "value\n";

            return true;
        }

        Node *current = head;

        for (int i = 2; i < length; i++)
        {
            if (current->next->data == value)
            {
                break;
            }

            current = current->next;

            if (i == length - 1)
            {
                return false;
            }
        }

        Node *nodeToBeDeleted = current->next;

        current->next = nodeToBeDeleted->next;
        delete nodeToBeDeleted;

        if (nodeToBeDeleted == tail)
        {
            tail = current;
        }

        cout << "Removed: " << value << "\n";

        length--;

        return true;
    }

    bool search(int value)
    {
        /*
            Loop using for loop and length property
        */

        Node *current = head;

        /*
            1->2->3->4

            1. current = 1
            2. i = 1; check value and do current = 2 if not matched
            3. i = 2; check value and do current = 3 if not matched
            4. i = 3; check value and do current = 4 if not matched
            5. i = 4; check value and do current = 1 if not matched
            6. i = 5; conditions fails
        */

        for (int i = 1; i <= length; i++)
        {
            if (current->data == value)
            {
                cout << "Value found: " << value << "\n";
                return true;
            }

            current = current->next;
        }

        cout << "Value not found: " << value << "\n";

        return false;
    }

    void printList()
    {
        /*
            Loop using for loop and length property
        */

        Node *current = head;

        for (int i = 1; i <= length; i++)
        {
            cout << current->data << " -> ";
            current = current->next;
        }

        cout << "head\n";
    }
};

int main()
{

    CircularSinglyLinkedList circularSinglyLinkedList;

    circularSinglyLinkedList.insertAtBeginning(1);
    circularSinglyLinkedList.printList();

    circularSinglyLinkedList.insertAtEnd(2);
    circularSinglyLinkedList.printList();

    circularSinglyLinkedList.insertAtPosition(3, 3);
    circularSinglyLinkedList.printList();

    circularSinglyLinkedList.search(3);

    return 0;
}