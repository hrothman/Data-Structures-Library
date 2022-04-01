//
// Created by hroth on 7/9/2021.
//

#ifndef BASICDATASTRUCTURES_DYNAMICARRAY_H
#define BASICDATASTRUCTURES_DYNAMICARRAY_H


#include <ctime>

template<typename T>
class DynamicArray {
public:

    DynamicArray(const size_t p_SIZE, T p_Array[]){
        copy(p_SIZE, p_Array);
        used = p_SIZE;
    }
    DynamicArray(DynamicArray<T> const &p_staticArray){
        copy(p_staticArray);
        used = p_staticArray.size();
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
    void setIndex(size_t p_Index) {
        index = p_Index;
    }
    void next()  {
        if (index == MAXSIZE - 1)
            index = 0;
        else
            ++index;
    }
    void prev()  {
        if (index == 0)
            index = MAXSIZE-1;
        else
            --index;
    }
    /*
    void copy(const unsigned int p_SIZE, T p_array[]) {
        if (p_SIZE > MAXSIZE)
            resize(p_SIZE);
        for (size_t i = 0; i < MAXSIZE; ++i)
            array[i] = T(p_array[i]);
        MAXSIZE = p_SIZE;
    }
    void copy(DynamicArray<T> const &p_DynamicArray) {
        if (p_DynamicArray.size() > MAXSIZE)
            resize(p_DynamicArray.size());
        for (size_t i = 0; i < MAXSIZE; ++i)
            array[i] = p_DynamicArray.getAt(i);
        MAXSIZE = p_DynamicArray.size();
    }
    void resize(const size_t newSize) {
        if (MAXSIZE == newSize)
            return;

        T * newArray = new T[newSize];
        for (size_t i = 0; i < newSize; ++i) {
            newArray[i] = array[i];
        }
        delete [] array;
        array = newArray;
        MAXSIZE = newSize;
    }

    void insert(const size_t INDEX, T entry) {
        if (used == MAXSIZE)
            resize(MAXSIZE + MAXSIZE / 2);
        T * newArray = new int[MAXSIZE];
        for (size_t i = 0; i < used + 1; ++i) {
            if (INDEX == i)
                newArray[i] = entry;
            newArray[i] = array[i];
        }
        delete [] array;
        array = newArray;
        ++used;
    } */

private:
    size_t index;
    size_t used;
    static size_t MAXSIZE;
    T *array;

};


#endif //BASICDATASTRUCTURES_DYNAMICARRAY_H
