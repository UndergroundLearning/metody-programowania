#include <iostream>

using namespace std;

class osoba
{
	protected:
	string naz;
	unsigned wi;
	public:
	osoba(): naz("brak"), wi(0){}
	osoba(const string& nazwisko, const unsigned wiek): naz(nazwisko), wi(wiek){}
	string& nazwisko(){return naz;}
	unsigned& liczba_lat(){return wi;}
	const string& nazwisko() const {return naz;}
	const unsigned& liczba_lat() const {return wi;}
	void pokaz() const	//dodałem tu consta, bo piątkowski powiedział, że tak będzie lepiej przy "pokazywaczach"
	{
		cout << naz << " " << wi << endl;
	}
};

class pracownik : public osoba
{
	protected:
	string stan;
	unsigned pl;
	public:
	pracownik(): osoba("brak", 0), stan("brak"), pl(0){}
	pracownik(const string& nazwisko, const unsigned wiek, const string& stanowisko, const unsigned placa): osoba(nazwisko, wiek), stan(stanowisko), pl(placa){}
	void pokaz()
	{
		cout << naz << " " << wi << " " << stan << " " << pl << endl;
	}
	string& stanowisko(){return stan;}
	unsigned& placa(){return pl;}
	const string& stanowisko() const {return stan;}
	const unsigned& placa() const {return pl;}
};

int main()
{
	osoba const os("Dolas", 26); //patrz wyżej
	os.pokaz();
	const pracownik pr1("Dyzma", 35, "mistrz", 1250.0);
	cout << pr1.nazwisko() << " " << pr1.liczba_lat() << " ";
	cout << pr1.stanowisko() << " " << pr1.placa() << endl;
	pracownik pr2(pr1);
	pr2.pokaz();
	pracownik pr3("Kos", 45, "kierownik", 2260.0);
	pr3.pokaz();
	pr3 = pr2;
	pr3.pokaz();
	osoba* w = &os;
	w->pokaz();
	w = &pr3;
	w->pokaz();
	static_cast<pracownik*>(w)->pokaz();
}
