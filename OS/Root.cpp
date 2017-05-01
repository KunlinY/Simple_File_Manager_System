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
