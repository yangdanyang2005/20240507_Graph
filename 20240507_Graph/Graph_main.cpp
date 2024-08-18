#include "manager.h"

/*�����ļ���ʽ���ı��ļ��������á����±������ߡ�д�ְ塱��
WPS��ExcelҲ���Դ򿪣�.csv����������ļ����൱��.xlsx�������ǲ��ܷ�ӳʵ��

1��cities.csv����������о�γ���ļ���
�ļ���ÿ����¼�ĸ�ʽΪ��һ��һ����¼����
����,������,γ��,����(����\n��

2. routes.csv������֮��������Ʊ�ۺ�ʱ��Ȩ�ء�
�ļ���ÿ����¼�ĸ�ʽΪ��һ��һ����¼����
������,�յ����,��ͨ��ʽ,ͨ��ʱ��,�ɱ�,������Ϣ(����\n��
*/

int main()/*C6262: ����ʹ�� constant_1 �ֽڵĶ�ջ������ /analyze:stacksize constant_2�� ���ǽ����������Ƶ���
���������manager.hǰ���ע��*/
{
	//��ȡ�ļ�����
	City* ct = nullptr;//���ж�������
	Route* route = nullptr;
	string strCityFile("cities.csv");
	string strRtFile("routes.csv");
	int nCtNum = 0, nRtNum = 0;
	//��ȡCity����
	ReadCityData(strCityFile, ct, nCtNum);
	//��ȡroute����
	ReadRouteData(strRtFile, route, nRtNum);
	//ע�⣺���ϲ���ѳ��е������ļ������ݶ�����һ��Route�͵Ľṹ�У�����������Щ���ݴ�Route��ת�Ƶ�Graph��

again:
	int nCostType = InitGraph();

	int i = 0, j = 0;
	Graph g;//ͼ
	//��ʼ���ڽӾ���
	AdjMatrix(g, nCtNum, ct, route, nRtNum, nCostType);

	while (true)
	{
		system("pause");
		system("cls");
		ShowMenu();//��ʾ���ܲ˵�

		int choice;
		cout << "\n�����빦����ţ�";
		cin >> choice;
		getchar();//������뻺����
		system("cls");

		switch (choice)
		{
			//�˳�������
		case 0:
		{
			ExitSystem();
		}
		continue;

		//���¹���ͼ
		case 1:
		{
			if (reInitGraph())
			{
				goto again;
			}
		}
		continue;

		//ͼ��������ȱ���
		case 2:
		{
			system("cls");
			cout << "ͼ��������ȱ����Ľ���ǣ�\n";
			DFSTraverse(g, ct);
			//cout << "\b \b\b \b";//�������һ���õ���DFSTraverse1(g, ct);������Ҫ���������һ���˸������ɾ������->
			cout << endl << endl;
		}
		continue;

		//ͼ�Ĺ�����ȱ���
		case 3:
		{
			system("cls");
			cout << "ͼ�Ĺ�����ȱ����Ľ���ǣ�\n";
			BFSTraverse(g, ct);
			cout << endl << endl;
		}
		continue;

		//ͼ�����·��
		case 4:
		{
			cout << "ͼ��������ȱ����Ľ���ǣ�\n";
			DFSTraverse(g, ct);
			cout << endl << endl;

			//���·��
			string a, b;//��㡢�յ������
			string cityl;
			string city2;
			int depart, dest;
			//��ȡ�û�����ĳ��У���Ϊ����ĵ��ĵ����·��������
			do
			{
				cout << "\n�����������ڵ����ĳ�������";
				getline(cin, a);
				cityl = a;
				depart = Locate(cityl, ct, nCtNum);
				if (depart == -1)
				{
					cout << "δ���ҵ�������������У����������룡\n"; continue;
				}
				break;
			} while (true);
			do
			{
				cout << "\n����������Ҫǰ����Ŀ�ĵصĳ�������";
				getline(cin, b);
				if (b == a)
				{
					cout << "�������Ŀ�ĵس������������������ " << a << " ��ͬ�����������룡\n\n"; continue;
				}
				city2 = b;
				dest = Locate(city2, ct, nCtNum);
				if (dest == -1)
				{
					cout << "δ���ҵ��������Ŀ�ĵس��У����������룡\n"; continue;
				}
				break;
			} while (true);

			//����P��D������Ҫ��������·����⺯��
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
			path.push(b);//�յ������ջ
			int nCurPos = P[dest];//�յ���е�ǰ����λ��
			//path.push(g.vertex[dest].city);
			while (nCurPos != -1)
			{
				path.push(g.vertex[nCurPos].city);//���·���к�����е�ǰ����㲻����ջ
				nCurPos = P[nCurPos];//���·���еĳ��н����ǰ�ƶ�һ��
			}

			switch (nCostType) {
			case 1:
			{
				if (D[dest] < Huge_Value)
				{
					cout << "\n�� " << a << " �� " << b << " ����С·�ѿ����ǣ�" << fixed << setprecision(2) << D[dest] << " ��Ԫ��\n";
					cout << "\n����õ�·�ѿ�����С��·��Ϊ��\n" << a;
					path.pop();//����Ѿ�������ˣ�����ֱ�ӳ�ջ��������Ϊ�˱��������ǰ������һ����->������������������һ��
					while (!path.empty())
					{
						cout << "->" << path.top();
						path.pop();
					}
					cout << "\n\n��Ҫ�����Сʱ�仨�Ѷ�Ӧ��·�����뷵�����˵���ѡ���ܡ�1. ���¹���ͼ����ѡ�񡾰�ʱ����̡�����ͼ��\n\n";

					// ����HTML�ļ�
					createHTMLInMian(g, D, depart, dest, P, nCostType);

					cout << "��Ҫ�����С·�ѿ�����Ӧ��·�����뷵�����˵���ѡ���ܡ�1. ���¹���ͼ����ѡ�񡾰�Ʊ����͡�����ͼ��\n\n";
				}
				else
				{
					cout << "\n�޷�ֱ�Ӵ�" << a << " ���� " << b << "��\n\n";
				}
				break;
			}
			case 2:
			{
				if (D[dest] < Huge_Value)
				{
					cout << "\n�� " << a << " �� " << b << " ����Сʱ�仨���ǣ�" << D[dest] << " Сʱ��\n";
					cout << "\n����õ�ʱ�仨����С��·��Ϊ��\n" << a;
					path.pop();
					while (!path.empty())
					{
						cout << "->" << path.top();
						path.pop();
					}
					cout << "\n\n��Ҫ�����С·�ѿ�����Ӧ��·�����뷵�����˵���ѡ���ܡ�1. ���¹���ͼ����ѡ�񡾰�Ʊ����͡�����ͼ��\n\n";

					// ����HTML�ļ�
					createHTMLInMian(g, D, depart, dest, P, nCostType);

					cout << "��Ҫ�����С·�ѿ�����Ӧ��·�����뷵�����˵���ѡ���ܡ�1. ���¹���ͼ����ѡ�񡾰�Ʊ����͡�����ͼ��\n\n";
				}
				else
				{
					cout << "\n�޷�ֱ�Ӵ�" << a << " ���� " << b << "��\n\n";
				}
				break;
			}
			}
		}
		continue;

		default:
		{
			system("cls");
			cout << "û�����Ϊ��" << choice << "���Ĺ��ܣ����������룡\n\n";
		}
		continue;

		}

		system("pause");
		return 0;
	}
}