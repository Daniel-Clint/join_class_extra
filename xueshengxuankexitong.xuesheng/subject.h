#include<string>
#include<fstream>
#include<vector>
#include<functional>
using namespace std;
#pragma once

struct student
{
	int ID;
	string name;
	int num_sub=0;
	int total_credit=0;
	vector<string> situation;
};

class subject
{
public:
	subject(FILE* file);
	static void scan(vector<subject>);
	static void choose(vector<subject>);
	static void al_stu_choose(vector<subject>,student&,bool&);
	static void new_stu_choose(vector<subject>,int);
	static void search_num(vector<subject> subjects);
	static void search_nature(vector<subject> subjects);
	static bool upload();
	static void write_(student i,FILE* file);

private:
	string num;
	string name;
	char nature;
	double total_time=0;
	double class_time=0;
	double comp_time=0;
	int credit;
	string piriod;
};

int get_order(std::function<void()> pFunc, int n);