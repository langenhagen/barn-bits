//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Headerdatei einer doppelt verketteten Liste und ihrer                                                    //
// Funktionen unter C                                                                                       //
//                                                                                                          //
// Author: Barn                                                                                             //
// Version: 20090612                                                                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////

// DATA TYPES ///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////// NOT GENERIC *****************
// DATENTYP node: ein Listenelement
 typedef struct node{

	int val;

	struct node* left;
	struct node* right;
} node;

/////////////////////////////////////////////////////////////////////
// DATENTYP listDC: die Liste, double chained
 typedef struct{
	int size;
	node* first;
	node* last;
} listDC;

listDC* newList();
node* newNode(int value);

node* getNode(listDC* lst, unsigned int pos);
int getPos(listDC* lst, node* nd);
int updateList(listDC* lst);
int switchNodes(listDC* lst, unsigned int n, unsigned int m);

void addRight(listDC* lst, node* new);
void addLeft(listDC* lst, node* new);
void add(listDC* lst, node* new);

listDC* delete( listDC* lst, node* nd);
listDC* deleteAt( listDC* lst, unsigned int pos);
listDC* delLast( listDC* lst);
listDC* delFirst( listDC* lst);
listDC* restore(listDC* lst, node* nd);

void insertRight(listDC* lst, node* nd, node* new);
void insertLeft(listDC* lst, node* nd, node* new);
void insert(node* nd, node* new);
int insertAt(listDC* lst, node* new, unsigned int pos);

int putLeft(listDC* lst, node* nd, unsigned int n);
int putLeftByPos(listDC* lst, unsigned int pos, unsigned int n);
int putRight(listDC* lst, node* nd, unsigned int n);
int putRightByPos(listDC* lst, unsigned int pos, unsigned int n);
