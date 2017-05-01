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

private:
	int id;
	bool used;
	int createTime;
	int updateTime;
};

