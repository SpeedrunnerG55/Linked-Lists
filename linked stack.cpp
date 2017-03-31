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
const short display_Width = 76;
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

// a self imposed limmit on the number of nodes avaluable to create not based on
// memory limitations but just baced of the size of the ID
int TotalIDS = 10000;

//switch to toggle on random node inputs to streamline debugging
bool Debug = false;

/* Prompts user to input information information
   into current node that temp1 is pointing at   */
inline void getInfo(){
  printLine('-');
  if(Debug){
    temp1 ->year = rand() % 8 + 1994;
    temp1 ->month = rand() % 12 + 1;
    temp1 ->day = rand() % 20 + 1;
    switch (rand() % 20) {
      case 0: temp1 ->name = "Bob";    break;
      case 1: temp1 ->name = "Bill";   break;
      case 2: temp1 ->name = "Mike";   break;
      case 3: temp1 ->name = "Joe";    break;
      case 4: temp1 ->name = "Sarah";  break;
      case 5: temp1 ->name = "Sandy";  break;
      case 6: temp1 ->name = "Jill";   break;
      case 7: temp1 ->name = "Roe";    break;
      case 8: temp1 ->name = "Larry";  break;
      case 9: temp1 ->name = "Henery"; break;
      case 10: temp1 ->name = "Tom";    break;
      case 11: temp1 ->name = "Tim";   break;
      case 12: temp1 ->name = "Sam";   break;
      case 13: temp1 ->name = "Suzie";    break;
      case 14: temp1 ->name = "Sue";  break;
      case 15: temp1 ->name = "Elon";  break;
      case 16: temp1 ->name = "Dan";   break;
      case 17: temp1 ->name = "Adam";    break;
      case 18: temp1 ->name = "John";  break;
      case 19: temp1 ->name = "Luke"; break;
    }
    temp1 ->height = rand() % 3 + 4;
  }
  else{
    getInput("Enter name",   temp1 ->name);
    LeftString("Date Of Birth");
    getInput("Enter year",   temp1 ->year);
    getInput("Enter month",  temp1 ->month);
    getInput("Enter day",    temp1 ->day);
    getInput("Enter height", temp1 ->height);
  }
}

/* Displays contents of current node that temp1 is pointing at */
inline void displayInfo(){
  printLine('-');
  string outstring;
  outstring.append(build("Name :",-1,temp1 ->name));
  outstring.append(string(14 -  temp1 ->name.length(),' '));
  outstring.append(build("ID :",temp1 ->ID,""));
  outstring.append(string(6 - to_string(temp1 ->ID).length(),' '));
  outstring.append("D.O.B. ");
  outstring.append(string(2 - to_string(temp1 ->day).length(),' '));
  outstring.append(string(2 - to_string(temp1 ->month).length(),' '));
  outstring.append(build("", temp1 ->month,"/"));
  outstring.append(build("", temp1 ->day,  "/"));
  outstring.append(to_string(temp1 ->year));
  outstring.push_back(' ');
  outstring.append(build("Height :",     temp1 ->height,""));
  outstring.append(string(10 - to_string(temp1 ->height).length(),' '));
  CenterString(outstring);
}

//stack functions
void Display_stack(); //displays whole stack
void add_start_node(); // used in add_To_Middle
void delete_start_node(); //used in purge_stack
inline bool empty(); //returns true of false if stack if empty
void purge_stack(); //for garbage collection and purging
bool Search_stack(int search); // searches lest for node containing ID
inline void createNode(); //sets up new node
inline void displayInfo(); //displays info for current node
void top(); //displays contents of top node

int main() {
  //generate random seed
  srand(time(NULL));

  //input variable
  int Menue;

  //running switch
  bool running = true;

  //Print Title
  printLine('#');
  CenterString("Dynamic stack v1.1");
  LeftString("");

  do{
    printLine('=');
    CenterString("Main Menue");
    printLine('-');
    CenterString(" 1 push      2 pop     [ Redacted ]  ");
    CenterString("[ Redacted ] 5 display  6 check empty");
    CenterString(" 7 purge     8 Top      9 quit       ");
    printLine('-');
    LeftString("what do you want to do");
    LeftString("");
    getInput("",Menue);
    cout << string(100,'\n');
    printLine('#');
    if (cin.fail()){
      getchar();
      cin.clear();
      CenterString("*****************");
      CenterString("* INVALID INPUT *");
      CenterString("* NOT A NUMBER  *");
      CenterString("*****************");
      continue;
    }
    switch (Menue) {
      case 1: add_start_node();    break;
      case 2: delete_start_node(); break;
      case 5: Display_stack();     break;
      case 6:
        if(empty()){
          CenterString("***********************");
          CenterString("*         YES         *");
          CenterString("* The stack is empty! *");
          CenterString("***********************");
        }
        else{
          CenterString("***************************");
          CenterString("*            NO           *");
          CenterString("* The stack is not empty! *");
          CenterString("***************************");
        }
        break;
      case 7: purge_stack();   break;
      case 8: top();           break;
      case 9: running = false; break;
      case 999:
      if(Debug) Debug = false;
      else {
        CenterString("DEBUG ACTIVATED!");
        Debug = true; break;
      }
      default:
      CenterString("*****************");
      CenterString("* INVALID INPUT *");
      CenterString("*****************");
    }
  } while(running);
  LeftString("Collecting garbage...");
  purge_stack(); //garbage collection
  LeftString("Done!");
  printLine('#'); //terminate console window
  return 0;
}

void top(){
  if(!empty()){
    temp1 = start_ptr;//dsiplay first node
    displayInfo();
  }
  else{
    CenterString("**********************");
    CenterString("* The Stack is empty! *");
    CenterString("**********************");
  }
}


/* gets information for ans sets up pointers for new node */
inline void createNode(){
  int ID;
  // Search first because search will move temp 1 and 2
  // to the proper location in stack
  do{
    ID = rand() % TotalIDS;
    LeftString(build("Generated ",ID,""));
  }while(Search_stack(ID) && !empty());
  // Reserve space for new node and fill it with data
  temp1 = new node;
  temp1 ->ID = ID;
  getInfo(); //get all record information with one single function!
  LeftString(build("Assigned ID ", temp1 ->ID ," To Student"));
  temp1 ->nxt = NULL;
}

/* creates a node and if empty, point the start pointer to it,
   else, point it to where the start pointer is pointing to
   then points the start pointer to it (insert at front)      */
void add_start_node(){
  createNode();
  if(empty()){
    start_ptr = temp1;
  }
  else{
    temp1 ->nxt = start_ptr;
    start_ptr = temp1;
  }
}

/* sets temp node to start pointer then makes the start pointer
   point to the next node then deletes node wtih temp           */
void delete_start_node(){
  if(empty()){
    CenterString("***********************");
    CenterString("* The stack is empty! *");
    CenterString("***********************");
  }
  else {
    temp1 = start_ptr;
    start_ptr = start_ptr ->nxt;
    delete temp1;
  }
}

/* if not empty will remove the first element untill it is empty */
void purge_stack(){
  if(empty()){
    CenterString("*******************************");
    CenterString("* The Stack is alreaddy empty! *");
    CenterString("*******************************");
  }
  else{
    CenterString("**********************");
    CenterString("* The Stack is purged *");
    CenterString("**********************");
    do{
      delete_start_node();
    }while(!empty());
  }
}

/* will display each node untill it reaches the end */
void Display_stack(){
  if(empty()){
    CenterString("***********************");
    CenterString("* The stack is empty! *");
    CenterString("***********************");
  }
  else{
    CenterString("Student Stack");
    CenterString("|  Top  |");
    temp1 = start_ptr;
    do {
      // Display details for what temp points to
      displayInfo();
      // Move to next node (if present)
      temp1 = temp1 ->nxt;
    } while (temp1 != NULL);
    printLine('+');
    CenterString("|  Bottom  |");
  }
}

/* returns boolian value */
inline bool empty(){
  return (start_ptr == NULL);
}

/* if not empty traverses the stack
   untill it reaches node with ID handles displaying
   if not in stack message                            */
bool Search_stack(int search){
  if(!empty()){
    temp1 = start_ptr;
    do {
      if (temp1 ->ID == search){
        return true; //student ID is in stack
      }
      // breaks when temp is greater than so search can end sooner
      // because stack is ordered
      if (temp1 ->ID > search){
        break;
      }
      // Move to next node (if present)
      temp1 = temp1 ->nxt;
    } while (temp1 != NULL); //because the return statments are above;
  }
  return false; //student ID is not in stack
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
