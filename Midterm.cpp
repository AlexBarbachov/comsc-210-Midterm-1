#include <iostream>
using namespace std;

// constants
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data; 
        Node* prev; // pointer to prev node for linked list
        Node* next; // pointer to next node for linked list

        // constructor
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // beg of list
    Node* tail; // end of list

public:
    // initilizes head and tail -> creates empty list
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) {

        // check valid pos
        if (position < 0) {
            cout << "Position must be >= 0." << endl; 
            return;
        }

        // dynamic mem with given value
        Node* newNode = new Node(value);

        // if list is empty newNode becomes both head tail (because the list is of length 1)
        if (!head) {
            head = tail = newNode;
            return;
        }

        // traverse through list
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;


        // if we got off the the list (hence !temp) then our position was too big
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // memory leak avoidance
            return;
        }
        
        // link new node into the list
        newNode->next = temp->next; // new node points to what temp used to point to
        newNode->prev = temp; // temp is now behind newNode

        // if it wasnt the tail fix node's prev pointer
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // if not the newNode is at end so it becomes the tail
        temp->next = newNode;
    }


    // deletes the first node that contains a certain value
    void delete_val(int value) {
        if (!head) return; // empty list

        Node* temp = head;
        
        // move forward until we get the value
        while (temp && temp->data != value)
            temp = temp->next;

        // val not found exit
        if (!temp) return; 

        // connects prev node to the next node
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // if we are deleting the head (first element) we need to create a new head.

        if (temp->next)
            temp->next->prev = temp->prev; // connect next to prev
        else
            tail = temp->prev; // if we are deleting the tail we need to update the tail

        delete temp; // free memory
    }

    // deletes by pos in list.
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl; 
            return;
        } // empty list
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        // get to the position
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        
        // if we are deleting the last node pop_back
        if (!temp->next) {
            pop_back();
            return;
        }
        
        // adjust the pointers to unlink temp
        Node* tempPrev = temp->prev; // store deleted pointer
        tempPrev->next = temp->next; // link prev to next so we can skip the temp 
        temp->next->prev = tempPrev; // now link the next node's prev to skip back over temp and point to prev node.
        delete temp; // free memory
    }

    // add element to end of a list
    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode; // update tail 
        }
    }
    
    // add element to front of a list
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode; // update head
        }
    }
    
    // remove first element 
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next; 
            head->prev = nullptr; 
        }
        else
            head = tail = nullptr; // only if there is one node
        delete temp; // free memory
    }

    // removes last element 
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail; // store the old tail

        // if more than one node move tail backward
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr; 
        delete temp; // free memory
    }

    // destructor  -> prevents memory leaks
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_element() {
        
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}