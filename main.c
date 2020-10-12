#include <stdlib.h>
#include <time.h>

#include "RedBlackTree.h"

#define N 15

int main(void){
    /*Create the Red Black tree*/
    RBTree tree = RBT_create();

    srand(time(NULL));

    /*Insert random integers*/
    for(int i = 0; i < N; i++)
        RBT_insert(tree, (rand() % 50));

    RBT_print(tree);

    return 0;
}