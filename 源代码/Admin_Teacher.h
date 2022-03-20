#pragma once
#include<string>
#include"LoginSystem.h"

using namespace std;

class teacher:public Account
{
private:
	string name;
	string classname;
public:
	teacher(string n = "0", string c = "None_class") { name = n; classname = c; }
	void setname(string c_name) { name=c_name; }
	void setClassName(string temp) { classname = temp; }
	string returnName() { return name; }
	string returnClassName() { return classname; }
};

class Admin :public Account
{
public:
	map<string, teacher> teacherMap;
	map<string, teacher>::iterator tMapiter;
	AccountManager* Ap;
	Admin(AccountManager* p) { stringTochar("admin", ID); Ap = p; A_readdata();  }
	~Admin() { A_savedata(); }
	int returnNum_teacher() { return teacherMap.size(); }
	void newTeacher(string, string, string, string);
	void newTeacher(Account&);
	void deleteTeacher(string);
	void A_savedata();
	void A_readdata();
};

void Admin::newTeacher(string c_name, string c_classname, string c_ID, string c_password)
{
	teacherMap[c_ID] = teacher(c_name, c_classname);
	Ap->NewAccount(teacherMap[c_ID], c_ID, stringTOhashword(c_password));
}
void Admin::newTeacher(Account& p)
{
	Ap->NewAccount(p);
}
void Admin::deleteTeacher(string p)
{
	Ap->deleteAccount(p);
	teacherMap.erase(p);
}

void Admin::A_savedata()
{
	/*
	教师个数
	ID1 name1 classname1
	....
	*/
	fstream outfile("teacher.dat", ios::out);
	outfile << teacherMap.size() << endl;
	tMapiter = teacherMap.begin();
	while (tMapiter != teacherMap.end())
	{
		outfile << tMapiter->second.returnID() << " " << tMapiter->second.returnName() << " " << tMapiter->second.returnClassName() << endl;
		tMapiter++;
	}
	outfile.close();
}

void Admin::A_readdata()
{
	fstream infile("teacher.dat", ios::in);
	if (!infile) return;
	int n; infile >> n;
	string ID1, name1, classname1;
	while (n--)
	{
		infile >> ID1 >> name1 >> classname1;
		teacherMap[ID1] = teacher(name1, classname1);
		teacherMap[ID1].setID(ID1);
		newTeacher(teacherMap[ID1]);
	}
	infile.close();
}