#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "treenodeforavl.h"

using namespace std;

template <typename T>
class avl{
public:
    avl();
    avl(const T* sorted_list, int size=-1);

    avl(const avl<T>& copy_me);
    avl<T>& operator =(const avl<T>& rhs);
    ~avl();

    bool insert(const T& insert_me);
    bool erase(const T& target);
    bool search(const T& target, tree_node<T>* & found_ptr);
    void clearall();
    friend ostream& operator <<(ostream& outs, const avl<T>& tree)
    {
        tree_print_debug(tree.root,0,outs);
        return outs;
    }
    avl<T>& operator +=(const avl<T>& rhs);
private:
    tree_node<T>* root;
};

template<typename T>
void avl<T>::clearall()
{
    tree_clear(root);
}

template<typename T>
avl<T>& avl<T>:: operator +=(const avl<T>& rhs)
{
    tree_add(root,rhs.root);
}

template<typename T>
bool avl<T>::search(const T& target, tree_node<T>* & found_ptr)
{
    return tree_search(root,target,found_ptr);
}

template<typename T>
bool avl<T>::erase(const T& target)
{
    return tree_erase(root, target);
}

template<typename T>
bool avl<T>::insert(const T& insert_me)
{
    return tree_insert(root, insert_me);
}

template<typename T>
avl<T>::avl()
{
    root = NULL;
}
template<typename T>
avl<T>::avl(const T* sorted_list, int size)
{
    root = tree_from_sorted_list(sorted_list,size);
}
template<typename T>
avl<T>::avl(const avl<T>& copy_me)
{
    root = tree_copy(copy_me);
}

template<typename T>
avl<T>::~avl()
{
    tree_clear(root);
}
template<typename T>
avl<T>&avl<T>:: operator =(const avl<T>& rhs)
{
    if(this == &rhs)
        return *this;
    tree_clear(root);
    root = tree_copy(rhs.root);
    return *this;
}
#endif // AVL_H
