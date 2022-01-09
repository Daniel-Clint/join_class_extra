#include "subject.h"
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>
#include<conio.h>
using namespace std;

#pragma warning(disable:4996)

static vector<student> students;

subject::subject(FILE* file)
{
	uint32_t size = 0;//size只需定义一次
	fread(&size, sizeof(uint32_t), 1, file);
	num.resize(size / sizeof(char), '\0');
	fread((void*)num.data(), size, 1, file);

	fread(&size, sizeof(uint32_t), 1, file);
	name.resize(size / sizeof(char), '\0');
	fread((void*)name.data(), size, 1, file);

	fread((void*)&nature, sizeof(char), 1, file);

	fread((void*)&total_time, sizeof(double), 1, file);

	fread((void*)&class_time, sizeof(double), 1, file);

	fread((void*)&comp_time, sizeof(double), 1, file);

	fread((void*)&credit, sizeof(int), 1, file);

	fread(&size, sizeof(uint32_t), 1, file);
	piriod.resize(size / sizeof(char), '\0');
	fread((void*)piriod.data(), size, 1, file);
}

void subject::scan(vector<subject>subjects)
{
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|                                        所有课程                                       |" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|编号\t|名称\t|性质\t|总学时\t|课堂学时\t|上机学时\t|学分\t|开课学期\t|"<<endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;

	for (auto& i : subjects)
	{
		cout << "|" << i.num << "\t|" << i.name << "\t|" << i.nature << "\t|" << i.total_time << "\t|" << i.class_time << "\t\t|" << i.comp_time << "\t\t|" << i.credit << "\t|" << i.piriod << "\t|" << endl;
		cout << "-----------------------------------------------------------------------------------------" << endl;
	}
}

void subject::search_num(vector<subject> subjects)
{
	cout << ("|------------------------------------|\n");
	cout << ("|             请输入编号             |\n");
	cout << ("|------------------------------------|\n");
	cout << (">>");
	string num_;
	cin.ignore(500, '\n');
	getline(cin, num_);
	bool a = false;
	for (auto& i : subjects)
	{
		if (i.num == num_)
		{
			system("cls");
			cout << "-----------------------------------------------------------------------------------------" << endl;
			cout << "|                                      课程浏览                                         |" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
			cout << "|编号\t|名称\t|性质\t|总学时\t|课堂学时\t|上机学时\t|学分\t|开课学期\t|" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
			cout << "|" << i.num << "\t|" << i.name << "\t|" << i.nature << "\t|" << i.total_time << "\t|" << i.class_time << "\t\t|" << i.comp_time << "\t\t|" << i.credit << "\t|" << i.piriod << "\t|" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
			a=true;
		}
	}
	if (!a)
		cout << "不存在的课程！" << endl;
	cout << ("按任意键继续...");
	fflush(stdout);
	int _r = _getch();
}

void subject::search_nature(vector<subject> subjects)
{
	system("cls");
	cout << ("|------------------------------------|\n");
	cout << ("|             请输入性质             |\n");
	cout << ("|------------------------------------|\n");
	cout << (">>");
	char nature_;
	cin >> nature_;
	bool a = false;
	system("cls");
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|                                      课程浏览                                         |" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|编号\t|名称\t|性质\t|总学时\t|课堂学时\t|上机学时\t|学分\t|开课学期\t|" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (auto& i : subjects)
	{
		if (i.nature == nature_)
		{
			cout << "|" << i.num << "\t|" << i.name << "\t|" << i.nature << "\t|" << i.total_time << "\t|" << i.class_time << "\t\t|" << i.comp_time << "\t\t|" << i.credit << "\t|" << i.piriod << "\t|" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
			a=true;
		}
	}
	if (!a)
		cout << "不存在的课程！" << endl;
	cout << ("按任意键继续...");
	fflush(stdout);
	int _r = _getch();
}

void read_(student& stu, FILE* file)//读取选课情况
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

void print_list()
{
	system("cls");
	cout << ("|------------------------------------|\n");
	cout << ("|              正在选课              |\n");
	cout << ("|      所有课程学分之和不少于30！    |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1——添加                    |\n");
	cout << ("|         2——删除已选课程            |\n");
	cout << ("|         0——完成并保存              |\n");
	cout << ("|------------------------------------|\n");
}

void subject::al_stu_choose(vector<subject>subjects,student &i,bool &exist_stu)
{
	for (auto& a : subjects)
	{
		if (a.nature == 'b')
		{
			bool alch = false;
			for (auto& k : i.situation)
			{
				if (k == a.num)
				{
					alch = true;
					break;
				}
			}
			if (!alch)
			{
				i.situation.push_back(a.num);
				i.total_credit += a.credit;
				i.num_sub++;
			}
		}
	}
	exist_stu = true;

	string temp_choose = "a";
	bool exist_sub = false;
	bool already = false;

	int order = -1;
	while (order != 0)
	{
		order = get_order(print_list, 2);
		if (order == 1)
		{
			exist_sub = false;
			subject::scan(subjects);
			cout << "已选课程：" << endl;
			for (auto& c : i.situation)
			{
				cout << c << endl;
			}

			cout << endl << "添加课程" << endl;
			cout << ">>";
			cin.ignore(500, '\n');
			getline(cin, temp_choose);

			already = false;
			for (auto& f : i.situation)
			{
				if (f == temp_choose)
				{
					cout << "该课程已选择!" << endl;
					already = true;
				}
			}

			if (already)
			{
				continue;
			}

			exist_sub = false;
			for (auto& d : subjects)
			{
				if (temp_choose == d.num)
				{
					{
						cout << endl << "选课成功！" << endl;
						i.num_sub++;
						i.total_credit += d.credit;
						exist_sub = true;
						i.situation.push_back(temp_choose);
						cout << ("按任意键继续...");
						fflush(stdout);
						int _r = _getch();

					}
				}
			}
			if (!exist_sub)
			{
				cout << "该课程不存在！" << endl;
				cout << ("按任意键继续...");
				fflush(stdout);
				int _r = _getch();
			}
		}

		else if (order == 2)
		{
			if (i.situation.size() == 0)
				cout << "";
			cout << "已选课程：" << endl;
			for (auto& g : i.situation)
			{
				for (auto& h : subjects)
				{
					if (g == h.num)
					{
						if (h.nature != 'b')
						{
							cout << g << endl;;
						}
					}
				}
			}
			cout << "你想要删除：";
			cin.ignore(500, '\n');
			getline(cin, temp_choose);
			bool refuse_delete = false;
			for (auto& h : subjects)
			{
				if (temp_choose == h.num)
				{
					if (h.nature == 'b')
					{
						refuse_delete = true;
						cout << "必修课不可删除！";
						cout << ("按任意键继续...");
						fflush(stdout);
						int _r = _getch();
					}
				}
			}
			if (!refuse_delete)
			{
				bool al = false;
				for (vector<string>::iterator iter = i.situation.begin(); iter != i.situation.end(); iter++)
				{
					if (temp_choose == *iter)
					{
						i.situation.erase(iter);
						for (auto& j : subjects)
						{
							if (j.num == temp_choose)
							{
								i.total_credit -= j.credit;
							}
						}
						i.num_sub--;
						al = true;
						cout << "已删除！" << endl;
						cout << ("按任意键继续...");
						fflush(stdout);
						int _r = _getch();
						break;
					}
				}
				if (!al)
				{
					cout << "此课程未被选择！" << endl;
					cout << ("按任意键继续...");
					fflush(stdout);
					int _r = _getch();
					order = -1;
				}
			}
		}
		else
		{
			if (i.total_credit > 30)
			{
				bool flag = upload();
				if (!flag)
				{
					cout << "保存失败！" << endl;
					order = -1;
					cout << ("按任意键继续...");
					fflush(stdout);
					int _r = _getch();
				}
				else
				{
					cout << "选课完成！" << endl;
					cout << ("按任意键继续...");
					fflush(stdout);
					int _r = _getch();
				}
			}
			else
			{
				cout << "所选课程的学分要高于30分！" << endl;
				order = -1;
				cout << ("按任意键继续...");
				fflush(stdout);
				int _r = _getch();
			}
		}
	}
}

void subject::new_stu_choose(vector<subject>subjects,int stu_ID)
{
	student stu;
	stu.ID = stu_ID;

	string temp_choose = "a";
	bool exist_sub = false;
	int total_sub = 0;
	bool already = false;

	cout << "请输入你的姓名" << endl << ">>";
	cin.ignore(500, '\n');
	getline(cin, stu.name);
	for (auto& a : subjects)
	{
		if (a.nature == 'b')
		{
			stu.situation.push_back(a.num);
			stu.total_credit += a.credit;
			stu.num_sub++;
		}
	}

	students.push_back(stu);

	int order = -1;
	while (order != 0)
	{
		order = get_order(print_list, 2);
		if (order == 1)
		{
			exist_sub = false;
			subject::scan(subjects);
			cout << "已选课程：" << endl;
			for (auto& c : students[students.size() - 1].situation)
			{
				cout << c << endl;
			}
			cout << endl << "添加课程(必修课已为你自动添加)" << endl;
			cout << ">>";
			cin.ignore(500, '\n');
			getline(cin, temp_choose);

			already = false;
			for (auto& f : students[students.size() - 1].situation)
			{
				if (f == temp_choose)
				{
					already = true;
					break;
				}
			}
			if (already)
			{
				cout << "该课程已选择!" << endl;
				cout << ("按任意键继续...");
				fflush(stdout);
				int _r = _getch();
				continue;
			}

			exist_sub = false;
			for (auto& d : subjects)
			{
				if (temp_choose == d.num)
				{
					{
						cout << endl << "选课成功！" << endl;
						students[students.size() - 1].num_sub++;
						students[students.size() - 1].total_credit += d.credit;
						exist_sub = true;
						students[students.size() - 1].situation.push_back(temp_choose);
						cout << ("按任意键继续...");
						fflush(stdout);
						int _r = _getch();
						break;
					}
				}
			}
			if (!exist_sub)
			{
				cout << "该课程不存在！" << endl;
				cout << ("按任意键继续...");
				fflush(stdout);
				int _r = _getch();
			}

		}
		else if (order == 2)
		{
			cout << "已选课程：" << endl;
			for (auto& g : students[students.size() - 1].situation)
			{
				for (auto& h : subjects)
				{
					if (g == h.num)
					{
						if (h.nature != 'b')
						{
							cout << g << endl;
						}
					}
				}
			}
			cout << "你想要删除：";
			cin.ignore(500, '\n');
			getline(cin, temp_choose);
			bool refuse_delete = false;
			for (auto& h : subjects)
			{
				if (temp_choose == h.num)
				{
					if (h.nature == 'b')
					{
						refuse_delete = true;
						cout << "必修课不可删除！";
						cout << ("按任意键继续...");
						fflush(stdout);
						int _r = _getch();
						break;
					}
				}
			}
			if (!refuse_delete)
			{
				bool al = false;
				for (vector<string>::iterator iter = students[students.size() - 1].situation.begin(); iter != students[students.size() - 1].situation.end(); iter++)
				{
					if (temp_choose == *iter)
					{
						for (auto& j : subjects)
						{
							if (j.num == temp_choose)
							{
								students[students.size() - 1].total_credit -= j.credit;
								break;
							}
						}
						al = true;
						students[students.size() - 1].situation.erase(iter);
						students[students.size() - 1].num_sub--;
						cout << "已删除！" << endl;
						cout << ("按任意键继续...");
						fflush(stdout);
						int _r = _getch();
						break;
					}
				}
				if (!al)
				{
					cout << "此课程未被选择！" << endl;
					order = -1;
				}
			}
		}
		else
		{
			if (students[students.size() - 1].total_credit > 30)
			{
				bool flag = upload();
				if (!flag)
				{
					cout << "保存失败！" << endl;
					order = -1;
				}
				else
				{
					cout << "选课完成！" << endl;
					cout << ("按任意键继续...");
					fflush(stdout);
					int _r = _getch();
				}
			}
			else
			{
				cout << "所选课程的学分要高于30分！" << endl;
				order = -1;
				cout << ("按任意键继续...");
				fflush(stdout);
				int _r = _getch();
			}
		}
	}
}

void subject::choose(vector<subject> subjects)
{
	students.clear();
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

	bool exist_stu = false;
	int stu_ID;
	cout << "请输入你的学号" << endl << ">>";
	cin >> stu_ID;


	for (auto& i : students)
	{
		if (i.ID == stu_ID)//修改学生档案
		{
			subject::al_stu_choose(subjects, i,exist_stu);
		}
	}

	if (!exist_stu)//建立新学生档案
	{
		subject::new_stu_choose(subjects, stu_ID);
	}
	system("cls");
}

bool subject::upload()//选课情况保存至文档
{
	FILE* file = fopen("D:\\xuankeqingkuang.xitong", "w+");
	if (file != nullptr)
	{
		for (auto& i : students)
		{
			write_(i,file);
		}
		fclose(file);
		return true;
	}
	else
		return false;
}

void subject::write_(student i,FILE* file)
{
	fwrite(&i.ID, sizeof(int), 1, file);
	
	uint32_t name_size = i.name.size() * sizeof(char);
	fwrite(&name_size, sizeof(uint32_t), 1, file);
	fwrite(i.name.data(), sizeof(char), i.name.size(), file);

	fwrite(&i.num_sub, sizeof(int), 1, file);

	fwrite(&i.total_credit, sizeof(int), 1, file);

	for (auto &a : i.situation)
	{
		uint32_t i_size = a.size() * sizeof(char);
		fwrite(&i_size, sizeof(uint32_t), 1, file);
		fwrite(a.data(), sizeof(char), a.size(), file);
	}
}
