//
// Created by hroth on 7/10/2021.
//

#ifndef BASICDATASTRUCTURES_BINARYSTREE_H
#define BASICDATASTRUCTURES_BINARYSTREE_H

#include "node_bptree.h"

template <typename T>
class bSTree
{
public:
    // TYPEDEFS and MEMBER CONSTANTS
    typedef T value_type;
    typedef std::size_t size_type;
    typedef node<value_type> node;

    node * getRoot() { return root; }

    // CONSTRUCTORS and DESTRUCTOR
    bSTree() { root = current = nullptr; node_count = 0; };

    //   sequence(std::initializer_list<value_type>)
    //     Postcondition: The sequence has been initialized using the passed sequence to initialize the
    //                    sequence. The current item will be set to the FIRST item in the sequence.
    //                    See the provided function in main from project 1 for help working with initializer lists, cool feature of C++11
    bSTree(std::initializer_list<value_type> int_List)
    {
        current = root = nullptr;
        node_count = 0;
        for (auto item : int_List)
            add(item);
    }
    //Dependencies: assignment operator
    bSTree(const bSTree& nObj) {
        node_count = 0;
        current = root = nullptr;
        copy(nObj.root);
        current = nObj.current;
    }

    ~bSTree() {
        empty();
    }
    // MODIFICATION MEMBER FUNCTIONS
    void to_first() { current = to_firstRec(root); }
    void to_last() { current = to_lastRec(root); }

    void prev()
    {
        if (!is_item())
            return;
        //Case 1: Item has a left child, THIS CASE WORKS
        if (current->left() != nullptr)
        {
            node* temp = current->left();
            while (temp->right() != nullptr)
            {
                temp = temp->right();
            }
            current = temp;
            return;
        }
        //Case 3: Item is root, case 1 should take care of this however
        //        if root does not have a left child then we must
        if (current->parent() == nullptr)
        {
            current = nullptr;
            return;
        }
        //Case 2: Item has a parent
        //if (current->parent() != nullptr)

        //Case 2A: Item is the right child of it's parent
        if (current->parent()->right() == current) //check if its right child
        {
            current = current->parent();
            return;
        }
        //Case 2B: Item is the left child of it's parent
        node* temp = current->parent();
        while (temp->data() >= current->data())
        {
            if (temp->parent() == nullptr)
            {
                current = nullptr;
                return;
            }
            temp = temp->parent();
        }
        current = temp;
    }
    void next()
    {
        if (!is_item())
            return;
        //Case 1: Item has a right child,
        if (current->right() != nullptr)
        {
            node* temp = current->right();
            while (temp->left() != nullptr)
            {
                temp = temp->left();
            }
            current = temp;
            return;
        }
        //Case 3: Item is root, case 1 should take care of this however
        //        if root does not have a right child then we must
        if (current->parent() == nullptr)
        {
            current = nullptr;
            return;
        }
        //Case 2: Item has a parent
        //if (current->parent() != nullptr)

        //Case 2A: Item is the right child of it's parent
        if (current->parent()->left() == current) //check if its right child
        {
            current = current->parent();
            return;
        }
        //Case 2B: Item is the left child of it's parent
        node* temp = current->parent();
        while (temp->data() < current->data())
        {
            if (temp->parent() == nullptr)
            {
                current = nullptr;
                return;
            }
            temp = temp->parent();
        }
        current = temp;
    }
    void add(const value_type& entry)
    {
        //Case 1: empty tree
        if (root == nullptr)
        {
            root = new node(entry);
            current = root;
            node_count = 1;
            return;
        }
        //Case 2: Tree is size > 0
        getAddSpotRet(entry, root);
        node* temp = current;
        if (temp->data() >= entry)
        {
            temp->setLeft(new node(entry, temp));
            current = temp->left();
        }
        else
        {
            temp->setRight(new node(entry, temp));
            current = temp->right();
        }
        ++node_count;
    }
    void empty() { empty(root); root = current = nullptr; }
    void remove() {
        if (current == nullptr)
            return;
        //Case 3: Current is leaf
        if (current->isLeaf())
        {
            node* temp = current;
            if (current->parent() != nullptr) {
                //Check if right child of parent
                if (current->parent()->right() == current)
                    current->parent()->right() = nullptr;
                else //must be left child then
                    current->parent()->left() = nullptr;
            }
            else
                root = current->parent();
            current = current->parent();
            delete temp;
            --node_count;
            return;
        }
        //Case 1: Current has left child
        if (current->left() != nullptr) {
            //Case 1A: Current's left child has right child
            if (current->left()->right() != nullptr) {
                node* temp = current->left()->right();
                while (temp->right() != nullptr) {
                    temp = temp->right();
                }
                current->setData(temp->data());
                if (temp->left() == nullptr)
                {
                    temp->parent()->setRight(nullptr);
                    delete temp;
                    --node_count;
                    return;
                }
                temp->left()->setParent(temp->parent());
                temp->parent()->setRight(temp->left());
                delete temp;
                --node_count;
                return;
            }
            //Case 1B: Current's left child has no right
            //Case 1B-1: current has parent
            if (current->parent() != nullptr) {
                //Case 1B-1A: current is the right child
                if (current->parent()->right() == current) {
                    current->parent()->right() = current->left();
                }
                else {
                    current->parent()->left() = current->left();
                }
                current->left()->setParent(current->parent());
                if (current->right() != nullptr) {
                    current->left()->setRight(current->right());
                }

                node* temp = current;
                current = current->left();
                delete temp;
                --node_count;
                return;
            }
            //Case 1B-1B: Current is root but has left child
            if (current->right() != nullptr)
            {
                current->left()->setRight(current->right());
                current->right()->setParent(current->left());
            }

        }
        //Case 2: Current only has right
        //Case 2A: Current has no parent
        if (current->parent() == nullptr)
        {
            if (current->left() != nullptr)
                root = current->left();
            else
                root = current->right();
            root->setParent(nullptr);
            delete current;
            current = root;
            --node_count;
            return;
        }
        //Case 2B: Current has parent
        if (current->parent()->right() == current)
            current->parent()->right() = current->right();
        else
            current->parent()->left() = current->right();
        current->right()->setParent(current->parent());
        node* temp = current;
        current = current->right();
        delete temp;
        --node_count;
    }

    bSTree& operator=(const bSTree& PASSED)
    {
        if (this == &PASSED)
            return *this;
        if (node_count > 0)
            empty();
        copy(PASSED.root);
        current = PASSED.current;
        return *this;
    }
    // CONSTANT MEMBER FUNCTIONS
    size_type size() const { return node_count; };
    //   bool is_item( ) const
    //     Postcondition: A true return value indicates that there is a valid
    //                    "current" item that may be retrieved by activating the current_value
    //                    member function (listed below). A false return value indicates that
    //                    there is no valid current_value item.
    bool is_item() const { return current != nullptr; }


    const value_type& current_value() const { return current->data(); }
    value_type standard_deviation() const
    {
        bSTree<T> i = *this;
        size_t pos = i.getPosition(i.current);
        value_type avg = i.sum(i.current) / pos;
        value_type var = i.variance(i.current, avg);
        return sqrt(var / pos);
    }

    //Note these should be const, but I found implementation a little easier without const
    std::string to_string()
    {
        std::string str = "[ ";
        bSTree<T>* temp = this;
        temp->to_first();
        return "[ " + to_stringRec(temp->current) + " ]";
    }
    std::string to_rstring()
    {
        std::string str = "[ ";
        bSTree<T>* temp = this;
        temp->to_last();
        return "[ " + to_rstringRec(temp->current) + " ]";
    }

    //Student can add additional functions here
    //***************Newly Added Helper Functions (since attempt 1)******************


    //Preconditions:
    //Postconditions: Will return the passed node's next node
    //Returns the node in front of to the passed node,
    node* next(node* pNode) const
    {
        if (!is_item())
            return nullptr;
        //Case 1: Item has a right child,
        if (pNode->right() != nullptr)
        {
            node* temp = pNode->right();
            while (temp->left() != nullptr)
            {
                temp = temp->left();
            }
            return temp;
        }
        //Case 3: Item is root, case 1 should take care of this however
        //        if root does not have a right child then we must
        if (pNode->parent() == nullptr)
        {
            return nullptr;
        }
        //Case 2: Item has a parent
        //if (current->parent() != nullptr)

        //Case 2A: Item is the right child of it's parent
        if (pNode->parent()->left() == pNode) //check if its right child
        {
            return pNode->parent();
        }
        //Case 2B: Item is the left child of it's parent
        node* temp = pNode->parent();
        while (temp->data() < pNode->data())
        {
            if (temp->parent() == nullptr)
            {
                return nullptr;
            }
            temp = temp->parent();
        }
        return temp;
    }

    //Preconditions:
    //Postconditions: Will return the passed node's previous node
    node* prev(node* pNode) const
    {
        if (!is_item())
            return nullptr;
        //Case 1: Item has a left child, THIS CASE WORKS
        if (pNode->left() != nullptr)
        {
            node* temp = pNode->left();
            while (temp->right() != nullptr)
            {
                temp = temp->right();
            }
            return temp;
        }
        //Case 3: Item is root, case 1 should take care of this however
        //        if root does not have a left child then we must
        if (pNode->parent() == nullptr)
        {
            return nullptr;
        }
        //Case 2: Item has a parent
        //if (current->parent() != nullptr)

        //Case 2A: Item is the right child of it's parent
        if (pNode->parent()->right() == pNode) //check if its right child
        {
            return pNode->parent();
        }
        //Case 2B: Item is the left child of it's parent
        node* temp = pNode->parent();
        while (temp->data() >= pNode->data())
        {
            if (temp->parent() == nullptr)
            {
                return nullptr;
            }
            temp = temp->parent();
        }
        return temp;
    }

    //Preconditions:
    //Postconditions: Will recursively return the sum from the given node to the end of the ordered representation. Counter
    //                can be used for average and variance or getPosition function (counter is probably less expensive but
    //                also requires use of memory)
    value_type sum(node* pNode, size_t counter = 0)
    {
        if (pNode == nullptr)
            return NULL;
        if (next(pNode) == nullptr)
        {
            ++counter;
            return pNode->data();
        }
        ++counter;
        return pNode->data() + sum(next(pNode));
    }

    //Preconditions:
    //Postconditions: Will recursively return the position from the given node to the end of the ordered representation
    size_t getPosition(node* pNode)
    {
        if (pNode == nullptr)
            return 0;
        if (next(pNode) == nullptr)
        {
            return 1;
        }
        return 1 + getPosition(next(pNode));

    }

    //Preconditions:
    //Postconditions: Returns a pointer to current
    node* getCurrent() const { return current; }

    //Preconditions:
    //Postconditions: Will recursively return the variance from the node given on, using the average given
    //                as well as the position from the given node to the end of the ordered representation
    value_type variance(node* pNode, value_type avg)
    {
        if (pNode == nullptr)
            return NULL;
        if (next(pNode) == nullptr)
            return (pNode->data() - avg) * (pNode->data() - avg);
        return (pNode->data() - avg) * (pNode->data() - avg) + variance(next(pNode), avg);

    }




    //*******************************8
private:

    node* root;
    size_type node_count;
    node* current;
    void empty( node* pNode)
    {
        if (pNode == nullptr)
            return;
        current = pNode;
        remove();
        empty(current);
    }

    //Student can add additional functions here

    //Preconditions
    //Postconditions: Will return the last node in a tree starting at the first passed node
    node* to_lastRec(node* pNode)
    {
        if (pNode == nullptr)
            return nullptr;
        if (pNode->right() == nullptr)
            return pNode;
        return to_lastRec(pNode->right());
    }

    //Preconditions
    //Postconditions: Will return the first node in a tree starting at the first passed node
    node* to_firstRec(node* pNode)
    {
        if (pNode == nullptr)
            return nullptr;
        if (pNode->left() == nullptr)
            return pNode;
        return to_firstRec(pNode->left());
    }

    //Preconditions:
    //Postconditions: Will set current to passed node
    void setCurrent(node* pNode)
    {
        current = pNode;
    }

    //Preconditions:
    //Postconditions: this function will recursively find the spot we should add to based on the entry value
    //                sets current to the location, DOES NOT do actual adding
    void getAddSpotRet(value_type entry, node* pRoot)
    {
        //Case 2A: entry <= temp val
        if (entry <= pRoot->data())
        {
            //Case 2A-2: go to next
            if (pRoot->left() != nullptr)
            {
                getAddSpotRet(entry, pRoot->left());
                return;
            }
            current = pRoot;
        }
        //Case 2B: entry > temp val
        if (entry > pRoot->data()) {
            //Case 2B-2: go to next
            if (pRoot->right() != nullptr)
            {
                getAddSpotRet(entry, pRoot->right());
                return;
            }
            current = pRoot;
        }
    }

    //Preconditions:
    //Postconditions: This function is passed a root node to a BST and recursively adds the passed BST
    //                to the object's BST
    void copy(node* nRoot)
    {
        if (nRoot == nullptr)
            return;
        add(nRoot->data());
        if (nRoot->left() != nullptr)
        {
            copy(nRoot->left());
        }
        if (nRoot->right() != nullptr)
        {
            copy(nRoot->right());
        }
    }

    //Recursive to string
    std::string to_stringRec(node* pNode) const
    {
        if (next(pNode) == nullptr)
            return std::to_string(pNode->data());
        return std::to_string(pNode->data()) + ", " + to_stringRec(next(pNode));
    }
    //Recursive to rstring
    std::string to_rstringRec(node* pNode) const
    {
        if (prev(pNode) == nullptr)
            return std::to_string(pNode->data());
        return std::to_string(pNode->data()) + ", " + to_rstringRec(prev(pNode));
    }

};


#endif //BASICDATASTRUCTURES_BINARYSTREE_H
