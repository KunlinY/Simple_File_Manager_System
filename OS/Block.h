#pragma once

#include "Header.h"


class Block
{
public:
	Block();
	Block(int i, long long time);
	~Block();

	static void save(string users, string records);
	void load();

	void showInfo();
	string content();
	bool write(string content);
	int size();
	void deleteBlock(Block* block);
	string getId();

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