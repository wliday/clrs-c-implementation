/*
按关键字的顺序遍历B-树:
(3, 11)
(7, 16)
(12, 4)
(24, 1)
(26, 13)
(30, 12)
(37, 5)
(45, 2)
(50, 6)
(53, 3)
(61, 7)
(70, 10)
(85, 14)
(90, 8)
(100, 9)
 
请输入待查找记录的关键字: 26
(26, 13)
 
5
没找到
 
37
(37, 5)
 
*/
 
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
 
#define m 3  // B树的阶，暂设为3
//3阶的B-数上所有非终点结点至多可以有两个关键字
#define N 16 // 数据元素个数
#define MAX 5 // 字符串最大长度 + 1  
 
//记录类型
struct Record{
    int key; // 关键字
    char info[MAX];
};  
 
//B-树ADT
struct BTreeNode {
    int keynum; // 结点中关键字个数
    struct BTreeNode * parent; // 指向双亲结点
    struct Node { // 结点类型
        int key; // 关键字
        Record * recptr; // 记录指针
        struct BTreeNode * ptr; // 子树指针
    }node[m + 1]; // key, recptr的0号单元未用
}; 
 
typedef BTreeNode BT;
typedef BTreeNode * Position;
typedef BTreeNode * SearchTree;
 
//B-树查找结果的类型
typedef struct {
    Position pt; // 指向找到的结点
    int i; // 1..m，在结点中的关键字序号
    int tag; // 1:查找成功，O:查找失败
}Result; 
 
inline void print(BT c, int i) {// TraverseSearchTree()调用的函数
    printf("(%d, %s)\n", c.node[i].key, c.node[i].recptr->info);
}
 
//销毁查找树
void DestroySearchTree(SearchTree tree) {
    if(tree) {// 非空树
        for(int i = 0; i <= (tree)->keynum; i++ ) {
            DestroySearchTree(tree->node[i].ptr); // 依次销毁第i棵子树
        }
        free(tree); // 释放根结点
        tree = NULL; // 空指针赋0
    }
}
 
//在p->node[1..keynum].key中查找i, 使得p->node[i].key≤K＜p->node[i + 1].key
//返回刚好小于等于K的位置
int Search(Position p, int K) {
    int location = 0;
    for(int i = 1; i <= p->keynum; i++ ) {
        if(p->node[i].key <= K) {
            location = i;
        }
    }
    return location;
}
 
/*
在m阶B树tree上查找关键字K，返回结果(pt, i, tag)。
若查找成功，tag = 1，指针pt所指结点中第i个关键字等于K；
若查找失败，tag = 0，等于K的关键字应插入在指针Pt所指结点中第i和第i + 1个关键字之间。
*/
Result SearchPosition(SearchTree tree, int K) {
    Position p = tree, q = NULL; // 初始化，p指向待查结点，q指向p的双亲
    bool found = false;
    int i = 0;
    Result r;
    while(p && !found) {
        i = Search(p, K); // p->node[i].key≤K<p->node[i + 1].key
        if(i > 0 && p->node[i].key == K) {// 找到待查关键字
            found = true;
        } else {
            q = p;
            p = p->node[i].ptr;
        }
    }
    r.i = i;
    if(found) {// 查找成功
        r.pt = p;
        r.tag = 1;
    } else {//  查找不成功，返回K的插入位置信息
        r.pt = q;
        r.tag = 0;
    }
    return r;
}
 
//将r->key、r和ap分别插入到q->key[i + 1]、q->recptr[i + 1]和q->ptr[i + 1]中
void Insert(Position q, int i, Record * r, Position ap) {
    for(int j = q->keynum; j > i; j--) {// 空出q->node[i + 1]
        q->node[j + 1] = q->node[j];
    }
    q->node[i + 1].key = r->key;
    q->node[i + 1].ptr = ap;
    q->node[i + 1].recptr = r;
    q->keynum++;
}
 
// 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap
void split(Position &q, Position &ap) {
    int s = (m + 1) / 2;
    ap = (Position)malloc(sizeof(BT)); // 生成新结点ap
    ap->node[0].ptr = q->node[s].ptr; // 后一半移入ap
    for(int i = s + 1; i <= m; i++ ) {
        ap->node[i-s] = q->node[i];
        if(ap->node[i - s].ptr) {
            ap->node[i - s].ptr->parent = ap;
        }
    }
    ap->keynum = m - s;
    ap->parent = q->parent;
    q->keynum = s - 1; // q的前一半保留，修改keynum
}
 
// 生成含信息(T, r, ap)的新的根结点*T，原T和ap为子树指针
void NewRoot(Position &tree, Record *r, Position ap) {
    Position p;
    p = (Position)malloc(sizeof(BT));
    p->node[0].ptr = tree;
    tree = p;
    if(tree->node[0].ptr) {
        tree->node[0].ptr->parent = tree;
    }
    tree->parent = NULL;
    tree->keynum = 1;
    tree->node[1].key = r->key;
    tree->node[1].recptr = r;
    tree->node[1].ptr = ap;
    if(tree->node[1].ptr) {
        tree->node[1].ptr->parent = tree;
    }
}
 
/*
在m阶B-树tree上结点*q的key[i]与key[i + 1]之间插入关键字K的指针r。若引起
结点过大, 则沿双亲链进行必要的结点分裂调整, 使tree仍是m阶B树。
*/
void InsertPosition(SearchTree &tree, Record &r, Position q, int i) {
    Position ap = NULL;
    bool finished = false;
    Record *rx = &r;
 
    while(q && !finished) {
        // 将r->key、r和ap分别插入到q->key[i + 1]、q->recptr[i + 1]和q->ptr[i + 1]中
        Insert(q, i, rx, ap);
        if(q->keynum < m) {
            finished = true; // 插入完成
        } else { // 分裂结点*q
            int s = (m + 1) >> 1;
            rx = q->node[s].recptr;
            // 将q->key[s + 1..m], q->ptr[s..m]和q->recptr[s + 1..m]移入新结点*ap
            split(q, ap);
            q = q->parent;
            if(q) {
                i = Search(q, rx->key); // 在双亲结点*q中查找rx->key的插入位置
            }
        }
    }
    if(!finished) {// T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap
        NewRoot(tree, rx, ap); // 生成含信息(T, rx, ap)的新的根结点*T，原T和ap为子树指针
    }
}
 
/*
操作结果: 按关键字的顺序对tree的每个结点调用函数Visit()一次且至多一次
*/
void TraverseSearchTree(SearchTree tree, void(*Visit)(BT, int)) {
    if(tree) {// 非空树
        if(tree->node[0].ptr) {// 有第0棵子树
            TraverseSearchTree(tree->node[0].ptr, Visit);
        }
        for(int i = 1; i <= tree->keynum; i++ ) {
            Visit(*tree, i);
            if(tree->node[i].ptr) { // 有第i棵子树
                TraverseSearchTree(tree->node[i].ptr, Visit);
            }
        }
    }
}
 
int main() {
    Record r[N] = {{24, "1"}, {45, "2"}, {53, "3"}, {12, "4"},
                   {37, "5"}, {50, "6"}, {61, "7"}, {90, "8"},
                   {100, "9"}, {70, "10"}, {3, "11"}, {30, "12"},
                   {26, "13"}, {85, "14"}, {3, "15"}, {7, "16"}};
    SearchTree tree = NULL;//初始化一棵空树
    Result res;//存放结果
 
    int i;
    for(i = 0; i < N; i++ ) {
        res = SearchPosition(tree, r[i].key);
        if(!res.tag) {
            InsertPosition(tree, r[i], res.pt, res.i);
        }
    }
 
    printf("按关键字的顺序遍历B-树:\n");
    TraverseSearchTree(tree, print);
    printf("\n请输入待查找记录的关键字: ");
    while (scanf("%d", &i)) {
        res = SearchPosition(tree, i);
        if(res.tag) {
            print(*(res.pt), res.i);
        } else {
            printf("没找到\n");
        }
        puts("");
    }
    DestroySearchTree(tree);
}