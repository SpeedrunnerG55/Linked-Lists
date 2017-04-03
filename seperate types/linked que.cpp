#include <iostream>

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
void printLine(char weight);
void titleLine(string str, char weight);
void LeftString(string str);
void CenterString(string str);

//combine string and int and string
string build(string sA, int sB, string sC) {
  if(sB != -1) { //none of the values will ever be -1 so use it as a null value
    sA.append(to_string(sB));
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
  int feet; // feet
  int inches; // inches
  Ptr nxt; // Pointer to next node
};

//start pointer
Ptr start_ptr = NULL;
//temp pointers
Ptr temp1;
Ptr temp2;

// a self imposed limmit on the number of nodes avaluable to create not based on
// memory limitations but just baced of the size of the ID
int TotalIDS = 10000;

//switch to toggle on random node inputs to streamline debugging
bool Debug = false;

/* Prompts user to input information information
   into current node that temp1 is pointing at   */
void getInfo(){
  printLine('-');
  if(Debug){
    temp1 ->year = rand() % 10 + 1990;
    temp1 ->month = rand() % 12 + 1;
    temp1 ->day = rand() % 20 + 1;
    switch (rand() % 2) {
      case 0: temp1 ->name = "LongName"; break;
      case 1: temp1 ->name = "ShrtNm";  break;
    }
    temp1 ->feet = rand() % 2 + 5;
    temp1 ->inches = rand() % 12;
  }
  else{
    getInput("Enter name",   temp1 ->name);
    LeftString("Date Of Birth");
    getInput("Enter year",   temp1 ->year);
    getInput("Enter month",  temp1 ->month);
    getInput("Enter day",    temp1 ->day);
    LeftString("Height");
    getInput("Feet",   temp1 ->feet);
    getInput("Inches", temp1 ->inches);
  }
}

/* Displays contents of current node that temp1 is pointing at */
void displayInfo(){
  printLine('-');
  //initialise output
  string outString;

  //build output
  outString.append("ID : ");
  outString.append(to_string(temp1 ->ID));
  outString.append(string(5 - to_string(temp1 ->ID).length(),' '));
  outString.append("Name : "); outString.append(temp1 ->name);
  outString.append(string(14 -  temp1 ->name.length(),' '));
  outString.append("D.O.B. : ");
  outString.append(build(to_string(temp1 ->month),-1,"/"));
  outString.append(build(to_string(temp1 ->day  ),-1,"/"));
  outString.append(build(to_string(temp1 ->year ),-1," "));
  outString.push_back(' '); //this should work for the next 8 thousand years
  outString.append(string(2 - to_string(temp1 ->month).length(),' '));
  outString.append(string(2 - to_string(temp1 ->day  ).length(),' '));
  outString.append("Height : ");
  outString.append(to_string(temp1 ->feet));
  outString.append("F,");
  outString.append(to_string(temp1 ->inches));
  outString.append("in");
  outString.append(string(2 - to_string(temp1 ->inches).length(),' '));

  //display output
  CenterString(outString);
}

//queue functions
void Display_queue(); //displays whole queue
void delete_start_node(); //deque
void add_node_at_end();
bool empty(); //returns true of false if queue if empty
void purge_queue(); //for garbage collection and purging
bool Search_queue(int search); //used to create unique ID
void createNode(); //sets up new node
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
    CenterString("  7 purge    8 front    9 quit       ");
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
      CenterString("*****************");
      continue;
    }
    switch (Menue) {
      case 1: add_node_at_end();   break;
      case 2: delete_start_node(); break;
      case 5: Display_queue();     break;
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
  purge_queue(); //garbage collection
  LeftString("Done! safe to close");
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
void createNode(){
  int ID;
  // Search first because search will move temp 1 and 2
  // to the proper location in queue
  do{
    ID = rand() % TotalIDS;
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

void purge_queue(){
  if(empty()){
    CenterString("********************************");
    CenterString("* The queue is alreaddy empty! *");
    CenterString("********************************");
  }
  else{
    CenterString("***********************");
    CenterString("* The queue is purged *");
    CenterString("***********************");
    do{
      delete_start_node();
    }while(!empty());
  }
}

/* will display each node untill it reaches the end */
void Display_queue(){
  if(empty()){
    CenterString("***********************");
    CenterString("* The queue is empty! *");
    CenterString("***********************");
  }
  else{
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
bool empty(){
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
  return false; //student ID is not in queue
}

/* prints a chatacter string across the display */
void printLine(char weight){
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
