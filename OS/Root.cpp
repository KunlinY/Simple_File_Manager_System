#include "stdafx.h"
#include "Root.h"


Root::Root()
{
}


Root::~Root()
{
}


Root::Root(string name) : name(name)
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
		childs[name] = new Root(name);
	}
	else {
		cout << "File " << name << " already exists" << endl;
	}
	return nullptr;
}

Root * Root::createFile(string name)
{
	if (childs.find(name) != childs.end()) {
		return childs[name];
	}
	else {
		cout << "File " << name << " doesn't' exist" << endl;
	}
	return nullptr;
}


bool Root::deleteFile(string name)
{
	return false;
}


Root* Root::visitFile(string name)
{
	return nullptr;
}

Root * Root::visitParent()
{
	return nullptr;
}

bool Root::copy(Root * src, Root * dest)
{
	return false;
}


void Root::showChilds()
{
}


void Root::showInfo()
{
}
