#include<stdio.h>
#include<stdlib.h>


struct Node {
	
	int data ;
	struct Node *left ;
	struct Node *right ;
	int height ;
} ;

struct Node * newNode ( int data ) {
	    struct Node *node ;		
		node = (struct Node *) malloc ( sizeof( struct Node ) ) ;
		node->data   = data ;
		node->left   = NULL ;
		node->right  = NULL ;
		node->height = 1 ; 
	
	return node ;
}

int height( struct Node *node ) {
	
	if ( node == NULL )
	     return 0 ;
	
	return node->height ;
	
	
} 

int max ( int a , int b ) {
	
	return ( a > b ) ? a : b ;
	
}

int getBalance( struct Node * node ) {
	
	if ( node == NULL ) 
	    return 0 ;
	
	return height(node->left) - height(node->right) ;
	
}



struct Node * rightRotate( struct Node * node ) {
	
	struct Node *y = node->left;
	struct Node *T = y->right ;
	
	//perform rotation

	y->right = node ;
	node->left = T ; 
	
	// update heights 
	
	node->height = max(height(node->left), height(node->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
	
	return y ;
}


struct Node * leftRotate( struct Node * node ) {
	
	struct Node *y = node->right ;
	struct Node *T = y->left ;
	
	//perform rotation

	y->left = node ;
	node->right = T ; 
	
	// update heights 
	
	node->height = max(height(node->left), height(node->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
	
	return y ;
}


struct Node* insertNode( struct Node *node , int data ) {
	
	if ( node == NULL ) 
       return newNode( data ) ;
       
    if ( node->data > data )               //left travel
       node->left = insertNode( node->left, data ) ;    
    else if ( node->data < data )          // right travel
       node->right = insertNode( node->right , data ) ;
    else
       return node;
   
    // update the Height based on child 
    node->height = 1 + max(height(node->left), height(node->right)); 
    
	int balance = getBalance(node) ;
	
	 if (balance > 1 && data < node->left->data)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && data > node->left->data)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
	
}


void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
	
	struct Node *root = NULL ;
	
	root = insertNode(root,10) ;
	root = insertNode(root,20) ;
	root = insertNode(root,30) ;
	root = insertNode(root,40) ;
	root = insertNode(root,50) ;
	root = insertNode(root,25) ;
	
    preOrder(root) ;	
	return 0 ;
}
