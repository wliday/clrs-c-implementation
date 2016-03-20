/*平方探测法代码实现
输出：
——————————————
表的大小是；11
89插入成功
18插入成功
49插入成功
58插入成功
69插入成功
位置4上的元素是：69
 
69删除成功
69不存在或者已被删除，删除失败
69插入成功
 
*/
 
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
 
struct HashTbl;
typedef struct HashTbl * HashTable;
typedef unsigned int Position;
 
typedef struct HashEntry Cell;
//用来表示这行是合法的，空的，还是删掉了
enum KindOfEntry {Legitimate, Empty, Deleted};
 
struct HashEntry {
    int element;
    enum KindOfEntry Info;
};
 
struct HashTbl {
    int TableSize;
    Cell *TheCells;
};
 
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
 
//是除法散列
Position Hash(int key, int TableSize) {
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
        return NULL;
    }
    //例子中，10不是素数，如果想测试，可以在这里改一改，下边这句改为：
    //H->TableSize = TableSize;
    H->TableSize = NextPrime(TableSize);
    H->TheCells = (HashEntry *)malloc(sizeof(Cell) * H->TableSize);
    if (H->TheCells == NULL) {
        puts("Out of space!");
        return NULL;
    }
 
    //每个单元的Info域都设置为Empty
    for (int i = 0; i < H->TableSize; i++) {
        H->TheCells[i].Info = Empty;
    }
    return H;
}
 
/*返回Key在散列表中的位置，如果Key不出现，那么Find返回最后的单元 ,上边讨论过
所以表的大小至少要是表中元素个数的两倍，这样平方探测才能实现
*/
Position Find(int key, HashTable H){
    Position pos;
    int num = 0;
    pos = Hash(key, H->TableSize);
    while (H->TheCells[pos].Info != Empty && H->TheCells[pos].element != key) {
        pos += 2 * (++num) - 1;
        if (pos >= (Position)(H->TableSize)) {//不要取模，取模真的很慢
            pos -= H->TableSize;
        }
    }
    return pos;
}
 
/*没找到就插入，修改状态，写入值*/
void Insert(int key, HashTable H) {
    Position pos;
    pos = Find(key, H);
    if (H->TheCells[pos].Info != Legitimate) {
        H->TheCells[pos].Info = Legitimate;
        H->TheCells[pos].element = key;
        printf("%d插入成功\n", key);
    } else {
        printf("%d已存在，无需插入", key);
    }
}
 
/*这里的删除并不是真正的删除，只是状态标记为删除而已
标准的删除这里不能实行，因为相应的单元可能已经引起过冲突，
元素绕过它存在了别处。例如，如果删除 89，那么实际上所有的
Find例程都不能正常运行，所以这里的删除是懒惰删除*/
void Delete(int key, HashTable H) {
    Position pos;
    pos = Find(key, H);
    if (H->TheCells[pos].Info == Legitimate) {
        H->TheCells[pos].Info = Deleted;
        printf("%d删除成功\n", key);
    } else {
        printf("%d不存在或者已被删除，删除失败\n", key);
    }
}
 
int main() {
     Seive_Prime() ;
 
     HashTable table = InitalizeTable(10);
     printf("表的大小是；%d\n", table->TableSize );//11
 
     //先插入5个元素
     Insert(89, table);
     Insert(18, table);
     Insert(49, table);
     Insert(58, table);
     Insert(69, table);
 
     //测试可以找到的
     Position  pos = Find(69, table);
     printf("位置%u上的元素是：%d\n", pos, table->TheCells[pos].element);
 
     Delete(69, table);
     Delete(69, table);
     Insert(69, table);
 
     return 0;
}