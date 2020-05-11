// @Author: NikhilP99
// Conway's game of Life

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void printGrid(vector<vector<bool>> &grid);
void getInitialState(vector<vector<bool>> &grid);
void readManually(vector<vector<bool>> &grid);
void readFromFile(vector<vector<bool>> &grid);

int main(){
  cout << "Welcome to Conway's game of life!" << endl;
  int size;
  char proceed;
  do{
    cout << "Enter side length of square grid (10-50)" << endl;
    cin >> size;
  }while(size<10 || size>50); //apply check for alphabet

  vector<vector<bool>> grid (size,vector<bool> (size, false));
  printGrid(grid);
  getInitialState(grid);
  printGrid(grid);
  cout << "Grid setup completed. To start the simulation press \"y\" or press any key to exit." << endl;
  cin >> proceed;

  if(proceed!='y') return 0;




  return 0;
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
