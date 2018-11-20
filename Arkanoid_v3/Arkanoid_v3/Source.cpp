#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <windows.h>
#include <string> // getline()
#include <cstdio>
#include <conio.h>
#include <ctime>
#include <fstream>

using namespace std;

const int WYGRANA = -1;

struct record {
	string name;
	int score;
};

void przesunkursor(int x, int y)
{
	COORD koordynaty;
	koordynaty.X = x;
	koordynaty.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordynaty);
}

bool przegrana(vector<queue<char> > Plansza, int w)
{
	for (int i = 0; i < Plansza.size(); i++)
	{
		if (Plansza[i].size() == w - 1)
		{
			return true;
		}


	}
	return false;
}

bool wygrana(vector<queue<char> > Plansza, int w)
{
	for (int i = 0; i < Plansza.size(); i++)
	{
		if (Plansza[i].empty() == false)
		{
			return false;
		}


	}
	return true;
}

void wstawblok(queue<char> &kolejka)
{
	int szansa = rand() % 10;
	if (szansa == 4)
	{
		kolejka.push('+');
	}
	else if (szansa == 9)
	{
		kolejka.push('0');
	}
	else kolejka.push('#');
}

void rysuj(vector<queue<char> > Plansza, int gracz, int w)
{
	system("cls");
	for (int i = 0; i < Plansza.size(); i++)
	{
		queue<char> kolejka = Plansza[i];
		while (kolejka.size() != 0)
		{
			przesunkursor(i * 5, kolejka.size() - 1);
			if (kolejka.front() == '#')
			{
				cout << "#### ";
			}
			if (kolejka.front() == '0')
			{
				cout << "#00# ";
			}
			if (kolejka.front() == '+')
			{
				cout << "#++# ";
			}
			kolejka.pop();
		}
	}
	przesunkursor(gracz * 5, w - 1);
	cout << "=[]= " << endl << "---------------------------------" << endl << endl << "sterowanie: 4 = w lewo   6 = w prawo   spacja strzal";
}



void aktualizujplansze(vector<queue<char> > &Plansza, int r, int n, int &iloscruchowpoprzesunieciu, int &rnd) // wskazuję na adresy tych zmiennych bo chcę operować na oryginałach, nie kopiach
{
	if (iloscruchowpoprzesunieciu > r + rnd)
	{
		for (int i = 0; i < Plansza.size(); i++)
		{
			wstawblok(Plansza[i]);
		}
		iloscruchowpoprzesunieciu = 0;
		if (n == 0)
			rnd = 0;
		else
			rnd = rand() % n;
	}
}

int gra(int w, int k, int b, int r, int n)
{

	vector<queue<char> > Plansza;
	for (int i = 0; i < k; i++)
	{
		Plansza.push_back(queue<char>());
		for (int j = 0; j < b; j++)
		{
			wstawblok(Plansza[i]);
		}
	}

	int gracz = k / 2; //pozycja gracza

	rysuj(Plansza, gracz, w);

	int iloscruchowpoprzesunieciu = 0;
	int iloscruchow = 0;
	int rnd;
	if (n == 0)
		rnd = 0;
	else
		rnd = rand() % n;
	bool win = false;
	do
	{
		iloscruchowpoprzesunieciu++;
		iloscruchow++;
		char ruch = _getch();
		if (ruch == '4')
		{
			if (gracz != 0)
			{
				gracz--;
			}

		}
		if (ruch == '6')
		{
			if (gracz != k - 1)
			{
				gracz++;
			}

		}
		if (ruch == ' ')
		{
			if (Plansza[gracz].empty() == false)
			{
				if (Plansza[gracz].front() == '0')
				{
					iloscruchowpoprzesunieciu = 0;
				}
				if (Plansza[gracz].front() == '+')
				{
					for (int i = 0; i < Plansza.size(); i++)
					{
						if (Plansza[i].empty() == false)
						{
							Plansza[i].pop();
						}
					}
				}
				else Plansza[gracz].pop();
			}
		}
		if (ruch == char(27))
		{
			break;
		}
		aktualizujplansze(Plansza, r, n, iloscruchowpoprzesunieciu, rnd);
		rysuj(Plansza, gracz, w);

		win = wygrana(Plansza, w);
	} while (przegrana(Plansza, w) == false && win == false);

	if (win == true)
	{
		return WYGRANA;
	}

	return iloscruchow;
}

void displayRanking()
{
	ifstream file;

	file.open("RANKING.txt", ios::in);

	if (file.good() == false){
		cout << "Plik ''RANKING'' nie istnieje" << endl;
		system("pause");
	}
	else {
		record ranking[10];
		string line;
		int lineNumber = 1;
		int iterator = 0;					// loading records data from RANKING.txt
		while (getline(file, line)) {
			
			switch (lineNumber) {
			case 1:
				ranking[iterator].name = line;
			case 2:
				ranking[iterator].score = atoi(line.c_str());
			}
			if (lineNumber == 2) {
				lineNumber = 0;
				iterator++;
			}
			lineNumber++;
		}

		for (int i = 0; i < 10; i++) {
			cout << "name: " << ranking[i].name << "\tscore: " << ranking[i].score << endl;
		}
		system("pause");
	}
	file.close();
}

void newRecord(string name, int score) {
											// setting a new record after a standard game
	fstream file;
	file.open("RANKING.txt", ios::in);

	if (file.good() == false) {
		cout << "\n\t failed to open the RANKING.txt file\n";
		system("pause");
	}
	else {
		cout << "\n\t opened the RANKING.txt file\n";
		record ranking[10];
		string line;
		int lineNumber = 1;
		int iterator = 0;					// loading records data from RANKING.txt
		while (getline(file, line)) {

			switch (lineNumber) {
			case 1:
				ranking[iterator].name = line;
			case 2:
				ranking[iterator].score = atoi(line.c_str());
			}
			if (lineNumber == 2) {
				lineNumber = 0;
				iterator++;
			}
			lineNumber++;
		}
		file.close();

		record player;
		player.name = name;
		player.score = score;
		cout << "\n\t player name: "<<player.name<<" score: "<<player.score<<endl;
		cout << "\n\t ranking[9] name: " << ranking[9].name << " score: " << ranking[9].score << endl;

		if (player.score > ranking[9].score) {
			ranking[9] = player;
		}

		cout << "\n\t after the change" << endl;
		cout << "\n\t ranking[9] name: " << ranking[9].name << " score: " << ranking[9].score << endl;

		
		record temporary;
		for (int i = 9; i > 0; i--) {
			if (ranking[i].score > ranking[i - 1].score) {
				temporary = ranking[i];
				ranking[i] = ranking[i - 1];
				ranking[i - 1] = temporary;
			}
		}

		file.open("RANKING.txt", ios::out);
		
		for (int i = 0; i < 10; i++) {
			cout << "\n\t saving ranking["<<i<<"] name: " << ranking[i].name << " score: " << ranking[i].score << endl;
			file << ranking[i].name << endl;
			file << ranking[i].score << endl;
		}
	}
	file.close();

}

int main()
{
	srand(time(NULL));
	int wybor;
	do
	{
		system("cls");
		cout << "    == ARKANOID THE GAME ==         " << endl;
		cout << "   1. Play the game  " << endl;
		cout << "   2. Credits & Authors  " << endl;
		cout << "   3. Options  " << endl;
		cout << "   4. Ranking  " << endl;
		cout << "   0. Exit  " << endl;
		cout << "   ------- ---- -------  " << endl;
		cout << "What would you like to do? :";

		cin >> wybor;
		if (wybor == 1)
		{
			system("cls");

			cout << " Witaj Graczu!" << endl << "Wybierz TRYB GRY:" << endl << endl << "    1. Standard game" << endl << "    2. Wlasna gra" << endl;
			int trybgry;
			do
			{
				cin >> trybgry;
				if (trybgry == 1)
				{
					system("cls");
					int k = 7; //kolumny
					int w = 10; //wiersze
					int b = 3; //bloki na poczatku
					int r = 3;
					int n = 4;
					cout << " Witaj Graczu!" << endl << "   Standard game is a game with:" << endl << "   " << k << " kolumn" << endl << "   " << w << " wierszy" << endl << "   " << b << " blokow na poczatku" << endl << "NACISNIJ ENTER JESLI ROZUMIESZ" << endl;
					system("pause");
					int wynik = gra(w, k, b, r+1, n);
					if (wynik == WYGRANA)
					{
						cout << endl << "-----------------------------" << endl << endl << "     WYGRANA!!!      " << endl << endl;
					}
					else {
						cout << endl << "-----------------------------" << endl << endl << "     WYNIK = " << wynik << endl << endl;
						string name;
						cout << "Zapisz swoj wynik:\n\tTwoje imie: ";
						cin >> name;
						newRecord(name, wynik);
					}
						

				}
				if (trybgry == 2)
				{
					system("cls");
					int w; //liczba wierszy
					int k; //liczba kolumn
					int b; //poczatkowa liczba bloków w ka¿dej kolumnie
					int r;
					int n;
					cout << " Witaj Graczu! " << endl << "Podaj rozmiary planszy na jakiej chcesz grac:" << endl << " Ilosc wierszy:  ";
					cin >> w;
					cout << endl << "Ilosc kolumn:  ";
					cin >> k;
					cout << endl << "Poczatkowa ilosc blokow w kazdej kolumnie:  ";
					cin >> b;
					cout << endl << "po ilu ruchach conajmniej schodzodza bloki?:  ";
					cin >> r;
					r++;
					cout << endl << "maxymalny bonus czasu :  ";
					cin >> n;
					n++;
					while (b >= w)
					{

						cout << "liczba blokow na poczatku nie moze byc wieksza od liczby wierszy" << endl << "Jeszcze raz podaj ilosc blokow na poczatku:    ";
						cin >> b;

					}

					int wynik = gra(w, k, b, r, n);
					if (wynik == WYGRANA)
					{
						cout << endl << "-----------------------------" << endl << endl << "     WYGRANA!!!      " << endl << endl;
					}
					else
						cout << endl << "-----------------------------" << endl << endl << "     WYNIK = " << wynik << endl << endl;

				}
				else if (trybgry != 1 && trybgry != 2)
				{
					cout << "Nie ma takiego numeru trybu. Wybierz 1 lub 2!" << endl;
				}

			} while (trybgry != 1 && trybgry != 2);


			system("pause");
			system("pause");
		}
		else if (wybor == 2)
		{
			cout << endl;
			cout << "        . -----=====||||=====----- .           " << endl;
			cout << "	 This game was made by Marek Mikulski " << endl;
			cout << "          -----=====||||=====-----            " << endl;
			cout << endl;
			system("pause");
		}
		else if (wybor == 3)
		{
			cout << endl << "There are no options yet..." << endl;
			cout << "I'm sorry" << endl << endl;
			system("pause");
		}
		else if (wybor == 4)
		{
			system("cls");
			displayRanking();
		}
		else if (wybor != 1 && wybor != 2 && wybor != 3 && wybor != 4 && wybor != 0)
		{
			cout << endl << " Nie ma takiego numeru w menu" << endl;
			system("pause");
		}

	} while (wybor != 0);
	cout << endl << endl << "   Do zobaczenia :)    " << endl << endl;
	Sleep(1000);
	return 0;
}
