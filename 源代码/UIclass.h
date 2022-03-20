#pragma once
#include<iostream>
#include"LoginSystem.h";
#include"StudentSystem.h"
#include"Admin_Teacher.h"
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

int GetInput()
{
	string Input;
	cin >> Input;
	if (Input[0] >= '0' && Input[0] <= '9') return Input[0] - '0';
	else return -1;
}

class UI :public StudentManager,public Admin
{
public:
		UI();
		void show();
		//学生界面
		void regis(); 
		void StudentLogin();
		void studentUI(student*);
		void UIs_PersonInformation(student*);
		void UIs_Addclass(student*);
		void UIs_Classmate(student*);
		void UIs_Grade(student*);
		void UIs_changePassword(student*);
		void UIs_changeInf(student*);
		void UIs_Grade_Insemester(student&, string);
		void grades_printInclass(string, string, int);
		//教师界面
		void TeacherLogin();
		void teacherUI(teacher&);
		void UIt_PersonInformation(teacher&);
		void UIt_StudentList(teacher&);	
		void UIt_GradeSetting(teacher&);
		void UIt_Grades(teacher&);
		void UIt_Grade_change(teacher&);
		void UIt_changePassword(teacher&);
		void UIt_addSubject(teacher&);
		void UIt_deleteSubject(teacher&);
		//管理员界面
		void AdminLogin();
		void UIa_StudentList();
		void UIa_TeacherList();
		void UIa_IDsearch();
		void UIa_ClassManager();
		void UIa_SemesterManager();
		void UIa_ChangePassword();
};
UI::UI():Admin(this)
{
	NewAccount(*this);
}

void UI::grades_printInclass(string sem_name, string cla_name, int type=1)
{
	/*
	type==1 学号排序
	type==2 GPA排序
	type==3 WAM排序
	*/
	int n = ClassMap[cla_name].NumberInClass();
	student** p1 = new student* [n];
	map<string, student>::iterator iter = ClassMap[cla_name].GetStupBegin();
	for (int i = 0; i < n; i++)
	{
		p1[i] = &iter->second;
		iter++;
	}
	cmpsem = sem_name;
	switch (type)
	{
	case 1:
		sort(p1, p1 + n, cmpbyID);
		break;
	case 2:
		sort(p1, p1 + n, cmpbyGPA);
		break;
	case 3:
		sort(p1, p1 + n, cmpbyWAM);
		break;
	default:
		break;
	}
	cout << "该班共有：" << n << "名学生\n";
	cout << "******************************\n";
	cout << "排名\t姓名\tGPA\t加权平均分\n";
	for (int i = 0; i < n; i++)
	{
		cout  << i + 1 << "\t" << p1[i]->returnName() << "\t";	
		cout << fixed << setprecision(2);
		cout  << p1[i]->return_Smap(sem_name)->returnGPA() << "\t" << "加权平均分:" << p1[i]->return_Smap(sem_name)->returnWAM();
		cout.unsetf(ios::fixed);
		cout << endl;
	}
	cout << "******************************\n";
	delete []p1;
}
void UI::show()
{
	char op;
	while (true)
	{
		
		cout << "***欢迎来到学生信息管理系统***\n";
		cout << "\t1.学生登陆" << endl;
		cout << "\t2.教师登录" << endl;
		cout << "\t3.管理员登录" << endl;
		cout << "\t4.注册账号(学生）" << endl;
		cout << "\t0.退出系统" << endl;
		cout << "******************************\n";
		cout << "请输入你要执行的操作：\0" << endl;
		opera:
		cin >> op;
		switch (op)
		{
		case '1':
			StudentLogin();
			break;
		case '2':
			TeacherLogin();
			break;
		case '3':
			AdminLogin();
			break;
		case '4':
			regis();
			break;
		case '0':
			return;
		default:
			cout << "输入格式不正确，请重新输入：\n\n\n";
			goto opera;
		}
		savedata();
		AccountManager::savedata();
		GradesManagerment::savedata();
		GradesManagerment::savedata();
	}
}
void UI::regis()
{
	string name, ID, password1, password2;
	string qq, phone;
	while (true)
	{
		cout << "请输入你的名字：\n";
		cin >> name;
		cout << "请输入你的学号：\n";
		cin >> ID;
		if (StudentMap.find(ID) != StudentMap.end())
		{
			cout << "该学号已存在！\n\n";
			return;
		}
		cout << "请输入你的密码:\n";
		cin >> password1;
		cout << "请再次输入你的密码:\n";
		cin >> password2;
		if (password1 != password2)
		{
			cout << "密码不匹配，请重新输入\n\n\n";
			continue;
		}
		cout << "请输入你的电话号码:\n";
		cin >> qq;
		cout << "请输入你的qq:\n";
		cin >> phone;
		CreateStudent(name, ID, password1, qq, phone);
		cout << "注册成功!!!\n\n\n";
		break;
	}
	return;
}
void UI::StudentLogin()
{
	system("cls");
	string  ID, password;
	cout << "请输入你的账号：\n";
	cin >> ID;
	cout << "请输入你的密码:\n";
	cin >> password;
	studentUI(&login(ID, password));
}
void UI::studentUI(student* sp)
{
	system("cls");
	if (sp->returnID().empty())
	{
		cout << "登录失败，请检查你的账号或密码\n\n" << endl;
		return;
	}
	cout << "\n\n登陆成功!\n\n" << endl;
	cout << endl;
	string c_ID=sp->returnID();
	while (true)
	{
		sp = StudentMap[c_ID];
		cout << "******************************\n";
		cout << "欢迎您：" << sp->returnName() << endl;
		cout << "\t1.查看个人资料\n";
		cout << "\t2.加入班级\n";
		cout << "\t3.查看同班同学\n";
		cout << "\t4.查看成绩\n\t5.修改密码\n\t6.修改资料\n\t0.退出登录\n";
		cout << "******************************\n";
		int ch = GetInput();
		switch (ch)
		{
		case 1:
			UIs_PersonInformation(sp);
			break;
		case 2:
			UIs_Addclass(sp);
			break;
		case 3:
			UIs_Classmate(sp);
			break;
		case 4:
			UIs_Grade(sp);
			break;
		case 5:
			UIs_changePassword(sp);
			break;
		case 6:
			UIs_changeInf(sp);
			break;
		case 0:
			system("cls");
			return;
		default:
			cout << "输入错误，请重新输入\n";
			break;
		}
	}
}


void UI::UIs_PersonInformation(student* sp)
{
	system("cls");
	cout << endl;
	cout << "姓名：" << sp->returnName() << endl;
	cout << "班级：" << sp->returnClassName() << endl;
	cout << "学号ID：" << sp->returnID() << endl;
	cout << "QQ:" << sp->returnqq() << endl;
	cout << "电话号码：" << sp->returnphone() << endl;
	cout << endl;
}
void UI::UIs_Addclass(student* sp)
{
	system("cls");
	cout << "你目前所在班级：" << sp->returnClassName()<<endl;
	cout << "目前可加入的班级数：" << ClassNum << endl;
	ClassIter = ClassMap.begin();
	int i = 1;
	map<int, string> tempmap;
	while (ClassIter != ClassMap.end())
	{
		cout << i << "." << ClassIter->second.returnClassName() << "  人数：" << ClassIter->second.NumberInClass() << endl;
		tempmap[i] = ClassIter->second.returnClassName();
		i++;
		ClassIter++;
	}
	cout << "0.返回上一步\n";
	cout << "请输入要加入的班级：\n";
	//cout << tempmap[1] << ClassMap.find(tempmap[1])->second.returnClassName();
	int ch;
	string c_ID = sp->returngID();
	while (cin >> ch)
	{
		if (ch >= 1 && ch < i)
		{
			ClassIter = ClassMap.find(tempmap[ch]);
			if (ClassIter->second.returnClassName() == sp->returnClassName())
			{
				cout << "你已经加入了此班级\n" << endl;
				return;
			}
			JoinClass(*sp, (ClassIter->second).returnClassName());
			sp = StudentMap[c_ID];
			cout << "成功加入班级:" << sp->returnClassName() << endl << endl;
			break;
		}
		if (ch == 0) break;
		cout << "输入错误，请重新输入：\n";
	}
}
void UI::UIs_Classmate(student* sp)
{
	system("cls");
	cout << sp->returnClassName();
	map<string,student> p=ClassMap[sp->returnClassName()].GetStup();
	int i = 1;
	map<string, student>::iterator iter = p.begin();
	cout << "内一共有" << p.size() << "个学生\n";
	for (i = 1; i <= p.size(); i++)
	{
		cout << i << "." << iter->second.returnName() << endl;
		iter++;
	}
	cout << "0.返回上一步\n";
	cout << "输入对应号码查看该学生信息\n";
	int ch;
	while (cin >> ch)
	{
		if (ch == 0) return;
		if (ch >= 1 && ch < i)
		{
			iter = p.begin();
			while (--ch) iter++;
			UIs_PersonInformation(&iter->second);
			cout << "0.返回上一步\n";
			cout << "输入对应号码查看同学信息\n";
			continue;
		}
		cout << "输入错误，请重新输入\n";
 	}
}
void UI::UIs_Grade(student* sp)
{
	cout << "\n******************************\n";
	cout << "当前一共有：" << sp->GetNum_Semester() << "个学期\n";
	int i = 1;
	map<string, semester*>::iterator iter = sp->GetGradesIter();
	for (i = 1; i <= sp->GetNum_Semester(); i++)
	{
		cout << i << "." << iter->first << "\n";
		cout << "总学分：" << iter->second->return_total_credit();
		cout << fixed << setprecision(2);
		cout << "   GPA:" << iter->second->returnGPA();
		cout << "   加权平均分:" << iter->second->returnWAM();
		cout.unsetf(ios::fixed);
		cout << endl;
		iter++;
	}
	cout << "0.返回上一步\n";
	cout << "\n******************************\n";
	int ch;
	while (cin >> ch)
	{
		if (ch == 0) break;
		if (ch >= 1 && ch < i)
		{
			iter = sp->GetGradesIter();
			while (--ch) iter++;
			UIs_Grade_Insemester(*sp, iter->first);
			ch = 0;
			while (true)
			{
				cout << endl << endl;
				grades_printInclass(iter->first, sp->returnClassName(),ch+1);
				cout << "\n1.按照GPA排序\n2.按照加权平均分排序\n0.返回上一步\n";
				while (cin >> ch)
				{
					if (ch == 0) return;
					if (ch == 1 || ch == 2) break;
				}
			}
			break;
		}
	}
}
void UI::UIs_changePassword(student* sp)
{
	system("cls");
	string password1, password2;
	cout << "请输入新密码:\n";
	cin >> password1;
	cout << "请再次新密码:\n";
	cin >> password2;
	if (password1 != password2)
	{
		cout << "密码不匹配，请重新输入\n\n\n";
		return;
	}
	sp->set(sp->returnID(), password1);
	cout << "修改密码成功！\n" << endl;
}
void UI::UIs_changeInf(student* sp)
{
	system("cls");
	cout << "1.姓名：" << sp->returnName() <<"(学生)"<< endl;
	cout << "2.QQ:" << sp->returnqq() << endl;
	cout << "3.电话号码：" << sp->returnphone() << endl;
	cout << "0.返回上一步\n";
	cout << "请输入需要修改的信息：(格式：数字+信息)\n";
	int ch; string ifor;
	while (true)
	{
		ch = GetInput();
		if (ch >= 1 && ch <= 3) cin >> ifor;
		switch (ch)
		{
		case 1:
			sp->setname(ifor);
			break;
		case 2:
			sp->setqq(ifor);
			break;
		case 3:
			sp->setphone(ifor);
			break;
		case 0:
			return;
		default:
			cout << "输入错误\n";
			continue;
		}
		break;
	}
}
void UI::UIs_Grade_Insemester(student& sp, string s_name)
{
	cout << endl << endl;
	cout << "姓名：" << sp.returnName() << endl;
	cout << "学期：" << s_name;
	cout << endl;
	semester* p = sp.return_Smap(s_name);
	cout << "总修学分：" << p->return_total_credit();
	cout << fixed << setprecision(2);
	cout <<" GPA:" << p->returnGPA();
	cout << " 加权平均分：" << p->returnWAM();
	cout.unsetf(ios::fixed);
	cout << endl << endl;
	p->iter = p->SubjectMap.begin();
	if (p->iter != p->SubjectMap.end())
		cout << "学科\t\t分数\t学分\t绩点\n";
	while (p->iter != p->SubjectMap.end())
	{
		cout<<p->iter->second.returnName() << "\t\t"<<int(p->iter->second.returnPoint()) << "\t"<<p->iter->second.returnCredit() << "\t"<<p->iter->second.returnGP() << "\t" << endl;
		p->iter++;
	}
	cout << endl;
	return;
}
//管理员界面
void UI::AdminLogin()
{
	system("cls");
	string  ID, password;
	cout << "请输入你的账号：\n";
	cin >> ID;
	cout << "请输入你的密码:\n";
	cin >> password;
	if (!checklogin(ID, password))
	{
		cout << "登录失败！\n\n";
		return;
	}
	cout << "登录成功！！\n\n";
	while (true)
	{
		cout << "******************************\n";
		cout << "\t当前数据库:\n     " << StudentMap.size() << "学生  " << teacherMap.size() << "教师  " << ClassMap.size() << "班级\n";
		cout << "\t1.查看所有学生名单\n";
		cout << "\t2.查看所有教师名单\n";
		cout << "\t3.ID查找学生/教师\n";
		cout << "\t4.班级管理\n";
		cout << "\t5.学期管理\n";
		cout << "\t6.修改管理员密码\n";
		cout << "\t7.保存当前数据库到文件\n";
		cout << "\t0.返回上一步\n";
		cout << "******************************\n";
		int ch;
		ch = GetInput();
		switch (ch)
		{
		case 1:
			UIa_StudentList();
			break;
		case 2:
			UIa_TeacherList();
			break;
		case 3:
			UIa_IDsearch();
			break;
		case 4:
			UIa_ClassManager();
			break;
		case 5:
			UIa_SemesterManager();
			break;
		case 6:
			UIa_ChangePassword();
			break;
		case 7:
			savedata();
			AccountManager::savedata();
			GradesManagerment::savedata();
			GradesManagerment::savedata();
			system("cls");
			cout << "\n保存成功\n";
			break;
		case 0:
			system("cls");
			return;
		default:
			cout << "输入错误,请重新输入\n";
			break;
		}
	}
}
void UI::UIa_StudentList()
{
	system("cls");
	int ch;
	while (true)
	{
		StudentIter = StudentMap.begin();
		int i = 1;
		cout << "编号\t姓名\t\t班级\n";
		while (StudentIter != StudentMap.end())
		{
			cout << i << "\t" << StudentIter->second->returnName() << "\t\t" << StudentIter->second->returnClassName() << endl;
			i++; StudentIter++;
		}
		cout << "输入编号查看详细信息\n0.返回上一步\n";
		cin >> ch;
		if (ch >= 1 && ch < i)
		{
			StudentIter = StudentMap.begin();
			while (--ch) StudentIter++;
			UIs_PersonInformation(StudentIter->second);
			cout << "1.登录该账号\n";
			cout << "2.删除该账号\n";
			cout << "0.返回上一步\n";
			while (cin >> ch)
			{
				if (ch == 1)
				{
					studentUI(StudentIter->second);
					break;
				}
				if (ch == 2)
				{
					deleteStudent(StudentIter->second->returnID());
					cout << "\n删除成功！!\n\n";
					break;
				}
				if (ch == 0) break;
			}
		}
		if (ch == 0) break;
	}
	system("cls");
}
void UI::UIa_TeacherList()
{
	system("cls");
	int ch;
	while (true)
	{
		tMapiter = teacherMap.begin();
		int i = 1;
		cout << "编号\t姓名\t管理班级\n";
		while (tMapiter != teacherMap.end())
		{
			cout << i << "\t" << tMapiter->second.returnName() << "\t" << tMapiter->second.returnClassName() << endl;
			i++; tMapiter++;
		}
		cout << i << "." << "添加新教师\n";
		cout << "\n0.返回上一步\n";
		cin >> ch;
		if (ch >= 1 && ch < i)
		{
			tMapiter = teacherMap.begin();
			while (--ch) tMapiter++;
			UIt_PersonInformation(tMapiter->second);
			cout << "1.登录该账号\n";
			cout << "2.删除该账号\n";
			cout << "0.返回上一步\n";
			while (cin >> ch)
			{
				if (ch == 1)
				{
					teacherUI(tMapiter->second);
					return;
				}
				if (ch == 2)
				{
					deleteTeacher(tMapiter->second.returnID());
					cout << "\n删除成功！\n\n";
					return;
				}
				if (ch == 0) return;
			}
		}
		if (ch == i)
		{
			string c_ID, c_name;
			cout << "输入教师的ID\n";
			cin >> c_ID;
			if (CheckExist(c_ID))
			{
				cout << "该ID已经存在！\n";
				return;
			}
			cout << "输入教师的名字\n";
			cin >> c_name;

			ClassIter = ClassMap.begin();
			int k = 1;
			while (ClassIter != ClassMap.end())
			{
				cout << k << "." << ClassIter->second.returnClassName() << "  人数：" << ClassIter->second.NumberInClass() << endl;
				k++; ClassIter++;
			}
			cout << "请选择该教师需要管理的班级\n";
			while (cin >> ch) 
				if (ch >= 1 && ch < k) break;
			ClassIter = ClassMap.begin();
			while (--ch) ClassIter++;
			newTeacher(c_name, ClassIter->second.returnClassName(),c_ID,c_ID);
			cout << "\n\n创建成功！\n教师的默认密码为自身ID\n\n\n";
		}
		if (ch == 0) return;
	}
}
void UI::UIa_IDsearch()
{
	system("cls");
	cout << "输入ID寻找学生/教师：";
	string c_ID;
	cin >> c_ID;
	if (StudentMap.find(c_ID) != StudentMap.end())
	{
		cout << "\n查找成功！";
		UIs_PersonInformation(StudentMap.find(c_ID)->second);
		cout << "1.登录该账号\n";
		cout << "2.删除该账号\n";
		cout << "0.返回上一步\n";
		int ch;
		while (cin >> ch)
		{
			if (ch == 1)
			{
				studentUI(StudentMap.find(c_ID)->second);
				break;
			}
			if (ch == 2)
			{
				deleteStudent(StudentMap.find(c_ID)->second->returnID());
				break;
			}
			if (ch == 0) break;
		}
		return;
	}
	if (teacherMap.find(c_ID) != teacherMap.end())
	{
		cout << "\n查找成功！";
		cout << teacherMap[c_ID].returnName()<<"(教师)\n";
		cout << "目前管理班级：" << teacherMap[c_ID].returnClassName() << endl;
		cout << "1.登录该账号\n";
		cout << "2.删除该账号\n";
		cout << "0.返回上一步\n";
		int ch;
		while (cin >> ch)
		{
			if (ch == 1)
			{
				studentUI(StudentMap.find(c_ID)->second);
				break;
			}
			if (ch == 2)
			{
				deleteStudent(StudentMap.find(c_ID)->second->returnID());
				break;
			}
			if (ch == 0) break;
		}
		return;
	}
	cout << "没有找到此ID的账号\n\n";
	return;

}
void UI::UIa_ClassManager()
{
	system("cls");
	int ch;
	while (true)
	{
		ClassIter = ClassMap.begin();
		int i = 1;
		while (ClassIter != ClassMap.end())
		{
			cout << i << "." << ClassIter->second.returnClassName() <<"  人数："<< ClassIter->second.NumberInClass() << endl;
			i++; ClassIter++;
		}
		cout << i << ".新增班级" << endl;
		cout << "\n0.返回上一步\n";
		cin >> ch;
		if (ch == i)
		{
			string c_name;
			cout << "输入新班级的名字:\n";
			cin >> c_name;
			if (ClassMap.find(c_name) != ClassMap.end())
			{
				cout << "\n创建失败！该名字的班级已存在\n";
				break;
			}
			newclass(c_name);
			cout << "\n新建班级成功！\n\n";
			break;
		}
		if (ch >= 1 && ch < i)
		{
			cout << "\n\n******************************\n";
			ClassIter = ClassMap.begin();
			while (--ch) ClassIter++;
			cout << ClassIter->second.returnClassName();
			map<string, student> p = ClassMap[ClassIter->second.returnClassName()].GetStup();
			int j = 1;
			map<string, student>::iterator iter = p.begin();
			cout << "内一共有" << p.size() << "个学生\n";
			while (iter!=p.end())
			{
				cout << iter->second.returnName() << endl;
				iter++;
			}
			cout << "1.删除该班级（将会损失所有在该班级的学生数据）\n";
			cout << "0.返回上一步\n";
			while (cin >> ch)
			{
				if (ch == 1)
				{
					if (ClassIter->second.returnClassName() == "None_class")
					{
						cout << "该班级为默认班级，无法被删除！" << endl;
						return;
					}
					cout << "输入Yes确认（区分大小写）\n";
					string input;
					cin >> input;
					if (input != "Yes") break;
					deleteClassp(ClassIter->second.returnClassName());
					cout << "删除成功！！！\n\n";
					return;
				}
				if (ch == 0) break;
			}
		}
		if (ch == 0) break;
	}
}
void UI::UIa_SemesterManager()
{
	system("cls");
	int ch;
	while (true)
	{
		sMapiter = sMap.begin();
		cout << "\n******************************\n";
		cout << "当前一共有：" << sMap.size() << "个年级\n";
		int i = 1;
		while (sMapiter != sMap.end())
		{
			cout << i << "." << sMapiter->first<<endl;
			sMapiter++;
			i++;
		}
		cout << endl << i << ".新增年级" << "\n0.返回上一步\n";
		cin >> ch;
		if (ch >= 1 && ch < i)
		{
			sMapiter = sMap.begin();
			while (--ch) sMapiter++;
			cout << "\n年级：" << sMapiter->first << "\n";
			cout << "1.删除该年级\n";
			cout << "0.返回上一步\n";
			cin >> ch;
			if (ch == 1)
			{
				cout << "输入Yes确认（区分大小写）\n";
				string input;
				cin >> input;
				if (input != "Yes") break;
				GradesManagerment::DeleteSemesters(sMapiter->first);
				cout << "删除成功！！！\n\n";
			}
			break;
		}
		if (ch == i)
		{
			cout << "请输入新的年级名字：\n";
			string name; cin >> name;
			if (sMap.find(name) != sMap.end())
			{
				cout << "该名字已存在！\n";
				break;
			}
			GradesManagerment::NewSemesters(name);
			cout << "\n\n新建成功！！\n";
			break;
		}
		if (ch == 0) break;
	}
}
void UI::UIa_ChangePassword()
{
	system("cls");
	string password1, password2;
	cout << "请输入新密码:\n";
	cin >> password1;
	cout << "请再次新密码:\n";
	cin >> password2;
	if (password1 != password2)
	{
		cout << "密码不匹配，请重新输入\n\n\n";
		return;
	}
	set(ID, password1);
	cout << "修改密码成功！\n" << endl;
}
//教师界面
void UI::TeacherLogin() 
{
	system("cls");
	string  ID, password;
	cout << "请输入你的账号：\n";
	cin >> ID;
	if (teacherMap.find(ID) == teacherMap.end())
	{
		cout << "账号不存在！\n\n\n";
		return;
	}
	cout << "请输入你的密码:\n";
	cin >> password;
	if (teacherMap[ID].checklogin(ID, password))
		teacherUI(teacherMap[ID]);
	else
		cout << "密码错误 ！！！\n\n";
	return;
}
void UI::teacherUI(teacher& tp)
{
	system("cls");
	cout << "登录成功！！！\n\n";
	while (true)
	{
		cout << "\n******************************\n";
		cout << "欢迎您：" << tp.returnName() << endl;
		cout << "\t1.查看个人资料\n";
		cout << "\t2.查看班级名单\n";
		cout << "\t3.查看班级成绩\n";
		cout << "\t4.成绩与科目管理\n\t5.修改密码\n\t0.退出登录\n";
		cout << "\n******************************\n";
		int ch = GetInput();
		switch (ch)
		{
		case 1:
			UIt_PersonInformation(tp);
			break;
		case 2:
			UIt_StudentList(tp);
			break;
		case 3:
			UIt_Grades(tp);
			break;
		case 4:
			UIt_GradeSetting(tp);
			break;
		case 5:
			UIt_changePassword(tp);
			break;
		case 0:
			system("cls");
			return;
		default:
			cout << "输入错误，请重新输入\n";
			break;
		}
	}
}
void UI::UIt_PersonInformation(teacher& tp)
{
	system("cls");
	cout << endl;
	cout << "姓名：" << tp.returnName() << endl;
	cout << "管理班级：" << tp.returnClassName() << endl;
	cout << "ID：" << tp.returnID() << endl;
	cout << endl;
}
void UI::UIt_StudentList(teacher& tp)
{
	system("cls");
	cout << tp.returnClassName();
	map<string, student> p = ClassMap[tp.returnClassName()].GetStup();
	int i = 1;
	map<string, student>::iterator iter = p.begin();
	cout << "内一共有" << p.size() << "个学生\n";
	for (i = 1; i <= p.size(); i++)
	{
		cout << i << "." << iter->second.returnName() << endl;
		iter++;
	}
	cout << "0.返回上一步\n";
	cout << "输入对应号码查看该学生信息\n";
	int ch;
	while (cin >> ch)
	{
		if (ch == 0)
		{
			system("cls");
			return;
		}
		if (ch >= 1 && ch < i)
		{
			iter = p.begin();
			while (--ch) iter++;
			UIs_PersonInformation(&iter->second);
			UIs_Grade(&iter->second);
			break;
		}
		cout << "输入错误，请重新输入\n";
	}
}
void UI::UIt_GradeSetting(teacher& tp)
{
	system("cls");
	while (true)
	{
		cout << "1.添加新科目\n";
		cout << "2.查看班级成绩\n";
		cout << "3.修改学生科目成绩\n";
		cout << "4.删除科目\n";
		cout << "0.返回上一步\n";
		int ch = GetInput();
		switch (ch)
		{
		case 1:
			UIt_addSubject(tp);
			break;
		case 2:
			UIt_Grades(tp);
			break;
		case 3:
			UIt_Grade_change(tp);
			break;
		case 4:
			UIt_deleteSubject(tp);
		case 0:
			return;
		default:

			cout << "输入错误，请重新输入\n";
			break;
		}
	}
	
}
void UI::UIt_Grades(teacher& tp)
{
	system("cls");
	cout << "\n******************************\n";
	cout << "当前一共有：" << sMap.size() << "个学期\n";
	int i = 1;
	sMapiter = sMap.begin();
	for (i = 1; sMapiter!=sMap.end() ; i++)
	{
		cout << i << "." << sMapiter->first ;
		cout << endl;
		sMapiter++;
	}
	cout << endl;
	cout << "0.返回上一步\n";
	int ch;
	while (cin >> ch)
	{
		if (ch == 0) break;
		if (ch >= 1 && ch < i)
		{
			sMapiter = sMap.begin();
			while (--ch) sMapiter++;
			ch = 0;
			while (true)
			{
				cout << endl << endl;
				grades_printInclass(sMapiter->first, tp.returnClassName(), ch + 1);
				cout << "\n1.按照GPA排序\n2.按照加权平均分排序\n0.返回上一步\n";
				while (cin >> ch)
				{
					if (ch == 0) return;
					if (ch == 1 || ch == 2) break;
				}
			}
			break;
		}
	}
}
void UI::UIt_changePassword(teacher& tp)
{
	system("cls");
	string password1, password2;
	cout << "请输入新密码:\n";
	cin >> password1;
	cout << "请再次新密码:\n";
	cin >> password2;
	if (password1 != password2)
	{
		cout << "密码不匹配，请重新输入\n\n\n";
		return;
	}
	tp.set(tp.returnID(), password1);
	cout << "修改密码成功！\n" << endl;
}
void UI::UIt_Grade_change(teacher& sp)
{
	system("cls");
	map<string, student>::iterator iter = ClassMap[sp.returnClassName()].GetStupBegin();
	int i=1;
	int point;
	cout << "选择需要修改的学生：\n";
	while (iter != ClassMap[sp.returnClassName()].GetStupEnd())
	{
		cout << i << "." << iter->second.returnName() << endl;
		iter++;
		i++;
	}
	cout << "0.返回上一步\n";
	int ch;
	while (cin >> ch)
	{
		if (ch >= 1 && ch < i)
		{
			iter = ClassMap[sp.returnClassName()].GetStupBegin();
			while (--ch) iter++;
			break;
		}
		if (ch == 0) return;
	}
	sMapiter = sMap.begin();
	while(sMapiter != sMap.end())
	{
		UIs_Grade_Insemester(iter->second, sMapiter->second.returnName());
		sMapiter++;
	}
	string sems_name, subj_name;
	cout << "\n输入修改信息:\n(格式：学期 科目名 分数）\n 0.返回上一步\n";
	cin >> sems_name;
	if (sems_name == "0") return;
	cin >> subj_name >> point;
	if (sMap.find(sems_name) == sMap.end())
	{
		cout << "不存在该学期\n";
		return;
	}
	if (sMap[sems_name].stup_semMap[iter->second.returnID()].SubjectMap.find(subj_name) == sMap[sems_name].stup_semMap[iter->second.returnID()].SubjectMap.end())
	{
		cout << "不存在该学科\n";
		return;
	}
	sMap[sems_name].stup_semMap[iter->second.returnID()].changeSubject(subj_name, point);
	system("cls");
	cout << "\n修改成功!\n\n";
	return;
}
void UI::UIt_addSubject(teacher& tp)
{
	system("cls");
	map<string, student>::iterator iter = ClassMap[tp.returnClassName()].GetStupBegin();
	cout << "输入添加的科目名：\n";
	string name;
	double credit;
	cin >> name;
	sMapiter = sMap.begin();
	int i;
	for (i = 1; sMapiter != sMap.end(); i++)
	{
		cout << i << "." << sMapiter->first;
		cout << endl;
		sMapiter++;
	}
	cout << "选择添加的学期:\n";
	int ch;
	while (cin >> ch)
	{
		if (ch >= 1 && ch < i)
		{
			sMapiter = sMap.begin();
			while (--ch) sMapiter++;
			break;
		}
	}
	cout << "输入科目所占学分：\n";
	cin >> credit;
	int point;
	while (iter != ClassMap[tp.returnClassName()].GetStupEnd())
	{
		cout << iter->second.returnName() << ":";
		cin >> point;
		iter->second.return_Smap(sMapiter->first)->NewSubject(name, credit, point);
		iter++;
	}
	cout << "\n添加完成！\n\n";
}
void UI::UIt_deleteSubject(teacher& tp)
{
	system("cls");
	cout << "\n输入（学期 科目名）删除学科\n0.返回上一步\n";
	string sems_name, sub_name;
	cin >> sems_name;
	if (sems_name == "0") return;
	if (!checkSemester(sems_name))
	{
		cout << "学期不存在\n"; return;
	}
	cin >> sub_name;
	map<string, student>::iterator iter = ClassMap[tp.returnClassName()].GetStupBegin();
	while (iter != ClassMap[tp.returnClassName()].GetStupEnd())
	{
		if (!iter->second.return_Smap(sems_name)->checksubject(sub_name)) return;
		iter->second.return_Smap(sems_name)->DeleteSubject(sub_name);
		iter++;
	}
	system("cls");
	cout << "\n删除成功\n\n";
}