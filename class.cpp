#include "setup.h"

void car::construct(char l, int i, int j){
  //initializing thse attributes of each car as they can be done as soon as they are read in the file

  //x and y represent the top-left poisition of the car
  //letter is the letter used to display the car
  x = j;
  y = i;
  letter = l;
}

void car::construct(game b){
  //to initialize each car's direction and length
  //this is done seperately to the other attributes as this requires those attributes for it, and can only be done once all the content of the file has been stored into the board  

  //tests if the letter directly underneath is the same, deduces vertical direction
  if (b.board[y+1][x] == letter){
    dir = 'v';
    if (b.board[y+2][x] == letter){//length calculation
      length = 3;
    } else {
      length = 2;
    }
  } 

  //tests if the letter directly right is the same, deduces horizontal direction
  if (b.board[y][x+1] == letter){
    dir = 'h';
    if (b.board[y][x+2] == letter){//length calculation
      length = 3;
    } else {
      length = 2;
    }
  }
}

bool car::collision(game b, string d){
  //Function for collision detection

  //checks above the car only if car is vertical
  if (d == "up" && dir == 'v'){
    if (y == 0){//if car is touching top wall
      return false;
    } else {
      if (b.board[y-1][x] == '.'){//check for empty space
        return true;
      }
    }
  }

  //checks below the car only if car is vertical
  if (d == "down" && dir == 'v'){
    if (y + length == b.width){//if car is touching the bottom wall
      return false;
    } else {
      if (b.board[y+length][x] == '.'){//check for empty space
        //length variable eliminates need to do seperate cases for different car lengths
        return true;
      }
    }
  }

  //checks left of the car only if car is horizontal
  if (d == "left" && dir == 'h'){
    if (x == 0){//if car is touching left wall
      return false;
    } else {
      if (b.board[y][x-1] == '.'){//check for empty space
        return true;
      }
    }
  }

  //checks right of the car only if car is horizontal
  if (d == "right" && dir == 'h'){
      if (x == 4 && y == 2){
        return true;
      } else if (x + length == b.width){//if car is touching right wall
       return false;
      } else {
        if (b.board[y][x+length] == '.'){//check for empty space
         return true;
        }
      }
  }
  
  return false;//if none of the above conditions are satisfied, car is next to another car therefore can not be moved
}

car car::operator-=(game *b){//up and left movement
  //length variable allows for more consice code as seperate cases are not need for different car lengths
  //letters' captial versions are used as the car is still selected
  
  //up
  if (dir == 'v'){
    b->board[y-1][x] = letter-32;//tile above becomes letter
    b->board[y+length-1][x] = '.';//tile below becomes empty
    y -= 1;//updating y position
  }

  //left
  if (dir == 'h'){
    b->board[y][x-1] = letter-32;//left adjacent tile becomes letter
    b->board[y][x+length-1] = '.';//right adjacent tile becomes empty
    x -= 1;//updating x position
  }

  return *this;//returning updated car
}

car car::operator+=(game *b){//down and right movement
  //down
  if (dir == 'v'){
    b->board[y][x] = '.';//current tile become empty
    b->board[y+length][x] = letter-32;//tile below becomes letter
    y += 1;//updating y position
  }

  //right
  if (dir == 'h'){
    b->board[y][x] = '.';//current tile becomes empty
    b->board[y][x+length] = letter-32;//right adjacent tile becomes letter
    x += 1;//updating x position
  }

  return *this;//returning updated car
}