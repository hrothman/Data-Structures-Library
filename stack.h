//
// Created by hroth on 7/10/2021.
//

#ifndef BASICDATASTRUCTURES_STACK_H
#define BASICDATASTRUCTURES_STACK_H

#include "node_s.h"

template<typename T>
class stack {
public:
    typedef T value_type;

    node_s<value_type> *getTop() const {
        return top;
    }
    void pop() {
        node_s<value_type> * temp = top->below();
        temp->setAbove(nullptr);
        delete top;
        top = temp;
    }
    void add(node_s<value_type> * addVal) {
        top->setAbove(addVal);
        top = addVal;
    }

private:
    node_s<value_type> * top;

};


#endif //BASICDATASTRUCTURES_STACK_H
