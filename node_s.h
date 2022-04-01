//
// Created by hroth on 7/10/2021.
//

#ifndef BASICDATASTRUCTURES_NODE_S_H
#define BASICDATASTRUCTURES_NODE_S_H

template<typename T>
class node_s {
public:
    typedef T value_type;
    node_s(value_type d = value_type(), node_s * n = nullptr, node_s * p = nullptr) : data_field(d), above_ptr(n), below_ptr(p) {}

    //Assessor/Getters
    const value_type& getData () const { return data_field; }
    node_s const * getAbove () const { return above_ptr; }
    node_s const * getBelow () const { return below_ptr; }
    //Shorter versions of the above two
    node_s const * above () const { return above_ptr; }
    node_s const * below () const { return below_ptr; }

    //Mutators/Setters
    void setData (const value_type& d) { data_field = d; }
    void setPrev (node_s * new_link) { prev_ptr = new_link; }
    void setAbove (node_s * new_link) { above_ptr = new_link; }

    //Other
    value_type& data() { return data_field; }
    const value_type& data() const { return data_field; }
    node_s*& prev () { return prev_ptr; }
    node_s*& above () { return above_ptr; }

private:
    value_type data_field;
    node_s* above_ptr;
    node_s* below_ptr;
};


#endif //BASICDATASTRUCTURES_NODE_S_H
