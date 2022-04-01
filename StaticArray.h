//
// Created by hroth on 7/9/2021.
//

#ifndef BASICDATASTRUCTURES_STATICARRAY_H
#define BASICDATASTRUCTURES_STATICARRAY_H


#include <ctime>

template<typename T>
class StaticArray {
public:
    StaticArray(const size_t p_SIZE, T p_Array[]){
        copy(p_SIZE, p_Array);
    }
    StaticArray(StaticArray<T> const &p_staticArray){
        copy(p_staticArray);
    }

    unsigned int size() const { return MAXSIZE; }
    T current() const { return array[index]; }
    T *getArray() const { return array; }
    T getAt(size_t index) const {
        if (index < MAXSIZE)
            return array[index];
        return T();
    }
    void setAt(size_t index, T entry) {
        if (index < MAXSIZE)
            array[index] = entry;
    }

    size_t getIndex() const {
        return index;
    }
    void setIndex(size_t index) {
        StaticArray::index = index;
    }
    void next()  {
        if (index == MAXSIZE - 1)
            index = 0;
        else
            ++index;
    }
    void prev()  {
        if (index == 0)
            index = MAXSIZE - 1;
        else
            --index;
    }

    void copy(const unsigned int p_SIZE, T p_array[]) {
        if (p_SIZE > MAXSIZE)
        {
            for (size_t i = 0; i < MAXSIZE; ++i)
                array[i] = p_array[i];
        }
        else {
            for (size_t i = 0; i < p_SIZE; ++i)
                array[i] = p_array[i];
        }
    }
    void copy(StaticArray<T> const &p_StaticArray) {
        if (p_StaticArray.size() > MAXSIZE)
        {
            for (size_t i = 0; i < MAXSIZE; ++i)
                array[i] = p_StaticArray.array[i];
        }
        else {
            for (size_t i = 0; i < p_StaticArray.size(); ++i)
                array[i] = p_StaticArray.array[i];
        }
    }

private:
    size_t index;
    static const unsigned int MAXSIZE = 10;
    T array[MAXSIZE];


};

#endif //BASICDATASTRUCTURES_STATICARRAY_H
