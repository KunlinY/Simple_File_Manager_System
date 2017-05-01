#include "stdafx.h"
#include "Block.h"


Block::Block()
{
	id = 0;
	createTime = 0;
	updateTime = 0;
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
	return 0;
}
