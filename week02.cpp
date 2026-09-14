#include <iostream>

using namespace std;


void example01() {
	//int arr[3][4]; //c++에서는 자동으로 초기화 되지 않아서 이상태로 출력하면 쓰레기 값이 나옴.
	int arr[3][4]{ {1,2,3,4},{1,2,3,4},{1,2,3,4} };
	cout << arr << "\t" << typeid(arr).name() << endl;
	cout << arr << "\t" << typeid(arr[0]).name() << endl;
	cout << arr << "\t" << typeid(arr[0][0]).name() << endl; //주소값은 같으나 의미하는 타입은 다를 거임. 찍어보셈. 
	
}


void example02() {
	constexpr int ROW = 2;
	constexpr int COL = 2;
	bool seats[ROW][COL]{};
	bool isEnd = false;
	while (true) {
		system("cls");
		for (int i = 0; i < COL; i++) {
			cout << '\t' << i + 1;
		}
		cout << endl;
		for (int i = 0; i < ROW; i++) {
			cout << static_cast<char>('A' + i) << '\t';
			for (int j = 0; j < COL; j++) {
				cout << (seats[i][j] ? "●" : "○") << '\t';
			}
			cout << endl;
		}
		char x, y;
		while (true) {
			cout << "좌석입력 (ex, A1) : ";
			cin >> x >> y;
			if (x<'A' || x>static_cast <char>('A' + ROW - 1) || y<'1' || y>static_cast <char>('1'+COL - 1)) {
				cout << "잘못 입력하셨습니다. 다시입력해주세요." << endl;
			}
			else {
				break;
			}
		}
		
		int count = 0;
		if (seats[x - 'A'][y - '1']) {
			cout << "이미 예약된 자리입니다." << endl;
		}
		else {
			seats[x - 'A'][y - '1'] = true;
			cout << "예약이 완료되었습니다." << endl;
			count++;
		}
		if (count == ROW * COL) {
			cout << "종료되었습니다." << endl;
			break;
		}
		
		system("pause");
	}
	
}








int main() {
	/*constexpr int SIZE = 5;
	constexpr char tab = '\t';
	int num[SIZE]{ 10,20,30,40 };
	int grade[SIZE]{};
	for (auto i : num) {
		cout << i << tab;
	}
	cout << endl; */
	//grade=num; 이건 오류임. 배열의 이름은 상수인 배열의 포인터 주소이다. 따라서 상수니까 변동 불가능!!!!

	//for (auto i : grade) {
	//	cout << i << tab; 
	//}

	//example01();

	example02();

	return 0;
}