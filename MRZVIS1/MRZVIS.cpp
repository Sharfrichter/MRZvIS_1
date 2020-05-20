#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;



int isEqual(bool* a, bool* b) //проверка на ревенство
{
	int ch = 0;
	for (size_t i = 1; i < 5; i++)
		if (a[i] == b[i])
			ch++;


	if (ch == 4)
		return 1;
	return 0;
}




void plusOne(bool* a) //прибавление единицы 
{


	if (a[sizeof a] == 0)
		a[sizeof a]++;
	else {
		a[sizeof a] = 0;
		int i = sizeof a - 1;
		while (a[i] != 0) {
			a[i] = 0;
			i--;
		}
		a[i] = 1;
	}

}
void additionalCode(bool* a)//дополнительный код 
{
	for (size_t i = 1; i < 5; i++)
	{
		a[i] = !a[i];

	}
	plusOne(a);

}
bool* addition(bool* a, bool* b) //сложение
{
	bool* answer = new bool[5];
	for (size_t i = 0; i < 5; i++)
	{
		answer[i] = a[i];
	}
	bool counter[5];
	for (size_t i = 0; i < 5; i++)
	{
		counter[i] = 0;
	}
	while (!isEqual(counter, b)) {
		plusOne(counter);
		plusOne(answer);
	}


	return answer;


}


void show(bool* a, int size)//вывод двоичного числа с указанием размера 
{
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i];
	}
	cout << " ";
}
void shift(bool* P, bool* A) {
	for (size_t i = 0; i < 4; i++)
	{
		P[i] = P[i + 1];
	}
	P[4] = A[0];
	for (size_t i = 0; i < 3; i++)
	{
		A[i] = A[i + 1];
	}

}
bool* toBin(int a, int size) //перевод в двоичный код с указанием размера массива
{
	bool* answer = new bool[size];
	for (size_t i = 0; i < size; i++)
		answer[i] = 0;

	if (size == 4)
		for (int i = 3; i >= 0; i--) {
			if (a - pow(2, i) >= 0) {
				answer[abs(3 - i)] = 1;
				a -= pow(2, i);
			}

		}
	else
		for (int i = 3; i >= 0; i--) {
			if (a - pow(2, i) >= 0) {
				answer[abs(3 - i) + 1] = 1;
				a -= pow(2, i);
			}

		}
	return answer;
}


vector<bool*> conveer(vector<pair<bool*, bool*>> vect) {
	int stage1 = 1;//стадия первой пары если stage > 0 то пара обрабатывается на текущем такте
	int stage2 = 0;//стадия второй
	int stage3 = -1;//стадия 3
	bool* A1 = vect[0].first;//первая пара
	bool* B1 = vect[0].second;

	bool initialP1[] = { 0,0,0,0,0 };//инициализация остатка 
	bool initialP2[] = { 0,0,0,0,0 };
	bool initialP3[] = { 0,0,0,0,0 };
	bool* P1 = initialP1;
	bool* P2 = initialP2;
	bool* P3 = initialP3;

	bool* A2 = vect[1].first;//вторая пара
	bool* B2 = vect[1].second;

	bool* A3 = vect[2].first;//третья пара
	bool* B3 = vect[2].second;

	bool* tmp1 = initialP1;//указатели на разность между P и B они равны initialP1 поскольку их нужно инициализировать иначе компилятор выдаст ошибку 
	bool* tmp2 = tmp1;
	bool* tmp3 = tmp1;

	additionalCode(B1);//перевод делителей в доп код для вычисления разности
	additionalCode(B2);
	additionalCode(B3);

	for (int i = 1; i <= 14; i++) {
		if (stage3 > 0) {
			for (int j = 1; j < stage3; j++)
				cout << "                   ";//сдвиг для красивой таблички

		}
		cout << "|";
		if (stage3 % 3 == 1) { //если стадия 1,4,7,11... то произволится сдвиг
			shift(P3, A3);
			show(P3, 5);
			show(A3, 3);
			cout << "  shift |";
		}
		if (stage3 % 3 == 2) {//если стадия 2,4,6,.... производится вычитание
			tmp3 = addition(P3, B3);
			show(tmp3, 5);
			cout << "    minus   |";

		}
		if (stage3 % 3 == 0 && stage3 != 0) {// если стадия 3,6,9... производится восстановление либо нет остатка
			if (tmp3[0] != 0) {
				P3 = tmp3;// no restoration
				A3[3] = 1;
				show(P3, 5);
				show(A3, 4);
				cout << "no rest|";
			}

			else {
				A3[3] = 0;
				show(P3, 5);
				show(A3, 4);
				cout << "restore|";
			}
		}//-------------------------аналогично для стадии 2, и 1
		if (i <= 13) {
			if (stage2 % 3 == 1) {
				shift(P2, A2);
				show(P2, 5);
				show(A2, 3);
				cout << "  shift |";
			}
			if (stage2 % 3 == 2) {
				tmp2 = addition(P2, B2);
				show(tmp2, 5);
				cout << "    minus   |";

			}
			if (stage2 % 3 == 0 && stage2 != 0) {
				if (tmp2[0] != 0) {
					P2 = tmp2;// no restoration
					A2[3] = 1;
					show(P2, 5);
					show(A2, 4);
					cout << "no rest|";
				}

				else {
					A2[3] = 0;
					show(P2, 5);
					show(A2, 4);
					cout << "restore|";
				}
			}
		}
		if (i <= 12) {
			if (stage1 % 3 == 1) {
				shift(P1, A1);
				show(P1, 5);
				show(A1, 3);
				cout << "  shift |";
				for (int j = i; j < 12; j++)
					cout << "                  |";
			}
			if (stage1 % 3 == 2) {
				tmp1 = addition(P1, B1);
				show(tmp1, 5);
				cout << "    minus   |";
				for (int j = i; j < 12; j++)
					cout << "                  |";
			}
			if (stage1 % 3 == 0) {
				if (tmp1[0] != 0) {
					P1 = tmp1;// no restoration
					A1[3] = 1;
					show(P1, 5);
					show(A1, 4);
					cout << "no rest|";
				}
				else {
					A1[3] = 0;
					show(P1, 5);
					show(A1, 4);
					cout << "restore|";
				}
				for (int j = i; j < 12; j++)
					cout << "                  |";
			}
		}
		stage1++;//следующий шаг
		stage2++;
		stage3++;

		cout << "\n";



	}

	vector<bool*> answer;
	answer.push_back(A1);
	answer.push_back(A2);
	answer.push_back(A3);
	return answer;
}

int main()
{
	vector<pair<bool*, bool*>> vect;
	pair<bool*, bool*> p;
	int a, b;
	for (int i = 0; i < 3; i++) {
		cin >> a >> b;
		show(toBin(a, 4), 4);
		show(toBin(b, 5), 5);
		cout << "\n";
		p.first = toBin(a, 4);
		p.second = toBin(b, 5);
		vect.push_back(p);
	}


	vector<bool*>answer = conveer(vect);
	cout << "\n";
	show(answer[0], 4);
	cout << "\n";
	show(answer[1], 4);
	cout << "\n";
	show(answer[2], 4);
	//15 5
	//9 2
	//13 4

	//show(B, 5);
	//bool* a = toBin(5, 5);
	//show(a, 5);
	//division(P, A, B);


}