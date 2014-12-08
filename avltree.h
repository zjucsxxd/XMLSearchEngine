/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 11/12/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <fstream>
using namespace std;

template <typename type> class AVLTree
{
public:
    AVLTree() : root(nullptr) {}

    AVLTree(const AVLTree& rhs) : root(nullptr)
    {
        *this = rhs;
    }

    ~AVLTree()
    {
        makeEmpty();
    }

    // insert the type variable into the tree by calling the private function
    void insert(type& x)
    {
        insertItem(x, root);
    }


    //Returns true if x is found in the tree
    type& find(type& x) const
    {
        return find(x, root);
    }


    // Test if the tree is logically empty.
    // Return true if empty, false otherwise.
    bool isEmpty() const
    {
        return root == nullptr;
    }


    // Print the tree contents in sorted order
    void printTree( ofstream& out ) const
    {
        if( isEmpty() )
            cout << "Empty tree" << endl;
        else
            printTree( out, root );
    }


    // Make the tree logically empty
    void makeEmpty()
    {
        makeEmpty(root);
    }

    // Deep copy
    const AVLTree& operator=(const AVLTree& rhs)
    {
        if(this != &rhs)
        {
            makeEmpty( );
            root = clone(rhs.root);
        }
        return *this;
    }

    bool isFound(type&x)
    {
        AVLNode* t = root;
        while(t != nullptr)
        {
            if (x < t->element)
                t = t->left;
            else if (t->element < x)
                t = t->right;
            else
                return true; // match
        }
        // if you have reached this point, the element is not in the tree
        return false;
    }

private:
    struct AVLNode
    {
        type element;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const type& theElement, AVLNode *lt, AVLNode *rt, int h = 0)
          : element(theElement), left(lt), right(rt), height(h) {}
    };

    AVLNode* root;


    void insertItem(type& x, AVLNode*& t)
    {
        if(t == nullptr)
            t = new AVLNode(x, nullptr, nullptr);
        else if(x < t->element)
        {
            insertItem(x, t->left);
            if( height(t->left) - height(t->right) == 2 ) // tree unbalanced
            {
                if(x < t->left->element)
                {
                    rotateWithLeftChild( t ); // case 1
                }
                else
                {
                    doubleWithLeftChild( t ); // case 2
                }
            }
        }
        else if(t->element < x)
        {
            insertItem(x, t->right);
            if( height(t->right) - height(t->left) == 2 ) // tree unbalanced
            {
                if(t->right->element < x)
                {
                    rotateWithRightChild( t ); // case 4
                }
                else
                {
                    doubleWithRightChild( t ); // case 3
                }
            }
        }
        else // Duplicate
        {
            t->element += x;
        }
        t->height = max( height(t->left), height(t->right) ) + 1;
    }


    type& find(type& x, AVLNode* t) const
    {
        while(t != nullptr)
        {
            if (x < t->element)
                t = t->left;
            else if (t->element < x)
                t = t->right;
            else
                return t->element; // match
        }
        // if you have reached this point, the element is not in the tree
        throw logic_error("Element not found in AVL Tree");
        // John: make a dummy object of null and check when you return it

        //return nullptr; // no match
        // USE TRY CATCH TO SEE IF THE ITEM IS IN THE TREE
    }


    void makeEmpty( AVLNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }


    void printTree(ofstream& out, AVLNode *t ) const
    {
        if( t != nullptr )
        {
            printTree(out, t->left );
            out << t->element << endl;
            printTree(out, t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AVLNode* clone( AVLNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AVLNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }

    int height(AVLNode* t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    // AVL MANIPULATIONS
    void rotateWithLeftChild(AVLNode*& k2) // CASE 1
    {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }


    void rotateWithRightChild(AVLNode*& k1) // CASE 4
    {
        AVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }


    void doubleWithLeftChild(AVLNode*& k3) // CASE 2
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }


    void doubleWithRightChild(AVLNode*& k1) // CASE 3
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }


};

#endif

// Code taken from:
// http://users.cis.fiu.edu/~weiss/dsaa_c++3/code/AvlTree.h
// accessed: November 12, 2014
