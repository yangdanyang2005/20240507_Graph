#include "manager.h"

int InitGraph()
{
	char ch[64]; char chr = '0';
	do
	{
		system("cls");
		cout << "****************************************************************************************" << endl;
		cout << "*****                                  【欢迎页】                                  *****" << endl;
		cout << "****************************************************************************************" << endl;
		cout << "*****                       数据结构实习（四）：图与最短路径                       *****" << endl;
		cout << "*****                                 姓名：杨丹阳                                 *****" << endl;
		cout << "*****                    班级：武汉大学 遥感信息工程学院 2305班                    *****" << endl;
		cout << "*****                             学号：2023302131259                              *****" << endl;
		cout << "*****                             指导老师：邬建伟老师                             *****" << endl;
		cout << "****************************************************************************************" << endl;
		cout << "*****                               欢迎使用本程序！                               *****" << endl;
		cout << "*****               本程序可以实现图的构建、遍历、求最短路径等功能。               *****" << endl;
		cout << "*****                    在自由测试开始之前，请先完成图的构建。                    *****" << endl;
		cout << "****************************************************************************************" << endl;
		cout << "\n请选择构建图的标准：【C：按票价最低  T：按时间最短】\n请输入：";
		//while ((chr = getchar()) != '\n' && chr != EOF);//把换行符读取掉，清空输入缓冲区
		scanf("%s", ch);//不要用getchar，它无法把后面的一个换行符读走
		int nCmpC = strcmp("C", ch);
		int nCmpT = strcmp("T", ch);
		/*Return Value of strcmp:
		The return value for each of these functions indicates the lexicographic relation of string1 to string2.
		Value Relationship of string1 to string2
		<0     string1 less than string2
		0      string1 identical to string2
		>0     string1 greater than string2 */
		if (nCmpC == 0)
		{
			system("cls");
			cout << "您选择的是：按【票价最低】构建图。\n\n";
			return 1;
		}
		else if (nCmpT == 0)
		{
			system("cls");
			cout << "您选择的是：按【时间最短】构建图。\n\n";
			return 2;
		}
		else if ((nCmpC != 0) && (nCmpT != 0))
		{
			system("cls");
			printf("请按照要求输入：【C：按票价最低  T：按时间最短】！\n\n");
			system("pause");
		}
		else
		{
			system("cls");
			printf("程序发生错误！正在全力抢修中……\n即将退出程序……\n\n");
			system("pause");
			exit(-1);//退出程序
		}
	} while (1);
}