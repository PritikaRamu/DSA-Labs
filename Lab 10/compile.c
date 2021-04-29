#include<stdio.h>
#include<stdlib.h>

typedef struct node TreeNode;
struct node
{
    int key;
    TreeNode* left;
    TreeNode* right;
    int balfactor;
} treenode;

TreeNode* newNode(int val)
{
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = val;
    temp->left = NULL;
    temp->right = NULL;
    temp->balfactor = 0;
    return temp;
}

int getHeightLeft(TreeNode *node)
{
    if (node == NULL)
        return -1;
    return getHeightLeft(node->left)+1;
}

int getHeightRight(TreeNode *node)
{
    if (node == NULL)
        return -1;
    return getHeightRight(node->right)+1;
}

TreeNode* add(TreeNode* root, int val){
    if(root == NULL) { // tree has no root
        return newNode(val);
    }

    TreeNode* curr = root;
    TreeNode* new = newNode(val);

    while((val < curr->key && curr->left != NULL) || (val > curr->key && curr->right != NULL)){
        if(val < curr->key) curr = curr->left;
        else if(val > curr->key) curr = curr->right;
    }
    if(val < curr->key) curr->left = new;
    else if(val > curr->key) curr->right = new;
    return root;
}

TreeNode* find(TreeNode* root, int val){
    if(root->key == val) return root;
    TreeNode* curr = root;

    while(curr != NULL){
        if(curr->key == val) return curr;
        else if(val < curr->key) curr = curr->left;
        else if(val > curr->key) curr = curr->right;
    }

    return NULL;
}

TreeNode* findParent(TreeNode* root, int val){
    if(root->key == val) return NULL;
    TreeNode* curr = root;

    while(curr->left != NULL || curr->right != NULL){
        if((curr->left != NULL && curr->left->key == val) || (curr->right != NULL && curr->right->key == val)) return curr;
        else if(curr->left != NULL && val < curr->key) curr = curr->left;
        else if(curr->right != NULL && val > curr->key) curr = curr->right;
    }

    return NULL;
}

void printInOrder(TreeNode* node){
    if(node != NULL){
        printInOrder(node->left);
        printf("%d ", node->key);
        printInOrder(node->right);
    }
}

TreeNode* minElementNode(TreeNode* node)
{
	while (node->left != NULL)
		node = node->left;
	return node;
}

TreeNode *findSuccessor(TreeNode *root, TreeNode *node)
{
    if (node->right != NULL)
        return minElementNode(node->right);

    TreeNode *parent = findParent(root, node->key);
    while (parent != NULL && node == parent->right)
    {
        node = parent;
        parent = findParent(root, node->key);
    }
    return parent;
}

TreeNode* deleteWithoutBalance(TreeNode* root, int val)
{
    TreeNode* fNode = find(root, val);
    if(!fNode)
    {
        printf("Cannot delete %d as it does not exist.\n", val);
        return root;
    }

    //Node is a leaf
    if(fNode->left == NULL && fNode->right == NULL){
        TreeNode* parent = findParent(root, val);

        if(!parent)
        {
            free(fNode);
            return NULL;
        }
        if(parent->right == fNode)
           parent->right = NULL;
        else if(parent->left = fNode)
           parent->left = NULL;
        free(fNode);
        return root;
    }

    //Node to be deleted is internal node and inorder successor exists
    TreeNode *successor = findSuccessor(root, fNode);
    if (successor)
    {
        int temp = successor->key;
        TreeNode *newRoot = deleteWithoutBalance(root, temp);
        fNode->key = temp;
        return newRoot;
    }
    //Node to be deleted is internal node and inorder successor does not exist
    else
    {
        TreeNode *parent = findParent(root, fNode->key);
        if(!parent)
            root = fNode->left;
        else
            parent->right = fNode->left;
        free(fNode);
        return root;
    }

}

int getBalance(TreeNode *node)
{
    if (node == NULL)
        return 0;
    return getHeightRight(node) - getHeightLeft(node);
}

TreeNode* rotate(TreeNode *root, TreeNode *x, TreeNode *y, TreeNode *z){
    TreeNode *a, *b, *c, *t0, *t1, *t2, *t3;
    if (z->left == y && y->left == x)
    {
        a = x;
        b = y;
        c = z;
        t1 = a->right;
        t2 = b->right;
    }
    else if (z->right == y && y->right == x)
    {
        a = z;
        b = y;
        c = x;
        t1 = b->left;
        t2 = c->left;
    }
    else if (z->right == y && y->left == x)
    {
        a = z;
        b = x;
        c = y;
        t1 = b->left;
        t2 = b->right;
    }
    else if (z->left == y && y->right == x)
    {
        a = y;
        b = x;
        c = z;
        t1 = b->left;
        t2 = b->right;
    }
    t0 = a->left;
    t3 = c->right;

    TreeNode *parent = findParent(root, z->key);
    if (!parent)
        root = b;
    else if (parent->left == z)
        parent->left = b;
    else
        parent->right = b;

    b->left = a;
    b->right = c;
    a->left = t0;
    a->right = t1;
    c->left = t2;
    c->right = t3;

    a->balfactor = getBalance(a);
    b->balfactor = getBalance(b);
    c->balfactor = getBalance(c);
    return root;

}

TreeNode* addAVL(TreeNode* root, TreeNode* node, int val){

    /* 1.  Perform the normal BST insertion */
    if (node == NULL){
        if(root == NULL)
        {
            root = newNode(val);
            return root;
        }
        return(newNode(val));
    }

    if (val < node->key){
        node->left  = addAVL(root, node->left, val);
    }
    else if (val > node->key){
        node->right = addAVL(root, node->right, val);
    }
    else // Equal vals are not allowed in BST
        return node;

    node->balfactor = getBalance(node);

    if (node->balfactor < -1){
        // Left Left Case
        if(val < node->left->key) return rotate(root, node->left->left, node->left, node);

        //Left Right Case
        if(val > node->left->key) return rotate(root, node->left->right, node->left, node);

    }

    if (node->balfactor > 1){

        //Right Right Case
        if(val > node->right->key) return rotate(root, node->right->right, node->right, node);

        // Right Left Case
        if(val < node->right->key) return rotate(root, node->right->left, node->right, node);
    }

    /* return the (unchanged) node pointer */
    return node;

}



TreeNode* deleteAVL(TreeNode* root, TreeNode* node, int val){
	if (node == NULL)
		return node;

	// If the val to be deleted is smaller than the root's val, then it lies in left subtree
	if ( val < node->key )
		node->left = deleteAVL(root, node->left, val);

	// If the val to be deleted is greater than the root's val, then it lies in right subtree
	else if( val > node->key )
		node->right = deleteAVL(root, node->right, val);

	else {
		// node with only one child or no child
		if( (node->left == NULL) || (node->right == NULL) ) {
			TreeNode *temp = node->left ? node->left : node->right;
			// No child
			if (temp == NULL) {
				temp = node;
				node = NULL;
			}
			else
            {
                // One child
                TreeNode* parent = findParent(node, temp->key);
			    node->key = temp->key;

                if(!parent) return NULL;
                if(parent->right == temp) parent->right = NULL;
                else if(parent->left = temp) parent->left = NULL;
            }
			free(temp);
		}
		else
        {
			TreeNode* temp = minElementNode(node->right);
            if(!temp) return NULL;
			node->key = temp->key;
			node->right = deleteAVL(root, node->right, temp->key);
		}
	}

	// Single node
	if (node == NULL)
	return node;

	node->balfactor = getBalance(node);

	// If this node becomes unbalfactord, then there are 4 cases

	// Left Left Case
	if (node->balfactor < -1 && node->left->balfactor <= 0) return rotate(root, node->left->left, node->left, node);

	// Left Right Case
	if (node->balfactor < -1 && node->left->balfactor > 0) return rotate(root, node->left->right, node->left, node);

	// Right Right Case
	if (node->balfactor > 1 && node->right->balfactor >= 0) return rotate(root, node->right->right, node->right, node);

	// Right Left Case
	if (node->balfactor > 1 && node->right->balfactor < 0) return rotate(root, node->right->left, node->right, node);

	return node;

}

int main(){
    TreeNode* root = NULL;
    int values[] = {8, 7, 6, 5, 10};

    for(int i=0; i<sizeof(values)/sizeof(int); i++){
        root = addAVL(root, root, values[i]);
    }

    printf("Initial tree - \n");

    printInOrder(root);
    printf("\n");

    int toBeDeleted = 8;

    printf("Tree after deleting %d - \n", toBeDeleted);
    root = deleteAVL(root, root, toBeDeleted);
    printInOrder(root);
    printf("\n");

    return 0;
}
