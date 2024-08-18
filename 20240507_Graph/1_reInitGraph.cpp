#include"manager.h"

bool reInitGraph()
{
    char ch[64]; char chr = '0';
    do
    {
        printf("请问您确定要重新构建图吗？\n请注意：“重新构建图”操作将会回到【欢迎页】！\n【是：请输入Y  否：请输入N】\n请输入：");
        //while ((chr = getchar()) != '\n' && chr != EOF);//把换行符读取掉，清空输入缓冲区
        //getchar();//清空输入缓冲区
        scanf("%s", ch);//不要用getchar，它无法把后面的一个换行符读走
        int nCmpY = strcmp("Y", ch);
        int nCmpN = strcmp("N", ch);
        /*Return Value of strcmp:
        The return value for each of these functions indicates the lexicographic relation of string1 to string2.
        Value Relationship of string1 to string2
        <0     string1 less than string2
        0      string1 identical to string2
        >0     string1 greater than string2 */
        if (nCmpY == 0)
        {
            system("cls");
            cout << "即将回到欢迎页以重新构建图！\n\n";
            system("pause");
            return true;
        }
        else if (nCmpN == 0)
        {
            system("cls");
            cout << "撤销重新构建图。即将回到主菜单……\n\n";
            return false;
        }
        else if ((nCmpY != 0) && (nCmpN != 0))
        {
            printf("\n请按照要求输入：【是：请输入Y  否：请输入N】！\n");
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