#include <iostream>
#include <fstream>
#include <string>

//Libraries for screen clearing and input collection
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

using namespace std;

//declaration of miscellaneous functions
void cls();
bool repeat(string letters, char l);
char collect();
char input();
void unicode();

//Creating the game class
class game;

//Creating the car class
class car {
  private:
    //All the important attributes of each car
    int x;//x coordinate
    int y;//y coordinate
    char letter;//letter as seen on grid
    int length;//length of car
    char dir;//direction of car

  public:
    //2 "constructor" functions used to assign the attributes
    //Done this way as constructor doesn't work with arrays
    inline void construct(char l, int i, int j);
    inline void construct(game b);
    
    //collision detection
    inline bool collision(game b, string dir);
    
    //movemnt functions
    inline car operator+=(game *b);//up and left
    inline car operator-=(game *b);//down and right
};


class game{
  public:
    //game attributes
    const int width = 6;//board dimension
    const int num_of_levels = 5;//number of levels in game
    char board[6][6];//board
    char selected = ' ';//the letter of the selected car
    bool is_running = false;//to see if a level is in play
    bool start = false;//to see if the game has been started
    bool empty = false;//for hiding/showing dots
    char menu_state = 'm';//for which menu user is on
    int level = 1;//level number
    int selector = 1;//reference level in the level select menu
    int moves = 0;//# of moves
    string lvlcomp;//contains level completeion info

    //having all these functions in this class instead of outside, eliminates the need to have a lot of parameters in each as most of the time, the same variables are being used
    void menu();
    void instructions();
    void lvlselect();
    void read();
    void write();
    void reset();
    void show();
    void update();
};

//array that will be used to store all the cars on the boar
//index is 26 as there are 26 letters in the alphabet therefore 26 possible letters to represent the cars, however WASD are resevered for movement, so those letters are never used
//this array allows me to access any car simply based on its letter's position in the alphabet
//useful because there arent always the same amount of cars in each level, and the order they are read from the level file is not alphabetical
//extern used to avoid repeated declaration
extern car cars[26];