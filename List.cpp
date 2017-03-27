#include <iostream>
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
const short size = 35;
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
  // uncomment this section before release
  temp1 ->year = rand() % 8 + 1994;
  temp1 ->month = rand() % 12 + 1;
  temp1 ->day = rand() % 20 + 1;
  temp1 ->name = "Bob";
  // getInput("Enter name",   temp1 ->name);
  // getInput("Enter age",    temp1 ->age);
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

//Main functions (the fnctions the user calls directly)
void Display_List();
// void add_start_node(); //unused
void add_To_Middle();
// void add_node_at_end(); //unused
// void delete_start_node();
void delete_middlenode(int search);
// void delete_end_node(); //unused


//tool kit functions
inline void createNode();
inline void displayInfo();
inline bool empty();
void purge_List(); //for garbage collection and purging
void Modify_Node(int search);
bool Search_List(int search);

int main() {
  //generate random seed
  srand(time(NULL));

  //input variable
  int Menue;

  //running switch
  bool running = true;

  //Print Title
  printLine('#');
  CenterString("Dynamic List v1.1");
  LeftString("");

  do{
    printLine('=');
    CenterString("Main Menue");
    printLine('-');
    CenterString("1 add node     5 display list  ");
    CenterString("2 delete       6 check if empty");
    CenterString("3 modify       7 purge         ");
    CenterString("4 search       9 quit          ");
    printLine('-');
    LeftString("what do you want to do");
    LeftString("");
    getInput("",Menue);
    if (cin.fail()){
      getchar();
      cin.clear();
      printLine('*');
      CenterString("INVALID INPUT");
      continue;
    }
    switch (Menue) {
      case 1: add_To_Middle();   break;
      case 2:
        getInput("ID to delete", Menue);
        delete_middlenode(Menue);
        break;
      case 3:
        getInput("ID to modify",Menue);
        Modify_Node(Menue);
      break;
      case 4:
        getInput("ID to search for",Menue);
        Search_List(Menue);
      case 5: Display_List(); break;
      case 6:
        if(empty()){
          printLine('*');
          CenterString("YES");
          CenterString("The list is empty!");
        }
        else{
          printLine('*');
          CenterString("NO");
          CenterString("The list is not empty!");
        }
        break;
      case 7: purge_List(); break;
      case 9: running = false; break;
      default:
        printLine('*');
        CenterString("INVALID INPUT");
    }
  } while(running);
  printLine('*');
  LeftString("Collecting garbage...");
  purge_List(); //garbage collection
  LeftString("Done!");
  printLine('#'); //terminate console window
  return 0;
}

/* gets information for ans sets up pointers for new node */
inline void createNode(){
  printLine('-');
  int ID;
  do{
    ID = rand() % 10000;
    LeftString(build("Generated ",ID,""));
  }while(Search_List(ID) && !empty());
  // Reserve space for new node and fill it with data
  temp1 = new node;
  temp1 ->ID = ID;
  getInfo(); //get all record information with one single function!
  LeftString(build("Assigned ID ", temp1 ->ID ," To Student"));
  temp1 ->nxt = NULL;
}

/* creates a node and if empty points the start pointer to it
   else it poins it to where the start pointer is pointing to
   then points the start pointer to it                        */
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
    printLine('*');
    CenterString("The list is empty!");
  }
  else {
    temp1 = start_ptr;
    start_ptr = start_ptr ->nxt;
    delete temp1;
  }
}

/* if not empty and has at least 2 nodes adds to the node behind the first */
void add_To_Middle(){
  if(empty()){
    add_start_node();
  }
  else{
    createNode();
    if(temp2 == NULL){
      temp1 ->nxt = start_ptr;
      start_ptr = temp1;
    }
    else{
      temp1 ->nxt = temp2 ->nxt;
      temp2 ->nxt = temp1;
    }
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

/* if not empty deletes firs node if only one node exists deletes the
   first node, else it traverses to the end and deletes the last node */
void delete_end_node(){
  if(empty()){
    printLine('*');
    CenterString("The list is empty!");
  }
  else {
    temp1 = start_ptr;
    if (temp1 ->nxt == NULL){
      delete temp1;
      start_ptr = NULL;
    }
    else{
      while (temp1->nxt != NULL){
        temp2 = temp1;
        temp1 = temp1 ->nxt;
      }
      delete temp1;
      temp2 ->nxt = NULL;
    }
  }
}

/* if not empty will remove the first element untill it is empty */
void purge_List(){
  if(empty()){
    printLine('*');
    CenterString("The list is alreaddy empty!");
  }
  else
    do{
      delete_start_node();
    }while(!empty());
}

/* will display each node untill it reaches the end */
void Display_List(){
  if(empty()){
    printLine('*');
    CenterString("The list is empty!");
  }
  else{
    printLine('=');
    CenterString("Student List");
    temp1 = start_ptr;
    do {
      // Display details for what temp points to
      displayInfo();
      // Move to next node (if present)
      temp1 = temp1 ->nxt;
      if (temp1 == NULL){
        printLine('+');
        CenterString("End of list");
      }
    } while (temp1 != NULL);
  }
}

/* returns boolian value */
inline bool empty(){
  return (start_ptr == NULL);
}

/* deletes the node with the ID */
void delete_middlenode(int search){
  if(empty()){
    printLine('*');
    LeftString("The list is empty!");
  }
  else if(Search_List(search)){
    temp2 ->nxt = temp1 ->nxt;
    delete temp1;
  }
}

/* changes the node with the ID */
void Modify_Node(int search){
  if(empty()){
    printLine('*');
    LeftString("The list is empty!");
  }
  else if(Search_List(search)) //returns true if ID is in list and sets pointers
    getInfo(); //get all record information with one single function!
}

/* if not empty traverses the list
   untill it reaches node with ID handles displaying
   if not in list message                            */
bool Search_List(int search){
  if(empty());
  else{
    temp1 = start_ptr;
    temp2 = NULL;
    do {
      if (temp1 ->ID == search){
        displayInfo(); //display info
        return true; //student ID is in list
      }
      // breaks when temp is greater than so search can end sooner
      // because list is ordered
      if (temp1 ->ID > search){
        break;
      }
      // Move to next node (if present)
      temp2 = temp1;
      temp1 = temp1 ->nxt;
    } while (temp1 != NULL); //because the return statments are above;
  }
  printLine('*');
  LeftString(build("ID :" , search, " Is not in list"));
  return false; //student ID is not in list
}

/* prints a chatacter string across the display */
inline void printLine(char weight){
  cout << "|";
  cout << string(size + 2, weight);
  cout << "|" << endl;
}

/* prints a title then a character string across the display */
void titleLine(string str, char weight){
  cout << "| ";
  int st_len = str.length();
  cout << str << " ";
  cout << string(size - st_len, weight);
  cout << "|" << endl;
}

/* contains a message within the display boundries centered */
void LeftString(string str){
  cout << "| ";
  int st_len = str.length();
  cout << str;
  cout << string(size - (st_len - 1),' ');
  cout << "|" << endl;
}

/* contains a message within the display boundries centered */
void CenterString(string str){
  cout << "| ";
  int st_len = str.length() / 2;
  if(size % 2 != 0)
    cout << " ";
  if(str.length() % 2)
    cout << string(size / 2 - st_len,' ');
  else
    cout << string(size / 2 - st_len + 1,' ');
  cout << str;
  cout << string(size / 2 - st_len,' ');
  cout << "|" << endl;
}
