#include"manager.h"

bool reInitGraph()
{
    char ch[64]; char chr = '0';
    do
    {
        printf("������ȷ��Ҫ���¹���ͼ��\n��ע�⣺�����¹���ͼ����������ص�����ӭҳ����\n���ǣ�������Y  ��������N��\n�����룺");
        //while ((chr = getchar()) != '\n' && chr != EOF);//�ѻ��з���ȡ����������뻺����
        //getchar();//������뻺����
        scanf("%s", ch);//��Ҫ��getchar�����޷��Ѻ����һ�����з�����
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
            cout << "�����ص���ӭҳ�����¹���ͼ��\n\n";
            system("pause");
            return true;
        }
        else if (nCmpN == 0)
        {
            system("cls");
            cout << "�������¹���ͼ�������ص����˵�����\n\n";
            return false;
        }
        else if ((nCmpY != 0) && (nCmpN != 0))
        {
            printf("\n�밴��Ҫ�����룺���ǣ�������Y  ��������N����\n");
        }
        else
        {
            system("cls");
            printf("��������������ȫ�������С���\n�����˳����򡭡�\n\n");
            system("pause");
            exit(-1);//�˳�����
        }
    } while (1);
}