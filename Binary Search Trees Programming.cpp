#include <iostream>
#include <algorithm> // For std::max and std::abs
using namespace std;


struct llnode {
  int data;
  struct llnode* next;
};
typedef struct llnode LLnode;

class LinkList {
private:
  LLnode* head;
  LLnode* tail;
public:
  LinkList() : head(nullptr), tail(nullptr) {}
  void add(int val);
  void print();
  void ll2binTree();
};

void LinkList::add(int val)
{
  if (head == nullptr) {
    head = tail = new LLnode;
    head->next = nullptr;
    tail->next = nullptr;
    head->data = val;
  }
  else {
    tail->next = new LLnode;
    tail = tail->next;
    tail->data = val;
    tail->next = nullptr;
  }
}

void LinkList::print()
{
  LLnode* temp = head;

  while (temp) {
    std::cout << temp->data << std::endl;
    temp = temp->next;
  }
}

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// Helper to get the height of a node (returns 0 for a null pointer)
int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Helper to update the height of a node (Max height of children + 1)
void update_height(Node* N) {
    if (N != nullptr) {
        N->height = 1 + std::max(height(N->left), height(N->right));
    }
}

// Helper function to get the balance factor of a node
int get_balance(Node* n) {
    if (n == nullptr) return 0;
    return height(n->left) - height(n->right);
}

Node* rotate_left(Node* Z) {
    Node* Y = Z->right;    // Y is the right child of Z (the pivot)
    Node* T2 = Y->left;    // T2 is the left subtree of Y (the subtree that moves)

    // Perform the rotation
    Y->left = Z;    // Z becomes the left child of Y
    Z->right = T2;  // T2 becomes the right child of Z

    // Update heights
    update_height(Z);  // Z is now lower in the tree, so its height must be updated first.
    update_height(Y);  // Y is the new root of the subtree, update its height last.

    // Return the new root
    return Y;
}

Node* rotate_right(Node* Z) {
    // Z is the unbalanced node
    Node* Y  = Z->left;   // Y is the pivot (new root)
    Node* T3 = Y->right;  // T3 is the subtree that moves

    // Perform the rotation
    Y->right = Z;
    Z->left  = T3;

    // Update heights (bottom-up)
    update_height(Z);
    update_height(Y);

    return Y; // Y is the new root of the subtree
}

// Left-Right Rotation (LR Case)
Node* rotate_left_right(Node* Z) {
    // Z is the critical node
    // Step 1: Left Rotate the left child (Y)
    Z->left = rotate_left(Z->left);
   
    // Step 2: Right Rotate Z
    return rotate_right(Z);
}

// Right-Left Rotation (RL Case)
Node* rotate_right_left(Node* Z) {
    // Z is the critical node
    // Right Rotate the right child (Y)
    Z->right = rotate_right(Z->right);

    // Step 2: Left Rotate Z
    return rotate_left(Z);
}

Node* insert(Node* node, int val) {
    // 1. STANDARD BST INSERTION (Base Case)
    if (node == nullptr) {
        return new Node(val);
    }

    if (val < node->data) {
        node->left = insert(node->left, val);
    } else if (val > node->data) {
        node->right = insert(node->right, val);
    } else {
        // Equal keys are generally not allowed in BSTs/AVLs (or simply ignored)
        return node;
    }

    // 2. UPDATE HEIGHT of the current node after recursion returns
    update_height(node);

    // 3. GET BALANCE FACTOR to check for imbalance
    int balance = get_balance(node);

    // 4. PERFORM ROTATION (Rebalancing Cases)

    // --- Left Heavy Imbalance (BF = +2) ---
    if (balance > 1) {
        // a) LL Case: Inserted node is in the left subtree of the left child
        if (val < node->left->data) {
            return rotate_right(node); // Single Right Rotation
        }
        // b) LR Case: Inserted node is in the right subtree of the left child
        if (val > node->left->data) {
            return rotate_left_right(node); // Double Rotation
        }
    }

    // --- Right Heavy Imbalance (BF = -2) ---
    if (balance < -1) {
        // c) RR Case: Inserted node is in the right subtree of the right child
        if (val > node->right->data) {
            return rotate_left(node); // Single Left Rotation
        }
        // d) RL Case: Inserted node is in the left subtree of the right child
        if (val < node->right->data) {
            return rotate_right_left(node); // Double Rotation
        }
    }

    // 5. RETURN UNCHANGED NODE if it was balanced (BF is -1, 0, or 1)
    return node;
}

void inOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    // 1. Recurse on the Left subtree
    inOrderTraversal(root->left);

    // 2. Print the Root's data
    std::cout << root->data << " ";

    // 3. Recurse on the Right subtree
    inOrderTraversal(root->right);
}

void inOrderTraversal2LL(Node* root, LinkList& ll) {
    if (root == nullptr) {
        return;
    }
    // 1. Recurse on the Left subtree
    inOrderTraversal2LL(root->left, ll);

    // 2. Print the Root's data
	ll.add(root->data);

    // 3. Recurse on the Right subtree
    inOrderTraversal2LL(root->right, ll);
}

void preOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    // 1. Print the Root's data
    std::cout << root->data << " ";

    // 2. Recurse on the Left subtree
    preOrderTraversal(root->left);

    // 3. Recurse on the Right subtree
    preOrderTraversal(root->right);
}


//q2:
void LinkList::ll2binTree(){
    LLnode* current = head;
    Node* root = nullptr; 
    while(current != nullptr){
          root = insert(root, current->data);
          current = current->next;
    }
    cout << "Inorder: ";
    inOrderTraversal(root);
    cout << endl;
}



int main() {
    LinkList ll;
    Node* root = nullptr;

    ////////////     Q1     /////////////
    // Create a BST with some values:
    //   Insert 10, 5, 2 (Forces LL Case -> rotate_right)
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 2);
    inOrderTraversal(root);
    std::cout << std::endl;
    preOrderTraversal(root);
    std::cout << "\n";
    // Tree: 5 (Root), 2 (L), 10 (R) - Balanced

    std::cout << "Sorted LinkList\n";
    ////   Homework Q1  ////
    // Pass in BST (root) and empty LinkList (ll)
    inOrderTraversal2LL(root, ll);
    // LinkList ll now has the sorted values, print them:
    ll.print();

    std::cout << std::endl << std::endl;

    // Add some more vvalues to the BST to trigger rotate cases.
    //   Insert 30, 40 (Forces RR Case at 10 -> rotate_left)
    root = insert(root, 30);
    root = insert(root, 40);
    inOrderTraversal(root);
    std::cout << std::endl;
    preOrderTraversal(root);
    // After 40 insertion, 10 is unbalanced. rotate_left at 10.
    // Tree: ... 30 (Root of 30-40 subtree), 40 (R)

    std::cout << "Root after all insertions: "
     << root->data << " (Expected 5)" << std::endl;

    ////////////     Q2     /////////////

    LinkList ll2;
    ll2.add(1);
    ll2.add(4);
    ll2.add(3);
    ll2.add(2);

    ll2.ll2binTree();



    return 0;
}

// question 3


bool mirrorHelper(binTree::bnode* a, binTree::bnode* b) {
    // both empty meaning mirrors
    if (a == nullptr && b == nullptr) return true;

    // one empty, one not meaning not mirrors
    if (a == nullptr || b == nullptr) return false;

    // values must match
    // left of A mirrors right of B
    // right of A mirrors left of B
    return (a->data() == b->data()) &&
           mirrorHelper(a->left(), b->right()) &&
           mirrorHelper(a->right(), b->left());
}

bool areMirrors(const binTree& T1, const binTree& T2) {
    return mirrorHelper(T1._root, T2._root);
}

// question 4

int checkHeight(binTree::bnode* p, bool& ok) {
    if (p == nullptr) return 0;

    int lh = checkHeight(p->left(), ok);
    int rh = checkHeight(p->right(), ok);

    // if difference > 1, mark tree as unbalanced
    if (abs(lh - rh) > 1) ok = false;

    return 1 + max(lh, rh);
}

bool isBalanced(const binTree& T) {
    bool ok = true;
    checkHeight(T._root, ok);
    return ok;
}

