#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* leftNode;
    struct node* rightNode;
    int height;
}treeNode;

typedef struct tree {
  treeNode* root;
  int size;
}Tree;

void printTree(treeNode* root){
    if(root==NULL){
        printf("NULL ");
        return;
    }
    printTree(root->leftNode);
    printf("%d ", root->value);
    printTree(root->rightNode);
}

Tree createTree() {
  Tree t;
  t.root = NULL;
  t.size = 0;
  return t;
}

treeNode* add(treeNode* t, int x) {             //passing root of tree
    if(t == NULL){
        treeNode* new = (treeNode*)malloc(sizeof(treeNode)); 
        new->leftNode = NULL;
        new->rightNode = NULL;
        new->height = 0;
        new->value = x;
        return new;
    }
    else {
        if(t->value >= x){
          t->leftNode = add(t->leftNode, x);
        } 
        else{
          t->rightNode = add(t->rightNode, x);
        }
    }
}

treeNode* find(treeNode* t, int x) {             //passing root of tree
    if(t == NULL){
        printf("Node not found.\n");
        return NULL;
    }
    else if(t->value == x){
        return t;
    }
    else {
        if(t->value >= x){
            find(t->leftNode, x);
        } 
        else{
            find(t->rightNode, x);
        }
    }
}

treeNode* inOrderSuccessor(treeNode* t) {
    if(t->leftNode == NULL) {
        return t;
    }
    else {
        return inOrderSuccessor(t->leftNode);
    }
}

treeNode* delete(treeNode* root, int val)
{
    treeNode* node = find(root, val);
    if(!node)
    {
        return root;
    }

    //Node is a leaf
    if(node->left == NULL && node->right == NULL){
        treeNode* Parent = parent(root, node);

        if(!Parent)
        {
            free(node);
            return NULL;
        }
        if(Parent->rightNode == node)
           Parent->rightNode = NULL;
        else if(Parent->leftNode = node)
           Parent->leftNode = NULL;
        free(node);
        return root;
    }

    //Node to be deleted is internal node and inorder successor exists
    treeNode *successor = inOrderSuccessor(root, node);
    if (successor)
    {
        int temp = successor->key;
        TreeNode *newRoot = deleteWithoutBalance(root, temp);
        node->key = temp;
        return newRoot;
    }
    //Node to be deleted is internal node and inorder successor does not exist
    else
    {
        TreeNode *parent = findParent(root, node->key);
        if(!parent)
            root = node->left;
        else
            parent->right = node->left;
        free(node);
        return root;
    }

}

treeNode* max(treeNode* x, treeNode* y){
    if(x->value>y->value){
        return x;
    }
    else{
        return y;
    }
}

treeNode* min(treeNode* x, treeNode* y){
    if(x->value>y->value){
        return y;
    }
    else{
        return x;
    }
}

treeNode* parent(treeNode* t,treeNode* child) {
  if(child == NULL) {
    return NULL;
  }
  if(t == NULL) {
    return NULL;
  }
  if(child->value>=t->value) {
    if(t->rightNode == child) {
      return t;
    }
    else {
      return parent(t->rightNode,child);
    }
  }
  else {
    if(t->leftNode == child) {
      return t;
    }
    else {
      return parent(t->leftNode,child);
    }
  }
}

treeNode* rotate(treeNode* bt,treeNode* x, treeNode* y, treeNode* z) {
  treeNode *a, *b, *c, *t0, *t1, *t2, *t3;
  a = max(x,y);
  a = max(a,z);

  c = min(x,y);
  c = min(c,z);

  if(x!=a&&x!=c) {
    b = x;
  }
  else if(y!=a&&y!=c) {
    b = y;
  }
  else {
    b = z;
  }

  t0 = a->leftNode;

  if(b->leftNode != a) {
    t1 = b->leftNode;
  }

  else {
    t1 = a->rightNode;
  }

  if(b->rightNode != c) {
    t2 = b->rightNode;
  }
  else {
    t2 = c->leftNode;
  }

  t3 = c->rightNode;

  treeNode* Parent = parent(bt,z);
  if(z->value > Parent->value) {
    Parent->rightNode = b;
  }
  else {
    Parent->leftNode = b;
  }

  b->leftNode = a;
  b->rightNode = c;
  a->leftNode = t0;
  a->rightNode = t1;
  c->leftNode = t2;
  c->rightNode = t3;

  return b;
}

int Height(treeNode* t)
{
	if(t==NULL){
		return 0;
  }
	if(t->leftNode==NULL && t->rightNode==NULL){
		return 0;
  }
	int a = Height(t->leftNode);
	int b = Height(t->rightNode);
  int h;
	if(a>b){
    h = a;
  }
  else{
    h = b;
  }
	t->height = h+1;
	return h+1;
}

treeNode* addAVL(treeNode* t, int val)
{
  treeNode *x, *y, *z;
	t = add(t,val);
	x = find(t,val);
	treeNode* b = x;
	while(x!=NULL)
	{
			x = b;
			if(t==x || t==parent(t,x)){
				break;
      }
      y = parent(t,x);
			z = parent(t,parent(t,x));
			int h;
			if(z->leftNode!=NULL && z->rightNode!=NULL){            //finding balance factor of z
        h = abs(Height(z->leftNode) - Height(z->rightNode));
      }	
			else if(z->leftNode!=NULL){
				h = Height(z->leftNode)+1;
      }
			else if(z->rightNode!=NULL){
				h = Height(z->rightNode)+1;
      }
			else{
        				h = 0;
      }
			if(h>1) //if point of imabalnce
			{
				if(y->value > z->value && x->value > y->value)    //case 1
				{
					t = rotate(t,z,y,x);
				}
				else if(y->value < z->value && x->value < y->value) //case 2
				{
					t = rotate(t,x,y,z);
				}
				else if(y->value > z->value && x->value < y->value) //case 3
				{
					t = rotate(t,z,x,y);
				}
        else{                                               //case 4
					t = rotate(t,y,x,z);
        }
      }

				if(b==t){
					break;
        }
				b = parent(t,b);
	}	
	return t;
}

treeNode* deleteCases(treeNode* t, treeNode* node)
{
	treeNode *x, *y, *z;

		z = node;
		treeNode* b = z;
		while(z!=NULL)
		{
			z = b;
			int h;
			if(z->leftNode!=NULL && z->rightNode!=NULL){
				h = abs(Height(z->leftNode) - Height(z->rightNode));
      }
			else if(z->leftNode!=NULL){
				h = Height(z->leftNode)+1;
      }
			else if(z->rightNode!=NULL){
				h = Height(z->rightNode)+1;
      }
			else{
				h = 0;
      }

			//check if Z is imbalanced
			if(h>1)
			{

				if(z->leftNode==NULL){
					y = z->rightNode;
        }
				else if(z->rightNode==NULL){
					y = z->leftNode;
        }
				else if(Height(z->leftNode) > Height(z->rightNode)){
					y = z->leftNode;
        }
				else{
					y = z->rightNode;
        }
				
				if(y->leftNode==NULL){
					x = y->rightNode;
        }
				else if(y->rightNode==NULL){
					x = y->leftNode;
        }
				else if(Height(y->leftNode) > Height(y->rightNode)){
					x = y->leftNode;
        }
				else{
					x = y->rightNode;
        }

				//this means that Z is a point of imbalance
			if(y->value > z->value && x->value > y->value)    //case 1
				{
					t = rotate(t,z,y,x);
				}
				else if(y->value < z->value && x->value < y->value) //case 2
				{
					t = rotate(t,x,y,z);
				}
				else if(y->value > z->value && x->value < y->value) //case 3
				{
					t = rotate(t,z,x,y);
				}
        else{                                               //case 4
					t = rotate(t,y,x,z);
        }
				
      }
      if(b==t){
                break;
              }
              b = parent(t,b);
        }	
	return t;
}

treeNode* deleteAVL(treeNode* t, int val)
{
	treeNode* f = find(t,val);
		
	if(f==NULL)
		return t;

	if(f->rightNode==NULL && f->leftNode==NULL)
	{
		treeNode* Parent = parent(t,f);
		if(parent==NULL)
		{
			free(f);
			return NULL;
		}

		if(Parent->leftNode==f){
			Parent->leftNode=NULL;
    }
		else if(Parent->rightNode==f){
			Parent->rightNode = NULL;
    }
		free(f);
		t = deleteCases(t,Parent);
		
		return t;
	}

	else if(f->rightNode==NULL)
	{
		treeNode* Parent = parent(t,f);
    if(Parent==NULL)
    {
			treeNode* temp = f->leftNode;
      free(f);
      return temp;
    }

    if(Parent->leftNode==f){
      Parent->leftNode=f->leftNode;
    }
 
    else if(Parent->rightNode==f){
      Parent->rightNode = f->leftNode;
    }

    free(f);
		t = deleteCases(t,Parent);
    return t;
	}

	else if(f->leftNode==NULL)
	{
		treeNode* Parent = parent(t,f);
    if(Parent==NULL)
    {
			treeNode* temp = f->rightNode;
      free(f);
      return temp;
    }

    if(Parent->leftNode==f){
      Parent->leftNode=f->rightNode;
    }
 
    else if(Parent->rightNode==f){
      Parent->rightNode = f->rightNode;
    }

    free(f);
		t = deleteCases(t,Parent);
    return t;
	}

	else{

		treeNode* temp = inOrderSuccessor(f);

		treeNode* Parent = parent(t,temp);
		int x = temp->value;
		f->value = x;	
		if(Parent->leftNode==temp)
		{
			Parent->leftNode = deleteAVL(temp,x);
		}
		else if(Parent->rightNode==temp)
		{
			Parent->rightNode = deleteAVL(temp,x);
		}
		f->value = x;
		t = deleteCases(t,Parent);
		return t;
	}

}

int main()
{
	treeNode* root = NULL;
	printf("\n\tCreating a binary search tree with 10 numbers\n");
	root = add(root,12);
	root = add(root,23);
	root = add(root,11);
	root = add(root,10);
	root = add(root,67);
	root = add(root,33);
	root = add(root,45);
	root = add(root,66);
	root = add(root,77);
	root = add(root,90);
	printTree(root);
	printf("\n\n\tDeleting the values 12,23 and 10\n");
	
	root = delete(root,12);
	root = delete(root,23);
	root = delete(root,10);
	printTree(root);


	printf("\n\n\tCreating an AVL search tree with 8 numbers\n");
	treeNode* AVLroot = NULL;
	AVLroot = addAVL(AVLroot,14);
	AVLroot = addAVL(AVLroot,17);
	AVLroot = addAVL(AVLroot,78);
	AVLroot = addAVL(AVLroot,32);
	AVLroot = addAVL(AVLroot,50);
	AVLroot = addAVL(AVLroot,88);
	AVLroot = addAVL(AVLroot,48);
	AVLroot = addAVL(AVLroot,62);
	AVLroot = addAVL(AVLroot,54);
	printTree(root);
	
	printf("\n\n\tDeleting the values 62,32,14 and 17\n");
	AVLroot = deleteAVL(AVLroot,62);
	AVLroot = deleteAVL(AVLroot,32);
	AVLroot = deleteAVL(AVLroot,14);
	AVLroot = deleteAVL(AVLroot,17);

	printTree(root);
	printf("\n\n");
	return 0;
}
