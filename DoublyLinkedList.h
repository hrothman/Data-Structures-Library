//
// Created by hroth on 7/10/2021.
//

#ifndef BASICDATASTRUCTURES_DOUBLYLINKEDLIST_H
#define BASICDATASTRUCTURES_DOUBLYLINKEDLIST_H

#include <initializer_list>
#include "node_dll.h"
#include <math.h>

template<typename T>
class DoublyLList {
public:

    // TYPEDEFS and MEMBER CONSTANTS
    typedef T value_type;
    typedef std::size_t size_type;
    typedef node_s<value_type> node;
    // CONSTRUCTORS and DESTRUCTOR
    DoublyLList(std::initializer_list<value_type> list)
    {
        current = head = tail = nullptr;
        node_count = 0;
        //iterate through passed initializer list
        for (auto item : list)
            append(item);
    }

    DoublyLList(const DoublyLList &source)
    {
        node_count = 0;
        head = tail = current = nullptr;
        //Using overloaded assignment operator
        *this = source;
    }

    ~DoublyLList()
    {
        empty();
    }

// MODIFICATION MEMBER FUNCTIONS
    void to_first()
    {
        current = head;
    }
    void to_last()
    {
        current = tail;
    }
    void prev()
    {
        if (current == head)
            current = nullptr;
        else
            current = current->prev();
    }
    void next()
    {
        if (current == tail)
            current = nullptr;
        else
        {
            current = current->next();
        }
    }
    void insert(const value_type& entry)
    {
        //Case 1: Current points to an invalid node
        if (current == nullptr)
        {
            //Case 1A: List is empty
            if (tail != nullptr || head != nullptr)
            {
                current = head;
                node *temp = new node_s<T>(entry);
                temp->setNext(current);
                current->setPrev(temp);
                temp->setPrev(nullptr);
                head = temp;
                ++node_count;
                current = temp;
                return;
            }
            //Case 1B: List is not empty
            node * temp = new node(entry);
            current = temp;
            tail = head = current;
            ++node_count;
            return;
        }
        //Case 2: Inserting to "middle"
        if (current->prev() != nullptr) {
            node *temp = new node(entry);
            temp->setPrev(current->prev());
            temp->setNext(current);
            current->setPrev(temp);
            temp->prev()->setNext(temp);
            ++node_count;
            current = temp;
            return;
        }
        //Case 3: Inserting at beginning
        node *temp = new node(entry);
        temp->setNext(current);
        current->setPrev(temp);
        temp->setPrev(nullptr);
        head = temp;
        ++node_count;
        current = temp;
    }
    void append(const value_type &entry)
    {
        //Case 1: Current points to an invalid node
        if (current == nullptr)
        {
            //Case 1A: List is empty
            if (tail != nullptr || head != nullptr)
            {
                current = tail;
                node * temp = new node(entry);
                current->setNext(temp);
                temp->setPrev(current);
                temp->setNext(nullptr);
                tail = temp;
                ++node_count;
                current = temp;
                return;
            }
            //Case 1B: List is not empty
            node * temp = new node(entry);
            current = temp;
            head = tail = temp;
            ++node_count;
            current = temp;
            return;
        }
        //case 2: Appending at end
        if (tail == current)
        {
            node * temp = new node(entry);
            current->setNext(temp);
            temp->setPrev(current);
            temp->setNext(nullptr);
            tail = temp;
            ++node_count;
            current = temp;
            return;
        }
        //Case 3: Appending to "middle"
        node * temp = new node(entry);
        temp->setPrev(current);
        temp->setNext(current->next());
        current->setNext(temp);
        temp->next()->setPrev(temp);
        ++node_count;
        current = temp;
    }
    void empty()
    {
        //If list is not already empty
        if (head != nullptr)
        {
            to_first();
            while (node_count > 0) {
                remove();
            }
        }
    }
    void remove()
    {
        //Case 1: List is empty
        if (head == nullptr)
            return;
        //Case 2: List contains 1 item
        if (node_count == 1)
        {
            tail = head = nullptr;
            delete current;
            current = nullptr;
            node_count = 0;
            return;
        }
        //Case 3: Removing from the end of the list
        if (current == tail)
        {
            node * temp = current;
            current = current->prev();
            current->setNext(nullptr);
            tail = current;
            delete temp;
            --node_count;
            return;
        }
        //Case 4: Removing from the beginning of the list
        if (current == head)
        {
            node * temp = current;
            current = current->next();
            head = current;
            current->setPrev(nullptr);
            delete temp;
            --node_count;
            return;
        }
        //Case 5: Removing from the middle of the list
        node * temp = current;
        current = current->next();
        temp->prev()->setNext(current);
        current->setPrev(temp->prev());
        delete temp;
        --node_count;
    }

    DoublyLList& operator=(const DoublyLList &source)
    {
        //Check for self-assignment
        if (this == &source)
            return *this;
        this->empty();
        node * temp = nullptr;
        //If source is empty
        if (source.node_count > 0 && (source.head != nullptr && source.tail != nullptr))
        {
            for (auto it = source.head; it != nullptr; it = it->next())
            {
                this->append(it->data());
                if (&it == &source.current)
                {
                    temp = this->current;
                }
            }
            this->current = temp;
        }
        return *this;
    }

// CONSTANT MEMBER FUNCTIONS
    bool is_item() const
    {
        return (current != nullptr);
    }

    size_type size( ) const { return node_count; };
    const value_type& current_value() const
    {
        return current->data();
    }

    size_type current_index() const
    {
        if (is_item())
        {
            size_type i = 0;
            node * temp = head;
            while (temp->next() != nullptr)
            {
                temp = temp->next();
                ++i;
            }
            return i;
        }
        return node_count;
    }

    value_type standard_deviation() const
    {
        //Calculates standard deviation
        value_type average = value_type(), variance = value_type(), counter = value_type();
        //Traverse from current node to tail node for average
        for (auto it = current; it != tail->next(); it = it->next())
        {
            average += it->data();
            ++counter;
        }
        average /= (counter);
        //Traverse from current node to tail node for variance
        for (auto it = current; it != tail->next(); it = it->next())
            variance += ((it->data() - average) * (it->data() - average));
        variance /= (counter);
        return sqrt(variance);
    }
private:
    node* head;
    node* tail;
    size_type node_count;
    node_s<T>* current;
    

};

#endif //BASICDATASTRUCTURES_DOUBLYLINKEDLIST_H
