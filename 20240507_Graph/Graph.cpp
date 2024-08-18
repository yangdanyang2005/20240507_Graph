#include"manager.h"

//从图中找到相应城市
int Locate(const string& origin, Graph graph)
{
	for (int i = 0; i < graph.vexnum; i++)
	{
		if (origin == graph.vertex[i].city)
		{
			return i;
		}
	}
	return -1;
}

//从城市类的数组中找到相应城市
int Locate(const string& origin, City* ct, int nCtNum)
{
	for (int i = 0; i < nCtNum; i++)
	{
		if (origin == ct[i].city/*不能写ct->city*/)
		{
			return i;
		}
	}
	return -1;//整个数组找遍了都没找到
}

//邻接矩阵结构下，找到G中V的第一个邻接点
inline int firstAdivex(Graph G, int v)//由于结点数比较多，使用内联函数（函数的代码直接拷贝而非调用函数）来加快代码运行速率
{
	for (int w = 0; w < G.vexnum; w++)
	{
		if (w == v)continue;
		//N是一个大值，当cost<N衣明，[v][w]这条弧存在，w是v的一个邻接点
		//if条件一旦第一次成立的一条弧就是与v相关联的第一条弧，相邻接的顶点也就
		if (G.arcs[v][w].cost < N)
			return w;
	}
	return -1;//返回-1表明v不存在邻接点
}

//求vw的下一条相关联弧对应的顶点，也即v的相对于w的下一个顶点
inline int nextAdivex(Graph G, int v, int w)
{
	if (w + 1 >= G.vexnum)
	{
		return -1;
	}
	for (int j = w + 1; j < G.vexnum; j++)
	{
		if (j == v)continue;
		if (G.arcs[v][j].cost < N)
		{
			return j;
		}
	}
	return -1;
}

//读取City数据
bool ReadCityData(string strFileName, City*& ct, int& nCtNum)
{
	char cBuffer[1024];
	nCtNum = 0;
	//获取线路数据条数
	ifstream inFile(strFileName.c_str(), ios::in);
	//int nRtNum=0;
	while (inFile.getline(cBuffer, 1024))
	{
		nCtNum++;
	}
	inFile.close();
	//读取文件数据
	FILE* fp;
	fp = fopen(strFileName.c_str(), "r");
	/*相对路径：
	在调试状态下，会到路径"D:\c_language_code\whu_2_data_structure_wujianwei\20240507_Graph\20240507_Graph"底下找；
	在可执行程序中，回到.exe文件同级目录下找*/
	if (!fp)
	{
		cerr << "cities.csv open ERRaOR !\n\n";//文件打开失败
		exit(-1);
	}
	char ch = '\0';
	double f = 0.0;
	int i = 0;
	ct = new City[nCtNum];
	while (!feof(fp))
	{
		/*fgetc 是 C 语言标准库中的一个函数，用于从指定的文件流中读取【一个】字符。
		这个函数是字符读取操作的基础，通常用于逐字符地处理文件内容。

		函数的原型定义在 stdio.h 头文件中：
		int fgetc(FILE *stream);

		stream：这是一个指向 FILE 对象的指针，表示要从中读取字符的输入流。这通常是通过 fopen 函数打开的文件。

		fgetc 函数会返回读取到的字符的 ASCII 值（一个 int 类型的值）。
		如果到达文件末尾或发生错误，则返回 EOF（End Of File，一个特殊的常量，通常是 -1）。
		*/
		for (ch = fgetc(fp); ch != ','; ch = fgetc(fp))
		{
			ct[i].country += ch;//获取国家名称
		}
		ch = fgetc(fp);
		for (; ch != ','; ch = fgetc(fp))
		{
			ct[i].city += ch;//获取城市名称
		}
		fscanf(fp, "%lf,", &f);//从文件指针fp指向的文件中，读取double型的纬度，储存在double型的变量f中。注意这里有一个“,”
		/*fscanf
		函数介绍：
		fscanf是C语言中的一个标准库函数，用于从指定的输入流（通常是文件）中读取格式化输入。
		这个函数是 scanf 的文件版本，允许从文件中读取数据，而不是从标准输入（通常是键盘）读取。

		函数的原型：
		定义在 stdio.h 头文件中：
		int fscanf(FILE *stream, const char *format, ...);

		参数说明：
		stream：这是一个指向 FILE 对象的指针，表示要从中读取数据的输入流。这通常是通过 fopen 函数打开的文件。
		format：这是一个格式字符串，指定了要读取的数据类型以及如何进行解析。这与 scanf 函数中的格式字符串相同。
		...：这是可变参数列表，对应于 format 字符串中指定的要读取的变量的地址。

		返回值：
		fscanf 函数会返回成功读取并赋值的输入项的数量。如果到达文件末尾或发生错误，则返回 EOF（通常是 -1）。*/
		ct[i].latitude = f;//纬度存入数组
		fscanf(fp, "%lf\n", &f);//从文件指针fp指向的文件中，读取double型的经度，储存在double型的变量f中
		ct[i].longitude = f;//经度存入数组
		i++;//读取下一个城市顶点
	}
	fclose(fp);
	return true;
}

//读取route数据
bool ReadRouteData(string strFileName, Route*& route, int& nRtNum)
{
	char cBuffer[1024];
	//获取城市数据个数
	ifstream ctFile(strFileName.c_str(), ios::in);
	nRtNum = 0;
	while (ctFile.getline(cBuffer, 1024))
	{
		nRtNum++;
	}
	ctFile.close();
	char ch = '\0';
	double f = 0.0;
	int i = 0;
	FILE* fp1 = fopen(strFileName.c_str(), "r");
	if (!fp1)
	{
		cerr << "routes.csv open ERROR !\n\n";//文件打开失败
		exit(-2);
	}
	route = new Route[nRtNum];
	ch = fgetc(fp1);
	while (!feof(fp1))
	{
		while (ch != ',')
		{
			route[i].origin_city += ch;
			ch = fgetc(fp1);
		}
		ch = fgetc(fp1);
		while (ch != ',')
		{
			route[i].destination_city += ch;
			ch = fgetc(fp1);
		}
		ch = fgetc(fp1);
		while (ch != ',')
		{
			route[i].transport += ch;
			ch = fgetc(fp1);
		}
		fscanf(fp1, "%lf,", &route[i].time);
		fscanf(fp1, "%lf,", &route[i].cost);
		ch = fgetc(fp1);
		while (ch != '\n')
		{
			route[i].other_infomation += ch;
			ch = fgetc(fp1);
		}
		ch = fgetc(fp1);
		i++;
	}
	fclose(fp1);
	return true;
}

//初始化邻接矩阵 BP162
bool AdjMatrix(Graph& g, int nCtNum, City* ct, Route* route, int nRtNum, int nCostType)
{
	int i = 0, j = 0;
	g.arcnum = nCtNum * nCtNum;//图的顶点数
	g.vexnum = nCtNum;//图的边数
	g.vertex = ct;//城市顶点数组
	g.arcs = new Arc * [nCtNum];
	for (i = 0; i < nCtNum; i++)
	{
		g.arcs[i] = new Arc[nCtNum];
	}
	for (i = 0; i < nCtNum; i++)
	{
		for (j = 0; j < nCtNum; j++)
		{
			if (i == j)//顶点ij到顶点ij的花费
			{
				g.arcs[i][j].cost = 0;
				g.arcs[i][j].time = 0;
			}
			else//顶点ij到其他顶点的花费（初始化为无穷大，即N）
			{
				g.arcs[i][j].cost = Huge_Value;
				g.arcs[i][j].time = Huge_Value;
			}
		}
	}
	for (i = 0; i < nRtNum; i++)
	{
		int origin, destination;
		/*
		Locate函数在：遍历城市顶点数组，查找有没有跟传入的数据一样的
		int Locate(const string& origin, City ct[])
		{
			for (int i = 0; i < nCtNum; i++)
			{
				if (origin == ct[i].city)
				{
					return i;
				}
			}
			return N;
		}
		*/
		origin = Locate(route[i].origin_city, g);
		destination = Locate(route[i].destination_city, g);
		/*实际上，以下代码大意大概相当于：从route[i]的对应成员变量中找到某个城市定点的该数据项（BP4）的信息，传入图中
		g.arcs[origin][destination].cost = route[i].cost;
		g.arcs[origin][destination].time = route[i].time;
		但是不要拿上面两行替代下面的代码！因为在文件中数据里面存在这样的现象：相同的两个城市之间的直接连接的路径也会存在不同的时间或者路费的权重！
		下面的两个if语句的判断是为了确保邻接矩阵中存储的是从起点到终点的最短成本或时间。
		如果不进行这个判断，可能会导致最终的路径不是最短的。*/
		if (nCostType == 1)
		{
			if (route[i].cost < g.arcs[origin][destination].cost)
			{
				g.arcs[origin][destination].cost = route[i].cost;
				g.arcs[origin][destination].time = route[i].time;
				g.arcs[origin][destination].transport = route[i].transport;
				g.arcs[origin][destination].otherInfo = route[i].other_infomation;
			}
		}
		else//nCostType == 2
		{
			if (route[i].time < g.arcs[origin][destination].time)
			{
				g.arcs[origin][destination].cost = route[i].time;
				g.arcs[origin][destination].time = route[i].time;
				g.arcs[origin][destination].transport = route[i].transport;
				g.arcs[origin][destination].otherInfo = route[i].other_infomation;
			}
		}
	}
	return true;
}

//对连通图G的深度优先搜索遍历，基于上述两个函数（firstAdivex、nextAdivex）编写的 BP169
void DFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[])
{
	// 从顶点v出发，深度优先搜索遍历连通图 G
	visited[v] = true;//从这里出发，那这里一定已经被访问过了（见下面）
	int w = 0;/*这行代码初始化变量`w`为0。这个变量`w`用来存储顶点`v`的邻接顶点。
	初始化为0只是一个赋初始值操作，实际值并不重要，因为在进入循环之前`w`的值会被`firstAdivex`函数的返回值覆盖。*/
	cout << ct[v].city;//这就是在访问嘛
	for (w = firstAdivex(G, v)/*初始化`w`为与顶点`v`相连的第一个顶点*/;
		w != -1;/*只要`nextAdivex`函数返回的不是 - 1（通常表示没有更多的邻接顶点），循环就会继续*/
		w = nextAdivex(G, v, w)/*更新`w`为下一个邻接顶点*/)
	{
		if (!visited[w])
			/*检查顶点`w`是否已经被访问过。布尔数组`visited`用来标记每个顶点是否被访问过。
			如果`visited[w]`是`false`，说明顶点`w`还没有被访问，那么就可以进入if语句内部进行访问。
			到了最后输出的一个顶点的时候，所有的`v`的邻接顶点`w`都被访问过了，不会进入这个分支，所以就可以保证最后一个输出的顶点的末尾不输出"->"*/
		{
			cout << "->"; //放到这里可以保证最后一个输出的顶点的末尾不输出"->"（注意思路可以这样想：我要访问下一个的时候，才需要打印出"->"）					
			DFSTraverseConnect(G, w, visited, ct);//递归调用
			/*递归调用，对顶点`w`进行深度优先遍历。通过递归，算法可以遍历图中与顶点`v`相连的所有未访问顶点*/
		}
	}
} // DFS：从顶点`v`开始，递归地遍历图`G`中的所有顶点，确保每个顶点只被访问一次，并打印出遍历过程中访问顶点的顺序
//要实现保证最后一个输出的顶点的末尾不输出"->"，还有一种方法如下（虽然用的是输入而非逻辑的方法）
void DFSTraverseConnect1(Graph& G, int v, bool*& visited, City ct[])
{
	// 从顶点v出发，深度优先搜索遍历连通图 G
	visited[v] = true;//从这里出发，那这里一定已经被访问过了（见下面）
	int w = 0;/*这行代码初始化变量`w`为0。这个变量`w`用来存储顶点`v`的邻接顶点。
	初始化为0只是一个赋初始值操作，实际值并不重要，因为在进入循环之前`w`的值会被`firstAdivex`函数的返回值覆盖。*/
	cout << ct[v].city << "->";//这就是在访问嘛
	for (w = firstAdivex(G, v)/*初始化`w`为与顶点`v`相连的第一个顶点*/;
		w != -1;/*只要`nextAdivex`函数返回的不是 - 1（通常表示没有更多的邻接顶点），循环就会继续*/
		w = nextAdivex(G, v, w)/*更新`w`为下一个邻接顶点*/)
	{
		if (!visited[w])
			/*检查顶点`w`是否已经被访问过。布尔数组`visited`用来标记每个顶点是否被访问过。
			如果`visited[w]`是`false`，说明顶点`w`还没有被访问，那么就可以进入if语句内部进行访问。
			到了最后输出的一个顶点的时候，所有的`v`的邻接顶点`w`都被访问过了，不会进入这个分支，所以就可以保证最后一个输出的顶点的末尾不输出"->"*/
		{
			DFSTraverseConnect1(G, w, visited, ct);//递归调用
			/*递归调用，对顶点`w`进行深度优先遍历。通过递归，算法可以遍历图中与顶点`v`相连的所有未访问顶点*/
		}
	}
} // DFS：从顶点`v`开始，递归地遍历图`G`中的所有顶点，确保每个顶点只被访问一次，并打印出遍历过程中访问顶点的顺序

//对非连通图G的深度优先搜索遍历
void DFSTraverse(Graph& G, City ct[])
{

	int v = 0;
	bool* visited = new bool[G.vexnum];
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = false; // 访问标志数组初始化
	for (v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v])
		{
			cout << "\n";
			//DFS(G, v, visited, ct);
			DFSTraverseConnect(G, v, visited, ct);//连通图的遍历
		}
	}
}
//要实现保证最后一个输出的顶点的末尾不输出"->"，还有一种方法如下（虽然用的是输入而非逻辑的方法）
void DFSTraverse1(Graph& G, City ct[])
{

	int v = 0;
	bool* visited = new bool[G.vexnum];
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = false; // 访问标志数组初始化
	for (v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v])
		{
			cout << "\b \b\b \b \n";//\b相当于光标回退一格，空格是将原来的字符给覆盖掉。注意：这样会造成末尾冗余空格
			//DFS(G, v, visited, ct);
			DFSTraverseConnect1(G, v, visited, ct);//连通图的遍历
		}
	}
}

//连通图的广度优先遍历函数，基于上述两个函数（firstAdivex、nextAdivex）编写的 BP170
void BFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[])
{
	queue<int> queue; // 使用队列存储待访问的顶点
	/*在广度优先遍历中使用队列：能够保证顶点是按照从近到远的顺序被访问的*/
	visited[v] = true; // 标记该联通分量的起点为已访问
	queue.push(v); // 将起点加入队列
	while (!queue.empty())
	{
		int vertex = queue.front(); // 获取队列的头部元素，这将是下一个将被访问的顶点
		queue.pop(); // 将队列的头部元素弹出
		cout << ct[vertex].city; // 访问顶点
		// 遍历所有邻接顶点
		for (int w = firstAdivex(G, vertex); w != -1; w = nextAdivex(G, vertex, w)) //这段代码遍历顶点`vertex`的所有邻接顶点。`firstAdivex`函数返回`vertex`的第一个邻接顶点，`nextAdivex`函数返回`vertex`的下一个邻接顶点（相对于`w`）
		{
			if (!visited[w])
			{
				queue.push(w); // 如果`w`未被访问，则将其加入队列，以便后续访问
				visited[w] = true; // 标记为已访问
			}
		}
		// 确保在访问下一个顶点之前输出"->"，除了最后一个顶点
		if (!queue.empty()) //如果队列中还有顶点
		{
			cout << "->";//则在输出下一个顶点之前打印"->"
		}
	}
}//BFS 整个过程中，队列保证了顶点的访问顺序是先入先出（FIFO），这意味着先被加入队列的顶点先被访问。这样，就能够实现从起点开始，逐层向外扩展的广度优先遍历

//对非连通图G的广度优先搜索遍历
void BFSTraverse(Graph& G, City ct[])
{
	bool* visited = new bool[G.vexnum];
	for (int v = 0; v < G.vexnum; ++v)
	{
		visited[v] = false; // 初始化访问标志数组
	}
	for (int v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v]) //如果有一个连通分量没有被访问过
		{
			cout << "\n"; // 输出换行，分隔不同的连通分量
			BFSTraverseConnect(G, v, visited, ct); // 对未访问的联通分量的顶点v进行广度优先遍历
		}
	}

	delete[] visited; // 释放访问标志数组内存
}

//求按cost比较最小的最短路径（求单源最短路径：BP189 迪杰斯特拉算法）
void ShortestPathByCost_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D) //v0是起点，P是用来存最短路径当中的各个结点的前驱结点，D用来存源点到当前点的最短距离
{
	int n = G.vexnum;
	bool* visited = new bool[n];
	int i = 0, j = 0, v = 0, w = 0;
	double min = 0.0;
	for (v = 0; v < n; ++v)
	{
		visited[v] = false;
		D[v] = G.arcs[v0][v].cost; // 初始化花费数组
		P[v] = -1; // 初始化路径数组为-1，表示未找到路径
		if ((D[v] < Huge_Value) && (v != v0)) //这里的无穷大必须跟在初始化的时候定义的无穷大一样
			//系统内置了一个无穷大INFINITY，不要在这里用！它会大于你设定的Huge_Value，导致出现逻辑问题。全局中使用的无穷大务必统一！
		{
			P[v] = v0;
		}
	}
	D[v0] = 0; // 起点到起点的距离为0
	visited[v0] = true;// 初始化，v0顶点属于S集。开始主循环之后，每次求得v0到某个v顶点的最短路径，并将v加入到S集
	for (i = 1; i < n; ++i) //访问其余G.vexnum-1个顶点
	{
		min = Huge_Value;//当前所知离v0顶点的最近距离
		// 找到未访问的最小距离顶点
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && D[w] < min) //w顶点在V-S集中，并且w顶点离v0顶点比S集中现有的路径还要近
			{
				v = w;// 更新当前最短路径
				min = D[w];//更新当前最短距离
			}
		}
		if (min == Huge_Value)
		{
			break;//处理非连通图：所有路径全部遍历完，最短长度还是无穷大
		}
		visited[v] = true; // 标记为已访问
		// 更新距离和路径
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && min + G.arcs[v][w].cost < D[w])
			{
				D[w] = min + G.arcs[v][w].cost;//修改D[w]和P[w], w∈V-S
				P[w] = v;
			}//if
		}//for
	}
	delete[] visited; // 释放内存
}

//求按time比较最小的最短路径（求单源最短路径：BP189 迪杰斯特拉算法）
void ShortestPathByTime_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D) //v0是起点，P是用来存最短路径当中的各个结点的前驱结点，D用来存源点到当前点的最短距离
{
	int n = G.vexnum;
	bool* visited = new bool[n];
	int i = 0, j = 0, v = 0, w = 0;
	double min = 0.0;
	for (v = 0; v < n; ++v)
	{
		visited[v] = false;
		D[v] = G.arcs[v0][v].time; // 初始化花费数组
		P[v] = -1; // 初始化路径数组为-1，表示未找到路径
		if ((D[v] < Huge_Value) && (v != v0)) //这里的无穷大必须跟在初始化的时候定义的无穷大一样
			//系统内置了一个无穷大，不要在这里用！
		{
			P[v] = v0;
		}
	}
	D[v0] = 0; // 起点到起点的距离为0
	visited[v0] = true;// 初始化，v0顶点属于S集。开始主循环之后，每次求得v0到某个v顶点的最短路径，并将v加入到S集
	for (i = 1; i < n; ++i) //访问其余G.vexnum-1个顶点
	{
		min = Huge_Value;//当前所知离v0顶点的最近距离
		// 找到未访问的最小距离顶点
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && D[w] < min) //w顶点在V-S集中，并且w顶点离v0顶点比S集中现有的路径还要近
			{
				v = w;// 更新当前最短路径
				min = D[w];//更新当前最短距离
			}
		}
		if (min == Huge_Value)
		{
			break;//处理非连通图：所有路径全部遍历完，最短长度还是无穷大
		}
		visited[v] = true; // 标记为已访问
		// 更新距离和路径
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && min + G.arcs[v][w].time < D[w])
			{
				D[w] = min + G.arcs[v][w].time;//修改D[w]和P[w], w∈V-S
				P[w] = v;
			}//if
		}//for
	}
	delete[] visited; // 释放内存
}

//创建HTML文件
bool CreateHtml(const Graph& G, const double* D, const char* strFile, const City* ct, int head, int end, const int* P, int nCostType) {
	int i = 1;
	int code;
	int pre;
	int a = 0;
	int k;

	// 使用 std::ofstream 替代 FILE* 和 fopen
	std::ofstream fp2(strFile);
	if (!fp2) {
		std::cerr << "\n发生错误：无法生成HTML文件！" << std::endl;
		return false;
	}

	// 存储路径
	int b[20];
	int c[20];
	b[0] = end;
	code = end;
	while (P[code] != -1) {
		pre = P[code];
		b[i] = pre;
		c[i] = P[pre];
		i++;
		code = pre;
	}

	// 使用 std::ofstream 和流操作写入 HTML 内容
	fp2 << "<!DOCTYPE html>\n<html>\n<head>\n"
		<< "\t<style type='text/css'>\n"
		<< "\t\tbody, html{width: 100%;height:100%;margin:0;font-family:'微软雅黑';}\n"
		<< "\t\t#allmap{height:100%;width:100%;}\n"
		<< "\t</style>\n"
		<< "\t<script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script>\n"
		<< "\t<title>从 " << ct[head].city << " 到 " << ct[end].city << " 的" << ((nCostType == 1) ? "最小路费开销" : "最小时间花费") << "路径</title>\n"
		<< "</head>\n<body>\n"
		<< "\t<div id='allmap'></div>\n"
		<< "\t<script type='text/javascript'>\n"
		<< "\t\twindow.onload = function() {\n"
		<< "\t\t\talert('欢迎使用本网页！\\n\\n您可以在本页面中查看从城市 " << ct[head].city << " 到城市 " << ct[end].city << " 的" << ((nCostType == 1) ? "最小路费开销" : "最小时间花费") << "路径。\\n\\n点击地图上的标记以查看城市信息。\\n点击路径以查看详细信息。');\n"
		<< "\t\t};\n"
		<< "\t\tvar map = new BMap.Map('allmap');\n"
		<< "\t\tvar point = new BMap.Point(0, 0);\n"
		<< "\t\tmap.centerAndZoom(point, 2);\n"
		<< "\t\tmap.enableScrollWheelZoom(true);\n";

	// 显示城市信息
	for (k = i - 1; k >= 0; k--) {
		if (k == i - 1) {
			fp2 << "\t\tvar marker" << a << " = new BMap.Marker(new BMap.Point("
				<< std::fixed << std::setprecision(4) << ct[b[k]].longitude << ", "
				<< ct[b[k]].latitude << "));\n"
				<< "\t\tmap.addOverlay(marker" << a << ");\n"
				<< "\t\tvar infoWindow" << a << " = new BMap.InfoWindow(\"<p style='font-size:14px;'>【起点】<br/>国家：" << ct[b[k]].country << "<br/>城市：" << ct[b[k]].city << "</p>\");\n"
				<< "\t\tmarker" << a << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << a << "); });\n";
		}
		else if (k == 0) {
			fp2 << "\t\tvar marker" << a << " = new BMap.Marker(new BMap.Point("
				<< std::fixed << std::setprecision(4) << ct[b[k]].longitude << ", "
				<< ct[b[k]].latitude << "));\n"
				<< "\t\tmap.addOverlay(marker" << a << ");\n"
				<< "\t\tvar infoWindow" << a << " = new BMap.InfoWindow(\"<p style='font-size:14px;'>【终点】<br/>国家：" << ct[b[k]].country << "<br/>城市：" << ct[b[k]].city << "</p>\");\n"
				<< "\t\tmarker" << a << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << a << "); });\n";
		}
		else {
			fp2 << "\t\tvar marker" << a << " = new BMap.Marker(new BMap.Point("
				<< std::fixed << std::setprecision(4) << ct[b[k]].longitude << ", "
				<< ct[b[k]].latitude << "));\n"
				<< "\t\tmap.addOverlay(marker" << a << ");\n"
				<< "\t\tvar infoWindow" << a << " = new BMap.InfoWindow(\"<p style='font-size:14px;'>第 " << i - 1 - k << " 个途径点：<br/>国家：" << ct[b[k]].country << "<br/>城市：" << ct[b[k]].city << "</p>\");\n"
				<< "\t\tmarker" << a << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << a << "); });\n";
		}
		a++; // a是标记的序号
	}

	// 显示路径信息
	int m = 1;
	for (k = i - 2; k >= 0; k--) {
		fp2 << "    var contentString" << std::setw(2) << std::setfill('0') << m << " = '"
			<< "第 " << m << " 段路线："
			<< ct[b[k + 1]].city << ", " << ct[b[k + 1]].country << " --> "
			<< ct[b[k]].city << ", " << ct[b[k]].country
			<< "\\n交通方式：" << G.arcs[b[k]][b[k + 1]].transport
			<< "\\n时间花费：" << G.arcs[b[k]][b[k + 1]].time << " 小时"
			<< "\\n路费开销：$ " << std::fixed << std::setprecision(2) << G.arcs[b[k]][b[k + 1]].cost
			<< "\\n参考信息来源：" << G.arcs[b[k]][b[k + 1]].otherInfo << "';\n"
			<< "    var path" << m << " = new BMap.Polyline([\n"
			<< "        new BMap.Point(" << std::fixed << std::setprecision(4) << ct[b[k]].longitude << ", "
			<< std::fixed << std::setprecision(4) << ct[b[k]].latitude << "),\n"
			<< "        new BMap.Point(" << std::fixed << std::setprecision(4) << ct[b[k + 1]].longitude << ", "
			<< std::fixed << std::setprecision(4) << ct[b[k + 1]].latitude << ")\n"
			<< "    ], {strokeColor:'#18a45b', strokeWeight:8, strokeOpacity:0.8});\n"
			<< "    map.addOverlay(path" << m << ");\n"
			<< "    path" << m << ".addEventListener(\"click\", function() {\n"
			<< "        alert(contentString" << std::setw(2) << std::setfill('0') << m << ");\n"
			<< "    });\n";
		m++;
	}

	fp2 << "\t</script>\n</body>\n</html>\n";
	fp2.close();

	return true;
}

// 在Windows下用默认浏览器打开HTML文件
bool OpenHtmlInBrowser(string filePath)
{
#if defined(_WIN32) || defined(_WIN64)
	std::string command = "start \"\" \""; //在 Windows 系统中，文件名中包含空格时，调用 system 函数时需要将文件路径用引号括起来。这样可以确保路径被正确解析，即使其中包含空格
	command += filePath;
	command += "\"";
#elif defined(__linux__)
	std::string command = "xdg-open ";
	command += filePath;
#elif defined(__APPLE__)
	std::string command = "open ";
	command += filePath;
#else
	std::cerr << "Unsupported platform" << std::endl;
	return;

#endif
	system(command.c_str());
	return true;
}

// 在主函数中选择是否创建HTML文件，支持选择是否打开
void createHTMLInMian(Graph g, double* D, int depart, int dest, int* P, int nCostType)
{
	cout << "请问您是否需要生成可视化显示" << ((nCostType == 1) ? "最小路费开销" : "最小时间花费") << "对应路径的HTML文件？【是，请输入“Y”；否，请输入“N”】请输入：";
	string strHTML;
againHTML:
	cin >> strHTML;
	if (strHTML == "Y")
	{
		char strFile[256];
		string filename = "Graph_html\\";//使用相对路径
		filename += "从 ";
		filename += g.vertex[depart].city;
		filename += " 到 ";
		filename += g.vertex[dest].city;
		filename += " 的";
		filename += (nCostType == 1) ? "最小路费开销计划.html" : "最小时间花费计划.html";
		strcpy(strFile, filename.c_str());
		if (CreateHtml(g, D, strFile, g.vertex, depart, dest, P, nCostType))
		{
			cout << "\nHTML文件“" << filename << "”生成成功！";
			cout << "\n\n请问您是否想要打开HTML文件？【是，请输入“Y”；否，请输入“N”】请输入：";
			string strOpen;
		againHTMLOpen:
			cin >> strOpen;
			if (strOpen == "Y")
			{
				if (OpenHtmlInBrowser(filename))
				{
					cout << "\n在浏览器中打开HTML文件“" << filename << "”成功！\n\n";
				}
				else
				{
					cout << "\n在浏览器中打开HTML文件“" << filename << "”失败！\n\n";
				}
			}
			else if (strOpen == "N")
			{
				cout << "\n取消打开HTML文件！\n\n";
			}
			else
			{
				cout << "\n请按照要求输入：【是，请输入“Y”；否，请输入“N”】！请输入：";
				goto againHTMLOpen;
			}
		}
		else
		{
			cout << "HTML文件生成失败！\n";
		}
	}
	else if (strHTML == "N")
	{
		cout << "\n取消生成HTML文件！\n";
	}
	else
	{
		cout << "\n请按照要求输入：【是，请输入“Y”；否，请输入“N”】！请输入：";
		goto againHTML;
	}
}