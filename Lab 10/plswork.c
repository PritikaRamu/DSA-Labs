#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
  struct treeNode* left;
  struct treeNode* right;
  int element;
  int heightBalance;
} TreeNode;

typedef struct tree {
  TreeNode* root;
  int size;
} Tree;

void printTree(TreeNode* root){
    if(root==NULL){
        printf("NULL ");
        return;
    }
    printTree(root->left);
    printf("%d ", root->element);
    printTree(root->right);
}

TreeNode* newNode(int v) {
  TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode)); 
  // printf("%d ",v);
  t->left = NULL;
  t->right = NULL;
  t->heightBalance = 0;
  t->element = v;
  // printf("%d ",t->value);
  return t;
}

Tree createTree() {
  Tree temp;
  temp.root = NULL;
  temp.size = 0;
  return temp;
}


int height(TreeNode* root) {
  int heightLeft = 0;
  int heightRight = 0;
  if(root == NULL) {
    return 0;
  }
  if(root->left == NULL) {
    heightLeft = 0;
  }
  else {
    heightLeft = height(root->left);
  }
  if(root->right == NULL) {
    heightRight = 0;
  }
  else {
    heightRight = height(root->right);
  }
  return (heightLeft > heightRight) ? (heightLeft + 1) : (heightRight + 1);
}

TreeNode* add(TreeNode* root, int x) {
    if(root == NULL) return newNode(x);
    else {
        if(root->element >= x) add(root->left, x);
        else add(root->right, x);
    }
    return root;
}

TreeNode* minValueNode(TreeNode* root) {
    if(root->left == NULL) {
        return root;
    }
    else {
        return minValueNode(root->left);
    }
}

TreeNode* delete(TreeNode* root, int x) {
    if(root == NULL) return root;
    if(root->element > x) return delete(root->left, x);
    else if(root->element < x) return delete(root->right, x);
    else {
        if(root->left == NULL) {
            TreeNode* tempNode = root->right;
            free(root);
            return tempNode;
        }
        else if(root->right == NULL) {
            TreeNode* tempNode = root->left;
            free(root);
            return tempNode;
        }
        else {
            TreeNode* tempNode = minValueNode(root->right);
            root->element = tempNode->element;
            root->right = delete(root->right, tempNode->element);
        }
    }
    return root;
}

TreeNode* getParent(TreeNode* root,TreeNode* node) {
  if(node == NULL) {
    return NULL;
  }
  if(root == NULL) {
    return NULL;
  }
  if(node->element<=root->element) {
    if(root->left == node) {
      return root;
    }
    else {
      return getParent(root->left,node);
    }
  }
  else {
    if(root->right == node) {
      return root;
    }
    else {
      return getParent(root->right,node);
    }
  }
}

TreeNode* rotate(TreeNode* root,TreeNode* x, TreeNode* y, TreeNode* z) {
  TreeNode *a, *b, *c, *t0, *t1, *t2, *t3;
  a = x;
  if(y->element < a->element) {
    a = y;
  }
  if(z->element < a->element) {
    a = z;
  }
  // printf("%d a\n", a->element);

  c = x;
  if(y->element >= c->element) {
    c = y;
  }
  if(z->element >= c->element) {
    c = z;
  }
  // printf("%d c\n", c->element);

  if(x!=a&&x!=c) {
    b = x;
  }
  else if(y!=a&&y!=c) {
    b = y;
  }
  else {
    c = z;
  }
  // printf("%d b\n", b->element);

  t0 = a->left;
  if(b->left != a) {
    t1 = b->left;
  }
  else {
    t1 = a->right;
  }
  if(b->right == c) {
    t2 = c->left;
  }
  else {
    t2 = b->right;
  }
  t3 = c->right;

  b->left = a;
  b->right = c;
  a->left = t0;
  a->right = t1;
  c->left = t2;
  c->right = t3;

  TreeNode* parent = getParent(root,z);
  // printf("parent %d\n",parent->element);
  if(z->element > parent->element) {
    parent->right = b;
    // printf("parent->right %d\n",parent->right->element);
  }
  else {
    parent->left = b;
    // printf("parent->left %d\n",parent->left->element);
  }
  return b;
}

void setHeightBalance(TreeNode* root) {
  if(root == NULL) {
    return;
  }
  //printf("root element:%d\n",root->element);
  root->heightBalance = height(root->right) - height(root->left); 
  //printf("root->heightBalance: %d\n",root->heightBalance);
}

void makeAVL(TreeNode* root) {
  setHeightBalance(root);
  if(root->left != NULL) {
    makeAVL(root->left);
  }
  if(root->right != NULL) {
    makeAVL(root->right);
  }
}

TreeNode* addAVL(int element, TreeNode* root, TreeNode* permRoot) {
  TreeNode* resNode;
  int isLeft = 1;
  if(root == NULL) {
    printf("%d successfully added!\n",element);
    root = newNode(element);
    return root;
  }
  makeAVL(permRoot);
  // printf("\n%d root element\n",root->element);
  if(element <= root->element) {
    resNode = root->left;
  }
  else {
    resNode = root->right;
    isLeft = 0;
  }
  if(resNode == NULL) {
    resNode = newNode(element);
    printf("%d successfully added!\n",element);
    (isLeft == 1) ? (root->left = resNode) : (root->right = resNode);
  }
  else {
    if(isLeft == 1) {
      root->left = addAVL(element,resNode,permRoot);
      makeAVL(permRoot);
      if(root->heightBalance > 1 || root->heightBalance < -1) {
        TreeNode *x,*y,*z;
        z = root;
        y = root->left;
        x = (root->left->heightBalance) > 0 ? root->left->right : root->left->left;
        // printf("rotate called. \n\n");
        // printf("z %d y %d x %d\n\n",z->element,y->element,x->element);
        // printf("%d \n",root->element);
        root = rotate(permRoot,x,y,z);
        // printf("\n\n");
      }
    }
    else {
      root->right = addAVL(element,resNode,permRoot);
      makeAVL(permRoot);
      if(root->heightBalance > 1 || root->heightBalance < -1) {
        TreeNode *x,*y,*z;
        z = root;
        y = root->right;
        x = (root->right->heightBalance) > 0 ? root->right->right : root->right->left;
        // printf("rotate called. \n\n");
        // printf("z %d y %d x %d\n\n",z->element,y->element,x->element);
        root = rotate(permRoot,x,y,z);
      }
    }
  }
  return root;
}


TreeNode* find(int element, TreeNode* root) {
  if(root == NULL) {
    return NULL;
  }
  // printf("%d\n",root->element);
  if(root->element == element) {
    return root;
  }
  else if(element < root->element) {
    return find(element,root->left);
  }
  else {
    return find(element,root->right);
  }
}

TreeNode* deleteAVL(TreeNode* permRoot,TreeNode* root,int element) {
  if(root == NULL) {
    return root;
  }
  printf("%d\n",root->element);
  if(element < root->element) {
    root->left = deleteAVL(permRoot,root->left,element);
  }
  else if(element > root->element) {
    root->right = deleteAVL(permRoot,root->right,element);
  }
  else {
    if(root->left == NULL) {
      TreeNode* temp = root->right;
      free(root);
      root = temp;
      return root;
    }
    else if(root->right == NULL) {
      TreeNode* temp = root->left;
      free(root);
      root = temp;
      return root;
    }
    TreeNode* tempo = minValueNode(root->right);
    root->element = tempo->element;
    root->right = deleteAVL(permRoot,root->right, tempo->element);
  }
  makeAVL(permRoot);
  if(root->heightBalance > 1 || root->heightBalance < -1) {
    TreeNode* z = root;
    TreeNode* y = root->heightBalance > 0 ? root->right : root->left;
    TreeNode* x = y->heightBalance > 0 ? y->right : y->left;
    TreeNode* parent = getParent(permRoot,root);
    if(parent == NULL) {
      root = rotate(permRoot,x,y,z);
    }
    else {
      if(root->element <= parent->element) {
        parent->left = rotate(permRoot,x,y,z);
      }
      else {
        parent->right = rotate(permRoot,x,y,z);
      }
    }
  }

  return root;
}


int main() {
  Tree avlTree = createTree();
  avlTree.root = addAVL(64,avlTree.root,avlTree.root);
  avlTree.root = addAVL(37,avlTree.root,avlTree.root);
  avlTree.root = addAVL(79,avlTree.root,avlTree.root);
  avlTree.root = addAVL(30,avlTree.root,avlTree.root);
  avlTree.root = addAVL(85,avlTree.root,avlTree.root);
  avlTree.root = addAVL(68,avlTree.root,avlTree.root);
  avlTree.root = addAVL(21,avlTree.root,avlTree.root);
  avlTree.root = addAVL(34,avlTree.root,avlTree.root);
  printf("The height of the tree is %d\n\n\n",height(avlTree.root));
  makeAVL(avlTree.root);
  avlTree.root = deleteAVL(avlTree.root,avlTree.root,79);
  printf("The height of the tree is %d\n\n\n",height(avlTree.root));
  makeAVL(avlTree.root);
}