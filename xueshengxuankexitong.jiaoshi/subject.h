#include<string>
#include<fstream>
#include<vector>
using namespace std;
#pragma once

struct student
{
	int ID;
	string name;
	int num_sub;
	int total_credit;
	vector<string> situation;
};

class subject
{
public:
	subject(int n);
	string num;
	void write_in(FILE* file);
	void change();
	void read(FILE* file);
	static void scan(vector<subject>);
	static void scan_students(vector<student>,vector<subject>);
private:
	string name;
	char nature;
	double total_time=0;
	double class_time=0;
	double comp_time=0;
	int credit;
	string piriod;

};

