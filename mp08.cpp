#include <iostream>

using namespace std;

class osoba {
	protected:
	string nazwisko;
	int lat;
	public:
	osoba(): nazwisko("br"), lat(0) {}
	osoba(string a, int b): nazwisko(a), lat(b) {}
//	osoba(osoba& o): nazwisko(o.nazwisko), lat(o.lat) {}
	string& nazwisko_() {return nazwisko;}
	const string& nazwisko_() const {return nazwisko; }
	int& liczba_lat() {return lat;}
	const int& liczba_lat() const {return lat;}

	void pokaz() const {
		cout<<nazwisko<<endl<<lat<<endl;
	}	
};
class pracownik : public osoba{
	string stan;
	double plac;
	public:
	pracownik(): osoba("br", 0), stan("br"), plac(0) {}
//	pracownik(string a, int b, string c, double d):osoba(a, b), stan(c), plac(d) {}
	pracownik(const string a, const int b, const string c, const double d): osoba(a, b), stan(c), plac(d) {}
	pracownik(const pracownik& p): osoba(p.nazwisko, p.lat), stan(p.stan), plac(p.plac) {}

	string& stanowisko() {return stan;}
	const string& stanowisko() const {return stan;}
	double& placa() {return plac;}
	const double& placa() const {return plac;}
/*	void pokaz() {
		cout<<stan<<endl<<plac<<endl;
	}
*/};

int main() {
	osoba os("Dolas", 26);
	os.pokaz();
	const pracownik pr1("Dyzma", 35, "mistrz", 1250.0);
	cout << pr1.nazwisko_() << pr1.liczba_lat();
	cout << pr1.stanowisko() << pr1.placa()<<endl;
	pracownik pr2(pr1);
	pr2.pokaz();
	pracownik pr3("Kos", 45, "kierownik", 2260.0);
	pr3.pokaz();
	pr3 = pr2;
	pr3.pokaz();
	osoba* w = &os; //tworzysz wskaznik na osobe i wrzucasz tam adres obiektu 'os'
	w->pokaz(); //wywolujesz metode pokaz dla niego (czyli osoby) i pokazuje standardowo pola osoby
	w = &pr3; //teraz wrzucasz pod niego adres obiektu pr3 (zauwaz, ze ten obiekt jest typu pracownik, a wskaznik stworzyles na osobe)
	w->pokaz(); //wywulujesz metode pokaz() i co sie dzieje ? mimo, ze jest tam adres obiektu pracownik to ta metoda pokaze Ci tylko pola z osoby (bo wskaznik jest na klase osoba, wiec reszte obcina)
	cout<<endl<<endl;
	static_cast<pracownik*>(w)->pokaz(); //i tutaj magia.. konwertujesz typ wskaznika (ktory byl na OSOBA*) na PRACOWNIK* i teraz jak wywolujesz te metode pokaz (tego samego obiektu)
	// to wyswietli Ci wszystkie pola
	
	return 0;
}
