#include "stdafx.h"
#include "Root.h"


Root::Root(string name) :
	name(name),
	parent(this),
	root(this),
	block(nullptr)	
{
	time(&createTime);
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
	time(&createTime);
}

Root::Root(Root * parent, string name, bool flag) :
	name(name),
	parent(parent),
	root(parent->root),
	block(new Block())
{
	time(&createTime);
}

Root::Root(Root * parent, string name, long long time, int id) :
	name(name),
	parent(parent),
	createTime(time)
{
	if (id > 0) {
		block = new Block(id, time);
		//cout << block->content();
	}
	else
		block = nullptr;

	parent->childs[name] = this;
}

//	TODO
//	接受命令行字符串
//	最开始对象为this，之后操作对象为返回后的Root*
//	ls	调用Root*->showChilds
//	cd	绝对路径的话先把操作对象设置为私有变量中的root
//		再循环调用visitFile
//		相对路径直接循环调用visitFile
//		支持../..、.等操作
//	vi	是文件的话显示文件内容
//		不是的话就报错
//		接受用户输入并写入
//	cp	第一个参数为源文件 第二个参数为目的文件
//		支持cd中的所有路径表达格式
//		调用bool copy()
//	rm	删除文件 调用bool deleteFile
//	mkdir	新建文件夹 createRoot
//	touch	新建文件 createFile
//	quit	return，回到Super界面
//	以上都是while循环 操作失败要有对应失败信息
void Root::run()
{
	Root * temp = this;
	string action;
	while (1)
	{
		cin >> action;
		if (action == "ls")
			temp->showChilds();
		else if (action == "cd")
		{
			Root * test;
			string route;
			cin >> route;

			test = temp->findRoute(route);

			if (test != nullptr && !test->isFile())
				temp = test;
		}
		else if (action == "vi")
		{
			Root * working;
			string route, instruction, content, add;
			cin >> route;
			working = temp->findRoute(route);
			if (working == nullptr || !working->isFile())
				continue;

			

			while (1)
			{
				content = working->read();
				cout << content << endl;
				cout << "******************************\n"
					<< "write: 1 + 'enter'\n"
					<< "clear: 2 + 'enter'\n"
					<< "quit: 3 + 'enter'\n"
					<< "quit writing: 'enter' + ':q'\n"
					<< "******************************\n";

				cin >> instruction;
				if (instruction == "1")
				{
					while (1)
					{
						getline(cin, add);
						if (add == ":q")
							break;
						content = content + add + "\n";
					}
					if (working->write(content))
						cout << "writing complete" << endl;
					else
						cout << "writing error" << endl;

					cout << "new version：\n" << content << endl;
				}
				else if (instruction == "2")
				{
					char flag;
					cout << "are you sure? all content will be cleared![y/n]" << endl;
					cin >> flag;
					if (flag == 'y')
						if (working->write(""))
							cout << "clear complete" << endl;
						else
							cout << "clear error" << endl;
				}
				else if (instruction == "3")
				{
					cout << "quit the 'vi' system" << endl;
					break;
				}
				else
				{
					cout << "invalid input! try again" << endl;
				}
			}
		}
		else if (action == "cp")
		{
			Root * location, *dest;
			string src, route;
			cin >> src >> route;
			location = temp->findRoute(route);
			if (location == nullptr)
				continue;
			
			
			if ((dest = location->createFile(src.substr(src.find_last_of('\\') + 1))) == nullptr)
				cout << "file construction error" << endl;
			else
				cout << "construction complete" << endl;
			if (!copy(src, dest))
				cout << "copy error" << endl;
		}
		else if (action == "rm")
		{
			string file;
			cin >> file;
			if (temp->deleteFile(file))
				cout << "delete complete" << endl;
			else
				cout << "delete error" << endl;
		}
		else if (action == "mkdir")
		{
			string dir;
			cin >> dir;
			if (temp->createRoot(dir) == nullptr)
				cout << "directory construction error" << endl;
			else
				cout << "construction complete" << endl;
		}
		else if (action == "touch")
		{
			string file;
			cin >> file;
			if (temp->createFile(file) == nullptr)
				cout << "file construction error" << endl;
			else
				cout << "construction complete" << endl;
		}
		else if (action == "stat") {
			temp->showInfo();
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
		cout << "File " << name << " already exists" << endl;
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
		cout << "File " << name << " already exist" << endl;
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
		cout << "File " << name << " not found" << endl;
		return false;
	}
}

Root* Root::visitFile(string name)
{
	if (childs.find(name) != childs.end()) {
		return childs[name];
	}
	else {
		cout << "File " << name << " not found" << endl;
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

bool Root::copy(string src, Root * dest)
{
	ifstream in(src);
	string temp;

	while (!in.eof()) {
		in >> temp;
	}

	return dest->write(temp);
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

string Root::getRecord()
{
	char time[20];
	itoa(createTime, time, 10);
	string temp = name + " " + parent->name + " " + time + " "
			+ (isFile() ? block->getId() : "-1") + " ";

	map<string, Root*>::iterator it;
	it = childs.begin();
	while (it != childs.end())
	{
		temp += it->second->getRecord();
		it++;
	}

	return temp;
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

string Root::getName()
{
	return name;
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
	return !(block == nullptr);
}

Root * Root::findRoute(string route)
{
	Root * test;
	if (route[0] == '/')
		test = findExcatRoute(route);
	else
		test = findRelativeRoute(route);
	return test;
}

Root * Root::DownToFile(string &route)
{
	Root * temp;
	string file;
	int pos = route.find('/');
	if (pos == -1)
	{
		temp = visitFile(route);
		route = "";
	}
	else
	{
		file = route.substr(0, pos);
		temp = visitFile(file);
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
	{
		temp = temp->DownToFile(route);
		if (temp == nullptr)
		{
			cout << "invalid input" << endl;
			return nullptr;
		}
	}
	return temp;
}

Root * Root::findRelativeRoute(string route)
{
	Root * temp;
	while (!route.empty())
	{
		if (route.substr(0, 2) == "..")
		{
			temp = parent;
			route = route.substr(2, route.length() - 2);
		}
		else
			temp = DownToFile(route);

		if (route.substr(0, 1) == "/")
			route = route.substr(1, route.length() - 1);

		if (temp == nullptr)
		{
			cout << "invalid input" << endl;
			return nullptr;
		}
		
	}
	return temp;
}


