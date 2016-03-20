#include<iostream>
#include<cstdio>
using namespace std;
 
typedef struct BSTNode BST;//BST代表结点
//BSTNode * == Position; Position代表指针
typedef struct BSTNode * Position;
//BSTNode * == SearchTree; SearchTree代表二叉树的地址
typedef struct BSTNode * SearchTree;
 
//二叉树数据结构
struct BSTNode {
    int key;
    Position parent, left, right;
}; 
 
//先序遍历(递归版)
void PreOrderTraverse(SearchTree tree) {
    if (tree != NULL) {
        printf("%d ", tree->key);
        PreOrderTraverse(tree->left);
        PreOrderTraverse(tree->right);
    }
}
 
//中序遍历(递归版)
void InOrderTraverse(SearchTree tree) {
    if (tree != NULL) {
        InOrderTraverse(tree->left);
        printf("%d ", tree->key);
        InOrderTraverse(tree->right);
    }
}
 
//后序遍历(递归版)
void PostOrderTraverse(SearchTree tree) {
    if (tree != NULL) {
        if (tree->left)
        PostOrderTraverse(tree->left);
        PostOrderTraverse(tree->right);
        printf("%d ", tree->key);
    }
}
 
//Search,查找操作(递归版本),递归版本简洁，易于理解，但效率不如非递归
Position BSTreeSearch(SearchTree tree, int k) {
    if (tree == NULL || k == tree->key) {
        return tree;
    }
    if (k < tree->key) {
        return BSTreeSearch(tree->left, k);
    } else {
        return BSTreeSearch(tree->right, k);
    }
}
 
// Search操作，非递归版本
Position BSTreeSearch1(SearchTree tree, int k) {
    while (tree != NULL && k != tree->key) {
        if (k < tree->key) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return tree;
}
 
//返回二叉树最左边值（即最小值）的指针，
Position BSTreeMinimim(SearchTree tree) {
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}
 
//返回二叉树最右边值（即最大值）的指针
Position BSTreeMaximum(SearchTree tree) {
    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}
 
//中序遍历下找它的后继
Position BSTreeSuccessor(Position x) {
    if (x->right != NULL) {
        return BSTreeMinimim(x->right);
    }
    Position y = x->parent;
    while (y != NULL && x == y-> right) {
        x = y;
        y = y->parent;
    }
    return y;
}
 
//找前驱是一样的道理，把right改为left就可以了
 Position BSTreePredecessor(Position x) {
    if (x->left != NULL) {
        return BSTreeMaximum(x->left);
    }
    Position y = x->parent;
    while (y != NULL && x == y-> left) {
        x = y;
        y = y->parent;
    }
    return y;
}
 
//插入操作
void BSTreeInsert(SearchTree &tree, int k) {
    Position y = NULL;
    Position x = tree;
    Position z = new BST;
    z->key = k;
    z->parent = z->left = z->right = NULL;//初始化
 
     //找到要插入的位置
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    //和周边点增加关系
    z->parent = y;
    if (y == NULL) {
        tree = z;
    } else {
        if (k < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }
}
 
// 删除操作
Position  BSTreeDelete(SearchTree tree, Position z) {
    Position x, y;
    //下边if-else确定要删除的节点y
    if (z->left == NULL || z->right == NULL) {
        y = z;//如果z不是第三种情况，则要删除的结点就是z
    } else {//如果是第三种情况，则先删除z的后继
        y = BSTreeSuccessor(z);
    }
    //x为y的子女或NULL
    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }
    //通过修改y周边的关系，将y删除 
 
    //改变x的parent 是y的parent
    if (x != NULL) {
        x->parent = y->parent;
    }
    //上边的if第一种情况处理完毕
    //下边的if-elseif-else第二种情况处理完毕
    //y的parent的儿子是x，父子关系都修改，y即删除
    if (y->parent == NULL) {
        tree = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    //处理第三种情况，把y中的内容复制到z中
    if (y != z) {
        z->key = y->key;
    }
    return y;
}
 
int main() {
    SearchTree tree = NULL;
 
    //构造文章开头图中的二叉树
    BSTreeInsert(tree,15); BSTreeInsert(tree, 6);
    BSTreeInsert(tree,18); BSTreeInsert(tree, 3);
    BSTreeInsert(tree, 7); BSTreeInsert(tree, 17);
    BSTreeInsert(tree, 20); BSTreeInsert(tree, 2);
    BSTreeInsert(tree, 4);  BSTreeInsert(tree, 13);
    BSTreeInsert(tree, 9);
 
    puts("先序遍历:");
    PreOrderTraverse(tree);
 
    puts("\n\n中序遍历:");
    InOrderTraverse(tree);
 
    puts("\n\n后序遍历:");
    PostOrderTraverse(tree);
 
    printf("\n\n最小值是：%d\n", BSTreeMinimim(tree)->key);
    printf("\n最大值是；%d\n\n", BSTreeMaximum(tree)->key);
 
    Position locate13 = BSTreeSearch(tree, 13);
    printf("13的前驱是：");
    printf("%d\n\n", BSTreePredecessor(locate13) -> key);
    printf("13的后继是：");
    printf("%d\n\n", BSTreeSuccessor(locate13) -> key); 
 
    puts("删除13后的中序遍历: ");
    BSTreeDelete(tree, locate13);
    InOrderTraverse(tree);
 
    return 0;
}
/*
运行结果：(运行环境C-FREE5专业版)
______________________________
先序遍历:
15 6 3 2 4 7 13 9 18 17 20
 
中序遍历:
2 3 4 6 7 9 13 15 17 18 20
 
后序遍历:
2 4 3 9 13 7 6 17 20 18 15
 
最小值是：2
 
最大值是；20
 
13的前驱是：9
 
13的后继是：15
 
删除13后的中序遍历:
2 3 4 6 7 9 15 17 18 20
*/