#pragma once

#include "Header.h"
#include "Root.h"

class File :
	public Root
{
public:
	File();
	~File();
private:
	string name;
	int block;
public:
	void read();
	void write(string content);
};

