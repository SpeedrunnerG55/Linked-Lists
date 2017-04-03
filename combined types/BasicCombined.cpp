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

//switch between types of programs
short type = 0;

//message for each behavior
string behavior[3] = {
  "List ",
  "Queue",
  "Stack"
};

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

//list functions
void Display_List(); //displays whole list
void add_start_node(); // used in list and stack
void add_To_Middle(); // list
void delete_start_node(); //list stack and que
void delete_middlenode(int search); // used in que
void add_node_at_end(); //used in queue
// void delete_end_node(); //unused because deleting from front is easier (more eficient)
bool empty(); // used in list and stack
void purge_List(); // used in list and stack
void Modify_Node(int search); // used in list
bool Search_List(int search); // used in list
void createNode(); //list stack and que
void first(); //used in que and stack
// void last(); //unused



int main() {
  //generate random seed
  srand(time(NULL));

  //input variable
  int Menu, ID;

  //running switch
  bool running = true;

  //Print Title
  printLine('#');
  CenterString("Super List v1.0");
  LeftString("");

  do{
    printLine('=');
    CenterString("Main Menu");
    printLine('-');
    CenterString("Current Behavior");
    CenterString(behavior[type]);
    printLine('-');
    switch (type) {
      case 0:
      CenterString("1 add     2 delete    3 modify");
      CenterString("4 search [ Redacted ] 6 empty?");
      CenterString("7 purge  [ Redacted ] 9 quit  ");
      CenterString("      10 Change behavior      ");
      break;
      case 1:
      CenterString("  1 enque    2 deque    [ Redacted ]");
      CenterString("[ Redacted ][ Redacted ] 6 empty?   ");
      CenterString("  7 purge    8 front     9 quit     ");
      CenterString("         10 Change behavior         ");
      break;
      case 2:
      CenterString(" 1 push      2 pop      [ Redacted ]");
      CenterString("[ Redacted ][ Redacted ] 6 empty?   ");
      CenterString(" 7 purge     8 Top       9 quit     ");
      CenterString("         10 Change behavior         ");
      break;
    }
    printLine('-');
    LeftString("what do you want to do");
    LeftString("");
    Display_List();
    getInput("",Menu);
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
    if(((type != 0) && (Menu == 3 || Menu == 4)) ||
       ((type == 0) && (Menu == 8))){
      CenterString("******************");
      CenterString("* This option is *");
      CenterString("*    Redacted    *");
      CenterString("******************");
      continue;
    }
    switch (Menu) {
      case 1:
      switch (type) {
        case 0: add_To_Middle();   break;
        case 1: add_node_at_end(); break;
        case 2: add_start_node();  break;
      }
      break;
      case 2:
      case 3:
      case 4:
        CenterString("Remove from");
        CenterString(behavior[type]);
        if(type == 0){
          switch (Menu) {
            case 2: getInput("Enter ID to delete", ID);    break;
            case 3: getInput("Enter ID to modify",ID);     break;
            case 4: getInput("Enter ID to search for",ID); break;
            cout << string(100,'\n');
          }
          //use the same input validation for case 2,3, and 4
          if (cin.fail()){
            getchar();
            cin.clear();
            CenterString("*****************");
            CenterString("* INVALID INPUT *");
            CenterString("* NOT A NUMBER  *");
            CenterString("*****************");
            break;
          }
          switch (Menu) {
            case 2: delete_middlenode(ID); break;
            case 3: Modify_Node(ID); break;
            case 4:
            if(Search_List(ID)){
              displayInfo(); //only display info if ID is present
            }
            else{
              string outstring;
              CenterString(build("***********************", -1 , string(to_string(ID).length(),'*')));
              CenterString(build("* ID :" , ID, " Is not in list *"));
              CenterString(build("***********************", -1 , string(to_string(ID).length(),'*')));
            }
            break;
          }
        }
        else{
          delete_start_node();
        }
        break;
      case 6:
        CenterString("**************************");
        if(empty()){
          CenterString("*           YES          *");
          CenterString("*    The list is empty!  *");
        }
        else{
          CenterString("*           NO           *");
          CenterString("* The list is not empty! *");
        }
        CenterString("**************************");
        break;
      case 7: purge_List();    break;
      case 8: first();         break;
      case 9: running = false; break;
      case 10:
      CenterString("1 List 2 Queue 3 Stack");
      getInput("Behavior",type);
      cout << string(100,'\n');
      type--; //decrement to index values
      break;
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
  purge_List(); //garbage collection
  LeftString("Done! safe to close");
  printLine('#'); //terminate console window
  return 0;
}

void first(){
  if(!empty()){
    temp1 = start_ptr;//dsiplay first node
    displayInfo();
  }
  else{
    string outString;
    outString.append("* the ");
    outString.append(behavior[type]);
    outString.append(" is empty! *");
    CenterString(string(outString.length(),'*'));
    CenterString(outString);
    CenterString(string(outString.length(),'*'));
  }
}

//UNUSED
// void last(){
//   if(!empty()){
//     do{
//       temp1 = temp1 ->nxt;//traverse the list untill the end is reached
//     }while (temp1 ->nxt != NULL)
//     displayInfo();
//   }
//   else{
//     CenterString("**********************");
//     CenterString("* The list is empty! *");
//     CenterString("**********************");
//   }switch (name) {
// }

/* gets information for ans sets up pointers for new node */
void createNode(){
  int ID;
  // Search first because search will move temp 1 and 2
  // to the proper location in list and search will set up
  // temp 1 and 2 for inserting a node inbetween them if needed
  do{
    ID = rand() % TotalIDS;
    LeftString(build("Generated ",ID,""));
  }while(Search_List(ID) && !empty());
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
    string outString;
    outString.append("* the ");
    outString.append(behavior[type]);
    outString.append(" is empty! *");
    CenterString(string(outString.length(),'*'));
    CenterString(outString);
    CenterString(string(outString.length(),'*'));
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
    // creates node, does a search and sets up pointers for operations
    // there is no need to do 2 searches when createnode alreaddy did a search
    createNode();
    // if temp 2 is NULL that means the first node is higher than
    // the one being inserted. add new node infront of the first
    // to keep it in asending order
    if(temp2 == NULL){
      temp1 ->nxt = start_ptr;
      start_ptr = temp1;
    }
    // else temp 2 will contain the node that is less than the node being added
    // and temp 1 will contain the node that is greater than it, or null if end
    // add the new node between temp 2 and temp 1
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

// UNUSED
// /* if not empty, if only one node exists delete the first node,
//                  else traverses to the end and deletes the last node */
// void delete_end_node(){
//   if(empty()){
//     CenterString("**********************");
//     CenterString("* The list is empty! *");
//     CenterString("**********************");
//   }
//   else {
//     temp1 = start_ptr;
//     if (temp1 ->nxt == NULL){
//       displayInfo();
//       delete temp1;
//       start_ptr = NULL;
//     }
//     else{
//       while (temp1->nxt != NULL){
//         temp2 = temp1;
//         temp1 = temp1 ->nxt;
//       }
//       displayInfo();
//       delete temp1;
//       temp2 ->nxt = NULL;
//     }
//   }
// }

/* if not empty will remove the first element untill it is empty */
void purge_List(){
  if(empty()){
    string outString;
    outString.append("* the ");
    outString.append(behavior[type]);
    outString.append(" is alreaddy empty! *");
    CenterString(string(outString.length(),'*'));
    CenterString(outString);
    CenterString(string(outString.length(),'*'));
  }
  else{
    string outString;
    outString.append("* the ");
    outString.append(behavior[type]);
    outString.append(" is purged! *");
    CenterString(string(outString.length(),'*'));
    CenterString(outString);
    CenterString(string(outString.length(),'*'));
    do{
      delete_start_node();
    }while(!empty());
  }
}

/* will display each node untill it reaches the end */
void Display_List(){
  if(empty()){
    string outString;
    outString.append("* the ");
    outString.append(behavior[type]);
    outString.append(" is empty! *");
    CenterString(string(outString.length(),'*'));
    CenterString(outString);
    CenterString(string(outString.length(),'*'));
  }
  else{
    CenterString("Student List");
    temp1 = start_ptr;
    do {
      // Display details for what temp points to
      displayInfo();
      // Move to next node (if present)
      temp1 = temp1 ->nxt;
    } while (temp1 != NULL);
    printLine('+');
    CenterString("End of list");
  }
}

/* returns boolian value */
bool empty(){
  return (start_ptr == NULL);
}

/* deletes the node with the ID */
void delete_middlenode(int search){
  if(empty()){
    // nothing special here
    CenterString("**********************");
    CenterString("* The list is empty! *");
    CenterString("**********************");
  }
  else if(Search_List(search)){
    displayInfo(); //display info
    // if temp 2 is NULL that means the first node
    // matches the one being seached for so delete the first node
    if (temp2 == NULL)
      delete_start_node();
    else{
      temp2 ->nxt = temp1 ->nxt;
      delete temp1;
    }
  }
}

/* changes the node with the ID */
void Modify_Node(int search){
  if(empty()){
    //nothing special here
    CenterString("**********************");
    CenterString("* The list is empty! *");
    CenterString("**********************");
  }
  else if(Search_List(search)) //returns true if ID is in list and sets pointers
    getInfo(); //get all record information with one single function!
  else{
    //nothing special here
    CenterString(build("***********************", -1 , string(to_string(search).length(),'*')));
    CenterString(build("* ID :" , search, " Is not in list *"));
    CenterString(build("***********************", -1 , string(to_string(search).length(),'*')));
  }
}

/* if not empty traverses the list
   untill it reaches node with ID handles displaying
   if not in list message                            */
bool Search_List(int search){
  if(!empty()){
    temp1 = start_ptr;
    temp2 = NULL;
    do {
      if (temp1 ->ID == search){
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
  return false; //student ID is not in list
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
