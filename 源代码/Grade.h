#pragma once
#include<string>
#include<map>
#include<vector>
#include<fstream>
using namespace std;



double Grade_point_cal(double point)
{
	if (point >= 90) return 4.0;
	if (point >= 85) return 3.7;
	if (point >= 82) return 3.3;
	if (point >= 78) return 3.0;
	if (point >= 75) return 2.7;
	if (point >= 71) return 2.3;
	if (point >= 66) return 2.0;
	if (point >= 62) return 1.7;
	if (point >= 60) return 1.3;
	return 0;
}
class subject
{
private:
	string Subject_name;
	double point;   //分数
	double credit;  //学分
	double Grade_point;  //绩点
public:
	void setpoint(double p)
	{
		point = p;
		Grade_point = Grade_point_cal(p);
	}
	subject(string n="0", double c=0) :Subject_name(n), credit(c) { setpoint(0); };
	subject(string n, double c, double p):Subject_name(n), credit(c)
	{
		setpoint(p);
	}
	string returnName() { return Subject_name; }
	double returnPoint() { return point; }
	double returnCredit() { return credit; }
	double returnGP() { return Grade_point; }
};

class semester
{
private:
	string Semester_name;
	double GPA;
	double total_credit;
	double WAM;//Weighted Average Mark
public:
	map<string, subject> SubjectMap;
	map<string, subject>::iterator iter;
	semester(string name="0",double G=0,double W=0) { Semester_name = name; GPA = G; total_credit = 0; WAM = W; }
	void NewSubject(string name, double credit)
	{
		SubjectMap[name] = subject(name, credit);
		Calculater();
	}
	void NewSubject(string name, double credit, double point)
	{
		SubjectMap[name] = subject(name, credit, point);
		Calculater();
	}
	void changeSubject(string name, int point)
	{
		SubjectMap[name].setpoint(point);
	}
	void DeleteSubject(string name) { SubjectMap.erase(name); Calculater();}
	void Calculater();
	string returnName(){ return Semester_name; }
	double returnGPA() { return GPA; }
	double returnWAM() { return WAM; }
	int return_numSubject() { return SubjectMap.size(); }
	double return_total_credit() { Calculater(); return total_credit; }
	bool checksubject(string p) { return SubjectMap.find(p) != SubjectMap.end(); }
};

void semester::Calculater()
{
	iter = SubjectMap.begin();
	total_credit = 0;
	GPA = 0;
	WAM = 0;
	while (iter != SubjectMap.end())
	{
		total_credit += iter->second.returnCredit();
		GPA += iter->second.returnGP() * iter->second.returnCredit();
		WAM += iter->second.returnPoint() * iter->second.returnCredit();
		iter++;
	}
	if (total_credit == 0) return;
	GPA /= total_credit;
	WAM /= total_credit;
	return;
}

class Grades //student基类
{
private:
	string gID;
	map<string, semester*> SemesterMap; //学期名 TO　semester
public:
	map<string, semester*>::iterator GetGradesIter() { return SemesterMap.begin(); }
	Grades(string c_ID) { gID = c_ID; }
	void NewSemester(semester& p) { SemesterMap[p.returnName()] = &p; }
	void NewSemester(semester* p) { SemesterMap[p->returnName()] = p; }
	void Delete_semester(string p) { if(SemesterMap.find(p)!=SemesterMap.end()) SemesterMap.erase(p); }
	semester* return_Smap(string s_name) { return SemesterMap[s_name]; }
	int GetNum_Semester() { return SemesterMap.size(); }
	string returngID() { return gID; }
};

class semesters		//同一个学期内所有学生的数据
{
private:
	string Semester_name;
public:
	map<string, semester> stup_semMap; //学生ID to Semester_name的Semester类
	map<string, semester>::iterator iter;
	semesters(string p="0") { Semester_name = p; }
	semester& GetSemester(string c_ID) { return stup_semMap[c_ID]; }
	void NewStudent(string c_ID,double G = 0, double W = 0) { stup_semMap[c_ID] = semester(Semester_name,G,W); return; }
	void Newsubject(string stud_name, string name, double credit, double point=0) { stup_semMap[stud_name].NewSubject(name, credit, point); }
	void DeleteSubject(string stud_name, string name) { stup_semMap[stud_name].DeleteSubject(name); }
	void Delete_semesters();
	void calculateAll();
	string returnName() { return Semester_name; }
};

void semesters::calculateAll()
{
	iter = stup_semMap.begin();
	while (iter != stup_semMap.end())
	{
		iter->second.Calculater();
		iter++;
	}
	return;
}
void semesters::Delete_semesters()
{
	stup_semMap.clear();
}

class GradesManagerment
{
public:
	map<string, semesters> sMap;	//学期名 to semesters
	map<string, Grades*> gMap;
	map<string, semesters>::iterator sMapiter;
	void readdata();
	void savedata();
	void NewGrades(Grades&);
	void DeleteSemesters(string);
	void deleteGrades(string gID) { sMap.erase(gID); }
	GradesManagerment() { readdata(); }
	~GradesManagerment() { savedata(); }
	semesters& NewSemesters(string p);
	semesters* Getsemesters(string p) { if (sMap.find(p) != sMap.end())return &sMap[p]; else return NULL; }
	int GetNum_Semester() { return sMap.size(); }
	bool checkSemester(string p) { return sMap.find(p) != sMap.end(); }
};

semesters& GradesManagerment::NewSemesters(string p)
{ 
	sMap[p] = semesters(p); 
	semesters* f = &sMap[p];
	map<string, Grades*>::iterator iter = gMap.begin();
	while (iter != gMap.end())
	{
		f->NewStudent(iter->first);
		iter->second->NewSemester(f->GetSemester(iter->first));
		iter++;
	}
	return *f;
}

void GradesManagerment::NewGrades(Grades& p)
{
	gMap[p.returngID()] = &p;
	if (sMap.size() == 0)
		return;
	else
	{
		sMapiter = sMap.begin();
		while (sMapiter != sMap.end())
		{
			p.NewSemester(sMapiter->second.stup_semMap[p.returngID()]);
			//sMapiter->second.stup_semMap[p.returngID()].Calculater();
			sMapiter++;
		}
	}
	return;
}

void GradesManagerment::DeleteSemesters(string s_name)
{
	sMap[s_name].Delete_semesters();
	sMap.erase(s_name);
	map<string, Grades*>::iterator giter=gMap.begin();
	while (giter != gMap.end())
	{
		giter->second->Delete_semester(s_name);
		giter++;
	}
	return;
}

void GradesManagerment::savedata()
{
	/*
	学期总数
	学期名1  学生数目
	ID1 GPA WAM
	学科总数
	学科1 分数1 绩点 学分
	学科2 分数2 绩点 学分
	...
	ID2 GPA WAM
	学科总数 
	学科1 分数1 绩点 学分
	学科2 分数2 绩点 学分
	...
	学期名2
	...
	*/
	fstream outfile("grades.dat", ios::out);
	outfile << sMap.size() << endl;  //学期总数
	sMapiter = sMap.begin(); 
	while (sMapiter != sMap.end()) //遍历所有学期
	{
		outfile << sMapiter->second.returnName() << " " << sMapiter->second.stup_semMap.size() << endl;  //学期名
		map<string, semester>::iterator stup_iter=sMapiter->second.stup_semMap.begin();
		while (stup_iter != sMapiter->second.stup_semMap.end()) //遍历该学期所有学生
		{
			semester& temps = sMapiter->second.GetSemester(stup_iter->first);
			outfile << stup_iter->first << " " << temps.returnGPA() << " " << temps.returnWAM() << endl;//ID GPA WAM
			outfile << temps.return_numSubject() << endl; //学科总数
			temps.iter = temps.SubjectMap.begin();
			while (temps.iter != temps.SubjectMap.end()) //遍历该学生在该学期的所有科目
			{
				outfile << temps.iter->second.returnName() <<" "<< temps.iter->second.returnPoint() << " " << temps.iter->second.returnGP() << " " << temps.iter->second.returnCredit() << endl;
				//学科 分数 绩点 学分
				temps.iter++;
			}
			stup_iter++;
		}
		sMapiter++;
	}
	outfile.close();
}

void GradesManagerment::readdata()
{
	fstream infile("grades.dat", ios::in);
	if (!infile)
	{
		infile.close();
		return;
	}
	int n; infile >> n;
	string subject_name, ID, semester_name;
	int count, num_student, num_subject;
	double point, GPA, AWM, Grade_point, credit;
	while (n--)
	{
		infile >> semester_name>> num_student;
		semesters* p = &NewSemesters(semester_name);
		for (int i = 1; i <= num_student; i++)
		{
			infile >> ID >> GPA >> AWM >> num_subject;
			p->NewStudent(ID, GPA, AWM);
			for (int j = 1; j <= num_subject; j++)
			{
				infile >> subject_name >> point >> Grade_point >> credit;
				p->Newsubject(ID, subject_name, credit, point);
			}
		}
		p->calculateAll();
	}
}
string cmpsem;
bool cmpbyID(Grades* p1, Grades* p2)
{
	return p1->returngID() > p2->returngID();
}
bool cmpbyGPA(Grades* p1, Grades* p2)
{
	return p1->return_Smap(cmpsem)->returnGPA() > p2->return_Smap(cmpsem)->returnGPA();
}
bool cmpbyWAM(Grades* p1, Grades* p2)
{
	return p1->return_Smap(cmpsem)->returnWAM() > p2->return_Smap(cmpsem)->returnWAM();
}
