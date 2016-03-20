/*
The keyNum = 10
 (1)  (11)  (10)  (9)  (7)  (6)  (5)  (4)  (3)  (2)
 
抽取最小值1之后：
The keyNum = 9
 (2 (3)  (6 (7)  (9 (10) ) )  (4 (5) ) )  (11)
 
查找11成功,减小到8后：
The keyNum = 9
 (2 (3)  (6 (7)  (9 (10) ) )  (4 (5) ) )  (8)
 
删除7成功:
The keyNum = 8
 (2 (3)  (6 (9 (10) ) )  (4 (5) ) )  (8)
 
*/
//说明：
//代码中Fibonacci Heap 用变量heap表示
//结点通常用x，y等表示
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
using namespace std;
 
//斐波那契结点ADT
struct FibonacciHeapNode {
    int key;       //结点
    int degree;    //度
    FibonacciHeapNode * left;  //左兄弟
    FibonacciHeapNode * right; //右兄弟
    FibonacciHeapNode * parent; //父结点
    FibonacciHeapNode * child;  //第一个孩子结点
    bool marked;           //是否被删除第1个孩子
};
 
typedef FibonacciHeapNode FibNode;
 
//斐波那契堆ADT
struct FibonacciHeap {
    int keyNum;   //堆中结点个数
    FibonacciHeapNode * min;//最小堆，根结点
    int maxNumOfDegree;   //最大度
    FibonacciHeapNode * * cons;//指向最大度的内存区域
};
 
typedef FibonacciHeap FibHeap;
 
/*****************函数申明*************************/
//将x从双链表移除
inline void FibNodeRemove(FibNode * x);
 
//将x堆结点加入y结点之前(循环链表中)
void FibNodeAdd(FibNode * x, FibNode * y);
 
//初始化一个空的Fibonacci Heap
FibHeap * FibHeapMake() ;
 
//初始化结点x
FibNode * FibHeapNodeMake();
 
//堆结点x插入fibonacci heap中
void FibHeapInsert(FibHeap * heap, FibNode * x);
 
//将数组内的值插入Fibonacci Heap
void FibHeapInsertKeys(FibHeap * heap, int keys[], int keyNum);
 
//将值插入Fibonacci Heap
static void FibHeapInsertKey(FibHeap * heap, int key);
 
//抽取最小结点
FibNode * FibHeapExtractMin(FibHeap * heap);
 
//合并左右相同度数的二项树
void FibHeapConsolidate(FibHeap * heap);
 
//将x根结点链接到y根结点
void FibHeapLink(FibHeap * heap, FibNode * x, FibNode *y);
 
//开辟FibHeapConsolidate函数哈希所用空间
static void FibHeapConsMake(FibHeap * heap);
 
//将堆的最小结点移出，并指向其有兄弟
static FibNode *FibHeapMinRemove(FibHeap * heap);
 
//减小一个关键字
void FibHeapDecrease(FibHeap * heap, FibNode * x, int key);
 
//切断x与父节点y之间的链接，使x成为一个根
static void FibHeapCut(FibHeap * heap, FibNode * x, FibNode * y);
 
//级联剪切
static void FibHeapCascadingCut(FibHeap * heap, FibNode * y);
 
//修改度数
void renewDegree(FibNode * parent, int degree);
 
//删除结点
void FibHeapDelete(FibHeap * heap, FibNode * x);
 
//堆内搜索关键字
FibNode * FibHeapSearch(FibHeap * heap, int key);
 
//被FibHeapSearch调用
static FibNode * FibNodeSearch(FibNode * x, int key);
 
//销毁堆
void FibHeapDestory(FibHeap * heap);
 
//被FibHeapDestory调用
static void FibNodeDestory(FibNode * x);
 
//输出打印堆
static void FibHeapPrint(FibHeap * heap);
 
//被FibHeapPrint调用
static void FibNodePrint(FibNode * x);
/************************************************/
 
//将x从双链表移除
inline void FibNodeRemove(FibNode * x) {
    x->left->right = x->right;
    x->right->left = x->left;
}
 
/*
将x堆结点加入y结点之前(循环链表中)
    a …… y
    a …… x …… y
*/
inline void FibNodeAdd(FibNode * x, FibNode * y) {
    x->left = y->left;
    y->left->right = x;
    x->right = y;
    y->left = x;
}
 
//初始化一个空的Fibonacci Heap
FibHeap * FibHeapMake() {
    FibHeap * heap = NULL;
    heap = (FibHeap *) malloc(sizeof(FibHeap));
    if (NULL == heap) {
        puts("Out of Space!!");
        exit(1);
    }
    memset(heap, 0, sizeof(FibHeap));
    return heap;
}
 
//初始化结点x
FibNode * FibHeapNodeMake() {
    FibNode * x = NULL;
    x = (FibNode *) malloc(sizeof(FibNode));
    if (NULL == x) {
        puts("Out of Space!!");
        exit(1);
    }
    memset(x, 0, sizeof(FibNode));
    x->left = x->right = x;
    return x;
}
 
//堆结点x插入fibonacci heap中
void FibHeapInsert(FibHeap * heap, FibNode * x) {
    if (0 == heap->keyNum) {
        heap->min = x;
    } else {
        FibNodeAdd(x, heap->min);
        x->parent = NULL;
        if (x->key < heap->min->key) {
            heap->min = x;
        }
    }
    heap->keyNum++;
}
 
//将数组内的值插入Fibonacci Heap
void FibHeapInsertKeys(FibHeap * heap, int keys[], int keyNum) {
    for (int i = 0; i < keyNum; i++) {
        FibHeapInsertKey(heap, keys[i]);
    }
}
 
//将值插入Fibonacci Heap
static void FibHeapInsertKey(FibHeap * heap, int key) {
    FibNode * x = NULL;
    x = FibHeapNodeMake();
    x->key = key;
    FibHeapInsert(heap, x);
}
 
//抽取最小结点
FibNode * FibHeapExtractMin(FibHeap * heap) {
    FibNode * x = NULL, * z = heap->min;
    if (z != NULL) {
 
        //删除z的每一个孩子
        while (NULL != z->child) {
            x = z->child;
            FibNodeRemove(x);
            if (x->right == x) {
                z->child = NULL;
            } else {
                z->child = x->right;
            }
            FibNodeAdd(x, z);//add x to the root list heap
            x->parent = NULL;
        }
 
        FibNodeRemove(z);
        if (z->right == z) {
            heap->min = NULL;
        } else {
            heap->min = z->right;
            FibHeapConsolidate(heap);
        }
        heap->keyNum--;
    }
    return z;
}
 
//合并左右相同度数的二项树
void FibHeapConsolidate(FibHeap * heap) {
    int D, d;
    FibNode * w = heap->min, * x = NULL, * y = NULL;
    FibHeapConsMake(heap);//开辟哈希所用空间
    D = heap->maxNumOfDegree + 1;
    for (int i = 0; i < D; i++) {
        *(heap->cons + i) = NULL;
    }
 
    //合并相同度的根节点，使每个度数的二项树唯一
    while (NULL != heap->min) {
        x = FibHeapMinRemove(heap);
        d = x->degree;
        while (NULL != *(heap->cons + d)) {
            y = *(heap->cons + d);
            if (x->key > y->key) {//根结点key最小
                swap(x, y);
            }
            FibHeapLink(heap, y, x);
            *(heap->cons + d) = NULL;
            d++;
        }
        *(heap->cons + d) = x;
    }
    heap->min = NULL;//原有根表清除
 
    //将heap->cons中结点都重新加到根表中，且找出最小根
    for (int i = 0; i < D; i++) {
        if (*(heap->cons + i) != NULL) {
            if (NULL == heap->min) {
                heap->min = *(heap->cons + i);
            } else {
                FibNodeAdd(*(heap->cons + i), heap->min);
                if ((*(heap->cons + i))->key < heap->min->key) {
                    heap->min = *(heap->cons + i);
                }//if(<)
            }//if-else(==)
        }//if(!=)
    }//for(i)
}
 
//将x根结点链接到y根结点
void FibHeapLink(FibHeap * heap, FibNode * x, FibNode *y) {
    FibNodeRemove(x);
    if (NULL == y->child) {
        y->child = x;
    } else {
        FibNodeAdd(x, y->child);
    }
    x->parent = y;
    y->degree++;
    x->marked = false;
}
 
//开辟FibHeapConsolidate函数哈希所用空间
static void FibHeapConsMake(FibHeap * heap) {
    int old = heap->maxNumOfDegree;
    heap->maxNumOfDegree = int(log(heap->keyNum * 1.0) / log(2.0)) + 1;
    if (old < heap->maxNumOfDegree) {
        //因为度为heap->maxNumOfDegree可能被合并,所以要maxNumOfDegree + 1
        heap->cons = (FibNode **) realloc(heap->cons,
            sizeof(FibHeap *) * (heap->maxNumOfDegree + 1));
        if (NULL == heap->cons) {
            puts("Out of Space!");
            exit(1);
        }
    }
}
 
//将堆的最小结点移出，并指向其有兄弟
static FibNode *FibHeapMinRemove(FibHeap * heap) {
    FibNode *min = heap->min;
    if (heap->min == min->right) {
        heap->min = NULL;
    } else {
        FibNodeRemove(min);
        heap->min = min->right;
    }
    min->left = min->right = min;
    return min;
}
 
//减小一个关键字
void FibHeapDecrease(FibHeap * heap, FibNode * x, int key) {
    FibNode * y = x->parent;
    if (x->key < key) {
        puts("new key is greater than current key!");
        exit(1);
    }
    x->key = key;
 
    if (NULL != y && x->key < y->key) {
        //破坏了最小堆性质，需要进行级联剪切操作
        FibHeapCut(heap, x, y);
        FibHeapCascadingCut(heap, y);
    }
    if (x->key < heap->min->key) {
        heap->min = x;
    }
}
 
//切断x与父节点y之间的链接，使x成为一个根
static void FibHeapCut(FibHeap * heap, FibNode * x, FibNode * y) {
    FibNodeRemove(x);
    renewDegree(y, x->degree);
    if (x == x->right) {
        y->child = NULL;
    } else {
        y->child = x->right;
    }
    x->parent = NULL;
    x->left = x->right = x;
    x->marked = false;
    FibNodeAdd(x, heap->min);
}
 
//级联剪切
static void FibHeapCascadingCut(FibHeap * heap, FibNode * y) {
    FibNode * z = y->parent;
    if (NULL != z) {
        if (y->marked == false) {
            y->marked = true;
        } else {
            FibHeapCut(heap, y, z);
            FibHeapCascadingCut(heap, z);
        }
    }
}
 
//修改度数
void renewDegree(FibNode * parent, int degree) {
    parent->degree -= degree;
    if (parent-> parent != NULL) {
        renewDegree(parent->parent, degree);
    }
}
 
//删除结点
void FibHeapDelete(FibHeap * heap, FibNode * x) {
    FibHeapDecrease(heap, x, INT_MIN);
    FibHeapExtractMin(heap);
}
 
//堆内搜索关键字
FibNode * FibHeapSearch(FibHeap * heap, int key) {
    return FibNodeSearch(heap->min, key);
}
 
//被FibHeapSearch调用
static FibNode * FibNodeSearch(FibNode * x, int key) {
    FibNode * w = x, * y = NULL;
    if (x != NULL) {
        do {
            if (w->key == key) {
                y = w;
                break;
            } else if (NULL != (y = FibNodeSearch(w->child, key))) {
                break;
            }
            w = w->right;
        } while (w != x);
    }
    return y;
}
 
//销毁堆
void FibHeapDestory(FibHeap * heap) {
    FibNodeDestory(heap->min);
    free(heap);
    heap = NULL;
}
 
//被FibHeapDestory调用
static void FibNodeDestory(FibNode * x) {
    FibNode * p = x, *q = NULL;
    while (p != NULL) {
        FibNodeDestory(p->child);
        q = p;
        if (p -> left == x) {
            p = NULL;
        } else {
            p = p->left;
        }
        free(q->right);
    }
}
 
//输出打印堆
static void FibHeapPrint(FibHeap * heap) {
    printf("The keyNum = %d\n", heap->keyNum);
    FibNodePrint(heap->min);
    puts("\n");
};
 
//被FibHeapPrint调用
static void FibNodePrint(FibNode * x) {
    FibNode * p = NULL;
    if (NULL == x) {
        return ;
    }
    p = x;
    do {
        printf(" (");
        printf("%d", p->key);
        if (p->child != NULL) {
            FibNodePrint(p->child);
        }
        printf(") ");
        p = p->left;
    }while (x != p);
}
 
int keys[10] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 11};
 
int main() {
    FibHeap * heap = NULL;
    FibNode * x = NULL;
    heap = FibHeapMake();
    FibHeapInsertKeys(heap, keys, 10);
    FibHeapPrint(heap);
 
    x = FibHeapExtractMin(heap);
    printf("抽取最小值%d之后：\n", x->key);
    FibHeapPrint(heap);
 
    x = FibHeapSearch(heap, 11);
    if (NULL != x) {
        printf("查找%d成功,", x->key);
        FibHeapDecrease(heap, x, 8);
        printf("减小到%d后：\n", x->key);
        FibHeapPrint(heap);
    }
 
    x = FibHeapSearch(heap, 7);
    if (NULL != x) {
        printf("删除%d成功:\n", x->key);
        FibHeapDelete(heap, x);
        FibHeapPrint(heap);
    }
 
    FibHeapDestory(heap);
    return 0;
}