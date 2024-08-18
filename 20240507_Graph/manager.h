#define _CRT_SECURE_NO_WARNINGS 1
#pragma once/*防止头文件重复包含*/
//#pragma comment(linker, "/STACK:1073741824")//调整堆栈大小
/*或者修改：解决方案-（右键菜单下拉）属性-链接器-系统-堆栈保留大小-1073741824*/
//添加头文件
#include <iostream>
#include <cstring>//用于string
#include<fstream>//用于iostream读文件
#include<stack>//用于STL容器stack
#include<queue>
#include<string>
#include<string.h>
#include<iomanip>//cout输出精度控制头文件
#include <cstring>
#include <cstring>  // For strerror()
#include <cerrno>   // For errno

//预定义常量和变量类型，注意有无分号
#define M 1975//最大查找次数
#define N INT_MAX-1//可以认为是无穷大值
#define Huge_Value INT_MAX-1//可以认为是无穷大值
#define OK 1
#define ERROR 0
typedef char VerTexType;
typedef int VRType;
typedef int* PathMatrix;
typedef double* ShortDistTable;


using namespace std;

//“城市”的定义（图的顶点）
typedef struct
{
	bool pass;
	string country, city;//国家，城市名称
	double latitude, longitude;//经度，纬度数据
}City;
typedef City Vertex;//城市的结构Vertex（顶点）

//边（无向）的定义
typedef struct
{
	double cost;//交通成本
	double time;//通勤时间
	string transport;//交通方式
	string otherInfo;//其他信息
}Arc;

//图的定义（用邻接矩阵表示）（BP161）
typedef struct
{
	Vertex* vertex;//城市顶点数组
	Arc** arcs;//邻接矩阵：表示图的一种存储结构。这里使用了动态分配内存
	int vexnum, arcnum;//图的当前顶点数、边数
}Graph;

/*文件中存储的一条路径，从某处到某处，
不完全等同于上述图中的边，但可以作为边的存储的“镜像”*/
typedef struct
{
	string origin_city, destination_city, transport, other_infomation;//交通成本，通勤时间，交通方式，其他信息
	double time, cost;//通勤时间，成本
}Route;

/*******************************前置函数*******************************/

void ShowMenu();

int InitGraph();

bool reInitGraph();

void ExitSystem();

/*********************完成图（邻接矩阵）创建的函数*********************/

int Locate(const string& origin, Graph graph);

int Locate(const string& origin, City* ct, int nCtNum);

//邻接矩阵结构下，G中V的第一个邻接点
inline int firstAdivex(Graph G, int v);

//求vw的下一条相关联弧对应的顶点，也即v的相对于w的下一个顶点
inline int nextAdivex(Graph G, int v, int w);

//读取City数据
bool ReadCityData(string strFileName, City*& ct, int& nCtNum);

//读取route数据
bool ReadRouteData(string strFileName, Route*& route, int& nRtNum);

//初始化邻接矩阵
bool AdjMatrix(Graph& g, int nCtNum, City* ct, Route* route, int nRtNum, int nCostType);

/**************************完成图的遍历的函数**************************/

//连通图的深度优先遍历函数，基于上述两个函数（firstAdivex、nextAdivex）编写的
void DFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[]); 
void DFSTraverseConnect1(Graph& G, int v, bool*& visited, City ct[]);

//对非连通图G的深度优先搜索遍历
void DFSTraverse(Graph& G, City ct[]);
void DFSTraverse1(Graph& G, City ct[]);

//连通图的广度优先遍历函数，基于上述两个函数（firstAdivex、nextAdivex）编写的
void BFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[]);

//对非连通图G的广度优先搜索遍历
void BFSTraverse(Graph& G, City ct[]);

/*************************求图的最短路径的函数*************************/

//求按cost比较最小的最短路径
void ShortestPathByCost_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D);
//v0是起点，P用来存最短路径的前驱点，是个int*类型的动态数组

//求按time比较最小的最短路径
void ShortestPathByTime_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D);
//v0是起点，D用来存源点到当前点的最短距离，是个double*类型的动态数组

//创建HTML文件，显示路径信息
bool CreateHtml(const Graph& G, const double* D, const char* strFile, const City* ct, int head, int end, const int* P, int nCostType);
//filePath是HTML文件路径，D是源点到各个顶点的最短距离ct是城市信息，head是起点，end是终点，P是最短路径的前驱点

//打开HTML文件并在浏览器中显示
bool OpenHtmlInBrowser(string filePath);

// 在主函数中选择是否创建HTML文件，支持选择是否打开
void createHTMLInMian(Graph g, double* D, int depart, int dest, int* P, int nCostType);