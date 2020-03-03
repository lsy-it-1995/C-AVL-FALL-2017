#ifndef TREENODEFORAVL_H
#define TREENODEFORAVL_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "../../../Documents/CS8(assignment)/BinarySearchTree/tree.h"
#include <cassert>

using namespace std;

template <typename T>
struct tree_node{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;

    int balance_factor()
    {
        //balance factor = height of the left subtree - the height of the right subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        int leftbalance=0, rightbalance=0;
        if(!_left)
            leftbalance=-1;
        else if(_left->height()==0)
            leftbalance=0;
        else
            leftbalance = _left->_height;

        if(!_right)
            rightbalance=-1;
        else if(_right->height()==0)
            rightbalance=0;
        else
            rightbalance = _right->_height;

        return leftbalance - rightbalance;
    }
    int height()
    {
        int leftbalance=0, rightbalance=0;
        if(!_left)
            leftbalance=-1;
        else if(_left->height()==0)
            leftbalance=0;
        else
            leftbalance = _left->height();

        if(!_right)
            rightbalance=-1;
        else if(_right->height()==0)
            rightbalance=0;
        else
            rightbalance = _right->height();

        if(rightbalance<leftbalance)
            return leftbalance+1;
        else
            return rightbalance+1;
    }

    int update_height()
    {
        //set the _height member variable (call height();)
        _height = height();
        return _height;

    }

    tree_node(T item=T(), tree_node* left=NULL, tree_node* right=NULL): _item(item), _left(left), _right(right)
    {
        _height = height();
        //don't forget to set the _height.

    }
    friend ostream& operator <<(ostream& outs, const tree_node<T>& t_node)
    {
        outs<<"|"<<t_node._item<<"|";
        return outs;
    }
};


// ---------------- ROTATIONS --------------------------
template <typename T>
tree_node<T>* rotate_right(tree_node<T>* &root)
{
    tree_node<T> *temproot;
    temproot = root->_left;
    root->_left = temproot->_right;
    temproot->_right = root;
    root = temproot;
    return root;
}
template <typename T>
tree_node<T>* rotate_left(tree_node<T>* &root)
{
    tree_node<T> *temproot;
    temproot = root->_right;
    root->_right = temproot->_left;
    temproot->_left = root;
    root = temproot;
    return root;
}
template <typename T>
tree_node<T>* rotate(tree_node<T>* & root) //decide which rotate is needed based on balance factor
{
    if(root)
    {
        if(root->balance_factor()<=-2)//left heavy
        {
            if(root->_right->balance_factor()>=1)
            {
                rotate_right(root->_right);
                rotate_left(root);
            }
            else
            {
                rotate_left(root);
            }
            root->update_height();
            root->_left->update_height();
            root->_right->update_height();
        }
        else if(root->balance_factor()>=2) //right heavy
        {
            if(root->_left->balance_factor()<=-1)
            {
                rotate_left(root->_left);
                rotate_right(root);
            }
            else
            {
                rotate_right(root);
            }
            root->update_height();
            root->_left->update_height();
            root->_right->update_height();
        }
        return root;

    }
}
template <typename T>
bool tree_insert(tree_node<T>* &root, T insert_me)
{
    const bool debug = false;
    bool success = true;
    if(root==NULL)
    {
        tree_node<T> *temp = new tree_node<T>(insert_me);
        root = temp;
        success = false;
    }
    else
    {
        if(insert_me<root->_item)
        {
            tree_insert(root->_left,insert_me);
            if(abs(root->balance_factor())==2)
                rotate(root);
            root->update_height();
        }
        else if(insert_me>root->_item)
        {
            tree_insert(root->_right,insert_me);
            if(abs(root->balance_factor())==2)
                rotate(root);
            root->update_height();
        }
        else{
            if (debug)
                cout<<"tree_insert: duplicate entry found. returning"<<endl;
        }
    }
    return success;
}

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target)
{
    if(root==NULL)
        return NULL;
    if(root->_item==target)
    {
        return root;
    }
    if(target>root->_item)
    {
        return tree_search(root->_right,target);
    }
    if(target<root->_item)
    {
        return tree_search(root->_left,target);
    }
}
template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr)
{
    if(root==NULL)
    {
        found_ptr=NULL;
        return false;
    }
    if(root->_item==target)
    {
        found_ptr=root;
        return true;
    }
    if(target>root->_item)
        return tree_search(root->_right,target,found_ptr);
    else
        return tree_search(root->_left,target,found_ptr);
}

template<typename T>
void tree_print(tree_node<T>* root, int level=0, ostream& outs=cout)
{
    if(root==NULL)
        return;
    else
    {
        tree_print(root->_right,level+1);
        outs<<Level(level);
        outs<<root->_item<<endl;
        tree_print(root->_left,level+1);
    }
}

template<typename T>       //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int level=0, ostream& outs=cout)
{
    if(root== NULL)
        return;
    tree_print_debug(root->_right,level+1);
    outs<<Level(level);
    outs<<root->_item<<"[H: "<<root->_height<<"]";
    outs<<"|B: "<<root->balance_factor()<<"|"<<endl;
    tree_print_debug(root->_left,level+1);
}

template <typename T>
void tree_remove_max(tree_node<T>* &root, T& max_value)
{

    tree_node<T> *temp=NULL;

    if(root->_right==NULL)
    {
        max_value = root->_item;
        temp = root;
        root = root->_left;
        delete temp;
        temp = NULL;
    }
    else
    {
        tree_remove_max(root->_right,max_value);
        root->update_height();
    }
}

template <typename T>       //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target)
{
    if(root != NULL)
    {
        if(target<root->_item)
        {
            tree_erase(root->_left,target);
            root->update_height();
        }
        else if(target>root->_item)
        {
            tree_erase(root->_right,target);
            root->update_height();
        }
        else
        {
            if(root->_right&&root->_left==NULL)
            {
                tree_node<T> *temp = root;
                root = root->_right;
                delete temp;
                temp = NULL;
            }
            else if(root->_right==NULL&&root->_left)
            {
                tree_node<T> *temp = root;
                root = root->_left;
                delete temp;
                temp = NULL;
            }
            else if(root->_left!=NULL&&root->_right!=NULL)
            {
                tree_remove_max(root->_left,root->_item);
            }
            else
            {
                delete root;
                root = NULL;
            }
            if(root)
            {
                rotate(root);
                root->update_height();
                if(abs(root->balance_factor()==2))
                    rotate(root);
            }
            return true;
        }
    }
    else
        return false;
}
template <typename T>       //clear the tree
void tree_clear(tree_node<T>* &root)
{
    if(root)
    {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = NULL;
    }
}

template <typename T>       //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root)
{
    if(root == NULL)
        return NULL;
    else
    {
        tree_node<T> *temp = new tree_node<T>(root->_item);
        temp->_left = tree_copy(root->_left);
        temp->_right = tree_copy(root->_right);
        temp->update_height();
        return temp;
    }
}

template <typename T>       //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src)
{
    if(src)
    {
        tree_insert(dest,src->_item);
        tree_add(dest,src->_left);
        tree_add(dest,src->_right);
    }
}

template <typename T>// sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size)
{
    int first =0;
    int last = size-1;
    int mid = (first+last)/2;
    tree_node<T> *root = NULL;
    const T* temp = a +mid +1;
    tree_insert(root, a[mid]);

    if((size-1)/2>0)
    {
        root->_left= tree_from_sorted_list(a, (size-1)/2);
        root->update_height();
    }
    if(size/2>0)
    {
        root->_right=tree_from_sorted_list(temp,size/2);
        root->update_height();
    }

    return root;
}

#endif // TREENODEFORAVL_H
