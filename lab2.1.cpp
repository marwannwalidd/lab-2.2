#include <iostream>
#include <cassert>
#include <unordered_set>
using namespace std;

// ============================================================
// Node class
// ============================================================
class Node {
public:
    int data;
    Node* next;
    Node(int value) { data = value; next = nullptr; }
};

// ============================================================
// LinkedList class
// ============================================================
class LinkedList {
public:
    Node* head;

    LinkedList() { head = nullptr; }

    // Walk the list, save next BEFORE deleting the current node
    ~LinkedList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
    }

    // O(1): new node points at old head, then becomes the head
    void insertAtHead(int value) {
        Node* n = new Node(value);
        n->next = head;
        head = n;
    }

    // O(n): walk to the last node and attach the new node
    void insertAtTail(int value) {
        Node* n = new Node(value);
        if (head == nullptr) {      // empty list: new node is the head
            head = n;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = n;
    }

    // O(n): find the first node with this value and unlink it
    bool deleteValue(int value) {
        if (head == nullptr) return false;      // empty list

        if (head->data == value) {              // deleting the head
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node* curr = head;                      // stop one node BEFORE the target
        while (curr->next != nullptr && curr->next->data != value) {
            curr = curr->next;
        }
        if (curr->next == nullptr) return false; // not found

        Node* temp = curr->next;
        curr->next = temp->next;                // bypass the target
        delete temp;
        return true;
    }

    bool search(int value) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == value) return true;
            curr = curr->next;
        }
        return false;
    }

    int length() {
        int count = 0;
        Node* curr = head;
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    // O(n) time, O(1) space: flip every next pointer using 3 pointers
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;  // 1. remember the rest of the list
            curr->next = prev;            // 2. flip the pointer
            prev = curr;                  // 3. move prev forward
            curr = nextNode;              // 4. move curr forward
        }
        head = prev;                      // prev is the new head
    }

    // Format: 10 -> 20 -> 30 -> null
    void print() {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "null" << endl;
    }

    // EXTENSION: O(n) time using a hash set, keeps first occurrence
    void removeDuplicates() {
        unordered_set<int> seen;
        Node* curr = head;
        Node* prev = nullptr;
        while (curr != nullptr) {
            if (seen.count(curr->data)) {     // duplicate: unlink and delete
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            } else {                          // first time: remember it
                seen.insert(curr->data);
                prev = curr;
                curr = curr->next;
            }
        }
    }
};

// ---- Do NOT modify below this line ----
int main() {
    LinkedList L;

    // TC1: insertAtHead (builds list in reverse order)
    L.insertAtHead(30);
    L.insertAtHead(20);
    L.insertAtHead(10);
    cout << "TC1: "; L.print();

    // TC2: insertAtTail
    L.insertAtTail(40);
    L.insertAtTail(50);
    cout << "TC2: "; L.print();

    // TC3: length
    cout << "TC3: length = " << L.length() << endl;

    // TC4: search
    cout << "TC4: search(30)=" << L.search(30)
         << " search(99)=" << L.search(99) << endl;

    // TC5: delete head
    L.deleteValue(10);
    cout << "TC5: "; L.print();

    // TC6: delete tail
    L.deleteValue(50);
    cout << "TC6: "; L.print();

    // TC7: delete middle
    L.deleteValue(30);
    cout << "TC7: "; L.print();

    // TC8: delete non-existent
    bool r = L.deleteValue(99);
    cout << "TC8: deleteValue(99)=" << r << endl;

    // TC9: reverse
    LinkedList L2;
    L2.insertAtTail(1); L2.insertAtTail(2); L2.insertAtTail(3);
    L2.reverse();
    cout << "TC9: "; L2.print();

    // TC10: empty list edge cases
    LinkedList L3;
    cout << "TC10: length=" << L3.length()
         << " search=" << L3.search(5)
         << " delete=" << L3.deleteValue(5) << endl;

    return 0;
}