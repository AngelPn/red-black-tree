#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "RedBlackTree.h"

#define N 15
#define M 50

int main(void){
    /*Create the Red Black tree*/
    RBTree tree = RBT_create();

    srand(time(NULL));
    unsigned char is_used[M] = {0}; //flags

    /*Insert random integers*/
    int i = N;
    while(i > 0){
        int num = (rand()%(M + 1));
        if(is_used[num]){
            i++;
            continue;
        }
        RBT_insert(tree, num);
        is_used[num] = 1;
        i--;
    }

    RBT_print(tree);
    printf("\n");

    return 0;
}