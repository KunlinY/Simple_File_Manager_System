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
