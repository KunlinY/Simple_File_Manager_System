#pragma once

#include "Header.h"
#include "Super.h"

static fstream disk;
static bool blocks[1024];

class Block
{
public:
	Block();
	~Block();

	void showInfo();
	string content();
	bool write(string content);
	int size();
	void deleteBlock(Block* block);

private:
	int id;
	Block* next;
	bool used;
	long long createTime;
	long long updateTime;
	static bool overflow;
};
bool Block::overflow = false;
