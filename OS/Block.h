#pragma once

#include "Header.h"

class Block
{
public:
	Block();
	~Block();
private:
//	map<string, Root*> users;
	int id;
	bool used;
	int createTime;
	int updateTime;
public:
	void showInfo();
};

