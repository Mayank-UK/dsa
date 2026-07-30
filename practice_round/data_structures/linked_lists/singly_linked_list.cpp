/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// using namespace std;

// struct Node
// {
//     int data;
//     Node *next;

//     Node(int value)
//     {
//         data = value;
//         next = nullptr;
//     }
// };

// class SinglyLinkedList
// {
// private:
//     Node *head;
//     Node *tail;
//     int length;

// public:
//     SinglyLinkedList()
//     {
//         head = tail = nullptr;
//         length = 0;
//     }

//     ~SinglyLinkedList()
//     {
//         Node *current = head;

//         while (current != nullptr)
//         {
//             Node *next = current->next;
//             delete current;
//             current = next;
//         }

//         head = tail = nullptr;
//         length = 0;
//     }

//     bool insertAtBeginning(int value)
//     {
//         Node *newNode = new Node(value);

//         if (head == nullptr)
//         {
//             head = tail = newNode;
//         }
//         else
//         {
//             newNode->next = head;
//             head = newNode;
//         }

//         length++;

//         cout << "Inserted at beginning: " << value << "\n";

//         return true;
//     }

//     bool insertAtEnd(int value)
//     {
//         Node *newNode = new Node(value);

//         if (head == nullptr)
//         {
//             head = tail = newNode;
//         }
//         else
//         {
//             tail->next = newNode;
//             tail = newNode;
//         }

//         length++;

//         cout << "Inserted at end: " << value << "\n";

//         return true;
//     }

//     bool insertAtPosition(int position, int value)
//     {
//         if (position < 1 || position > length + 1)
//         {
//             cout << "Invalid position\n";
//             return false;
//         }

//         if (position == 1)
//         {
//             return insertAtBeginning(value);
//         }

//         if (position == length + 1)
//         {
//             return insertAtEnd(value);
//         }

//         Node *currentNode = head;

//         for (int i = 1; i < position - 1; i++)
//         {
//             currentNode = currentNode->next;
//         }

//         Node *newNode = new Node(value);

//         newNode->next = currentNode->next;
//         currentNode->next = newNode;

//         length++;

//         cout << "Inserted at position: " << position << "\n";

//         return true;
//     }

//     bool deleteByValue(int value)
//     {
//         if (head == nullptr)
//         {
//             return false;
//         }

//         if (head->data == value)
//         {
//             if (head->next == nullptr)
//             {
//                 delete head;
//                 head = tail = nullptr;
//             }
//             else
//             {
//                 Node *newHead = head->next;
//                 delete head;
//                 head = newHead;
//             }

//             cout << "Deleted value: " << value << "\n";

//             length--;

//             return true;
//         }
//         else
//         {
//             Node *prevNode = head;
//             Node *currentNode = head;

//             while (currentNode != nullptr)
//             {
//                 if (currentNode->data == value)
//                 {
//                     prevNode->next = currentNode->next;

//                     if (currentNode->next == nullptr)
//                     {
//                         tail = prevNode;
//                     }

//                     delete currentNode;

//                     length--;

//                     cout << "Deleted value: " << value << "\n";

//                     return true;
//                 }

//                 prevNode = currentNode;
//                 currentNode = currentNode->next;
//             };
//         }

//         return false;
//     }

//     bool deleteByPosition(int position)
//     {
//         if (position < 1 || position > length)
//         {
//             cout << "Invalid position: " << position << "\n";

//             return false;
//         }

//         if (head == nullptr)
//         {
//             return false;
//         }

//         if (position == 1)
//         {
//             if (head->next == nullptr)
//             {
//                 delete head;
//                 head = tail = nullptr;
//             }
//             else
//             {
//                 Node *nextNode = head->next;
//                 delete head;
//                 head = nextNode;
//             }

//             length--;

//             return true;
//         }

//         Node *currentNode = head;

//         for (int i = 1; i < position - 1; i++)
//         {
//             currentNode = currentNode->next;
//         }

//         Node *nodeToDelete = currentNode->next;
//         currentNode->next = nodeToDelete->next;

//         if (nodeToDelete == tail)
//         {
//             tail = currentNode;
//         }

//         delete nodeToDelete;

//         length--;

//         cout << "Deleted at position: " << position << "\n";

//         return true;
//     }

//     bool search(int value)
//     {
//         Node *currentNode = head;

//         while (currentNode != nullptr)
//         {
//             if (currentNode->data == value)
//             {
//                 cout << value << " : value found\n";
//                 return true;
//             }

//             currentNode = currentNode->next;
//         }

//         cout << value << " : value not found\n";

//         return false;
//     }

//     void printLinkedList()
//     {
//         Node *currentNode = head;

//         cout << "list: ";

//         while (currentNode != nullptr)
//         {
//             cout << currentNode->data << "->";
//             currentNode = currentNode->next;
//         }

//         cout << "nullptr\n";
//     }
// };

// int main()
// {
//     SinglyLinkedList singlyLikedList;

//     singlyLikedList.insertAtBeginning(1);
//     singlyLikedList.printLinkedList();

//     singlyLikedList.insertAtEnd(2);
//     singlyLikedList.printLinkedList();

//     singlyLikedList.insertAtPosition(3, 3);
//     singlyLikedList.printLinkedList();

//     singlyLikedList.search(3);
// }

/*
            ############################################# Practice round 2 #############################################
*/
