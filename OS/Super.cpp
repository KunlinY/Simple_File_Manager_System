#include "stdafx.h"
#include "Super.h"


Super::Super()
{
}

Super::Super(bool flag)
{
	Block block[3];
	block[1].load();
	istringstream user(block[0].content()), record(block[2].content());

	string temp;
	while (user >> temp) {
		createUser(temp);
	}

	string name, parent;
	long long time;
	int next;
	Root* root = nullptr;
	while (record >> name >> parent >> time >> next) {
		if (flag) {
			flag = false;
			root = users[parent];
			continue;
		}
		if (root->getName() == parent) {
			root = new Root(root, name, time, next);
			continue;
		}

		while (root->getName() != parent) {
			if (root->visitParent() == root) {
				if (root->getName() != parent)
					root = users[parent];
				else 
					flag = true;
				
				break;
			}
			root = root->visitParent();
		}

		if (!flag) 
			root = new Root(root, name, time, next);
	}


	boot();
}

Super::~Super()
{
	string user, record;

	map<string, Root*>::iterator it;
	it = users.begin();
	while (it != users.end())
	{
		user += it->first + " ";
		it++;
	}

	it = users.begin();
	while (it != users.end()) {
		record += it->second->getRecord();
		it++;
	}

	Block::save(user, record);
}

void Super::boot()
{
	while (1)
	{
		cout << "******************************\n"
			<< "create user: create + username + 'enter'\n"
			<< "delete user: delete + username + 'enter'\n"
			<< "log user: log + username + 'enter' + ':q:\n"
			<< "shut down: shut down + 'enter'" << endl
			<< "show info: show info + 'enter'" << endl
			<< "remark: if you create a new user, you need to relog\n"
			<< "******************************\n";
		string action, name;
		cin >> action >> name;
		if (action == "create")
		{
			if (createUser(name))
				cout << "create " << name << " success" << endl;
			else
				cout << "create error" << endl;
		}
		else if (action == "delete")
		{
			if (deleteUser(name))
				cout << "delete " << name << " success" << endl;
			else
				cout << "delete error" << endl;
		}
		else if (action == "log")
		{
			if (logUser(name))
			{
				cout << "log " << name << " success" << endl;
				users[name]->run();
				continue;
			}
			else
				cout << "log error" << endl;
		}
		else if (action == "shut") {
			break;
		}
		else if (action == "show") {
			showInfo();
			continue;
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
		return true;
	}
	else {
		cout << "User " << name << " doesn't exist" << endl;
		return false;
	}
}

void Super::showInfo()
{
	map<string, Root*>::iterator it;
	it = users.begin();
	while (it != users.end())
	{
		cout << it->first << "\t" << it->second->getSize() << " block" << endl;
		it++;
	}
}
