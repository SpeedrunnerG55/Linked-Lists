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
const short size = 76;
inline void printLine(char weight);
void titleLine(string str, char weight);
void Container(string str);

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

// keep all record specific functions and
// details in one spot to maintain simplisity
// and maintinability
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

inline void displayInfo(){
  printLine('-');
  Container(build("Name   :",-1,temp1 ->name));
  Container(build("ID     :",   temp1 ->ID,""));
  Container(      "D.O.B.  ");
  Container(build("  Year :",   temp1 ->year,""));
  Container(build("  Month:",   temp1 ->month,""));
  Container(build("  Day  :",   temp1 ->day,""));
  Container(build("Height :",   temp1 ->height,""));
}

//Main functions (the fnctions the user calls directly)
void Display_List();
void add_start_node();
void add_To_Middle();
void add_node_at_end();

//tool kit functions
inline void createNode();
inline void displayInfo();
inline bool empty();
void delete_start_node();
void delete_middlenode(int search);
void delete_end_node();
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

  do{
    printLine('#');
    Container("Dynamic List v1.1");
    Container("");
    titleLine("Main Menue", '=');
    Container("");
    Container("Type 1 to add node   type 5 to display list");
    Container("Type 2 to delete     type 6 to check if empty");
    Container("Type 3 to modify     type 7 to purge");
    Container("type 4 to search     type 9 to end program");
    printLine('-');
    Container("what do you want to do");
    Container("");
    getInput("",Menue);
    if (cin.fail()){
      printLine('*');
      getchar();
      Container("INVALID INPUT");
      cin.clear();
      continue;
    }
    switch (Menue) {
      case 1:
      Container("1 To front");
      Container("2 To middle");
      Container("3 To back");
      Container("");
      getInput("Add", Menue);
      switch (Menue) {
        case 1: add_start_node();  break;
        case 2: add_To_Middle();   break;
        case 3: add_node_at_end(); break;
        default:
        printLine('*');
        Container("INVALID INPUT");
      }
      break;
      case 2:
        Container("1 From front");
        Container("2 From middle");
        Container("3 From back");
        Container("");
        getInput("Delete", Menue);
        switch (Menue) {
          case 1: delete_start_node(); break;
          case 2:
            getInput("ID to delete", Menue);
            delete_middlenode(Menue);
          break;
          case 3: delete_end_node(); break;
          default:
            printLine('*');
            Container("INVALID INPUT");
        }
        break;
      case 3:
        getInput("ID to modify",Menue);
        Modify_Node(Menue);
      break;
      case 4:
        getInput("ID search for",Menue);
        Search_List(Menue);
      case 5: Display_List(); break;
      case 6:
        if(empty()){
          printLine('*');
          Container("YES");
          Container("The list is empty!");
        }
        else{
          printLine('*');
          Container("NO");
          Container("The list is not empty!");
        }
        break;
      case 7: purge_List(); break;
      case 9: running = false; break;
      default:
        printLine('*');
        Container("INVALID INPUT");
    }
  } while(running);
  printLine('*');
  Container("Collecting garbage...");
  purge_List(); //garbage collection
  Container("Done!");
  printLine('#'); //terminate console window
  return 0;
}

inline void createNode(){
  printLine('-');
  int ID;
  do{
    ID = rand() % 10000;
    Container(build("Generated ",ID,""));
  }while(Search_List(ID) && !empty());
  // Reserve space for new node and fill it with data
  temp1 = new node;
  temp1 ->ID = ID;
  getInfo(); //get all record information with one single function!
  Container(build("Assigned ID ", temp1 ->ID ," To Student"));
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
    Container("The list is empty!");
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
  else if(start_ptr ->nxt == NULL){
    add_node_at_end();
  }
  else{
    createNode();
    temp1 ->nxt = start_ptr ->nxt;
    start_ptr ->nxt = temp1;
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
    Container("The list is empty!");
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
    Container("The list is alreaddy empty!");
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
    Container("The list is empty!");
  }
  else{
    printLine('=');
    Container("Student List");
    temp1 = start_ptr;
    do {
      // Display details for what temp points to
      displayInfo();
      // Move to next node (if present)
      temp1 = temp1 ->nxt;
      if (temp1 == NULL){
        printLine('+');
        Container("End of list");
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
    Container("The list is empty!");
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
    Container("The list is empty!");
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
    do {
      if (temp1 ->ID == search){
        displayInfo(); //display info
        return true; //student ID is in list
      }
      // Move to next node (if present)
      if (temp1 ->nxt == NULL){
        printLine('*');
        Container(build("ID " , search, " Is not in list"));
        return false; //student ID is not in list
      }
      temp2 = temp1;
      temp1 = temp1 ->nxt;
    } while (true); //because the return statments are above;
  }
  return false;
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
  int length = st_len;
  cout << str << " ";
  cout << string(size - length, weight);
  cout << "|" << endl;
}

/* contains a message within the display boundries */
void Container(string str){
  cout << "| ";
  int st_len = str.length();
  int length = st_len - 1;
  cout << str;
  cout << string(size - length,' ');
  cout << "|" << endl;
}
