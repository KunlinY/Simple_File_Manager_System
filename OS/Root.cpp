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
