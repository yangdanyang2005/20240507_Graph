#include"manager.h"

void ExitSystem()
{
    char ch[64]; char chr = '0';
    do
    {
        printf("������ȷ��Ҫ�˳��������𣿡��ǣ�������Y  ��������N��\n�����룺");
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
            cout << "�����˳������򣬻�ӭ���´�ʹ�ã�\n\n";
            system("pause");
            exit(0);//�˳�����
        }
        else if (nCmpN == 0)
        {
            cout << "�����˳������򡣼����������˵�����\n\n";
            break;
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