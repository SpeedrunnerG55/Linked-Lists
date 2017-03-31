#include <iostream>
#include <fstream>
#include <iomanip>

/*
uses elements from c++11
if std::to_string is not declared in scope
add -std=c++11 as a compiler option in g++ or gcc
*/

using namespace std;

//custom input function
#define getInput(output,input) cout << "| " << output << " >"; cin>>input

//custom graphical functions
const short display_Width = 40;
inline void printLine(char weight);
void titleLine(string str, char weight);
void LeftString(string str);
void CenterString(string str);

//combine string and int and string
inline string build(string sA, float sB, string sC) {
  if(sB != -1) { //none of the values will ever be -1 so use it as a null value
    sA.append(to_string(sB));
    sA.erase(sA.find_last_not_of('0') + 1, string::npos); //remove trailing '0's
    sA.erase(sA.find_last_not_of('.') + 1, string::npos); //remove trailng '.'
  }
  sA.append(sC);
  return sA;
}

/* Struct to contain node information */
struct node;
typedef  node *Ptr;
struct node {
  string name; // Name of up to 20 letters
  int ID; // Student ID (assigned durring insertion)
  //DOB
  int year; // Date of birth
  int month; // Date of birth
  int day; // Date of birth
  float height; // In metres
  Ptr prv; // Pointer to previous node
  Ptr nxt; // Pointer to next node
};

//start pointer
Ptr start_ptr = NULL;
//temp pointers
Ptr temp1;
Ptr temp2;

/* Prompts user to input information information
   into current node that temp1 is pointing at   */
inline void getInfo(){
  printLine('-');
  // Debug: comment this section before release
  temp1 ->year = rand() % 8 + 1994;
  temp1 ->month = rand() % 12 + 1;
  temp1 ->day = rand() % 20 + 1;
  temp1 ->name = "Bob"; //everyone is Bob
  // uncomment this section before release
  // getInput("Enter name",   temp1 ->name);
  // LeftString("Date Of Birth");
  // getInput("Enter year",   temp1 ->year);
  // getInput("Enter month",  temp1 ->month);
  // getInput("Enter day",    temp1 ->day);
  // getInput("Enter height", temp1 ->height);
}

/* Displays contents of current node that temp1 is pointing at */
inline void displayInfo(){
  printLine('-');
  LeftString(build("Name   :",-1,temp1 ->name));
  LeftString(build("ID     :",   temp1 ->ID,""));
  LeftString(      "D.O.B.  ");
  LeftString(build("  Year :",   temp1 ->year,""));
  LeftString(build("  Month:",   temp1 ->month,""));
  LeftString(build("  Day  :",   temp1 ->day,""));
  LeftString(build("Height :",   temp1 ->height,""));
}

//queue functions
void Display_queue(); //displays whole queue
void delete_start_node(); //deque
void add_node_at_end();
inline bool empty(); //returns true of false if queue if empty
void purge_queue(); //for garbage collection and purging
bool Search_queue(int search); //used to create unique ID
inline void createNode(); //sets up new node
inline void displayInfo(); //displays info for current node
void front(); //displays contents of back node

int main() {
  //generate random seed
  srand(time(NULL));

  //input variable
  int Menue;

  //running switch
  bool running = true;

  //Print Title
  printLine('#');
  CenterString("Dynamic que v1.0");
  LeftString("");

  do{
    printLine('=');
    CenterString("Main Menue");
    printLine('-');
    CenterString("  1 enque    2 deque   [ Redacted ]  ");
    CenterString("[ Redacted ] 5 display  6 check empty");
    CenterString("  7 purge    8 back     9 quit       ");
    printLine('-');
    LeftString("what do you want to do");
    LeftString("");
    getInput("",Menue);
    if (cin.fail()){
      getchar();
      cin.clear();
      CenterString("*****************");
      CenterString("* INVALID INPUT *");
      CenterString("*****************");
      continue;
    }
    switch (Menue) {
      case 1: add_node_at_end();   break;
      case 2: delete_start_node(); break;
      case 5: Display_queue();      break;
      case 6:
        if(empty()){
          CenterString("***********************");
          CenterString("*         YES         *");
          CenterString("* The queue is empty! *");
          CenterString("***********************");
        }
        else{
          CenterString("***************************");
          CenterString("*            NO           *");
          CenterString("* The queue is not empty! *");
          CenterString("***************************");
        }
        break;
      case 7: purge_queue();   break;
      case 8: front();          break;
      case 9: running = false; break;
      default:
      CenterString("*****************");
      CenterString("* INVALID INPUT *");
      CenterString("*****************");
    }
  } while(running);
  printLine('*');
  LeftString("Collecting garbage...");
  purge_queue(); //garbage collection
  LeftString("Done!");
  printLine('#'); //terminate console window
  return 0;
}

void front(){
  if(!empty()){
    temp1 = start_ptr;
    displayInfo();
  }
  else{
    CenterString("***********************");
    CenterString("* The queue is empty! *");
    CenterString("***********************");
  }
}

/* gets information for ans sets up pointers for new node */
inline void createNode(){
  printLine('-');
  int ID;
  // Search first because search will move temp 1 and 2
  // to the proper location in queue
  do{
    ID = rand() % 100000;
    LeftString(build("Generated ",ID,""));
  }while(Search_queue(ID) && !empty());
  // Reserve space for new node and fill it with data
  temp1 = new node;
  temp1 ->ID = ID;
  getInfo(); //get all record information with one single function!
  LeftString(build("Assigned ID ", temp1 ->ID ," To Student"));
  temp1 ->nxt = NULL;
}

/* sets temp node to start pointer then makes the start pointer
   point to the next node then deletes node wtih temp           */
void delete_start_node(){
  if(empty()){
    CenterString("***********************");
    CenterString("* The queue is empty! *");
    CenterString("***********************");
  }
  else {
    temp1 = start_ptr;
    displayInfo();
    start_ptr = start_ptr ->nxt;
    delete temp1;
  }
}


/* creates a node then carries it to the end and attaches it */
void add_node_at_end (){
  createNode();
  // Set up link to this node
  if (empty())
  start_ptr = temp1;
  else {
    // carries the temp node to the end and attaches it to the last node
    temp2 = start_ptr;
    while (temp2 ->nxt != NULL) {
      temp2 = temp2 ->nxt; // Move to next link in chain
    }
    temp2->nxt = temp1;
  }
}

/* if not empty will remove the first element untill it is empty */
void purge_queue(){
  if(empty()){
    CenterString("********************************");
    CenterString("* The queue is alreaddy empty! *");
    CenterString("********************************");
  }
  else
    do{
      delete_start_node();
    }while(!empty());
}

/* will display each node untill it reaches the end */
void Display_queue(){
  if(empty()){
    CenterString("***********************");
    CenterString("* The queue is empty! *");
    CenterString("***********************");
  }
  else{
    printLine('=');
    CenterString("Student queue");
    printLine('-');
    CenterString("|  front  |");
    temp1 = start_ptr;
    do {
      // Display details for what temp points to
      displayInfo();
      // Move to next node (if present)
      temp1 = temp1 ->nxt;
    } while (temp1 != NULL);
    printLine('+');
    CenterString("|  back of queue  |");
  }
}

/* returns boolian value */
inline bool empty(){
  return (start_ptr == NULL);
}

/* if not empty traverses the queue
   untill it reaches node with ID handles displaying
   if not in queue message                            */
bool Search_queue(int search){
  if(!empty()){
    temp1 = start_ptr;
    temp2 = NULL;
    do {
      if (temp1 ->ID == search){
        return true; //student ID is in queue
      }
      // breaks when temp is greater than so search can end sooner
      // because queue is ordered
      if (temp1 ->ID > search){
        break;
      }
      // Move to next node (if present)
      temp2 = temp1;
      temp1 = temp1 ->nxt;
    } while (temp1 != NULL); //because the return statments are above;
  }
  CenterString(build("************************", -1 , string(to_string(search).length(),'*')));
  CenterString(build("* ID :" , search, " Is not in queue *"));
  CenterString(build("************************", -1 , string(to_string(search).length(),'*')));
  return false; //student ID is not in queue
}

/* prints a chatacter string across the display */
inline void printLine(char weight){
  cout << "|";
  cout << string(display_Width + 2, weight);
  cout << "|" << endl;
}

/* prints a title then a character string across the display */
void titleLine(string str, char weight){
  cout << "| ";
  int str_length = str.length();
  cout << str << " ";
  cout << string(display_Width - str_length, weight);
  cout << "|" << endl;
}

/* contains a message within the display boundries centered */
void LeftString(string str){
  cout << "| ";
  int str_length = str.length();
  cout << str;
  cout << string(display_Width - (str_length - 1),' ');
  cout << "|" << endl;
}

/* contains a message within the display boundries centered */
void CenterString(string str){
  cout << "| ";
  int str_length = str.length() / 2;
  if(display_Width % 2 != 0)
    cout << " ";
  if(str.length() % 2)
    cout << string(display_Width / 2 - str_length,' ');
  else
    cout << string(display_Width / 2 - str_length + 1,' ');
  cout << str;
  cout << string(display_Width / 2 - str_length,' ');
  cout << "|" << endl;
}
