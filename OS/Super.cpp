#include "stdafx.h"
#include "Super.h"


Super::Super()
{
}

Super::Super(bool flag)
{
	boot();
}


Super::~Super()
{
}

//	TODO
//	�����û��Ĳ���
//	���ܿ���̨������string���͵��û��� �޿ո�
//	�����û��Ĳ�������������������
//	�ֱ��Ǵ������û� ɾ���û� ��¼�û�
//create name
//delete name
//log name
//	����һ��Ҫ��¼�û�
//	whileѭ��
void Super::boot()
{
	while (1)
	{
		string action, name;
		cin >> action >> name;
		if (action == "create")
		{
			if (createUser(name))
				cout << "create " << name << "success" << endl;
			else
				cout << "create error" << endl;
		}
		else if (action == "delete")
		{
			if (deleteUser(name))
				cout << "delete " << name << "success" << endl;
			else
				cout << "delete error" << endl;
		}
		else if (action == "log")
		{
			if (logUser(name))
			{
				cout << "log " << name << "success" << endl;
				return;
			}
			else
				cout << "log error" << endl;
		}
		cout << "please log in" << endl;
	}
}


bool Super::createUser(string name)
{
	if (users.find(name) == users.end()) {
		users[name] = new Root(name);
		return true;
	}
	else {
		cout << "User " << name << " already exists" << endl;
		return false;
	}
}


bool Super::deleteUser(string name)
{
	if (users.find(name) != users.end()) {
		users.erase(users.find(name));
		return true;
	}
	else {
		cout << "User " << name << " doesn't exist" << endl;
		cout << "Delete failed!" << endl;
		return false;
	}
}


bool Super::logUser(string name)
{
	if (users.find(name) != users.end()) {
		users[name]->run();
		return true;
	}
	else {
		cout << "User " << name << " doesn't exist" << endl;
		return false;
	}
}


//	TODO
//	չ�������ೣ����Ϣ һ����ʾһ��
//	�г������û������Լ������û�����ռ�ռ��С
//	�ӿں���showSize()
void Super::showInfo()
{
	map<string, Root*>::iterator it;
	it = users.begin();
	while (it != users.end())
	{
		//cout << it->first << it->second->showSize() << endl;
		it++;
	}
}
