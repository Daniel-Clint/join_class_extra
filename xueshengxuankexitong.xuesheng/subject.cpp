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
	uint32_t size = 0;//sizeֻ�趨��һ��
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
	cout << "|                                        ���пγ�                                       |" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|���\t|����\t|����\t|��ѧʱ\t|����ѧʱ\t|�ϻ�ѧʱ\t|ѧ��\t|����ѧ��\t|"<<endl;
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
	cout << ("|             ��������             |\n");
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
			cout << "|                                      �γ����                                         |" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
			cout << "|���\t|����\t|����\t|��ѧʱ\t|����ѧʱ\t|�ϻ�ѧʱ\t|ѧ��\t|����ѧ��\t|" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
			cout << "|" << i.num << "\t|" << i.name << "\t|" << i.nature << "\t|" << i.total_time << "\t|" << i.class_time << "\t\t|" << i.comp_time << "\t\t|" << i.credit << "\t|" << i.piriod << "\t|" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
			a=true;
		}
	}
	if (!a)
		cout << "�����ڵĿγ̣�" << endl;
	cout << ("�����������...");
	fflush(stdout);
	int _r = _getch();
}

void subject::search_nature(vector<subject> subjects)
{
	system("cls");
	cout << ("|------------------------------------|\n");
	cout << ("|             ����������             |\n");
	cout << ("|------------------------------------|\n");
	cout << (">>");
	char nature_;
	cin >> nature_;
	bool a = false;
	system("cls");
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|                                      �γ����                                         |" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|���\t|����\t|����\t|��ѧʱ\t|����ѧʱ\t|�ϻ�ѧʱ\t|ѧ��\t|����ѧ��\t|" << endl;
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
		cout << "�����ڵĿγ̣�" << endl;
	cout << ("�����������...");
	fflush(stdout);
	int _r = _getch();
}

void read_(student& stu, FILE* file)//��ȡѡ�����
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
	cout << ("|              ����ѡ��              |\n");
	cout << ("|      ���пγ�ѧ��֮�Ͳ�����30��    |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1�������                    |\n");
	cout << ("|         2����ɾ����ѡ�γ�            |\n");
	cout << ("|         0������ɲ�����              |\n");
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
			cout << "��ѡ�γ̣�" << endl;
			for (auto& c : i.situation)
			{
				cout << c << endl;
			}

			cout << endl << "��ӿγ�" << endl;
			cout << ">>";
			cin.ignore(500, '\n');
			getline(cin, temp_choose);

			already = false;
			for (auto& f : i.situation)
			{
				if (f == temp_choose)
				{
					cout << "�ÿγ���ѡ��!" << endl;
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
						cout << endl << "ѡ�γɹ���" << endl;
						i.num_sub++;
						i.total_credit += d.credit;
						exist_sub = true;
						i.situation.push_back(temp_choose);
						cout << ("�����������...");
						fflush(stdout);
						int _r = _getch();

					}
				}
			}
			if (!exist_sub)
			{
				cout << "�ÿγ̲����ڣ�" << endl;
				cout << ("�����������...");
				fflush(stdout);
				int _r = _getch();
			}
		}

		else if (order == 2)
		{
			if (i.situation.size() == 0)
				cout << "";
			cout << "��ѡ�γ̣�" << endl;
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
			cout << "����Ҫɾ����";
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
						cout << "���޿β���ɾ����";
						cout << ("�����������...");
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
						cout << "��ɾ����" << endl;
						cout << ("�����������...");
						fflush(stdout);
						int _r = _getch();
						break;
					}
				}
				if (!al)
				{
					cout << "�˿γ�δ��ѡ��" << endl;
					cout << ("�����������...");
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
					cout << "����ʧ�ܣ�" << endl;
					order = -1;
					cout << ("�����������...");
					fflush(stdout);
					int _r = _getch();
				}
				else
				{
					cout << "ѡ����ɣ�" << endl;
					cout << ("�����������...");
					fflush(stdout);
					int _r = _getch();
				}
			}
			else
			{
				cout << "��ѡ�γ̵�ѧ��Ҫ����30�֣�" << endl;
				order = -1;
				cout << ("�����������...");
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

	cout << "�������������" << endl << ">>";
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
			cout << "��ѡ�γ̣�" << endl;
			for (auto& c : students[students.size() - 1].situation)
			{
				cout << c << endl;
			}
			cout << endl << "��ӿγ�(���޿���Ϊ���Զ����)" << endl;
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
				cout << "�ÿγ���ѡ��!" << endl;
				cout << ("�����������...");
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
						cout << endl << "ѡ�γɹ���" << endl;
						students[students.size() - 1].num_sub++;
						students[students.size() - 1].total_credit += d.credit;
						exist_sub = true;
						students[students.size() - 1].situation.push_back(temp_choose);
						cout << ("�����������...");
						fflush(stdout);
						int _r = _getch();
						break;
					}
				}
			}
			if (!exist_sub)
			{
				cout << "�ÿγ̲����ڣ�" << endl;
				cout << ("�����������...");
				fflush(stdout);
				int _r = _getch();
			}

		}
		else if (order == 2)
		{
			cout << "��ѡ�γ̣�" << endl;
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
			cout << "����Ҫɾ����";
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
						cout << "���޿β���ɾ����";
						cout << ("�����������...");
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
						cout << "��ɾ����" << endl;
						cout << ("�����������...");
						fflush(stdout);
						int _r = _getch();
						break;
					}
				}
				if (!al)
				{
					cout << "�˿γ�δ��ѡ��" << endl;
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
					cout << "����ʧ�ܣ�" << endl;
					order = -1;
				}
				else
				{
					cout << "ѡ����ɣ�" << endl;
					cout << ("�����������...");
					fflush(stdout);
					int _r = _getch();
				}
			}
			else
			{
				cout << "��ѡ�γ̵�ѧ��Ҫ����30�֣�" << endl;
				order = -1;
				cout << ("�����������...");
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
	cout << "���������ѧ��" << endl << ">>";
	cin >> stu_ID;


	for (auto& i : students)
	{
		if (i.ID == stu_ID)//�޸�ѧ������
		{
			subject::al_stu_choose(subjects, i,exist_stu);
		}
	}

	if (!exist_stu)//������ѧ������
	{
		subject::new_stu_choose(subjects, stu_ID);
	}
	system("cls");
}

bool subject::upload()//ѡ������������ĵ�
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
