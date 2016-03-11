#ifndef LORD_H
#define LORD_H
#include<iostream>


class Lord
{
    public:
        Lord();
        Lord(std::string, std::string, int, int, int, int, int);
        virtual ~Lord();

        std::string getName() { return name; }
        std::string getTerritory() { return territory; }
        int getHonorable() { return honorable; };
        int getPious() { return pious; };
        int getGregarious() { return gregarious; };
        int getAdventurous() { return adventurous; };
        int getLavish() { return lavish; };
        int getLordNumber() { return lordNumber; };
        void setLordNumber(int val) { lordNumber = val; }
        int getVectorKey() { return vectorKey; };
        void setVectorKey(int val) { vectorKey = val; }
        void showDetails();


    private:
        std::string name;
        std::string territory;
        int honorable;
        int pious;
        int gregarious;
        int adventurous;
        int lavish;
        int lordNumber;
        int vectorKey;

};


#endif // LORD_H
