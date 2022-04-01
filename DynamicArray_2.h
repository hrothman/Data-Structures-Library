//
// Created by hroth on 7/10/2021.
//

#ifndef BASICDATASTRUCTURES_DYNAMICARRAY_2_H
#define BASICDATASTRUCTURES_DYNAMICARRAY_2_H

#include <cstdlib>
#include <math.h>


template<typename T>
class DynamicArray_2 {
public:
    // TYPEDEFS and MEMBER CONSTANTS
    typedef T value_type;
    typedef std::size_t size_type;
    static const size_type DEFAULT_CAPACITY = 30;
    // CONSTRUCTORS and DESTRUCTOR
    DynamicArray_2(size_type initial_capacity = DEFAULT_CAPACITY) /*Copy Constructor*/ {
        capacity = initial_capacity; // set capacity to new value
        data = new value_type[capacity]; //create an empty array of new size
        used = 0; //set used to 0 since array is empty
        current = -1; //set current to invalid index since array is empty
    }
    DynamicArray_2(const DynamicArray_2& SOURCE)
    {
        capacity = SOURCE.capacity; //set capacity to source's capacity
        data = new value_type[capacity]; //allocate new memory in order to do a DEEP copy
        for (size_t i = 0; i < SOURCE.used; ++i) //traverse through array (but only until used NOT capacity, it would work the same but is slightly faster in most cases)
            data[i] = SOURCE.data[i];
        used = SOURCE.used; //set used to source's used
        current = SOURCE.current; //set current to source's current
    }
    ~DynamicArray_2() {
        delete[] this->data; //return memory used for this program
    }
    // MODIFICATION MEMBER FUNCTIONS
    void resize(size_type new_capacity) {
        if (new_capacity <= capacity) //in case the new capacity is the same OR the new capacity is smaller
            return; //just return without doing anything
        value_type *temp; //warning referenced directly below is fixed by splitting statement instead of doing it all in 1 line
        temp = new value_type[new_capacity]; //create a new temp pointer pointing to an array
        for (size_t i = 0; i < capacity; ++i) //traverse through original array
            temp[i] = data[i]; //for every element of ORIGINAL array, copy it into the temp array
        delete[] data; //now delete memory for data
        data = temp; //and point data to new array with desired size
        capacity = new_capacity;
    }
    void to_first()
    {
        if (size() > 0)
            current = 0; //if the array is not empty set the index to the first element
        else
            current = -1; //if the array is empty then we must set current to an invalid index for future calls to is_item
    }
    void to_last()
    {
        if (size() > 0)
            current = used - 1; //if the array is not empty set the index to the last element
        else
            current = -1; //if the array is empty then we must set current to an invalid index for future calls to is_item
    }
    void prev()
    {
        --current; //We can de-increment current even if it is 0 since in that case it current must equal an invalid index value
    }
    void next()
    {
        if (current < used)
            ++current;//if the current value is not the last element of the array then increment current
        if (current == used)
            current = -1; //if current is already at the last index then we must set current to an invalid index for future calls to is_item
    }
    void insert(const value_type& ENTRY)
    {
//1st check if there is room to add
        if (used > capacity) //in case somehow used got messed up (not needed)
            resize(capacity + (used - capacity)); //resize to capacity plus the difference in used and capacity
        if (used == capacity) //if we are at capacity (VERY MUCH needed)
        {
            if (size() > 9)  //in case the size is ten or more, multiplying by 1.1 will give us desired result
                resize(capacity * 1.1); //resizing array by 10%
            else
                resize(capacity + 1); //resize the array by 1, done since if size is below 10 then it's just simpler than worrying about rounding
        }
        //allocate new memory for temp variable
        value_type* tempDataPtr; //warning referenced directly below is fixed by splitting statement instead of doing it all in 1 line
        tempDataPtr = new value_type[capacity];//compiler warning saying use auto when initializing a new to avoid duplicating  the type name, (but i am worried that auto may be an STL container)

        //2nd check if there is valid value for current
        if (current <= 0 || current >= used)
        { //current is invalid index OR current is first index
            tempDataPtr[0] = ENTRY; //sent first index to entry value
            current = 0; //set current to 0, since entry value is now there
            for (size_t i = 0; i < used; ++i)
                tempDataPtr[i + 1] = data[i];
        }
        else
        { //current is valid
            for (size_t i = 0, j = 0; i < used + 1; ++i, ++j) //traverse through array
            {
                if (i == current)
                { //i is equal to the current index
                    tempDataPtr[i] = ENTRY; // set temp of current index equal to the entry value
                    ++i; //increment i, since we just set temp
                    tempDataPtr[i] = data[j];  //copy over old right before current index item into new array
                }
                else //i is not equal to current
                    tempDataPtr[i] = data[j];//copy over old right before current index item into new array
            }
        }
        ++used; //increment used values
        delete[] data;//delete memory for data
        data = tempDataPtr; //point data to the temporary array with the new size and value
    }
    void append(const value_type& ENTRY)
    {
//1st check if there is room to add
        if (used > capacity) //in case somehow used got messed up (not needed)
            resize(capacity + (used - capacity)); //resize to capacity plus the difference in used and capacity
        if (used == capacity) //if we are at capacity (VERY MUCH needed)
        {
            if (size() > 9)  //in case the size is ten or more, multiplying by 1.1 will give us desired result
                resize(capacity * 1.1); //resizing array by 10%
            else
                resize(capacity + 1); // resize the array by 1, done since if size is below 10 then it's just simpler than worrying about rounding
        }

        //allocate new memory for temp variable
        value_type* tempDataPtr; //warning referenced directly below is fixed by splitting statement instead of doing it all in 1 line
        tempDataPtr = new value_type[capacity];//compiler warning saying use auto when initializing a new to avoid duplicating  the type name, (but i am worried that auto may be an STL container)

        //2nd check if there is valid value for current
        if ((current <= 0 || current >= used))
        { //if current is invalid OR current is 0; either way same result insert at the last position
            for (size_t i = 0; i < used; ++i) //traverse through array
                tempDataPtr[i] = data[i]; //copy old items into new array
            tempDataPtr[used] = ENTRY; //set last index to the entry value
            current = used; // set current to the inserted value
        }
        else
        { //current index is valid
            for (size_t i = 0, j = 0; i < used + 1; ++i, ++j) //traverse through array
            {
                if (current == i)
                { //i is equal to current index
                    tempDataPtr[i] = data[j]; //copy over old right before current index item into new array
                    ++i; //increment i, the counter for temp array
                    tempDataPtr[i] = ENTRY; //set index after current to the entry value
                    current = i; // set current to the inserted value
                }
                else //i is not equal to current
                    tempDataPtr[i] = data[j];  //copy over old right before current index item into new array
            }
        }
        ++used; //increment used values
        delete [] data; //delete memory for data
        data = tempDataPtr; //point data to the temporary array with the new size and value
    }
    void remove()
    {
        if (size() < 1) //if the array is empty there is nothing to remove
            return; //so return
        for (size_t i = 0, j = 0; j < used; ++i, ++j) //traverse through array
        {
            if (i == current)
            { //i is equal to the current index
                ++j; //increment j to skip over remove index
                data[i] = data[j]; //copy over skipping remove index
            }
            else
                data[i] = data[j]; //copy over data
        }
        --used; //de-increment used;
        if (current + 1 < used) //if we can increment current without getting an invalid index
            ++current; //increment current
    }
    DynamicArray_2& operator=(const DynamicArray_2& SOURCE)
    {
        if (this != &SOURCE) //self assignment check
        {
            delete[] this->data; //delete the memory to avoid memory leak
            this->data = new value_type[SOURCE.capacity]; // allocate new memory in order to do a DEEP copy
            for (size_t i = 0; i < SOURCE.used; ++i) //traverse through array (but only until used NOT capacity, it would work the same but is slightly faster in most cases)
                this->data[i] = SOURCE.data[i]; //for every element of SOURCE array being used, copy it into the original  array
            this->capacity = SOURCE.capacity; //set capacity to new capacity
            this->used = SOURCE.used; //set used to new used
            this->current = SOURCE.current; //set current to new current
            return *this; //return newly changed object
        }
        //self assignment check (if the passed object's data points to the same memory location as the this objects data)
        return *this; //if they are the same no need to do anything else just return the object
    }
// CONSTANT MEMBER FUNCTIONS
    bool is_item() const
    {
        if (capacity <= 0 || used <= 0) //if capacity is less than or equal to 0 OR used is less than or equal to 0
            return false; //return false because array will be empty
        if (current >= 0 && current < used) //if current is greater than or equal to 0 AND current is less than used
            return true; //return true because current item is valid
        return false; //anything else should return false
    }
    value_type current_value() const
    {
        return data[current];
    }
    size_type size() const { return used; };
    value_type current_index() const { return current; };
    value_type standard_deviation() const
    {
        value_type average = 0, variance = 0; //initialize temporary variables used in calculations
        for (size_t i = current; i < used; ++i) //traverse through array from current until used
            average += data[i]; //add up all the values of data into average
        average /= (used - current); //divide average by the number of elements that were added
        for (size_t i = current; i < used; ++i) //traverse through array from current until used
            variance += ((data[i] - average) * (data[i] - average)); //add up all the values of the difference between the current element of data and the average value all squared
        variance /= (used - current); //divide variance by the number of elements that were added
        return sqrt(variance); //return the square root of the variance (the standard deviation)
    }
    private:
    value_type* data;
    size_type used;
    size_type current;
    size_type capacity;

};





#endif //BASICDATASTRUCTURES_DYNAMICARRAY_2_H
