// File: ListL/ListL.hpp

#ifndef LISTL_HPP_
#define LISTL_HPP_

#include <iostream> // ostream.
#include <memory> // shared_ptr.

using namespace std;

template<class T>
class LNode; // Forward declaration.
template<class T>
class ListLIterator; // Forward declaration.

/**
 * ListL is a subclass of "enable_shared_from_this" because "shared_from_this()",
 * a shared_ptr referring to "this" ListL, is needed by ListLIterator.
 * The ListL object must be created as a shared_ptr so the list iterator can use it.
 * See: https://riptutorial.com/cplusplus/example/9319/getting-a-shared-ptr-referring-to-this
 *
 * @tparam T type of data stored in this ListL.
 */
template<class T>
class ListL : public enable_shared_from_this<ListL<T>> {
    friend class ListLIterator<T>;

private:
    shared_ptr<LNode<T>> _head;

public:
    ListL() = default;  // Constructor
    // Post: This list is initialized to be empty.

    ListL(ListL<T> const &rhs) = delete; // Copy constructor disabled.

    void append(T const &data);
    // Post: data is appended to this list.

    void clear();
    // Post: This list is cleared to the empty list.

    void concat(ListL<T> &suffix);
    // Post: suffix is appended to this list.
    // suffix is empty (cut concatenate, as opposed to copy concatenate).

    bool contains(T const &data) const;
    // Post: true is returned if data is contained in this list;
    // Otherwise, false is returned.

private:
    shared_ptr<LNode<T>> copyHead(ListL<T> const &rhs);
    // Post: A deep copy of the head of rhs is returned.

public:
    bool equals(ListL<T> const &rhs) const;
    // Post: true is returned if this list equals list rhs;
    // Otherwise, false is returned.
    // Two lists are equal if they contain the same number
    // of equal elements in the same order.

    T const &first() const;
    // Pre: This list is not empty.
    // Post: A reference tp the first element of this list is returned.

    bool isEmpty() const { return _head == nullptr; }
    // Post: true is returned if this list is empty;
    // Otherwise, false is returned.

    int length() const;

    int length2() const;
    // Post: The length of this list is returned.

    T const &max() const;

    T const &max3() const;
    // Pre: This list is not empty.
    // Post: The maximum element of this list is returned.

    ListL<T> &operator=(ListL<T> const &rhs);
    // Post: This list is a deep copy of rhs.

    void prepend(T const &data);
    // Post: data is prepended to this list.

    T remFirst();
    // Pre: This list is not empty.
    // Post: The first element is removed from this list and returned.

    T remLast();
    // Pre: This list is not empty.
    // Post: The last element is removed from this list and returned.

    void remove(T const &data);
    // Post: If data is in this list, it is removed;
    // Otherwise this list is unchanged.

    void reverse();
    // Post: This list is reversed.

    void setFirst(T const &data);
    // Pre: This list is not empty.
    // Post: The first element of this list is changed to data.

    void toStream(ostream &os) const;
    void toStream4(ostream &os) const;
    // Post: A string representation of this list is returned.

    shared_ptr<ListL<T>> unZip();
    // Post: This list is every other element of this list
    // starting with the first.
    // A pointer to a list with every other element of this list
    // starting with the second is returned.

    void zip(ListL<T> &other);
    // Post: This list is the same perfect shuffle of this list and other,
    // starting with the first element of this.
    // other is the empty list (cut zip, as opposed to copy zip).
};

template<class T>
class LNode {
    friend class ListL<T>;
    friend class ListLIterator<T>;

private:
    T _data;
    shared_ptr<LNode<T>> _next;

    LNode(T const &data);
};

template<class T>
class ListLIterator {
private:
    shared_ptr<const ListL<T>> _listL;
    shared_ptr<LNode<T>> _current;

public:
    void setIterListL(shared_ptr<const ListL<T>> listL) { _listL = listL; }

    // Post: Positions the iterator to the first element.
    void first() { _current = _listL->_head; }

    // Post: Advances the current element.
    void next() { _current = _current->_next; }

    // Post: Checks whether there is a next element.
    bool hasNext() const { return bool(_current->_next); }

    // Post: Checks whether at end of the list.
    bool isDone() const { return !_current; }

    // Pre: The current element exists.
    // Post: The current element of this list is returned.
    T const &currentItem() const {
        if (!_current) {
            cerr << "currentItem precondition violated: "
                 << "Current element does not exist." << endl;
            throw -1;
        }
        return _current->_data;
    }
};

// ========= Constructors =========
template<class T>
LNode<T>::LNode(T const &data): _data(data) {
}

// ========= append =========
template<class T>
void ListL<T>::append(T const &data) {
    auto p = _head;
    auto temp = shared_ptr<LNode<T>>(new LNode<T>(data));
    if (isEmpty()) {
        _head = temp;
    } else {
        while (p-> _next) {
            p = p->_next;
        }
        p->_next = temp;
    }
}


// ========= clear =========
template<class T>
void ListL<T>::clear() {
    _head.reset();
}

// ========= concat =========
template<class T>
void ListL<T>::concat(ListL<T> &suffix) {
    cerr << "ListL<T>::concat: Exercise for the student." << endl;
    throw -1;
}

// ========= contains =========
template<class T>
bool ListL<T>::contains(T const &data) const {
    auto p = _head;
    while (p) {
        if (p->_data == data) {
            return true;
        } else {
            p = p -> _next;
        }
    }
    return false;
}

// ========= copyHead =========
template<class T>
shared_ptr<LNode<T>> ListL<T>::copyHead(ListL<T> const &rhs) {
    if (rhs.isEmpty()) {
        return nullptr;
    }
    else {
        auto p = rhs._head;
        auto result = shared_ptr<LNode<T>>(new LNode<T>(p->_data));
        auto q = result;
        while(p->_next) {
            p = p->_next;
            q->_next = shared_ptr<LNode<T>>(new LNode<T>(p->_data));
            q = q->_next;
        }
        return result;
        // You must use only three local variables: p, result, and q.
        // p and result are initialized above. You must initialize q,
        // followed by a single while loop with only three lines in the body.
    }
}

// ========= equals =========
template<class T>
bool ListL<T>::equals(ListL<T> const &rhs) const {
    auto p = _head;
    auto q = rhs._head;
    while (p && q) {
        if (!(p->_data == q->_data)){
            return false;
        }
        p = p-> _next;
        q = q-> _next;
        }
    if (p || q) {
        return false;
    }
    return true;
    }



    // Two initialization statements,
    // followed by a single while with three tests and two statements in the body,
    // followed by a single return.


// ========= first =========
template<class T>
T const &ListL<T>::first() const {
    if (!isEmpty()) {
        return _head -> _data;
    } else {
        cerr << "first() precondition violated, it is an empty list" << endl;
        throw -1;
    }
}

// ========= length =========
template<class T>
int ListL<T>::length() const {
    if (isEmpty()) {
        return 0;
    } else {
       auto p = _head;
       int count = 1;
       while (p) {
           if (p -> _next) {
               count ++;
           }
           p = p->_next;
       }
        return count;
    }
}

// ========= length2 =========
template<class T>
int ListL<T>::length2() const {
    ListLIterator<T> iter;
    iter.setIterListL(this->shared_from_this());
    int count = 0;
    for (iter.first(); !iter.isDone(); iter.next()){
        count ++;
    }
    return count;
}
// ========= max =========
template<class T>
T const &ListL<T>::max() const {
    if (isEmpty()) {
        cerr << "max precondition violated: An empty list has no maximum." << endl;
        throw -1;
    }
    T &result = _head->_data;
    cerr << "ListL<T>::max: Exercise for the student." << endl;
    throw -1;
}

// ========= max3 =========
template<class T>
T const &ListL<T>::max3() const {
    cerr << "ListL<T>::max3: Exercise for the student." << endl;
    throw -1;
}

// ========= operator= =========
template<class T>
ListL<T> &ListL<T>::operator=(ListL<T> const &rhs) {
    if (this != &rhs) { // In case someone writes myList = myList;
        _head = copyHead(rhs);
    }
    return *this;
}

// ========= operator== =========
template<class T>
bool operator==(ListL<T> const &lhs, ListL<T> const &rhs) {
    return lhs.equals(rhs);
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, ListL<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= prepend =========
template<class T>
void ListL<T>::prepend(T const &data) {
    auto temp = _head;
    _head.reset(new LNode<T>(data));
    _head->_next = temp;
}

// ========= remFirst =========
template<class T>
T ListL<T>::remFirst() {
    if(isEmpty()) {
        cerr << "You cannot remove the first element if the List is empty" << endl;
        throw -1;
    } else {
        T temp = _head -> _data;
        auto p = _head->_next;
        _head = p;
        return temp;
    }
}

// ========= remLast =========
template<class T>
T ListL<T>::remLast() {
    if (isEmpty()) {
        cerr << "You cannot remove the last element if the List is empty" << endl;
        throw -1;
    } else {
        auto p = _head;
        auto q = p;
        while (p->_next) {
            q = p;
            p = p->_next;
        }
        if (q->_next == nullptr) {
            _head = nullptr;
            return q->_data;
        }
        q->_next = nullptr;
        return p->_data;
    }
}

// ========= remove =========
template<class T>
void ListL<T>::remove(T const &data) {
    if (isEmpty()) {
        _head = nullptr;
    } else {
        auto p = _head;
        shared_ptr<LNode<T>> q = p;
        while (p->_next) {
            q = p;
            p = p->_next;
            if (q->_data == data) {
                _head = p;
            }
            if (p->_data == data) {
                q->_next = p->_next;
                p->_next = nullptr;
            }
        }
        if (q->_data == data) {
            _head = nullptr;
        }
    }
}


// ========= reverse =========
template<class T>
void ListL<T>::reverse() {
    shared_ptr<LNode<T>> pReverse;
    auto pRest = _head;
    while (pRest != nullptr) {
        auto next = pRest->_next;
        pRest->_next = pReverse;
        pReverse = pRest;
        pRest = next;
    }
    _head = pReverse;
}

    // Invariants:
    // pReverse points to the reverse of the first part of the list,
    // pRest points to the rest of the unmodified list.
    // A single while with four statements in the body,
    // followed by a single assignment to _head



// ========= setFirst =========
template<class T>
void ListL<T>::setFirst(T const &data) {
    if (isEmpty()) {
        cerr << "setFirst precondition violated: Cannot set first on an empty list." << endl;
        throw -1;
    }
    _head->_data = data;
}

// ========= toStream =========
template<class T>
void ListL<T>::toStream(ostream &os) const {
    os << "(";
    for (auto p = _head; p; p = p->_next) {
        if (p->_next) {
            os << p->_data << ", ";
        } else {
            os << p->_data;
        }
    }
    os << ")";
}

// ========= toStream4 =========
template<class T>
void ListL<T>::toStream4(ostream &os) const {
    ListLIterator<T> iter;
    iter.setIterListL(this->shared_from_this());
    os << "(";
    for (iter.first(); !iter.isDone(); iter.next()) {
        if (iter.hasNext()) {
            os << iter.currentItem() << ", ";
        } else {
            os << iter.currentItem();
        }
    }
    os << ")";
}

// ========= unZip =========
template<class T>
shared_ptr<ListL<T>> ListL<T>::unZip() {
    cerr << "ListL<T>::unZip: Exercise for the student." << endl;
    throw -1;
}

// ========= zip =========
template<class T>
void ListL<T>::zip(ListL<T> &other) {
    cerr << "ListL<T>::zip: Exercise for the student." << endl;
    throw -1;
}

#endif
