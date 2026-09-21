#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <filesystem>

using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif


int** load_file(const string& filename, int& row, int& col, int& reserved,int& reservation_num);//함수 내에서 변하지 않게 하려고 const로
//int&로 인자를 선언하는 이유는 안에서 값을 바꾸어 주기 위해서!!!
//리턴은 시트 모양의 2차원 배열을 반환함.
void save_file(const string& filename, int**& seats,
	const int row, const int col,int reservation_num);
void show_seats(int** seats, const int row, const int col);
void reserve_seat(int**& seats, const int row, const int col,int& reserved,int& reservation_num);
void cancel_seat(int**& seats, const int row, const int col, int& reserved);
void free_seats(int**& seats, const int row);
bool verify_menu_input(const string input);

void example03() {
	string filename = "seats.txt";
	int row, col, reserved = 0;
	int reservation_num = 0;
	int** seats = load_file(filename, row, col, reserved,reservation_num);
	int selection=0;
	string menu_input;
	while (true) {
		system("cls");
		cout << "1. 좌석 현황 " << "2. 좌석 예약 " << "3. 좌석 취소 " << "4. 종료" << endl;
		cout << "메뉴 선택: ";
		cin >> menu_input;
		if (verify_menu_input(menu_input)) {
			selection =stoi(menu_input);
			if (selection == 1) {
				show_seats(seats, row, col);
			}
			else if (selection == 2) {
				reserve_seat(seats, row, col,reserved,reservation_num);
			}
			else if (selection == 3) {
				cancel_seat(seats, row, col, reserved);
			}
			else if (selection == 4) {
				save_file(filename, seats, row, col,reservation_num);
				cout << "종료합니다." << endl;
				break;
			}
		}
		else {
			cout << "1~4번 중에 메뉴를 선택해주십시오." << endl;
		}
		selection = 0;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("pause");

	}
	free_seats(seats, row);

}

int** load_file(const string& filename, int& row, int& col, int& reserved,int& reservation_num) {
	ifstream file(filename);
	//
	if (file.peek() == 0xEF) {
		char bom[3];
		file.read(bom, 3);
	}
	//
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
	file >> reservation_num;

	return seats;
}

void save_file(const string& filename, int**& seats,
	const int row, const int col, int reservation_num) {
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
	file << reservation_num;
}


void show_seats(int** seats, const int row, const int col) {
	for (int i = 0; i < col; i++) {
		cout << '\t' << i + 1;
	}
	cout << endl;
	for (int i = 0; i < row; i++) {
		cout << static_cast<char>('A' + i) << '\t';
		for (int j = 0; j < col; j++) {
			cout << (seats[i][j] ? "●" : "○") << '\t';
		}
		cout << endl;
	}
}

void reserve_seat(int**& seats, const int row, const int col,int& reserved,int& reservation_num) {
	char x, y;
	while (true) {
		cout << "좌석입력 (ex, A1) : ";
		cin >> x >> y;
		if (x<'A' || x>static_cast <char>('A' + row - 1) || y<'1' || y>static_cast <char>('1' + col - 1)) {
			cout << "잘못 입력하셨습니다. 다시입력해주세요." << endl;
		}
		else {
			break;
		}
	}

	if (seats[x - 'A'][y - '1']) {
		cout << "이미 예약된 자리입니다." << endl;
	}
	else {
		seats[x - 'A'][y - '1'] = 1000+(++reservation_num);
		cout << "예약이 완료되었습니다." << endl;
		cout << "예약번호는 " << 1000+reservation_num << "입니다." << endl;
	}
}

void cancel_seat(int**& seats, const int row, const int col,int& reserved) {
	char x, y;
	int input = 0;
	while (true) {
		cout << "취소할 좌석입력 (ex, A1) : ";
		cin >> x >> y;
		if (x<'A' || x>static_cast <char>('A' + row - 1) || y<'1' || y>static_cast <char>('1' + col - 1)) {
			cout << "잘못 입력하셨습니다. 다시입력해주세요." << endl;
		}
		else {
			if (seats[x - 'A'][y - '1']) {
				cout << "예약번호 입력: ";
				cin >> input;
				if (input == seats[x - 'A'][y - '1']) {
					seats[x - 'A'][y - '1'] = 0;
					reserved--;
					cout << "취소가 완료되었습니다.." << endl;
					break;
				}
				else {
					cout << "예약번호가 일치하지 않습니다."<<endl;
				}
			}
			else {
				cout << "예약 되지 않은 좌석입니다." << endl;
			}
		}
	}

	
}

void free_seats(int**& seats, const int row)
{
	if (seats == nullptr)
	{
		return;
	}

	for (int i = 0; i < row; i++)
	{
		delete[] seats[i];
		seats[i] = nullptr;
	}

	delete[] seats;
	seats = nullptr;
}

bool verify_menu_input(string menu_input) {
	if (menu_input.length() != 1) {
		return false;
	}
	for (int i = 0; i < menu_input.length(); i++){
		if (menu_input[i] < '1' || menu_input[i] > '4')
		{
			return false;
		}
	}
	return true;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	example03();
	return 0;
}


//지금은 메모리 누수가 나는데!!!! 없도록 하기!!!!!
