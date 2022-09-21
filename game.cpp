#include "class.cpp"

void cls(){
  //function to clear screen
  ostream& clear_screen();
  system("cls || clear");
}

char collect(){
  //method of collecting input wihtout having to press enter
  //done in a function as is repeatedly called throughout the project
  char ch;
  system("/bin/stty raw");
  ch = getc(stdin);
  system("/bin/stty cooked");
  return ch;
}

void unicode(){
  //unicode art at the end of the game
  cout<<"\n\n\n                      █████████\n  ███████          ███▒▒▒▒▒▒▒▒███\n  █▒▒▒▒▒▒█       ███▒▒▒▒▒▒▒▒▒▒▒▒▒███\n   █▒▒▒▒▒▒█    ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n    █▒▒▒▒▒█   ██▒▒▒▒▒██▒▒▒▒▒▒██▒▒▒▒▒███\n     █▒▒▒█   █▒▒▒▒▒▒████▒▒▒▒████▒▒▒▒▒▒██\n   █████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n   █▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒██\n ██▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒██▒▒▒▒▒▒▒▒▒▒██▒▒▒▒██\n██▒▒▒███████████▒▒▒▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒██\n█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒████████▒▒▒▒▒▒▒██\n██▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n █▒▒▒███████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n ██▒▒▒▒▒▒▒▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█\n  ████████████   █████████████████";
}

void game::instructions(){
  cls();
  //game instructions
  cout<<"RULES:\n• The goal of the game is to get the car denoted by the letter 'r' out of the maze.\n• A letter is printed for every tile in the maze that a car occupies, and dots represent empty space.\n• The row that the 'r' car is in has an extra spot, and once the 'r' car occupies that spot, you will have completed the level.\n\n• To play, select a car by pressing its corresponding key. \n• The letters on the board that represent the car will capitalize to indicate that the car has been selected.\n• Then, use the WS or AD keys to move the car around in its respective direction.\n• Cars can only move in the direction that they are facing.\n• If you want to select another car, simply press its corresponding key and the previous car will deselect itself.\n• If you want to deselect all cars, repress the letter of the car or any other key on the keyboard that doesn't correspond to a car. \n• If you get stuck and want to reset the level at any point, press 1. Or, if you want to go back to the main menu at any point, press 2. \n\n*Now that you have finished reading the rules, press any key on the keyboard to return to the main menu*\n";

  char ch;
  ch = collect();//collecting input

}

void game::read(){
  //function will determine what levels have been compeleted to put the player on the appropriate one
  //done via reading completion.txt

  char ch;
  lvlcomp = "";//clearing the string to prevent it from exceeding 5 characters
  ifstream fin;
  
  //opening the file
  fin.open("completion.txt");
    
  //collecting characters from file and appending them to the string
  while (fin.get(ch)){
    lvlcomp += ch;  
  }

  fin.close();//closing file

  //To determine level
  for (int i = 0; i < num_of_levels; i++){
    if (lvlcomp[i] == '0'){//when the first uncompleted level has been encountered, that is the level that player should be on
      level = i+1;
      break;//breaking as there can be more than 1 uncompleted level
    } else if (i == 4 && lvlcomp[i] == '1'){//if the last character has been reached and still no 0's(all levels complete), restart at level 1
      level = 1;
    }
  }    
}

void game::write(){
  //function to update level completion status
  ofstream fout;
  
  lvlcomp[level-1] = '1';//changing current level status to complete

  fout.open("completion.txt");
  fout<<lvlcomp;//printing to file
  fout.close();
  
}

bool repeat(string letters, char l){
  //checks if a letter in "letters" string repeat
  for (int i = 0; i < size(letters); i++){
    if (letters[i] == l){
      return true;
    }
  }
  return false;
}

void game::reset(){
  ifstream fin;
  char ch, dir;

  //resetting the letters, moves and selected car
  string letters = "";//this string holds the letters of all unique cars. Used to avoid mulitple iterations of the same car
  string file;//file number string
  moves = 0;
  selected = ' ';

  //to determine which variable to use for level selection
  //if in level select menu, use the selector as that is the level that will be shown on screen
  //if level has been chosen, using that level
  if (!start){
    file = to_string(selector);
  } else {
    file = to_string(level);
  }

  //opening the corresponding level file from the levels folder
  fin.open("levels/" + file + ".txt");

  if (!fin.is_open()){
    is_running = false;//just in case file does not open
  } else {
    if (start){//if not on the level select menu
      is_running = true;
    }
      
    int i = 0, j = 0;
    while (fin.get(ch)){
      if (ch != '\n'){
        //adding each character to the board that arent '\n'
        board[i][j] = ch;
        
        //only if not in the level select menu
        //if the character is not empty space, check if the letter has already been added to the "letters" string
        if (start){
          if (ch != '.'){
            if (!repeat(letters, ch)){
              letters += ch; //adding the letter to letters

              int n = ((int) ch) - 96 - 1;// finding index in cars[] to add the car to. Cars are in the item corresponding to the letter's position in the alphabet  
              
              cars[n].construct(ch, i, j);//calling first constructor
            }
          }
        }
        j++;
      } else {
        //Increment at the end of each line, works like nested loops for 2 dimensions
        i++;
        j = 0;
      } 
    }
    fin.close();//closing file

    //Calling the second constructor for each car if not in the level select menu
    if (start){
      for (int i = 0; i < size(letters); i++){
        int n = (((int) (letters)[i]) - 96 - 1);//same index calculation logic as above
        cars[n].construct(*this);
      }
    }
  }
}

void game::show(){
  //display level number if in a level
  if (is_running){
    cls();
    cout<<"LEVEL "<<level;
  }

  //printing the board
  cout<<"\n\n---------------";//top bar
  for (int i = 0; i < width; i++){
    cout<<endl<<"| ";//left bar
    for (int j = 0; j < width; j++){
      if (board[i][j] == '.'){
        if (!empty){//if dots are to be shown
          cout<<"· ";//Centered dots look nicer than periods on the screen :)
        } else {
          cout<<"  ";//if dots are not shown, print space insead
        } 
      } else {
        cout<<board[i][j]<<" ";
      }
      //right bars
      if (j == width - 1){
        if (i == 1){
          cout<<"L";
        } else if (i == 3){
          cout<<"Γ";
        } else if (i != 2){
          cout<<"|";
        }
      }

      //printing the extra tile and checking for win
      //if the extra tile in the third row from the top is occupied, the level has been complete
      if (i == 2 && j == width-1){
        if (board[i][j-1] != 'R' && board[i][j] == 'R'){
          cout<<"R";// tile is occupied
          is_running = false;//update that level iscomplete
        } else {//tile is not occupied
          if (!empty){//if dots are to be shown
            cout<<"·";
          } else {
            cout<<" ";//if dots are not to be shown
          }
          if (start){
            cout<<"  -->";//arrow when game is in progress, shows objective of game
          } 
        }
        
        //to show if level has been completed, only in the level select menu
        if (menu_state == 'l' && !start){
          if (lvlcomp[selector-1] == '1'){
            cout<<"\t\tCompleted ✔";
          }
        }  
      }
    }
  }
  cout<<"\n---------------\n";//bottom bar

  if (start){
    cout<<"Moves: "<<moves;//Moves counter
    cout<<"\n\nEnter the letter of a vehicle to select it, then press WASD to move.\nPress 1 to reset the level, 2 for main menu, or 5 to hide the dots.\nRepress the letter of the car or any other key to deselect:\n\n";//input instructions
  }
}

void game::lvlselect(){
  //level select menu
  string play;

  //based on the current level determined by the read function, set the status of a level to be playable or locked depending on if the previous level has been completed
  //anything before the current level is playable(when all levels not completed)
  //if previous level is completed, then playable (when all levels have been completed)
  if (selector <= level || lvlcomp[selector-2] == '1'){
    play = " Play";
  } else {
    play = "Locked";
  }

  cls();
  cout<<"LEVEL PREVIEW";//label text

  //for showing level grid
  reset();
  show();

  //to display the level that is currently being previewed
  cout<<"\n\t<  0"<<selector<<"  >";//level #
  cout<<"\n\t "<<play;//playability
  cout<<"\n\nUse AD to swap between levels and Space to play.\nPress 2 to go back to main menu.\n";//instructions
  
  //corresponding action depending on input
  switch (collect()){
    case 'd':
      if (selector < num_of_levels){
        selector++;//next level
      } else {
        selector = 1;//going back to first level if reached end
      }
    break;

    case 'a':
      if (selector > 1){
        selector--;//previous level
      } else {
        selector = num_of_levels;//skipping to lasy level if reached beginning
      }
    break;

    case '2':
      menu_state = 'm';//going back to main menu
    break;

    case '5': //grid clearing is still togglable in menu
      empty = !empty;
    break;

    case ' ':
      //checking if player is allowed to play the level when they press space, if so, starting level
      if (play == " Play"){
        start = true;
        level = selector;//the level that will be played, is the current selector level
      }
    break;
  }
}

void game::menu(){
  cls();

  //menu navigation text
  cout<<"Welcome to RUSH HOUR!";
  cout<<"\n\nMain Menu\n----------";
  cout<<"\n\nPress 1 to play\nPress 2 for instructions.\nPress 3 for level selection.\n\n";

  //executing corresponding action
  switch (collect()){
    case '1': //play
      start = true;
      read();
    break;

    case '2': //instructions menu
      instructions();
    break;

    case '3': //level select menu
      menu_state = 'l';
      read();
      selector = level;
    break;
  }
}

void game::update(){
  bool chosen = false;//used when checking for if a car is selected
  int n = (int) selected - 96 - 1;

  //for cases w,a,s,d: check if a car is selected, the check for potential collision is the respective direction, move the car, add a move to the total
  char ch = collect();
  switch(ch){
    case 'w': //up movement
      if (selected != ' '){
        if (cars[n].collision(*this, "up")){
          cars[n] -= this;
          moves++;
        }
        
      }
    break;

    case 'a': //left movement
      if (selected != ' '){
        if (cars[n].collision(*this, "left")){
          cars[n] -= this;
          moves++;
        }
      }
    break;

    case 's': //down movement
      if (selected != ' '){
        if (cars[n].collision(*this, "down")){
          cars[n] += this;
          moves++;
        }
      }
    break;

    case 'd': //right movement
      if (selected != ' '){
        if (cars[n].collision(*this, "right")){
          cars[n] += this;
          moves++;
        }
      }
    break;

    case '1': //level reset
      //call the reset function
      reset();
    break;
      
    case '2': //return to main menu
      //setting main menu conditions true;
      start = false;
      menu_state = 'm';
    break;
    
    case '5': //hide or show dots
      //toggling empty state
      empty = !empty;
      break;

    default:
      //to check if a car is selected, and if so, capitilize it
      for (int i = 0; i < width; i++){
        for (int j = 0; j < width; j++){
          if (board[i][j] >= 'a' && board[i][j] <= 'z'){
            if (board[i][j] == ch){//if car is not selected and the input matches its letter, capitalize it and assigning it to the selected, set "chosen" to true to prevent multiple selections
              board[i][j] -= 32;
              selected = ch;
              chosen = true;
            } 
          } else if (board[i][j] >= 'A' && board[i][j] <= 'Z'){//if a car is currently selected then is unselected, return the car to lowercase
            board[i][j] += 32;
          }
          if (i == width - 1 && j == width - 1 && !chosen && ch != '5'){//if the very last position on the board has been reached, no car has been chosen and user did not input '5', make the "selected" variable blank again. 5 is included as a condition to prevent deselecting a car when toggling grid appearance
            selected = ' ';
          }
        }
      }
    break;
  }
}