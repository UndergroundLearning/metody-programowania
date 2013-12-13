#include <iostream>

using namespace std;

class operacja
{
        string op;
        int wart;
        public:
        operacja(): op("brak"), wart(0){}
        operacja(const string& opis, const int wartosc): op(opis), wart(wartosc){}
        string& opis(){return op;}
        const string& opis() const {return op;}
        int& wartosc(){return wart;}
        const int& wartosc() const {return wart;}
};

class robot
{
        protected:
        unsigned nr;
        public:
        robot(): nr(0){}
        robot(const unsigned numer): nr(numer){}
        virtual void praca() const = 0;
        virtual ~robot(){}
};

class robot1R : public robot
{
        protected:
        unsigned roz1;
        operacja* ram1;
        public:
        robot1R(): robot(), roz1(0), ram1(0){}
        robot1R(const unsigned numer, const operacja* b, const operacja* e): robot(numer), roz1((e-b)?e-b:0), ram1(roz1 ? new operacja[roz1] : 0)
        {
                for(unsigned i=0; i<roz1; i++)
                        ram1[i] = b[i];
        }
        robot1R(const robot1R& drugi): robot(drugi), roz1(drugi.roz1), ram1(roz1 ? new operacja [roz1] : 0)
        {
                for(unsigned i=0; i<roz1; i++)
                        ram1[i] = drugi.ram1[i];
        }
        robot1R& operator = (const robot1R& drugi)
        {
                if(this != &drugi)
                {
						nr = drugi.nr;
                        delete [] ram1;
                        roz1 = drugi.roz1;
						ram1 = roz1 ? new operacja [roz1] : 0;
                        for(unsigned i=0; i<roz1; i++)
                                ram1[i] = drugi.ram1[i];
                }
                return *this;
        }
        void praca() const
        {
                if(ram1)
                {
                        for(unsigned i=0; i<roz1; i++)
                        {
                                cout << ram1[i].opis() << " " << ram1[i].wartosc() << endl;
                        }
                }
        }
        ~robot1R(){delete []ram1;}
};

class robot2R : public robot1R
{
        unsigned roz2;
        operacja* ram2;
        public:
        robot2R(): robot1R(), roz2(0), ram2(0){}
        robot2R(const unsigned numer, const operacja* b1, const operacja* e1, const operacja* b2, const operacja* e2): robot1R(numer, b1, e1), roz2((e2-b2)>0 ? e2-b2 : 0), ram2(roz2 ? new operacja[roz2] : 0)
        {
                for(unsigned i=0; i<roz2; i++)
                        ram2[i] = b2[i];
        }
        robot2R(const robot2R& drugi): robot1R(drugi), roz2(drugi.roz2), ram2(roz2 ? new operacja[roz2] : 0)
        {
                for(unsigned i=0; i<roz2; i++)
                        ram2[i] = drugi.ram2[i];
        }
        robot2R& operator= (const robot2R& drugi)
        {
                if(this!=&drugi)
                {
                        robot1R::operator=(drugi);
                        roz2 = drugi.roz2;
                        delete [] ram2;
                        ram2 = roz2 ? new operacja[roz2] : 0;
                        for(unsigned i=0; i<roz2; i++)
                                ram2[i] = drugi.ram2[i];
                }
                return *this;
        }
        void praca() const
        {
                robot1R::praca();
                if(ram2)
                {
                        for(unsigned i=0; i<roz2; i++)
                                cout << ram2[i].opis() << " " << ram2[i].wartosc() << endl;
                }
        }
        ~robot2R(){delete[] ram2;}
};

class podajnik : public robot
{
        public:
        podajnik(): robot(){}
        podajnik(const unsigned numer): robot(numer){}
        void praca() const
        {
                cout << "Podajnik" << endl;
        }
};

void wykonaj(robot** b, robot** e)
{
        unsigned roz= e-b;
        for(unsigned i=0; i<roz; i++)
				b[i]->praca();
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
new podajnik(6), new robot1R(7, o+7, o+10),
new podajnik(8)
};
wykonaj(linia, linia+9);
for(unsigned i=0; i<9; i++)
        delete linia[i];
}
