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

void read_file_1(FILE* file)//���ļ���ȡѧ�Ƶ���
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

void read_file_2()//���ļ���ȡѧ��ѡ�ε���
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
	cout << ("|          ѧ��ѡ��ϵͳ              |\n");
	cout << ("|       ������ѡ���ţ�0��5����      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1��������γ�                |\n");
	cout << ("|         2�����޸Ŀγ�                |\n");
	cout << ("|         3�����鿴�γ�                |\n");
	cout << ("|         4��������γ�                |\n");
	cout << ("|         5�����鿴ѡ�����            |\n");
	cout << ("|         0�����˳�ϵͳ                |\n");
	cout << ("|------------------------------------|\n");
}

void print_list_2()
{
	cout << ("|------------------------------------|\n");
	cout << ("|            �Ƿ񱣴�                |\n");
	cout << ("|       ������ѡ���ţ�0��2����      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1��������                    |\n");
	cout << ("|         2����������                  |\n");
	cout << ("|         0����ȡ��                    |\n");
	cout << ("|------------------------------------|\n");
}

int get_order()//��ʼָ��ѡ��
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

void add()//����¿γ�
{
	if (subjects.size() == 0)
	{
		cout << ("|------------------------------------|\n");
		cout << ("|        ��ǰδ�����κογ̣�        |\n");
		cout << ("|------------------------------------|\n\n\n");
	}
	else
	{
		cout << "�����ÿγ̱�ţ�" << endl;
		for (auto& i : subjects)
			cout << i.num << endl;
	}
		
	string n;
	cout << ("|------------------------------------|\n");
	cout << ("|          �������¿γ̱��          |\n");
	cout << ("|------------------------------------|\n");
	cout << ">>";

	cin.ignore(1000, '\n');
	getline(cin,n);
	system("cls");

	for (auto& i : subjects)
	{
		if (i.num == n)
		{
			cout << "����Ѵ��ڣ�" << endl;
			cout << ("�����������...");
			fflush(stdout);
			int _r = _getch();
			return;
		}
	}

	subject sub(1);
	sub.num = n;
	subjects.push_back(sub);

	cout << ("�����������...");
	fflush(stdout);
	int _r = _getch();
}

void change()//�޸���ѡ�γ�
{	
	if (subjects.size() == 0)
	{
		cout << "��ǰ��δ���ÿγ�!" << endl;
	}
	else
	{
		cout << "�����ÿγ̱�ţ�" << endl;
		for (auto& i : subjects)
		{
			cout << i.num << endl;
		}
		cout << "������γ̱��" << endl;
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
			cout << "�����ڵĿγ�" << endl;
		}
	}
	cout << ("�����������...");
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
	read_file_2();//��ȡ�����ÿγ�
	
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
							cout << "����ɹ���" << endl;
						}
						else
						{
							cout << "����ʧ�ܣ�" << endl;
							order = -1;
							cout << ("�����������...");
							fflush(stdout);
							int _r = _getch();
						}
					}
					else if(result==2)
					{	
						cout << ("�����������...");
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
					cout << "����ɹ���" << endl;
					cout << ("�����������...");
					fflush(stdout);
					int _r = _getch();

				}
				else
				{
					//��д�ڼ������ļ���ʧ�ܵ�������������Ӵ����
					cout << "����ʧ�ܣ�" << endl;
					cout << ("�����������...");
					fflush(stdout);
					int _r = _getch();
				}
				break;
			}
		case 5:
			subject::scan_students(students,subjects);

			//�鿴ѧ�����
			/*{
			һ.��ȡ�ļ�
			��1��ѧ��(int)������(stirng)��ѡ���ſ�(int)��������ݾ�����ȡ��д�룩,�γ����飨vector��
			��.������
			��2���������ݣ�scan���� ��
			}*/
			break;
		}
	}

	cout << ("�����������...");
	fflush(stdout);
	int _r = _getch();
}