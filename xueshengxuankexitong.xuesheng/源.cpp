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
	cout << ("|            学生选课系统            |\n");
	cout << ("|       请输入选项编号（0—2）：      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1——课程查询                |\n");
	cout << ("|         2——开始选课                |\n");
	cout << ("|         0——退出系统                |\n");
	cout << ("|------------------------------------|\n");
}

void print_list_0_1()
{
	cout << ("|------------------------------------|\n");
	cout << ("|              课程查询              |\n");
	cout << ("|       请输入选项编号（0—2）：      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1——按编号查                |\n");
	cout << ("|         2——按性质查                |\n");
	cout << ("|         0——返回                    |\n");
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
			cout << "请输入正确指令！" << endl;
	}
	system("cls");
	return result;
}

void read_file(FILE* file)//读取课程
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
	//读文件读取课程详情
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
			cout << "选课已完成！感谢您的使用！" << endl;
			cout << ("按任意键继续...");
			fflush(stdout);
			int _r = _getch();
			break;
		}
		}
	}	
}