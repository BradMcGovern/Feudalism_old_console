#ifndef TERRITORY_H
#define TERRITORY_H
#include<iostream>


class Territory
{
    public:
        Territory();
        virtual ~Territory();

        std::string Getname() { return name; }
        void Setname(std::string val) { name = val; }
        int Getnumber() { return number; }
        void Setnumber(int val) { number = val; }
        int Getwealth() { return wealth; }
        void Setwealth(int val) { wealth = val; }
        int Getpopulation() { return population; }
        void Setpopulation(int val) { population = val; }
        int GetfightingStrength() { return fightingStrength; }
        void SetfightingStrength(int val) { fightingStrength = val; }
        int GetlordNumber() { return lordNumber; }
        void SetlordNumber(int val) { lordNumber = val; }

    protected:

    private:
        std::string name;
        int number;
        int wealth;
        int population;
        int fightingStrength;
        int lordNumber;
};

#endif // TERRITORY_H
