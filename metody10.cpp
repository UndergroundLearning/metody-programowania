#include <iostream>

using namespace std;

class operacja
{
	string op;
	int wart;
	public:
	operacja(): op("brak"), wart(0){}
	operacja(const string& opis, const int wartosc): op(opis), wart(wartosc){}
	//metody dostepu..
	string& opis(){return op;}
	int& wartosc(){return wart;}
	const string& opis() const {return op;}
	const int& wartosc() const {return wart;}
};

class robot
{
	protected:
	unsigned nr;
	public:
	robot(): nr(0){}
	robot(const unsigned numer): nr(numer){}
	virtual void praca() const {} //definicja virtualnej metody, ktora dla 'robot' nie bedzie nic robila
	virtual ~robot(){} // --||-- destruktor virtualny, dziala tak, ze jak wywoluje sie destruktor klasy pochodnej to automatycznie wywoluja sie destruktory w gore, az do bazowej
};

class robot1R : public robot //robot z jednym ramieniem dziedziczy po 'robot'
{
	protected:
	operacja* I; 
	operacja* II; //wskazniki na obiekt klasy operacja
	public:
	robot1R(): robot(), I(0), II(0){} //jawne wolanie konstruktora domyslnego z 'robot' + zerowanie wskaznikow
	robot1R(const unsigned numer, const operacja* pierwsza, const operacja* druga): robot(numer), I(pierwsza ? new operacja(*pierwsza) : 0), II(druga ? new operacja(*druga): 0){} // tu tez jawne wolanie konstruktora z jednym argumentem z 'robot'
	void praca() const // tu juz definicja tej motody praca, nie powtarza sie juz 'virtual'
	{
		if(I && II)
		{
			cout << I->opis() << " " << I->wartosc() << endl;
			cout << II->opis() << " " << II->wartosc() << endl; //proste wyswietlanie, tak kazal..
		}
		else
			cout << "Brak operacji" << endl;
	}
	~robot1R(){delete I; delete II;} //destruktor, bo sa wskazniki, tez nie powtarza sie juz virtual

};

class robot2R : public robot1R //robot z dwoma ramionami dziedziczy po robocie z jednym, dlatego, ze tworzy sobie jako podobiekt robota z jednym i dokladasz tylko jedno ramie gratis :D
{
	operacja* III; 
	operacja* IV; //drugie ramie (full gratis)
	public:
	robot2R(): robot1R(), III(0), IV(0){} //tez jawnie konstruktor z robot1R, ktory wywola sobie kosntruktor z 'robot', feel me ?
	robot2R(const unsigned numer, const operacja* pierwsza, const operacja* druga, const operacja* trzecia, const operacja* czwarta): robot1R(numer, pierwsza, druga), III(trzecia ? new operacja(*trzecia) : 0), IV(czwarta ? new operacja(*czwarta) : 0 ){} //tutaj tez jawnie wolasz kontruktor ten inicjalizujacy z robota1R i dokladasz inicjalizacje drugiego ramienia
	void praca() const //definicja pracy dla tego z dwoma ramionami (polimorficzna, czyli, ze dla kazdej klasy pochodnej moze miec inna definicje i pozniej na podstawie typu wskaznika w mainie wywola sie odpowiednia
	{
		if(III && IV)
		{
			robot1R::praca(); //dla tego z jednym ramieniem ona jest jez zdefiniowana wiec mozna ja zawolac :P i ona wyswietli co robie to pierwsze ramie
			cout << III->opis() << " " << III->wartosc() << endl; // a tu dokladasz wyswietlanie do robi drugie
			cout << IV->opis() << " " << IV->wartosc() << endl;
		}
		else
			cout << "Brak operacji" << endl;
	}
	~robot2R(){delete III; delete IV;} // --||-- destruktor z wiadomych wzgledow :P
};

class podajnik : public robot //podajnik ma tylko numer, wiec dziedziczy sobie go bezposrednio od 'robot'
{
	public:
	podajnik(): robot(){} //jawnie bo tak :D
	podajnik(const unsigned numer): robot(numer){} //same old shit
	void praca() const
	{
		cout << "Podawanie" << endl; //nie wiedzialem co napisac :P
	}
};

void wykonaj(robot** b, robot** e) //tutaj podwojne wskazniki bo ta 'linia' z maina to tablica wskaznikow do wskaznikow
{
	unsigned roz = e-b; //jak odejmiesz wskaznik konca tablicy od wskaznika poczatku wyjdzie Ci rozmiar
	for(unsigned i=0; i<roz; i++)
	{
		b[i]->praca(); //i w petelce wywolujesz sobie po kolei prace z wszystkich robotow, i tu wlasnie dziala ten polimorfizm, bo ta tablica 'linia' to jest tablica obiektow typu 'robot' a sa w niej rozne roboty(z 1 ramieniem czy tam z dwoma i podajniki), na podstawie typu wywola odpowiednia definicje funkcji praca
	}
}


int main()
{
	operacja o[] = {
	operacja("w lewo", 12), operacja("obrot", 8),
	operacja("w gore", 32), operacja("obrot", 10),
	operacja("w prawo", 5), operacja("w dol", 25),
	operacja("obrot", 32), operacja("w gore", 21),
	operacja("obrot", 11), operacja("w prawo", 6)
			};
	robot* linia[] = {
	new podajnik(0), new robot1R(1, o, o+3),
	new podajnik(2), new robot2R(3, o+2, o+5, o+3, o+6),
	new podajnik(4), new robot2R(5, o, o+4, o+2, o+6),
	new podajnik(6), new robot1R(7, o+7, o+10), //nie wiem czy on sie tu pomylil czy specjalnie dojebal takie cos, ale o+10 to element za ostatnim, koniec tablicy.. wiec wyswietla jakies bzdury i trzeba zrobic obsluge tego wyzej..
	new podajnik(8)
	};
	wykonaj(linia, linia+9);
	for(unsigned i=0; i<9; i++)
		delete linia[i];
}
