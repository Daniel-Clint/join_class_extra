#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<fstream>
#include<string>
#include"subject.h"
#include<vector>
#include<functional>
using namespace std;

#pragma warning(disable:4996)

static vector<subject> subjects;
static vector<student> students;
void read_(student& stu, FILE* file);


void print_list_0()
{
	cout << ("|------------------------------------|\n");
	cout << ("|            ѧ��ѡ��ϵͳ            |\n");
	cout << ("|       ������ѡ���ţ�0��2����      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1�����γ̲�ѯ                |\n");
	cout << ("|         2������ʼѡ��                |\n");
	cout << ("|         0�����˳�ϵͳ                |\n");
	cout << ("|------------------------------------|\n");
}

void print_list_0_1()
{
	cout << ("|------------------------------------|\n");
	cout << ("|              �γ̲�ѯ              |\n");
	cout << ("|       ������ѡ���ţ�0��2����      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1��������Ų�                |\n");
	cout << ("|         2���������ʲ�                |\n");
	cout << ("|         0��������                    |\n");
	cout << ("|------------------------------------|\n");
}


int get_order(std::function<void()> pFunc,int n)
{
	system("cls");
	int result = -1;
	pFunc();
	while (!(result >= 0 && result <= n))
	{
		cout << (">>");
		fflush(stdout);
		rewind(stdin);
		cin >> result;
		if (!(result >= 0 && result <= n))
			cout << "��������ȷָ�" << endl;
	}
	system("cls");
	return result;
}

void read_file(FILE* file)//��ȡ�γ�
{
	fseek(file, 0, SEEK_END);
	int p = ftell(file);
	fseek(file, 0, SEEK_SET);
	while (p - ftell(file)!=0)
	{
		subject sub(file);
		subjects.push_back(sub);
	}
}

int main()
{
	//���ļ���ȡ�γ�����
	FILE* file_1 = fopen("D:\\xueshengxuanke.xitong", "r");
	read_file(file_1);
	fclose(file_1);

	int order_0 = -1;
	while (order_0 != 0)
	{
		order_0 = get_order(print_list_0, 2);
		switch (order_0)
		{
		case 1:
		{
			system("cls");
			int order_0_1 = get_order(print_list_0_1, 2);
			switch (order_0_1)
			{
			case 1:
				subject::search_num(subjects);
				break;
			case 2:
				subject::search_nature(subjects);
				break;
			case 0:
				break;
			}
			break;
		}
		case 2:
			system("cls");
			subject::choose(subjects);
			break;
		case 0:
		{
			cout << "ѡ������ɣ���л����ʹ�ã�" << endl;
			cout << ("�����������...");
			fflush(stdout);
			int _r = _getch();
			break;
		}
		}
	}	
}