#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>

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
void example02() {
	int num[2][3]{ 10,20,30 };
	int (&rnum)[2][3] = num; 
	int (&rnum2)[3] = num[0]; //배열에 대한 레퍼런스 선언방법


	cout << "num : " << typeid(num).name() << endl; //num : int [2][3]
	cout << "num[0] : " << typeid(num[0]).name() << endl; //num[0] : int [3]
	cout << "num[0][0] : " << typeid(num[0][0]).name() << endl; //yhnum[0][0] : int
}

void example03() {
	constexpr int SIZE = 5;
	constexpr char TAB = '\t';
	int arr1[SIZE] = { 10,20,30,40,50 };
	cout << arr1 << TAB << arr1[1] << endl;
	cout << "SIZE : " << size(arr1) << endl;
	cout << arr1[0] << TAB << arr1[1] << endl;
	cout << *(arr1) << TAB << *(arr1 + 1) << endl;
}


int main() {
	cout << "202211284 김준수"<<endl;
	example03();

	return 0;
}
