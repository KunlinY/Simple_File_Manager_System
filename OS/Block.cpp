#include "stdafx.h"
#include "Block.h"

bool Block::overflow = false;
bool Block::blocks[1024];
fstream Block::disk("disk");

Block::Block() :
	next(nullptr)
{
	time(&createTime);
	time(&updateTime);

	int i;
	for (i = 0; i < 1024; i++) {
		if (!blocks[i]) {
			id = i;
			blocks[i] = true;
			break;
		}
	}

	if (i == 1024) {
		overflow = true;
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
		disk.seekg(1024 * pos->id, ios::beg);

		streampos item = disk.tellg();
		cout << item << ends;

		disk.read(temp, 1024);

		item = disk.tellg();
		cout << item << ends;

		temp[1024] = 0;
		content += temp;
		pos = pos->next;
	}

	return content;
}

bool Block::write(string content)
{
	Block* pos = this;
	content += (char)0;

	while (content.size() > 0) {
		time(&pos->updateTime);
		disk.seekp(1024 * pos->id, ios::beg);

		streampos item = disk.tellp();
		cout << item << ends;

		if (content.size() <= 1024) {
			disk.write(content.c_str(), content.size());
			break;
		}
		else {
			disk.write(content.c_str(), 1024);
			content = content.substr(1024);
		}

		item = disk.tellp();
		cout << item << ends;

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
