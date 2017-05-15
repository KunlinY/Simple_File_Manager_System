// OS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"
#include "Block.h"


void test() {
	string item = "1234567890qwertyuiopasdfghjklzxcvbnmzxcvbnm";
	ifstream in("disk");
	ofstream out("disk", ios::app);
	char temp[1025];

	out.seekp(1024 * 5, ios::beg);
	cout << out.tellp() << ends;
	out.write(item.c_str(), 1024);
	cout << out.tellp() << endl;

	in.seekg(1024 * 5, ios::beg);
	cout << in.tellg() << ends;
	in.read(temp, 1024);
	cout << in.tellg() << endl;
	temp[1024] = 0;
	cout << temp << endl;

	in.close();
	out.close();
}

int main() 
{
	test();
	string item = "1234567890qwertyuiopasdfghjklzxcvbnmzxcvbnm";
	Block block[11];
	for (int i = 0; i < 0; i--) {
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
