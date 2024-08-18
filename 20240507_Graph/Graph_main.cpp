#include "manager.h"

/*数据文件格式：文本文件，可以用“记事本”或者“写字板”打开
WPS的Excel也可以打开（.csv被当作表格文件，相当于.xlsx），但是不能反映实质

1、cities.csv：世界各城市经纬度文件。
文件中每条记录的格式为（一行一条记录）：
国名,城市名,纬度,经度(换行\n）

2. routes.csv：城市之间来往的票价和时间权重。
文件中每条记录的格式为（一行一条记录）：
起点城市,终点城市,交通方式,通勤时间,成本,其他信息(换行\n）
*/

int main()/*C6262: 函数使用 constant_1 字节的堆栈：超过 /analyze:stacksize constant_2。 考虑将部分数据移到堆
解决方法见manager.h前面的注释*/
{
	//读取文件数据
	City* ct = nullptr;//城市顶点数组
	Route* route = nullptr;
	string strCityFile("cities.csv");
	string strRtFile("routes.csv");
	int nCtNum = 0, nRtNum = 0;
	//读取City数据
	ReadCityData(strCityFile, ct, nCtNum);
	//读取route数据
	ReadRouteData(strRtFile, route, nRtNum);
	//注意：以上步骤把城市的两个文件的数据读到了一个Route型的结构中，接下来将这些数据从Route中转移到Graph中

again:
	int nCostType = InitGraph();

	int i = 0, j = 0;
	Graph g;//图
	//初始化邻接矩阵
	AdjMatrix(g, nCtNum, ct, route, nRtNum, nCostType);

	while (true)
	{
		system("pause");
		system("cls");
		ShowMenu();//显示功能菜单

		int choice;
		cout << "\n请输入功能序号：";
		cin >> choice;
		getchar();//清空输入缓冲区
		system("cls");

		switch (choice)
		{
			//退出本程序
		case 0:
		{
			ExitSystem();
		}
		continue;

		//重新构建图
		case 1:
		{
			if (reInitGraph())
			{
				goto again;
			}
		}
		continue;

		//图的深度优先遍历
		case 2:
		{
			system("cls");
			cout << "图的深度优先遍历的结果是：\n";
			DFSTraverse(g, ct);
			//cout << "\b \b\b \b";//如果上面一行用的是DFSTraverse1(g, ct);，就需要加上最后这一组退格操作，删除最后的->
			cout << endl << endl;
		}
		continue;

		//图的广度优先遍历
		case 3:
		{
			system("cls");
			cout << "图的广度优先遍历的结果是：\n";
			BFSTraverse(g, ct);
			cout << endl << endl;
		}
		continue;

		//图的最短路径
		case 4:
		{
			cout << "图的深度优先遍历的结果是：\n";
			DFSTraverse(g, ct);
			cout << endl << endl;

			//最短路径
			string a, b;//起点、终点城市名
			string cityl;
			string city2;
			int depart, dest;
			//获取用户输入的城市，作为求从哪到哪的最短路径的输入
			do
			{
				cout << "\n请输入您所在的起点的城市名：";
				getline(cin, a);
				cityl = a;
				depart = Locate(cityl, ct, nCtNum);
				if (depart == -1)
				{
					cout << "未查找到您输入的起点城市，请重新输入！\n"; continue;
				}
				break;
			} while (true);
			do
			{
				cout << "\n请输入您想要前往的目的地的城市名：";
				getline(cin, b);
				if (b == a)
				{
					cout << "您输入的目的地城市与您输入的起点城市 " << a << " 相同，请重新输入！\n\n"; continue;
				}
				city2 = b;
				dest = Locate(city2, ct, nCtNum);
				if (dest == -1)
				{
					cout << "未查找到您输入的目的地城市，请重新输入！\n"; continue;
				}
				break;
			} while (true);

			//定义P和D，根据要求调用最短路径求解函数
			PathMatrix P = new int[g.vexnum];
			ShortDistTable D = new double[g.vexnum];

			switch (nCostType) {
			case 1:
			{
				ShortestPathByCost_DIJ(g, depart, P, D);
				break;
			}
			case 2:
			{
				ShortestPathByTime_DIJ(g, depart, P, D);
				break;
			}
			}

			stack<string> path;
			path.push(b);//终点城市入栈
			int nCurPos = P[dest];//终点城市的前驱的位置
			//path.push(g.vertex[dest].city);
			while (nCurPos != -1)
			{
				path.push(g.vertex[nCurPos].city);//最短路径中后面城市的前驱结点不断入栈
				nCurPos = P[nCurPos];//最短路径中的城市结点向前移动一个
			}

			switch (nCostType) {
			case 1:
			{
				if (D[dest] < Huge_Value)
				{
					cout << "\n从 " << a << " 到 " << b << " 的最小路费开销是：" << fixed << setprecision(2) << D[dest] << " 美元。\n";
					cout << "\n所求得的路费开销最小的路径为：\n" << a;
					path.pop();//起点已经输出过了，所以直接出栈。这里是为了避免在起点前面多输出一个“->”，所以这样处理了一下
					while (!path.empty())
					{
						cout << "->" << path.top();
						path.pop();
					}
					cout << "\n\n若要求得最小时间花费对应的路径，请返回主菜单，选择功能【1. 重新构建图】，选择【按时间最短】构建图！\n\n";

					// 创建HTML文件
					createHTMLInMian(g, D, depart, dest, P, nCostType);

					cout << "若要求得最小路费开销对应的路径，请返回主菜单，选择功能【1. 重新构建图】，选择【按票价最低】构建图！\n\n";
				}
				else
				{
					cout << "\n无法直接从" << a << " 到达 " << b << "！\n\n";
				}
				break;
			}
			case 2:
			{
				if (D[dest] < Huge_Value)
				{
					cout << "\n从 " << a << " 到 " << b << " 的最小时间花费是：" << D[dest] << " 小时。\n";
					cout << "\n所求得的时间花费最小的路径为：\n" << a;
					path.pop();
					while (!path.empty())
					{
						cout << "->" << path.top();
						path.pop();
					}
					cout << "\n\n若要求得最小路费开销对应的路径，请返回主菜单，选择功能【1. 重新构建图】，选择【按票价最低】构建图！\n\n";

					// 创建HTML文件
					createHTMLInMian(g, D, depart, dest, P, nCostType);

					cout << "若要求得最小路费开销对应的路径，请返回主菜单，选择功能【1. 重新构建图】，选择【按票价最低】构建图！\n\n";
				}
				else
				{
					cout << "\n无法直接从" << a << " 到达 " << b << "！\n\n";
				}
				break;
			}
			}
		}
		continue;

		default:
		{
			system("cls");
			cout << "没有序号为“" << choice << "”的功能，请重新输入！\n\n";
		}
		continue;

		}

		system("pause");
		return 0;
	}
}