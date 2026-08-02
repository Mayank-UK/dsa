/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

struct Node
{
    int data;
    Node *prev;
    Node *next;

    Node(int value)
    {
        data = value;
        prev = next = nullptr;
    }
};

class CircularDoublyLinkedList
{
private:
    Node *head;
    Node *tail;
    int length;

public:
    CircularDoublyLinkedList()
    {
        head = tail = nullptr;
        length = 0;
    }

    ~CircularDoublyLinkedList()
    {
        Node *current = head;

        /*
            1->2->3

            1. i = 1, 1 <= 3 is true, curent = 1, then current = 2
            2. i = 2, 2 <= 3 is true,  current = 2, then current = 3
            3. i = 3, 3 <= 3 is true, current = 3, then current = 1 again

            Simple logic is, that if there are 3 nodes then it will take 3 iterations to delete those nodes
        */

        for (int i = 1; i <= length; i++)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }

        head = tail = nullptr;
        length = 0;
    }

    bool insertAtBeginning(int value)
    {
        /*
            1. If head == nullptr
                - head = tail = newNode
                - newNode->next = head
                - length++
            2. If length >= 1
                - newNode->next = head
                - newNode->prev = tail
                - head->prevNode = newNode
                - head = newNode
                - tail->next = head
                - length++
        */

        Node *newNode = new Node(value);

        if (head == nullptr)
        {
            head = tail = newNode;
            newNode->next = newNode->prev = newNode;

            cout << "Inserted: " << value << " at beginning\n";

            length++;

            return true;
        }

        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        head = newNode;
        tail->next = head;

        length++;

        cout << "Inserted: " << value << " at beginning\n";

        return true;
    }

    bool insertAtEnd(int value)
    {
        /*
            1. If head == nullptr
                - call insertAtBeginning
            2. If length == 1
                - newNode->next = head
                - newNode->prev = tail
                - head->prevNode = newNode
                - tail = newNode
                - length++
            2. For other cases
                - newNode->next = head
                - newNode->prev = tail
                - head->prev = newNode
                - tail->next = newNode
                - tail = newNode
                - length++
        */

        if (head == nullptr)
        {
            return insertAtBeginning(value);
        }

        Node *newNode = new Node(value);

        tail->next = newNode;
        head->prev = newNode;
        newNode->next = head;
        newNode->prev = tail;
        tail = newNode;

        length++;

        cout << "Inserted: " << value << " at the end\n";

        return true;
    }

    bool insertAtPosition(int position, int value)
    {
        /*
            1. If head == nullptr or position == 1
                - call insertAtBeginning
            2. If position == length
                - call insertAtEnd
            3. For other cases
                - loop till the previous position
                - currentNode->next = newNode
                - newNode->prev = currentNode
                - newNode->next = currentNode->next
                - currentNode->next->prev = newNode
                - length++
        */

        if (position < 1 || position > length + 1)
        {
            cout << "Invalid position: " << position << " \n";

            return false;
        }

        if (head == nullptr || position == 1)
        {
            return insertAtBeginning(value);
        }

        if (position == length + 1)
        {
            return insertAtEnd(value);
        }

        Node *current = head;

        /*
            1->2->3

            Insert at position 2

            int i = 1, 1 < 2 is true
            int i = 2, 2 < 2 is false
        */

        for (int i = 1; i < position - 1; i++)
        {
            current = current->next;
        }

        Node *newNode = new Node(value);

        newNode->next = current->next;
        newNode->prev = current;
        current->next = newNode;
        newNode->next->prev = newNode;

        length++;

        cout << "Inserted: " << value << " at the position: " << position << "\n";

        return true;
    }

    bool removeAtPosition(int position)
    {
        /*
            1. If head == nullptr
                - return false
            2. If position == 1
                - delete head
                - head = tail = nullptr
                - length--
            3. If position == length
                - tail->prev->next = head
                - head->prev = tail->prev
                - delete tail
                - tail = head->prev
                - length--
            4. For other cases
                - loop till the previous position
                - nextNode = currentNode->next
                - currentNode->next = nextNode->next
                - nextNode->next->prev = currentNode
                - delete nextNode
                - length--
        */

        if (position < 1 || position >= length + 1)
        {
            cout << "Invalid position: " << position << " \n";

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
                Node *newHead = head->next;

                newHead->prev = tail;

                delete head;

                head = newHead;
                tail->next = newHead;
            }

            length--;

            cout << "Removed from position: " << position << "\n";

            return true;
        }

        if (position == length)
        {
            tail->prev->next = head;
            head->prev = tail->prev;
            delete tail;

            tail = head->prev;
            length--;

            cout << "Removed from position: " << position << "\n";

            return true;
        }

        Node *current = head;

        for (int i = 1; i < position - 1; i++)
        {
            current = current->next;
        }

        Node *nextNode = current->next;
        current->next = nextNode->next;
        nextNode->next->prev = current;
        delete nextNode;

        length--;

        cout << "Removed from position: " << position << "\n";

        return true;
    }

    bool removeByValue(int value)
    {
        /*
            1. If head = nullptr
                - return false
            2, If head->value == value
                - delete head
                - head = tail = nullptr
                - length --
            3. For other cases
                - loop till the previous position
                - compare value, and if found
                - nextNode = currentNode->next
                - currentNode->next = nextNode->next
                - nextNode->next->prev = currentNode
                - delete nextNode
                - length--
        */

        if (head == nullptr)
        {
            return false;
        }

        if (head->data == value)
        {

            if (length == 1)
            {
                delete head;

                head = tail = nullptr;
            }
            else
            {
                Node *newHead = head->next;

                newHead->prev = tail;

                tail->next = newHead;

                delete head;

                head = newHead;
            }

            length--;

            cout << "Removed value: " << value << "\n";

            return true;
        }

        if (tail->data == value)
        {
            Node *newTail = tail->prev;
            head->prev = newTail;
            newTail->next = head;

            delete tail;

            tail = newTail;

            length--;

            cout << "Removed value: " << value << "\n";

            return true;
        }

        Node *current = head;

        for (int i = 1; i <= length; i++)
        {
            if (current->data == value)
            {
                Node *prev = current->prev;
                Node *next = current->next;

                prev->next = next;
                next->prev = prev;

                delete current;

                length--;

                cout << "Removed value: " << value << "\n";

                return true;
            }

            current = current->next;
        }

        return false;
    }

    bool search(int value)
    {
        /*
            1. Loop through the list and compare
        */

        Node *current = head;

        for (int i = 1; i <= length; i++)
        {
            if (current->data == value)
            {
                cout << "Value found at position: " << i << "\n";

                return true;
            }

            current = current->next;
        }

        cout << "Value not found\n";

        return false;
    }

    void printList()
    {
        /*
            1. Loop through the list and print based on length
        */

        Node *current = head;

        cout << "List: ";

        for (int i = 1; i <= length; i++)
        {
            cout << current->data << "->";
            current = current->next;
        }

        cout << "head\n";
    }

    void printListReverse()
    {
        /*
            1. Loop through the list and print based on length
        */

        Node *current = tail;

        cout << "ListReversed: ";

        for (int i = 1; i <= length; i++)
        {
            cout << current->data << "->";
            current = current->prev;
        }

        cout << "tail\n";
    }
};

int main()
{

    CircularDoublyLinkedList circularDoublyLinkedList;

    circularDoublyLinkedList.insertAtBeginning(1);
    circularDoublyLinkedList.printList();

    circularDoublyLinkedList.insertAtEnd(2);
    circularDoublyLinkedList.printList();

    circularDoublyLinkedList.insertAtPosition(3, 3);
    circularDoublyLinkedList.printList();

    circularDoublyLinkedList.search(3);

    return 0;
}