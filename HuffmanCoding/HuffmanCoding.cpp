/*
运行环境：VC++2010
result:
_____________________________
编码结果为：
 5 : 1110
 9 : 1111
12 : 100
13 : 101
16 : 110
45 : 0
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<climits>
using namespace std;
 
//HuffmanTree --> HT;
typedef struct HuffmanTreeNode HT;
typedef struct HuffmanTreeNode * SearchTree;//哈夫曼树
typedef char * *HTCode;//动态分配数组储存哈夫蛮编码 
 
//哈夫曼树ATD
struct HuffmanTreeNode {
    int key;
    int parent, left, right;
    HuffmanTreeNode(int a, int b, int c, int d) {
        key = a, parent = b, left = c, right = d;
    }
};
 
void CreatHuffmanTree(SearchTree &tree, int *w, int n);
void Select(SearchTree tree, int t, int &s1, int &s2);
void HuffmanCoding (SearchTree tree, HTCode &HC, int n);
void PrintHTCode(HTCode HC, int *c, int n);
 
//构造哈夫曼树
void CreatHuffmanTree(SearchTree &tree, int *w, int n) {
    int i, s1, s2;
    SearchTree p;
    /*哈夫蛮树中没有度为1的结点，是满二叉树，因为根节点不保存信息，
    所以至少应该有2个结点，才能构成满二叉树  */
    if (n <= 1) {
        return ;
    }
    int m = 2 * n - 1;//n个叶子结点的哈夫曼树共有2n - 1个结点
    tree = (SearchTree) malloc((m + 1) * sizeof(HT));//0位置木有结点
 
    for (p = tree + 1, i = 1; i <= n; i++, p++, w++) {
        *p = HT(*w, 0, 0, 0);//前n个结点初始化为已知结点key 
 
    }
    for (; i <= m; i++, p++) {//后n + 1 ~ 2n - 1初始化为0
        *p = HT(0, 0, 0, 0);
    }
 
    //找到最小的两个结点，给新结点tree[i]赋值
    for (i = n + 1; i <= m; i++) {
        Select(tree, i - 1, s1, s2);
        tree[s1].parent = tree[s2].parent = i;
        tree[i] = HT(tree[s1].key + tree[s2].key, tree[i].parent, s1, s2);
    }
}
 
//完成编码任务
void HuffmanCoding (SearchTree tree, HTCode &HC, int n) {
    int i, c, f, start;
    char *cd;
    HC = (HTCode) malloc ((n + 1) * sizeof(char *)); //分配n个字符编码的头指针向量
    cd = (char *) malloc(n * sizeof(char));//分配编码的工作空间
    //n个结点的哈夫曼树高度最多为n, 所以路径最高为n - 1，稍微画下图就可以了解，
    //也就是说编码空间有n - 1就足够了
    cd[n - 1] = '\0';
    for (i = 1; i <= n; i++) {
        start = n - 1;
        //从叶子到根逆向求编码
        for (c = i, f = tree[i].parent; f != 0; c = f, f = tree[f].parent) {
            if (tree[f].left == c) {
                cd[--start] = '0';
            } else {
                cd[--start] = '1';
            }
        }
        HC[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
}
 
//找出最小值，次小值下标
void Select (SearchTree tree, int t, int &s1, int &s2) {
    int i, min1, min2;
    min1 = min2 = INT_MAX;
    /*  当t为偶数时      min1-->最小
                        min2-->次小
        当t为奇数时， min1->次小
                        min2->最小
        因为有两种情况，所以for循环结束之后，还要判断一次来确定最小值，次小值
    */
    for (i = 1; i <= t; i++) {
        if (tree[i].parent == 0 &&
             (tree[i].key < min1 || tree[i].key < min2)) {
                if (min1 < min2) {//先找到次小
                    min2 = tree[i].key;
                    s2 = i;
                } else {//再找到最小
                    min1 = tree[i].key;
                    s1 = i;
                }//if
             }//if (……)
    }//for(i)
    if (s1 > s2) {
        swap(s1, s2);
    }
}
 
//输出编码结果
void PrintHTCode(HTCode HC, int *w, int n) {
    puts("编码结果为：");
    for (int i = 1; i <= n; i++) {
        printf("%2d : %s\n", w[i - 1], HC[i]);
    }
}
 
int w[6] = {5, 9, 12, 13, 16, 45};
const int N = 6;
int main() {
    SearchTree tree;
    HTCode HC;
    CreatHuffmanTree(tree, w, N);
    HuffmanCoding (tree, HC, N);
    PrintHTCode(HC, w, N);
    return 0;
}