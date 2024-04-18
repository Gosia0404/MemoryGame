#include <iostream>
#include <windows.h> // funkcja sleep
#include <cstdlib> //rand()
#include <iomanip> //setw()
#include <locale.h> //polskie znaki

using namespace std;


struct card {
	int number;
	char letter;
	bool hidden;
};

const int row = 4;
const int column = 4;
const int cardCounter = column * row;
const int pairCounter = cardCounter / 2;
card board[row][column] = {};

void debug()
{
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << "[" << board[i][j].letter << "]" << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void showBoard()
{
	system("cls");
	setlocale(LC_CTYPE, "Polish");
	cout << "MEMORY GAME" << endl;
	cout << endl;
	cout << "INSTRUKCJA GRY:" << endl;
	cout << "Zostanie wylosowana plansza 4x4." << endl;
	cout<< "Na pocz¹tku widoczne bêd¹ cyfry od 0 do 15, a pod niby kryj¹ sie pary liter od A do H." << endl;
	cout << "Twoim zadaniem jest dopasowanie wszystkich 8 par" << endl; 
	cout<< "Poprzez podawanie dwóch cyfr oraz zapamiêtywanie jaka litera znajduje siê w tym miejscu" << endl;
	cout << "Podczas gry zliczane bêd¹ twoje ruchy. :)" << endl;
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << setw(3);
			if (board[i][j].hidden)
			{
				cout << board[i][j].number;
			}
			else 
			{
				cout << board[i][j].letter;
			}
			
		}
		cout << endl;
	}
	cout << endl;
	//debug(); //todo usunac podczas gry ;)
}

void fillBoard(char givenLetter)
{
	do {
		int possibleCardNumber = rand() % cardCounter;
		int x = possibleCardNumber / column;
		int y = possibleCardNumber % column;
		if (board[x][y].letter == NULL)
		{
			board[x][y] = card{ possibleCardNumber, givenLetter,true };
			break;
		}
	} while (true);
}

void play(int firstNumber, int secondNumber, int * successCounter, int *guessCounter)
{
	card* a = &board[firstNumber / column][firstNumber % column];
	card* b = &board[secondNumber / column][secondNumber % column];
	(*a).hidden = false;
	(*b).hidden = false;

	showBoard();
	if ((*a).letter == (*b).letter)
	{
		cout << "SUKCES!!!!!!!!!"<<endl;
		(*successCounter)++;
	}
	else
	{
		cout << "Karty s¹ ró¿ne"<<endl;
		(*a).hidden = true;
		(*b).hidden = true;

	}
	(*guessCounter)++;
	cout << "Próba nr." << *guessCounter << endl;
}


int main()
{
	/* initialize random seed: */
	srand(time(NULL));
	

	// generowanie kart
	for (int i = 0; i < pairCounter; i++)
	{
		char givenLetter = i + 65;
		fillBoard(givenLetter);
		fillBoard(givenLetter);
	}


	int successCounter = 0;
	int guessCounter = 0;
	int firstNumber;
	int secondNumber;
	bool playing = true;
	while (playing)
	{
		showBoard();

		cout << "Wybierz pierwsz¹ liczbê: ";
		cin >> firstNumber;

		cout << "Wybierz drug¹ liczbê: ";
		cin >> secondNumber;

		
		if (firstNumber == secondNumber)
		{
			cout << "B³¹d" << endl;
			cout << "Wpisa³eœ 2 razy t¹ sam¹ liczbê";

		}
		else if (firstNumber >= cardCounter || secondNumber >= cardCounter)
		{
			cout << "B³¹d" << endl;
			cout << "Liczba poza skal¹";
		}
		else if (board[firstNumber / column][firstNumber % column].hidden == false || board[secondNumber / column][secondNumber % column].hidden == false)
		{
			cout << "B³¹d"<<endl;
			cout << "Próbujesz odkryæ odkryta ju¿ karte, podaj nowe wartoœci";
		}
		else
		{
			play(firstNumber, secondNumber, &successCounter, &guessCounter);
		}

		

		if (successCounter == pairCounter)
		{
			cout << "WYGRANA" << endl;
			cout << "Uda³o siê wygraæ po " << guessCounter << " próbach" << endl;
			playing = false;
		}

		Sleep(3000);
	}
	system("pause");
}
