//
// Created by hroth on 7/10/2021.
//

#ifndef BASICDATASTRUCTURES_NODE_DLL_H
#define BASICDATASTRUCTURES_NODE_DLL_H

template<typename T>
class node_s {
public:
    typedef T value_type;
    node_s(value_type d = value_type(), node_s * n = nullptr, node_s * p = nullptr) : data_field(d), next_ptr(n), prev_ptr(p) {}

    //Assessor/Getters
    const value_type& getData () const { return data_field; }
    node_s const * getPrev () const { return prev_ptr; }
    node_s const * getNext () const { return next_ptr; }
    //Shorter versions of the above two
    node_s const * prev () const { return prev_ptr; }
    node_s const * next () const { return next_ptr; }

    //Mutators/Setters
    void setData (const value_type& d) { data_field = d; }
    void setPrev (node_s * new_link) { prev_ptr = new_link; }
    void setNext (node_s * new_link) { next_ptr = new_link; }

    //Other
    value_type& data() { return data_field; }
    const value_type& data() const { return data_field; }
    node_s*& prev () { return prev_ptr; }
    node_s*& next () { return next_ptr; }

private:
    value_type data_field;
    node_s* next_ptr;
    node_s* prev_ptr;
};

#endif //BASICDATASTRUCTURES_NODE_DLL_H
