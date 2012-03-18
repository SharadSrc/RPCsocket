/* RPC client for simple addition example */
/*
 * Name :sharad Dixit
 * Institute:Indian institute of information technology
 */


#include <stdio.h>

#include <stdlib.h>


#include "ll.h" 
/* Created for us by rpcgen - has everything we need ! */


void display(tree*st,int level)
{
	int i;
	if(st)
	{
		display(st->right,level+1);
		printf("\n");
		for(i=0;i<level;i++)
			printf("  ");
		printf("%d",st->x);
		display(st->left,level+1);
	}
}


//printing the inorder of the tree
void inorder(tree * root)
{
	static int count=0;
	if(root!=NULL)
	{
		count=1;
		inorder(root->left);
		printf("->%d",root->x);
		inorder(root->right);
	}
	else if((root==NULL)&&(count==0))
	{
		printf("Tree is null");
	}
}


//printing the preorder of the tree
void preorder(tree * root)
{
	static int count=0;
	if(root!=NULL)
	{
		count=1;
		printf("->%d",root->x);
		preorder(root->left);
		preorder(root->right);
	}
	else if((root==NULL)&&(count==0))
	{
		printf("Tree is null");
	}
}


//printing the postorder of the tree
void postorder(tree * root)
{
	static int count=0;
	if(root!=NULL)
	{
		count=1;
		postorder(root->left);
		postorder(root->right);
		printf("->%d",root->x);
	}
	else if((root==NULL)&&(count==0))
	{
		printf("Tree is null");
	}
}

//printing the nodes given in input
void printnums( foo *f) 
{  
	printf(" the entered nodes are:::");
	while (f) {
		printf("%d ",f->x);
		f=f->next; 
	}
	printf("\n");
}

void print_inorder( foo *head, CLIENT *clnt)
{

	tree *result;


	result = in_1(head, clnt);


	if (result == NULL)
	{
		clnt_perror(clnt, "call failed");

		return;
	}
	display(result,1);
	printf("\n\n\n");
	printf("preorder of the tree::\n");   
	preorder(result);
	printf("\n");
	printf("inorder of the tree::\n");   
	inorder(result);
	printf("\n");
	printf("postorder of the tree::\n");   
	postorder(result);
	printf("\n");   

}


int main( int argc, char *argv[])
{

	CLIENT *clnt;

	int n,i;

	foo *f;

	foo *head;

	foo *prev;


	if (argc<3)
	{

		fprintf(stderr,"Usage: %s hostname num1 num2 ...\n",argv[0]);

		exit(0);

	}



	/* Create a CLIENT data structure that reference the RPC

	   procedure SIMP_PROG, version SIMP_VERSION running on the

	   host specified by the 1st command line arg. */


	clnt = clnt_create(argv[1], LL_PROG, LL_VERSION, "udp"); 


	/* Make sure the create worked */

	if (clnt == (CLIENT *) NULL) 
	{

		clnt_pcreateerror(argv[1]);

		exit(1);

	}


	n = argc-2;

	f = head = (foo *) malloc(sizeof(foo));

	for (i=0;i<n;i++) 
	{

		f->x = atoi(argv[i+2]);

		f->next = (foo *) malloc(sizeof(foo));

		prev=f;

		f = f->next;

	}


	free(prev->next);

	prev->next=NULL;

	printnums(head);

	print_inorder(head,clnt);



	return(0);

}



