/*
    Optimize the code below according to design principals
*/

//data structures

//array
/*
#include<iostream>
using namespace std;

int main() {
    int arr[10];
    
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        arr[i] = i;
    }
    
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        cout<<arr[i];
    }
    
    return 0;
}
*/

//stl array
/*
#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> arr;
    arr.push_back(0);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    
    for(int i = 0; i < arr.size(); i++) {
        cout<<arr[i];
    }
    
    return 0;
}
*/

//singly-linked list
/*
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Singly_linked_list {
    public:
        struct Node* head = NULL;
        struct Node* tail = NULL;
        
        void push_head(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            
            if(list_size() < 1) {
                new_node->next = NULL;
                head = new_node;
                tail = head;
                
                return;
            }
            
            new_node->next = head;
            head = new_node;
        }
        
        void push_tail(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            new_node->next = NULL;
            
            if(list_size() < 1) {
                head = new_node;
                tail = head;
                
                return;
            }
            
            tail->next = new_node;
            tail = new_node;
        }
        
        void pop_head() {
            if(list_size() > 0) {
                struct Node* new_head = head->next;
                delete head;
                head = new_head;   
            }
        }
        
        void pop_tail() {
            int size = list_size();
            
            if(size < 1) {
                return;    
            }
            
            if(size == 1) {
                delete head;
                head = NULL;
                tail = head;
                
                return;
            }
            
            struct Node* current = head;
            int count = 1;
            
            while(current != NULL) {
                if(count == size-1) {
                    current->next = NULL;
                    delete tail;
                    tail = current;
                }
                
                current = current->next;
                count++;
            }
        }
        
        void remove_node(int data) {
            struct Node* current = head;
            struct Node* prev = NULL;
            
            if(current != NULL) { 
                if(current->data == data) {
                    head = current->next;
                    delete current;
                    
                    return;   
                }
            } 
            
            while(current != NULL && current->data != data) {
                prev = current;
                current = current->next;
            }
            
            if(current == NULL) {
                return;
            }

            if(current->next == NULL) {
                tail = current;
            }
            
            prev->next = current->next;
            delete current;
        }
        
        int list_size() {
            struct Node* current = head;
            int count = 0;
            
            while(current != NULL) {
                current = current->next;
                count++;
            }
            
            return count;
        }
        
        void print() {
            struct Node* current = head;
            while(current != NULL) {
                cout<<current->data<<" ";
                current = current->next;
            }
        }
};

int main()
{
    Singly_linked_list list;
    
    list.push_head(1);
    list.push_head(2);
    
    list.push_tail(3);
    list.push_tail(4);
    
    cout<<"before update: ";
    list.print();
    cout<<endl;
    
    //list.pop_head();
    //list.pop_tail();
    
    list.remove_node(1);

    cout<<"after update: ";
    list.print();
   
    return 0;
}
*/


//doubly-linked list
/*
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

class Doubly_linked_list {
    public:
        struct Node* head = NULL;
        struct Node* tail = NULL;
        
        void push_head(int data) {
            
            struct Node* new_node = new Node;
            new_node->data = data;
            new_node->prev = NULL;
            
            if(list_size() < 1) {
                new_node->next = NULL;
                head = new_node;
                tail = head;
                
                return;
            }
            
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        
        void push_tail(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            new_node->next = NULL;
            
            if(list_size() < 1) {
                new_node->prev = NULL;
                head = new_node;
                tail = new_node;
                
                return;
            }
            
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        
        void pop_head() {
            if(list_size() < 1) {
                return;
            }
            
            if(list_size() == 1) {
                delete head;
                head = NULL;
                tail = head;
                
                return;
            }
            
            struct Node* new_head = head->next;
            new_head->prev = NULL;
            delete head;
            head = new_head;
        }
        
        void pop_tail() {
            int size = list_size();
            
            if(size < 1) {
                return;
            }
            
            if(size == 1) {
                delete head;
                head = NULL;
                tail = head;
                
                return;
            }
            
            struct Node* current = head;
            int count = 1;
            while(current != NULL) {
                if(count == size-1) {
                    current->next = NULL;
                    delete tail;
                    tail = current;
                }
                
                current = current->next;
                count++;
            }
        }
        
        void remove_node(int data) {
            struct Node* current = head;
            
            if(current != NULL) { 
                if(current->data == data) {
                    head = current->next;
                    head->prev = NULL;
                    delete current;
                    
                    return;   
                }
            } 
            
            while(current != NULL && current->data != data) {
                current = current->next;
            }
            
            if(current == NULL) {
                return;
            }

            if(current->next == NULL) {
                tail = current->prev;
            }
            
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        
        int list_size() {
            struct Node* current = head;
            int count = 0;
            
            while(current != NULL) {
                current = current->next;
                count++;
            }
            
            return count;
        }
        
        void print() {
            struct Node* current = head;
            while(current != NULL) {
                cout<<current->data<<" ";
                current = current->next;
            }
        }
        
        void print_reverse() {
            struct Node* current = tail;
            while(current != NULL) {
                cout<<current->data<<" ";
                current = current->prev;
            }
        }
};

int main() {
    Doubly_linked_list list;
    
    list.push_head(1);
    list.push_head(2);
    
    list.push_tail(3);
    list.push_tail(4);
    
    cout<<"(before update)"<<endl;
    cout<<"head -> tail: ";
    list.print();
    cout<<endl;
    cout<<"tail -> head: ";
    list.print_reverse();
    cout<<endl<<endl;
    
    //list.pop_head();
    //list.pop_tail();
    
    list.remove_node(2);
    
    cout<<"(after update)"<<endl;
    cout<<"head -> tail: ";
    list.print();
    cout<<endl;
    cout<<"tail -> head: ";
    list.print_reverse();
    
    return 0;
}
*/

//single circular linked list
/*
#include<iostream>
using namespace std;

struct Node {
    int data;
    struct Node* next;
};

class Singly_circular_list {
    public:
        struct Node* head = NULL;
        struct Node* tail = NULL;
        
        void push(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            
            if(list_size() < 1) {
                new_node->next = new_node;
                head = new_node;
                tail = head;
                
                return;
            }
            
            tail->next = new_node;
            tail = new_node;
        }
        
        void pop() {
            int size = list_size();
            
            if(size < 1) {
                return;
            }
            
            if(size == 1) {
                delete head;
                head = NULL;
                tail = NULL;
                
                return;
            }
            
            struct Node* current = head;
            for(int i = 1; i <= size; i++) {
                if(i == size-1) {
                    current->next = head;
                    delete tail;
                    tail = current;
                    
                    break;
                }
                
                current = current->next;
            }   
        }
        
        int list_size() {
            struct Node* current = head;
            int count = 0;
            while(current!= NULL && current != tail) {
                current = current->next;
                count++;
            }
            
            if(head == NULL) {
                return count;    
            }
            
            return count+1;
        }
        
        void print() {
            int size = list_size();
            
            if(size < 1) {
                return;
            }
            
            struct Node* current = head;
            for(int i = 1; i <= size; i++) {
                cout<<current->data<<" ";
                current = current->next;
            }   
        }
};

int main() {
    Singly_circular_list list;
    
    list.push(1);
    list.push(2);
    
    cout<<"(before update)"<<endl;
    list.print();
    cout<<endl<<endl;
    
    list.pop();
    
    cout<<"(after update)"<<endl;
    list.print();
    cout<<endl<<endl;
    
    return 0;
}
*/

//double circular linked list
/*
#include<iostream>
using namespace std;

struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
};

class Doubly_circular_list {
    public:
        struct Node* head = NULL;
        struct Node* tail = NULL;
        
        void push(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            
            if(list_size() < 1) {
                new_node->prev = new_node;
                new_node->next = new_node;
                head = new_node;
                tail = head;
                
                return;
            }
            
            new_node->prev = tail;
            new_node->next = head;
            tail->next = new_node;
            tail = new_node;
        }
        
        void pop() {
            int size = list_size();
            
            if(size < 1) {
                return;
            }
            
            if(size == 1) {
                delete head;
                head = NULL;
                tail = NULL;
                
                return;
            }
            
            struct Node* current = head;
            for(int i = 1; i <= size; i++) {
                if(i == size-1) {
                    current->next = head;
                    delete tail;
                    tail = current;
                    
                    break;
                }
                
                current = current->next;
            }   
        }
        
        int list_size() {
            struct Node* current = head;
            int count = 0;
            while(current!= NULL && current != tail) {
                current = current->next;
                count++;
            }
            
            if(head == NULL) {
                return count;    
            }
            
            return count+1;
        }
        
        void print() {
            int size = list_size();
            
            if(size < 1) {
                return;
            }
            
            struct Node* current = head;
            for(int i = 1; i <= size; i++) {
                cout<<current->data<<" ";
                current = current->next;
            }   
        }
        
        void print_reverse() {
            int size = list_size();
            
            if(size < 1) {
                return;
            }
            
            struct Node* current = tail;
            for(int i = 1; i <= size; i++) {
                cout<<current->data<<" ";
                current = current->prev;
            }   
        }
};

int main() {
    Doubly_circular_list list;
    
    list.push(1);
    list.push(2);
    
    cout<<"(before update)"<<endl;
    cout<<"print: ";
    list.print();
    cout<<endl;
    cout<<"print_reverse: ";
    list.print_reverse();
    cout<<endl<<endl;
    
    list.pop();
    
    cout<<"(after update)"<<endl;
    cout<<"print: ";
    list.print();
    cout<<endl;
    cout<<"print_reverse: ";
    list.print_reverse();
    cout<<endl<<endl;
    
    return 0;
}
*/

//STL linked list
/*
#include<iostream>
#include<list>
using namespace std;

int main() {
    list<int> list_1;
    
    list_1.push_back(1);
    list_1.push_front(2);
    
    //list_1.pop_back();
    //list_1.pop_front();
    
    for (auto it = list_1.begin(); it != list_1.end(); it++) {
        cout<<*it<<" ";   
    }
    
    return 0;
}
*/

//stack
/*
#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

class Stack {
    public:
        struct Node* top = NULL;
        
        void push(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            
            if(stack_size() < 1) {
                new_node->next = NULL;
                top = new_node;
                
                return;
            }
            
            new_node->next = top;
            top = new_node;
        }
        
        void pop() {
            if(stack_size() < 1) {
                return;
            }
            
            if(stack_size() == 1) {
                delete top;
                top = NULL;
                
                return;
            }
            
            struct Node* new_top = top->next;
            delete top;
            top = new_top;
        }
        
        int stack_size() {
            struct Node* current = top;
            int count = 0;
            while(current != NULL) {
                current = current->next;
                count++;
            }
            
            return count;
        }
        
        void print() {
            struct Node* current = top;
            while (current != NULL) {
                cout<<current->data;
                current = current->next;
            }
        }
};

int main() {
    Stack stack;
    
    stack.push(1);
    stack.push(2);
    
    cout<<"(before update)"<<endl;
    cout<<"stack: ";
    stack.print();
    cout<<endl;
    
    stack.pop();
    
    cout<<"(after update)"<<endl;
    cout<<"stack: ";
    stack.print();
    
    return 0;
}
*/

//STL stack
/*
#include<iostream>
#include<stack>
using namespace std;

int main() {
    stack<int> stack_1;
    
    stack_1.push(1);
    stack_1.push(2);
    
    //stack_1.pop();
    //stack_1.pop();
    
    while (!stack_1.empty()) 
    { 
        cout<<stack_1.top(); 
        stack_1.pop(); 
        cout<<endl;
    } 
    
    return 0;
}
*/

//queue
/*
#include<iostream>
using namespace std;

struct Node {
    int data;
    struct Node* next;
};

class Queue {
    public:
        struct Node* first = NULL;
        struct Node* last = NULL;
        
        void enqueue(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            new_node->next = NULL;
            
            if(queue_size() < 1) {
                first = new_node;
                last = new_node;
                
                return;
            }
            
            last->next = new_node;
            last = new_node;
        }
        
        void dequeue() {
            if(queue_size() < 1) {
                return;
            }
            
            if(queue_size() == 1) {
                delete first;
                first = NULL;
                last = NULL;
                
                return;
            }
            
            struct Node* next_new = first->next;
            delete first;
            first = next_new;
        }
        
        int queue_size() {
            struct Node* current = first;
            int count = 0;
            while(current != NULL) {
                current = current->next;
                count++;
            }
            
            return count;
        }
        
        void print() {
            struct Node* current = first;
            while(current != NULL) {
                cout<<current->data<<" ";
                current = current->next;
            }
        }
};

int main() {
    Queue queue;
    
    queue.enqueue(1);
    queue.enqueue(2);
    
    cout<<"(before update)"<<endl;
    cout<<"queue is: ";
    queue.print();
    cout<<endl;
    
    queue.dequeue();
    
    cout<<"(after update)"<<endl;
    cout<<"queue is: ";
    queue.print();
    cout<<endl;
    
    return 0;
}
*/

//priority queue implemented using heap
/*
#include<iostream>
#include<vector>
using namespace std;

struct Node {
    int data;
};

class Priority_queue {
    private:
        vector<struct Node*> heap;
        
        void heapify_insert(int parent, int child) {
            if(child <= 0) {
                return;
            }
            
            if(heap[parent]->data >= heap[child]->data) {
                return;
            }
            
            struct Node* temp = heap[parent];
            heap[parent] = heap[child];
            heap[child] = temp;
            
            child = parent;
            parent = (int)(child-1)/2;
            heapify_insert(parent, child);
        }
        
        void heapify_delete(int parent, int first_child, int second_child) {
            if(heap.size() == 0) {
                return;    
            }
            
            if(parent >= heap.size()-1 || first_child >= heap.size() || second_child >= heap.size()) {
                return;
            }
            
            if(heap.size() == 3) {
                if(heap[parent]->data < heap[first_child]->data) {
                    struct Node* temp = heap[parent];
                    heap[parent] = heap[first_child];
                    heap[first_child] = temp;
                    
                    parent = first_child;
                }
            }
            
            if(heap[parent]->data >= heap[first_child]->data && heap[parent]->data >= heap[second_child]->data) {
                return;
            }
            else if(heap[first_child]->data > heap[second_child]->data) {
                struct Node* temp = heap[parent];
                heap[parent] = heap[first_child];
                heap[first_child] = temp;
                
                parent = first_child;
            }
            else{
                struct Node* temp = heap[parent];
                heap[parent] = heap[second_child];
                heap[second_child] = temp;
            
                parent = second_child;
            }
            
            first_child = 2*parent+1;
            second_child = 2*parent+2;
            
            heapify_delete(parent, first_child, second_child);
        }
        
    public:
        struct Node* top() {
            return heap[0];
        }
        
        void push(int data) {
            struct Node* new_node = new Node;
            new_node->data = data;
            
            heap.push_back(new_node);
            
            int child = heap.size()-1;
            int parent = (int)(child-1)/2;
            
            heapify_insert(parent, child);
        }
        
        void pop() {
            int parent;
            int first_child;
            int second_child;
            
            heap[0] = heap[heap.size()-1];
            heap.pop_back();
            parent = 0;
            first_child = 2*parent+1;
            second_child = 2*parent+2;
            
            heapify_delete(parent, first_child, second_child);
        }
        
        bool empty() {
            if(heap.size() > 0) {
                return false;
            }
            
            return true;
        }
};

int main() {
    Priority_queue pq;
    
    pq.push(2);
    pq.push(5);
    pq.push(7);
    pq.push(6);
    pq.push(8);
    pq.push(8);

    while(!pq.empty()) {
        cout<<pq.top()->data<<endl;
        pq.pop();
    }
    
    return 0;
}
*/

//STL queue
/*
#include<iostream>
#include<queue>
using namespace std;

int main() {
    queue<int> queue_1;
    
    queue_1.push(1);
    queue_1.push(2);
    
    //queue_1.pop();
    //queue_1.pop();
    
    while (!queue_1.empty()) 
    { 
        cout<<queue_1.front(); 
        queue_1.pop(); 
        cout<<endl;
    } 
    
    return 0;
}
*/

//stl priority queue
/*
#include<iostream>
#include<queue>
using namespace std;

int main() {
    priority_queue<int> pq;
    
    pq.push(4);
    pq.push(3);
    pq.push(6);
    pq.push(1);
    
    while (!pq.empty()) { 
        cout<<pq.top()<<endl; 
        pq.pop(); 
    } 
    
    return 0;
}
*/

//hash table
/*
#include<iostream>
#include<string>
using namespace std;

struct Node {
    string key = "";
    string value = "";
    struct Node* next = NULL;
};

class Hash_table {
    private:
        int size = 100;
        struct Node* hash_table = new Node[size]();
        
        int hash_key(string key) {
            int sum = 0;
            
            for(int i = 0; i < key.length(); i++) {
                sum = sum+(int)key[i];
            }
            
            return sum % size;
        }
    public:
        void insert_key(string key, string value) {
            int index = hash_key(key);
            
            if(index_size(index) < 1) {
                hash_table[index].key = key;
                hash_table[index].value = value;
                
                return;
            }
            
            if(index_size(index) == 1) {
                if(hash_table[index].key == key) {
                    hash_table[index].value = value;
                    
                    return;
                }
                
                struct Node* new_node = new Node;
                new_node->key = key;
                new_node->value = value;
                hash_table[index].next = new_node;
                
                return;
            }
            
            struct Node* current = &hash_table[index];
            while(current != NULL && current->key != "") {
                if(current->key == key) {
                    current->value = value;
                    
                    return;
                }
                current = current->next;
            }
            
            struct Node* last_node = index_last_node(index);
            struct Node* new_node = new Node;
            new_node->key = key;
            new_node->value = value;
            last_node->next = new_node;
        }
        
        void delete_key(string key) {
            int index = hash_key(key);
            
            if(index_size(index) < 1) {
                return;
            }
            
            if(index_size(index) == 1) {
                hash_table[index].key = "";
                hash_table[index].value = "";
                
                return;
            }
            
            struct Node* current = &hash_table[index];
            while(current != NULL && current->key != "") {
                if(current->key == key) {
                    current->key = "";
                    current->value = "";
                    
                    return;    
                }
                
                current = current->next;
            }
        }
        
        int index_size(int index) {
            int count = 0;
            struct Node* current = &hash_table[index];
            while(current != NULL && current->key != "") {
                count++;
                current = current->next;
            }
            
            return count;
        }
        
        int table_size() {
            int count = 0;
            
            for(int i = 1; i <= size; i++) {
                struct Node* current = &hash_table[i];
                while(current != NULL && current->key != "") {
                    count++;
                    current = current->next;
                }
            }
            
            return count;
        }
        
        Node* index_last_node(int index) {
            struct Node* current = &hash_table[index];
            
            if(index_size(index) < 1) {
                return NULL;
            }
            
            while(current != NULL && current->key != "") {
                if(current->next == NULL) {
                    return current;
                }
                
                current = current->next;
            }
        }
        
        bool check_key(string key) {
            int index = hash_key(key);
            struct Node* current = &hash_table[index];
            while(current != NULL && current->key != "") {
                if(current->key == key) {
                    return true;    
                }
                
                current = current->next;
            }
            
            return false;
        }
        
        string get_value(string key) {
            int index = hash_key(key);
            
            struct Node* current = &hash_table[index];
            while(current != NULL && current->key != "") {
                if(current->key == key) {
                    return current->value;    
                }
                
                current = current->next;
            }
            
            return "key not set";
        }
        
        void print() {
            for(int i = 0; i < size; i++) {
                struct Node* current = &hash_table[i];
                while(current != NULL && current->key != "") {
                    cout<<current->key<<" -> "<<current->value<<endl;
                    
                    current = current->next;
                }
            }
        }
};

int main() {
    Hash_table hash;
    
    hash.insert_key("dd", "mak");
    hash.insert_key("ag", "any");
    hash.insert_key("mn", "random");
    
    cout<<"(before update)"<<endl;
    hash.print();
    
    hash.delete_key("ag");
    hash.insert_key("ag", "any_1");
    //cout<<hash.get_value("none");
    
    
    cout<<"(after update)"<<endl;
    hash.print();
    
    
    return 0;
}
*/

//STL hash table/unordered_map
/*
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

int main() {
    unordered_map<string, string> u_map;
    
    u_map["first"] = "mak";
    u_map["second"] = "any";
    u_map["third"] = "random";
    
    for(auto itr = u_map.begin(); itr != u_map.end(); itr++) {
        cout<<itr->first<<" : "<<itr->second<<endl;
    }
    
    cout<<endl;
    if(u_map.find("first") != u_map.end()) {
        cout<<"\"first\" found"<<endl;
    }
    
    if(u_map.find("none") == u_map.end()) {
        cout<<"\"none\" not found";
    }
    
    return 0;
}
*/

//STL hash table/uordered_set
/*
#include<iostream>
#include<unordered_set>
using namespace std;

int main() {
    unordered_set<int> u_set;
    
    u_set.insert(1);
    u_set.insert(2);
    u_set.insert(3);
    u_set.insert(1);
    
    for(auto itr = u_set.begin(); itr != u_set.end(); itr++) {
        cout<<*itr<<endl;
    }
    
    cout<<endl;
    if(u_set.find(1) != u_set.end()) {
        cout<<"1 found"<<endl;
    }
    
    if(u_set.find(5) == u_set.end()) {
        cout<<"5 not found";
    }
    
    return 0;
}
*/

//AVL binary search tree
/*
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    struct Node* left = NULL;
    struct Node* right = NULL;
    struct Node* parent = NULL;
};

class BST{
    private:
        struct Node* main_root = NULL;
        
        struct Node* insert_node_abstract(struct Node* root, int data) {
            if(main_root == NULL) {
                struct Node* new_node = new Node;
                new_node->data = data;
                main_root = new_node;
                
                return main_root;
            }
            
            if(data < root->data) {
                if(root->left == NULL) {
                    struct Node* new_node = new Node;
                    new_node->data = data;
                    new_node->parent = root;
                    root->left = new_node;   
                    
                    return root;
                }
                
                root->left = insert_node_abstract(root->left, data);
                root = balance_abstract(root);
            }
            else if(data > root->data) {
                if(root->right == NULL) {
                    struct Node* new_node = new Node;
                    new_node->data = data;
                    new_node->parent = root;
                    root->right = new_node;
                    
                    return root;
                }
                
                root->right = insert_node_abstract(root->right, data);
                root = balance_abstract(root);
            }
            
            return root;
        }
        
        struct Node* delete_node_abstract(struct Node* root, int data) {
            if(root == NULL) {
                return root;
            }
            
        	if(data < root->data) {
        	    root->left = delete_node_abstract(root->left,data);
        	    root = balance_abstract(root);
        	}
        	else if (data > root->data) {
        	    root->right = delete_node_abstract(root->right,data);
        	    root = balance_abstract(root);
        	}
        	else {
        		// Case 1:  No child
        		if(root->left == NULL && root->right == NULL) { 
        		    if(data == main_root->data) {
        		        delete main_root;
                        main_root = NULL;
                        
                        return main_root;
        		    }
        		    
        			delete root;
        			root = NULL;
        		}
        		//Case 2: One child 
        		else if(root->left == NULL) {
        		    struct Node *temp = root;
        			root = root->right;
        			
        		    if(data == main_root->data) {
        		        delete main_root;
                        main_root = root;
                        return main_root;
        		    }
        		    
        			delete temp;
        		}
        		else if(root->right == NULL) {
        			struct Node *temp = root;
        			root = root->left;
        			
        			if(data == main_root->data) {
        		        delete main_root;
                        main_root = root;
                        return main_root;
        		    }
        			
        			delete temp;
        		}
        		// case 3: 2 children
        		else { 
        			int temp = min_abstract(root->right);
        			root->right = delete_node_abstract(root->right,temp);
        			root = balance_abstract(root);
        			root->data = temp;
        		}
        	}
        	
        	return root;
        }
        
        struct Node* balance_abstract(struct Node* root) {
            int left_height = height_abstract(root->left);
            int right_height = height_abstract(root->right);
            int difference = left_height - right_height;
            
            if(difference >= -1 && difference <= 1) {
                return root;
            }
        
            if(root->right == NULL) {
                //LR
                if(root->left->right != NULL) {
                    root->left->right->left = root->left;
                    root->left = root->left->right;
                    root->left->left->right = NULL;
                    
                    root->left->parent = root;
                    root->left->left->parent = root->left;
                }
                
                //LL
                root->left->right = root;
                struct Node* new_root = root->left;
                root->left = NULL;
                root = new_root;
                
                root->parent = root->right->parent;
                root->left->parent = root;
                root->right->parent = root;
                
                if(root->right == main_root) {
                    main_root = root;
                }
            }
            else{
                //RL
                if(root->right->left != NULL) {
                    root->right->left->right = root->right;
                    root->right = root->right->left;
                    root->right->right->left = NULL;
                    
                    root->right->parent = root;
                    root->right->right->parent = root->right;
                }
                
                //RR
                root->right->left = root;
                struct Node* new_root = root->right;
                root->right = NULL;
                root = new_root;
                
                root->parent = root->left->parent;
                root->right->parent = root;
                root->left->parent = root;
                
                if(root->left == main_root) {
                    main_root = root;
                }
            }
            
            return root;
        }
        
        bool search_abstract(Node* root, int data) {
            if(main_root == NULL) {
                return false;
            }
            
            if(root == NULL) {
                return false;
            }
            
            if(data == root->data) {
                return true;
            }
            
            if(data < root->data) {
                return search_abstract(root->left, data);
            }
            
            return search_abstract(root->right, data);
        }
        
        int min_abstract(struct Node* root) {
            if(root == NULL) {
                return -1;
            }
            
            struct Node* current = root;
            while(current->left != NULL) {
                current = current->left;
            }
            
            return current->data;
        }
        
        int max_abstract(struct Node* root) {
            if(root == NULL) {
                return -1;
            }
            
            struct Node* current = root;
            while(current->right != NULL) {
                current = current->right;
            }
            
            return current->data;
        }
        
        int height_abstract(struct Node* root) {
            if(root == NULL) {
                return -1;
            }
            
            int left_height = height_abstract(root->left);
            int right_height = height_abstract(root->right);
            
            if(left_height < right_height) {
                return right_height+1;
            }
            else if(left_height > right_height) {
                return left_height+1;
            }
            else {
                return left_height+1;
            }
        }
        
        void level_order_print_abstract(struct Node* root) {
            if(root == NULL) {
                return;
            }
            
            queue<struct Node*> Q;
            Q.push(root);
            
            while(!Q.empty()) {
                struct Node* current = Q.front();
                
                if(current == main_root) {
                    cout<<current->data<<": root";
                }
                else {
                    cout<<current->data<<": "<<current->parent->data;
                }
                
                if(current->left != NULL) {
                    Q.push(current->left);
                }
                
                if(current->right != NULL){
                    Q.push(current->right);
                }
                
                cout<<endl;
                Q.pop();
            }
        }
        
    public:
        struct Node* insert_node(int data) {
            return insert_node_abstract(main_root, data);
        }
        
        struct Node* delete_node(int data) {
            return delete_node_abstract(main_root, data);
        }
        
        bool search(int data) {
            return search_abstract(main_root, data);
        }
        
        int min() {
            return min_abstract(main_root);
        }
        
        int max() {
            return max_abstract(main_root);
        }
                
        int height() {
            return height_abstract(main_root);
        }
        
        void level_order_print() {
            return level_order_print_abstract(main_root);
        }
};

int main()
{
   BST bst;
   
   bst.insert_node(8);
   bst.insert_node(6);
   bst.insert_node(9);
   bst.insert_node(4);
   
   cout<<"(before update): "<<endl;
   bst.level_order_print();
   cout<<endl;
   
   cout<<"max: "<<bst.max()<<endl;
   cout<<"min: "<<bst.min()<<endl;
   cout<<"height: "<<bst.height()<<endl;
   cout<<"search(false): "<<bst.search(9)<<endl;
   cout<<"search(true): "<<bst.search(3)<<endl;
   cout<<endl<<endl;
   
   bst.delete_node(9);
   
   cout<<"(after update): "<<endl;
   bst.level_order_print();
   cout<<endl;
   
   cout<<"max: "<<bst.max()<<endl;
   cout<<"min: "<<bst.min()<<endl;
   cout<<"height: "<<bst.height()<<endl;
   cout<<"search(false): "<<bst.search(9)<<endl;
   cout<<"search(true): "<<bst.search(2)<<endl;
   
   return 0;
}
*/

//binary heap(max) implemented using an array
/*
#include<iostream>
#include<vector>
using namespace std;

class Max_heap {
    private:
        vector<int> heap;

        void heapify_insert(int parent, int child) {
            if(child <= 0) {
                return;
            }
            
            if(heap[parent] >= heap[child]) {
                return;
            }
            
            int temp = heap[parent];
            heap[parent] = heap[child];
            heap[child] = temp;
            
            child = parent;
            parent = (int)(child-1)/2;
            heapify_insert(parent, child);
        }

        void heapify_delete(int parent, int first_child, int second_child) {
            if(heap.size() == 0) {
                return;    
            }
            
            if(parent >= heap.size()-1 || first_child >= heap.size() || second_child >= heap.size()) {
                return;
            }
            
            if(heap.size() == 3) {
                if(heap[parent] < heap[first_child]) {
                    int temp = heap[parent];
                    heap[parent] = heap[first_child];
                    heap[first_child] = temp;
                    
                    parent = first_child;
                }
            }
            
            if(heap[parent] >= heap[first_child] && heap[parent] >= heap[second_child]) {
                return;
            }
            else if(heap[first_child] > heap[second_child]) {
                int temp = heap[parent];
                heap[parent] = heap[first_child];
                heap[first_child] = temp;
                
                parent = first_child;
            }
            else{
                int temp = heap[parent];
                heap[parent] = heap[second_child];
                heap[second_child] = temp;
            
                parent = second_child;
            }
            
            first_child = 2*parent+1;
            second_child = 2*parent+2;
            
            heapify_delete(parent, first_child, second_child);
        }
        
    public:
        int max() {
            return heap[0];    
        }
        
        void insert(int data) {
            heap.push_back(data);
            
            int child = heap.size()-1;
            int parent = (int)(child-1)/2;
            
            heapify_insert(parent, child);
        }
        
        void delete_data(int data) {
            int parent;
            int first_child;
            int second_child;
            
            for(int i = 0; i < heap.size(); i++) {
                if(heap[i] == data) {
                    heap[i] = heap[heap.size()-1];
                    heap.pop_back();
                    parent = i;
                    first_child = 2*i+1;
                    second_child = 2*i+2;
                    break;
                }
            }
            
            heapify_delete(parent, first_child, second_child);
        }
        
        void print() {
            for(int i = 0; i < heap.size(); i++) {
                cout<<heap[i]<<endl;
            }
        }
};

int main() {
    Max_heap heap;
    
    heap.insert(2);
    heap.insert(5);
    heap.insert(7);
    heap.insert(6);
    heap.insert(8);
    heap.insert(8);
    
    cout<<"before: "<<endl;
    heap.print();
    cout<<endl;
    cout<<"min: "<<heap.max()<<endl;
    
    //heap.insert(3);
    heap.delete_data(8);
    
    cout<<endl;
    cout<<"after: "<<endl;
    cout<<endl;
    heap.print();
    
    return 0;
}
*/

//trie
/*
#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

const int children_size = 26;

struct Node {
    struct Node* children[children_size];  
    bool is_word;
    
    Node() {
        for(int i = 0; i < sizeof(children)/sizeof(children[0]); i++) {
            children[i] = NULL;
        }
    }
};

class Trie {
    private:
        void print_abstract(struct Node* root, string formed_string) {
            for(int i = 0; i < sizeof(root->children)/sizeof(root->children[0]); i++) {
                if(root->children[i] != NULL) {
                    formed_string.push_back((char)(i+(int)'a'));
                    print_abstract(root->children[i], formed_string);
                    formed_string.pop_back();
                }
            }
            
            if(root->is_word) {
                cout<<formed_string<<endl;
            }
            
            return;
        }
        
    public:  
        struct Node* main_root = new Node;
        
        void insert(string data) {
            transform(data.begin(), data.end(), data.begin(), ::tolower);
            
            struct Node* current = main_root;
            
            for(int i = 0; i < data.length(); i++) {
                int children_index = data[i] - 'a';
                
                if(current->children[children_index] == NULL) {
                    current->children[children_index] = new Node;
                }
                
                current = current->children[children_index];
            }
            
            current->is_word = true;
        }
        
        void delete_string(string data) {
            transform(data.begin(), data.end(), data.begin(), ::tolower);
            
            struct Node* current = main_root;
            for(int i = 0; i < data.length(); i++) {
                int children_index = data[i] - 'a';
                
                if(current->children[children_index] == NULL) {
                    return;
                }
                
                if(i == data.length()-1) {
                    if(current->children[children_index]) {
                        current->children[children_index]->is_word = false;
                    }
                }
                
                current = current->children[children_index];
            }
        }
        
        bool check(string data) {
            transform(data.begin(), data.end(), data.begin(), ::tolower);
            
            struct Node* current = main_root;
            for(int i = 0; i < data.length(); i++) {
                int children_index = data[i] - 'a';
                
                if(current->children[children_index] == NULL) {
                    return false;
                }
                
                current = current->children[children_index];
            }
            
            return current->is_word;
        }
        
        void print() {
            print_abstract(main_root, "");
        }
};

int main() {
    Trie trie;
    
    trie.insert("mayank");
    trie.insert("mak");
    trie.insert("any");
    
    //cout<<trie.check("mayank");
    
    cout<<"before: "<<endl;
    trie.print();
    
    trie.delete_string("mak");
    
    cout<<endl;
    cout<<"after: "<<endl;
    trie.print();
    
    return 0;
}
*/

//general undirected tree(represented as graph)
/*
#include<iostream>
#include<map>
#include<queue>
using namespace std;

//structure for verteces stored in adjacency list
struct Adj_node{
    int data;
    int weight;
    struct Adj_node* next = NULL;
};

//structure for edges
struct Edge{
    int weight;
    int start_vertex;
    int end_vertex;
};

class Graph{
    private: 
        map<int, struct Adj_node*> adj_list;
        map<int, bool> visited_arr_dfs;
        
    public:
        Graph() {
            //initialize visited_arr with false
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                visited_arr_dfs[itr->first] = false;
            }
        }
    
        struct Node* insert_vertex(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                adj_list[data] = NULL;
            }
        }
        
        void delete_vertex(int data) {
            struct Adj_node* current = adj_list[data];
            
            while(current != NULL) {
                struct Adj_node* nested_current = adj_list[current->data];
                struct Adj_node* prev = NULL;
                
                if(nested_current != NULL) { 
                    if(nested_current->data == data) {
                        adj_list[current->data] = nested_current->next;
                        delete nested_current;
                        
                        return;    
                    }
                } 
                
                while(nested_current != NULL && nested_current->data != data) {
                    prev = nested_current;
                    nested_current = nested_current->next;
                }
                
                if(nested_current == NULL) {
                    return;
                }
                
                prev->next = nested_current->next; 
                
                current = current->next;
            }
            
            adj_list.erase(data);
        }
        
        void insert_edge(struct Edge edge) {
            if(adj_list.find(edge.end_vertex) == adj_list.end()) {
                return;
            }
            
            struct Adj_node* new_node = new Adj_node;
            new_node->data = edge.end_vertex;
            new_node->weight = edge.weight;
            
            if(adj_list[edge.start_vertex] == NULL) {
                adj_list[edge.start_vertex] = new_node;
            } 
            else {
                // check for repeated edge 
                struct Adj_node* current = adj_list[edge.start_vertex];
                while(current != NULL) {
                    if(new_node->data == current->data) {
                        return;
                    }
                    
                    current = current->next;
                }
                
                struct Adj_node* head = adj_list[edge.start_vertex];
                new_node->next = head->next;
                head->next = new_node;   
            }
            
            struct Adj_node* new_node_1 = new Adj_node;
            new_node_1->weight = edge.weight;
            new_node_1->data = edge.start_vertex;
            
            if(adj_list[edge.end_vertex] == NULL) {
                adj_list[edge.end_vertex] = new_node_1;
            } 
            else {
                struct Adj_node* head = adj_list[edge.end_vertex];
                new_node_1->next = head->next;
                head->next = new_node_1;   
            }
        }
        
        void delete_edge(struct Edge edge) {
            if(adj_list.find(edge.start_vertex) == adj_list.end()) {
                return;
            }
            else if(adj_list.find(edge.end_vertex) == adj_list.end()) {
                return;
            }
            
            int arr_vertices[2] = {edge.start_vertex, edge.end_vertex};
            
            for(int i = 0; i < sizeof(arr_vertices)/sizeof(arr_vertices[0]); i++) {
                if(i == 0) {
                    struct Adj_node* current = adj_list[arr_vertices[0]];
                    struct Adj_node* prev = NULL;
                    
                    if(current != NULL) { 
                        if(current->data == arr_vertices[1]) {
                            adj_list[arr_vertices[0]] = current->next;
                            delete current;
                            
                            continue;    
                        }
                    } 
                    
                    while(current != NULL && current->data != arr_vertices[1]) {
                        prev = current;
                        current = current->next;
                    }
                    
                    if(current == NULL) {
                        continue;
                    }
                    
                    prev->next = current->next;
                }
                else {
                    struct Adj_node* current_1 = adj_list[arr_vertices[1]];
                    struct Adj_node* prev_1 = NULL;
                    
                    if(current_1 != NULL) { 
                        if(current_1->data == arr_vertices[0]) {
                            adj_list[arr_vertices[1]] = current_1->next;
                            delete current_1;
                            
                            continue;    
                        }
                    } 
                    
                    while(current_1 != NULL && current_1->data != arr_vertices[0]) {
                        prev_1 = current_1;
                        current_1 = current_1->next;
                    }
                    
                    if(current_1 == NULL) {
                        continue;
                    }
                    
                    prev_1->next = current_1->next;                    
                }
            }
        }
        
        void bfs(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                return;
            }
            
            map<int, bool> visited_arr;
            queue<int> q;
            
            //initialize visited_arr with false
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                visited_arr[itr->first] = false;
            }
            
            q.push(data);
            visited_arr[data] = true;
            
            //print the queue
            while (!q.empty()) 
            { 
                cout<<q.front()<<" "; 
                struct Adj_node* current = adj_list[q.front()];
                q.pop(); 
                
                while(current != NULL) {
                    if(!visited_arr[current->data]) {
                        q.push(current->data);
                        visited_arr[current->data] = true;
                    }
                    
                    current = current->next;
                }
            }
        }
        
        int dfs(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                return -1;
            }
            
            visited_arr_dfs[data] = true;
            
            struct Adj_node* current = adj_list[data];
            while(current != NULL) {
                if(!visited_arr_dfs[current->data]) {
                    int temp = dfs(current->data);
                    visited_arr_dfs[current->data] = true;
                }
                
                current = current->next;
            }
            
            cout<<data<<" ";
            visited_arr_dfs[data] = false;
            return data;
        }
        
        void print_verteces() {
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                cout<<itr->first<<endl;
            }
        }
        
        void print_edges() {
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                cout<<itr->first<<": ";
                
                struct Adj_node* current = itr->second;
                while(current != NULL) {
                    cout<<current->data<<" ";
                    current = current->next;
                }
                cout<<endl;
            }
        }
};

int main() {
    Graph graph;
    graph.insert_vertex(1);
    graph.insert_vertex(2);
    graph.insert_vertex(3);
    graph.insert_vertex(4);
    graph.insert_vertex(5);
    graph.insert_vertex(6);
    
    struct Edge edge_1;
    edge_1.weight = 1;
    edge_1.start_vertex = 1;
    edge_1.end_vertex = 2;
    
    struct Edge edge_2;
    edge_2.weight = 1;
    edge_2.start_vertex = 1;
    edge_2.end_vertex = 3;
    
    struct Edge edge_3;
    edge_3.weight = 2;
    edge_3.start_vertex = 2;
    edge_3.end_vertex = 4;
    
    struct Edge edge_4;
    edge_4.weight = 3;
    edge_4.start_vertex = 3;
    edge_4.end_vertex = 5;
    
    struct Edge edge_5;
    edge_5.weight = 4;
    edge_5.start_vertex = 4;
    edge_5.end_vertex = 3;
    
    struct Edge edge_6;
    edge_6.weight = 4;
    edge_6.start_vertex = 4;
    edge_6.end_vertex = 6;
    
    struct Edge edge_7;
    edge_7.weight = 5;
    edge_7.start_vertex = 5;
    edge_7.end_vertex = 6;
    
    graph.insert_edge(edge_1);
    graph.insert_edge(edge_2);
    graph.insert_edge(edge_3);
    graph.insert_edge(edge_4);
    graph.insert_edge(edge_5);
    graph.insert_edge(edge_6);
    graph.insert_edge(edge_7);
    
    //graph.delete_vertex(6);
    graph.delete_edge(edge_7);
    
    cout<<"vertices: "<<endl;
    graph.print_verteces();
    cout<<endl<<endl;
    cout<<"edges: "<<endl;
    graph.print_edges();
    cout<<endl<<endl;
    cout<<"BFS: "<<endl;
    graph.bfs(1);
    cout<<endl<<endl;
    cout<<"DFS: "<<endl;
    graph.dfs(1);
    
    return 0;
}
*/

//STL BST red-black tree/map
/*
#include<iostream>
#include<string>
#include<map>
using namespace std;

int main() {
    map<int, string> map_1;
    
    map_1[1] = "mak";
    map_1[2] = "any";
    map_1[3] = "random";
    
    for(auto itr = map_1.begin(); itr != map_1.end(); itr++) {
        cout<<itr->first<<" : "<<itr->second<<endl;
    }
    
    cout<<endl;
    if(map_1.find(1) != map_1.end()) {
        cout<<"1 found"<<endl;
    }
    
    if(map_1.find(5) == map_1.end()) {
        cout<<"5 not found";
    }
    
    return 0;
}
*/

//STL BST red-black tree/set
/*
#include<iostream>
#include<set>
using namespace std;

int main() {
    set<int> set_1;
    
    set_1.insert(1);
    set_1.insert(3);
    set_1.insert(2);
    set_1.insert(1);
    
    for(auto itr = set_1.begin(); itr != set_1.end(); itr++) {
        cout<<*itr<<endl;
    }
    
    cout<<endl;
    if(set_1.find(1) != set_1.end()) {
        cout<<"1 found"<<endl;
    }
    
    if(set_1.find(5) == set_1.end()) {
        cout<<"5 not found";
    }
    
    return 0;
}
*/

//directed weighted graph
/*
#include<iostream>
#include<map>
#include<queue>
using namespace std;

//structure for verteces stored in adjacency list
struct Adj_node{
    int data;
    int weight;
    struct Adj_node* next = NULL;
};

//structure for edges
struct Edge{
    int weight;
    int start_vertex;
    int end_vertex;
};

class Graph{
    private: 
        map<int, struct Adj_node*> adj_list;
        map<int, bool> visited_arr_dfs;
        
    public:
        Graph() {
            //initialize visited_arr with false
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                visited_arr_dfs[itr->first] = false;
            }
        }
    
        struct Node* insert_vertex(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                adj_list[data] = NULL;
            }
        }
        
        void insert_edge(struct Edge edge) {
            if(adj_list.find(edge.end_vertex) == adj_list.end()) {
                return;
            }
            
            struct Adj_node* new_node = new Adj_node;
            new_node->data = edge.end_vertex;
            new_node->weight = edge.weight;
            
            if(adj_list[edge.start_vertex] == NULL) {
                adj_list[edge.start_vertex] = new_node;
            } 
            else {
                //check for repeated edge 
                struct Adj_node* current = adj_list[edge.start_vertex];
                while(current != NULL) {
                    if(new_node->data == current->data) {
                        return;
                    }
                    
                    current = current->next;
                }
                
                struct Adj_node* head = adj_list[edge.start_vertex];
                new_node->next = head->next;
                head->next = new_node;   
            }
        }
        
        void delete_vertex(int data) {
            struct Adj_node* current = adj_list[data];
            
            while(current != NULL) {
                struct Adj_node* nested_current = adj_list[current->data];
                struct Adj_node* prev = NULL;
                
                if(nested_current != NULL) { 
                    if(nested_current->data == data) {
                        adj_list[current->data] = nested_current->next;
                        delete nested_current;
                        
                        return;    
                    }
                } 
                
                while(nested_current != NULL && nested_current->data != data) {
                    prev = nested_current;
                    nested_current = nested_current->next;
                }
                
                if(nested_current == NULL) {
                    return;
                }
                
                prev->next = nested_current->next; 
                
                current = current->next;
            }
            
            adj_list.erase(data);
        }
        
        void delete_edge(struct Edge edge) {
            if(adj_list.find(edge.start_vertex) == adj_list.end()) {
                return;
            }
            else if(adj_list.find(edge.end_vertex) == adj_list.end()) {
                return;
            }
            
            int arr_vertices[2] = {edge.start_vertex, edge.end_vertex};
            
            for(int i = 0; i < sizeof(arr_vertices)/sizeof(arr_vertices[0]); i++) {
                if(i == 0) {
                    struct Adj_node* current = adj_list[arr_vertices[0]];
                    struct Adj_node* prev = NULL;
                    
                    if(current != NULL) { 
                        if(current->data == arr_vertices[1]) {
                            adj_list[arr_vertices[0]] = current->next;
                            delete current;
                            
                            continue;    
                        }
                    } 
                    
                    while(current != NULL && current->data != arr_vertices[1]) {
                        prev = current;
                        current = current->next;
                    }
                    
                    if(current == NULL) {
                        continue;
                    }
                    
                    prev->next = current->next;
                }
                else {
                    struct Adj_node* current_1 = adj_list[arr_vertices[1]];
                    struct Adj_node* prev_1 = NULL;
                    
                    if(current_1 != NULL) { 
                        if(current_1->data == arr_vertices[0]) {
                            adj_list[arr_vertices[1]] = current_1->next;
                            delete current_1;
                            
                            continue;    
                        }
                    } 
                    
                    while(current_1 != NULL && current_1->data != arr_vertices[0]) {
                        prev_1 = current_1;
                        current_1 = current_1->next;
                    }
                    
                    if(current_1 == NULL) {
                        continue;
                    }
                    
                    prev_1->next = current_1->next;                    
                }
            }
        }
        
        void bfs(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                return;
            }
            
            map<int, bool> visited_arr;
            queue<int> q;
            
            //initialize visited_arr with false
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                visited_arr[itr->first] = false;
            }
            
            q.push(data);
            visited_arr[data] = true;
            
            //print the queue
            while (!q.empty()) 
            { 
                cout<<q.front()<<" "; 
                struct Adj_node* current = adj_list[q.front()];
                q.pop(); 
                
                while(current != NULL) {
                    if(!visited_arr[current->data]) {
                        q.push(current->data);
                        visited_arr[current->data] = true;
                    }
                    
                    current = current->next;
                }
            }
        }
        
        int dfs(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                return -1;
            }
            
            visited_arr_dfs[data] = true;
            
            struct Adj_node* current = adj_list[data];
            while(current != NULL) {
                if(!visited_arr_dfs[current->data]) {
                    int temp = dfs(current->data);
                    visited_arr_dfs[current->data] = true;
                }
                
                current = current->next;
            }
            
            cout<<data<<" ";
            visited_arr_dfs[data] = false;
            return data;
        }
        
        void print_verteces() {
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                cout<<itr->first<<endl;
            }
        }
        
        void print_edges() {
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                cout<<itr->first<<": ";
                
                struct Adj_node* current = itr->second;
                while(current != NULL) {
                    cout<<current->data<<" ";
                    current = current->next;
                }
                cout<<endl;
            }
        }
};

int main() {
    Graph graph;
    graph.insert_vertex(1);
    graph.insert_vertex(2);
    graph.insert_vertex(3);
    graph.insert_vertex(4);
    graph.insert_vertex(5);
    graph.insert_vertex(6);
    
    struct Edge edge_1;
    edge_1.weight = 1;
    edge_1.start_vertex = 1;
    edge_1.end_vertex = 2;
    
    struct Edge edge_2;
    edge_2.weight = 1;
    edge_2.start_vertex = 1;
    edge_2.end_vertex = 3;
    
    struct Edge edge_3;
    edge_3.weight = 2;
    edge_3.start_vertex = 2;
    edge_3.end_vertex = 4;
    
    struct Edge edge_4;
    edge_4.weight = 3;
    edge_4.start_vertex = 3;
    edge_4.end_vertex = 5;
    
    struct Edge edge_5;
    edge_5.weight = 4;
    edge_5.start_vertex = 4;
    edge_5.end_vertex = 3;
    
    struct Edge edge_6;
    edge_6.weight = 4;
    edge_6.start_vertex = 4;
    edge_6.end_vertex = 6;
    
    struct Edge edge_7;
    edge_7.weight = 5;
    edge_7.start_vertex = 5;
    edge_7.end_vertex = 6;
    
    graph.insert_edge(edge_1);
    graph.insert_edge(edge_2);
    graph.insert_edge(edge_3);
    graph.insert_edge(edge_4);
    graph.insert_edge(edge_5);
    graph.insert_edge(edge_6);
    graph.insert_edge(edge_7);
    
    //graph.delete_vertex(6);
    //graph.delete_edge(edge_7);
    
    cout<<"vertices: "<<endl;
    graph.print_verteces();
    cout<<endl<<endl;
    cout<<"edges: "<<endl;
    graph.print_edges();
    cout<<endl<<endl;
    cout<<"BFS: "<<endl;
    graph.bfs(1);
    cout<<endl<<endl;
    cout<<"DFS: "<<endl;
    graph.dfs(1);
    
    return 0;
}
*/

//undirected weighted graph
/*
#include<iostream>
#include<map>
#include<queue>
using namespace std;

//structure for verteces stored in adjacency list
struct Adj_node{
    int data;
    int weight;
    struct Adj_node* next = NULL;
};

//structure for edges
struct Edge{
    int weight;
    int start_vertex;
    int end_vertex;
};

class Graph{
    private: 
        map<int, struct Adj_node*> adj_list;
        map<int, bool> visited_arr_dfs;
        
    public:
        Graph() {
            //initialize visited_arr with false
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                visited_arr_dfs[itr->first] = false;
            }
        }
    
        struct Node* insert_vertex(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                adj_list[data] = NULL;
            }
        }
        
        void delete_vertex(int data) {
            struct Adj_node* current = adj_list[data];
            
            while(current != NULL) {
                struct Adj_node* nested_current = adj_list[current->data];
                struct Adj_node* prev = NULL;
                
                if(nested_current != NULL) { 
                    if(nested_current->data == data) {
                        adj_list[current->data] = nested_current->next;
                        delete nested_current;
                        
                        return;    
                    }
                } 
                
                while(nested_current != NULL && nested_current->data != data) {
                    prev = nested_current;
                    nested_current = nested_current->next;
                }
                
                if(nested_current == NULL) {
                    return;
                }
                
                prev->next = nested_current->next; 
                
                current = current->next;
            }
            
            adj_list.erase(data);
        }
        
        void insert_edge(struct Edge edge) {
            if(adj_list.find(edge.end_vertex) == adj_list.end()) {
                return;
            }
            
            struct Adj_node* new_node = new Adj_node;
            new_node->data = edge.end_vertex;
            new_node->weight = edge.weight;
            
            if(adj_list[edge.start_vertex] == NULL) {
                adj_list[edge.start_vertex] = new_node;
            } 
            else {
                // check for repeated edge 
                struct Adj_node* current = adj_list[edge.start_vertex];
                while(current != NULL) {
                    if(new_node->data == current->data) {
                        return;
                    }
                    
                    current = current->next;
                }
                
                struct Adj_node* head = adj_list[edge.start_vertex];
                new_node->next = head->next;
                head->next = new_node;   
            }
            
            struct Adj_node* new_node_1 = new Adj_node;
            new_node_1->weight = edge.weight;
            new_node_1->data = edge.start_vertex;
            
            if(adj_list[edge.end_vertex] == NULL) {
                adj_list[edge.end_vertex] = new_node_1;
            } 
            else {
                struct Adj_node* head = adj_list[edge.end_vertex];
                new_node_1->next = head->next;
                head->next = new_node_1;   
            }
        }
        
        void delete_edge(struct Edge edge) {
            if(adj_list.find(edge.start_vertex) == adj_list.end()) {
                return;
            }
            else if(adj_list.find(edge.end_vertex) == adj_list.end()) {
                return;
            }
            
            int arr_vertices[2] = {edge.start_vertex, edge.end_vertex};
            
            for(int i = 0; i < sizeof(arr_vertices)/sizeof(arr_vertices[0]); i++) {
                if(i == 0) {
                    struct Adj_node* current = adj_list[arr_vertices[0]];
                    struct Adj_node* prev = NULL;
                    
                    if(current != NULL) { 
                        if(current->data == arr_vertices[1]) {
                            adj_list[arr_vertices[0]] = current->next;
                            delete current;
                            
                            continue;    
                        }
                    } 
                    
                    while(current != NULL && current->data != arr_vertices[1]) {
                        prev = current;
                        current = current->next;
                    }
                    
                    if(current == NULL) {
                        continue;
                    }
                    
                    prev->next = current->next;
                }
                else {
                    struct Adj_node* current_1 = adj_list[arr_vertices[1]];
                    struct Adj_node* prev_1 = NULL;
                    
                    if(current_1 != NULL) { 
                        if(current_1->data == arr_vertices[0]) {
                            adj_list[arr_vertices[1]] = current_1->next;
                            delete current_1;
                            
                            continue;    
                        }
                    } 
                    
                    while(current_1 != NULL && current_1->data != arr_vertices[0]) {
                        prev_1 = current_1;
                        current_1 = current_1->next;
                    }
                    
                    if(current_1 == NULL) {
                        continue;
                    }
                    
                    prev_1->next = current_1->next;                    
                }
            }
        }
        
        void bfs(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                return;
            }
            
            map<int, bool> visited_arr;
            queue<int> q;
            
            //initialize visited_arr with false
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                visited_arr[itr->first] = false;
            }
            
            q.push(data);
            visited_arr[data] = true;
            
            //print the queue
            while (!q.empty()) 
            { 
                cout<<q.front()<<" "; 
                struct Adj_node* current = adj_list[q.front()];
                q.pop(); 
                
                while(current != NULL) {
                    if(!visited_arr[current->data]) {
                        q.push(current->data);
                        visited_arr[current->data] = true;
                    }
                    
                    current = current->next;
                }
            }
        }
        
        int dfs(int data) {
            if(adj_list.find(data) == adj_list.end()) {
                return -1;
            }
            
            visited_arr_dfs[data] = true;
            
            struct Adj_node* current = adj_list[data];
            while(current != NULL) {
                if(!visited_arr_dfs[current->data]) {
                    int temp = dfs(current->data);
                    visited_arr_dfs[current->data] = true;
                }
                
                current = current->next;
            }
            
            cout<<data<<" ";
            visited_arr_dfs[data] = false;
            return data;
        }
        
        void print_verteces() {
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                cout<<itr->first<<endl;
            }
        }
        
        void print_edges() {
            for(auto itr = adj_list.begin(); itr != adj_list.end(); itr++) {
                cout<<itr->first<<": ";
                
                struct Adj_node* current = itr->second;
                while(current != NULL) {
                    cout<<current->data<<" ";
                    current = current->next;
                }
                cout<<endl;
            }
        }
};

int main() {
    Graph graph;
    graph.insert_vertex(1);
    graph.insert_vertex(2);
    graph.insert_vertex(3);
    graph.insert_vertex(4);
    graph.insert_vertex(5);
    graph.insert_vertex(6);
    
    struct Edge edge_1;
    edge_1.weight = 1;
    edge_1.start_vertex = 1;
    edge_1.end_vertex = 2;
    
    struct Edge edge_2;
    edge_2.weight = 1;
    edge_2.start_vertex = 1;
    edge_2.end_vertex = 3;
    
    struct Edge edge_3;
    edge_3.weight = 2;
    edge_3.start_vertex = 2;
    edge_3.end_vertex = 4;
    
    struct Edge edge_4;
    edge_4.weight = 3;
    edge_4.start_vertex = 3;
    edge_4.end_vertex = 5;
    
    struct Edge edge_5;
    edge_5.weight = 4;
    edge_5.start_vertex = 4;
    edge_5.end_vertex = 3;
    
    struct Edge edge_6;
    edge_6.weight = 4;
    edge_6.start_vertex = 4;
    edge_6.end_vertex = 6;
    
    struct Edge edge_7;
    edge_7.weight = 5;
    edge_7.start_vertex = 5;
    edge_7.end_vertex = 6;
    
    graph.insert_edge(edge_1);
    graph.insert_edge(edge_2);
    graph.insert_edge(edge_3);
    graph.insert_edge(edge_4);
    graph.insert_edge(edge_5);
    graph.insert_edge(edge_6);
    graph.insert_edge(edge_7);
    
    //graph.delete_vertex(6);
    graph.delete_edge(edge_7);
    
    cout<<"vertices: "<<endl;
    graph.print_verteces();
    cout<<endl<<endl;
    cout<<"edges: "<<endl;
    graph.print_edges();
    cout<<endl<<endl;
    cout<<"BFS: "<<endl;
    graph.bfs(1);
    cout<<endl<<endl;
    cout<<"DFS: "<<endl;
    graph.dfs(1);
    
    return 0;
}
*/

//algorithms
/*
-Learn to calculate the time and space complecity of the algorithms
-Always leverage standard library if possible 
-Using popular algorithms
    -Only understand the psedo steps
    -Avoid rewriting the code if possible
-When developing algorithms
    -Do not reinvent the wheel, search for related algorithm
    -Focus on programming techniques like "divide and conquer", "greedy technique" to solve a problem
    -Consider in terms of time and space complexity
*/