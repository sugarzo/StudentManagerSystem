#pragma once
#include"LoginSystem.h"
#include"Grade.h"
#include<string>
#include<vector>
#include<map>
using namespace std;

class student :public Account,public Grades
{
private:
	char name[20];
	char phone[20];
	char qq[20];
	char ClassName[20];
public:
	student(string, string ,string ,string ,string);
	void setname(string c_name) { stringTochar(c_name, name); }
	void setphone(string temp){ stringTochar(temp,phone); }
	void setqq(string temp) { stringTochar(temp, qq); }
	void setClassName(string temp) { stringTochar(temp, ClassName); }
	student():Grades("0") { name[0] = '0'; name[1] = '\0', ID[0] = '\0'; ClassName[0] = '\0'; qq[0] = '\0'; ClassName[0] = '\0'; }
	string returnName() { return name; }
	string returnqq() { return qq; }
	string returnphone() { return phone; }
	string returnClassName() { return ClassName; }
};
student::student(string c_name, string c_ID,string c_qq,string c_phone,string c_class):Grades(c_ID)
{
	stringTochar(c_ID, ID);
	setname(c_name);
	setphone(c_phone);
	setqq(c_qq);
	setqq(c_qq);
	setClassName(c_class);
	hashword = NULL;
}


class classp
{
private:
	char ClassName[20];
	map<string,student> stup;
public:
	void Setname(string p) { stringTochar(p, ClassName); }
	classp(string p="None_class") { Setname(p); }
	student& class_add(string,string,string,string);
	student& class_add(student&);
	const map<string,student>& GetStup() { return stup; }
	map<string, student>::iterator GetStupBegin() { return stup.begin(); }
	map<string, student>::iterator GetStupEnd() { return stup.end(); }
	void deletestudent(string);
	string returnClassName() { return ClassName; }
	int NumberInClass() { return stup.size(); }
	void class_delete(string);
};
student& classp::class_add(string c_name,string c_ID,string c_qq,string c_phone)
{
	stup[c_ID]=student(c_name,c_ID,c_qq,c_phone,this->ClassName);
	return stup[c_ID];
}
student& classp::class_add(student& temp)
{
	//stup[temp.returnID()] = temp; 
	return class_add(temp.returnName(), temp.returngID(), temp.returnqq(), temp.returnphone());
}
void classp::deletestudent(string c_ID)
{
	stup.erase(c_ID);
}


class StudentManager:public AccountManager,public GradesManagerment
{
private:
	classp emptyclass;
public:
	map<string, student*> StudentMap;
	map<string, classp> ClassMap;
	map<string, classp>::iterator ClassIter;
	map<string, student*>::iterator StudentIter;
	int num;
	int ClassNum;
	int StudentNum;
	student EmptyStudent;
	StudentManager() {  ClassNum = 1; StudentNum = 0; ClassMap["None_class"] = emptyclass; readdata();}
	~StudentManager() { savedata(); }
	student& CreateStudent(string, string, string, string, string, string);
	student& CreateStudent(student&);
	student& login(string,string);
	student& JoinClass(student&, string);
	void deleteStudent(string);
	void deleteClassp(string);
	void newclass(string);
	void savedata();
	void readdata();
	bool CheckExist(string c_ID); 
};
student& StudentManager::CreateStudent(string c_name, string c_ID, string c_password, string c_qq, string c_phone, string c_class="None_class")
{
	if (ClassMap.find(c_class) == ClassMap.end())
	{
		ClassMap[c_class] = classp(c_class);
		ClassNum++;
	}
	StudentNum++;
	AccountManager::NewAccount(StudentMap[c_ID] = &ClassMap.find(c_class)->second.class_add(c_name, c_ID, c_qq, c_phone),c_ID,c_password);
	GradesManagerment::NewGrades(*StudentMap[c_ID]);
	return *StudentMap[c_ID];
}
student& StudentManager::CreateStudent(student& sdp)
{
	StudentMap[sdp.returnID()] = &sdp;
	AccountManager::NewAccount(*StudentMap[sdp.returnID()]);
	GradesManagerment::NewGrades(*StudentMap[sdp.returnID()]);
	return sdp;
}

student& StudentManager::login(string ID, string password)
{
	if (AccountManager::login(ID, password))
	{
		return *StudentMap.find(ID)->second;
	}
	else return EmptyStudent;
}

bool StudentManager::CheckExist(string c_ID)
{
	if (StudentMap.find(c_ID) == StudentMap.end()) return false;
	else return true;
}

void StudentManager::savedata()
{
	/*
	* 班级个数 学生总数
	* 班级名1  班级人数
	* 名字1 电话 qq ID
	* 名字2 电话 qq ID
	* ...........
	* 班级名2  班级人数
	* ...........
	*/
	fstream outfile("student.dat",ios::out);
	outfile << ClassNum << " "<<StudentNum<<endl;
	map<string, classp>::iterator iter = ClassMap.begin();
	while (iter != ClassMap.end())
	{
		outfile << iter->second.returnClassName() <<" "<< iter->second.NumberInClass() << endl;
		map<string,student> temp = iter->second.GetStup();
		map<string, student>::iterator tempIter = temp.begin();
		while(tempIter!=temp.end())
		{
			outfile << tempIter->second.returnName() << " " << tempIter->second.returnphone() << " " << tempIter->second.returnqq() <<" "<< tempIter->second.returnID() << endl;
			tempIter++;
		}
		iter++;
	}
	outfile.close();
}
void StudentManager::readdata()
{
	fstream infile("student.dat", ios::in);
	if (!infile) return;
	string classname; int classnum; int studentnum;
	string a, b, c, d;
	infile >> ClassNum >> studentnum;
	for (int i = 1; i <= ClassNum; i++)
	{
		infile >> classname; infile >> classnum;
		ClassMap[classname] = classp(classname);
		for (int j = 1; j <= classnum; j++)
		{
			infile >> a >> b >> c >> d;
			CreateStudent(ClassMap[classname].class_add(a, d, c, b));
		}
	}
	StudentNum = studentnum;
	infile.close();
}
void StudentManager::deleteStudent(string c_ID)
{
	StudentIter = StudentMap.find(c_ID);
	ClassMap.find(StudentIter->second->returnClassName())->second.deletestudent(c_ID);
	AccountManager::deleteAccount(c_ID);
	GradesManagerment::deleteGrades(c_ID);
	StudentMap.erase(StudentIter);
	StudentNum--;
	return;
}
void StudentManager::deleteClassp(string c_name)
{
	map<string, student> p = ClassMap.find(c_name)->second.GetStup();
	map<string, student>::iterator iter = p.begin();
	for (int i = 1; i <= p.size(); i++)
	{
		StudentMap.erase(iter->second.returnID());
		deleteAccount(iter->second.returnID());
		iter++;
	}
	ClassMap.erase(ClassMap.find(c_name));
	return;
}
student& StudentManager::JoinClass(student& c_student, string c_name)
{
	string c_ID = c_student.returngID();
	ClassIter = ClassMap.find(c_student.returnClassName());
	c_student.setClassName(c_name);
	CreateStudent(ClassMap.find(c_name)->second.class_add(c_student));
	ClassIter->second.deletestudent(c_student.returnID());
	ClassIter = ClassMap.find(c_name);
	return *StudentMap[c_ID];
}
void StudentManager::newclass(string name)
{
	ClassMap[name] = classp(name);
	ClassNum++;
}