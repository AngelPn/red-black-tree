#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "RedBlackTree.h"

struct RB_tree{
    int size;
    RBTreeNode root;
};

struct RB_tree_node{
    int item;
    char colour;
    RBTreeNode parent;
    RBTreeNode left;
    RBTreeNode right;
};

RBTree RBT_create(){
    RBTree tree = malloc(sizeof(struct RB_tree));
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

int BTIsNil(RBTreeNode node){
	if (node == NULL) return 1;
	else return 0;
}

int RBT_size(RBTree tree){
    return tree->size;
}

int maxDepth(RBTree tree, RBTreeNode node){
    if(RBTIsNil(node)) return 0;
	else{
		int LeftDepth= maxDepth(tree, node->left); /*Find the height of left subtree recursively*/
		int RightDepth= maxDepth(tree, node->right); /*Find the height od right subtree recursively*/
		/*Return the highest height*/
		if (LeftDepth>RightDepth) return LeftDepth+1; 
		else return RightDepth+1;
	}
}

int RBT_height(RBTree tree){
    if(RBTIsNil(tree->root) ){
		printf("Error! The tree is empty\n");
		exit(EXIT_FAILURE);
	}
	else return maxDepth(tree, tree->root);
}

RBTreeNode RBT_root(RBTree tree){
    return tree->root;
}

RBTreeNode RBT_parent(RBTreeNode node){
    return node->parent;
}

RBTreeNode RBT_childleft(RBTreeNode node){
    return node->left;
}

RBTreeNode RBT_childright(RBTreeNode node){
    return node->right;
}

int RBT_get_item(RBTreeNode node){
    return node->item;
}

void RBT_set_item(RBTree tree, RBTreeNode node, int item){
    node->item = item;
}

void RBT_insert_root(RBTree tree, int item){
    if (!RBTIsNil(tree->root)){
		printf("Error! Root is not empty");
		return;
	}
	(tree->size)++; /*Increase the size*/
	tree->root = malloc(sizeof(struct RB_tree_node)); /*Allocate memory for a new node*/
	
    tree->root->item = item;
    tree->root->colour = 'b';
    //Initialize children
    tree->root->parent = NULL;
	tree->root->left=NULL;
	tree->root->right=NULL;
}

RBTreeNode RBT_insert_left(RBTree tree, RBTreeNode node, int item, char colour){
    if (!RBTIsNil(node->left)){
		printf("Error! ChildLeft of the node is not empty\n");
		return;
	}
	(tree->size)++; /*Increase the size*/
	node->left = malloc(sizeof(struct RB_tree_node)); /*Allocate memory for a new node*/
	node->left->item = item;
    node->left->colour = colour;
	node->left->parent = node;
	node->left->left=NULL; /*Initialize children*/
	node->left->right=NULL;
    return node->left;
}

RBTreeNode RBT_insert_right(RBTree tree, RBTreeNode node, int item, char colour){
    if (!RBTIsNil(node->right)){
		printf("Error! ChildRight of the node is not empty\n");
		return;
	}
	(tree->size)++; /*Increase the size*/
	node->right = malloc(sizeof(struct RB_tree_node)); /*Allocate memory for a new node*/
	node->right->item = item;
    node->right->colour = colour;
	node->right->parent = node;
	node->right->left=NULL; /*Initialize children*/
	node->right->right=NULL;
    return node->right;
}

void left_rotate(RBTree tree, RBTreeNode node){
    /*Turn y’s left subtree into nodes’s right subtree*/
    RBTreeNode y = RBT_childright(node);
    node->right = y->left;

    /*Update y's subtree parent pointer*/
    if(!RBTisNil(y->left->parent))
        y->left->parent = node;
    
    y->parent = node->parent;

    /*Turn node's parent into y's parent*/
    if(BTisNil(RBT_parent(node)))
        tree->root = y;
    else if(node == node->parent->left)
        node->parent->left = y;
    else if(node == node->parent->right)
        node->parent->right = y;
    
    /*Turn y into node's new parent*/
    y->left = node;
    node->parent = y;

}

void right_rotate(RBTree tree, RBTreeNode node){
    /*Turn y’s left subtree into node’s right subtree*/
    RBTreeNode y = RBT_childleft(node);
    node->left = y->right;

    /*Update y's subtree parent pointer*/
    if(!RBTisNil(y->right->parent))
        y->right->parent = node;
    
    y->parent = node->parent;

    /*Turn node's parent into y's parent*/
    if(BTisNil(RBT_parent(node)))
        tree->root = y;
    else if(node == node->parent->left)
        node->parent->left = y;
    else if(node == node->parent->right)
        node->parent->right = y;
    
    /*Turn y into node's new parent*/
    y->right = node;
    node->parent = y;
}

void RBT_insert_fixup(RBTree tree, RBTreeNode node){

    /*Make sure node is not root, node's grandparent is not NULL and node's parent is RED*/
    while(node != RBT_root(tree) && RBT_parent(node->parent) != NULL && RBT_parent(node)->colour == 'r'){
        
        /*Find node's uncle*/
        RBTreeNode uncle = NULL;
        if(RBT_parent(node)->item == RBT_parent(node)->parent->left->item)
            uncle = RBT_parent(node)->parent->right;
        else
            uncle = RBT_parent(node)->parent->left;

        /*If uncle's colour is RED*/
        if(uncle->colour == 'r'){
            /*Change colour of uncle and parent as BLACK and colour of grand parent as RED*/
            RBT_parent(node)->colour = 'b';
            uncle->colour = 'b';
            RBT_parent(node)->parent->colour = 'r';
            /*Change node = node’s grandparent*/
            node = RBT_parent(node)->parent;
        }
        /*If uncle's colour is BLACK*/
        else{
            RBTreeNode parent = RBT_parent(node);
            RBTreeNode grand_parent = RBT_parent(parent);
            /*Left Left Case*/
            if(node == RBT_parent(uncle)->left->left){
                char c = parent->colour;
                parent->colour = grand_parent->colour;
                grand_parent->colour = c;
                right_rotate(tree, grand_parent);
            }
            /*Left Right Case*/
            else if(node == RBT_parent(uncle)->left->right){
                char c = node->colour;
                node->colour = grand_parent->colour;
                grand_parent->colour = c;
                left_rotate(tree, parent);
                right_rotate(tree, grand_parent);
            }
            /*Right Right Case*/
            else if(node == RBT_parent(uncle)->right->right){
                char c = parent->colour;
                parent->colour = grand_parent->colour;
                grand_parent->colour = c;
                left_rotate(tree, grand_parent);
            }
            /*Right Left Case*/
            else if(node == RBT_parent(uncle)->right->left){
                char c = node->colour;
                node->colour = grand_parent->colour;
                grand_parent->colour = c;
                right_rotate(tree, parent);
                left_rotate(tree, grand_parent);
            }
        }
    }
    RBT_root(tree)->colour = 'b';
}

void RBT_insert(RBTree tree, int item){
    /*If root is empty, insert root*/
    if(RBTIsNil(RBT_root(tree))){
        RBT_insert_root(tree, item);
    }
    else{
        /*Find a leaf node*/
        RBTreeNode current = RBT_root(tree);
        RBTreeNode leaf_node = NULL;
        while(current != NULL){
            leaf_node = current;
            if(item < current->item)
                current = current->left;
            else
                current = current->right;
        }

        /*The new node is added as a child of the leaf node*/
        RBTreeNode new_node = NULL;
        if(item > leaf_node->item)
            new_node = RBT_insert_right(tree, leaf_node, item, 'r');
        else
            new_node = RBT_insert_left(tree, leaf_node, item, 'r');

        /*Do following if color of new node's parent is not BLACK and new node is not root*/
        RBT_insert_fixup(tree, new_node);
    }
}

void RBT_remove(RBTree tree, RBTreeNode node){
    if(!RBTIsNil(node->left) && !RBTIsNil(node->right)){
        printf("Error! The node can't be removed because it has two children\n");
        return;
    }
    else{

    }
}

void RBT_traverse_preorder(RBTree tree, RBTreeNode node, RBTreeVisitFunc visit){
    if(node!= NULL){
        visit(tree, node);
        RBT_traverse_preorder(tree, node->left, visit);
        RBT_traverse_preorder(tree, node->right, visit);
    }
}

void RBT_preorder(RBTree tree, RBTreeVisitFunc visit){
    RBT_traverse_preorder(tree, BT_root(tree), visit);
}

void RBT_traverse_inorder(RBTree tree, RBTreeNode node, RBTreeVisitFunc visit){
    if(node!= NULL){
        RBT_traverse_inorder(tree, node->left, visit);
        visit(tree, node);
        RBT_traverse_inorder(tree, node->right, visit);
    }
}

void RBT_inorder(RBTree tree, RBTreeVisitFunc visit){
    RBT_traverse_inorder(tree, BT_root(tree), visit);
}

void RBT_traverse_postorder(RBTree tree, RBTreeNode node, RBTreeVisitFunc visit){
    if(node!= NULL){
        RBT_traverse_postorder(tree, node->left, visit);
        RBT_traverse_postorder(tree, node->right, visit);
        visit(tree, node);
    }
}

void RBT_postorder(RBTree tree, RBTreeVisitFunc visit){
    RBT_traverse_postorder(tree, BT_root(tree), visit);
}

void FreeNode(RBTree tree, RBTreeNode node){
	free(node);
}

void RBT_destroy(RBTree tree){
    RBT_postorder(tree, FreeNode);
}

void printFunc(RBTree tree, RBTreeNode node){
    if(node->colour == 'r')
        printf("\033%d\033[0m", node->item);
    else
        printf("%d", node->item);
}

void RBT_print(RBTree tree){
    RBT_inorder(tree, printFunc);
}