#include<iostream>
#include<cstdio>
using namespace std; 
 
const int RED = 0;
const int BLACK = 1;
typedef struct RBTNode RBT;
typedef struct RBTNode * Position;
typedef struct RBTNode * SearchTree;
//红黑树数据结构
struct  RBTNode{
    int key;
    int color;
    Position parent, left, right;
}; 
 
static RBT sentinel = {0, 1, 0, 0, 0}; //哨兵
#define NIL &sentinel 
 
/*红黑树的查找，最小，最大，前驱，后继操作和二叉查找树
几乎是一模一样的，直接复制过来，改了下名字和NULL
*/
 
//红黑树查找
Position RBTreeSearch(SearchTree tree, int k) {
    if (tree == NIL || k == tree->key) {
        return tree;
    }
    if (k < tree->key) {
        return RBTreeSearch(tree->left, k);
    } else {
        return RBTreeSearch(tree->right, k);
    }
} 
 
//返回二叉树最左边值（即最小值）的指针，
Position RBTreeMinimim(SearchTree tree) {
    while (tree->left != NIL) {
        tree = tree->left;
    }
    return tree;
}  
 
//返回二叉树最右边值（即最大值）的指针
Position RBTreeMaximum(SearchTree tree) {
    while (tree->right != NIL) {
        tree = tree->right;
    }
    return tree;
} 
 
//中序遍历下找它的后继
Position RBTreeSuccessor(Position x) {
    if (x->right != NIL) {
        return RBTreeMinimim(x->right);
    }
    Position y = x->parent;
    while (y != NIL && x == y-> right) {
        x = y;
        y = y->parent;
    }
    return y;
}  
 
//左旋，旋转只有指针被改变，其他域保持不变
void LeftRotate(SearchTree &tree, Position x) {
    Position y = x->right;
    //set y's z左子树 into x's 右子树
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    } 
 
    //下面代码修改x的父节点与y的关系
    y->parent = x->parent;
    if (x->parent == NIL) {//如果x是根节点
        tree = y;
    } else if (x == x->parent->left) {//如果x不是根节点
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    //修改x与y的关系
    y->left = x;
    x->parent = y;
} 
 
//右旋，只要把左旋里的程序对称就行了
void RightRotate(SearchTree &tree, Position x) {
    Position y = x->left;
    //set y's 右子树 into x's 左子树
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    } 
 
    //下面代码修改x的父节点与y的关系
    y->parent = x->parent;
    if (x->parent == NIL) {//如果x是根节点
        tree = y;
    } else if (x == x->parent->left) {//如果x不是根节点
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    //修改x与y的关系
    y->right = x;
    x->parent = y;
}    
 
//插入的FixUp
void RBTreeInsertFixUp(SearchTree &tree, Position z) {
    while (z->parent->color == RED) {
        if (z->parent = z->parent->parent->left) {//y在右边
            Position y = z->parent->parent->right;//设定y
            if (y->color == RED) {//Case1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent ->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {//Case2
                    z = z->parent;//旋转会改变新结点的位置，所以要调整
                    LeftRotate(tree, z); //case2->case3
                }
                z->parent->color = BLACK;//Case3
                z->parent->parent->color = RED;
                RightRotate(tree, z->parent->parent);
            }
        } else {//y在左边
            Position y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent ->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {//Case2
                    z = z->parent;//旋转会改变新结点的位置，所以要调整
                    RightRotate(tree, z); //case2->case3
                }
                z->parent->color = BLACK;//Case3
                z->parent->parent->color = RED;
                LeftRotate(tree, z->parent->parent);
            }
        }//if-else
    }//while
    tree->color = BLACK;
}//RBInsertFixUp 
 
//插入操作
void RBTreeInsert(SearchTree &tree, int k) {
    Position y = NIL;
    Position x = tree;
    Position z = new RBT;
    z->key = k;
    z->parent = z->left = z->right = NIL;//初始化  
 
     //找到要插入的位置
    while (x != NIL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    //和周边点增加关系
    z->parent = y;
    if (y == NIL) {
        tree = z;
    } else {
        if (k < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }
    z->left = z->right = NIL;
    z->color = RED;
    RBTreeInsertFixUp(tree, z);
}    
 
//删除FixUp
void RBTreeDeleteFixUp(SearchTree &tree, Position x) {
    while (x != tree && x->color == BLACK) {
        if (x == x->parent->left) {
            Position w = x->parent->right;
            if (w->color == RED) {//Case1
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(tree, x->parent);
                w = x->parent->right;
            }
            //____________Case2__________________
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->right->color == BLACK) {//Case3->Case4
                w->left->color = BLACK;
                w->color = RED;
                RightRotate(tree, w);
                w = x->parent->right;
            } else {//Case4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(tree, x->parent);
                x = tree;
            }
        } else {//if-else完全对称
            Position w = x->parent->left;
            if (w->color == RED) {//Case1
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(tree, x->parent);
                w = x->parent->left;
            }
            //____________Case2__________________
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->left->color == BLACK) {//Case3->Case4
                w->left->color = BLACK;
                w->color = RED;
                LeftRotate(tree, w);
                w = x->parent->left;
            } else {//Case4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(tree, x->parent);
                x = tree;
            }
        }
    }
    x->color = BLACK;
} 
 
//删除操作 ,可以参考二叉查找树中的注释
Position RBTreeDelete(SearchTree tree, Position z) {
    Position x, y;  
 
    if (z->left == NIL || z->right == NIL) {
        y = z;
    } else {
        y = RBTreeSuccessor(z);
    }  
 
    if (y->left != NIL) {
        x = y->left;
    } else {
        x = y->right;
    }  
 
    //去掉了判断条件
    x->parent = y->parent;  
 
    if (y->parent == NIL) {
        tree = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }  
 
    if (y != z) {
        z->key = y->key;
    }  
 
    if (y->color == BLACK) {
        RBTreeDeleteFixUp(tree, x);
    }
    return y;
} 
 
//中序遍历，输出颜色
void InOrderTraverse(SearchTree tree) {
    if (tree != NIL) {
        InOrderTraverse(tree->left);
        printf("\nkey = %2d ：color = ", tree->key);
        if (tree->color == 0) {
            printf("RED  " );
        } else {
            printf("BLACK" );
        } 
 
        printf("  parent = %2d ", tree->parent->key);
        if (tree->left != NIL) {
            printf(" left  = %2d ", tree->left->key);
        }
        if (tree->right != NIL) {
            printf(" right = %2d", tree->right->key);
        }
        InOrderTraverse(tree->right);
    }
}         
 
int main() {
    SearchTree tree = NIL;
    //构造文章最开头的红黑树
    RBTreeInsert(tree, 26), RBTreeInsert(tree, 17);
    RBTreeInsert(tree, 41), RBTreeInsert(tree, 14);
    RBTreeInsert(tree, 21), RBTreeInsert(tree, 30);
    RBTreeInsert(tree, 47), RBTreeInsert(tree, 10);
    RBTreeInsert(tree, 16), RBTreeInsert(tree, 19);
    RBTreeInsert(tree, 23), RBTreeInsert(tree, 28);
    RBTreeInsert(tree, 38), RBTreeInsert(tree, 7);
    RBTreeInsert(tree, 12), RBTreeInsert(tree, 15);
    RBTreeInsert(tree, 20), RBTreeInsert(tree, 35);
    RBTreeInsert(tree, 39), RBTreeInsert(tree, 3); 
 
    puts("中序遍历:");
    InOrderTraverse(tree);  
 
    Position locate28 = RBTreeSearch(tree, 28);
    printf("\n\n28的后继是：");
    printf("%d\n\n", RBTreeSuccessor(locate28) -> key);
    puts("删除28后的中序遍历: ");
    RBTreeDelete(tree, locate28);
    InOrderTraverse(tree);  
 
    return 0;
}
/*
运行结果：
___________________________________________________________
中序遍历:
 
key =  3 ：color = RED    parent =  7
key =  7 ：color = BLACK  parent = 10  left  =  3
key = 10 ：color = RED    parent = 14  left  =  7  right = 12
key = 12 ：color = BLACK  parent = 10
key = 14 ：color = BLACK  parent = 17  left  = 10  right = 16
key = 15 ：color = RED    parent = 16
key = 16 ：color = BLACK  parent = 14  left  = 15
key = 17 ：color = RED    parent = 26  left  = 14  right = 21
key = 19 ：color = BLACK  parent = 21  right = 20
key = 20 ：color = RED    parent = 19
key = 21 ：color = BLACK  parent = 17  left  = 19  right = 23
key = 23 ：color = BLACK  parent = 21
key = 26 ：color = BLACK  parent =  0  left  = 17  right = 41
key = 28 ：color = BLACK  parent = 30
key = 30 ：color = RED    parent = 41  left  = 28  right = 38
key = 35 ：color = RED    parent = 28
key = 38 ：color = BLACK  parent = 30  left  = 35  right = 39
key = 39 ：color = RED    parent = 38
key = 41 ：color = BLACK  parent = 26  left  = 30  right = 47
key = 47 ：color = BLACK  parent = 41
 
28的后继是：30
 
删除28后的中序遍历:
 
key =  3 ：color = RED    parent =  7
key =  7 ：color = BLACK  parent = 10  left  =  3
key = 10 ：color = RED    parent = 14  left  =  7  right = 12
key = 12 ：color = BLACK  parent = 10
key = 14 ：color = BLACK  parent = 17  left  = 10  right = 16
key = 15 ：color = RED    parent = 16
key = 16 ：color = BLACK  parent = 14  left  = 15
key = 17 ：color = RED    parent = 26  left  = 14  right = 21
key = 19 ：color = BLACK  parent = 21  right = 20
key = 20 ：color = RED    parent = 19
key = 21 ：color = BLACK  parent = 17  left  = 19  right = 23
key = 23 ：color = BLACK  parent = 21
key = 26 ：color = BLACK  parent =  0  left  = 17  right = 41
key = 30 ：color = BLACK  parent = 38  right = 35
key = 35 ：color = RED    parent = 30
key = 38 ：color = RED    parent = 41  left  = 30  right = 39
key = 39 ：color = BLACK  parent = 38
key = 41 ：color = BLACK  parent = 26  left  = 38  right = 47
key = 47 ：color = BLACK  parent = 41
PS：结合上边的图可知：程序运行结果正确
*/