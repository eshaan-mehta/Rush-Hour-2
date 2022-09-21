#include "class.cpp"

car cars[26];//redeclaring global cars array 

int main() {
game b;//creating game object

//game loop
while (true){
  //main menu
  if (!b.start){
    b.is_running = false;
    //depending on the menu state, execute the corresponding function
    if (b.menu_state == 'm'){
      b.menu();//main menu
    }
    if (b.menu_state == 'l'){
      b.lvlselect();//level select menu
    } 
  }
  
  //level generation
  if (!b.is_running && b.start){
    cls();
    b.reset();
    b.show();
  }

  //when level in play 
  if (b.is_running && b.start){
    b.update();
    b.show();
  }

  //in between levels and after last level
  if (!b.is_running && b.start){
    char ch;
    cls();
    
    //to complete level if it and not all other levels are complete
    if (b.lvlcomp[b.level-1] == '0'){
      b.write();
    }
    
    //between level menu
    if (b.level < b.num_of_levels){
      cout<<"Level complete!\n\nPress 1 to replay that level.\nPress 2 to go back to the main menu.\nPress any other key to play the next level.\n\n";
    
      ch = collect();

      if (ch == '2'){ //if you want to go back to the main menu 
        b.start = false;
        b.menu_state = 'm';
      } else if (ch != '1'){
        b.level++;
      } 
    } else {
      cls();

      //Message for once all levels have been completed
      cout<<"Congratulations! You completed all the levels.";

      //unicode art
      unicode();  
      
      cout<<"\n\n\nPress 1 to return to menu, anything else to exit";

      
      if (collect() == '1'){//return to main menu
        b.start = false;
        b.menu_state = 'm';
      } else {//exiting from loop
        break;
      } 
    }
  } 
}

//final screen before program ends
cls();
cout<<"Thanks for playing!";

return 0;
} 