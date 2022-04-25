#include <iostream>
#include <string>
#include <vector>
#define WIDTH 10
#define HEIGHT 10

using namespace std;

//1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров
template<class T>
T div(T a, T b) {
	if (b != 0)
	{
		return (a / b);
	}
	else {//и запускать исключение DivisionByZero, если второй параметр равен 0.
		throw " don 't divide by zero ";
		return 0;
	}
}

void FirstTask() {
	int firstIntNum{ 10 }, secondIntNum{ 2 };
	float firstFloatNum{ 3.14 }, secondFloatNum{ 0 };

	try {//В функции main выводить результат вызова функции div в консоль

		cout << "Сперва мы делим int 10 на int 2 и получаем : " << div<int>(firstIntNum, secondIntNum) << endl;
		cout << div<float>(firstFloatNum, secondFloatNum) << endl;
	}
	catch (const char* exception) {//а также ловить исключения.
		cerr << "Error :мы попытались, при помощи шаблонной ф-ии разделить float на 0 :" << exception << endl;
	}

}



//2. Написать класс Ex, имеющий конструктор по вещественному числу,инициализирующий x значением параметра,хранящий вещественное число x
class Ex :public exception
{
public:
	Ex(float _x) :x(_x) {}
	float Get() { return x; }
	float x;

};

class Bar {//Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным параметром a
public:
	Bar(float _y = 0) :y(_y) {};
	void set(float a) {
		if (y + a > 100)
		{
			float temp = a * y;
			cout << "a*y=" << temp << endl;
			throw Ex(temp);
		}
		else {
			y += a;
			cout << "y= " << y << endl;
		}
	}
private:
	float y;
};


void SecondTask() {
	float varForSetFunc;
	Bar obj;
	do
	{
		cout << "введите множитель, мы его прибавим к 'y' :";
		cin >> varForSetFunc;
		try {
			obj.set(varForSetFunc);
		}
		catch (Ex& ex) {
			cout << "Поймали исключение при y+a>100 :" << ex.Get() << endl;
		}
	} while (varForSetFunc != 0);


}

//3

class OffTheField :public exception {
public:
	OffTheField(int _newWIDTH, int _newHEIGHT, int _oldWIDTH, int  _oldHEIGHT) :newWIDTH(_newWIDTH), newHEIGHT(_newHEIGHT), oldWIDTH(_oldWIDTH), oldHEIGHT(_oldHEIGHT) {};

	int GetNewW() { return newWIDTH; }
	int GetNewH() { return newHEIGHT; }

	int GetOldW() { return oldWIDTH; }
	int GetOldH() { return oldHEIGHT; }

	int newWIDTH, newHEIGHT, oldWIDTH, oldHEIGHT;

};
class IllegalCommand :public exception {
public:
	IllegalCommand(char inputedSymbol) :wrongSymbol(inputedSymbol) {};
	char GetWrongSymbol() { return wrongSymbol; }
	char wrongSymbol;
};



class Robot
{
public:

	int arr[WIDTH][HEIGHT];
	int** a = new int* [WIDTH];
	int x{ 4 }, y{ 4 };

	void Borned();
	void SetLocation();
	void Map();
	void Move(char move);
};

void Robot::Borned() {

	for (size_t i = 0; i < 10; i++)
	{

		a[i] = new int[HEIGHT] {0};
	}
}
void Robot::SetLocation() {
	a[x][y] = 1;
}
void Robot::Map() {
	for (size_t w = 0; w < 10; w++)
	{
		for (size_t h = 0; h < 10; h++)
		{
			(a[w][h] == 0) ? cout << "|  |" : cout << "| " << 1 << "|";
		}
		cout << "\n----------------------------------------\n";
	}
}
void Robot::Move(char move) {
	int oldX = x;
	int oldY = y;
	if (move == 'a' || move == 'A') {
		a[x][y] = 0;
		--y;
		y < 0 ? throw OffTheField(x, y, oldX, oldY) : cout << ' ';
		Robot::SetLocation();
	}
	else if (move == 'd' || move == 'D') {
		a[x][y] = 0;
		++y;
		y > 9 ? throw OffTheField(x, y, oldX, oldY) : cout << ' ';
		Robot::SetLocation();
	}
	else if (move == 'w' || move == 'W') {
		a[x][y] = 0;
		--x;
		x < 0 ? throw OffTheField(x, y, oldX, oldY) : cout << ' ';
		Robot::SetLocation();
	}
	else if (move == 's' || move == 'S') {
		a[x][y] = 0;
		++x;
		x > 9 ? throw OffTheField(x, y, oldX, oldY) : cout << ' ';
		Robot::SetLocation();
	}
	else {
		throw IllegalCommand(move);
	}
}

void ThirdTask() {
	Robot r1;
	r1.Borned();
	r1.SetLocation();
	r1.Map();

	char move = ' ';
	cout << "where to go?";
	cin >> move;
	try
	{
		do
		{
			r1.Move(move);
			system("cls");
			r1.Map();

			cin.clear();
			cin >> move;

		} while (move != '0');
	}
	catch (OffTheField& ex) {
		cerr << "Error : tries to go to the: WH :" << ex.GetNewW() << ex.GetNewH() << " from :" << ex.GetOldW() << ex.GetOldH();
	}
	catch (IllegalCommand& ex) {
		cerr << "Error : user tried to go to :" << ex.GetWrongSymbol();
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	FirstTask();
	SecondTask();
	ThirdTask();
}


//PS спасибо большое за участие. Курс по ООП был Супер Увлекательным
//Бордунос А)
