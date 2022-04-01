//
// Created by hroth on 7/10/2021.
//

#ifndef BASICDATASTRUCTURES_NODE_BPTREE_H
#define BASICDATASTRUCTURES_NODE_BPTREE_H

#include <ostream>

template <typename T>
class node
{
public:
    typedef T value_type;
    node(value_type d = value_type(), node * p = nullptr, node * l = nullptr, node * r = nullptr)
            : data_field(d), parent_ptr(p), left_ptr(l), right_ptr(r) {}

    //Accessors/Getters
    const value_type& data() const { return data_field; }
    node const * parent () const { return parent_ptr; }
    node const * left () const { return left_ptr; }
    node const * right () const { return right_ptr; }
    bool isLeaf() const { return left_ptr == nullptr && right_ptr == nullptr; }

    //Mutators/Setters
    void setData (const value_type& d) {data_field = d; }
    void setParent (node * new_link) {parent_ptr= new_link; }
    void setLeft (node * new_link) {left_ptr= new_link; }
    void setRight (node * new_link) {right_ptr = new_link; }
    //Special accessors that give us a mutable item
    value_type& data() { return data_field; }
    node*& parent() { return parent_ptr; }
    node*& left() { return left_ptr; }
    node*& right () { return right_ptr; }

private:
    value_type data_field;
    node* parent_ptr;
    node* left_ptr;
    node* right_ptr;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const node<T>* n) {
    out << n->data();
    return out;
}

#endif //BASICDATASTRUCTURES_NODE_BPTREE_H
