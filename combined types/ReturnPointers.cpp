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

struct SearchResults{
  Ptr temp1, temp2;
  bool found;
};

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
void getInfo(Ptr temp1){
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

//displays node at temp1
/* Displays contents of current node that temp1 is pointing at */
void displayInfo(Ptr temp1){
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

//indipendant
void Display_List       (Ptr start_ptr); //displays whole list

//list functions
//functions that do not change the start pointer
// requres no user input
SearchResults createNode (Ptr start_ptr); //list stack and que
bool empty               (Ptr start_ptr); // used in list and stack

//generates pointer information reguarding an ID;
SearchResults Search_List (Ptr start_ptr, int search, int sort); // used in list

//Returns Node
void first (Ptr start_ptr); //used in que and stack

//functions that do change pointer values.
//ADDS
void add_start_node (Ptr &start_ptr,Ptr); // used in list and stack
void add_To_Middle  (Ptr &start_ptr,Ptr, Ptr); // list
void add_node_at_end(Ptr &start_ptr,Ptr); //used in queue

//REMOVES
void delete_start_node (Ptr &start_ptr); //list stack and que
void purge_List        (Ptr &start_ptr); // used in list and stack
void delete_middlenode (Ptr &start_ptr, int search); // used in que

//Can be used by user and program
void Modify_Node (Ptr start_ptr, int search); // used in list

// void delete_end_node(); //unused because deleting from front is easier (more eficient)
// void last(); //unused

//stores sort type
int sort = 0;

int main() {

  //start pointers
  Ptr List_ptr = NULL;
  Ptr Queue_ptr = NULL;
  Ptr Stack_ptr = NULL;

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
      CenterString("  1 add     2 delete     3 modify   ");
      CenterString("  4 search [ Redacted ]  6 empty?   ");
      CenterString("  7 purge  [ Redacted ]  9 quit     ");
      break;
      case 1:
      CenterString("  1 enque    2 deque    [ Redacted ]");
      CenterString("[ Redacted ][ Redacted ] 6 empty?   ");
      CenterString("  7 purge    8 front     9 quit     ");
      break;
      case 2:
      CenterString(" 1 push      2 pop      [ Redacted ]");
      CenterString("[ Redacted ][ Redacted ] 6 empty?   ");
      CenterString(" 7 purge     8 Top       9 quit     ");
      break;
    }
    CenterString("10 Change behavior");
    printLine('-');
    LeftString("what do you want to do");
    LeftString("");
    switch (type) {
      case 0: Display_List(List_ptr);   break;
      case 1: Display_List(Queue_ptr); break;
      case 2: Display_List(Stack_ptr);  break;
    }
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
        case 0: add_To_Middle(List_ptr,   NULL, NULL); break;
        case 1: add_node_at_end(Queue_ptr,NULL); break;
        case 2: add_start_node(Stack_ptr, NULL); break;
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
            case 2: delete_middlenode(List_ptr,ID); break;
            case 3: Modify_Node(List_ptr,ID); break;
            case 4: SearchResults results = Search_List(List_ptr,ID, sort); //unpack
            if(results.found){
              displayInfo(results.temp1); //only display info if ID is present
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
          switch (type) {
            case 1: delete_start_node(Queue_ptr); break;
            case 2: delete_start_node(Stack_ptr); break;
          }
        }
        break;
      case 6:
        bool EMPTY;
        switch (type) {
          case 0: EMPTY = empty(List_ptr); break;
          case 1: EMPTY = empty(Queue_ptr); break;
          case 2: EMPTY = empty(Stack_ptr); break;
        }
        if(EMPTY){
          string outString;
          outString.append("* the ");
          outString.append(behavior[type]);
          outString.append(" is empty! *");
          CenterString(string(outString.length(),'*'));
          CenterString(outString);
          CenterString(string(outString.length(),'*'));
        }
        else{
          string outString;
          outString.append("* the ");
          outString.append(behavior[type]);
          outString.append(" is not empty! *");
          CenterString(string(outString.length(),'*'));
          CenterString(outString);
          CenterString(string(outString.length(),'*'));
        }

        break;
      case 7:
        switch (type) {
          case 0: purge_List(List_ptr);  break;
          case 1: purge_List(Queue_ptr); break;
          case 2: purge_List(Stack_ptr); break;
        }
      case 8:
      switch (type) {
        case 1: first(Queue_ptr); break;
        case 2: first(Stack_ptr); break;
      }
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
  type = 0; //for display
  purge_List(List_ptr); //garbage collection
  type = 1; //for display
  purge_List(Queue_ptr); //garbage collection
  type = 2; //for display
  purge_List(Stack_ptr); //garbage collection
  LeftString("Done! safe to close");
  printLine('#'); //terminate console window
  return 0;
}

void first(Ptr start_ptr){
  if(!empty(start_ptr)){
    displayInfo(start_ptr); //dsiplay first node
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
//     Ptr temp1;
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
SearchResults createNode(Ptr start_ptr){
  int ID;
  SearchResults results; //initalise holder for search and pointer data
  // Search first because search will move temp 1 and 2
  // to the proper location in list and search will set up
  // temp 1 and 2 for inserting a node inbetween them if needed
  do{
    ID = rand() % TotalIDS;
    LeftString(build("Generated ",ID,""));
    results = Search_List(start_ptr, ID, sort); //pack each iteration untill not found unless empty
  }while(results.found);
  Ptr temp1 = results.temp1;
  // Reserve space for new node and fill it with data
  temp1 = new node;
  temp1 ->ID = ID;
  getInfo(temp1); //get all record information with one single function!
  LeftString(build("Assigned ID ", temp1 ->ID ," To Student"));
  temp1 ->nxt = NULL;
  results.temp1 = temp1; //pack
  return results;
}

/* sets temp node to start pointer then makes the start pointer
   point to the next node then deletes node wtih temp           */
void delete_start_node(Ptr &start_ptr){
  if(empty(start_ptr)){
    string outString;
    outString.append("* the ");
    outString.append(behavior[type]);
    outString.append(" is empty! *");
    CenterString(string(outString.length(),'*'));
    CenterString(outString);
    CenterString(string(outString.length(),'*'));
  }
  else {
    Ptr temp1;
    temp1 = start_ptr;
    start_ptr = start_ptr ->nxt;
    delete temp1;
  }
}

/* creates a node and if empty, point the start pointer to it,
   else, point it to where the start pointer is pointing to
   then points the start pointer to it (insert at front)      */
void add_start_node(Ptr &start_ptr, Ptr temp1){
  if (temp1 == NULL) temp1 = createNode(start_ptr).temp1;
  if(empty(start_ptr)){
    start_ptr = temp1;
  }
  else{
    temp1 ->nxt = start_ptr;
    start_ptr = temp1;
  }
}

/* if not empty and has at least 2 nodes adds to the node behind the first */
void add_To_Middle(Ptr &start_ptr, Ptr temp2, Ptr temp1){
  if(empty(start_ptr)){
    add_start_node(start_ptr,temp1);
  }
  else{
    // creates node, does a search and sets up pointers for operations
    // there is no need to do 2 searches when createnode alreaddy did a search
    SearchResults results;
    if (temp1 == NULL){
      results = createNode(start_ptr); //unpack
      temp1 = results.temp1;
      temp2 = results.temp2;
    }
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
void add_node_at_end (Ptr &start_ptr,Ptr temp1){
  if (temp1 == NULL) temp1 = createNode(start_ptr).temp1;
  // Set up link to this node
  if (empty(start_ptr))
  start_ptr = temp1;
  else {
    // carries the temp node to the end and attaches it to the last node
    Ptr temp2 = start_ptr;
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
//     Ptr temp1, temp2;
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
void purge_List(Ptr &start_ptr){
  if(empty(start_ptr)){
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
      delete_start_node(start_ptr);
    }while(!empty(start_ptr));
  }
}

/* will display each node untill it reaches the end */
void Display_List(Ptr start_ptr){
  Ptr temp1;
  if(empty(start_ptr)){
    string outString;
    outString.append("* the ");
    outString.append(behavior[type]);
    outString.append(" is empty! *");
    CenterString(string(outString.length(),'*'));
    CenterString(outString);
    CenterString(string(outString.length(),'*'));
  }
  else{
    switch (type) {
      case 0: CenterString("Student List");  break;
      case 1: CenterString("Student Queue"); break;
      case 2: CenterString("Student Stack"); break;
    }
    temp1 = start_ptr;
    do {
      // Display details for what temp points to
      displayInfo(temp1);
      // Move to next node (if present)
      temp1 = temp1 ->nxt;
    } while (temp1 != NULL);
    printLine('+');
    switch (type) {
      case 0: CenterString("End of List");  break;
      case 1: CenterString("Back of Queue"); break;
      case 2: CenterString("Bottom of Stack"); break;
    }
  }
}

/* returns boolian value */
bool empty(Ptr start_ptr){
  return (start_ptr == NULL);
}

/* deletes the node with the ID */
void delete_middlenode(Ptr &start_ptr, int search){
  if(empty(start_ptr)){
    // nothing special here
    CenterString("**********************");
    CenterString("* The list is empty! *");
    CenterString("**********************");
  }
  else{
    SearchResults results = Search_List(start_ptr,search, sort);
    if(results.found){
      Ptr temp1 = results.temp1;
      Ptr temp2 = results.temp2;
      displayInfo(temp1); //display info
      // if temp 2 is NULL that means the first node
      // matches the one being seached for so delete the first node
      if (temp2 == NULL){
        delete_start_node(start_ptr);
      }
      else{
        temp2 ->nxt = temp1 ->nxt;
        delete temp1;
      }
    }
  }
}

/* changes the node with the ID */
void Modify_Node(Ptr start_ptr, int search){
  if(empty(start_ptr)){
    //nothing special here
    CenterString("**********************");
    CenterString("* The list is empty! *");
    CenterString("**********************");
  }
  else{
    SearchResults results = Search_List(start_ptr,search, sort);
    if(results.found) //returns true if ID is in list and sets pointers
      getInfo(results.temp1); //get all record information with one single function!
    else{
      //nothing special here
      CenterString(build("***********************", -1 , string(to_string(search).length(),'*')));
      CenterString(build("* ID :" , search, " Is not in list *"));
      CenterString(build("***********************", -1 , string(to_string(search).length(),'*')));
    }
  }
}

/* if not empty traverses the list
   untill it reaches node with ID handles displaying
   if not in list message                            */
SearchResults Search_List(Ptr start_ptr, int search, int sort){
  SearchResults results;
  Ptr temp1, temp2;
  if(!empty(start_ptr)){
    temp1 = start_ptr;
    temp2 = NULL;
    do {
      if (temp1 ->ID == search){
        results.temp1 = temp1; //pack
        results.temp2 = temp2; //pack
        results.found = true;  //pack
        return results; //student ID is in list
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
  results.temp1 = temp1; //pack
  results.temp2 = temp2; //pack
  results.found = false; //pack
  return results; //student ID is not in list
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
