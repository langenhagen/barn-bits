//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementierung einer doppelt verketteten Liste und ihrer 																								//
// Funktionen unter C																																												//
//																																																					//
// Author: Barn																																															//
// Version: 20090612																																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ListDC.h"
#include <stdlib.h>

// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////

// nicht generische Funktionen ******************************************************************************

/////////////////////////////////////////////////////////////////////
// newNode: erstellt einen neuen Knoten (Packing inbegriffen)
node* newNode( int val){

	node* new = (node*)malloc(sizeof(node));
	new->val = value;

	// Integritaet in Liste
	new->left = NULL;
	new->right = NULL;

	return node;
}

// generische Funktionen ************************************************************************************

/////////////////////////////////////////////////////////////////////
// newList: erstellt eine neue Liste
listDC* newList(){
	listDC* lst = (listDC*)malloc(sizeof(listDC));
	lst->size= 0;
	lst->first = NULL;
	lst->last = NULL;
	return lst;
}

/////////////////////////////////////////////////////////////////////
// updateList:	Ueber?pr?ft die Gueltigkeit der first / last Elemente,
//							updatet sie ggf, zaehlt die Elemente, updatet
//							die Zahl im Head und gibt sie zurueck
//							Liefert -1 wenn die Liste gleich NULL ist
int updateList(listDC* lst){

	if(lst==NULL)
		return -1;

	// first, last updaten
	while( lst->first->left != NULL)
		lst->first = lst->first->left;
	while( lst->last->right != NULL)
		lst->last = lst->last->right;

	// Elemente zaehlen
	int cntr = 0;
	node* nd = lst->first;
	while( nd != NULL){
		cntr++;
		nd = nd->right;
	}

  lst->size = cntr;
  return cntr;
}

/////////////////////////////////////////////////////////////////////
// getNode:	liefert den Node an der Uebergebenen Stelle
//					bzw liefert NULL, wenn die Stelle
//					ausserhalb des Scopes ist oder ein Parameter falsch ist
node* getNode(listDC* lst, unsigned int pos){

	if( lst==NULL)
		return NULL;

	node* nd = lst->first;

	while( pos-- > 0 && nd != NULL)
		nd = nd->right;
	return nd;
}

/////////////////////////////////////////////////////////////////////
// getPos:	die Position des übergebenen Nodes
//          - liefert -1 falls ein Fehler auftrat
int getPos(listDC* lst, node* nd){

  if(lst == NULL || nd==NULL)
		return -1;

  int ix = 0;

  node* tmp = lst->first;
  while(tmp != NULL && tmp != nd){
    tmp = tmp->right;
    ix++;
  }

  if( tmp==NULL)
		return -1;
  return ix;
}

/////////////////////////////////////////////////////////////////////
// switchNodes: tauscht den n-ten Node mit dem m-ten node
//							bzw tut nichts, wenn eine der beiden Zahlen
//							ausserhalb des Range der Liste befinden
//							-liefert 0 bei Erfolg und bei Misserfolg -1
int switchNodes(listDC* lst, unsigned int n, unsigned int m){

	// wenn Werte ausserhalb des Scopes
	if(n==m || lst==NULL)
		return -1;

  // Reihenfolge der Zahlen beibehalten
  if( n > m){
    int t = n;
    n = m;
    m = t;
  }

  node* nNode = getNode(lst, n);
	node* mNode = getNode(lst, m);

	delete(lst, nNode);
	delete(lst, mNode);
  insertAt(lst, nNode, m-1);
  insertAt(lst, mNode, n);

	return 0;
}

/////////////////////////////////////////////////////////////////////
// addRight: Anfuegen neuer Elemente am Listenende
void addRight(listDC* lst, node* new){

  if(lst==NULL || new==NULL)
    return;

  lst->size +=1;

	if(lst->first == NULL)		// wenn kein EL inder Liste
		lst->first = new;
  else{
    lst->last->right = new;
    new->left = lst->last;
  }
  new->right = NULL;
  lst->last = new;
}

/////////////////////////////////////////////////////////////////////
// addLeft: Anfuegen neuer Elemente am Listenanfang
void addLeft(listDC* lst, node* new){

  if(lst==NULL || new==NULL)
    return;

  lst->size +=1;

	if(lst->first == NULL)		// wenn kein EL inder Liste
		lst->first = new;
  else{
    lst->first->left = new;
    new->right= lst->first;
  }
  new->left = NULL;
  lst->first= new;
}

/////////////////////////////////////////////////////////////////////
// add:	Anfuegen neuer Elemente am Listenende
//			- entspricht addRight, nur aufgrund
//					besserer Handhabung eingefuegt
void add(listDC* lst, node* new){

  if(lst==NULL || new==NULL)
    return;

  lst->size +=1;

	if(lst->first == NULL)		// wenn kein EL inder Liste
		lst->first = new;
  else{
    lst->last->right = new;
    new->left = lst->last;
  }
  new->right = NULL;
  lst->last = new;
}

/////////////////////////////////////////////////////////////////////
// delete: Loescht ein Element konsistent aus der Liste
listDC* delete( listDC* lst, node* nd){

	if( lst==NULL || nd==NULL)
		return NULL;

	lst->size -= 1;
	if( lst->first == lst->last){
		lst->first = NULL;
		lst->last = NULL;
	}
	else if(lst->last == nd){
		lst->last = nd->left;
		nd->left->right = nd->right;
	}
	else if(lst->first == nd){
		lst->first = nd->right;
		nd->right->left = nd->left;
	}
	else{
		nd->right->left = nd->left;
		nd->left->right = nd->right;
	}
	return lst;
}

/////////////////////////////////////////////////////////////////////
// deleteAt: Loescht das Element an der angegebenen Stelle
listDC* deleteAt( listDC* lst, unsigned int pos){
	return delete( lst, getNode(lst, pos));
}

/////////////////////////////////////////////////////////////////////
// delLast: Loescht das letzte Element
listDC* delLast( listDC* lst){

	if( lst==NULL)
		return NULL;

	// wenn Liste leer oder einelementig
	if( lst->last == NULL){
		lst->last = NULL;
		lst->first = NULL;
		lst->size = 0;
		return lst;
  }
  lst->last = lst->last->left;
  if(lst->last != NULL)
    lst->last->right = NULL;
	lst->size -= 1;
  return lst;

}

/////////////////////////////////////////////////////////////////////
// delFirst: Loescht das erste Element
listDC* delFirst( listDC* lst){

	if( lst==NULL)
		return NULL;

	// wenn Liste leer oder einelementig
	if( lst->first == NULL){
		lst->last = NULL;
		lst->first = NULL;
		lst->size = 0;
		return lst;
  }
  lst->first = lst->first->right;
  if(lst->first != NULL)
    lst->first->left= NULL;
	lst->size -= 1;
  return lst;
}

/////////////////////////////////////////////////////////////////////
// restore:	Elemente zur entspr Liste restoren
//					Wenn Element schon in der Liste passiert nichts
 listDC* restore(listDC* lst, node* nd){

 	if( lst == NULL || nd ==NULL || nd->right->left == nd)
		return lst;

	// Restorevorgang
	nd->right->left = nd;
	nd->left->right = nd;

	// Listenkonsistenz
	lst->size +=1;
	if(nd->right == lst->first)
		lst->first = nd;
	if(nd->left == lst->last)
		lst->last = nd;
	return lst;
}

/////////////////////////////////////////////////////////////////////
// insertRight: Einfuegen neuer Elemente rechts
//							- Datenkonsistenz nur durch ein nachfolgendes
//								updateList() gewaehrleistet!
void insertRight(listDC* lst, node* nd, node* new){

	if( lst==NULL || nd==NULL || new==NULL)
		return;

	new->right = nd->right;
	new->left = nd;
	nd->right = new;

	if( new->right != NULL)
		new->right->left = new;
  updateList(lst);
}

/////////////////////////////////////////////////////////////////////
// insertLeft:	Einfuegen neuer Elemente links
//							- Datenkonsistenz nur durch ein nachfolgendes
//								updateList() gewaehrleistet!
void insertLeft(listDC* lst, node* nd, node* new){

	if( lst==NULL || nd==NULL || new==NULL)
		return;


	new->right = nd;
	new->left = nd->left;
	nd->left = new;

	if( new->left != NULL)
		new->left->right = new;
  updateList(lst);
}

/////////////////////////////////////////////////////////////////////
// insert:	Einfuegen neuer Elemente rechts
//					-	entspricht insertRight, nur aufgrund
//						besserer Handhabung eingefuegt
//					- Datenkonsistenz nur durch ein nachfolgendes
//						updateList() gewaehrleistet!
void insert(node* nd, node* new){

	if( nd==NULL || new==NULL)
		return;

	new->right = nd->right;
	new->left = nd;
	nd->right = new;

	if( new->right != NULL)
		new->right->left = new;
}

/////////////////////////////////////////////////////////////////////
// insertAt:	Einfuegen eines neuen Knotens an der angegebenen
//						Stelle
//						- liefert pos bei Erfolg und -1 bei Misserfolg
int insertAt(listDC* lst, node* new, unsigned int pos){

	if( lst==NULL || new==NULL)
		return -1;

	node* nd = lst->first;

	int i=0;
	while( i<pos && nd != NULL){
		nd = nd->right;
		i++;
	}

	if( i<pos) return -1;

  if(nd == NULL)
    addRight(lst, new);
  else
    insertLeft( lst, nd, new);
	return pos;
}

/////////////////////////////////////////////////////////////////////
// putLeft:	Schiebt einen ListNode um n Schritte nach hinten
// 					ist n groesser als Anzahl der Vorgaenger des Nodes,
//					wird der Knoten als erstes Listenelement angeordnet.
//					Gibt die Anzahl der wirklich gemachten Schritte zurueck.
//					- Datenkonsistenz nur durch ein nachfolgendes
//						updateList() gewaehrleistet!
int putLeft(listDC* lst, node* nd, unsigned int n){

	if( lst==NULL || nd==NULL)
		return -1;

	int cntr = n;
	node* tmp = nd;

	// Zuruecksetzen
	while( cntr>0){
		if(tmp->left == NULL) break;
		tmp = tmp->left;
		cntr--;
	}
	if( tmp == nd)	// Fehlerabfangen: ueberhaupt bewegt?!
		return 0;

	delete( lst, nd);
	insertLeft(lst, tmp, nd);

	return n-cntr;
}

/////////////////////////////////////////////////////////////////////
// putLeftByPos:Schiebt einen ListNode um n Schritte nach hinten
// 							ist n groesser als Anzahl der Vorgaenger des Nodes,
//							wird der Knoten als erstes Listenelement angeordnet.
//							Gibt die Anzahl der wirklich gemachten Schritte zurueck.
//							- Datenkonsistenz nur durch ein nachfolgendes
//								updateList() gewaehrleistet!
int putLeftByPos(listDC* lst, unsigned int pos, unsigned int n){
  return putLeft( lst, getNode(lst, pos), n);
}

/////////////////////////////////////////////////////////////////////
// putRight:	Schiebt einen ListNode um n Schritte nach vorn;
// 						ist n groesser als Anzahl der Nachfolger des Nodes,
//						wird der Knoten als erstes Listenelement angeordnet.
//						Gibt die Anzahl der wirklich gemachten Schritte zurueck.
//						- Datenkonsistenz nur durch ein nachfolgendes
//							updateList() gewaehrleistet!
int putRight( listDC* lst, node* nd, unsigned int n){

	if( lst==NULL || nd==NULL)
		return -1;

	int cntr = n;
	node* tmp = nd;

	// Vorsetzen
	while( cntr>0){
		if(tmp->right == NULL) break;
		tmp = tmp->right;
		cntr--;
	}
	if( tmp == nd)	// Fehlerabfangen:  ueberhaupt bewegt?!
		return 0;

	delete( lst, nd);
	insertRight(lst, tmp, nd);

	return n-cntr;
}

/////////////////////////////////////////////////////////////////////
// putRightByPos:	Schiebt einen ListNode um n Schritte nach vorn;
// 								ist n groesser als Anzahl der Nachfolger des Nodes,
//								wird der Knoten als erstes Listenelement angeordnet.
//								Gibt die Anzahl der wirklich gemachten Schritte zurueck.
//								- Datenkonsistenz nur durch ein nachfolgendes
//									updateList() gewaehrleistet!
int putRightByPos(listDC* lst, unsigned int pos, unsigned int n){
  return putRight( lst, getNode(lst, pos), n);
}
