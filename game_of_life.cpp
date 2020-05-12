// @Author: NikhilP99
// Conway's game of Life

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

void printGrid(vector<vector<bool>> &grid);
void getInitialState(vector<vector<bool>> &grid);
void readManually(vector<vector<bool>> &grid);
void readFromFile(vector<vector<bool>> &grid);
void clearTerminal();
void getNextBoardConfig(vector<vector<bool>> &grid);
void deepCopy(vector<vector<bool>> original,vector<vector<bool>> &copy);
int getNeighbours(vector<vector<bool>> grid, int x, int y);
bool inBounds(int size, int r, int c);

int main(){

  //aesthetics
  //see this for reference https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

  cout << "\033[36m"; //text colour
  cout << "\033[40m"; //background colour


  clearTerminal();
  cout << "Welcome to Conway's Game of Life!" << endl;
  cout << "Go throuth the README.md file to know the rules. Press Ctrl + C to quit anytime. Enjoy!" << endl;
  int size;
  char proceed;
  do{
    cout << "Enter side length of square grid (10-50)" << endl;
    cin >> size;
  }while(size<10 || size>50); //apply check for alphabet

  vector<vector<bool>> grid (size,vector<bool> (size, false));
  printGrid(grid);
  getInitialState(grid);
  cout << "Grid setup completed. To start the simulation press \"y\" or press any other key to exit." << endl;
  cin >> proceed;

  if(proceed!='y') return 0;

  while(true){
    printGrid(grid);
    getNextBoardConfig(grid);
    usleep(150000);
    clearTerminal();
  }
  return 0;
}

void getNextBoardConfig(vector<vector<bool>> &original){
  int n = original.size();
  vector<vector<bool>> copy(n,vector<bool> (n, false));
  deepCopy(original, copy);

  for(int x=0;x<n;x++){
    for(int y=0;y<n;y++){
      int live_neighbours = getNeighbours(copy,x,y);

      if(live_neighbours < 2){
        original[x][y] = false;
      }
      else if(live_neighbours == 3){
        original[x][y] = true;
      }
      else if(live_neighbours > 3){
        original[x][y] = false;
      }
    }
  }
}

int getNeighbours(vector<vector<bool>> grid, int x, int y){
  int live = 0;
  int n = grid.size();

  for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++){
      if(!(i==0 && j==0) && inBounds(n,x+i,y+j)){
        if(grid[x+i][y+j]){
          live++;
        }
      }
    }
  }

  return live;
}

bool inBounds(int size, int r,int c){
  if(r<0 || c<0 || r>=size || c>=size){
    return false;
  }
  return true;
}

void deepCopy(vector<vector<bool>> original,vector<vector<bool>> &copy){
  int n = original.size();
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      copy[i][j] = original[i][j];
    }
  }
}

void clearTerminal(){
  cout << "\033[2J\033[1;1H";
  //system("clear");
}

void getInitialState(vector<vector<bool>> &grid){
  int n = grid.size();
  string method;

  do{
    cout << "Press \"m\" to manually enter coordinates of initially live cells or press \"f\" if you want to read coordinates from a file." << endl;
    cin >> method;
  }while(method!="m" && method!="f");

  if(method == "m"){
    readManually(grid);
  }

  if(method == "f"){
    readFromFile(grid);
  }

}

void readManually(vector<vector<bool>> &grid){
  int size = grid.size();
  int n;
  cout << "Enter number of initially live cells: ";
  cin >> n;
  cout << "Enter valid coordinates(zero based indexing) of initially live cells in the format \"x y\" and press Enter" << endl ;

  for(int i=0;i<n;i++){
    int x,y;
    cout << "Enter the coordinates of cell " << i+1 << ": ";
    cin >> x >> y;
    grid[x][y] = true;
    cout << endl;
    printGrid(grid);
  }
}

void readFromFile(vector<vector<bool>> &grid){
  string filename;
  while(true){
    cout << "Enter name of txt file to read from. Make sure the text file is in same directory as this file." << endl;
    cin >> filename;
    ifstream coordinates(filename);

    if(!coordinates.is_open()){
      cout << "File not found. Please try again." << endl;
      continue;
    }

    string coordinate, x_, y_ ;

    while(getline(coordinates,coordinate)) {
      stringstream s(coordinate);
      getline(s,x_,' ');
      getline(s,y_,' ');

      int x = stoi(x_);
      int y = stoi(y_);

      grid[x][y] = true;
    }
    printGrid(grid);
    break;
  }
}

void printGrid(vector<vector<bool>> &grid){
  int n = grid.size();

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(grid[i][j]){
        cout << " O " ;
      }else{
        cout << " - " ;
      }
    }
    cout << endl ;
  }
}
