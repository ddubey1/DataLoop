#include "DataLoop.h"

// default constructor
// creates a DataLoop object containing no nodes
DataLoop::DataLoop() {
    count = 0;
    start = nullptr;
}

// non-default constructor
// takes in a number and creates a DataLoop object containing one node
// with the inputted number being its data
DataLoop::DataLoop(const int & num) {
    count = 1;
    _Node* n = new _Node;
    n->data = num;
    n->next = n;
    n->prev = n;
    start = n;
}

// copy constructor
// takes in the reference of another DataLoop as its input
// and creates a new DataLoop object
DataLoop::DataLoop(const DataLoop & rhs) {
    count = 0;
    start = nullptr;
    *this = rhs;
}

// clear functions
// deallocates the allocated memory in the implicit DataLoop parameter
void DataLoop::clear() {
    _Node* n = this->start;
    for (int i = 0; i < (int) this->count; i++) {
        _Node* temp = n;
        if (i != ((int) this->count - 1)) {
            n = n->next;
        }
        delete temp;
    }
    // set DataLoop to having no nodes and no count
    this->start = nullptr;
    this->count = 0;
}


// assignment operator
// creates a deep copy of the inputted rhs DataLoop and assigns it to and returns
// the implicit DataLoop
DataLoop & DataLoop::operator=(const DataLoop & rhs) {
    if(this != &rhs) { // checking for self-assignment
        clear();
        if(rhs.count == 0) {
            this->count = 0;
            this->start = nullptr;
        }
        else {
            _Node* cur = rhs.start;
            // goes through each node in rhs and addes it to the implicit DataLoop
            for(int i = 0; i < (int) rhs.count; i++) {
                add(cur->data);
                cur = cur->next;
            }
        }

    }
    return *this;
}

// double equals operator
// Checks if each node in the implicit and explicit DataLoops are the same
// if the same, program returns true; if different, false is returned.
bool DataLoop::operator==(const DataLoop & rhs) const {
    // checks if two DataLoops are the same size
    if (rhs.count == this->count) {
        int same_count = rhs.count;

        // counter for how many similar nodes there are between the two DataLoop
        int similar = 0;
        _Node* cur = start;
        _Node* cur_rhs = rhs.start;

        // getting past the first node (start)
        if(cur->data == cur_rhs->data) {
            similar++;
        }
        cur = cur->next;
        cur_rhs = cur_rhs->next;

        // go through each node in the DataLoops
        while(cur != start) {
            if(cur->data == cur_rhs->data) {
                similar++;
            }
            cur = cur->next;
            cur_rhs = cur_rhs->next;

        }
        if(similar == same_count) {
            return true;
        }
    }
    
    return false;
}

// add value to DataLoop function
// Takes in an integer value as the input and inserts it as the
// last node (node before start) in the implicit DataLoop
void DataLoop::add(int value) {

    // allocates new node and sets it to value
    _Node* new_node = new _Node;
    new_node->data = value;
    new_node->prev = nullptr;
    new_node->next = nullptr;

    // if circular doubly linked list is empty
    if (start == nullptr) {
        start = new_node;
        new_node->next = start;
        new_node->prev = start;
        this->count += 1;
    }
    
    // if it is not empty
    else {
        _Node* cur = start;
        // gets cur to the last node
        for (int i = 0; i < (int) this->count - 1; i++) {
            cur = cur->next;
        }
        // add the new node
        cur->next = new_node;
        new_node->next = start;
        start->prev = new_node;
        new_node->prev = cur;

        this->count += 1;
    }
    
}

// add assignment operator
// adds the inputted num to the end of the implicit
// DataLoop parameter
DataLoop & DataLoop::operator+=(const int & num) {
    add(num);
    return *this;
}

// concatenation operator
// Creates and returns a new DataLoop which concatenates the 
// inputted DataLoop rhs with the implicit DataLoop. In this case,
// the implicit DataLoop comes first in the returned DataLoop
DataLoop DataLoop::operator+(const DataLoop & rhs) {

    // Set new DataLoop equal to the contents of the implicit DataLoop
    DataLoop new_dl = *this;

    // _Node pointer to iterate through DataLoop rhs
    _Node* cur_rhs = rhs.start;

    // Adding the nodes of rhs to new_dl
    for(int i = 0; i < (int) rhs.count; i++) {
        (new_dl).add(cur_rhs->data);
        cur_rhs = cur_rhs->next;
    }
    return new_dl;

}

// offset operator
// Offsets the nodes in the implicit DataLoop by a integer offset
// If offset is positive, the nodes are shifted to the right
// If negative, the shift is to the left. The DataLoop is returned
// at the end.
DataLoop & DataLoop::operator^(int offset) {
    // case for no shift
    if(offset == 0 || this->count == 0 || this->count == 1) {
        return *this;
    }
    // shift is positive (forward shift)
    if (offset > 0) {
        _Node* cur = start;
        for(int i = 0; i < offset; i++) {
            cur = cur->next;
        }
        start = cur;
    }
    // shift is negative (backwards shift)
    if (offset < 0) {
        _Node* cur = start;
        for(int i = 0; i < (-1 * offset); i++) {
            cur=cur->prev;
        }
        start = cur;

    }
    
    return *this;
}

// splice operator
// Splices together the rhs DataLoop and the implicit DataLoop at the position
// of the implicit DataLoop indicated by pos (start counting nodes from 0, and
// splice occurs before pos). Returns a DataLoop reference of the modified
// DataLoop
DataLoop & DataLoop::splice(DataLoop & rhs, size_t pos) {

    // Checking edge cases
    if (start == nullptr) {
        *this = rhs;
        rhs.count = 0;
        rhs.start = nullptr;
        return *this;
    }
    if (rhs.start == nullptr) {
        return *this;
    }

    // adjusts pos if it is out range; pos is the index rhs has to be inserted before
    if(pos >= this->count) {
        pos = pos % this->count;
    }

    _Node* insert_before = start;
    // will take insert_before to the node that rhs has to be inserted before (pos)
    for(int i = 0; i < (int) pos; i++) {
        insert_before = insert_before->next;
    }
    _Node* before_insert_before = insert_before->prev;
    insert_before->prev = nullptr;
    before_insert_before->next = nullptr;

    // getting nodes that point to the first and last node of rhs
    _Node* rhs_first = rhs.start;
    _Node* rhs_last = rhs.start;
    for(int i = 0; i < (int) rhs.count - 1; i++) {
        rhs_last = rhs_last->next;
    }

    // joining the first and last nodes of rhs DataLoop to the implicit DataLoop
    before_insert_before->next = rhs_first;
    rhs_first->prev = before_insert_before;

    insert_before->prev = rhs_last;
    rhs_last->next = insert_before;

    // updating count
    this->count += rhs.count;

    // set start
     if(pos == 0) {
        this->start = rhs_first;
    } 

    // clearing rhs
    rhs.count = 0;
    rhs.start = nullptr;
    return *this;

}


// destructor
// Deallocates memory calling the clear function
DataLoop::~DataLoop() {
    clear();
}

// printing operator
// Friend function that prints out the contents of the inputted DataLoop dl
// Does this by adding values to the inputted ostream os, and then returns a 
// reference to this ostream once all the nodes have been printed to it
std::ostream & operator<<(std::ostream & os, const DataLoop & dl) {
    if(dl.count == 0) {
        os << ">no values<";
        return os;
    }
    os << "-> ";
    DataLoop::_Node* newNode = dl.start; // Is this okay??
    os << newNode->data;
    newNode = newNode->next;
    if(dl.count > 1) {
        while(newNode != dl.start) {
            os << " <--> ";
            os << newNode->data;
            newNode = newNode->next;
        }
    }
    os << " <-";
    return os;
}