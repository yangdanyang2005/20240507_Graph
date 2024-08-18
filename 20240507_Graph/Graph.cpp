#include"manager.h"

//��ͼ���ҵ���Ӧ����
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

//�ӳ�������������ҵ���Ӧ����
int Locate(const string& origin, City* ct, int nCtNum)
{
	for (int i = 0; i < nCtNum; i++)
	{
		if (origin == ct[i].city/*����дct->city*/)
		{
			return i;
		}
	}
	return -1;//���������ұ��˶�û�ҵ�
}

//�ڽӾ���ṹ�£��ҵ�G��V�ĵ�һ���ڽӵ�
inline int firstAdivex(Graph G, int v)//���ڽ�����Ƚ϶࣬ʹ�����������������Ĵ���ֱ�ӿ������ǵ��ú��������ӿ������������
{
	for (int w = 0; w < G.vexnum; w++)
	{
		if (w == v)continue;
		//N��һ����ֵ����cost<N������[v][w]���������ڣ�w��v��һ���ڽӵ�
		//if����һ����һ�γ�����һ����������v������ĵ�һ���������ڽӵĶ���Ҳ��
		if (G.arcs[v][w].cost < N)
			return w;
	}
	return -1;//����-1����v�������ڽӵ�
}

//��vw����һ�����������Ӧ�Ķ��㣬Ҳ��v�������w����һ������
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

//��ȡCity����
bool ReadCityData(string strFileName, City*& ct, int& nCtNum)
{
	char cBuffer[1024];
	nCtNum = 0;
	//��ȡ��·��������
	ifstream inFile(strFileName.c_str(), ios::in);
	//int nRtNum=0;
	while (inFile.getline(cBuffer, 1024))
	{
		nCtNum++;
	}
	inFile.close();
	//��ȡ�ļ�����
	FILE* fp;
	fp = fopen(strFileName.c_str(), "r");
	/*���·����
	�ڵ���״̬�£��ᵽ·��"D:\c_language_code\whu_2_data_structure_wujianwei\20240507_Graph\20240507_Graph"�����ң�
	�ڿ�ִ�г����У��ص�.exe�ļ�ͬ��Ŀ¼����*/
	if (!fp)
	{
		cerr << "cities.csv open ERRaOR !\n\n";//�ļ���ʧ��
		exit(-1);
	}
	char ch = '\0';
	double f = 0.0;
	int i = 0;
	ct = new City[nCtNum];
	while (!feof(fp))
	{
		/*fgetc �� C ���Ա�׼���е�һ�����������ڴ�ָ�����ļ����ж�ȡ��һ�����ַ���
		����������ַ���ȡ�����Ļ�����ͨ���������ַ��ش����ļ����ݡ�

		������ԭ�Ͷ����� stdio.h ͷ�ļ��У�
		int fgetc(FILE *stream);

		stream������һ��ָ�� FILE �����ָ�룬��ʾҪ���ж�ȡ�ַ�������������ͨ����ͨ�� fopen �����򿪵��ļ���

		fgetc �����᷵�ض�ȡ�����ַ��� ASCII ֵ��һ�� int ���͵�ֵ����
		��������ļ�ĩβ���������򷵻� EOF��End Of File��һ������ĳ�����ͨ���� -1����
		*/
		for (ch = fgetc(fp); ch != ','; ch = fgetc(fp))
		{
			ct[i].country += ch;//��ȡ��������
		}
		ch = fgetc(fp);
		for (; ch != ','; ch = fgetc(fp))
		{
			ct[i].city += ch;//��ȡ��������
		}
		fscanf(fp, "%lf,", &f);//���ļ�ָ��fpָ����ļ��У���ȡdouble�͵�γ�ȣ�������double�͵ı���f�С�ע��������һ����,��
		/*fscanf
		�������ܣ�
		fscanf��C�����е�һ����׼�⺯�������ڴ�ָ������������ͨ�����ļ����ж�ȡ��ʽ�����롣
		��������� scanf ���ļ��汾��������ļ��ж�ȡ���ݣ������Ǵӱ�׼���루ͨ���Ǽ��̣���ȡ��

		������ԭ�ͣ�
		������ stdio.h ͷ�ļ��У�
		int fscanf(FILE *stream, const char *format, ...);

		����˵����
		stream������һ��ָ�� FILE �����ָ�룬��ʾҪ���ж�ȡ���ݵ�����������ͨ����ͨ�� fopen �����򿪵��ļ���
		format������һ����ʽ�ַ�����ָ����Ҫ��ȡ�����������Լ���ν��н��������� scanf �����еĸ�ʽ�ַ�����ͬ��
		...�����ǿɱ�����б���Ӧ�� format �ַ�����ָ����Ҫ��ȡ�ı����ĵ�ַ��

		����ֵ��
		fscanf �����᷵�سɹ���ȡ����ֵ�����������������������ļ�ĩβ���������򷵻� EOF��ͨ���� -1����*/
		ct[i].latitude = f;//γ�ȴ�������
		fscanf(fp, "%lf\n", &f);//���ļ�ָ��fpָ����ļ��У���ȡdouble�͵ľ��ȣ�������double�͵ı���f��
		ct[i].longitude = f;//���ȴ�������
		i++;//��ȡ��һ�����ж���
	}
	fclose(fp);
	return true;
}

//��ȡroute����
bool ReadRouteData(string strFileName, Route*& route, int& nRtNum)
{
	char cBuffer[1024];
	//��ȡ�������ݸ���
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
		cerr << "routes.csv open ERROR !\n\n";//�ļ���ʧ��
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

//��ʼ���ڽӾ��� BP162
bool AdjMatrix(Graph& g, int nCtNum, City* ct, Route* route, int nRtNum, int nCostType)
{
	int i = 0, j = 0;
	g.arcnum = nCtNum * nCtNum;//ͼ�Ķ�����
	g.vexnum = nCtNum;//ͼ�ı���
	g.vertex = ct;//���ж�������
	g.arcs = new Arc * [nCtNum];
	for (i = 0; i < nCtNum; i++)
	{
		g.arcs[i] = new Arc[nCtNum];
	}
	for (i = 0; i < nCtNum; i++)
	{
		for (j = 0; j < nCtNum; j++)
		{
			if (i == j)//����ij������ij�Ļ���
			{
				g.arcs[i][j].cost = 0;
				g.arcs[i][j].time = 0;
			}
			else//����ij����������Ļ��ѣ���ʼ��Ϊ����󣬼�N��
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
		Locate�����ڣ��������ж������飬������û�и����������һ����
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
		/*ʵ���ϣ����´���������൱�ڣ���route[i]�Ķ�Ӧ��Ա�������ҵ�ĳ�����ж���ĸ������BP4������Ϣ������ͼ��
		g.arcs[origin][destination].cost = route[i].cost;
		g.arcs[origin][destination].time = route[i].time;
		���ǲ�Ҫ�����������������Ĵ��룡��Ϊ���ļ��������������������������ͬ����������֮���ֱ�����ӵ�·��Ҳ����ڲ�ͬ��ʱ�����·�ѵ�Ȩ�أ�
		���������if�����ж���Ϊ��ȷ���ڽӾ����д洢���Ǵ���㵽�յ����̳ɱ���ʱ�䡣
		�������������жϣ����ܻᵼ�����յ�·��������̵ġ�*/
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

//����ͨͼG�������������������������������������firstAdivex��nextAdivex����д�� BP169
void DFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[])
{
	// �Ӷ���v�����������������������ͨͼ G
	visited[v] = true;//�����������������һ���Ѿ������ʹ��ˣ������棩
	int w = 0;/*���д����ʼ������`w`Ϊ0���������`w`�����洢����`v`���ڽӶ��㡣
	��ʼ��Ϊ0ֻ��һ������ʼֵ������ʵ��ֵ������Ҫ����Ϊ�ڽ���ѭ��֮ǰ`w`��ֵ�ᱻ`firstAdivex`�����ķ���ֵ���ǡ�*/
	cout << ct[v].city;//������ڷ�����
	for (w = firstAdivex(G, v)/*��ʼ��`w`Ϊ�붥��`v`�����ĵ�һ������*/;
		w != -1;/*ֻҪ`nextAdivex`�������صĲ��� - 1��ͨ����ʾû�и�����ڽӶ��㣩��ѭ���ͻ����*/
		w = nextAdivex(G, v, w)/*����`w`Ϊ��һ���ڽӶ���*/)
	{
		if (!visited[w])
			/*��鶥��`w`�Ƿ��Ѿ������ʹ�����������`visited`�������ÿ�������Ƿ񱻷��ʹ���
			���`visited[w]`��`false`��˵������`w`��û�б����ʣ���ô�Ϳ��Խ���if����ڲ����з��ʡ�
			������������һ�������ʱ�����е�`v`���ڽӶ���`w`�������ʹ��ˣ�������������֧�����ԾͿ��Ա�֤���һ������Ķ����ĩβ�����"->"*/
		{
			cout << "->"; //�ŵ�������Ա�֤���һ������Ķ����ĩβ�����"->"��ע��˼·���������룺��Ҫ������һ����ʱ�򣬲���Ҫ��ӡ��"->"��					
			DFSTraverseConnect(G, w, visited, ct);//�ݹ����
			/*�ݹ���ã��Զ���`w`����������ȱ�����ͨ���ݹ飬�㷨���Ա���ͼ���붥��`v`����������δ���ʶ���*/
		}
	}
} // DFS���Ӷ���`v`��ʼ���ݹ�ر���ͼ`G`�е����ж��㣬ȷ��ÿ������ֻ������һ�Σ�����ӡ�����������з��ʶ����˳��
//Ҫʵ�ֱ�֤���һ������Ķ����ĩβ�����"->"������һ�ַ������£���Ȼ�õ�����������߼��ķ�����
void DFSTraverseConnect1(Graph& G, int v, bool*& visited, City ct[])
{
	// �Ӷ���v�����������������������ͨͼ G
	visited[v] = true;//�����������������һ���Ѿ������ʹ��ˣ������棩
	int w = 0;/*���д����ʼ������`w`Ϊ0���������`w`�����洢����`v`���ڽӶ��㡣
	��ʼ��Ϊ0ֻ��һ������ʼֵ������ʵ��ֵ������Ҫ����Ϊ�ڽ���ѭ��֮ǰ`w`��ֵ�ᱻ`firstAdivex`�����ķ���ֵ���ǡ�*/
	cout << ct[v].city << "->";//������ڷ�����
	for (w = firstAdivex(G, v)/*��ʼ��`w`Ϊ�붥��`v`�����ĵ�һ������*/;
		w != -1;/*ֻҪ`nextAdivex`�������صĲ��� - 1��ͨ����ʾû�и�����ڽӶ��㣩��ѭ���ͻ����*/
		w = nextAdivex(G, v, w)/*����`w`Ϊ��һ���ڽӶ���*/)
	{
		if (!visited[w])
			/*��鶥��`w`�Ƿ��Ѿ������ʹ�����������`visited`�������ÿ�������Ƿ񱻷��ʹ���
			���`visited[w]`��`false`��˵������`w`��û�б����ʣ���ô�Ϳ��Խ���if����ڲ����з��ʡ�
			������������һ�������ʱ�����е�`v`���ڽӶ���`w`�������ʹ��ˣ�������������֧�����ԾͿ��Ա�֤���һ������Ķ����ĩβ�����"->"*/
		{
			DFSTraverseConnect1(G, w, visited, ct);//�ݹ����
			/*�ݹ���ã��Զ���`w`����������ȱ�����ͨ���ݹ飬�㷨���Ա���ͼ���붥��`v`����������δ���ʶ���*/
		}
	}
} // DFS���Ӷ���`v`��ʼ���ݹ�ر���ͼ`G`�е����ж��㣬ȷ��ÿ������ֻ������һ�Σ�����ӡ�����������з��ʶ����˳��

//�Է���ͨͼG�����������������
void DFSTraverse(Graph& G, City ct[])
{

	int v = 0;
	bool* visited = new bool[G.vexnum];
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = false; // ���ʱ�־�����ʼ��
	for (v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v])
		{
			cout << "\n";
			//DFS(G, v, visited, ct);
			DFSTraverseConnect(G, v, visited, ct);//��ͨͼ�ı���
		}
	}
}
//Ҫʵ�ֱ�֤���һ������Ķ����ĩβ�����"->"������һ�ַ������£���Ȼ�õ�����������߼��ķ�����
void DFSTraverse1(Graph& G, City ct[])
{

	int v = 0;
	bool* visited = new bool[G.vexnum];
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = false; // ���ʱ�־�����ʼ��
	for (v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v])
		{
			cout << "\b \b\b \b \n";//\b�൱�ڹ�����һ�񣬿ո��ǽ�ԭ�����ַ������ǵ���ע�⣺���������ĩβ����ո�
			//DFS(G, v, visited, ct);
			DFSTraverseConnect1(G, v, visited, ct);//��ͨͼ�ı���
		}
	}
}

//��ͨͼ�Ĺ�����ȱ���������������������������firstAdivex��nextAdivex����д�� BP170
void BFSTraverseConnect(Graph& G, int v, bool*& visited, City ct[])
{
	queue<int> queue; // ʹ�ö��д洢�����ʵĶ���
	/*�ڹ�����ȱ�����ʹ�ö��У��ܹ���֤�����ǰ��մӽ���Զ��˳�򱻷��ʵ�*/
	visited[v] = true; // ��Ǹ���ͨ���������Ϊ�ѷ���
	queue.push(v); // �����������
	while (!queue.empty())
	{
		int vertex = queue.front(); // ��ȡ���е�ͷ��Ԫ�أ��⽫����һ���������ʵĶ���
		queue.pop(); // �����е�ͷ��Ԫ�ص���
		cout << ct[vertex].city; // ���ʶ���
		// ���������ڽӶ���
		for (int w = firstAdivex(G, vertex); w != -1; w = nextAdivex(G, vertex, w)) //��δ����������`vertex`�������ڽӶ��㡣`firstAdivex`��������`vertex`�ĵ�һ���ڽӶ��㣬`nextAdivex`��������`vertex`����һ���ڽӶ��㣨�����`w`��
		{
			if (!visited[w])
			{
				queue.push(w); // ���`w`δ�����ʣ����������У��Ա��������
				visited[w] = true; // ���Ϊ�ѷ���
			}
		}
		// ȷ���ڷ�����һ������֮ǰ���"->"���������һ������
		if (!queue.empty()) //��������л��ж���
		{
			cout << "->";//���������һ������֮ǰ��ӡ"->"
		}
	}
}//BFS ���������У����б�֤�˶���ķ���˳���������ȳ���FIFO��������ζ���ȱ�������еĶ����ȱ����ʡ����������ܹ�ʵ�ִ���㿪ʼ�����������չ�Ĺ�����ȱ���

//�Է���ͨͼG�Ĺ��������������
void BFSTraverse(Graph& G, City ct[])
{
	bool* visited = new bool[G.vexnum];
	for (int v = 0; v < G.vexnum; ++v)
	{
		visited[v] = false; // ��ʼ�����ʱ�־����
	}
	for (int v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v]) //�����һ����ͨ����û�б����ʹ�
		{
			cout << "\n"; // ������У��ָ���ͬ����ͨ����
			BFSTraverseConnect(G, v, visited, ct); // ��δ���ʵ���ͨ�����Ķ���v���й�����ȱ���
		}
	}

	delete[] visited; // �ͷŷ��ʱ�־�����ڴ�
}

//��cost�Ƚ���С�����·������Դ���·����BP189 �Ͻ�˹�����㷨��
void ShortestPathByCost_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D) //v0����㣬P�����������·�����еĸ�������ǰ����㣬D������Դ�㵽��ǰ�����̾���
{
	int n = G.vexnum;
	bool* visited = new bool[n];
	int i = 0, j = 0, v = 0, w = 0;
	double min = 0.0;
	for (v = 0; v < n; ++v)
	{
		visited[v] = false;
		D[v] = G.arcs[v0][v].cost; // ��ʼ����������
		P[v] = -1; // ��ʼ��·������Ϊ-1����ʾδ�ҵ�·��
		if ((D[v] < Huge_Value) && (v != v0)) //���������������ڳ�ʼ����ʱ����������һ��
			//ϵͳ������һ�������INFINITY����Ҫ�������ã�����������趨��Huge_Value�����³����߼����⡣ȫ����ʹ�õ���������ͳһ��
		{
			P[v] = v0;
		}
	}
	D[v0] = 0; // ��㵽���ľ���Ϊ0
	visited[v0] = true;// ��ʼ����v0��������S������ʼ��ѭ��֮��ÿ�����v0��ĳ��v��������·��������v���뵽S��
	for (i = 1; i < n; ++i) //��������G.vexnum-1������
	{
		min = Huge_Value;//��ǰ��֪��v0������������
		// �ҵ�δ���ʵ���С���붥��
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && D[w] < min) //w������V-S���У�����w������v0�����S�������е�·����Ҫ��
			{
				v = w;// ���µ�ǰ���·��
				min = D[w];//���µ�ǰ��̾���
			}
		}
		if (min == Huge_Value)
		{
			break;//�������ͨͼ������·��ȫ�������꣬��̳��Ȼ��������
		}
		visited[v] = true; // ���Ϊ�ѷ���
		// ���¾����·��
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && min + G.arcs[v][w].cost < D[w])
			{
				D[w] = min + G.arcs[v][w].cost;//�޸�D[w]��P[w], w��V-S
				P[w] = v;
			}//if
		}//for
	}
	delete[] visited; // �ͷ��ڴ�
}

//��time�Ƚ���С�����·������Դ���·����BP189 �Ͻ�˹�����㷨��
void ShortestPathByTime_DIJ(Graph G, int v0, PathMatrix& P, ShortDistTable& D) //v0����㣬P�����������·�����еĸ�������ǰ����㣬D������Դ�㵽��ǰ�����̾���
{
	int n = G.vexnum;
	bool* visited = new bool[n];
	int i = 0, j = 0, v = 0, w = 0;
	double min = 0.0;
	for (v = 0; v < n; ++v)
	{
		visited[v] = false;
		D[v] = G.arcs[v0][v].time; // ��ʼ����������
		P[v] = -1; // ��ʼ��·������Ϊ-1����ʾδ�ҵ�·��
		if ((D[v] < Huge_Value) && (v != v0)) //���������������ڳ�ʼ����ʱ����������һ��
			//ϵͳ������һ������󣬲�Ҫ�������ã�
		{
			P[v] = v0;
		}
	}
	D[v0] = 0; // ��㵽���ľ���Ϊ0
	visited[v0] = true;// ��ʼ����v0��������S������ʼ��ѭ��֮��ÿ�����v0��ĳ��v��������·��������v���뵽S��
	for (i = 1; i < n; ++i) //��������G.vexnum-1������
	{
		min = Huge_Value;//��ǰ��֪��v0������������
		// �ҵ�δ���ʵ���С���붥��
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && D[w] < min) //w������V-S���У�����w������v0�����S�������е�·����Ҫ��
			{
				v = w;// ���µ�ǰ���·��
				min = D[w];//���µ�ǰ��̾���
			}
		}
		if (min == Huge_Value)
		{
			break;//�������ͨͼ������·��ȫ�������꣬��̳��Ȼ��������
		}
		visited[v] = true; // ���Ϊ�ѷ���
		// ���¾����·��
		for (w = 0; w < n; ++w)
		{
			if (!visited[w] && min + G.arcs[v][w].time < D[w])
			{
				D[w] = min + G.arcs[v][w].time;//�޸�D[w]��P[w], w��V-S
				P[w] = v;
			}//if
		}//for
	}
	delete[] visited; // �ͷ��ڴ�
}

//����HTML�ļ�
bool CreateHtml(const Graph& G, const double* D, const char* strFile, const City* ct, int head, int end, const int* P, int nCostType) {
	int i = 1;
	int code;
	int pre;
	int a = 0;
	int k;

	// ʹ�� std::ofstream ��� FILE* �� fopen
	std::ofstream fp2(strFile);
	if (!fp2) {
		std::cerr << "\n���������޷�����HTML�ļ���" << std::endl;
		return false;
	}

	// �洢·��
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

	// ʹ�� std::ofstream ��������д�� HTML ����
	fp2 << "<!DOCTYPE html>\n<html>\n<head>\n"
		<< "\t<style type='text/css'>\n"
		<< "\t\tbody, html{width: 100%;height:100%;margin:0;font-family:'΢���ź�';}\n"
		<< "\t\t#allmap{height:100%;width:100%;}\n"
		<< "\t</style>\n"
		<< "\t<script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script>\n"
		<< "\t<title>�� " << ct[head].city << " �� " << ct[end].city << " ��" << ((nCostType == 1) ? "��С·�ѿ���" : "��Сʱ�仨��") << "·��</title>\n"
		<< "</head>\n<body>\n"
		<< "\t<div id='allmap'></div>\n"
		<< "\t<script type='text/javascript'>\n"
		<< "\t\twindow.onload = function() {\n"
		<< "\t\t\talert('��ӭʹ�ñ���ҳ��\\n\\n�������ڱ�ҳ���в鿴�ӳ��� " << ct[head].city << " ������ " << ct[end].city << " ��" << ((nCostType == 1) ? "��С·�ѿ���" : "��Сʱ�仨��") << "·����\\n\\n�����ͼ�ϵı���Բ鿴������Ϣ��\\n���·���Բ鿴��ϸ��Ϣ��');\n"
		<< "\t\t};\n"
		<< "\t\tvar map = new BMap.Map('allmap');\n"
		<< "\t\tvar point = new BMap.Point(0, 0);\n"
		<< "\t\tmap.centerAndZoom(point, 2);\n"
		<< "\t\tmap.enableScrollWheelZoom(true);\n";

	// ��ʾ������Ϣ
	for (k = i - 1; k >= 0; k--) {
		if (k == i - 1) {
			fp2 << "\t\tvar marker" << a << " = new BMap.Marker(new BMap.Point("
				<< std::fixed << std::setprecision(4) << ct[b[k]].longitude << ", "
				<< ct[b[k]].latitude << "));\n"
				<< "\t\tmap.addOverlay(marker" << a << ");\n"
				<< "\t\tvar infoWindow" << a << " = new BMap.InfoWindow(\"<p style='font-size:14px;'>����㡿<br/>���ң�" << ct[b[k]].country << "<br/>���У�" << ct[b[k]].city << "</p>\");\n"
				<< "\t\tmarker" << a << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << a << "); });\n";
		}
		else if (k == 0) {
			fp2 << "\t\tvar marker" << a << " = new BMap.Marker(new BMap.Point("
				<< std::fixed << std::setprecision(4) << ct[b[k]].longitude << ", "
				<< ct[b[k]].latitude << "));\n"
				<< "\t\tmap.addOverlay(marker" << a << ");\n"
				<< "\t\tvar infoWindow" << a << " = new BMap.InfoWindow(\"<p style='font-size:14px;'>���յ㡿<br/>���ң�" << ct[b[k]].country << "<br/>���У�" << ct[b[k]].city << "</p>\");\n"
				<< "\t\tmarker" << a << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << a << "); });\n";
		}
		else {
			fp2 << "\t\tvar marker" << a << " = new BMap.Marker(new BMap.Point("
				<< std::fixed << std::setprecision(4) << ct[b[k]].longitude << ", "
				<< ct[b[k]].latitude << "));\n"
				<< "\t\tmap.addOverlay(marker" << a << ");\n"
				<< "\t\tvar infoWindow" << a << " = new BMap.InfoWindow(\"<p style='font-size:14px;'>�� " << i - 1 - k << " ��;���㣺<br/>���ң�" << ct[b[k]].country << "<br/>���У�" << ct[b[k]].city << "</p>\");\n"
				<< "\t\tmarker" << a << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << a << "); });\n";
		}
		a++; // a�Ǳ�ǵ����
	}

	// ��ʾ·����Ϣ
	int m = 1;
	for (k = i - 2; k >= 0; k--) {
		fp2 << "    var contentString" << std::setw(2) << std::setfill('0') << m << " = '"
			<< "�� " << m << " ��·�ߣ�"
			<< ct[b[k + 1]].city << ", " << ct[b[k + 1]].country << " --> "
			<< ct[b[k]].city << ", " << ct[b[k]].country
			<< "\\n��ͨ��ʽ��" << G.arcs[b[k]][b[k + 1]].transport
			<< "\\nʱ�仨�ѣ�" << G.arcs[b[k]][b[k + 1]].time << " Сʱ"
			<< "\\n·�ѿ�����$ " << std::fixed << std::setprecision(2) << G.arcs[b[k]][b[k + 1]].cost
			<< "\\n�ο���Ϣ��Դ��" << G.arcs[b[k]][b[k + 1]].otherInfo << "';\n"
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

// ��Windows����Ĭ���������HTML�ļ�
bool OpenHtmlInBrowser(string filePath)
{
#if defined(_WIN32) || defined(_WIN64)
	std::string command = "start \"\" \""; //�� Windows ϵͳ�У��ļ����а����ո�ʱ������ system ����ʱ��Ҫ���ļ�·������������������������ȷ��·������ȷ��������ʹ���а����ո�
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

// ����������ѡ���Ƿ񴴽�HTML�ļ���֧��ѡ���Ƿ��
void createHTMLInMian(Graph g, double* D, int depart, int dest, int* P, int nCostType)
{
	cout << "�������Ƿ���Ҫ���ɿ��ӻ���ʾ" << ((nCostType == 1) ? "��С·�ѿ���" : "��Сʱ�仨��") << "��Ӧ·����HTML�ļ������ǣ������롰Y�����������롰N���������룺";
	string strHTML;
againHTML:
	cin >> strHTML;
	if (strHTML == "Y")
	{
		char strFile[256];
		string filename = "Graph_html\\";//ʹ�����·��
		filename += "�� ";
		filename += g.vertex[depart].city;
		filename += " �� ";
		filename += g.vertex[dest].city;
		filename += " ��";
		filename += (nCostType == 1) ? "��С·�ѿ����ƻ�.html" : "��Сʱ�仨�Ѽƻ�.html";
		strcpy(strFile, filename.c_str());
		if (CreateHtml(g, D, strFile, g.vertex, depart, dest, P, nCostType))
		{
			cout << "\nHTML�ļ���" << filename << "�����ɳɹ���";
			cout << "\n\n�������Ƿ���Ҫ��HTML�ļ������ǣ������롰Y�����������롰N���������룺";
			string strOpen;
		againHTMLOpen:
			cin >> strOpen;
			if (strOpen == "Y")
			{
				if (OpenHtmlInBrowser(filename))
				{
					cout << "\n��������д�HTML�ļ���" << filename << "���ɹ���\n\n";
				}
				else
				{
					cout << "\n��������д�HTML�ļ���" << filename << "��ʧ�ܣ�\n\n";
				}
			}
			else if (strOpen == "N")
			{
				cout << "\nȡ����HTML�ļ���\n\n";
			}
			else
			{
				cout << "\n�밴��Ҫ�����룺���ǣ������롰Y�����������롰N�����������룺";
				goto againHTMLOpen;
			}
		}
		else
		{
			cout << "HTML�ļ�����ʧ�ܣ�\n";
		}
	}
	else if (strHTML == "N")
	{
		cout << "\nȡ������HTML�ļ���\n";
	}
	else
	{
		cout << "\n�밴��Ҫ�����룺���ǣ������롰Y�����������롰N�����������룺";
		goto againHTML;
	}
}