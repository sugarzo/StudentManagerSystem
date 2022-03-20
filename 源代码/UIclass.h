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
		//ѧ������
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
		//��ʦ����
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
		//����Ա����
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
	type==1 ѧ������
	type==2 GPA����
	type==3 WAM����
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
	cout << "�ð๲�У�" << n << "��ѧ��\n";
	cout << "******************************\n";
	cout << "����\t����\tGPA\t��Ȩƽ����\n";
	for (int i = 0; i < n; i++)
	{
		cout  << i + 1 << "\t" << p1[i]->returnName() << "\t";	
		cout << fixed << setprecision(2);
		cout  << p1[i]->return_Smap(sem_name)->returnGPA() << "\t" << "��Ȩƽ����:" << p1[i]->return_Smap(sem_name)->returnWAM();
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
		
		cout << "***��ӭ����ѧ����Ϣ����ϵͳ***\n";
		cout << "\t1.ѧ����½" << endl;
		cout << "\t2.��ʦ��¼" << endl;
		cout << "\t3.����Ա��¼" << endl;
		cout << "\t4.ע���˺�(ѧ����" << endl;
		cout << "\t0.�˳�ϵͳ" << endl;
		cout << "******************************\n";
		cout << "��������Ҫִ�еĲ�����\0" << endl;
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
			cout << "�����ʽ����ȷ�����������룺\n\n\n";
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
		cout << "������������֣�\n";
		cin >> name;
		cout << "���������ѧ�ţ�\n";
		cin >> ID;
		if (StudentMap.find(ID) != StudentMap.end())
		{
			cout << "��ѧ���Ѵ��ڣ�\n\n";
			return;
		}
		cout << "�������������:\n";
		cin >> password1;
		cout << "���ٴ������������:\n";
		cin >> password2;
		if (password1 != password2)
		{
			cout << "���벻ƥ�䣬����������\n\n\n";
			continue;
		}
		cout << "��������ĵ绰����:\n";
		cin >> qq;
		cout << "���������qq:\n";
		cin >> phone;
		CreateStudent(name, ID, password1, qq, phone);
		cout << "ע��ɹ�!!!\n\n\n";
		break;
	}
	return;
}
void UI::StudentLogin()
{
	system("cls");
	string  ID, password;
	cout << "����������˺ţ�\n";
	cin >> ID;
	cout << "�������������:\n";
	cin >> password;
	studentUI(&login(ID, password));
}
void UI::studentUI(student* sp)
{
	system("cls");
	if (sp->returnID().empty())
	{
		cout << "��¼ʧ�ܣ���������˺Ż�����\n\n" << endl;
		return;
	}
	cout << "\n\n��½�ɹ�!\n\n" << endl;
	cout << endl;
	string c_ID=sp->returnID();
	while (true)
	{
		sp = StudentMap[c_ID];
		cout << "******************************\n";
		cout << "��ӭ����" << sp->returnName() << endl;
		cout << "\t1.�鿴��������\n";
		cout << "\t2.����༶\n";
		cout << "\t3.�鿴ͬ��ͬѧ\n";
		cout << "\t4.�鿴�ɼ�\n\t5.�޸�����\n\t6.�޸�����\n\t0.�˳���¼\n";
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
			cout << "�����������������\n";
			break;
		}
	}
}


void UI::UIs_PersonInformation(student* sp)
{
	system("cls");
	cout << endl;
	cout << "������" << sp->returnName() << endl;
	cout << "�༶��" << sp->returnClassName() << endl;
	cout << "ѧ��ID��" << sp->returnID() << endl;
	cout << "QQ:" << sp->returnqq() << endl;
	cout << "�绰���룺" << sp->returnphone() << endl;
	cout << endl;
}
void UI::UIs_Addclass(student* sp)
{
	system("cls");
	cout << "��Ŀǰ���ڰ༶��" << sp->returnClassName()<<endl;
	cout << "Ŀǰ�ɼ���İ༶����" << ClassNum << endl;
	ClassIter = ClassMap.begin();
	int i = 1;
	map<int, string> tempmap;
	while (ClassIter != ClassMap.end())
	{
		cout << i << "." << ClassIter->second.returnClassName() << "  ������" << ClassIter->second.NumberInClass() << endl;
		tempmap[i] = ClassIter->second.returnClassName();
		i++;
		ClassIter++;
	}
	cout << "0.������һ��\n";
	cout << "������Ҫ����İ༶��\n";
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
				cout << "���Ѿ������˴˰༶\n" << endl;
				return;
			}
			JoinClass(*sp, (ClassIter->second).returnClassName());
			sp = StudentMap[c_ID];
			cout << "�ɹ�����༶:" << sp->returnClassName() << endl << endl;
			break;
		}
		if (ch == 0) break;
		cout << "����������������룺\n";
	}
}
void UI::UIs_Classmate(student* sp)
{
	system("cls");
	cout << sp->returnClassName();
	map<string,student> p=ClassMap[sp->returnClassName()].GetStup();
	int i = 1;
	map<string, student>::iterator iter = p.begin();
	cout << "��һ����" << p.size() << "��ѧ��\n";
	for (i = 1; i <= p.size(); i++)
	{
		cout << i << "." << iter->second.returnName() << endl;
		iter++;
	}
	cout << "0.������һ��\n";
	cout << "�����Ӧ����鿴��ѧ����Ϣ\n";
	int ch;
	while (cin >> ch)
	{
		if (ch == 0) return;
		if (ch >= 1 && ch < i)
		{
			iter = p.begin();
			while (--ch) iter++;
			UIs_PersonInformation(&iter->second);
			cout << "0.������һ��\n";
			cout << "�����Ӧ����鿴ͬѧ��Ϣ\n";
			continue;
		}
		cout << "�����������������\n";
 	}
}
void UI::UIs_Grade(student* sp)
{
	cout << "\n******************************\n";
	cout << "��ǰһ���У�" << sp->GetNum_Semester() << "��ѧ��\n";
	int i = 1;
	map<string, semester*>::iterator iter = sp->GetGradesIter();
	for (i = 1; i <= sp->GetNum_Semester(); i++)
	{
		cout << i << "." << iter->first << "\n";
		cout << "��ѧ�֣�" << iter->second->return_total_credit();
		cout << fixed << setprecision(2);
		cout << "   GPA:" << iter->second->returnGPA();
		cout << "   ��Ȩƽ����:" << iter->second->returnWAM();
		cout.unsetf(ios::fixed);
		cout << endl;
		iter++;
	}
	cout << "0.������һ��\n";
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
				cout << "\n1.����GPA����\n2.���ռ�Ȩƽ��������\n0.������һ��\n";
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
	cout << "������������:\n";
	cin >> password1;
	cout << "���ٴ�������:\n";
	cin >> password2;
	if (password1 != password2)
	{
		cout << "���벻ƥ�䣬����������\n\n\n";
		return;
	}
	sp->set(sp->returnID(), password1);
	cout << "�޸�����ɹ���\n" << endl;
}
void UI::UIs_changeInf(student* sp)
{
	system("cls");
	cout << "1.������" << sp->returnName() <<"(ѧ��)"<< endl;
	cout << "2.QQ:" << sp->returnqq() << endl;
	cout << "3.�绰���룺" << sp->returnphone() << endl;
	cout << "0.������һ��\n";
	cout << "��������Ҫ�޸ĵ���Ϣ��(��ʽ������+��Ϣ)\n";
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
			cout << "�������\n";
			continue;
		}
		break;
	}
}
void UI::UIs_Grade_Insemester(student& sp, string s_name)
{
	cout << endl << endl;
	cout << "������" << sp.returnName() << endl;
	cout << "ѧ�ڣ�" << s_name;
	cout << endl;
	semester* p = sp.return_Smap(s_name);
	cout << "����ѧ�֣�" << p->return_total_credit();
	cout << fixed << setprecision(2);
	cout <<" GPA:" << p->returnGPA();
	cout << " ��Ȩƽ���֣�" << p->returnWAM();
	cout.unsetf(ios::fixed);
	cout << endl << endl;
	p->iter = p->SubjectMap.begin();
	if (p->iter != p->SubjectMap.end())
		cout << "ѧ��\t\t����\tѧ��\t����\n";
	while (p->iter != p->SubjectMap.end())
	{
		cout<<p->iter->second.returnName() << "\t\t"<<int(p->iter->second.returnPoint()) << "\t"<<p->iter->second.returnCredit() << "\t"<<p->iter->second.returnGP() << "\t" << endl;
		p->iter++;
	}
	cout << endl;
	return;
}
//����Ա����
void UI::AdminLogin()
{
	system("cls");
	string  ID, password;
	cout << "����������˺ţ�\n";
	cin >> ID;
	cout << "�������������:\n";
	cin >> password;
	if (!checklogin(ID, password))
	{
		cout << "��¼ʧ�ܣ�\n\n";
		return;
	}
	cout << "��¼�ɹ�����\n\n";
	while (true)
	{
		cout << "******************************\n";
		cout << "\t��ǰ���ݿ�:\n     " << StudentMap.size() << "ѧ��  " << teacherMap.size() << "��ʦ  " << ClassMap.size() << "�༶\n";
		cout << "\t1.�鿴����ѧ������\n";
		cout << "\t2.�鿴���н�ʦ����\n";
		cout << "\t3.ID����ѧ��/��ʦ\n";
		cout << "\t4.�༶����\n";
		cout << "\t5.ѧ�ڹ���\n";
		cout << "\t6.�޸Ĺ���Ա����\n";
		cout << "\t7.���浱ǰ���ݿ⵽�ļ�\n";
		cout << "\t0.������һ��\n";
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
			cout << "\n����ɹ�\n";
			break;
		case 0:
			system("cls");
			return;
		default:
			cout << "�������,����������\n";
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
		cout << "���\t����\t\t�༶\n";
		while (StudentIter != StudentMap.end())
		{
			cout << i << "\t" << StudentIter->second->returnName() << "\t\t" << StudentIter->second->returnClassName() << endl;
			i++; StudentIter++;
		}
		cout << "�����Ų鿴��ϸ��Ϣ\n0.������һ��\n";
		cin >> ch;
		if (ch >= 1 && ch < i)
		{
			StudentIter = StudentMap.begin();
			while (--ch) StudentIter++;
			UIs_PersonInformation(StudentIter->second);
			cout << "1.��¼���˺�\n";
			cout << "2.ɾ�����˺�\n";
			cout << "0.������һ��\n";
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
					cout << "\nɾ���ɹ���!\n\n";
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
		cout << "���\t����\t����༶\n";
		while (tMapiter != teacherMap.end())
		{
			cout << i << "\t" << tMapiter->second.returnName() << "\t" << tMapiter->second.returnClassName() << endl;
			i++; tMapiter++;
		}
		cout << i << "." << "����½�ʦ\n";
		cout << "\n0.������һ��\n";
		cin >> ch;
		if (ch >= 1 && ch < i)
		{
			tMapiter = teacherMap.begin();
			while (--ch) tMapiter++;
			UIt_PersonInformation(tMapiter->second);
			cout << "1.��¼���˺�\n";
			cout << "2.ɾ�����˺�\n";
			cout << "0.������һ��\n";
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
					cout << "\nɾ���ɹ���\n\n";
					return;
				}
				if (ch == 0) return;
			}
		}
		if (ch == i)
		{
			string c_ID, c_name;
			cout << "�����ʦ��ID\n";
			cin >> c_ID;
			if (CheckExist(c_ID))
			{
				cout << "��ID�Ѿ����ڣ�\n";
				return;
			}
			cout << "�����ʦ������\n";
			cin >> c_name;

			ClassIter = ClassMap.begin();
			int k = 1;
			while (ClassIter != ClassMap.end())
			{
				cout << k << "." << ClassIter->second.returnClassName() << "  ������" << ClassIter->second.NumberInClass() << endl;
				k++; ClassIter++;
			}
			cout << "��ѡ��ý�ʦ��Ҫ����İ༶\n";
			while (cin >> ch) 
				if (ch >= 1 && ch < k) break;
			ClassIter = ClassMap.begin();
			while (--ch) ClassIter++;
			newTeacher(c_name, ClassIter->second.returnClassName(),c_ID,c_ID);
			cout << "\n\n�����ɹ���\n��ʦ��Ĭ������Ϊ����ID\n\n\n";
		}
		if (ch == 0) return;
	}
}
void UI::UIa_IDsearch()
{
	system("cls");
	cout << "����IDѰ��ѧ��/��ʦ��";
	string c_ID;
	cin >> c_ID;
	if (StudentMap.find(c_ID) != StudentMap.end())
	{
		cout << "\n���ҳɹ���";
		UIs_PersonInformation(StudentMap.find(c_ID)->second);
		cout << "1.��¼���˺�\n";
		cout << "2.ɾ�����˺�\n";
		cout << "0.������һ��\n";
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
		cout << "\n���ҳɹ���";
		cout << teacherMap[c_ID].returnName()<<"(��ʦ)\n";
		cout << "Ŀǰ����༶��" << teacherMap[c_ID].returnClassName() << endl;
		cout << "1.��¼���˺�\n";
		cout << "2.ɾ�����˺�\n";
		cout << "0.������һ��\n";
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
	cout << "û���ҵ���ID���˺�\n\n";
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
			cout << i << "." << ClassIter->second.returnClassName() <<"  ������"<< ClassIter->second.NumberInClass() << endl;
			i++; ClassIter++;
		}
		cout << i << ".�����༶" << endl;
		cout << "\n0.������һ��\n";
		cin >> ch;
		if (ch == i)
		{
			string c_name;
			cout << "�����°༶������:\n";
			cin >> c_name;
			if (ClassMap.find(c_name) != ClassMap.end())
			{
				cout << "\n����ʧ�ܣ������ֵİ༶�Ѵ���\n";
				break;
			}
			newclass(c_name);
			cout << "\n�½��༶�ɹ���\n\n";
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
			cout << "��һ����" << p.size() << "��ѧ��\n";
			while (iter!=p.end())
			{
				cout << iter->second.returnName() << endl;
				iter++;
			}
			cout << "1.ɾ���ð༶��������ʧ�����ڸð༶��ѧ�����ݣ�\n";
			cout << "0.������һ��\n";
			while (cin >> ch)
			{
				if (ch == 1)
				{
					if (ClassIter->second.returnClassName() == "None_class")
					{
						cout << "�ð༶ΪĬ�ϰ༶���޷���ɾ����" << endl;
						return;
					}
					cout << "����Yesȷ�ϣ����ִ�Сд��\n";
					string input;
					cin >> input;
					if (input != "Yes") break;
					deleteClassp(ClassIter->second.returnClassName());
					cout << "ɾ���ɹ�������\n\n";
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
		cout << "��ǰһ���У�" << sMap.size() << "���꼶\n";
		int i = 1;
		while (sMapiter != sMap.end())
		{
			cout << i << "." << sMapiter->first<<endl;
			sMapiter++;
			i++;
		}
		cout << endl << i << ".�����꼶" << "\n0.������һ��\n";
		cin >> ch;
		if (ch >= 1 && ch < i)
		{
			sMapiter = sMap.begin();
			while (--ch) sMapiter++;
			cout << "\n�꼶��" << sMapiter->first << "\n";
			cout << "1.ɾ�����꼶\n";
			cout << "0.������һ��\n";
			cin >> ch;
			if (ch == 1)
			{
				cout << "����Yesȷ�ϣ����ִ�Сд��\n";
				string input;
				cin >> input;
				if (input != "Yes") break;
				GradesManagerment::DeleteSemesters(sMapiter->first);
				cout << "ɾ���ɹ�������\n\n";
			}
			break;
		}
		if (ch == i)
		{
			cout << "�������µ��꼶���֣�\n";
			string name; cin >> name;
			if (sMap.find(name) != sMap.end())
			{
				cout << "�������Ѵ��ڣ�\n";
				break;
			}
			GradesManagerment::NewSemesters(name);
			cout << "\n\n�½��ɹ�����\n";
			break;
		}
		if (ch == 0) break;
	}
}
void UI::UIa_ChangePassword()
{
	system("cls");
	string password1, password2;
	cout << "������������:\n";
	cin >> password1;
	cout << "���ٴ�������:\n";
	cin >> password2;
	if (password1 != password2)
	{
		cout << "���벻ƥ�䣬����������\n\n\n";
		return;
	}
	set(ID, password1);
	cout << "�޸�����ɹ���\n" << endl;
}
//��ʦ����
void UI::TeacherLogin() 
{
	system("cls");
	string  ID, password;
	cout << "����������˺ţ�\n";
	cin >> ID;
	if (teacherMap.find(ID) == teacherMap.end())
	{
		cout << "�˺Ų����ڣ�\n\n\n";
		return;
	}
	cout << "�������������:\n";
	cin >> password;
	if (teacherMap[ID].checklogin(ID, password))
		teacherUI(teacherMap[ID]);
	else
		cout << "������� ������\n\n";
	return;
}
void UI::teacherUI(teacher& tp)
{
	system("cls");
	cout << "��¼�ɹ�������\n\n";
	while (true)
	{
		cout << "\n******************************\n";
		cout << "��ӭ����" << tp.returnName() << endl;
		cout << "\t1.�鿴��������\n";
		cout << "\t2.�鿴�༶����\n";
		cout << "\t3.�鿴�༶�ɼ�\n";
		cout << "\t4.�ɼ����Ŀ����\n\t5.�޸�����\n\t0.�˳���¼\n";
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
			cout << "�����������������\n";
			break;
		}
	}
}
void UI::UIt_PersonInformation(teacher& tp)
{
	system("cls");
	cout << endl;
	cout << "������" << tp.returnName() << endl;
	cout << "����༶��" << tp.returnClassName() << endl;
	cout << "ID��" << tp.returnID() << endl;
	cout << endl;
}
void UI::UIt_StudentList(teacher& tp)
{
	system("cls");
	cout << tp.returnClassName();
	map<string, student> p = ClassMap[tp.returnClassName()].GetStup();
	int i = 1;
	map<string, student>::iterator iter = p.begin();
	cout << "��һ����" << p.size() << "��ѧ��\n";
	for (i = 1; i <= p.size(); i++)
	{
		cout << i << "." << iter->second.returnName() << endl;
		iter++;
	}
	cout << "0.������һ��\n";
	cout << "�����Ӧ����鿴��ѧ����Ϣ\n";
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
		cout << "�����������������\n";
	}
}
void UI::UIt_GradeSetting(teacher& tp)
{
	system("cls");
	while (true)
	{
		cout << "1.����¿�Ŀ\n";
		cout << "2.�鿴�༶�ɼ�\n";
		cout << "3.�޸�ѧ����Ŀ�ɼ�\n";
		cout << "4.ɾ����Ŀ\n";
		cout << "0.������һ��\n";
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

			cout << "�����������������\n";
			break;
		}
	}
	
}
void UI::UIt_Grades(teacher& tp)
{
	system("cls");
	cout << "\n******************************\n";
	cout << "��ǰһ���У�" << sMap.size() << "��ѧ��\n";
	int i = 1;
	sMapiter = sMap.begin();
	for (i = 1; sMapiter!=sMap.end() ; i++)
	{
		cout << i << "." << sMapiter->first ;
		cout << endl;
		sMapiter++;
	}
	cout << endl;
	cout << "0.������һ��\n";
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
				cout << "\n1.����GPA����\n2.���ռ�Ȩƽ��������\n0.������һ��\n";
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
	cout << "������������:\n";
	cin >> password1;
	cout << "���ٴ�������:\n";
	cin >> password2;
	if (password1 != password2)
	{
		cout << "���벻ƥ�䣬����������\n\n\n";
		return;
	}
	tp.set(tp.returnID(), password1);
	cout << "�޸�����ɹ���\n" << endl;
}
void UI::UIt_Grade_change(teacher& sp)
{
	system("cls");
	map<string, student>::iterator iter = ClassMap[sp.returnClassName()].GetStupBegin();
	int i=1;
	int point;
	cout << "ѡ����Ҫ�޸ĵ�ѧ����\n";
	while (iter != ClassMap[sp.returnClassName()].GetStupEnd())
	{
		cout << i << "." << iter->second.returnName() << endl;
		iter++;
		i++;
	}
	cout << "0.������һ��\n";
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
	cout << "\n�����޸���Ϣ:\n(��ʽ��ѧ�� ��Ŀ�� ������\n 0.������һ��\n";
	cin >> sems_name;
	if (sems_name == "0") return;
	cin >> subj_name >> point;
	if (sMap.find(sems_name) == sMap.end())
	{
		cout << "�����ڸ�ѧ��\n";
		return;
	}
	if (sMap[sems_name].stup_semMap[iter->second.returnID()].SubjectMap.find(subj_name) == sMap[sems_name].stup_semMap[iter->second.returnID()].SubjectMap.end())
	{
		cout << "�����ڸ�ѧ��\n";
		return;
	}
	sMap[sems_name].stup_semMap[iter->second.returnID()].changeSubject(subj_name, point);
	system("cls");
	cout << "\n�޸ĳɹ�!\n\n";
	return;
}
void UI::UIt_addSubject(teacher& tp)
{
	system("cls");
	map<string, student>::iterator iter = ClassMap[tp.returnClassName()].GetStupBegin();
	cout << "������ӵĿ�Ŀ����\n";
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
	cout << "ѡ����ӵ�ѧ��:\n";
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
	cout << "�����Ŀ��ռѧ�֣�\n";
	cin >> credit;
	int point;
	while (iter != ClassMap[tp.returnClassName()].GetStupEnd())
	{
		cout << iter->second.returnName() << ":";
		cin >> point;
		iter->second.return_Smap(sMapiter->first)->NewSubject(name, credit, point);
		iter++;
	}
	cout << "\n�����ɣ�\n\n";
}
void UI::UIt_deleteSubject(teacher& tp)
{
	system("cls");
	cout << "\n���루ѧ�� ��Ŀ����ɾ��ѧ��\n0.������һ��\n";
	string sems_name, sub_name;
	cin >> sems_name;
	if (sems_name == "0") return;
	if (!checkSemester(sems_name))
	{
		cout << "ѧ�ڲ�����\n"; return;
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
	cout << "\nɾ���ɹ�\n\n";
}