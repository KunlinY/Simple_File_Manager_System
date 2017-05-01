#include "stdafx.h"
#include "Block.h"


Block::Block() : 
	next(nullptr)
{
	time(&createTime);
	time(&updateTime);

	for (int i = 0; i < 1024; i++) {
		if (!blocks[i]) {
			id = i;
			break;
		}
	}

	if (!disk.is_open()) {
		disk.open("disk");
	}
}


Block::~Block()
{
}


void Block::showInfo()
{
}

string Block::content()
{
	return string();
}

bool Block::write(string content)
{
	return false;
}

int Block::size()
{
	if (next != nullptr) {
		return next->size() + 1;
	}
	return 1;
}
