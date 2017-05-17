#pragma once

#include "Header.h"


class Block
{
public:
	Block();
	Block(bool);
	~Block();

	string readUser();
	string readNode();
	string readFile();
	void save(string users, string records);

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