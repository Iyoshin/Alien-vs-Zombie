// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT3L
// Names:  NG YI MIN | NUR'AIN AFIQAH BINTI ABDULL HAKIM
// IDs: 1221303664 | 1221303643
// Emails: 1221303664@student.mmu.edu.my | 1221303643@student.mmu.edu.my
// Phones: 011-56911939 | 016-2941806
// *********************************************************

#include "pf/helper.h"
#include <iostream>
#include "board.cpp"
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <iomanip> //for setw()
#include <fstream>
#include <string>
using namespace std;

void alienMoveUp(Alien *al, Board *bd, Zombie zo[], int zombieCount); // early declaration
void alienMoveDown(Alien *al, Board *bd, Zombie zo[], int zombieCount);
void alienMoveLeft(Alien *al, Board *bd, Zombie zo[], int zombieCount);
void alienMoveRight(Alien *al, Board *bd, Zombie zo[], int zombieCount);

void pauseClear()
{
    pf::Pause();
    pf::ClearScreen();
}

void boardSettings(int &x, int &y)
{
    bool change = false;
    do
    {
        cout << "Board Settings" << endl;
        cout << "----------------" << endl;
        cout << "Enter rows (odd number only) => ";
        cin >> x;

        cout << "Enter columns (odd number only) => ";
        cin >> y;
        cout << endl;

        if ((x % 2 == 0) || // if no odd number need to re-enter the values
            (y % 2 == 0))
        {
            cout << "Please re-enter rows and columns..." << endl;
            pf::Pause();
            cout << endl;
        }
        else
        {
            change = true;
        }
    } while (!change);
}

void zombieSettings(int &zombieCount)
{
    bool change = false;
    do
    {

        cout << "Zombie Settings" << endl;
        cout << "----------------" << endl;
        cout << "Enter number of zombies (max 9) => ";
        cin >> zombieCount;
        cout << endl;

        if ((zombieCount > 9) || (zombieCount < 1)) // check if more than 9 or less than 1
        {
            cout << "Please re-enter number of zombies..." << endl;
            pf::Pause();
            cout << endl;
        }
        else
        {
            change = true;
        }
    } while (!change);
}

void defaultGame(int rows, int columns, int zombieCount)
{
    pf::ClearScreen();
    cout << "Default Game Settings" << endl;
    cout << "----------------------" << endl;
    cout << "Board Rows     : " << rows << endl;
    cout << "Board Columns  : " << columns << endl;
    cout << "Zombie Count   : " << zombieCount << endl;
    cout << endl;
}

void displayAlienStat(Alien al) // just to display stat
{
    cout << setw(21); // lining up the display
    cout << " Alien     : Life: " << setw(3) << al.getHp() << " Atk: " << setw(3) << al.getAtk() << endl;
}

void displayZombieStat(Zombie zo[], int zombieCount) // just to display stat
{
    for (int i = 0; i < zombieCount; ++i)
    {
        cout << setw(9); // lining up the display
        cout << " Zombie" << i + 1 << "   : Life: " << setw(3) << zo[i].getZombieHp() << " Atk: " << setw(3) << zo[i].getZombieAtk() << " Range: " << setw(1) << zo[i].getZombieRange() << endl;
    }
    cout << endl;
}

void alienTurn(Alien al) // display -> to indicate the current playing character
{
    cout << "->";
    cout << " Alien     : Life: " << setw(3) << al.getHp() << " Atk: " << setw(3)  << al.getAtk() << endl;
}

void zombieTurn(Zombie zo[], int zombieCount, int n) // display -> to indicate the current moving character
{
    for (int i = 0; i < zombieCount; ++i)
    {
        if (n == i)
        {
            cout << "->";
            cout << " Zombie" << i + 1 << "   : Life: " << setw(3) << zo[i].getZombieHp() << " Atk: " << setw(3) << zo[i].getZombieAtk() << " Range: " << setw(1) << zo[i].getZombieRange() << endl;
        }
        else
        {
            cout << setw(9);
            cout << " Zombie" << i + 1 << "   : Life: " << setw(3) << zo[i].getZombieHp() << " Atk: " << setw(3) << zo[i].getZombieAtk() << " Range: " << setw(1) << zo[i].getZombieRange() << endl;
        }
    }
    cout << endl;
}

char findNearestZombie(Board bd, Alien al, Zombie zo[], int zombieCount)
{
    int alX = al.getX();
    int alY = al.getY();
    int bdX = bd.getRow();
    int bdY = bd.getCol();
    int nearest = (bdX)*(bdX) + (bdY)*(bdY); //ensure the value is large enough
    int nZ_; // storage for nearest zombie
    vector<char> zb;

    for (int i = 0; i < zombieCount; ++i)
    {
        if (!zo[i].zombieDefeat())
        {
            int nearZ = zo[i].getZombieChar();
            int zoX = zo[i].getZombieRow();
            int zoY = zo[i].getZombieCol();
            int distance_ = (alX - zoX) * (alX - zoX) + (alY - zoY) * (alY - zoY); // calculate distance, inspired by internet's forum. This formula is derived from the distance between 2 points but no sqrt

            if (distance_ < nearest) // comparing
            {   
                zb.clear(); // clear container if previous one is not the nearest
                nearest = distance_;
                nZ_ = nearZ;
                zb.push_back(nearZ);
             
            }
            if (distance_ == nearest) // if same shortest distance found push back the char and then rng it, the nZ_ will continuously update if more numbers are added to it
            {
                zb.push_back(nearZ);
                int noOfSameDist = zb.size();
                int rnd = rand() % noOfSameDist;

                nZ_ = zb[rnd];
            }
        }
    }

    return nZ_;
}

void podCombat(Board bd, Alien al, Zombie zo[], int zombieCount)
{
    int dmg = 10;
    char nearZomb = findNearestZombie(bd, al, zo, zombieCount);
    for (int i = 0; i < zombieCount; ++i)
    {
        if (nearZomb == zo[i].getZombieChar())
        {
            zo[i].zombieReceiveDmg(dmg);
            cout << "Zombie" << i + 1 << " received 10 damage from pod!" << endl;
        }
    }
}

int searchEnemy(Board *bd, Zombie zo[], int zombieCount, int x, int y)
{
    int i;
    for (i = 0; i < zombieCount; i++)
    {
        cout << "x: " << x << " y: " << y << " char: "<< zo[i].getZombieChar() << endl;
        if (bd->getObj(x, y) == zo[i].getZombieChar()) // searching for the enemy
        {
            
            i = i; // return i to identify which zombie
            break;
        }
    }
    cout << i;
    return i;
}

void checkAlienWithinRange(Board *bd, Alien *al, Zombie zo[], int zombieCount, int i)
{
    int range = zo[i].getZombieRange();
    int zombX = zo[i].getZombieRow();
    int zombY = zo[i].getZombieCol();

    int alienX = al->getX();
    int alienY = al->getY();

    int distanceX = zombX - alienX;
    int distanceY = zombY - alienY;
    if (distanceX < 0)
    {
        distanceX = -1 * distanceX;
    }
    if (distanceY < 0)
    {
        distanceY = -1 * distanceY;
    }

    if (((zombX == alienX) && (distanceY <= range))) // same row , different column
    {
        cout << "Zombie" << i + 1 << " attacks Alien!" << endl;
        int dmg = zo[i].getZombieAtk();
        al->alienReceiveDmg(dmg);
        cout << "Alien received " << dmg << " damage!" << endl;
    }
    else if (((zombY == alienY) && (distanceX <= range))) // same column, different row
    {
        cout << "Zombie" << i + 1 << " attacks Alien!" << endl;
        int dmg = zo[i].getZombieAtk();
        al->alienReceiveDmg(dmg);
        cout << "Alien received " << dmg << " damage!" << endl;
    }
    else
    {
        cout << "Alien is out of range..." << endl;
    }
}

void changeArrow(Board *bd, Alien *al, Zombie zo[], int zombieCount)
{
    int x;
    int y;
    string direction;

    cout << "Enter row, column, and direction: ";
    cin >> x >> y >> direction;
    char arr_ = bd->getObj(x, y);
    char arr[] = {'^', 'v', '<', '>'};

    if ((!bd->arrowUp(x, y)) && // checking for arrow
        (!bd->arrowDown(x, y)) &&
        (!bd->arrowLeft(x, y)) &&
        (!bd->arrowRight(x, y)))
    {
        cout << "Arrow does not exists at (" << x << ", " << y << ")" << endl;
    }
    else
    {
        if (direction == "up")
        {
            bd->setObj(x, y, arr[0]);
            cout << "The arrow " << arr_ << " is changed to " << arr[0] << endl;
        }
        if (direction == "down")
        {
            bd->setObj(x, y, arr[1]);
            cout << "The arrow " << arr_ << " is changed to " << arr[1] << endl;
        }
        if (direction == "left")
        {
            bd->setObj(x, y, arr[2]);
            cout << "The arrow " << arr_ << " is changed to " << arr[2] << endl;
        }
        if (direction == "right")
        {
            bd->setObj(x, y, arr[3]);
            cout << "The arrow " << arr_ << " is changed to " << arr[3] << endl;
        }
    }
    pauseClear();
}

void alienMoveUp(Alien *al, Board *bd, Zombie zo[], int zombieCount)
{
    while (1)
    {
        int x = al->getX();
        int y = al->getY();
        if (al->getY() == 1)
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien hits the border." << endl;
            cout << endl;
            pauseClear();
            break;
        }
        if (bd->rock(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a rock." << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            bd->rockObj(x, y - 1);
            cout << endl;
            pauseClear();

            break;
        }
        if (bd->zombiePresent(x, y - 1))
        {
            int i = searchEnemy(bd, zo, zombieCount, x, y - 1);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien attacks zombie" << i + 1 << "!" << endl;
            cout << endl;
            pauseClear();

            int dmg = al->getAtk();
            zo[i].zombieReceiveDmg(dmg);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Zombie" << i + 1 << " receives " << dmg << " damage!" << endl;

            if (!zo[i].zombieDefeat())
            {

                cout << "Zombie" << i + 1 << " survived." << endl;
                cout << endl;
                pauseClear();
                break;
            }
            if (zo[i].zombieDefeat())
            {

                cout << "Zombie" << i + 1 << " is defeated!" << endl;
                cout << endl;
                pauseClear();
            }
        }
        if (bd->healthObj(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a health pack!" << endl;
            al->alienGainHealth();
            cout << endl;
            pauseClear();
        }
        if (bd->pod(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a pod!" << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            podCombat(*bd, *al, zo, zombieCount);
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << endl;
            pauseClear();
        }
        if (bd->gridIsEmpty(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds an empty space. There's nothing inside." << endl;
            cout << endl;
            pauseClear();
        }
        if (bd->arrowLeft(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveUp(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving to left now." << endl;
            cout << endl;
            pauseClear();

            alienMoveLeft(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowRight(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveUp(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving to right now." << endl;
            cout << endl;
            pauseClear();

            alienMoveRight(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowUp(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveUp(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien continues to move up." << endl;
            cout << endl;
            pauseClear();

            alienMoveUp(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowDown(x, y - 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveUp(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving down now." << endl;
            cout << endl;
            pauseClear();

            alienMoveDown(al, bd, zo, zombieCount);
            break;
        }

        al->moveUp(*bd);
        bd->displayBoard();
        alienTurn(*al);
        displayZombieStat(zo, zombieCount);
        cout << endl;
        pauseClear();
    }
}

void alienMoveDown(Alien *al, Board *bd, Zombie zo[], int zombieCount)
{

    while (1)
    {
        int x = al->getX();
        int y = al->getY();
        if (al->getY() == bd->getCol())
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien hits the border." << endl;
            cout << endl;
            pauseClear();
            break;
        }
        if (bd->rock(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a rock." << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            bd->rockObj(x, y + 1);
            cout << endl;
            pauseClear();

            break;
        }
        if (bd->zombiePresent(x, y + 1))
        {
            int i = searchEnemy(bd, zo, zombieCount, x, y + 1);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien attacks zombie" << i + 1 << "!" << endl;
            cout << endl;
            pauseClear();

            int dmg = al->getAtk();
            zo[i].zombieReceiveDmg(dmg);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Zombie" << i + 1 << " receives " << dmg << " damage!" << endl;

            if (!zo[i].zombieDefeat())
            {

                cout << "Zombie" << i + 1 << " survived." << endl;
                cout << endl;
                pauseClear();
                break;
            }
            if (zo[i].zombieDefeat())
            {

                cout << "Zombie" << i + 1 << " is defeated!" << endl;
                cout << endl;
                pauseClear();
            }
        }
        if (bd->healthObj(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a health pack!" << endl;
            al->alienGainHealth();
            cout << endl;
            pauseClear();
        }
        if (bd->pod(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a pod!" << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            podCombat(*bd, *al, zo, zombieCount);
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << endl;
            pauseClear();
        }
        if (bd->gridIsEmpty(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds an empty space. There's nothing inside." << endl;
            cout << endl;
            pauseClear();
        }
        if (bd->arrowLeft(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveDown(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving to left now." << endl;
            cout << endl;
            pauseClear();

            alienMoveLeft(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowRight(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveDown(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving to right now." << endl;
            cout << endl;
            pauseClear();

            alienMoveRight(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowUp(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveDown(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving up now." << endl;
            cout << endl;
            pauseClear();

            alienMoveUp(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowDown(x, y + 1))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveDown(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien continues to move down." << endl;
            cout << endl;
            pauseClear();

            alienMoveDown(al, bd, zo, zombieCount);
            break;
        }

        al->moveDown(*bd);
        bd->displayBoard();
        alienTurn(*al);
        displayZombieStat(zo, zombieCount);
        cout << endl;
        pauseClear();
    }
}

void alienMoveLeft(Alien *al, Board *bd, Zombie zo[], int zombieCount)
{

    while (1)
    {
        int x = al->getX();
        int y = al->getY();
        if (al->getX() == 1)
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien hits the border." << endl;
            cout << endl;
            pauseClear();
            break;
        }
        if (bd->rock(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a rock." << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            bd->rockObj(x - 1, y);
            cout << endl;
            pauseClear();

            break;
        }
        if (bd->zombiePresent(x - 1, y))
        {
            int i = searchEnemy(bd, zo, zombieCount, x - 1, y);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien attacks zombie" << i + 1 << "!" << endl;
            cout << endl;
            pauseClear();

            int dmg = al->getAtk();
            zo[i].zombieReceiveDmg(dmg);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Zombie" << i + 1 << " receives " << dmg << " damage!" << endl;

            if (!zo[i].zombieDefeat())
            {

                cout << "Zombie" << i + 1 << " survived." << endl;
                cout << endl;
                pauseClear();
                break;
            }
            if (zo[i].zombieDefeat())
            {

                cout << "Zombie" << i + 1 << " is defeated!" << endl;
                cout << endl;
                pauseClear();
            }
        }
        if (bd->healthObj(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a health pack!" << endl;
            al->alienGainHealth();
            cout << endl;
            pauseClear();
        }
        if (bd->pod(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a pod!" << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            podCombat(*bd, *al, zo, zombieCount);
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << endl;
            pauseClear();
        }
        if (bd->gridIsEmpty(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds an empty space. There's nothing inside." << endl;
            cout << endl;
            pauseClear();
        }
        if (bd->arrowLeft(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveLeft(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien continues to move left." << endl;
            cout << endl;
            pauseClear();

            alienMoveLeft(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowRight(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveLeft(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moveing to right now." << endl;
            cout << endl;
            pauseClear();

            alienMoveRight(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowUp(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveLeft(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving up now." << endl;
            cout << endl;
            pauseClear();

            alienMoveUp(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowDown(x - 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveLeft(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving down now." << endl;
            cout << endl;
            pauseClear();

            alienMoveDown(al, bd, zo, zombieCount);
            break;
        }

        al->moveLeft(*bd);
        bd->displayBoard();
        alienTurn(*al);
        displayZombieStat(zo, zombieCount);
        cout << endl;
        pauseClear();
    }
}

void alienMoveRight(Alien *al, Board *bd, Zombie zo[], int zombieCount)
{

    while (1)
    {
        int x = al->getX();
        int y = al->getY();
        if (al->getX() == bd->getRow())
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien hits the border." << endl;
            cout << endl;
            pauseClear();
            break;
        }
        if (bd->rock(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a rock." << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            bd->rockObj(x + 1, y);
            cout << endl;
            pauseClear();

            break;
        }
        if (bd->zombiePresent(x + 1, y))
        {
            int i = searchEnemy(bd, zo, zombieCount, x + 1, y);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien attacks zombie" << i + 1 << "!" << endl;
            cout << endl;
            pauseClear();

            int dmg = al->getAtk();
            zo[i].zombieReceiveDmg(dmg);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Zombie" << i + 1 << " receives " << dmg << " damage!" << endl;

            if (!zo[i].zombieDefeat())
            {

                cout << "Zombie" << i + 1 << " survived." << endl;
                cout << endl;
                pauseClear();
                break;
            }
            if (zo[i].zombieDefeat())
            {
                cout << "Zombie" << i + 1 << " is defeated!" << endl;
                cout << endl;
                pauseClear();
            }
        }
        if (bd->healthObj(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a health pack!" << endl;
            al->alienGainHealth();
            cout << endl;
            pauseClear();
        }
        if (bd->pod(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds a pod!" << endl;
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            podCombat(*bd, *al, zo, zombieCount);
            cout << endl;
            pauseClear();

            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << endl;
            pauseClear();
        }
        if (bd->gridIsEmpty(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien finds an empty space. There's nothing inside." << endl;
            cout << endl;
            pauseClear();
        }
        if (bd->arrowLeft(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveRight(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving to left now." << endl;
            cout << endl;
            pauseClear();

            alienMoveLeft(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowRight(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveRight(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien continues to move right." << endl;
            cout << endl;
            pauseClear();

            alienMoveRight(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowUp(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveRight(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving to left now." << endl;
            cout << endl;
            pauseClear();

            alienMoveUp(al, bd, zo, zombieCount);
            break;
        }
        if (bd->arrowDown(x + 1, y))
        {
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            al->alienGainAtk();
            cout << "Alien finds an arrow!" << endl;
            cout << "Alien gained 20 atk!" << endl;
            cout << endl;
            pauseClear();

            al->moveRight(*bd);
            bd->displayBoard();
            alienTurn(*al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien is moving down now." << endl;
            cout << endl;
            pauseClear();

            alienMoveDown(al, bd, zo, zombieCount);
            break;
        }

        al->moveRight(*bd);
        bd->displayBoard();
        alienTurn(*al);
        displayZombieStat(zo, zombieCount);
        cout << endl;
        pauseClear();
    }
}

void saveFile(Alien *al, Board *bd, Zombie zo[], int *zombieCount, int *rows, int *columns)
{
    string fileName;
    cout << "Enter the file name to save the current game (e.g. text1.txt), input (./0) to abort: ";
    cin >> fileName;
    cout << endl;
    if ((fileName == ".") || (fileName == "0"))
    {
        cout << "Saving aborted, the game continues." << endl;
        
    }
    else
    {
        ofstream outputFile(fileName, ios::out);

        outputFile << setw(3) << *zombieCount << setw(3) << *rows << setw(3) << *columns << endl;                      // saving line for zombieCount, Row, Col, setw(3) for different section of information
        outputFile << setw(3) << al->getX() << setw(3) << al->getY() << setw(3) << al->getHp() << setw(3) << al->getAtk() << endl; // alien x, y , hp , atk
        for (int i = 0; i < *zombieCount; ++i)
        {
            outputFile << setw(3) << zo[i].getZombieRow() << setw(3) << zo[i].getZombieCol() << setw(3) << zo[i].getZombieHp() << setw(3) << zo[i].getZombieAtk() << setw(1) << zo[i].getZombieRange() << setw(3) << zo[i].getZombieChar() << endl; // zombie x, y, hp, atk, range
        }
        for (int i = 1; i <= bd->getCol(); ++i)
        {
            for (int j = 1; j <= bd->getRow(); ++j)
            {
                outputFile << setw(1) << bd->getObj(j, i); //board objects
            }

            outputFile << endl;
        }
        outputFile.close();

        cout << "Game file saved as " << fileName << ". The game continues." << endl
             << endl;
        
    }
    pauseClear();
}

void loadFile(Alien *al, Board *bd, Zombie zo[], int *zombieCount, int *rows, int *columns)
{
    string fileName;
    string temp; // act as buffer
    int counter = 0;
    int zb = 0;
    int alX, alY, alHp, alAtk;
    int zoX, zoY, zoHp, zoAtk, zoRange;
    char zoChar;
    int i = 1;
    char bdChar;

    cout << "Enter the file name to load: ";
    cin >> fileName;

    ifstream inputFile(fileName, ios::in);

    if (inputFile.is_open()) //if file successfully open
    {
        while (getline(inputFile, temp)) //reading line by line, inspired by internet forum
        {
            if (counter == 0)
            {
                *zombieCount = stoi(temp.substr(0, 3)); // substring read from [0] size of 3, string to int
                *rows = stoi(temp.substr(3, 3)); 
                *columns = stoi(temp.substr(6, 3));

                bd->setRow(*rows); // set the loaded values
                bd->setCol(*columns);
            }
            else if (counter == 1)
            {
                alX = stoi(temp.substr(0, 3));
                alY = stoi(temp.substr(3, 3));
                alHp = stoi(temp.substr(6, 3));
                alAtk = stoi(temp.substr(9, 3));

                al->setAlienX(alX);
                al->setAlienY(alY);
                al->setAlienHp(alHp);
                al->setAlienAtk(alAtk);
            }
            else if (counter > 1 && counter <= (1 + *zombieCount))
            {
                zoX = stoi(temp.substr(0, 3));
                zoY = stoi(temp.substr(3, 3));
                zoHp = stoi(temp.substr(6, 3));
                zoAtk = stoi(temp.substr(9, 3));
                zoRange = stoi(temp.substr(12, 3));
                zoChar = temp[15];

                zo[zb].setZombieX(zoX);
                zo[zb].setZombieY(zoY);
                zo[zb].setZombieHp(zoHp);
                zo[zb].setZombieAtk(zoAtk);
                zo[zb].setZombieRange(zoRange);
                zo[zb].setZombieChar(zoChar);

                zb++; // +1 until this section stops
            }
            else
            {
                for (int j = 1; j <= bd->getRow(); ++j)
                {
                    bdChar = temp[j - 1];
                    bd->setObj(j, i, bdChar);
                }
                i++; // + 1 until the section stops
            }
            counter++;
        }

        cout << "Game loaded." << endl;
    }
    else // no such file existed
    {
        cout << "There is no such file existed." << endl;
    }

    inputFile.close();
    pauseClear();
}

int main()
{
    srand(time(NULL));
    int rows = 5;
    int columns = 9;
    int zombieCount = 1;
    int x;
    int y;
    char ans;

    char restart;

    Alien al = Alien();
    Zombie zo[9] = {Zombie()}; // declare zombie as array
    Board bd = Board(rows, columns);

    bool turnEnd = false;

    do // restart loop
    {

        bool win = false;
        bool lose = false;
        bool quit = false;

        defaultGame(rows, columns, zombieCount);

        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> ans;
        cout << endl;

        if (ans == 'y' || ans == 'Y')
        {
            pf::ClearScreen();
            boardSettings(rows, columns);
            bd.fill_(rows, columns); // only call for fill_ function after change
            zombieSettings(zombieCount);

            cout << "Settings Updated." << endl;
            cout << endl;
            pauseClear();
        }
        else
        {
            bd.fill_(rows, columns);
            cout << "Default settings maintained." << endl;
            cout << endl;
            pauseClear();
        }

        pf::ClearScreen();
        al.setAlienPos(bd);

        for (int i = 0; i < zombieCount; ++i)
        {
            zo[i].setZombPos(bd, zombieCount, i); // set zombie on board
        }
        for (int i = 0; i < zombieCount; ++i)
        {
            zo[i].createZombie(bd, i); // create the stats for each zombie
        }

        while (1) // the main game loop
        {
            do // alien turn
            {
                turnEnd = false;
                string command;

                pf::ClearScreen();
                bd.displayBoard();
                alienTurn(al);
                displayZombieStat(zo, zombieCount);
                cout << "Alien's turn." << endl
                     << endl;
                cout << "command> ";
                cin >> command;

                if (command == "up")
                {
                    pf::ClearScreen();
                    alienMoveUp(&al, &bd, zo, zombieCount);
                    turnEnd = true;
                }
                if (command == "down")
                {
                    pf::ClearScreen();
                    alienMoveDown(&al, &bd, zo, zombieCount);
                    turnEnd = true;
                }
                if (command == "left")
                {
                    pf::ClearScreen();
                    alienMoveLeft(&al, &bd, zo, zombieCount);
                    turnEnd = true;
                }
                if (command == "right")
                {
                    pf::ClearScreen();
                    alienMoveRight(&al, &bd, zo, zombieCount);
                    turnEnd = true;
                }
                if (command == "arrow")
                {
                    changeArrow(&bd, &al, zo, zombieCount);
                }
                if (command == "help")
                {
                    cout << "Commands" << endl;
                    cout << "1. up      - Move up." << endl;
                    cout << "2. down    - Move down." << endl;
                    cout << "3. left    - Move left." << endl;
                    cout << "4. right   - Move right." << endl;
                    cout << "5. arrow   - Input row, column and direction to change arrow facing." << endl;
                    cout << "6. help    - Display commands." << endl;
                    cout << "7. save    - Save file." << endl;
                    cout << "8. load    - Load file." << endl;
                    cout << "9. quit    - Quit game." << endl;
                    pauseClear();
                }
                if (command == "save")
                {
                    saveFile(&al, &bd, zo, &zombieCount, &rows, &columns);
                }
                if (command == "load")
                {
                    cout << "Do you wish to save current game? (y/n) => ";
                    cin >> ans;
                    if (ans == 'y' || ans == 'Y')
                    {
                        saveFile(&al, &bd, zo, &zombieCount, &rows, &columns);
                    }
                    pf::ClearScreen();
                    bd.displayBoard();
                    alienTurn(al);
                    displayZombieStat(zo, zombieCount);
                    loadFile(&al, &bd, zo, &zombieCount, &rows, &columns);
                }
                if (command == "quit")
                {
                    cout << "Are you sure? (y/n) => ";
                    cin >> ans;
                    cout << endl;

                    if (ans == 'y' || ans == 'Y')
                    {
                        quit = true;
                        break;
                    }
                    if (ans != 'y' || ans != 'Y')
                    {
                        cout << "The game continues." << endl;
                        pauseClear();
                    }
                }

            } while (!turnEnd); // alien turn

            if (quit) // break if quit
            {
                break;
            }

            bd.resetTrail(rows, columns);
            al.alienAtkReset();
            bd.displayBoard();
            alienTurn(al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien's turn ended." << endl;
            cout << endl;
            pauseClear();

            int defeat = 0;
            for (int i = 0; i < zombieCount; ++i) // checking if all zombie is defeated
            {
                if (zo[i].zombieDefeat())
                {
                    defeat = defeat + 1;
                }
                if (defeat == zombieCount)
                {
                    win = true;
                }
            }

            if (win) // break if win
            {
                break;
            }

            for (int i = 0; i < zombieCount; ++i) // zombie turn
            {
                if (!zo[i].zombieDefeat())
                {
                    bd.displayBoard();
                    displayAlienStat(al);
                    zombieTurn(zo, zombieCount, i);
                    cout << "Zombie" << 1 + i << "'s turn." << endl;
                    cout << endl;
                    pauseClear();

                    bd.displayBoard();
                    displayAlienStat(al);
                    zombieTurn(zo, zombieCount, i);
                    zo[i].zombieValidMove(bd, i); // moving
                    cout << endl;
                    pauseClear();

                    bd.displayBoard();
                    displayAlienStat(al);
                    zombieTurn(zo, zombieCount, i);
                    checkAlienWithinRange(&bd, &al, zo, zombieCount, i); // attack
                    cout << endl;
                    pauseClear();

                    bd.displayBoard();
                    displayAlienStat(al);
                    zombieTurn(zo, zombieCount, i);
                    cout << "Zombie" << 1 + i << "'s turn ended." << endl;
                    cout << endl;
                    pauseClear();
                }
            }

            if (al.alienDefeat()) // break if lose
            {
                lose = true;
                break;
            }
        }
        if (quit)
        {
            break;
        }
        if (win)
        {
            bd.displayBoard();
            displayAlienStat(al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien wins!" << endl
                 << endl;
        }
        if (lose)
        {
            bd.displayBoard();
            displayAlienStat(al);
            displayZombieStat(zo, zombieCount);
            cout << "Alien lose!" << endl
                 << endl;
        }

        cout << endl;
        cout << "Play again? (y/n) => ";
        cin >> restart;

    } while (restart == 'Y' || restart == 'y');

    if (restart != 'y' || restart != 'Y')
    {
        cout << "Goodbye!";
    }
}
