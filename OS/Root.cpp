#include "stdafx.h"
#include "Root.h"


Root::Root(string name) :
	name(name),
	parent(this),
	root(this),
	block(nullptr)
{
}

Root::~Root()
{
	for (auto &r : childs) {
		delete r.second;
	}
}

Root::Root(Root* parent, string name) : 
	name(name), 
	parent(parent), 
	root(parent->root),
	block(nullptr)
{
}

Root::Root(Root * parent, string name, bool flag) :
	name(name),
	parent(parent),
	root(parent->root),
	block(new Block())
{
}

//	TODO
//	�����������ַ���
//	�ʼ����Ϊthis��֮���������Ϊ���غ��Root*
//	ls	����Root*->showChilds
//	cd	����·���Ļ��ȰѲ�����������Ϊ˽�б����е�root
//		��ѭ������visitFile
//		���·��ֱ��ѭ������visitFile
//		֧��../..��.�Ȳ���
//	vi	���ļ��Ļ���ʾ�ļ�����
//		���ǵĻ��ͱ���
//		�����û����벢д��
//	cp	��һ������ΪԴ�ļ� �ڶ�������ΪĿ���ļ�
//		֧��cd�е�����·������ʽ
//		����bool copy()
//	rm	ɾ���ļ� ����bool deleteFile
//	mkdir	�½��ļ��� createRoot
//	touch	�½��ļ� createFile
//	quit	return���ص�Super����
//	���϶���whileѭ�� ����ʧ��Ҫ�ж�Ӧʧ����Ϣ
void Root::run()
{
	string action;
	while (1)
	{
		cin >> action;
		if (action == "ls")
			showChilds();
		else if (action == "cd")
		{
			Root * temp;
			string route;
			cin >> route;
			if (route[0] == '/')
				temp = findExcatRoute(route);
			else
				temp = findRelativeRoute(route);
		}
		else if (action == "vi")
		{
			//���޷��ж��ļ���Ŀ¼
		}
		else if (action == "cp")
		{
			string src, dest;
			cin >> src >> dest;
		}
		else if (action == "rm")
		{
			string file;
			cin >> file;
			if (deleteFile(file))
				cout << "delete complete" << endl;
			else
				cout << "delete error" << endl;
		}
		else if (action == "mkdir")
		{
			string dir;
			cin >> dir;
			if (createRoot(dir) == nullptr)
				cout << "directory construction error" << endl;
			else
				cout << "construction complete" << endl;
		}
		else if (action == "touch")
		{
			string file;
			cin >> file;
			if (createFile(file) == nullptr)
				cout << "file construction error" << endl;
			else
				cout << "construction conplete" << endl;
		}
		else if (action == "quit")
		{
			cout << "go back to super" << endl;
			return;
		}
		else
			cout << "instructions error, please try another time." << endl;
	}
}

Root* Root::createRoot(string name)
{
	if (childs.find(name) == childs.end()) {
		childs[name] = new Root(this, name);
		return childs[name];
	}
	else {
		//cout << "File " << name << " already exists" << endl;
		return nullptr;
	}
}

Root* Root::createFile(string name)
{
	if (childs.find(name) == childs.end()) {
		childs[name] = new Root(this, name, true);
		return childs[name];
	}
	else {
		//cout << "File " << name << " already exist" << endl;
		return nullptr;
	}
}

bool Root::deleteFile(string name)
{
	if (childs.find(name) != childs.end()) {
		delete childs[name];
		childs.erase(name);
		return true;
	}
	else {
		//cout << "File " << name << " not found" << endl;
		return false;
	}
}

Root* Root::visitFile(string name)
{
	if (childs.find(name) != childs.end()) {
		return childs[name];
	}
	else {
		//cout << "File " << name << " not found" << endl;
		return nullptr;
	}
}

Root * Root::visitRoot()
{
	return root;
}

Root * Root::visitParent()
{
	return parent;
}

//	TODO
bool Root::copy(Root * src, Root * dest)
{
	if (!(src && dest)) return false;
	return true;
}


void Root::showChilds()
{
	for (auto &r : childs) {
		cout << r.first << ends;
	}
	cout << endl;
}

void Root::showInfo()
{
	int folderNum = 0;
	int fileNum = 0;
	int size = 0;

	for (auto &r : childs) {
		folderNum += r.second->getFolderNum();
		fileNum += r.second->getFileNum();
		size += r.second->getSize();
	}
	cout << name << " contains "
		<< folderNum << " folders "
		<< fileNum << " files and total size is "
		<< size << "." << endl;
}

int Root::getFolderNum()
{
	int folderNum = 1;
	for (auto &r : childs) {
		folderNum += r.second->getFolderNum();
	}
	return folderNum;
}

int Root::getFileNum()
{
	int fileNum = 0;
	for (auto &r : childs) {
		if (r.second->block != nullptr) {
			fileNum++;
		}
		else {
			fileNum += r.second->getFileNum();
		}
	}
	return fileNum;
}

int Root::getSize()
{
	if (block != nullptr) {
		return block->size();
	}

	int size = 0;
	for (auto &r : childs) {
		size += r.second->getSize();
	}
	return size;
}

string Root::read()
{
	if (block == nullptr) return "";
	return block->content();
}

bool Root::write(string content)
{
	if (block == nullptr) return false;
	return block->write(content);
}

bool Root::isFile()
{
	return block;
}

Root * Root::DownToFile(string route)
{
	Root * temp;
	int pos = route.find('/');
	if (pos == -1)
	{
		temp = visitFile(route);
		route = "";
	}
	else
	{
		temp = visitFile(route.substr(0, pos + 1));
		route = route.substr(pos + 1, route.length() - pos - 1);
	}
	return temp;
}

Root * Root::findExcatRoute(string route)
{
	Root * temp;

	temp = root;
	route = route.substr(1, route.length() - 1);
	while (!route.empty())
		temp = DownToFile(route);
	return temp;
}

Root * Root::findRelativeRoute(string route)
{
	Root * temp;
	while (!route.empty())
	{
		if (route.substr(0, 3) == "../")
		{
			temp = parent;
			route = route.substr(3, route.length() - 3);
		}
		else
			temp = DownToFile(route);
		
	}
	return temp;
}


