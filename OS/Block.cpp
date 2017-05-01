#include "stdafx.h"
#include "Block.h"


Block::Block() : 
	next(nullptr)
{
	time(&createTime);
	time(&updateTime);

	int i;
	for (i = 0; i < 1024; i++) {
		if (!blocks[i]) {
			id = i;
			break;
		}
	}

	if (i == 1024) {
		overflow = true;
	}

	if (!disk.is_open()) {
		disk.open("disk");
	}
}


Block::~Block()
{
	blocks[id] = false;
}


void Block::showInfo()
{
	cout << "This block is created at " << createTime
		<< " and the latest edit time is " << updateTime
		<< ". " << endl;
}

string Block::content()
{
	Block* pos = this;
	string content;
	char temp[1025];

	while (pos != nullptr) {
		disk.seekg(1024 * pos->id);
		disk.read(temp, 1024);
		temp[1024] = 0;
		content += temp;
		pos = pos->next;
	}

	return content;
}

bool Block::write(string content)
{
	Block* pos = this;

	while (content.size() > 0) {
		time(&pos->updateTime);
		disk.seekp(1024 * pos->id);
		disk.write(content.c_str(), 1024);
		content = content.substr(1025);

		if (pos->next == nullptr) {
			pos->next = new Block();

			if (overflow)
				return false;
		}
		pos = pos->next;
	}
	
	deleteBlock(pos->next);

	return true;
}

void Block::deleteBlock(Block* block) {
	if (block == nullptr)
		return;

	deleteBlock(block->next);
	delete block;
}

int Block::size()
{
	if (next != nullptr) {
		return next->size() + 1;
	}
	return 1;
}
