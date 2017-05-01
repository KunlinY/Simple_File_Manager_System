#pragma once

#include "Header.h"

class Root
{
public:
	Root();
	~Root();
	Root(string name);

	void run();

	Root* createRoot(string name);
	Root* createFile(string name);
	bool deleteFile(string name);

	Root* visitFile(string name);
	Root* visitParent();
	bool copy(Root* src, Root* dest);

	void showChilds();
	void showInfo();

private:
	string name;
	map<string, Root*> childs;
	Root* parent;
	Root* root;
};

