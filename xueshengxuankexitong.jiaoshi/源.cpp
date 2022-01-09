#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<string>
#include"subject.h"
#include<vector>
using namespace std;

#pragma warning(disable:4996)

struct student;

static vector<subject> subjects;

static vector<student> students;

static bool flag_ = true;

void read_(student& stu, FILE* file)
{
	uint32_t size = 0;
	fread((void*)&stu.ID, sizeof(int), 1, file);

	fread(&size, sizeof(uint32_t), 1, file);
	stu.name.resize(size / sizeof(char), '\0');
	fread((void*)stu.name.data(), size, 1, file);

	fread((void*)&stu.num_sub, sizeof(int), 1, file);

	fread((void*)&stu.total_credit, sizeof(int), 1, file);

	for (int b = 1; b <= stu.num_sub; b++)
	{
		string temp;
		fread(&size, sizeof(uint32_t), 1, file);
		temp.resize(size / sizeof(char), '\0');
		fread((void*)temp.data(), size, 1, file);
		stu.situation.push_back(temp);
	}
}

void read_file_1(FILE* file)//从文件读取学科档案
{
	fseek(file, 0, SEEK_END);
	int p = ftell(file);
	fseek(file, 0, SEEK_SET);
	while (p - ftell(file)!=0)
	{
		subject sub(0);
		sub.read(file);
		subjects.push_back(sub);
	}
}

void read_file_2()//从文件读取学生选课档案
{
	FILE* file_2 = fopen("D:\\xuankeqingkuang.xitong", "a+");
	fseek(file_2, 0, SEEK_END);
	int p = ftell(file_2);
	fseek(file_2, 0, SEEK_SET);
	while (p - ftell(file_2) != 0)
	{
		student st;
		read_(st, file_2);
		students.push_back(st);
	}
	fclose(file_2);

}

void print_list_0()
{
	cout << ("|------------------------------------|\n");
	cout << ("|          学生选课系统              |\n");
	cout << ("|       请输入选项编号（0—5）：      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1——加入课程                |\n");
	cout << ("|         2——修改课程                |\n");
	cout << ("|         3——查看课程                |\n");
	cout << ("|         4——保存课程                |\n");
	cout << ("|         5——查看选课情况            |\n");
	cout << ("|         0——退出系统                |\n");
	cout << ("|------------------------------------|\n");
}

void print_list_2()
{
	cout << ("|------------------------------------|\n");
	cout << ("|            是否保存                |\n");
	cout << ("|       请输入选项编号（0—2）：      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1——保存                    |\n");
	cout << ("|         2——不保存                  |\n");
	cout << ("|         0——取消                    |\n");
	cout << ("|------------------------------------|\n");
}

int get_order()//初始指令选择
{
	system("cls");
	int result = -1;
	print_list_0();
	do
	{
		cout<<(">>");
		fflush(stdout);
		rewind(stdin);
		cin >> result;
	} while (!(result >= 0 && result <= 5));
	system("cls");
	return result;
}

void add()//添加新课程
{
	if (subjects.size() == 0)
	{
		cout << ("|------------------------------------|\n");
		cout << ("|        当前未设置任何课程！        |\n");
		cout << ("|------------------------------------|\n\n\n");
	}
	else
	{
		cout << "已设置课程编号：" << endl;
		for (auto& i : subjects)
			cout << i.num << endl;
	}
		
	string n;
	cout << ("|------------------------------------|\n");
	cout << ("|          请输入新课程编号          |\n");
	cout << ("|------------------------------------|\n");
	cout << ">>";

	cin.ignore(1000, '\n');
	getline(cin,n);
	system("cls");

	for (auto& i : subjects)
	{
		if (i.num == n)
		{
			cout << "编号已存在！" << endl;
			cout << ("按任意键继续...");
			fflush(stdout);
			int _r = _getch();
			return;
		}
	}

	subject sub(1);
	sub.num = n;
	subjects.push_back(sub);

	cout << ("按任意键继续...");
	fflush(stdout);
	int _r = _getch();
}

void change()//修改已选课程
{	
	if (subjects.size() == 0)
	{
		cout << "当前还未设置课程!" << endl;
	}
	else
	{
		cout << "已设置课程编号：" << endl;
		for (auto& i : subjects)
		{
			cout << i.num << endl;
		}
		cout << "请输入课程编号" << endl;
		string n;
		cin >> n;

		bool flag = false;
		for (auto& i : subjects) {
			if (i.num == n) {
				i.change();
				flag = true;
				break;
			}
		}

		if (!flag) {
			cout << "不存在的课程" << endl;
		}
	}
	cout << ("按任意键继续...");
	fflush(stdout);
	int _r = _getch();
}

int main()
{
	FILE* file1= fopen("D:\\xueshengxuanke.xitong", "a+");
	if (file1 != nullptr) {
		read_file_1(file1);
		fclose(file1);
	}
	read_file_2();//读取已设置课程
	
	int order = -1;
	while (order != 0)
	{
		order = get_order();
		switch (order)
		{
		case 0:
			{
				if (!flag_)
				{
					system("cls");
					int result = -1;
					print_list_2();
					do
					{
						cout << (">>");
						fflush(stdout);
						rewind(stdin);
						cin >> result;
					} while (!(result >= 0 && result <= 2));
					system("cls");

					if(result==1)
					{
						FILE* file = fopen("D:\\xueshengxuanke.xitong", "w");
						if (file != nullptr)
						{
							for (auto& i : subjects)
							{
								i.write_in(file);
							}
							fclose(file);
							flag_ = true;
							system("cls");
							cout << "保存成功！" << endl;
						}
						else
						{
							cout << "保存失败！" << endl;
							order = -1;
							cout << ("按任意键继续...");
							fflush(stdout);
							int _r = _getch();
						}
					}
					else if(result==2)
					{	
						cout << ("按任意键继续...");
						fflush(stdout);
						int _r = _getch();
					}
					else
					{
						order = -1;
						break;
					}
				}
				break;
			}
		case 1:
			{
				add();
				flag_ = false;
				break;
			}
		case 2:
			{
				change();
				flag_ = false;
				break;
			}
		case 3:
			{
				subject::scan(subjects);
				break;
			}
		case 4:
			{
				FILE* file = fopen("D:\\xueshengxuanke.xitong", "w");
				if (file != nullptr)
				{
					for (auto& i : subjects)
					{
						i.write_in(file);
					}
					fclose(file);
					flag_ = true;
					system("cls");
					cout << "保存成功！" << endl;
					cout << ("按任意键继续...");
					fflush(stdout);
					int _r = _getch();

				}
				else
				{
					//编写期间遇到文件打开失败的情况，所以增加此项步骤
					cout << "保存失败！" << endl;
					cout << ("按任意键继续...");
					fflush(stdout);
					int _r = _getch();
				}
				break;
			}
		case 5:
			subject::scan_students(students,subjects);

			//查看学科情况
			/*{
			一.读取文件
			（1）学号(int)，姓名(stirng)，选几门课(int)（这个数据决定读取和写入）,课程详情（vector）
			二.输出结果
			（2）整体数据（scan（） ）
			}*/
			break;
		}
	}

	cout << ("按任意键继续...");
	fflush(stdout);
	int _r = _getch();
}