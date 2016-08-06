#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*
Red Black Tree Properties 
1) Every Node is Either Red or Black
2) Every Leaf (nil) is black
3) if a node is Red then both of its children are black
4) Every Simple path from a node to a decendant leaf contains the same number of black nodes
*/

enum NODE_COLOR
  {
    no_colour,
    black,
    red
  };

char *colors[] = {"No Color", "Black", "Red"};

struct node
{
  int key;
  enum NODE_COLOR color;
  struct node *left;
  struct node *right;
  struct node *parent;
};

struct node *RotateLeft(struct node *root)
{
  struct node *rt = NULL;
  struct node *newHead = NULL;
  struct node *parent = NULL;

  if (NULL == root || NULL == root->right)
    {
      /*you cannot rotate this node*/
      return (root);
    }

  parent = root->parent;
  newHead = root->right;

  if(NULL != root->parent)
    {
      if (root->parent->left == root)
	{
	  /*left*/
	  root->parent->left = newHead;
	}
      else 
	{
	  /*right*/
	  root->parent->right = newHead;
	}
    }

  rt = root->right->left;
  root->right->left = root;
  root->parent = root->right;
  root->right = rt;
  
  if(NULL != rt)
    {
      rt->parent = root;
    }

  newHead->parent = parent;

  return (newHead);
}

struct node *RotateRight(struct node *root)
{
  struct node *lt = NULL;
  struct node *newHead = NULL;
  struct node *parent = NULL;

  if (NULL == root || NULL == root->left)
    {
      /*you cannot rotate this node*/
      return (root);
    }

  parent = root->parent;
  newHead = root->left;

  if(NULL != root->parent)
    {
      if (root->parent->left == root)
	{
	  /*left*/
	  root->parent->left = newHead;
	}
      else 
	{
	  /*right*/
	  root->parent->right = newHead;
	}
    }

  lt = root->left->right;
  root->left->right = root;

  root->parent = root->left;

  root->left = lt;
  if(NULL!=lt)
    {
      lt->parent = root;
    }

  newHead->parent = parent;

  return (newHead);
}

void spaces(int space)
{
  int i;

  for (i = 0 ; i < space; i++)
    {
      printf("\t");
    }
}

void printTree(struct node *root,int level)
{

  if(NULL == root)
    {
      spaces(level);
      printf("Nil\n");
      return;
    }

  spaces(level);
  printf ("Level %d, Key (%d), Color %s, ",level,root->key,colors[root->color]);
  if(NULL != root->parent)
    {
      printf("Parent Key [%d]\n",root->parent->key);
    }
  else
    {
      printf("Parent Nil\n");
    }
  spaces(level);
  printf ("Left:\n");
  printTree(root->left,level+1);
  spaces(level);
  printf ("Right:\n");
  printTree(root->right,level+1);

}

struct node* Insert(struct node *root,struct node *entry)
{

  if (NULL == root)
    {
      entry->parent = NULL;
      return (entry);
    } 

  if (entry->key < root->key)
    {
      root->left = Insert(root->left,entry);
      /*set parent Pointer of Left Child*/
      root->left->parent = root;
    }
  else
    {
      root->right = Insert(root->right,entry);
      /*set parent Pointer of Left Child*/
      root->right->parent = root;
    }

  return (root);
}

struct node* RBInsert(struct node *root,struct node *entry)
{
    struct node *x = NULL;
    struct node *y = NULL;
  
    root = Insert(root,entry);
    entry->color = red;

    x = entry;

    while (NULL != x->parent && 
	   red == x->parent->color)
      {
	/*check to see if the parent of this node is the left of the grand 
	  parent*/
	if (NULL != x->parent->parent && x->parent == x->parent->parent->left)
	  {
	    y = x->parent->parent->right;
	    if((NULL != y) && (red == y->color))
	      {
		x->parent->color = black;
		y->color = black;
		x->parent->parent->color = red;
		x = x->parent->parent;
	      }
	    else 
	      {
		if(x == x->parent->right)
		  {
		    x = x->parent;
		    RotateLeft(x);
		  }
		x->parent->color = black;
		x->parent->parent->color = red;
		RotateRight(x->parent->parent);
	      }
	  }
	else
	  {
	    y = x->parent->parent->left;
	    if((NULL != y) && (red == y->color))
	      {
		x->parent->color = black;
		y->color = black;
		x->parent->parent->color = red;
		x = x->parent->parent;
	      }
	    else 
	      {
		if(x == x->parent->left)
		  {
		    x = x->parent;
		    RotateRight(x);
		  }
		x->parent->color = black;
		x->parent->parent->color = red;
		RotateLeft(x->parent->parent);
	      }
	  }
      }

    /*The Root may have been rotated, so we must go up to find it*/
    while (NULL != root->parent)
      {
	root = root->parent;
      }

    root->color = black;
    return (root);
}

int main(int argc, char *argv[])
{
  struct node *root = NULL;
  struct node *tmp = NULL;

  int key;
  int i;

  for (i = 1 ; i < argc ; i++)
    {
      key = atoi(argv[i]);
      tmp = (struct node *)malloc(sizeof(struct node));
      tmp->key = key;
      tmp->parent = NULL;
      tmp->right = NULL;
      tmp->left = NULL;
      tmp->color = no_colour;
      root = RBInsert(root,tmp);
      tmp = NULL;
    }
  
  printTree (root,0);

#if 0
  struct node head,right,left;
  struct node *root = NULL;

  head.key = 0;
  head.left = &left;
  head.right = &right;
  head.parent = NULL;

  left.key = 1;
  left.left = NULL;
  left.right = NULL;
  left.parent = &head;

  right.key = 2;
  right.right = NULL;
  right.left = NULL;
  right.parent = &head;

  root = &head;

  printTree (root,0);
  printf("\n\n\n\n");

  root = RotateLeft(root);
  printTree (root,0);
  printf("\n\n");
  root = RotateRight(root);
  root = RotateRight(root);
  printTree (root,0);
#endif


}

