/*
You have a singly-linked list ↴ and want to check if it contains a cycle.

A singly-linked list is built with nodes, where each node has:

node.next—the next node in the list.
node.value—the data held in the node. For example, if our linked list stores people in line at the movies, node.value might be the person's name.
For example:

  class LinkedListNode(object):

    def __init__(self, value):
        self.value = value
        self.next  = None

A cycle occurs when a node’s next points back to a previous node in the list. The linked list is no longer linear with a beginning and end—instead, it cycles through a loop of nodes.

Write a function contains_cycle() that takes the first node in a singly-linked list and returns a boolean indicating whether the list contains a cycle.

It's possible to do this in O(n) time and O(1) space
*/

#include <iostream>
#include <unordered_set>

struct node_t {
    int value;
    node_t* next;
};

node_t* create_list() {
    // create a new linked list with the node [0]
    node_t *head = new node_t();
    head->value = 0;
    head->next = nullptr;

    // add some dummy values [1, 2, 3] to the list
    node_t *current = head;
    for (int i = 1; i <= 3; ++i) {
        current->next = new node_t();
        current = current->next;
        current->value = i;
        current->next = nullptr;
    }

    return head;
}

node_t* create_cycle() {
    node_t *head = new node_t();
    head->value = 1;
    node_t *second = new node_t();
    second->value = 2;
    head->next = second;
    second->next = head;
    return head;
}

void free_list(node_t* head) {
    node_t *next;
    while (head != nullptr) {
        next = head->next;
        delete head;
        head = next;
    }
}

// this solution uses O(n^2) time and O(1) space
/*
bool has_cycle(node_t* head) {
    node_t *current = head;
    while (current->next != nullptr) {
        node_t* tmp = head;
        while (tmp != current) {
            if (tmp == current->next)
                return true;
            tmp = tmp->next;
        }
        current = current->next;
    }
    return false;
}
*/

// this solution uses O(n) time and O(n) space
/*
bool has_cycle(node_t* head) {
    std::unordered_set<node_t*> nodes;

    while (head->next != nullptr) {
        if (nodes.count(head))
            return true;
        nodes.insert(head);
        head = head->next;
    }
    return false;
}
*/

// this solution uses O(n) time and O(1) space
bool has_cycle(node_t* head) {
    node_t *slow = head;
    node_t *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (fast == slow)
            return true;
    }
    return false;
}

int main() {
    node_t *head = create_list();
    std::cout << "has_cycle for [0, 1, 2, 3] says " << std::boolalpha << has_cycle(head) << "\n";
    free_list(head);

    node_t *cycle = create_cycle();
    std::cout << "has_cycle for [1 <-> 2] says " << std::boolalpha << has_cycle(cycle) << std::endl;
    node_t *second = cycle->next;
    delete second;
    delete cycle;
    
    return 0;
}