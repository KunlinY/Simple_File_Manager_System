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

	int getFolderNum();
	int getFileNum();
	int getSize();

	string read();
	bool write(string content);

	void findExcatRoute(string route);
	void findRelativeRoute(string route);
private:
	string name;
	map<string, Root*> childs;
	Block* block;
	Root* parent;
	Root* root;
};

