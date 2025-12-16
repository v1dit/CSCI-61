//Programming Queues Homework
//Vidit Agarwal and Fiona Hsiao

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

class Queue
{
protected: 
    struct node
    {
        int _d;
        node* _n;

        node(int d, node* n = nullptr)
        {
            _d = d;
            _n = n;
        }

    };

    int _size;
    node* _back;
    node* _front;

    void init()
    {
        _back = _front = nullptr;
        _size = 0;
    }

    void clear()    //a function to clear the whole LL 
    {
        while (_front)
        {
            node *tmp = _front;
            _front = _front->_n;
            delete tmp;
            _size--;
        }
        init();
    }

public:
    Queue() { init(); } //constructor
    ~Queue() { clear(); }   //destructor
    Queue(const Queue& other)   //copy constructor
    {
        init();
        node* p = other._front;
        _back = nullptr;
        while (p)   //while p != nullptr
        {
            if (_size == 0)
            {
                _back = new node(p->_d);
                _size++;
                _front = _back;
            }
            else
            {
                _back->_n = new node(p->_d);
                _size++;
                _back = _back->_n;
            }
            p = p->_n;
        } 
    }

    Queue& operator=(Queue& rhs)
    {
        //self check
        if (this == &rhs) return *this;     //if the address of this and rhs is the same, that means they are the same LL
        clear();
        Queue tmp(rhs);     //copying rhs data with tmp by calling copy constructor
        _back = tmp._back;
        _front = tmp._front;
        _size = tmp._size;
        tmp.init();     //deleting the tmp
        return *this;
    }

    void enqueue(int x)     //function to add to back of queue
    {
        if (_size == 0)
        {
            _back = _front = new node(x);
        }
        else
        {
            _back->_n = new node(x);
            _back = _back->_n;
        }
        _size++;
    }

    void dequeue()     //function to remove from the front of queue
    {
        if (_size != 0)
        {
             node *tmp = _front;
            _front = _front->_n;
            delete tmp;
            _size--;
        }
        if (_size == 0) init();
    }

    int front() { return _front->_d; }
    int size() { return _size; }
    bool empty() { return size() == 0; }

    void print()
    {
        cout << "Queue: ";
        for(node *n = _front; n != nullptr; n = n->_n)
        {
            cout << n->_d << " ";
        }
        cout << endl;
    }
};

//Problem 1
//Creating PriorityQueue class inherited from Queue
class PriorityQueue : public Queue
{
public:
    void enqueue(int x)     //function to add per priority 
    {
        if (_size == 0)
        {
            _back = _front = new node(x);
        }
        else
        {
            node *n;
            for (n = _front; n != nullptr; n = n->_n)
            {
                if (n == _front && x >= n->_d)
                {
                    node *tmp = new node(x, _front);
                    _front = tmp;
                    break;
                }
                else if (n->_n != nullptr && x >= n->_n->_d)
                {
                    //insert before n->_n
                    node *tmp = new node(x, n->_n);
                    n->_n = tmp; 
                    break;
                }
            }
            if (n == nullptr)
            {
                //insert after _back
                _back->_n = new node(x);
                _back = _back->_n;
            }
        }
        _size++;
    }
};

//Problem 2
//using a circular linked list to implement Queue class
class CircularQueue
{
    struct node
    {
        int _d;
        node* _n;

        node(int d, node* n = nullptr)
        {
            _d = d;
            _n = n;
        }
    };

    int _size;
    node* _front;

    void init()
    {
        _front = nullptr;
        _size = 0;
    }

    void clear()    //a function to clear the whole LL 
    {
        while (_size != 0)
        {
            node *tmp = _front;
            _front = _front->_n;
            delete tmp;
            _size--;
        }
        init();
    }

public:
    CircularQueue() { init(); } //constructor
    ~CircularQueue() { clear(); }   //destructor
    CircularQueue(CircularQueue& other)   //copy constructor
    {
        init();
        //until p->_n == other._front, enqueue p value into queue
        node *p;
        int i;
        for (p = other._front, i = 0; i < other.size(); p = p->_n, i++)
        {
            enqueue(p->_d);
        }
    }

    //function overriding operator= using copy constructor
    CircularQueue& operator=(CircularQueue& rhs)
    {
        //self check
        if (this == &rhs) return *this;     //if the address of this and rhs is the same, that means they are the same LL
        clear();
        CircularQueue tmp(rhs);     //copying rhs data with tmp by calling copy constructor
        _front = tmp._front;
        _size = tmp._size;
        tmp.init();     
        return *this;
    }

    //function to add to the back of queue
    void enqueue(int x)  
    {
        if (_size == 0)
        {
            _front = new node(x);
            _front->_n = _front;
        }
        else
        {
            node *back = _front;
            while (back->_n != _front)
            {
                back = back->_n;
            }
            back->_n = new node(x, _front);
        }
        _size++;
    }

    //function to remove from the front of queue
    void dequeue()     
    {
        if (_size != 0)
        {
             node *tmp = _front;
            _front = _front->_n;
            delete tmp;
            _size--;
        }
        if (_size == 0)
            init();
    }

    int front() { return _front->_d; }
    int size() { return _size; }
    bool empty() { return size() == 0; }

    void print()
    {
        cout << "Circular Queue: ";
        int i;
        node *n;
        for(n = _front, i = 0; i < _size; n = n->_n, i++)
        {
            cout << n->_d << " ";
        }
        cout << endl;
    }
};

//Problem 3
//vector of delimiters
vector<char> delim = {' ', '\n', ',', '.', '?', '!', ';', ':', '\t'};

//function to split the string with multiple delimiters
vector<string> splitString(string line, vector<char> delim)
{
    vector<string> tokens;
    string word = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (find(delim.begin(), delim.end(), line[i]) == delim.end())
        {
            word += tolower(line[i]);
        }
        else
        {
            if (word.length() != 0)
            {
                tokens.push_back(word);
                word = "";
            }
        }
    }
    if (word.length() != 0)
    {
        tokens.push_back(word);
    }
    return tokens;
}

//Function to check if a phrase is a palindrome
void if_palindrome(string phrase)
{
    vector<string> tokens = splitString(phrase, delim);

    //create a queue for each word of the phrase
    queue<string> s_queue;
    for (int i = 0; i < tokens.size(); i++)
    {
        s_queue.push(tokens[i]);
    }

    //checking if the string is palindrome or not by comparing top of stack and index of string
    for (int i = tokens.size() - 1, j = tokens.size()/2; i >= j; i--)
    {
        if ((s_queue.front() != tokens[i]))
        {
            cout << "\"" << phrase << "\" is not a palindrome." << endl;;
            return;
        }
        s_queue.pop();
    }
    cout << "\"" << phrase << "\" is a palindrome." << endl;
}

//Problem 3
//Function that calls if_palindrome to determine whether a phrase is a palindrome or not
//This function creates a user friendly interface, allowing users to input as many phrases as they want
void Problem3()
{
    string line;
    cout << "Insert a phrase and hit <enter> to end: " << endl;
    while (true)
    {
        getline(cin, line);
        if (line.length() == 0)
            break;
        if_palindrome(line);
    }
    cout << "Exit" << endl;
}

//Problem 4
//function to create matrix (implemented in class)
void buildPic(vector<vector<int>> & A) {
    unsigned int X = A.size();
    unsigned int Y = A[0].size();
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            A[i][j] = rand() % 2;
        }
    }
}

//function to print matrix (implemented in class)
void printPic(const vector<vector<int>> & A) {
    unsigned int X = A.size();
    unsigned int Y = A[0].size();
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            cout <<  " " << A[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

//floodFill function implemented in class
void floodFill(vector<vector<int>>& A, int x, int y, int v) {
    queue<pair<int, int>> todo;
    todo.push(pair<int, int>(x, y));
    int target = A[x][y];
    unsigned int N = A.size(); //tracking the boundary of the pic (row)
    unsigned int M = A[0].size(); //tracking the boundary of the pic (col)
    while (!todo.empty()) {
        pair<int, int> p = todo.front();
        todo.pop();
        int i = p.first;
        int j = p.second;
        //finding neighbors of target point
        if (A[i][j] == target) {
            A[i][j] = v;
            // Adding 12 o'clock neighbor
            if (j + 1 < M) todo.push(make_pair(i, j + 1));
            // Adding 1.5 o'clock neighbor
            if (i + 1 < N && j + 1 < M) todo.push(make_pair(i + 1, j + 1));
            // Adding 3 o'clock neighbor
            if (i + 1 < N) todo.push(make_pair(i + 1, j));
            // Adding 4.5 o'clock neighbor
            if (i + 1 < N && j - 1 >= 0) todo.push(make_pair(i + 1, j - 1));
            // Adding 6 o'clock neighbor
            if (j - 1 >= 0) todo.push(make_pair(i, j - 1));
            // Adding 7.5 o'clock neighbor
            if (i - 1 >= 0 && j - 1 >= 0) todo.push(make_pair(i - 1, j - 1));
            // Adding 9 o'clock neighbor
            if (i - 1 >= 0) todo.push(make_pair(i - 1, j));
            // Adding 10.5 o'clock neighbor
            if (i - 1 >= 0 && j + 1 < M) todo.push(make_pair(i - 1, j + 1));
        }
    }
}

//Function to count and label all islands
int countIslands(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int islandCount = 0;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[y][x] == 1) {
                islandCount++;
                floodFill(grid, y, x, islandCount + 1); 
            }
        }
    }
    return islandCount;
}

int main()
{
    //Testing for Problem 1
    cout << "Testing Problem 1" << endl;
    Queue nQ;
    PriorityQueue pQ;
    CircularQueue cQ;
    srand(time(nullptr));
    for (int i = 0; i < 20; i++)
    {
        int x = rand() % 20 - 10;
        cout << x << " ";
        nQ.enqueue(x);
        pQ.enqueue(x);
        cQ.enqueue(x);
    }
    cout << endl;
    nQ.print();
    cout << "Priority ";
    pQ.print();
    cout << endl;

    //Testing for Problem 2
    cout << "Testing Problem 2" << endl;
    cQ.print();

    CircularQueue cQ2(cQ);
    cout << "#2 ";
    cQ2.print();

    CircularQueue cQ3 = cQ2;
    cout << "#3 ";
    cQ3.print();

    //Testing Problem 3
    cout << "\nTesting Problem 3" << endl;
    Problem3();
    
    //Testing Problem 4
    cout << "\nTesting Problem 4" << endl;
    vector<vector<int>> matrix(6, vector<int> (6));
    buildPic(matrix);
    printPic(matrix);
    cout << "Number of islands: " << countIslands(matrix) << endl;
    printPic(matrix);

    return 0;
}
