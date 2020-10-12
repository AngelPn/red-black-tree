#pragma once

// ADT Red-Black Tree

//struct RB_tree and struct RB_tree_node are incomplete structs
typedef struct RB_tree* RBTree;
typedef struct RB_tree_node* RBTreeNode;

typedef void (*RBTreeVisitFunc)(RBTree, RBTreeNode);

//Creates and returns a new RB Tree
RBTree RBT_create();

//Returns size and height of RB Tree
int RBT_size(RBTree tree); /*size is the number of nodes that has the RB tree*/
int RBT_heigth(RBTree tree);

int RBT_get_item(RBTreeNode node);
void RBT_set_item(RBTree tree, RBTreeNode node, int item);

void RBT_insert(RBTree tree, int item);
void RBT_remove(RBTree tree, RBTreeNode node);

//Traverse RB Tree
void RBT_preorder(RBTree tree, RBTreeVisitFunc visit);
void RBT_inorder(RBTree tree, RBTreeVisitFunc visit);
void RBT_postorder(RBTree tree, RBTreeVisitFunc visit);

void RBT_Destroy(RBTree tree);

void RBT_print(RBTree tree);