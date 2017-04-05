const int ROWS = 38;
const int COLS = 42;

int Map[ROWS][COLS] = {
  { 1 , 1 , 1 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 9 , 9 , 9 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 9 , 9 , 9 , 1 , 1 , 9 , 9 , 9 } ,
  { 9 , 9 , 9 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 9 , 9 , 9 , 1 , 1 , 9 , 9 , 9 } ,
  { 9 , 9 , 9 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 9 , 9 , 9 , 1 , 1 , 9 , 9 , 9 } ,
  { 9 , 9 , 9 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 9 , 9 , 9 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 9 , 9 , 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 9 , 9 , 9 } ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ,
}; 
