#include "stdafx.h"
#include "Super.h"


Super::Super()
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
//	����һ��Ҫ��¼�û�
//	whileѭ��
void Super::boot()
{
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
}
