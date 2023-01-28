#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

class Board
{
private:
    vector<vector<char>> grid_;
    int row_, column_;

public:
    Board(int row, int column);
    void init_(int row, int column);
    void rockObj(int row, int column);
    void displayBoard() const;
    void boardSettings(int &x, int &y);
    char getObj(int x, int y) const; // just getting the obj so need constant
    void setObj(int x, int y, char ch); //setting the object on board
    void resetTrail(int x, int y);

    int getRow() const;
    int getCol() const;

    bool gridIsEmpty(int x, int y);
    bool isInsideGrid(int x, int y);
    bool isTrail(int x, int y);

    bool arrowUp(int x, int y);
    bool arrowDown(int x, int y);
    bool arrowLeft(int x, int y);
    bool arrowRight(int x, int y);
    bool rock(int x, int y);
    bool pod(int x, int y);
    bool healthObj(int x, int y);
};

class Alien
{
private:
    int row_, col_, attack_ = 0, health_ = 100, pos_;

public:
    Alien();
    int getX() const;
    int getY() const;
    int getHp();
    int getAtk();

    void setAlienPos(Board &board);
    int alienGainHealth();
    int alienGainAtk();
    int alienReceiveDmg(int dmg);

    void moveUp(Board &board);
    void moveDown(Board &board);
    void moveLeft(Board &board);
    void moveRight(Board &board);

    void alienMovingUp(Board &board);
    void alienMovingDown(Board &board);
    void alienMovingLeft(Board &board);
    void alienMovingRight(Board &board);
};

class Zombie
{
private:
    int x_, y_, attack_, health_, pos_, range_, zombieCount;

public:
    Zombie();
    int getZoX() const;
    int getZoY() const;
    int getZoHp();
    int getZoAtk();

    void setZombPos(Board &board);
    int setZombAtk();
    int setZomHp();
    int setZomRange();
    int zombReceiveDmg(int dmg);
    
};

Board::Board(int row, int column)
{
    row_ = row;
    column_ = column;
}

void Board::init_(int x, int y)
{
    row_ = x;
    column_ = y;
    // cout << "row: " << row_  <<  " col : " << column_;

    char objects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' ', ' ', ' '};
    int noOfObjects = 10;

    grid_.resize(column_);

    for (int i = 0; i < column_; ++i)
    {
        grid_[i].resize(row_);
    }

    for (int i = 0; i < column_; ++i)
    {
        for (int j = 0; j < row_; ++j)
        {
            int objNo = rand() % noOfObjects;
            grid_[i][j] = objects[objNo];
        }
    }
}

void Board::rockObj(int x, int y)
{
    char rockObject[] = {'^', 'v', '<', '>', 'h', 'p', ' '};
    int noOfRObj = 7;

    int rObjNo = rand() % noOfRObj;
    char ch = rockObject[rObjNo];

    setObj(x, y, ch);
    
    if (ch == '^' ||
        ch == 'v' ||
        ch == '<' ||
        ch == '>')
        {
            cout << "An arrow has been found below rock." << endl;
        }

    if (ch == 'h')
    {
        cout << "A health pack has been found below rock." << endl;
    }    

    if (ch == 'p')
    {
        cout << "A pod has been found below rock." << endl;
    }

    if (ch == ' ')
    {
         cout << "An empty space has been found below rock." << endl;
    }
}

void Board::displayBoard() const
{
    cout.width(10 + column_);
    cout << ".: Alien vs Zombie :. " << endl;

    for (int i = 0; i < column_; ++i) //display +-+ border
    {

        cout << "  ";
        for (int j = 0; j < row_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << setw(2) << (i + 1); //display side numbers

        for (int j = 0; j < row_; ++j) // display cell | |
        {
            cout << "|" << grid_[i][j];
        }
        cout << "|" << endl;
    }

    cout << "  ";
    for (int j = 0; j < row_; ++j)  //display last line border
    {
        cout << "+-";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < row_; ++j)   //display bottom numbers
    {
        int num = (j + 1) / 10;
        cout << " ";
        if (num == 0)
        {
            cout << " ";
        }
        else
        {
            cout << num;
        }
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < row_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;

    
}


void Board::boardSettings(int &x, int &y)
{
    cout << "Board Settings" << endl;
    cout << "----------------" << endl;
    cout << "Enter rows => ";
    cin >> x;

    cout << "Enter columns => ";
    cin >> y;
    cout << endl;
}

void Board::resetTrail(int x, int y)
{
    row_ = x;
    column_ = y;

    char objects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' ', ' ', ' '};
    int noOfObjects = 10;

    for (int i = 0; i < column_; ++i)
    {
        for (int j = 0; j < row_; ++j)
        {
            if (grid_[i][j] == '.')
            {
                int objNo = rand() % noOfObjects;
                grid_[i][j] = objects[objNo];
            }
        }
    }
}

int Board::getRow() const
{
    return row_;
}

int Board::getCol() const
{
    return column_;
}

void Board::setObj(int x, int y, char ch)
{
    grid_[y - 1][x - 1] = ch;
}

char Board::getObj(int x, int y) const 
{
    return grid_[y - 1][x - 1];
}

bool Board::gridIsEmpty(int x, int y)
{
    return (grid_[y - 1][x - 1] == ' ');
}

bool Board::isInsideGrid(int x, int y)
{
    return (x <= row_) && (x > 0) && (y <= column_) && (y > 0);
}

bool Board::arrowUp(int x, int y)
{
    return (grid_[y - 1][x - 1] == '^');
}

bool Board::arrowDown(int x, int y)
{
    return (grid_[y - 1][x - 1] == 'v');
}

bool Board::arrowLeft(int x, int y)
{
    return (grid_[y - 1][x - 1] == '<');
}

bool Board::arrowRight(int x, int y)
{
    return (grid_[y - 1][x - 1] == '>');
}

bool Board::rock(int x, int y)
{
    return (grid_[y - 1][x - 1] == 'r');
}

bool Board::pod(int x, int y)
{
    return (grid_[y - 1][x - 1] == 'p');
}

bool Board::healthObj(int x, int y)
{
    return (grid_[y - 1][x - 1] == 'h');
}







Alien::Alien()
{
}

void Alien::setAlienPos(Board &board)
{
    row_ = (board.getRow() + 1) / 2; //setting alien at middle position
    col_ = (board.getCol() + 1) / 2;
    pos_ = 'A';
    // cout << "alien row: " << row_ << endl; /////testting purpose
    // cout << "Alien col: " << col_ << endl;;

    board.setObj(row_, col_, pos_);
}


int Alien::getX() const
{
    return row_;
}

int Alien::getY() const
{
    return col_;
}

int Alien::getHp() 
{
    return health_;
}

int Alien::getAtk() 
{
    return attack_;
}


int Alien::alienGainHealth()
{
    health_ = health_ + 20;
    cout << "Alien gained 20 health!" << endl; 
    if (health_ > 100)
    {
    cout << "Health full." << endl;
     health_ = 100;
    }
    return health_;
}

int Alien::alienGainAtk()
{
    attack_ = attack_ + 20;
    return attack_;
}

int Alien::alienReceiveDmg(int dmg)
{
    health_ = health_ - dmg;
    return health_;
}

void Alien::moveUp(Board &board)
{
    row_ = getX();
    col_ = getY();
    pos_ = '.';
    board.setObj(row_, col_, pos_);

    row_ = getX();
    // cout << "getx : " << getX() << endl; //debugging purpose
    // cout << "row: " << row_ << endl;
    col_ = getY() - 1;
    // cout << "gety : " << getY() << endl;
    // cout << "col: " << col_ << endl;
    pos_ = 'A';
    board.setObj(row_, col_, pos_);
}

void Alien::moveDown(Board &board)
{
    row_ = getX();
    col_ = getY();
    pos_ = '.';
    board.setObj(row_, col_, pos_);

    row_ = getX();
    col_ = getY() + 1;
    pos_ = 'A';
    board.setObj(row_, col_, pos_);
}

void Alien::moveLeft(Board &board)
{
    row_ = getX();
    col_ = getY();
    pos_ = '.';
    board.setObj(row_, col_, pos_);

    row_ = getX() - 1;
    col_ = getY();
    pos_ = 'A';
    board.setObj(row_, col_, pos_);
}

void Alien::moveRight(Board &board)
{
    row_ = getX();
    col_ = getY();
    pos_ = '.';
    board.setObj(row_, col_, pos_);

    row_ = getX() + 1;
    col_ = getY();
    pos_ = 'A';
    board.setObj(row_, col_, pos_);
}


Zombie::Zombie()
{
}

void Zombie::setZombPos(Board &board)
{
    x_ = rand() % board.getRow() + 1; //becuz rand starts from 0
    y_ = rand() % board.getCol() + 1;
    pos_ = '1';

    board.setObj(x_, y_, pos_);
}

int Zombie::zombReceiveDmg(int dmg)
{
    health_ = health_ - dmg;
    return health_;
}