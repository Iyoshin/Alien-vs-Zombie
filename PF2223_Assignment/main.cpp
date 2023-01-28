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
// #include "test.cpp"
using namespace std;

void alienMoveUp(Alien al, Board &bd, Zombie zo);
void alienMoveDown(Alien al, Board &bd, Zombie zo);
void alienMoveLeft(Alien al, Board &bd, Zombie zo);
void alienMoveRight(Alien al, Board &bd, Zombie zo);

void zombieSettings(int &zombieCount)
{
    cout << "Zombie Settings" << endl;
    cout << "----------------" << endl;
    cout << "Enter number of zombies => ";
    cin >> zombieCount;
    cout << endl;
}

void pauseClear()
{
    pf::Pause();
    pf::ClearScreen();
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



void displayStat(Alien al ,Zombie zo)
{
    cout << " Alien     : Life " << al.getHp() << ", Atk " << al.getAtk() << endl;
    cout << " Zombie    : Life , Atk , Range " << endl << endl;
}

void showBoard(Board bd, Alien al, Zombie zo) //display board and stats
{
    bd.displayBoard();
    displayStat(al, zo);
}

void alienMoveUp(Alien al,  Board &bd, Zombie zo)
{
    while (1)
    {
        int x = al.getX();
        int y = al.getY();
        // cout << " current facing up x: " << x << " y: " << y << endl; //debugging purpose
        // cout << " next: " << bd.getObj(x, y - 1) << endl;
        if (al.getY() == 1)
        {
            showBoard(bd, al, zo);
            cout << "Alien hits the border." << endl;
            pf::Pause();
            break;
        }
        if (bd.rock(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "rock found" << endl;
            pf::Pause();
            showBoard(bd, al, zo);
            bd.rockObj(x, y - 1);
            pf::Pause();

            break;
        }
        if (bd.healthObj(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "Health found" << endl;
            al.alienGainHealth();
            pf::Pause();

            al.moveUp(bd);
            showBoard(bd, al, zo);
            cout << "Alien gained 20 health!" << endl; 
            pf::Pause();
        }
        if (bd.pod(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "Pod found" << endl;
            pf::Pause();

            al.moveUp(bd);
            showBoard(bd, al, zo);
            pf::Pause();
        }
        if (bd.gridIsEmpty(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "Empty Space found." << endl;
            pf::Pause();

            al.moveUp(bd);
            showBoard(bd, al, zo);
            pf::Pause();
        }
        if (bd.arrowLeft(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveUp(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveLeft(al, bd, zo);
            break;
        }
        if (bd.arrowRight(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveUp(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveRight(al, bd, zo);
            break;
        }
        if (bd.arrowUp(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveUp(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveUp(al, bd, zo);
            break;
        }
        if (bd.arrowDown(x, y - 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveUp(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveDown(al, bd, zo);
            break;
        }
        
        
        
       
 
    }
}

void alienMoveDown(Alien al, Board &bd, Zombie zo)
{

    while (1)
    {
        int x = al.getX();
        int y = al.getY();
        // cout << " current facing down x: " << x << " y: " << y << endl; ///debuggin purpose 
        // cout << " next: " << bd.getObj(x, y + 1) << endl;
        if (al.getY() == bd.getCol())
        {
            showBoard(bd, al, zo);
            cout << "Alien hits the border." << endl;
            pf::Pause();
            break;
        }
        if (bd.rock(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "rock found" << endl;
            pf::Pause();
            showBoard(bd, al, zo);
            bd.rockObj(x, y + 1);
            pf::Pause();
            
            break;
        }
        if (bd.healthObj(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "Health found" << endl;
            al.alienGainHealth();
            pf::Pause();

            al.moveDown(bd);
            showBoard(bd, al, zo);
            cout << "Alien gained 20 health!" << endl; 
            pf::Pause();
            
        }
        if (bd.pod(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "Pod found" << endl;
            pf::Pause();

            al.moveDown(bd);
            showBoard(bd, al, zo);
            pf::Pause();
        }
        if (bd.gridIsEmpty(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "Empty Space found." << endl;
            pf::Pause();

            al.moveDown(bd);
            showBoard(bd, al, zo);
            pf::Pause();
        }
        if (bd.arrowLeft(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveDown(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveLeft(al, bd, zo);
            break;
        }
        if (bd.arrowRight(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveDown(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveRight(al, bd, zo);
            break;
        }
        if (bd.arrowUp(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveDown(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveUp(al, bd, zo);
            break;
        }
        if (bd.arrowDown(x, y + 1))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveDown(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveDown(al, bd, zo);
            break;
        }
        
        
       

    }

}

void alienMoveLeft(Alien al, Board &bd, Zombie zo)
{

    while (1)
    {
        int x = al.getX();
        int y = al.getY();
        // cout << " current facing left x: " << x << " y: " << y << endl; ////debuging purpose
        // cout << " next: " << bd.getObj(x - 1, y) << endl;
        if (al.getX() == 1)
        {
            showBoard(bd, al, zo);
            cout << "Alien hits the border." << endl;
            pf::Pause();
            break;
        }
        if (bd.rock(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "rock found" << endl;
            pf::Pause();
            showBoard(bd, al, zo);
            bd.rockObj(x - 1, y);
            pf::Pause();

            break;
        }
        if (bd.healthObj(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "Health found" << endl;
            al.alienGainHealth();
            pf::Pause();

            al.moveLeft(bd);
            showBoard(bd, al, zo);
            cout << "Alien gained 20 health!" << endl; 
            pf::Pause();
            
        }
        if (bd.pod(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "Pod found" << endl;
            pf::Pause();

            al.moveLeft(bd);
            showBoard(bd, al, zo);
            pf::Pause();
        }
        if (bd.gridIsEmpty(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "Empty Space found." << endl;
            pf::Pause();

            al.moveLeft(bd);
            showBoard(bd, al, zo);
            pf::Pause();
        }
        if (bd.arrowLeft(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveLeft(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveLeft(al, bd ,zo);
            break;
        }
        if (bd.arrowRight(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveLeft(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveRight(al, bd, zo);
            break;
        }
        if (bd.arrowUp(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveLeft(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveUp(al, bd, zo);
            break;
        }
        if (bd.arrowDown(x - 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveLeft(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveDown(al, bd, zo);
            break;
        }
       
        
       
       
    }

}

void alienMoveRight(Alien al, Board &bd, Zombie zo)
{

    while (1)
    {
        int x = al.getX();
        int y = al.getY();
        // cout << " current facing right x: " << x << " y: " << y << endl; ////debuggin purpose
        // cout << " next: " << bd.getObj(x + 1, y) << endl;
        if (al.getX() == bd.getRow())
        {
            showBoard(bd, al, zo);
            cout << "Alien hits the border." << endl;
            pf::Pause();
            break;
        }
        if (bd.rock(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "rock found" << endl;
            pf::Pause();

            showBoard(bd, al, zo);
            bd.rockObj(x + 1, y);
            pf::Pause();
            
            break;
        }
        if (bd.healthObj(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "Health found" << endl;
            al.alienGainHealth();
            pf::Pause();

            al.moveRight(bd);
            showBoard(bd, al, zo);
            cout << "Alien gained 20 health!" << endl; 
            pf::Pause();
            
        }
        if (bd.pod(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "Pod found" << endl;
            pf::Pause();

            al.moveRight(bd);
            showBoard(bd, al, zo); 
            pf::Pause();
        }
        if (bd.gridIsEmpty(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "Empty Space found." << endl;
            pf::Pause();

            al.moveRight(bd);
            showBoard(bd, al, zo); 
            pf::Pause();
        }
        if (bd.arrowLeft(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveRight(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveLeft(al, bd, zo);
            break;
        }
        if (bd.arrowRight(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveRight(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveRight(al, bd, zo);
            break;
        }
        if (bd.arrowUp(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveRight(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveUp(al, bd, zo);
            break;
        }
        if (bd.arrowDown(x + 1, y))
        {
            showBoard(bd, al, zo);
            cout << "arrow found" << endl;
            pf::Pause();

            al.moveRight(bd);
            al.alienGainAtk();
            showBoard(bd, al, zo);
            cout << "Alien gained 20 atk!" << endl;
            pf::Pause();

            alienMoveDown(al, bd, zo);
            break;
        }
   
       
        
    }
}


void alienTurn(Alien al, Board &bd, Zombie zo, int x, int y)
{
    char ans;
    bool quit = false;
    bool turnEnd = false;
    string command;
    do
    {
        showBoard(bd, al, zo);
        cout << "command> ";
        cin >> command;

        if (command == "up")
        {
            alienMoveUp(al, bd, zo);
            turnEnd = true;
        }
        if (command == "down")
        {
            alienMoveDown(al, bd, zo);
            turnEnd = true;
        }
        if (command == "left")
        {
            alienMoveLeft(al, bd, zo);
            turnEnd = true;
        }
        if (command == "right")
        {
            alienMoveRight(al, bd, zo);
            turnEnd = true;
        }
        if (command == "arrow")
        {
            string direction;
            cout << "Enter row, column, and direction: ";
            cin >> x >> y >> direction;
            char arr_ = bd.getObj(x, y);
            char arr[] = {'^', 'v', '<', '>'};

            if (direction == "up")
            {
                bd.setObj(x, y, arr[0]);
                cout << "The arrow " << arr_ << " is changed to " << arr[0] << endl;
                pauseClear();
            }
            if (direction == "down")
            {
                bd.setObj(x, y, arr[1]);
                cout << "The arrow " << arr_ << " is changed to " << arr[1] << endl;
                pauseClear();
            }
            if (direction == "left")
            {
                bd.setObj(x, y, arr[2]);
                cout << "The arrow " << arr_ << " is changed to " << arr[2] << endl;
                pauseClear();
            }
            if (direction == "right")
            {
                bd.setObj(x, y, arr[3]);
                cout << "The arrow " << arr_ << " is changed to " << arr[3] << endl;
                pauseClear();
            }
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
            cout << "7. save (not implemented)  - Save file." << endl;
            cout << "8. load (not implemented)  - Load file." << endl;
            cout << "9. quit (not implemented)  - Quit game." << endl;
            pauseClear();
        }

        if (command == "quit")
        {
            cout << "Are you sure? (y/n) ";
            cin >> ans;

            if (ans == y)
            {
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            }
        }

    } while (!turnEnd);

    if(turnEnd && !quit)
    {
        bd.resetTrail(x, y);
        showBoard(bd, al, zo);
        cout << "Alien's turn ended." << endl;
        pf::Pause();

    }
}

// void zombieTurn(Zombie zo, int rows, int col)
// {
//     char kBoard[rows][col];
//     int maxRow, maxCol;
//     int atk;

//     zo.zombieMove(kBoard, rows, col);

// }

int main()
{
    // srand(1); // testing purpose
    srand(time(NULL));
    int rows = 5;
    int columns = 9;
    int zombieCount = 1;
    int hp ;
    int atk ;
    char ans;
    char arrow[rows][columns];
    bool win = false;
    string direction;

    Alien al = Alien();
    Zombie zo = Zombie();
    Board bd = Board(rows, columns);

  

    // char obj = bd.getObject(1, 1); /////testing purpose

    defaultGame(rows, columns, zombieCount);

    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> ans;
    cout << endl;

    if (ans == 'y' || ans == 'Y')
    {
        pf::ClearScreen();
        bd.boardSettings(rows, columns);
        // cout << "main : row: " << rows  <<  " col : " << columns << endl;
        bd.init_(rows, columns);
        zombieSettings(zombieCount);
        cout << "Settings Updated." << endl;
        pf::Pause();
    }
    else
    {
        bd.init_(rows, columns);
    }

    pf::ClearScreen();
    al.setAlienPos(bd);
    // zo.setZombPos(bd);
    // showBoard(bd, al, zo);


    // showBoard(bd, al);
    // while (!win)
    // {
        alienTurn(al, bd, zo, rows, columns);
    // }
    // alienMoveUp(al, bd);
    

    // int x = 1; ////testing use
    // int y = 3;
    // cout << "is (" << x << ", " << y << " ) a 'p'? ans " << bd.pod(x, y);
    // cout << "is (" << x << ", " << y << " ) arrow left? ans " << bd.arrowLeft(x, y);

    // cout << "is (" << x << "' " << y << ") empty? ans: " << bd.gridIsEmpty(x, y);

}
