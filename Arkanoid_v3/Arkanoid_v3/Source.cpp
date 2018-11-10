#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <windows.h> // COORD, SetConsoleCursorPosition(), Sleep() 
#include <cstdio>
#include <conio.h>
#include <ctime>

using namespace std;

const int WYGRANA = -1;

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



void aktualizujplansze(vector<queue<char> > &Plansza, int r, int n, int &iloscruchowpoprzesunieciu, int &rnd)
{
	if (iloscruchowpoprzesunieciu >= r + rnd)
	{
		for (int i = 0; i < Plansza.size(); i++)
		{
			wstawblok(Plansza[i]);
		}
		iloscruchowpoprzesunieciu = 0;
		rnd = rand() % n;
	}
}

int gra(int w, int k, int b, int r, int n)	// w = liczba wierszy w planszy;	k = liczba kolumn w planszy;	b = liczba wieszy blokow na poczatku gry 
{											// r i n = bloki zejdą o krok niżej po liczbie ruchów określonej przez wzór r + n 
											// (n to bonus czasowy od 0 do wartości podanej jako 'n' przed grą)
	vector<queue<char> > Plansza;	// tworze vector (= tablice) kolejek charow
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
	int rnd = rand() % n;
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
		cout << "   0. Exit  " << endl;
		cout << "   ------- ---- -------  " << endl;
		cout << "What would you like to do? :";

		cin >> wybor;
		if (wybor == 1)
		{
			system("cls");

			int w; //liczba wierszy
			int k; //liczba kolumn
			int b; //poczatkowa liczba bloków w ka¿dej kolumnie
			int r;	// bloki zejdą o krok niżej po liczbie ruchów określonej przez wzór r + n
			int n;	// n to bonus czasowy od 0 do wartości podanej jako 'n' przed grą
			cout << " Witaj Graczu! " << endl << "Podaj rozmiary planszy na jakiej chcesz grac:" << endl << " Ilosc wierszy:  ";
			cin >> w;
			cout << endl << "Ilosc kolumn:  ";
			cin >> k;
			cout << endl << "Poczatkowa ilosc blokow w kazdej kolumnie:  ";
			cin >> b;
			cout << endl << "po ilu ruchach conajmniej schodzodza bloki?:  ";
			cin >> r;
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

			//            Player(k);

			system("pause");
		}
		else if (wybor == 2)
		{
			cout << endl;
			cout << "        . -----=====||||=====----- .           " << endl;
			cout << " This game was made by Marek Mikulski " << endl;
			cout << "          -----=====||||=====-----            " << endl;
			cout << endl;
			system("pause");
		}
		else if (wybor == 3)
		{
			cout << endl << "There are no options actually..." << endl;
			cout << "I'm sorry" << endl << endl;
			system("pause");
		}
		else if (wybor != 1 && wybor != 2 && wybor != 3 && wybor != 0)
		{
			cout << endl << " Nie ma takiego numeru w menu" << endl;
			system("pause");
		}
	} while (wybor != 0);
	cout << endl << endl << "   Do zobaczenia :)    " << endl << endl;
	Sleep(1000);
	return 0;
}
