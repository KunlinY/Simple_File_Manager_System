#pragma once

#include "Header.h"
#include "Root.h"

using namespace std;

class Super
{
public:
	Super();
	Super(bool flag);
	~Super();

	const static int FILE_SIZE = 1024 * 1024;
	const static int BLOCK_SIZE = 1024;
	const static int NAME_SIZE = 8;
	const static int NODE_SIZE = 64;

	void boot();
	bool createUser(string name);
	bool deleteUser(string name);
	bool logUser(string name);
	void showInfo();

private:
	map<string, Root*> users;
};

