#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string.h>
using namespace std;
int graph[100][100], n, m = 0;  //用二维数组存图，节点数、边数初始化为0
int ans[50], count = 0;  //记录欧拉路的路径，路径数
bool visted[50];  //标记点是否被访问
int begin;  //判是否为连通图，搜索的起点


struct stack
{
    int top, node[100];
}s;  //定点的栈结构

//输出随机生成的无向图关系矩阵
void Print()
{
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
}

//初始化图
void Init()
{
    bool flag = false;  //标记是否生成图
    memset(graph, 0, sizeof(graph));  //初始化为0
    memset(visted, false, sizeof(visted));  //初始化都未被访问
    memset(ans, 0, sizeof(ans));  //欧拉图初始化为0
    srand((unsigned)time(NULL));
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            graph[i][j] = 0 + rand() % 2;  //随机生成无向图
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(graph[i][j])
            {
                flag = true;    //最少有一条边
                m++;            //记录边的条数
                graph[j][i] = 1;  //无向图的定义
                begin = i;         //有一条边则其任意一个端点设为起点
            }
    while(!flag)  //如果没有边则重新生成图：防止 rand 随机值恰好生成不了图
        Init();
}

//深度优先搜索
void DFS(int x)
{   
    visted[x] = true;
    for(int i = 0; i < n; i++)
        if(!visted[i] && graph[x][i])
            DFS(i);
}   
 
//从所设定的起点深度优先遍历图，若有一个点没被访问，则为非连通图
bool Judge()
{
    DFS(begin);
    for(int i = 0; i < n; i++)
        if(!visted[i])
            return false;
    return true;
}

//深度优先搜索
void DFSGraph(int x)
{
    s.top++;
    s.node[s.top] = x;
    for(int i = 0; i < n; i++)
    {
        if(graph[i][x] > 0)
        {
            graph[i][x] = 0;  //删除该边
            graph[x][i] = 0; 
            DFSGraph(i);
            break;
        }
    }
}

//Fleury算法
void Fleury(int x)
{
    int flag;
    s.top = 0; 
    s.node[s.top] = x;  //起点入栈
    while(s.top >= 0)
    {
        flag = 0;
        for(int i = 0; i < n; i++)
        {
            if(graph[s.node[s.top]][i] > 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)  //如果没有可扩展的点，则记录下该点并将其出栈
        {
            ans[count ++] = s.node[s.top] + 1;
            s.top --;
        }
        else  //如果有，则将其出栈并继续搜索
        {
            s.top --;
            DFSGraph(s.node[s.top + 1]);
        }
    }
    cout << endl;
}

//输出答案
void Answer()
{
    for(int i = 0; i < count; i++)
        cout << ans[i] << " ";
    cout << endl;
}


int main()
{
    int num = 0, start = 0, degree;  //奇度顶点个数, 欧拉路的起点, 每个顶点的度
    cout << "Please input n(1 <= n <= 20): ";
    cin >> n;
    Init();
    cout << endl << "The generated undirected graph is: " << endl;
    Print();
    cout << endl;
    if(!Judge())
    {
        cout << "Non-connected graph" << endl;
        return 0;   
    }
    //如果存在奇度顶点，则从奇度顶点出发，否则从0出发
    for(int i = 0; i < n; i++)
    {
        degree = 0;
        for(int j = 0; j < n; j++)
            degree += graph[i][j];
        if(degree % 2)
        {
            start = i;
            num++;
        }
    }
    //无向图具有一条欧拉路，当且仅当G是连通的，且有0个或2个奇数度结点
    if(num == 0 || num == 2)
    {
        Fleury(start);
        //欧拉路径的头和尾相等，则说明欧拉路是回路
        if(ans[0] == ans[count - 1])
            cout << "This graph is Euler Graph, its Euler Loop is: ";
        else
            cout << "This graph is Half-Euler Graph, its Euler Path is: ";
        Answer();
    }
    else
        cout << "This graph is Non-Euler Graph or Half-Euler Graph." << endl;
    return 0;
}   
