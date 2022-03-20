#pragma once
#include<fstream>
#include<string>
#include<map>
#include<cmath>
using namespace std;
typedef unsigned long long ull;
const ull base =131;
const int prime = 233317;
const ull mod = 212370440130137957ll;
unsigned long long stringTOhashword(string p) 
{
	ull ret = 0;
	int len = p.length();
	for (int i = 0; i < len; i++)
	{
		ret = (ret * base + (ull)p[i]) % mod + prime;
	}
	return ret;
}

void stringTochar(string p1, char* p2)  //将一个string类型的p1存到p2的char[20]数组里
{
	int len = 19 > p1.length() ? p1.length() : 19;
	for (int i = 0; i < len; i++) p2[i] = p1[i];
	p2[len] = '\0';
}


class Account
{
protected:
	ull* hashword;
	char ID[20];
public:
	Account() { ID[0] = '\0', hashword = 0; };
	void set(string, string);
	void setID(string p) { stringTochar(p, ID); }
	void set_hashword(ull& p) { hashword = &p; }
	bool checklogin(string, string);
	string returnID() { return ID; }
	ull returnhashword() { return *hashword; }
};

void Account::set(string L_ID, string L_password)
{
	stringTochar(L_ID, ID);
	*hashword = stringTOhashword(L_password);
}
bool Account::checklogin(string c_ID, string hw)
{
	string rID = ID;
	if (c_ID == rID && stringTOhashword(hw) == *hashword) return true;
	else return false;
}

class AccountManager
{
public:
	AccountManager();
	~AccountManager() { savedata(); p.clear(); }
	bool login(string, string);
	bool ChangePassword(string, string);
	bool deleteAccount(string);
	void ClearAll() { p.clear(); num = 0; }
	void savedata();
	void NewAccount(Account&);
	void NewAccount(Account&, string, ull);
	void NewAccount(Account* temp, string ID, string hashword) { NewAccount(*temp, ID, stringTOhashword(hashword)); }
	bool readdata();
	int num;
private:
	map<string, ull> p; //ID to Hashword
	map<string, ull>::iterator iter;
};

void AccountManager::savedata()
{
	fstream outfile("Account.dat", ios::binary | ios::out);
	outfile.write((char*)&num, sizeof(int));
	iter = p.begin();
	char cp[20];
	while (iter != p.end())
	{
		string temp1 = iter->first;
		ull temp2 = iter->second;
		stringTochar(temp1, cp);
		outfile.write((char*)&cp,sizeof(cp));
		outfile.write((char*)&temp2, sizeof(temp2));
		iter++;
	}
	outfile.close();
}
bool AccountManager::readdata() //return 是否成功打开文件
{
	fstream infile("Account.dat", ios::binary | ios::in);
	if (!infile) return false;
	infile.read((char*)&num, sizeof(int));
	if (num == 0) return false;
	char str[20];
	ull temp;
	for (int i = 1; i <= num; i++)
	{
		infile.read((char*)&str,sizeof(char[20]));
		infile.read((char*)&temp, sizeof(temp));
		p[str] = temp;
	}
	infile.close();
	return true;
}
bool AccountManager::login(string L_ID, string L_password)
{
	iter = p.find(L_ID);
	if (iter == p.end()) return false;
	if (iter->second != stringTOhashword(L_password)) return false;
	return true;
}

bool AccountManager::deleteAccount(string L_ID)
{
	iter = p.find(L_ID);
	if (iter == p.end()) return false;
	num--;
	p.erase(iter);
}
bool AccountManager::ChangePassword(string L_ID, string L_password)
{
	iter = p.find(L_ID);
	if (iter == p.end()) return false;
	iter->second = stringTOhashword(L_password);
	return true;
}

AccountManager::AccountManager()
{
	num = 0;
	readdata();
	iter = p.begin();
}
void AccountManager::NewAccount(Account& a, string ID, ull hw)
{
	p[ID] = hw;
	a.set_hashword(p[ID]);
	a.setID(ID);
	num++;
}

void AccountManager::NewAccount(Account& a)
{
	if (p.find(a.returnID()) == p.end())
	{
		p[a.returnID()] = stringTOhashword(a.returnID());
	}
	a.set_hashword(p[a.returnID()]);
	a.setID(a.returnID());
	num++;
}