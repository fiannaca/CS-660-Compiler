#ifndef _AVL_TREE_
#define _AVL_TREE_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include <list>

/**
 * Allows for variability in the number of children a given node in the tree can 
 * have
 */
#define CHILD_SIZE  2

/**
 * Enumeration for indicating the direction of the rotations on the AVL tree
 */
enum
{
    LEFT ,
    RIGHT
};

using namespace std;

/**
 * An implementation of a balanced binary tree called an AVL tree. This 
 * implementation assumes that the DataItem template class implements the 
 * operators < (less than), > (greater than), == (equality), and << (insertion).
 */
template <class DataItem> 
class AVLTree
{
    /**
     * A node which composes the DataItem template class with pointers to its 
     * children nodes in the AVL tree and the balance factor at the current 
     * node.
     */
    struct Node
    { 
        DataItem data; 
        Node  *children[CHILD_SIZE];
        int balanceFactor;
        
        public:
        
            Node()
            {
                children[LEFT] = NULL;
                children[RIGHT] = NULL;
                balanceFactor = 0 ;
            }
    };
    
    Node *root; /**< Root node of the AVL tree */
    list<DataItem> elements;   
    private:
        /**
         * Performs a single rotation in the indicated direction and about the
         * specified node
         *
         * @param rootNode Node to rotate about
         * @param direction the direction in which to rotate
         *
         * @return The height change (either 1 or 0)
         */
        int SingleRotate(Node* &rootNode, int direction)
        { 
            int opposite_dir = !direction;
            int heightChange;
            Node *save = rootNode;
            heightChange  = ( rootNode->children[opposite_dir]->balanceFactor == 0 ) ?  0 : 1 ;
            rootNode = save->children[opposite_dir];
            save->children[opposite_dir] = rootNode->children[direction];
            rootNode->children[direction] = save;
            save->balanceFactor = - ( ( direction == LEFT) ? --(rootNode->balanceFactor) : ++(rootNode->balanceFactor));

            return heightChange;
        }
        
        /**
         * Performs a double rotation in the indicated direction and about the
         * specified node
         *
         * @param rootNode Node to rotate about
         * @param direction the direction in which to rotate
         * @see SingleRotate()
         *
         * @return The height change (always 1)
         */
        int DoubleRotate(Node  *&rootNode , int direction)
        {
            int   opposite_dir = !direction;
            Node * save = rootNode;
            Node * save_child = rootNode->children[opposite_dir];

            rootNode = save->children[opposite_dir]->children[direction];   
            
            save->children[opposite_dir] = rootNode->children[direction];
            rootNode->children[direction] = save;


            save_child->children[direction] = rootNode->children[opposite_dir];
            rootNode->children[opposite_dir] = save_child;

            rootNode->children[LEFT]->balanceFactor  = -max(rootNode->balanceFactor, 0);
            rootNode->children[RIGHT]->balanceFactor = -min(rootNode->balanceFactor, 0);
            rootNode->balanceFactor = 0;
            


            return  1;    
        }
        
        /**
         * Balances the tree beginning at the provided root node using single 
         * and double rotations
         *
         * @param rootNode The root node of a tree to balance (not necessarily 
                           the root of the entire AVL tree)
         * @see SingleRotate()
         * @see DoubleRotate()
         *
         * @return The height change
         */
        int  Balance(Node *&rootNode)
        {
            int  heightChange = 0;
            
            if (rootNode->balanceFactor  < -1 ) 
            {
                if (rootNode->children[LEFT]->balanceFactor  ==  1 ) 
                {
                    heightChange = DoubleRotate(rootNode, RIGHT);
                } 
                else 
                {
                    heightChange = SingleRotate(rootNode, RIGHT);
                }
            } 
            else if (rootNode->balanceFactor> 1 ) 
            {
                if (rootNode->children[RIGHT]->balanceFactor  ==  -1) 
                {
                    heightChange = DoubleRotate(rootNode, LEFT);
                } 
                else 
                {
                    heightChange = SingleRotate(rootNode, LEFT);
                }
            }         

            return  heightChange;
        }
        
        /**
         * Outputs the AVL tree to stdout using the << operator of the provided
         * DataItem template type
         *
         * @param node The current node to print and recursively print the 
         *             children of
         */
        void Dump(Node *node)
        {
            if( node != NULL )
            {
                cout << node->data; 
                Dump(node->children[LEFT]);
                Dump(node->children[RIGHT]);  
            }
        }
	
	list<DataItem> GetElements(Node *node)
	{
	    
	    if( node != NULL )
            {
                cout<< node->data;
		elements.push_back(node->data); 
                GetElements(node->children[LEFT]);
                GetElements(node->children[RIGHT]);  
            }
	    return elements;
	}
         
    public:
        /**
         * Default AVL tree constructor. Only sets the root of the tree to NULL 
         * since there are no nodes in the initial tree.
         */
        AVLTree()
        {
            this->root = NULL;
        }	

        /**
         * Inserts a new node into the tree
         * 
         * @param item The new data to create a node for and to insert into the
         *             tree
         */
        void Insert( DataItem item )
        {
            int change;
            Insert(item,root,change);
        }

        /**
         * Inserts a new node into the tree
         * 
         * @param item The new data to create a node for and to insert into the
         *             tree
         * @param node The root of the tree to insert the node into
         * @param change Boolean indicating if the tree has been changed or not
         * @see Insert(DataItem)
         */
        void Insert(DataItem item, Node* &node, int &change)
        {
            int direction = 0;  
            int increase;
            int result = 0;

            if (node == NULL) 
            {
                node = new Node();
                node->data = item;
                change = 1;
                return; 
            }
            
            direction = ( item >  root->data ) ? LEFT : RIGHT; 
            
            if ( node->data < item )
            {
                result = -1 ; 
            }   
            else if ( node->data == item )
            {
                result = 0 ;
            }
            else 
            {
                result = 1;
            }
            
            if ( !(node->data == item) ) 
            {
                Insert(item, node->children[direction], change);
                increase = result * change;                       
            } 
            else 
            {  
                return;
            }

            node->balanceFactor += increase;     
            
            change =  (increase && root->balanceFactor)? (1 - Balance(node)) : 0;
        }

        /**
         * Searches the AVL tree for a given DataItem.
         *
         * @param itemToFind The item to search for
         * 
         * @return NULL if the item wasn't found, or a pointer to the item data
         *         in the tree otherwise
         */
        DataItem* Fetch(DataItem itemToFind)
        {
            DataItem *item = NULL;
            Node *rootNode = this->root ;

            while (rootNode != NULL)
            {
                if ( itemToFind < rootNode->data )
                {
                    rootNode = rootNode->children[RIGHT];
                }
                else if ( itemToFind > rootNode->data )
                {
                    rootNode = rootNode->children[LEFT];
                }
                else if ( itemToFind == rootNode->data )
                {
                    item = &(rootNode->data);
                    return item;
                }
            }
            
            return item;
        }

        /**
         * Searches the AVL tree for a given DataItem. Returns a pointer to the
         * node containing the data rather than the a pointer to the actual data.
         *
         * @param itemToFind The item to search for
         * 
         * @return NULL if the item wasn't found, or a pointer to the node
         *         which contains the given data item otherwise
         */
        Node* Find(DataItem itemToFind)
        {
            Node *rootNode = this->root ;

            while (  rootNode != NULL )
            {
                if ( itemToFind < rootNode->data  )
                {
                    rootNode = rootNode->children[RIGHT];
                }
                else if ( itemToFind > rootNode->data )
                {
                    rootNode = rootNode->children[LEFT];
                }
                else if ( itemToFind == rootNode->data )
                {
                    return rootNode;
                }
            }
            
            return rootNode;
        }
        
        /**
         * Checks if the given data item is in the tree or not
         *
         * @param itemToFind A data item to search for
         *
         * @return TRUE if the item is in the tree, FALSE otherwise
         */
        bool Contains( DataItem itemToFind)
        {
            return ( Find(itemToFind) != NULL );
        }  	 

        /**
         * Outputs the AVL tree to stdout recursively using the insertion 
         * operator for the DataItem template type
         */
        void Dump()
        {
            Dump(this->root); 
        }    
	
	list<DataItem> GetElements()
	{
	    elements.clear();
	    return GetElements(this->root);
	
	    
	}	           	 
};

#endif 
