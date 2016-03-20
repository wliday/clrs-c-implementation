/*最好先手动画下图，或者看上边那张图，这样好理解，否则不太好理解二重指针
输出：
————————————————
表的大小是；23
 
89插入表中
18插入表中
49插入表中
58插入表中
69插入表中
 
小伙子，69查找成功了
25不存在表中
69删除成功
25不存在, 无法删除
*/
 
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
 
struct HashTbl;
struct ListNode;
 
typedef struct HashTbl * HashTable;//不用这几个typedef程序很难看懂
typedef struct ListNode * Position;
//下边这个typedef也是为了更好的理解
typedef Position List;
 
const int maxn = 400000; // maxn : size
bool prime[maxn]; // true : prime number
 
//Sieve Prime素数筛法, 先预处理好，否则很费时间
//单独判定素数是非常耗时间的
void Seive_Prime() {//判素,素数筛选
     memset(prime, true, sizeof(prime));
     prime[0] = prime[1] = false;
     for (int i = 2; i * i < maxn; i++) {
          if (prime[i]) {
               for (int j = i * i; j < maxn ; j += i) {
                    prime[j] = false;
               }
          }
     }//for
}
 
//一个点代表一个槽
struct ListNode {//代表每行的节点
    int element;
    Position next;
};
 
//一个点代表槽中的一个链表上的一个点
struct HashTbl {
    int TableSize;
    Position *TheList;//指针的指针，指向由于冲突形成的链表
};
 
//简单起见，这里用int整型，然后是除法散列
int Hash(int key, int TableSize) {
    return key % TableSize;//TableSize得是素数
}
 
//素数的分布很均匀，所以这里耗时平均应该差不多，找到第一个比它大的素数
int NextPrime(int x) {
    if (prime[x]) {
        return x;
    } else {
        NextPrime(x + 1);
    }
}
 
//初始化, 返回的是一个指针
HashTable InitalizeTable(int TableSize) {
    if (TableSize <= 0) {
        puts("Table size is too small");
        return NULL;
    }
 
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
    if (H == NULL) {
        puts("Out of space");
    }
 
    //指定List的一个数组，由于List是一个指针，因此结果为指针的数组
    H->TableSize = NextPrime(TableSize);
    H->TheList = (List *)malloc(sizeof(List) * H->TableSize);
    if (H->TheList == NULL) {
        puts("Out of space");
    }
 
    //List是带头结点的
    H->TheList[0] = (List)malloc(H->TableSize * sizeof(struct ListNode));
    if (H->TheList[0] == NULL) {
        printf("Out of space");
    }
 
    for (int i = 0; i < H->TableSize; i++) {
        H->TheList[i] = H->TheList[0] + i;
        H->TheList[i]->next = NULL;
    }
    return H;
}
 
//返回的是一个指针，指向包含Key的那个单元
Position Find(int key, HashTable H){
    Position p;
    //先找到所在行
    List L = H->TheList[Hash(key, H->TableSize)];
    p = L->next;
    while (p != NULL && p->element != key) {
        p = p->next;
    }
    if (p == NULL) {
        return L;
    } else {
        return p;
    }
}
 
//如果没有找到，就插入，如果找到了，就什么也不做
void Insert(int key, HashTable H) {
    Position pos,  NewCell;
    pos = Find(key, H);
    if (pos->element != key) {//Key没找到，所以要插入
        NewCell = (List)malloc(sizeof(struct ListNode));
        if (NewCell == NULL) {
            puts("Out of space");
        } else {
            List L = H->TheList[Hash(key, H->TableSize)];
            NewCell->next = L->next;//新节点放在表的最前面
            NewCell->element = key;
            pos->next = NewCell;//表头指向新加入的节点，新节点成为了第一个节点
        }
        printf("%d插入表中\n", key);
    } else {
        printf("%d已经存在, 无需重复插入.\n", key);
    }
}
 
//如果找到该值，原来的节点用一个空节点替换，销毁原来节点，如果没找到，什么也不做
void Delete(int key, HashTable H) {
    Position pos, NewCell;
    pos = Find(key, H);
    if (pos->element == key) {
        NewCell = H->TheList[Hash(key, H->TableSize)];
        while (NewCell->next != pos) {
            NewCell = NewCell->next;
        }
        NewCell->next = pos->next;
        free(pos);
        printf("%d删除成功\n", key);
    } else {
        printf("%d不存在, 无法删除\n", key);
    }
}
 
inline void Find_Description(Position p, int key) {
    if (p->element == key) {
        printf("小伙子，%d查找成功了\n", key);
    } else {
        printf("%d不存在表中\n", key);
    }
}
 
int main() {
     Seive_Prime() ;
 
     HashTable table = InitalizeTable(20);
     printf("表的大小是；%d\n", table->TableSize );//23
 
     Position pos = NULL;
 
     //先插入5个元素
     Insert(89, table);
     Insert(18, table);
     Insert(49, table);
     Insert(58, table);
     Insert(69, table);
 
     //测试可以找到的
     pos = Find(69, table);
     Find_Description(pos, 69);
 
     //测试找不到的
     pos = Find(25, table);
     Find_Description(pos, 25);
 
     //测试删除有的key
     Delete(69, table);
 
     //测试删除没有的key
     Delete(25, table);
 
     return 0;
}