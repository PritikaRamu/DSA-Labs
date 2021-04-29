#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* leftNode;
    struct node* rightNode;
    int height;
}treeNode;


void printTree(treeNode* root)
{
	if(root==NULL)
		return;
	printTree(root->leftNode);
	printf("\n  node value : %d ",root->value);
	if(root->leftNode!=NULL)
		printf("  left child: %d ",root->leftNode->value);
	if(root->rightNode!=NULL)
		printf("  right child: %d ",root->rightNode->value);
	printTree(root->rightNode);

}

//works
treeNode* add(treeNode* t, int x) {             //passing root of tree
    if(t == NULL){
        treeNode* new = (treeNode*)malloc(sizeof(treeNode));      // if tree is empty
        new->leftNode = NULL;
        new->rightNode = NULL;
        new->height = 0;
        new->value = x;
        t = new;
        return t;
    }
    else {
        if(t->value >= x){
          //printf("%d",t->value);
          t->leftNode = add(t->leftNode, x);
        } 
        else{
          //printf("%d",t->value);
          t->rightNode = add(t->rightNode, x);
        }
    }
    return t;
}

//works
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

treeNode* minNode(treeNode* t)
{
	if(t==NULL){
    return NULL;
  }
	treeNode* x = t;
	while(t->leftNode!=NULL)
	{t = t->leftNode;}
	return t;
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

//works
treeNode* inOrderSuccessor(treeNode* node, treeNode* t)
{
		if(node==NULL){
			return NULL;
    }
		if(node->rightNode!=NULL){
			return minNode(node->rightNode);
    }

		treeNode* Parent = parent(t,node);
		while(Parent!=NULL && node==Parent->rightNode)
		{
			node = Parent;
			Parent = parent(t,node);
		}
		
		
		return t;

}

treeNode* delete(treeNode* root, int val)
{
    treeNode* node = find(root, val);
    if(!node)
    {
        return root;
    }

    //Node is a leaf
    if(node->leftNode == NULL && node->rightNode == NULL){
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

    treeNode *successor = inOrderSuccessor(node, root);
    if (successor)                                      //if node to be deleted is not a leaf, inordersuccessor takes replaces the node to be deleted
    {
        int temp = successor->value;
        treeNode *newRoot = delete(root, temp);
        node->value = temp;
        return newRoot;
    }
  
    else                                                  //if inorder successor does not exist, the left child takes the position of the node to be deleted
    {
        treeNode* Parent = parent(root, node);
        if(!Parent)
            root = node->leftNode;
        else
            Parent->rightNode = node->leftNode;
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

//works
treeNode* rotate(treeNode* bt,treeNode* x, treeNode* y, treeNode* z) {
  treeNode *a, *b, *c, *t0, *t1, *t2, *t3;
  a = max(x,y);                                           //logic of rotate implemented exactly as given in link in lab sheet
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

//works
treeNode* addAVL(treeNode* t, int val)
{
  treeNode *x, *y, *z;
  Height(t);
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
			if(h>1) //if point of imabalnce                    //different rotate cases(case number followed as given in link)
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

//works
treeNode* deleteCases(treeNode* t, treeNode* node){       //function to balance tree after deleting. Balances from point of imbalance till root
	treeNode *x, *y, *z;
  Height(t);
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

//works
treeNode* deleteAVL(treeNode* t, int val)
{
	treeNode* f = find(t,val);
		
	if(f==NULL)
		return t;

	if(f->rightNode==NULL && f->leftNode==NULL)             //leaf node 
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

	else if(f->rightNode==NULL)                     //has only left child then the child takes the position of the delted node and then the tree is balanced using deleteCases function.
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

	else if(f->leftNode==NULL)                //has only right child then the child takes the position of the delted node and then the tree is balanced using deleteCases function.
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

	else{                           //if both children exist, inorder successor is found and then balanced 

		treeNode* temp = inOrderSuccessor(f,t);
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
