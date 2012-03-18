/* Linked list example - a linked list of integers,

 
  The remote procedure returns the sum
*/


#define VERSION_NUMBER 1


struct foo {


	int x;
	foo *next;

};






struct tree {

int x;

tree *left;

tree *right;

};




program LL_PROG {


   version LL_VERSION {


     tree in(foo) = 1;


   } = VERSION_NUMBER;


} = 0x20000210;

