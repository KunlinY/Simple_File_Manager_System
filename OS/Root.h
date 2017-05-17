#pragma once

#include "Header.h"
#include "Block.h"

class Root
{
public:
	Root(string name);
	Root(Root* parent, string name);
	Root(Root* parent, string name, bool flag);
	~Root();

	void run();

	Root* createRoot(string name);
	Root* createFile(string name);
	bool deleteFile(string name);

	Root* visitFile(string name);
	Root* visitRoot();
	Root* visitParent();
	bool copy(Root* src, Root* dest);

	void showChilds();
	void showInfo();
	string getRecord();

	int getFolderNum();
	int getFileNum();
	int getSize();

	string read();
	bool write(string content);
	bool isFile();

	Root * findRoute(string route);
	Root * DownToFile(string &route);
	Root * findExcatRoute(string route);
	Root * findRelativeRoute(string route);

private:
	string name;
	map<string, Root*> childs;
	Block* block;
	Root* parent;
	Root* root;
	long long createTime;
};

