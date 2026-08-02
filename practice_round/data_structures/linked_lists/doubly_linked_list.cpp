/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

struct Node
{
    int data;
    Node *next;
    Node *prev;

    Node(int value)
    {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList
{
private:
    Node *head;
    Node *tail;
    int length;

public:
    DoublyLinkedList()
    {
        head = tail = nullptr;
        length = 0;
    }

    ~DoublyLinkedList()
    {
        Node *currentNode = head;

        while (currentNode != nullptr)
        {
            Node *nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }

        head = tail = nullptr;
        length = 0;
    }

    int insertAtBeginning(int value)
    {
        /*
            If head is nullptr then insert newNode at head and head = tail = newNode
            If one or more nodes exit then point newNode to existing head and point head to newNode
        */

        Node *newNode = new Node(value);

        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        length++;
        cout << "Inserted " << value << " at beginning\n";

        return true;
    }

    int insertAtEnd(int value)
    {
        /*
            If head is nullptr then call insertAtBeginning()
            If one or more nodes exist then point newNode to existing tail and point tail to newNode
        */

        if (head == nullptr)
        {
            return insertAtBeginning(value);
        }

        Node *newNode = new Node(value);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;

        length++;

        cout << "Inserted " << value << " at end\n";
        return true;
    }

    int insertAtPosition(int position, int value)
    {
        /*
            Check for valid position, it should be >=1 and < length + 1
            If position is 1
                If head is nullptr then call insertAtBeginning()
                If only one node exists then point newNode to existing head and assign head as newNode
            If position is equal to length then call insertAtEnd()
            If position is equal to length + 1 then call insertAtEnd()
            For other cases, loop till the prevNode of position, then store prevNode->next into a temp variable and point prevNode to newNode and newNode to temp variable address
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

        for (int i = 1; i < position - 1; i++)
        {
            currentNode = currentNode->next;
        }

        Node *nextNode = currentNode->next;
        Node *newNode = new Node(value);
        currentNode->next = newNode;
        newNode->next = nextNode;
        nextNode->prev = newNode;
        newNode->prev = currentNode;

        length++;

        cout << "Inserted at position: " << position << " value " << value << "\n";

        return true;
    }

    int removeAtPosition(int position)
    {
        /*
            Check if valid position, it should be >=1 and <=length
            If head is nullptr then return
            If position is 1 and their is only 1 node then remove that and point head = tail = null
            For other cases, loop till prevNode of position, then store prevNode->next into a currentNode and point prevNode->next to currentNode->next and delete currentNode
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

            if (length > 1)
            {
                Node *temp = head->next;
                delete head;
                head = temp;
                head->prev = nullptr;
            }

            length--;

            cout << "Removed at position " << position << "\n";

            return true;
        }

        if (position == length)
        {
            Node *secondLastNode = tail->prev;
            secondLastNode->next = nullptr;
            delete tail;
            tail = secondLastNode;

            length--;

            cout << "Removed at position " << position << "\n";

            return true;
        }

        Node *currentNode = head;

        for (int i = 2; i < position; i++)
        {
            currentNode = currentNode->next;
        }

        Node *nextNode = currentNode->next;
        currentNode->next = nextNode->next;
        nextNode->next->prev = currentNode;
        delete nextNode;

        length--;

        cout << "Removed at position " << position << "\n";

        return true;
    }

    int search(int value)
    {
        /*
            If head is nullptr then return
            For other cases, loop using while loop till the value is found
        */

        if (head == nullptr)
        {
            return false;
        }

        Node *currentNode = head;

        while (currentNode != nullptr)
        {
            if (currentNode->data == value)
            {
                return true;
            }

            currentNode = currentNode->next;
        }

        return false;
    }

    void printList()
    {
        /*
            If head is nullptr then print list is empty
            For other cases, print using while loop
        */

        if (head == nullptr)
        {
            cout << "List is empty\n";
            return;
        }

        Node *currentNode = head;

        cout << "List: ";

        while (currentNode != nullptr)
        {
            cout << currentNode->data << " -> ";

            currentNode = currentNode->next;
        }

        cout << "nullptr\n";

        return;
    }

    void printReverseList()
    {
        if (tail == nullptr)
        {
            cout << "list is empty\n";
            return;
        }

        Node *currentNode = tail;

        cout << "List in reverse: ";

        while (currentNode != nullptr)
        {
            cout << currentNode->data << " -> ";

            currentNode = currentNode->prev;
        }

        cout << "nullptr\n";

        return;
    }
};

int main()
{

    DoublyLinkedList doublyLinkedList;

    doublyLinkedList.insertAtBeginning(1);
    doublyLinkedList.printList();

    doublyLinkedList.insertAtEnd(2);
    doublyLinkedList.printList();

    doublyLinkedList.insertAtPosition(3, 3);
    doublyLinkedList.printList();

    doublyLinkedList.search(3);

    doublyLinkedList.printReverseList();

    return 0;
}

/*
            ############################################# Practice round 2 #############################################
*/