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
	osoba* w = &os;
	w->pokaz();
	w = &pr3;
	w->pokaz();
	cout<<endl<<endl;
	static_cast<pracownik*>(w)->pokaz();
	
	return 0;
}
