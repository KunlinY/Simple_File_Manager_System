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
			write("");
			break;
		}
	}

	if (i == 1024) {
		overflow = true;
	}
}

Block::Block(int i, long long time) :
	next(nullptr)
{
	id = i;
	createTime = time;
	updateTime = time;
}

Block::~Block()
{
	blocks[id] = false;
}

void Block::save(string users, string records)
{
	disk.seekp(0, ios::beg);
	disk.write(users.c_str(), users.size());

	string temp;
	for (int i = 0; i < 1024; i++) {
		if (blocks[i])
			temp += '1';
		else temp += '0';
	}
	disk.seekp(1024, ios::beg);
	disk.write(temp.c_str(), 1024);

	disk.seekp(2048, ios::beg);
	disk.write(records.c_str(), records.size());
}

void Block::load()
{
	string item = content();
	for (int i = 0; i < item.size(); i++) {
		if (item[i] == '1')
			blocks[i] = true;
	}
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
	while (content.size() < 1016) 
		content += (char)0;

	while (content.size() > 0) {
		time(&pos->updateTime);
		disk.seekp(1024 * pos->id, ios::beg);

		if (content.size() <= 1016) {
			disk.write(content.c_str(), content.size());
			break;
		}
		else {
			disk.write(content.c_str(), 1016);
			content = content.substr(1016);
		}
		
		if (pos->next == nullptr) {
			pos->next = new Block();

			if (overflow)
				return false;
		}

		pos = pos->next;

		disk.seekp(1024 * pos->id + 1017, ios::beg);
		char temp[6];
		itoa(pos->id, temp, 10);
		disk.write(temp, 6);
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

string Block::getId()
{
	char temp[25];
	itoa(id, temp, 10);
	return temp;
}

int Block::size()
{
	if (next != nullptr) {
		return next->size() + 1;
	}
	return 1;
}
