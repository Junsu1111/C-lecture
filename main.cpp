#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


void example01() {
	ifstream file("testdata.txt");
	if (!file.is_open()) {
		cerr << "파일 읽기 실패\n";
		return;
	}
	string data;
	while (!file.eof()) {
		string str;
		getline(file, str);
		data += str + " \n";
	}
	cout << data << endl;
	cout << "--------------------------------" << endl;
	string findStr;
	string replaceStr;
	cout << "찾을 문자열을 입력하세요 : ";
	getline(cin, findStr);
	cout << "바꿀 문자열을 입력하세요 : ";
	getline(cin, replaceStr);
	int pos = data.find(findStr);
	while (pos != string::npos) {
		data.replace(pos, findStr.length(), replaceStr);
		pos = data.find(findStr, pos + replaceStr.length());
	}

	
	cout << data << endl;
}



int main() {

	example01();

	return 0;
}