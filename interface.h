#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(string name, MetroLine* metroLine, int fare);

    // Getter methods
    string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(string name, MetroLine* metroLine, int fare) {
    stopName = name;
    this->nextStop = nullptr;
    this->prevStop = nullptr;
    this->line = metroLine;
    this->fare = fare;
}

string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    string lineName;
    MetroStop* node;

public:
    MetroLine(string name);

    // Getter methods
    string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(string name) {
    lineName = name;
    node = nullptr;
}

string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    MetroStop* stop = node;
    int count = 0;
    while (stop != nullptr) {
        count++;
        stop = stop->getNextStop();
    }
    return count;
}

void MetroLine::populateLine(string filename) {
    // Read the file and populate the line

    string lineName = filename.substr(0, filename.length() - 4);

    // Open the file
    ifstream inputFile(filename);

    // Check if the file is open
    if (!inputFile.is_open()) {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }

    string line;

    getline(inputFile, line);
    istringstream lineStream(line);
    string word,stop_name = "";
    vector<string> words;
    int no_of_words = 0;
    // Read each word separated by spaces
    while (lineStream >> word) {
        words.push_back(word);
        no_of_words++;
    }
    stop_name = words[0];
    for (int i = 1; i < no_of_words-1; i++) {
        stop_name += " " + words[i] ;
    }
    int fare = stoi(words[no_of_words - 1]);
    MetroStop *node = new MetroStop(stop_name,this,fare);
    this->node = node;

    // Read the file line by line
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        string word,stop_name = "";
        vector<string> words;
        int no_of_words = 0;
        // Read each word separated by spaces
        while (lineStream >> word) {
            words.push_back(word);
            no_of_words++;
        }
        stop_name = words[0];
        for (int i = 1; i < no_of_words-1; i++) {
            stop_name += " " + words[i];
        }
        int fare = stoi(words[no_of_words - 1]);
        MetroStop *new_node = new MetroStop(stop_name,this,fare);
        node->setNextStop(new_node);
        new_node->setPrevStop(node);
        node = node->getNextStop();
    }

    // Close the file
    inputFile.close();
}

// AVLNode class
class AVLNode {
private:
    string stopName;
    int height;
    vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(string name);

    // Getter methods
    string getStopName() const;
    const vector<MetroStop*>& getStops() const; 
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;
    int getHeight() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
    void setHeight(int height);
};

AVLNode::AVLNode(string name) {
    stopName = name;
    height = 1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

string AVLNode::getStopName() const {
    return stopName;
}

const vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

int AVLNode::getHeight() const {
    return height;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::setHeight(int height) {
    this->height = height;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    AVLNode* insert(AVLNode* node, AVLNode* parent_node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    void preOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
    AVLNode* searchStop_byNode(AVLNode* node, string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node==nullptr)
        return 0;
    return node->getHeight();
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    delete[] c1; // Free the allocated memory
    delete[] c2; // Free the allocated memory
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    if(node == nullptr) {
        return 0;
    }
    return this->height(node->getLeft()) - this->height(node->getRight());
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode *y = x->getRight();
    AVLNode *T2 = y->getLeft();

    // perform rotation
    y->setLeft(x);
    x->setRight(T2);

    // update parents
    y->setParent(x->getParent());
    x->setParent(y);
    if(T2 != nullptr)
        T2->setParent(x);

    // update heights
    y->setHeight(max(this->height(y->getLeft()),this->height(y->getRight()))+1);
    x->setHeight(max(this->height(x->getLeft()),this->height(x->getRight()))+1);

    return y;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode *x = y->getLeft();
    AVLNode *T2 = x->getRight();

    // perform rotation
    x->setRight(y);
    y->setLeft(T2);

    // update parents
    x->setParent(y->getParent());
    y->setParent(x);
    if(T2 != nullptr)
        T2->setParent(y);

    // update heights
    y->setHeight(max(this->height(y->getLeft()),this->height(y->getRight()))+1);
    x->setHeight(max(this->height(x->getLeft()),this->height(x->getRight()))+1);

    return x;
}

void AVLTree::balance(AVLNode* node) {
}

AVLNode* AVLTree::insert(AVLNode* node, AVLNode* parent_node, MetroStop* metroStop) {
    /* 1. Perform the normal BST insertion */
    // base case
    if (node == NULL) 
    {
        AVLNode *new_node = new AVLNode(metroStop->getStopName());
        new_node->setParent(parent_node);
        // new_node->parent = parent_node;
        new_node->addMetroStop(metroStop);
        return new_node;
    }

    int key = this->stringCompare(metroStop->getStopName(), node->getStopName());
    if (key < 0)
        node->setLeft(this->insert(node->getLeft(), node, metroStop));
        // node->left = insert(node->left, node, key); 
	else if (key > 0)
        node->setRight(this->insert(node->getRight(), node, metroStop));
        // node->right = insert(node->right, node, key); 
	else // Equal keys are not allowed in BST but here is its importance...
        {
            node->addMetroStop(metroStop);
            return node;
        }

    /* 2. Update height of this ancestor node */
    node->setHeight(1 + max(this->height(node->getLeft()), this->height(node->getRight())));

    /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
    int balance = this->balanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && this->stringCompare(metroStop->getStopName(), node->getLeft()->getStopName()) < 0)
        return this->rotateRight(node);

    // Right Right Case
    if (balance < -1 && this->stringCompare(metroStop->getStopName(), node->getRight()->getStopName()) > 0)
        return this->rotateLeft(node);

    // Left Right Case
    if (balance > 1 && this->stringCompare(metroStop->getStopName(), node->getLeft()->getStopName()) > 0)
    {
        node->setLeft(this->rotateLeft(node->getLeft()));
        return this->rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && this->stringCompare(metroStop->getStopName(),node->getRight()->getStopName())<0) {
        node->setRight(this->rotateRight(node->getRight()));
        return this->rotateLeft(node);
    }
        
    /* return the (unchanged) node pointer */
	return node; 
}

void AVLTree::populateTree(MetroLine* metroLine) {
    MetroStop *stop = metroLine->getNode();
    while(stop != nullptr)
    {
        this->setRoot(this->insert(this->getRoot(), nullptr, stop));
        stop = stop->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

void AVLTree::preOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    if(node->getStops().size()>1)
    cout << node->getStopName() << endl;
    preOrderTraversal(node->getLeft());
    preOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop_byNode(AVLNode* node , string stopName) {
    if(node == nullptr)
        return nullptr;
    if(node->getStopName() == stopName)
        return node;
    AVLNode *node1 = this->searchStop_byNode(node->getLeft(), stopName);
    AVLNode *node2 = this->searchStop_byNode(node->getRight(), stopName);
    if(node1!=nullptr)
        return node1;
    else
        return node2;
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode *node = this->getRoot();
    return this->searchStop_byNode(node,stopName);
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;
    char type; // 'F' for forward and 'B' for backward

public:
    Trip(MetroStop* metroStop, Trip* previousTrip , char type);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
    char getType() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip, char type) {
    node = metroStop;
    prev = previousTrip;
    this->type = type;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

char Trip::getType() const {
    return type;
}

class Path {
private:
    vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    int count = 0;
    for (auto stop : stops) {
        count++;
        cout << "Stop Name = " << stop->getStopName() << "  ,  Line Name = " << stop->getLine()->getLineName() << endl;
    }
    cout << endl
         << "total stops = " << count << endl;
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    vector<string> lines;

public:
    PathFinder(AVLTree* avlTree);
    // void createAVLTree();
    Path* findPath(string origin, string destination);

    // Getter methods
    AVLTree* getTree() const;
    void setLines(string line);
    const vector<string>& getLines() const;
    bool checkLine(string line);
};

PathFinder::PathFinder(AVLTree* avlTree) {
    tree = avlTree;
    // lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

void PathFinder::setLines(string line) {
    lines.push_back(line);
}

const vector<string>& PathFinder::getLines() const {
    return lines;
}

bool PathFinder::checkLine(string line) {
    for (int i = 0; i < lines.size(); i++) {
        if(lines[i] == line)
            return true;
    }
    return false;
}

// need to include a case when origin == destination
Path* PathFinder::findPath(string origin, string destination) {
    AVLTree *tree = this->getTree();
    AVLNode *startingStop = tree->searchStop(origin);

    if (startingStop == nullptr) {
        cerr << "Error: Origin stop not found in tree." << endl;
        return nullptr;
    }

    vector<MetroStop *> stops = startingStop->getStops();

    if (stops.empty()) {
        cerr << "Error: No stops found for the origin." << endl;
        return nullptr;
    }

    queue<Trip *> Exploration;
    Trip *currTrip = nullptr;
    MetroStop *currStop = nullptr;
    bool flagFind = false;

    for (int i = 0; i < stops.size(); i++) {
        Trip *trip1 = new Trip(stops[i], nullptr, 'F');
        Trip *trip2 = new Trip(stops[i], nullptr, 'B');
        Exploration.push(trip1);
        Exploration.push(trip2);
        this->setLines(stops[i]->getLine()->getLineName());

        while(!Exploration.empty() && !flagFind) {
            currTrip = Exploration.front();
            Exploration.pop();
            currStop = currTrip->getNode();

            if (currStop == nullptr) {
                delete currTrip;
                continue;
            }

            if(currTrip->getType() == 'F') {
                currStop = currStop->getNextStop();
                while(currStop != nullptr) {
                    if(currStop->getStopName() == destination) {
                        flagFind = true;

                        break;
                    }
                    AVLNode *IM_Stop = tree->searchStop(currStop->getStopName());
                    if(IM_Stop && IM_Stop->getStops().size() > 1)
                    {
                        vector<MetroStop *> IM_Stops = IM_Stop->getStops();
                        for (int j = 0; j < IM_Stops.size(); j++) {
                            if(currStop->getLine() != IM_Stops[j]->getLine() && !this->checkLine(IM_Stops[j]->getLine()->getLineName())) {
                                Trip *IM_Trip1 = new Trip(IM_Stops[j], currTrip, 'F');
                                Trip *IM_Trip2 = new Trip(IM_Stops[j], currTrip, 'B');
                                Exploration.push(IM_Trip1);
                                Exploration.push(IM_Trip2);
                                this->setLines(IM_Stops[j]->getLine()->getLineName());
                            }
                        }
                            
                    }
                    currStop = currStop->getNextStop();
                }
            }
            else {
                currStop = currStop->getPrevStop();
                while(currStop != nullptr) {
                    if(currStop->getStopName() == destination) {
                        flagFind = true;

                        break;
                    }
                    AVLNode *IM_Stop = tree->searchStop(currStop->getStopName());
                    if(IM_Stop && IM_Stop->getStops().size() > 1)
                    {
                        vector<MetroStop *> IM_Stops = IM_Stop->getStops();
                        for (int j = 0; j < IM_Stops.size(); j++) {
                            if(currStop->getLine() != IM_Stops[j]->getLine() && !this->checkLine(IM_Stops[j]->getLine()->getLineName())) {
                                Trip *IM_Trip1 = new Trip(IM_Stops[j], currTrip, 'F');
                                Trip *IM_Trip2 = new Trip(IM_Stops[j], currTrip, 'B');
                                Exploration.push(IM_Trip1);
                                Exploration.push(IM_Trip2);
                                this->setLines(IM_Stops[j]->getLine()->getLineName());
                            }
                        }
                            
                    }
                    currStop = currStop->getPrevStop();
                }
            }
            if(flagFind == true)
                break;
        }
        if(flagFind == true)
            break;
    }

    if (!flagFind) {
        cerr << "Error: Destination not found." << endl;
        return nullptr;
    }
    // else
    // {
    //     cout << "Destination find\n";
    //     return nullptr;
    // }

    Path *reqPath = new Path();
    int totalFare = 0;
    while(currTrip != nullptr) {
        if(currTrip->getType() == 'F') {
            totalFare += currStop->getFare();
            while(currStop->getStopName() != currTrip->getNode()->getStopName()) {
                reqPath->addStop(currStop);
                currStop = currStop->getPrevStop();
            }
            // reqPath->addStop(currStop);
            totalFare -= currStop->getFare();
            if(currTrip->getPrev() !=nullptr) {
                currTrip = currTrip->getPrev();
                AVLNode *node = tree->searchStop(currStop->getStopName());
                vector<MetroStop *> pStops = node->getStops();
                for (int i = 0; i < pStops.size(); i++) {
                    if(pStops[i]->getLine() == currTrip->getNode()->getLine()) {
                        currStop = pStops[i];
                        break;
                    }
                }
            }
            else {
                reqPath->addStop(currStop);
                currTrip = currTrip->getPrev();
            }
        }
        else {
            totalFare -= currStop->getFare();
            while(currStop->getStopName() != currTrip->getNode()->getStopName()) {
                reqPath->addStop(currStop);
                currStop = currStop->getNextStop();
            }
            // reqPath->addStop(currStop);
            totalFare += currStop->getFare();
            if(currTrip->getPrev() !=nullptr) {
                currTrip = currTrip->getPrev();
                AVLNode *node = tree->searchStop(currStop->getStopName());
                vector<MetroStop *> pStops = node->getStops();
                for (int i = 0; i < pStops.size(); i++) {
                    if(pStops[i]->getLine() == currTrip->getNode()->getLine()) {
                        currStop = pStops[i];
                        break;
                    }
                }
            }
            else {
                reqPath->addStop(currStop);
                currTrip = currTrip->getPrev();
            }
        }
    }
    reqPath->setTotalFare(totalFare);
    return reqPath;
}
    
vector<MetroLine*> lines;