#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<string>
#include"subject.h"
#include<vector>
using namespace std;

subject::subject(int n)
{
	if (n == 0)
		return;
	else
		this->change();
}


void print_list_1()
{
	cout << ("|------------------------------------|\n");
	cout << ("|            ����¿γ�              |\n");
	cout << ("|       ������ѡ���ţ�0��6����      |\n");
	cout << ("|------------------------------------|\n");
	cout << ("|         1�����༭����                |\n");
	cout << ("|         2�����༭ѧ������            |\n");
	cout << ("|         3�����༭�ϻ�ѧʱ            |\n");
	cout << ("|         4�����༭����ѧʱ            |\n");
	cout << ("|         5�����༭ѧ��                |\n");
	cout << ("|         6�����༭����ѧ��            |\n");
	cout << ("|         0��������                    |\n");
	cout << ("|------------------------------------|\n");
	cout << ">>";
}

int get_order1()
{
	system("cls");
	int result = -1;
	print_list_1();
	do
	{
		cout << (">>");
		fflush(stdout);
		rewind(stdin);
		cin >> result;
	} while (!(result >= 0 && result <= 6));
	system("cls");
	return result;
}

void subject::change()
{
	int order=-1;
	for (; order != 0;)
	{
		order= get_order1();
		switch (order)
		{
		case 0:
			cout << "�γ̵���������ɣ�" << endl;
			break;
		case 1:
			cout << ("|------------------------------------|\n");
			cout << ("|          ������ѧ������:           |\n");
			cout << ("|------------------------------------|\n");
			cout << ">>";
			cin.ignore(500, '\n');
			getline(cin, name);
			system("cls");
			break;
		case 2:
			cout << ("|------------------------------------------------|\n");
			cout << ("| ������ѧ�����ʣ����޿�:b��ѡ�޿�:x��������:g��:|\n");
			cout << ("|------------------------------------------------|\n");
			cout << ">>";
			cin >> nature;
			system("cls");
			break;
		case 3:
			cout << ("|------------------------------------|\n");
			cout << ("|          �������ϻ�ѧʱ:           |\n");
			cout << ("|------------------------------------|\n");
			cout << ">>";
			cin >> comp_time;
			system("cls");
			break;
		case 4:
			cout << ("|------------------------------------|\n");
			cout << ("|          ���������ѧʱ:           |\n");
			cout << ("|------------------------------------|\n");
			cout << ">>";
			cin >> class_time;
			system("cls");
			total_time = comp_time + class_time;
			break;
		case 5:
			cout << ("|------------------------------------|\n");
			cout << ("|          ������γ�ѧ��:           |\n");
			cout << ("|------------------------------------|\n");
			cout << ">>";
			cin >> credit;
			system("cls");
			break;
		case 6:
			cout << ("|------------------------------------|\n");
			cout << ("|          ������γ�ѧ��:           |\n");
			cout << ("|------------------------------------|\n");
			cout << ">>";
			cin >> piriod;
			system("cls");
			break;

		}
	}
}

void subject::scan(vector<subject>subjects)
{
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|                                      �γ����                                         |" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|���\t|����\t|����\t|��ѧʱ\t|����ѧʱ\t|�ϻ�ѧʱ\t|ѧ��\t|����ѧ��\t|" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (auto& i : subjects)
	{
		cout << "|" << i.num << "\t|" << i.name << "\t|" << i.nature << "\t|" << i.total_time << "\t|" << i.class_time << "\t\t|" << i.comp_time << "\t\t|" << i.credit << "\t|" << i.piriod << "\t|"<<endl;
		cout << "-----------------------------------------------------------------------------------------" << endl;
	}
	cout << ("�����������...");
	fflush(stdout);
	int _r = _getch();
}

void subject::scan_students(vector<student>students,vector<subject>subjects)
{
	system("cls");
	cout << "---------------------------------" << endl;
	cout << "|         ѡ��������          |" << endl;
	cout << "---------------------------------" << endl;
	cout << "|ѧ��\t|����\t|ѧ��\t|ѡ����\t|" << endl;
	cout << "---------------------------------" << endl;
	for (auto& i : students)
	{
		bool first_line = true;
		cout << "|" << i.ID << "\t|" << i.name << "\t|" << i.total_credit << "\t|";
		for (auto& b : i.situation)
		{
			if (first_line)
			{
				first_line = false;
				for (auto& c : subjects)
				{
					if (b == c.num)
					{
						cout << c.name << "\t|" << endl;
						cout << "---------------------------------" << endl;
						break;
					}
				}
			}
			else
			{
				cout << "|\t|\t|\t|";
				for (auto& c : subjects)
				{
					if (b == c.num)
					{
						cout << c.name << "\t|" << endl;
						cout << "---------------------------------" << endl;
						break;
					}
				}
			}
		}
		first_line = true;
	}
	cout << ("�����������...");
	fflush(stdout);
	int _r = _getch();
}



void subject::read(FILE* file)
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

void subject::write_in(FILE* file)
{
	uint32_t num_size = this->num.size() * sizeof(char);
	fwrite(&num_size, sizeof(uint32_t), 1, file);
	fwrite(this->num.data(), sizeof(char), this->num.size(),  file);

	uint32_t name_size = this->name.size() * sizeof(char);
	fwrite(&name_size, sizeof(uint32_t), 1, file);
	fwrite(this->name.data(), sizeof(char), this->name.size(), file);

	fwrite(&nature, sizeof(char), 1, file);

	fwrite(&total_time, sizeof(double), 1, file);

	fwrite(&class_time, sizeof(double), 1, file);
	
	fwrite(&comp_time, sizeof(double), 1, file);

	fwrite(&credit, sizeof(int), 1, file);

	uint32_t piriod_size = this->piriod.size() * sizeof(char);
	fwrite(&piriod_size, sizeof(uint32_t), 1, file);
	fwrite(this->piriod.data(), sizeof(char), this->piriod.size(), file);
}
