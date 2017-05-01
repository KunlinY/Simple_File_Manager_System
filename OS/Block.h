#pragma once

#include "Header.h"
#include "Super.h"

static fstream disk;
static int blocks[1024];

class Block
{
public:
	Block();
	~Block();

	void showInfo();
	string content();
	bool write(string content);
	int size();

private:
	int id;
	Block* next;
	bool used;
	long long createTime;
	long long updateTime;
};
