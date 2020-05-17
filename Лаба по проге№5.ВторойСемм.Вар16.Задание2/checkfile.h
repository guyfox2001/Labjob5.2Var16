#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

bool check_file(string _FILENAME) {
	ifstream read_file(_FILENAME, ios::in || ios::binary);
	if (read_file) {
		return true;
	}
	else {
		cerr << "Файл не был найден \n";
		return false;
	}
}
string check_mask(string _FILENAME) {
	if (_FILENAME.find(".pbs") != -1) {
		return _FILENAME;
	}
	else
	{
		return _FILENAME += ".pbs";
	}
}
bool check_empty(string _FILENAME) {
	int cnt = 0;
	string buff;
	ifstream check;
	check.open(_FILENAME, ios::in || ios::binary);
	while (!check.eof()) {
		check >> buff;
		if (!buff.empty())
			return false;
		else
			return true;
	}
}
