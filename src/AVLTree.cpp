#include "AVLTree.h"

AVLTree::Node::Node(Student student) {
    this->student = student;
    left = nullptr;
    right = nullptr;
    height = 1;
}

AVLTree::Node *AVLTree::rotateRight(AVLTree::Node* root) {
    Node* grandchild = root->left->right;
    Node* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;

    // Update root heights
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;
    return newParent;
}

AVLTree::Node *AVLTree::rotateLeft(AVLTree::Node* root) {
    Node* grandchild = root->right->left;
    Node* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    // Update root heights
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;
    return newParent;
}

int AVLTree::getBalanceFactor(AVLTree::Node* root) {
    return getHeight(root->left) - getHeight(root->right);
}

int AVLTree::getHeight(AVLTree::Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return 1 + max(getHeight(root->left), getHeight(root->right));
}

AVLTree::Node *AVLTree::insertNode(AVLTree::Node *root, Student student) {
    if (root == nullptr) {
        root = new Node(student);
    }
    else if (stoi(student.getID()) < stoi(root->student.getID())) {
        root->left = insertNode(root->left, student);
    }
    else {
        root->right = insertNode(root->right, student);
    }

    // If tree is right heavy
    if (getBalanceFactor(root) < -1) {
        // If tree's right subtree is left heavy
        if (getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        else {
            return rotateLeft(root);
        }
    }

    // If tree is left heavy
    else if (getBalanceFactor(root) > 1) {
        // If tree's left subtree is right heavy
        if (getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        else {
            return rotateRight(root);
        }
    }

    return root;
}

AVLTree::Node *AVLTree::deleteNode(AVLTree::Node *root, string ID) {
    if (root == nullptr) {
        return root;
    }

    // Find the root to be deleted
    if (stoi(ID) < stoi(root->student.getID())) {
        root->left = deleteNode(root->left, ID);
    }
    else if (stoi(ID) > stoi(root->student.getID())) {
        root->right = deleteNode(root->right, ID);
    }
    else {
        // Node with only one child or no child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder predecessor (rightmost in the left subtree)
        Node* temp = root->left;
        while (temp->right != nullptr) {
            temp = temp->right;
        }

        // Copy the inorder predecessor's content to this root and delete the inorder predecessor
        root->student = temp->student;
        root->left = deleteNode(root->left, temp->student.getID());
    }

    // Update height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Perform rotations if necessary
    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rotateRight(root);
    }

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return rotateLeft(root);
    }

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

string AVLTree::stringInOrder(AVLTree::Node *root) {
    string inOrderTraversal;

    if (root == nullptr) {
        return "";
    }

    // LNR
    inOrderTraversal += stringInOrder(root->left);
    inOrderTraversal += root->student.getName() + ",";
    inOrderTraversal += stringInOrder(root->right);

    return inOrderTraversal;
}

string AVLTree::stringPreOrder(AVLTree::Node *root) {
    string preOrderTraversal;

    if (root == nullptr) {
        return "";
    }

    // NLR
    preOrderTraversal += root->student.getName() + ",";
    preOrderTraversal += stringPreOrder(root->left);
    preOrderTraversal += stringPreOrder(root->right);

    return preOrderTraversal;
}

string AVLTree::stringPostOrder(AVLTree::Node *root) {
    string postOrderTraversal;

    if (root == nullptr) {
        return "";
    }

    // LRN
    postOrderTraversal += stringPostOrder(root->left);
    postOrderTraversal += stringPostOrder(root->right);
    postOrderTraversal += root->student.getName() + ",";

    return postOrderTraversal;
}


AVLTree::AVLTree() {
    head = nullptr;
}

void AVLTree::insert(string name, string ID) {
    Student newStudent = Student(name,ID);
    head = insertNode(head, newStudent);
}

void AVLTree::remove(string ID) {
    head = deleteNode(head, ID);
}

void AVLTree::searchID(string ID) {
    Node* current = head;

    while (current != nullptr) {
        int currentID = stoi(current->student.getID());

        if (currentID == stoi(ID)) {
            cout << current->student.getName() << endl;
            return;
        }
        else if (stoi(ID) < currentID) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    cout << "unsuccessful" << endl;
}

void AVLTree::searchName(string name) {
    searchNameHelper(head, name);
}

void AVLTree::searchNameHelper(AVLTree::Node *root, std::string name) {
    static bool found = false;

    if (root == nullptr) {
        if (!found) {
            cout << "unsuccessful" << endl;
        }
        return;
    }

    if (root->student.getName() == name) {
        cout << root->student.getID() << endl;
        found = true;
    }

    searchNameHelper(root->left, name);
    searchNameHelper(root->right, name);
}

void AVLTree::printInorder() {
    string inOrder = stringInOrder(head);
    cout << inOrder.substr(0, inOrder.length() - 1) << endl;
}

void AVLTree::printPreorder() {
    string preOrder = stringPreOrder(head);
    cout << preOrder.substr(0, preOrder.length() - 1) << endl;
}

void AVLTree::printPostorder() {
    string postOrder = stringPostOrder(head);
    cout << postOrder.substr(0, postOrder.length() - 1) << endl;
}

void AVLTree::printLevelCount() {
    cout << getHeight(head) << endl;
}

// Helper function for inorder removal which returns a vector of strings containing the inorder traversal
// of the IDs in the tree by reference
void AVLTree::fillInorder(Node* root, vector<string>& ids) {
    if (root == nullptr) {
        return;
    }
    fillInorder(root->left, ids);
    ids.push_back(root->student.getID());
    fillInorder(root->right, ids);
}

void AVLTree::removeInorder(int N) {
    vector<string> ids;
    fillInorder(head, ids);
    if (N >= 0 && N < ids.size()) {
        remove(ids[N]);
    }
}
