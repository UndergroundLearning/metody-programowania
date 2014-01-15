#include <iostream>

using namespace std;

class pojazd
{
	protected:
	string nr;
	unsigned liczba;
	public:
	pojazd(): nr(0), liczba(0){}
	pojazd(const string& numer, const unsigned& licz): nr(numer), liczba(licz){}
	string& nr_rejestracyjny() {return nr;}
	const string& nr_rejestracyjny() const {return nr;}
	unsigned& liczba_pasazerow() {return liczba;}
	const unsigned& liczba_pasazerow() const {return liczba;}
	virtual void wyswietl() const
	{
		cout << nr << " " << liczba << endl;
	}
	virtual ~pojazd(){}
};

class autobus : public pojazd
{
	string naz;
	unsigned* nrl;
	public:
	autobus(): naz("brak"), nrl(0){}
	autobus(const string& numer, const unsigned& licz, const string& nazwisko, const unsigned& nrlin): pojazd(numer, licz), naz(nazwisko), nrl(new unsigned(nrlin)){}
	string& nazwisko_kierowcy() {return naz;}
	const string& nazwisko_kierowcy() const {return naz;}
	unsigned& numer_linii() {return *nrl;}
	const unsigned& numer_linii() const {return *nrl;}
	autobus(const autobus& drugi): pojazd(drugi), naz(drugi.naz), nrl(new unsigned(*drugi.nrl)){}
	autobus& operator=(const autobus& drugi)
	{
		if(this!=&drugi)
		{
			nr= drugi.nr;
			liczba = drugi.liczba;
			naz = drugi.naz;
			nrl = new unsigned(*drugi.nrl);
		}
		return *this;
	}
	void wyswietl() const
	{
		cout << nr_rejestracyjny() << " " << liczba_pasazerow() << " " << naz << " " << *nrl << endl;
	}
	~autobus() {delete nrl;}
};

int main()
{
	pojazd p1("SC 12345", 20);
	cout << p1.nr_rejestracyjny() << p1.liczba_pasazerow() << endl;
	
	autobus a1("SC 99999", 20, "Kowalski", 24);
	cout << a1.nazwisko_kierowcy() << a1.numer_linii();
	cout << a1.nr_rejestracyjny() << a1.liczba_pasazerow() << endl;
	
	autobus a2(a1);
	a2.wyswietl();
	
	autobus a3("SC 11111", 23, "Jankowski", 16);
	a3.wyswietl();
	a3 = a2;
	a3.wyswietl();
	
	pojazd* p2 = &p1;
	p2->wyswietl();
	p2 = &a3;
	p2->wyswietl();
}
