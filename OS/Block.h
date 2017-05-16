#pragma once

#include "Header.h"


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
	static bool blocks[1024];
	static fstream disk;
};