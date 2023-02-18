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
    void fill_(int row, int column);
    void rockObj(int row, int column);
    void displayBoard() const;
    char getObj(int x, int y) const; 
    void setObj(int x, int y, char ch);
    void resetTrail(int x, int y);

    int getRow() const;
    int getCol() const;

    void setRow(int x);
    void setCol(int y);

    bool gridIsEmpty(int x, int y);
    bool isInsideGrid(int x, int y);
    bool arrowUp(int x, int y);
    bool arrowDown(int x, int y);
    bool arrowLeft(int x, int y);
    bool arrowRight(int x, int y);
    bool rock(int x, int y);
    bool pod(int x, int y);
    bool healthObj(int x, int y);
    bool alienPresent(int x, int y);
    bool zombiePresent(int x, int y);
  
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
    int alienAtkReset();

    void setAlienX(int x);
    void setAlienY(int y);
    void setAlienHp(int hp);
    void setAlienAtk(int atk);

    void moveUp(Board &board);
    void moveDown(Board &board);
    void moveLeft(Board &board);
    void moveRight(Board &board);

    bool alienDefeat();
};

class Zombie
{
private:
    int x_, y_,  pos_, zombieCount, hp_, atk_, range_;


public:
    Zombie();

    void setZombPos(Board &board, int &n, int i);
    void createZombie(Board bd, int i);
    int getZombieRow() const;
    int getZombieCol() const;
    int getZombieHp();
    int getZombieAtk();
    int getZombieRange() const;
    char getZombieChar() const;

    void setZombieX(int X);
    void setZombieY(int Y);
    void setZombieHp(int Hp);
    void setZombieAtk(int Atk);
    void setZombieRange(int Rn);
    void setZombieChar(char zoChar);

    void zombieMoveUp(Board &board, int i);
    void zombieMoveDown(Board &board, int i);
    void zombieMoveLeft(Board &board, int i);
    void zombieMoveRight(Board &board, int i);
    int zombieReceiveDmg(int dmg);

    void zombieValidMove(Board &bd, int i);
    
    bool zombieDefeat();
   
    
};


Board::Board(int row, int column)
{
    row_ = row;
    column_ = column;
}

void Board::fill_(int x, int y) //filling in the game objects
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

void Board::rockObj(int x, int y) //will return random objects after alien encounters a rock
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
    cout.width(14 + row_); // keeping the title as middle as possible
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



void Board::resetTrail(int x, int y) // fill back the trail walked by alien
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

void Board::setRow(int x)
{
    row_ = x;
}

void Board::setCol(int y)
{
    column_ = y;
}

void Board::setObj(int x, int y, char ch)  //used for setting objects
{
    grid_[y - 1][x - 1] = ch;
}

char Board::getObj(int x, int y) const  //will return object on indicated x, y
{
    return grid_[y - 1][x - 1];
}

bool Board::gridIsEmpty(int x, int y) //check if the grid is empty
{
    return (grid_[y - 1][x - 1] == ' ');
}

bool Board::isInsideGrid(int x, int y) //check if the coordinate is within the board
{
    return (x <= row_) && (x > 0) && (y <= column_) && (y > 0);
}
 
bool Board::arrowUp(int x, int y) //check for ^
{
    return (grid_[y - 1][x - 1] == '^');
}

bool Board::arrowDown(int x, int y) // check for v
{
    return (grid_[y - 1][x - 1] == 'v');
}

bool Board::arrowLeft(int x, int y) // check for <
{
    return (grid_[y - 1][x - 1] == '<');
}

bool Board::arrowRight(int x, int y) // check for >
{
    return (grid_[y - 1][x - 1] == '>');
}

bool Board::rock(int x, int y) // check for r
{
    return (grid_[y - 1][x - 1] == 'r');
}

bool Board::pod(int x, int y) // check for p
{
    return (grid_[y - 1][x - 1] == 'p');
}

bool Board::healthObj(int x, int y) //check for h
{
    return (grid_[y - 1][x - 1] == 'h');
}

bool Board::alienPresent(int x, int y) // check for alien
{
    return (grid_[y - 1][x - 1] == 'A');
}

bool Board::zombiePresent(int x, int y) // checking for zombie
{
    return  (grid_[y - 1][x - 1] == '1') ||
            (grid_[y - 1][x - 1] == '2') ||
            (grid_[y - 1][x - 1] == '3') ||
            (grid_[y - 1][x - 1] == '4') ||
            (grid_[y - 1][x - 1] == '5') ||
            (grid_[y - 1][x - 1] == '6') ||
            (grid_[y - 1][x - 1] == '7') ||
            (grid_[y - 1][x - 1] == '8') ||
            (grid_[y - 1][x - 1] == '9');
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
    if (health_ < 0)
    {
        health_ = 0;
    }
    return health_;
}

int Alien::getAtk() 
{
    return attack_;
}


int Alien::alienGainHealth() //when alien gain haealth
{
    health_ = health_ + 20;
    cout << "Alien gains 20 health!" << endl;
    if (health_ > 100) //hp will not go over 100
    {
        cout << "Health is full." << endl;
        health_ = 100;
    }
    return health_;
}

int Alien::alienGainAtk() //when alien gain attack
{
    attack_ = attack_ + 20;
    return attack_;
}

int Alien::alienReceiveDmg(int dmg) //when alien receive dmg
{
    health_ = health_ - dmg;
    return health_;
}

int Alien::alienAtkReset() // reset the atk at the end of alien's turn
{
    attack_ = 0;
    return attack_;
}

void Alien::setAlienX(int x)
{
    row_ = x;
}

void Alien::setAlienY(int y)
{
    col_ = y;
}

void Alien::setAlienHp(int hp)
{
    health_ = hp;
}

void Alien::setAlienAtk(int atk)
{
    attack_ = atk;
}


void Alien::moveUp(Board &board) //move up function
{
    row_ = getX();
    col_ = getY();
    pos_ = '.'; // leaves trail behind
    board.setObj(row_, col_, pos_); 

    row_ = getX();
    col_ = getY() - 1;
    pos_ = 'A';
    board.setObj(row_, col_, pos_);
}

void Alien::moveDown(Board &board) //move down function
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

void Alien::moveLeft(Board &board) //move left function
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

void Alien::moveRight(Board &board) //move right function
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

bool Alien::alienDefeat() //check if alien if defeated
{
    return (getHp() == 0);
}



Zombie::Zombie()
{

}


void Zombie::setZombPos(Board &board, int &n, int i) //set zombie according to the zombiecount passed in
{
    char zomb[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    x_ = rand() % board.getRow() + 1; //becuz rand starts from 0
    y_ = rand() % board.getCol() + 1;
    pos_ = zomb[i];
    board.setObj(x_, y_, pos_);
}


void Zombie::createZombie(Board bd, int i) //set the zombie stats
{
    int rn;
    if ((bd.getRow()/2) > (bd.getCol()/2)) //for the range no larger than either row/2 or column/2
    {
        rn = bd.getCol()/2;
    }
    else if ((bd.getCol()/2) > (bd.getRow()/2))
    {
        rn = bd.getRow()/2;
    }
    else if ((bd.getCol()/2) == (bd.getRow()/2)) //if equal then take either also same
    {
        rn = bd.getRow()/2;
    }

    hp_ = (rand() % 5 + 2) * 50;
    atk_ = (rand() % 9 + 1) * 10;
    range_ = rand() % rn + 2; // int/int will get smaller num

}    

int Zombie::getZombieRow() const
{
    return x_;
}

int Zombie::getZombieCol() const
{
    return y_;
}

int Zombie::getZombieHp() 
{
    if (hp_ < 0) //hp will not go below than 0
    {
        hp_ = 0;
    }
    return hp_;
}

int Zombie::getZombieAtk() 
{
    return atk_;
}

int Zombie::getZombieRange() const
{
    return range_;
}

char Zombie::getZombieChar() const
{
    return pos_;
}

void Zombie::setZombieX(int X)
{
    x_ = X;
}

void Zombie::setZombieY(int Y)
{
    y_ = Y;
}

void Zombie::setZombieHp(int Hp)
{
    hp_ = Hp;
}

void Zombie::setZombieAtk(int Atk)
{
    atk_ = Atk;
}

void Zombie::setZombieRange(int Rn)
{
    range_ = Rn;
}

void Zombie::setZombieChar(char zoChar)
{
    pos_ = zoChar;
}

void Zombie::zombieMoveUp(Board &bd, int i) //moving up pass in i to identify which zombie
{
    x_ = getZombieRow();
    y_ = getZombieCol();
    char objects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' ', ' ', ' '}; 
    int noOfObjects = 10;
    int objNo = rand()% noOfObjects; //this will return random objects after the zombie moves.
    pos_ = objects[objNo];
    bd.setObj(x_, y_ , pos_);

    char zomb[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    x_ = getZombieRow();
    y_ = getZombieCol() - 1;
    pos_ = zomb[i];
    bd.setObj(x_, y_ , pos_);

}

void Zombie::zombieMoveDown(Board &bd, int i) //moving down
{
    x_ = getZombieRow();
    y_ = getZombieCol();
    char objects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' ', ' ', ' '};
    int noOfObjects = 10;
    int objNo = rand()% noOfObjects;
    pos_ = objects[objNo];
    bd.setObj(x_, y_ , pos_);

    char zomb[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    x_ = getZombieRow();
    y_ = getZombieCol() + 1;
    pos_ = zomb[i];
    bd.setObj(x_, y_ , pos_);

}

void Zombie::zombieMoveLeft(Board &bd, int i) //moving left
{
    x_ = getZombieRow();
    y_ = getZombieCol();
    char objects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' ', ' ', ' '};
    int noOfObjects = 10;
    int objNo = rand()% noOfObjects;
    pos_ = objects[objNo];
    bd.setObj(x_, y_ , pos_);

    char zomb[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    x_ = getZombieRow() - 1;
    y_ = getZombieCol();
    pos_ = zomb[i];
    bd.setObj(x_, y_ , pos_);

}

void Zombie::zombieMoveRight(Board &bd, int i) //moving right
{
    x_ = getZombieRow();
    y_ = getZombieCol();
    char objects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' ', ' ', ' '};
    int noOfObjects = 10;
    int objNo = rand()% noOfObjects;
    pos_ = objects[objNo];
    bd.setObj(x_, y_ , pos_);

    char zomb[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    x_ = getZombieRow() + 1;
    y_ = getZombieCol();
    pos_ = zomb[i];
    bd.setObj(x_, y_ , pos_);

}


void Zombie::zombieValidMove(Board &bd, int i)
{    
    vector<int> num;                 
    x_ = getZombieRow(); //0 for up, 1 for right, 2 for down, 3 for left
    y_ = getZombieCol();

    if (bd.isInsideGrid(x_, y_ - 1)) //check if its inside grid then proceed to 2nd checking process
    {
        if ((!bd.alienPresent(x_, y_ - 1)) && (!bd.zombiePresent(x_, y_ - 1))) // check if zombie/alien present in the desired next move
        {
            num.push_back(0); // going up
        }
    }

    if (bd.isInsideGrid(x_ + 1, y_))
    {
        if ((!bd.alienPresent(x_ + 1, y_)) && (!bd.zombiePresent(x_ + 1, y_)))
        {
            num.push_back(1); // going right
        }
    }

    if (bd.isInsideGrid(x_ , y_ + 1))
    {
        if ((!bd.alienPresent(x_, y_ + 1)) && (!bd.zombiePresent(x_, y_ + 1)))
        {
            num.push_back(2); // going down
        }
    }

    if (bd.isInsideGrid(x_ - 1, y_))
    {
        if ((!bd.alienPresent(x_ - 1, y_ )) && (!bd.zombiePresent(x_ - 1, y_ )))
        {
            num.push_back(3); // going left
        }
    }

    int noOfValids = num.size();
    int move = rand()% noOfValids;

    if (num[move] == 0)
    {
        zombieMoveUp(bd, i);
        cout << "Zombie" << i + 1 << " moves up." << endl;
    }
    if (num[move] == 1)
    {
        zombieMoveRight(bd, i);
        cout << "Zombie" << i + 1 << " moves right." << endl;
    }
    if (num[move] == 2)
    {
        zombieMoveDown(bd, i);
        cout << "Zombie" << i + 1 << " moves down." << endl;
    }
    if (num[move] == 3)
    {
        zombieMoveLeft(bd, i);
        cout << "Zombie" << i + 1 << " moves left." << endl;
    }
}


int Zombie::zombieReceiveDmg(int dmg) //zombie receives dmg
{
    hp_ = hp_ - dmg;
    return hp_;
}

bool Zombie::zombieDefeat() //check if zombie is defeated
{
    return (getZombieHp() == 0);
}
