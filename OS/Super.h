#pragma once

#include "Header.h"
#include "Root.h"

using namespace std;

class Super
{
public:
	Super();
	~Super();

public:
	const int FILE_SIZE = 1024 * 1024;
	const int BLOCK_SIZE = 1024;
	const int NAME_SIZE = 8;
	const int NODE_SIZE = 64;
private:
	map<string, Root*> users;
public:
	void boot();
	bool createUser(string name);
	bool deleteUser(string name);
	bool logUser(string name);
	void showInfo();
};

