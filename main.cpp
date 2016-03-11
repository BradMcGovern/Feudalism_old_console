#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Lord.h"

std::vector<Lord> lordList;
std::vector<int> affinityList;
std::vector<int> relationshipList;
std::vector< std::vector<int> > opinionList;

int numberOfLords = 0;
int counter;
int counter2;
int choice;

void initializeLordList();
int affinityCheck (int, int);
int statBomb();
void showVectorMatrix(std::vector<int>&);
void showOpinionMatrix();
int getVectorValue(int, int, std::vector<int>&);
void changeVectorValue(int, int, int, std::vector<int>&);
int getPlayerChoice (int);
int selectALord();
void getLordInformation();
void displayLordInformation(bool);
void takeAnAction();




int main()
{
    bool continueGame = true;

    srand (time(NULL));

    initializeLordList();

    while(continueGame) {
        std::cout << "\n\nWhat action do you want to take?" <<
        "\n1) Get information" <<
        "\n2) Take an action" <<
        "\n3) Quit\n";
        choice = getPlayerChoice(3);
        switch (choice) {
        case 1:
            getLordInformation();
            break;
        case 2:
            takeAnAction();

            break;
        case 3:
            std::cout << "\nGame over!";
            continueGame = false;
            break;
        }
    }


    std::cin.get();
    return 0;
}

void initializeLordList() {

    std::vector<int> stats;
    std::vector<int> opinionVector;
    int affinity;
    int value;
    numberOfLords = 0;


    //set up initial stat list for -2 to 2
    for (int counter = -2; counter < 3; counter++){
        stats.push_back(counter);
    }

    //load lord info from file
    std::ifstream file ( "Irish_Lords.csv" );
    std::string lordName;
    std::string lordTerritory;

    //create all the lords with names form the file and randomize stats
    while (file.good()){
        getline(file, lordName, ',' );
        getline(file, lordTerritory);
        if (lordName != "") {
            random_shuffle (stats.begin(), stats.end());
            //lordNumber = strtol(strLordNumber.c_str(),0,10);
            Lord newLord(lordName,lordTerritory,stats[0],stats[1],stats[2],stats[3],stats[4]);
            lordList.push_back(newLord);
            numberOfLords += 1;
        }

    }//end lord creation

    /********

    This works, but implement later

    std::cout << "\nWhich lord would you like to play as?\n";
    for (counter = 0; counter < numberOfLords; counter++){
        std::cout << counter + 1 << ") " << lordList[counter].getName() << " (" << lordList[counter].getTerritory() << ")\n";
    }
    std::cout << "\nYour choice: ";
    choice = getPlayerChoice(numberOfLords) - 1;
    Lord playerLord = lordList[choice];
    lordList.erase(lordList.begin() + choice);
    lordList.insert(lordList.begin(), playerLord);
    std::cout << "\nYou will play as " << lordList[0].getName() << ", the lord of " << lordList[0].getTerritory();
    ******/

    //create std::vector keys
    int newKey = 0;
    int lordCount = numberOfLords - 1;

    for (counter = 0; counter < lordCount; counter++) {
        lordList[counter].setVectorKey(newKey);
        newKey += lordCount - counter;
    }

    //set affinity between the two lords
    for(counter=0;counter < numberOfLords - 1; counter++){
        for(counter2 = counter + 1; counter2 < numberOfLords; counter2++){//only calculate affinity for lord pairs that have yet been calculated
                affinity = 0;
                affinity += affinityCheck(lordList[counter].getHonorable(), lordList[counter2].getHonorable());
                affinity += affinityCheck(lordList[counter].getPious(), lordList[counter2].getPious());
                affinity += affinityCheck(lordList[counter].getGregarious(), lordList[counter2].getGregarious());
                affinity += affinityCheck(lordList[counter].getAdventurous(), lordList[counter2].getAdventurous());
                affinity += affinityCheck(lordList[counter].getLavish(), lordList[counter2].getLavish());
                affinityList.push_back(affinity);
        }
    }

    //set initial opinion between lords, and set all lord numbers
    for(counter = 0;counter < numberOfLords; counter++){
        lordList[counter].setLordNumber(counter);
        opinionVector.clear();
        for(counter2 = 0; counter2 < numberOfLords; counter2++) {
            if (counter == counter2) {
                opinionVector.push_back(std::max(-99, std::min(99, 100 + (rand() % 41 - 20))));
            } else {
                //affinity = getVectorValue(counter, counter2, affinityList);
                opinionVector.push_back(std::max(-99, std::min(99, getVectorValue(counter, counter2, affinityList) * 15 + (rand() % 41 - 20))));
            }

        }
        opinionList.push_back(opinionVector);
    }

    //set initial relationship between lords
    for(counter = 0;counter < numberOfLords - 1; counter++){
        for(counter2 = counter + 1; counter2 < numberOfLords; counter2++){ //only calculate relationship for lord pairs that have yet been calculated
            relationshipList.push_back(std::max(-75, std::min(75, affinity * 10 + (rand() % 61 - 30))));
            value = statBomb();
            if (value != 0) {
                changeVectorValue(counter, counter2, value, relationshipList);
            }
        }
    }
}


int affinityCheck (int firstLordAttribute, int secondLordAttribute) {
    int affinity = firstLordAttribute * secondLordAttribute;
    if (abs(affinity) > 1){
        affinity /= 2;
    }
return affinity;
}

int statBomb(){
    int value = (rand() % 100);
    if (value < 70) {
        return 0;
    } else if (value < 80) {
        return 25;
    } else if (value < 90) {
        return -25;
    } else if (value < 95) {
        return 50;
    } else {
        return -50;
    }
}

void showVectorMatrix(std::vector<int>& vectorList){
    int value;

    //Print Header
    std::cout << "\n  ";
    for(counter=0; counter < numberOfLords; counter++){
        std::cout << "   " << counter;
    }
    std::cout << "\n--";
    for(counter=0; counter < numberOfLords; counter++){
        std::cout << "----";
    }

    //Print information
    std::cout << "\n";
    for(counter=0; counter < numberOfLords; counter++){
        std::cout << counter << "| ";
        for(counter2 = 0; counter2 < numberOfLords; counter2++){
            if (counter == counter2){
                std::cout << "    ";
            } else {
                value = getVectorValue(counter, counter2, vectorList);
                if (value > -10){
                    std::cout << " ";
                }
                if (value > -1 && value < 10){
                    std::cout << " ";
                }
                std::cout << value << " ";
            }
        }
        std::cout << "\n";

    }

}

void showOpinionMatrix(){
    int value;

    //Print Header
    std::cout << "\n  ";
    for(counter=0; counter < numberOfLords; counter++){
        std::cout << "   " << counter;
    }
    std::cout << "\n--";
    for(counter=0; counter < numberOfLords; counter++){
        std::cout << "----";
    }

    //Print information
    std::cout << "\n";
    for(counter=0; counter < numberOfLords; counter++){
        std::cout << counter << "| ";
        for(counter2 = 0; counter2 < numberOfLords; counter2++){
            if (counter == counter2){
                std::cout << "    ";
            } else {
                value = opinionList[counter] [counter2];
                if (value > -10){
                    std::cout << " ";
                }
                if (value > -1 && value < 10){
                    std::cout << " ";
                }
                std::cout << value << " ";
            }
        }
        std::cout << "\n";

    }

}

int getVectorValue(int firstLord, int secondLord, std::vector<int>& vectorList){
    if (firstLord < secondLord)
        return vectorList[lordList[firstLord].getVectorKey() + (secondLord - firstLord - 1)];
    else
        return vectorList[lordList[secondLord].getVectorKey() + (firstLord - secondLord - 1)];
}

void changeVectorValue(int firstLord, int secondLord, int adjustment, std::vector<int>& vectorList){
    int valueToChange;

    if (firstLord < secondLord)
        valueToChange = lordList[firstLord].getVectorKey() + (secondLord - firstLord - 1);
    else
        valueToChange = lordList[secondLord].getVectorKey() + (firstLord - secondLord - 1);

     vectorList[valueToChange] = std::max(-99, std::min(99,vectorList[valueToChange] + adjustment));
}


int getPlayerChoice (int maximumValue){
    while (true){
        std::cin >> choice;
        if (!std::cin) {
            std::cout << "Please enter a number from 1 to " << maximumValue << "\n";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        } else if (choice < 1 || choice > maximumValue) {
            std::cout << "Please enter a number from 1 to " << maximumValue << "\n";
        } else {
            return choice;
        }
    }
}

int selectALord() {
    std::cout << "\nSelect a lord\n";
    for (counter = 1; counter < numberOfLords; counter++){
        std::cout << counter << ") " << lordList[counter].getName() << " (" << lordList[counter].getTerritory() << ")\n";
    }
    std::cout << "\nYour selection: ";
    return getPlayerChoice(numberOfLords);
}

void getLordInformation () {
    int choice;

    std::cout << "\nWhat information would you like?" <<
            "\n1) See affinity matrix" <<
            "\n2) See relationship matrix" <<
            "\n3) See opinion matrix"
            "\n4) See info on all lords" <<
            "\n5) See info on a single lord" <<
            "\n6) Return \n";
    choice = getPlayerChoice(6);
    switch (choice) {
    case 1:
        std::cout << "\n\nAffinity Matrix";
        showVectorMatrix(affinityList);
        break;
    case 2:
        std::cout << "\n\nRelations Matrix";
        showVectorMatrix(relationshipList);
        break;
    case 3:
        std::cout << "\n\nOpinion Matrix";
        showOpinionMatrix();
        break;
    case 4:
        displayLordInformation(true);
        break;
    case 5:
        displayLordInformation(false);
        break;
    case 6:
        break;
    }
}

void displayLordInformation(bool showAll){
    if (showAll) {
        for (counter = 1; counter < numberOfLords; counter++){
            std::cout << "\n";
                lordList[counter].showDetails();
                std::cout << "\nRelation with you: " << getVectorValue(0, counter, relationshipList) << "\n";
                std::cout << "Affinity with you: " << getVectorValue(0, counter, affinityList) << "\n";
        }
    } else {
        lordList[selectALord()].showDetails();
    }
}

void takeAnAction(){
    std::cout << "\nWhat type of action would you like to take?" <<
            "\n1) Visit a lord" <<
            "\n2) Hold a feast" <<
            "\n3) Return"<<
            "\n\nEnter action to take: ";
    choice = getPlayerChoice(3);

    switch (choice) {
        case 1:
            std::cout << "\nYou visit a lord";
            break;
        case 2:
            std::cout << "\nYou hold a feast";
            break;
        case 3:
            break;
    }
}

