#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = right = nullptr;
    }
};

//Task 1: build tree from string
//Time: O(n), n = length of string
Node* buildTree(const string& s, int& i) {
    if (i >= (int)s.size() || s[i] == ',' || s[i] == ')')
        return nullptr;

    Node* root = new Node(s[i]);
    i++;

    if (i < (int)s.size() && s[i] == '(') {
        i++;   //skip (

        if (s[i] != ',')
            root->left = buildTree(s, i);

        if (s[i] == ',')
            i++;   //skip comma

        if (s[i] != ')')
            root->right = buildTree(s, i);

        if (s[i] == ')')
            i++;   //skip )
    }

    return root;
}

//Task 5: check the string without making the tree
//Time: O(n)
bool checkNode(const string& s, int& i) {
    if (i >= (int)s.size() || s[i] == '(' || s[i] == ')' || s[i] == ',')
        return false;

    i++;

    if (i < (int)s.size() && s[i] == '(') {
        i++;

        if (i < (int)s.size() && s[i] != ',') {
            if (!checkNode(s, i)) return false;
        }

        if (i >= (int)s.size() || s[i] != ',')
            return false;
        i++;

        if (i < (int)s.size() && s[i] != ')') {
            if (!checkNode(s, i)) return false;
        }

        if (i >= (int)s.size() || s[i] != ')')
            return false;
        i++;
    }

    return true;
}

bool isValid(const string& s) {
    if (s.empty()) return false;

    int i = 0;
    return checkNode(s, i) && i == (int)s.size();
}

//Task 2: preorder (recursive), printed in string format
//Time: O(n)
void preorder(Node* root) {
    if (!root) return;

    cout<<root->data;

    if (root->left || root->right) {
        cout<<"(";
        preorder(root->left);
        cout<<",";
        preorder(root->right);
        cout<<")";
    }
}

//Task 3: inorder using a stack
//Time: O(n)
void inorder(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        cout<<current->data;
        current = current->right;
    }
}

//Task 4: postorder using two stacks
//Time: O(n)
void postorder(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }

    while (!s2.empty()) {
        cout<<s2.top()->data;
        s2.pop();
    }
}

//Task 6: height (counted in levels)
//Time: O(n)
int height(Node* root) {
    if (!root) return 0;

    int l = height(root->left);
    int r = height(root->right);

    if (l > r) return l + 1;
    return r + 1;
}

//Task 6: depth of each node (root = 0)
//Time: O(n)
void showDepth(Node* root, int depth) {
    if (!root) return;

    cout<<root->data << " : depth " << depth <<endl;
    showDepth(root->left, depth + 1);
    showDepth(root->right, depth + 1);
}

//Task 7: BST
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) {
        data = value;
        left = right = nullptr;
    }
};

//Time: O(h), average O(log n), worst O(n)
BSTNode* insertBST(BSTNode* root, int value) {
    if (!root) return new BSTNode(value);

    if (value < root->data)
        root->left = insertBST(root->left, value);
    else if (value > root->data)
        root->right = insertBST(root->right, value);

    return root;
}

//inorder of BST gives sorted order
//Time: O(n)
void showBST(BSTNode* root) {
    if (!root) return;

    showBST(root->left);
    cout<<root->data << " ";
    showBST(root->right);
}

int main() {
    string text = "a(b(d,e),c(,f(g,)))";

    cout<<"Tree string: " << text <<endl;

    if (isValid(text))
        cout<<"Validation: Valid" <<endl;
    else {
        cout<<"Validation: Invalid" <<endl;
        return 0;
    }

    int index = 0;
    Node* root = buildTree(text, index);

    cout<<" \n Preorder: ";
    preorder(root);

    cout<<" \nInorder: ";
    inorder(root);

    cout<<" \n Postorder: ";
    postorder(root);

    cout<<" \n\nHeight: " << height(root) << " levels" <<endl;

    cout<<"Node depths:" <<endl;
    showDepth(root, 0);

    //Task 7
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    BSTNode* bst = nullptr;

    for (int i = 0; i < 7; i++)
        bst = insertBST(bst, values[i]);

    cout<<" \n BST inorder: ";
    showBST(bst);
    cout<<endl;

    return 0;
}