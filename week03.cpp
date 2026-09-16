#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>

using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif


int** load_file(const string& filename, int& row, int& col, int& reserved);//함수 내에서 변하지 않게 하려고 const로
//int&로 인자를 선언하는 이유는 안에서 값을 바꾸어 주기 위해서!!!
//리턴은 시트 모양의 2차원 배열을 반환함.
void save_file(const string& filename, int**& seats,
	const int row, const int col);

void example03() {
	string filename = "seats.txt";
	int row, col, reserved = 0;
	int** seats = load_file(filename, row, col, reserved);
}

int** load_file(const string& filename, int& row, int& col, int& reserved) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "파일 경로 확인 요망" << endl;
		return nullptr;
	}
	file >> row >> col; //파일에서 첫줄을 읽어서 row랑 col에 넣어줌.
	int** seats = new int* [row];
	for (int i = 0; i < row; i++) {
		seats[i] = new int[col];
		for (int j = 0; j < col; j++) {
			file >> seats[i][j];
			if (seats[i][j] != 0)
				reserved++;
		}
	}
	return seats;
}

void save_file(const string& filename, int**& seats,
	const int row, const int col) {
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "파일 경로 확인 요망" << endl;
		return;
	}
	file << row << " " << col << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			file << seats[i][j] << " ";
		}
		file << endl;
	}
}



int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	example03();
	return 0;
}


//지금은 메모리 누수가 나는데!!!! 없도록 하기!!!!!