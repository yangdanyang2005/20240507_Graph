#define _CRT_SECURE_NO_WARNINGS 1
#pragma once/*��ֹͷ�ļ��ظ�����*/
//#pragma comment(linker, "/STACK:1073741824")//������ջ��С
/*�����޸ģ��������-���Ҽ��˵�����������-������-ϵͳ-��ջ������С-1073741824*/
//���ͷ�ļ�
#include <iostream>
#include <cstring>//����string
#include<fstream>//����iostream���ļ�
#include<stack>//����STL����stack
#include<queue>
#include<string>
#include<string.h>
#include<iomanip>//cout������ȿ���ͷ�ļ�
#include <cstring>
#include <cstring>  // For strerror()
#include <cerrno>   // For errno

//Ԥ���峣���ͱ������ͣ�ע�����޷ֺ�
#define M 1975//�����Ҵ���
#define N INT_MAX-1//������Ϊ�������ֵ
#define Huge_Value INT_MAX-1//������Ϊ�������ֵ
#define OK 1
#define ERROR 0
typedef char VerTexType;
typedef int VRType;
typedef int* PathMatrix;
typedef double* ShortDistTable;


using namespace std;

//�����С��Ķ��壨ͼ�Ķ��㣩
typedef struct
{
	bool pass;
	string country, city;//���ң���������
	double latitude, longitude;//���ȣ�γ������
}City;
typedef City Vertex;//���еĽṹVertex�����㣩

//�ߣ����򣩵Ķ���
typedef struct
{
	double cost;//��ͨ�ɱ�
	double time;//ͨ��ʱ��
	string transport;//��ͨ��ʽ
	string otherInfo;//������Ϣ
}Arc;

//ͼ�Ķ��壨���ڽӾ����ʾ����BP161��
typedef struct
{
	Vertex* vertex;//���ж�������
	Arc** arcs;//�ڽӾ��󣺱�ʾͼ��һ�ִ洢�ṹ������ʹ���˶�̬�����ڴ�
	int vexnum, arcnum;//ͼ�ĵ�ǰ������������
}Graph;

/*�ļ��д洢��һ��·������ĳ����ĳ����
����ȫ��ͬ������ͼ�еıߣ���������Ϊ�ߵĴ洢�ġ�����*/
typedef struct
{
	string origin_city, destination_city, transport, other_infomation;//��ͨ�ɱ���ͨ��ʱ�䣬��ͨ��ʽ��������Ϣ
	double time, cost;//ͨ��ʱ�䣬�ɱ�
}Route;

/*******************************ǰ�ú���*******************************/

void ShowMenu();

int InitGraph();

bool reInitGraph();

void ExitSystem();

/*********************���ͼ���ڽӾ��󣩴����ĺ���*********************/

int Locate(const string& origin, Graph graph);

int Locate(const string& origin, City* ct, int nCtNum);

//�ڽӾ���ṹ�£�G��V�ĵ�һ���ڽӵ�
inline int firstAdivex(Graph G, int v);

//��vw����һ�����������Ӧ�Ķ��㣬Ҳ��v�������w����һ������
inline int nextAdivex(Graph G, int v, int w);

//��ȡCity����
bool ReadCityData(string strFileName, City*& ct, int& nCtNum);

//��ȡroute����
bool ReadRouteData(string strFileName, Route*& route, int& nRtNum);

//��ʼ���ڽӾ���
bool AdjMatrix(Graph& g, int nCtNum, City* ct, Route* route, int nRtNum, int nCostType);

/**************************���ͼ�ı����ĺ���**************************/

//��ͨͼ��������ȱ���������������������������firstAdivex��nextAdivex����д��
void DFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[]); 
void DFSTraverseConnect1(Graph& G, int v, bool*& visited, City ct[]);

//�Է���ͨͼG�����������������
void DFSTraverse(Graph& G, City ct[]);
void DFSTraverse1(Graph& G, City ct[]);

//��ͨͼ�Ĺ�����ȱ���������������������������firstAdivex��nextAdivex����д��
void BFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[]);

//�Է���ͨͼG�Ĺ��������������
void BFSTraverse(Graph& G, City ct[]);

/*************************��ͼ�����·���ĺ���*************************/

//��cost�Ƚ���С�����·��
void ShortestPathByCost_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D);
//v0����㣬P���������·����ǰ���㣬�Ǹ�int*���͵Ķ�̬����

//��time�Ƚ���С�����·��
void ShortestPathByTime_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D);
//v0����㣬D������Դ�㵽��ǰ�����̾��룬�Ǹ�double*���͵Ķ�̬����

//����HTML�ļ�����ʾ·����Ϣ
bool CreateHtml(const Graph& G, const double* D, const char* strFile, const City* ct, int head, int end, const int* P, int nCostType);
//filePath��HTML�ļ�·����D��Դ�㵽�����������̾���ct�ǳ�����Ϣ��head����㣬end���յ㣬P�����·����ǰ����

//��HTML�ļ��������������ʾ
bool OpenHtmlInBrowser(string filePath);

// ����������ѡ���Ƿ񴴽�HTML�ļ���֧��ѡ���Ƿ��
void createHTMLInMian(Graph g, double* D, int depart, int dest, int* P, int nCostType);