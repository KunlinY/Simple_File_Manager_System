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
//	接受用户的操作
//	接受控制台的输入string类型的用户名 无空格
//	根据用户的操作调用下列三个函数
//	分别是创建新用户 删除用户 登录用户
//create name
//delete name
//log name
//	最终一定要登录用户
//	while循环
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
//	展现所有类常量信息 一行显示一个
//	列出所有用户名字以及所有用户的所占空间大小
//	接口函数showSize()
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
