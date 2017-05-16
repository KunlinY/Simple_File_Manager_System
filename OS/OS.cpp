// OS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"
#include "Block.h"


void test() {
	string item = "1234567890qwertyuiopasdfghjklzxcvbnmzxcvbnm";
	fstream file("disk");
	char temp[1025];

	file.seekp(1024 * 5, ios::beg);
	cout << file.tellp() << ends;
	file.write(item.c_str(), 1024);
	cout << file.tellp() << endl;

	file.seekg(1024 * 5, ios::beg);
	cout << file.tellg() << ends;
	file.read(temp, 1024);
	cout << file.tellg() << endl;
	temp[1024] = 0;
	cout << temp << endl;

	file.close();
}

int main() 
{
	//test();
	string item = "1234567890qwertyuiopasdfghjklzxcvbnmzxcvbnm";
	Block block[11];
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		cout << block[i].content() << endl;
		block[i].write(item.substr(i, 3 * (i + 1)));
		cout << block[i].content() << endl;
	}
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		cout << block[i].content() << endl;
	}
    return 0;
}
