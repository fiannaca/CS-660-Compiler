#ifndef _AVL_TREE_
#define _AVL_TREE_
#include <iostream>
#include <cstdlib>
using namespace std;


/*
**********************************************************************
AVL Tree class :
     AVL tree is a balanced binary search tree . 
     Asssumtion , it is assumed that the
     class DataItem implements the operators < , > == 

***********************************************************************
*/

#define CHILD_SIZE  2 
enum
{
    LEFT ,
    RIGHT 

};
template <class DataItem> 
class AVLTree
{
	
	         
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
	   Node *root;  
       private:
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
                 void Dump(Node *node)
		 {
		     
   
                     if( node != NULL )
                     {                 
                        cout<< " \t" << node->data; 
                        Dump(node->children[LEFT]);
                        
                        Dump(node->children[RIGHT]);  
                     }
 
		   
		 }  		 
       public:
	         AVLTree()
		 {
                     
                     this->root = NULL;  

		 }	 
         void Insert( DataItem item )
         {
         	int change;
         	Insert(item,root,change);
         }
		  
		 void Insert( DataItem item ,Node* &node ,  int &change)
		 {
		        
                     int direction = 0 ;  
		     int increase;
		     int result = 0  ;
		     
		     if (node == NULL) 
		     {
                       node = new Node();
                       node->data = item;  
                       change = 1 ; 
                       return; 
                     }
                     direction = ( item >  root->data  ) ? LEFT  :RIGHT   ; 
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
                     if ( !( node->data == item )) 
		     {
        
                        Insert(item, node->children[direction], change);
                        increase = result * change;                       
		    } 
		    else 
		    {  
 			    return ;
                    }

                    node->balanceFactor += increase;     

 

                    change =  (increase && root->balanceFactor)? (1 - Balance(node)): 0;
                    
		     
	         }
		 
                 DataItem* Fetch( DataItem itemToFind)
                 {
                     DataItem *item = NULL;
                     Node *rootNode = this->root ;
		    
		    while (  rootNode != NULL )
		    {
		       if ( itemToFind < rootNode->data  )
		       {
		          rootNode = rootNode->children[RIGHT];
		       }
                       else if ( itemToFind > rootNode->data)
		       {
		          rootNode = rootNode->children[LEFT];
		       }
		       else if ( itemToFind == rootNode->data)
		       {
		          item = &(rootNode->data);
                          return item;
		       }
			     
		    }
		    return item;
  

                 }

	         Node* Find( DataItem itemToFind)
		 {
		    Node *rootNode = this->root ;
		    
		    while (  rootNode != NULL )
		    {
		       if ( itemToFind < rootNode->data  )
		       {
		          rootNode = rootNode->children[RIGHT];
		       }
                       else if ( itemToFind > rootNode->data)
		       {
		          rootNode = rootNode->children[LEFT];
		       }
		       else if ( itemToFind == rootNode->data)
		       {
		          return rootNode;
		       }
			     
		    }
		    return rootNode;
		 }
	     bool Contains( DataItem itemToFind)
		 {
		 	return ( Find(itemToFind) != NULL );
		 }  	 
		
		 
		 void Dump()
		 {
		    Dump(this->root); 
		 }
                  	           	 
};

#endif 
