#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

//question 1
#include <iostream>
using namespace std;
struct Node{
    int data;
    Node* next;

    Node(int val){
        data = val;
        next = nullptr;
    }
};
//Function to print the list
void printList(Node* head){
    Node* temp = head;
    while(temp != nullptr){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr\n";
}

Node* insertionSort(Node* head){
    if(head == nullptr || head->next == nullptr){
        return head;
    }

    Node* sortedHead = nullptr; //This will be the head of our new, sorted list

    Node* current = head;

    while(current != nullptr){ //loop through the original list
        Node* nextNode = current-> next;

        if(sortedHead == nullptr || sortedHead->data >= current->data){
            current->next = sortedHead;
            sortedHead = current;
        }

        else{ //find the node before the insertion point
            Node* sortedTemp = sortedHead;
            while(sortedTemp->next != nullptr && sortedTemp->next->data < current->data){
                sortedTemp = sortedTemp->next;
            }
            current->next = sortedTemp->next;
            sortedTemp->next = current;
        }

        current = nextNode;
    }
    return sortedHead;
}


int main(){
    Node* head = new Node(5);
    head->next = new Node(2);
    head->next->next = new Node(10);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(8); // This was missing

    cout << "Original list: ";
    printList(head);

    //sort thel list
    head = insertionSort(head);
    
    cout << "Sorted List: ";
    printList(head);

    return 0;
}


// question 2 

struct Node {
    int data;
    Node* next;

    Node(int val){
        data = val;
        next = nullptr;
    }
};

// Function to print the list
void printList(Node* head){
    Node* temp = head;
    while(temp != nullptr){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr\n";
}

//  Helper function: Split list into two halves
Node* getMiddle(Node* head){
    if(head == nullptr)
        return head;

    Node* slow = head;
    Node* fast = head->next;

    // Move fast by 2 and slow by 1
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

//  Helper function: Merge two sorted linked lists
Node* mergeLists(Node* left, Node* right){
    // If either list is empty
    if(left == nullptr) return right;
    if(right == nullptr) return left;

    Node* result = nullptr;

    if(left->data <= right->data){
        result = left;
        result->next = mergeLists(left->next, right);
    }
    else{
        result = right;
        result->next = mergeLists(left, right->next);
    }

    return result;
}

//  Merge Sort function
Node* mergeSort(Node* head){
    // Base case: 0 or 1 element
    if(head == nullptr || head->next == nullptr)
        return head;

    // Get the middle of the list
    Node* middle = getMiddle(head);
    Node* secondHalf = middle->next;
    middle->next = nullptr; // split the list

    // Recursively sort both halves
    Node* left = mergeSort(head);
    Node* right = mergeSort(secondHalf);

    // Merge the two sorted halves
    return mergeLists(left, right);
}

int main(){
    Node* head = new Node(5);
    head->next = new Node(2);
    head->next->next = new Node(10);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(8);

    cout << "Original list: ";
    printList(head);

    // Sort the list using merge sort
    head = mergeSort(head);

    cout << "Sorted list:   ";
    printList(head);

    return 0;
}


//question 3 

//function to print the vector
void printArray(const vector<int>& arr){
    for(int val: arr){
        cout << val << " ";
    }
    cout << "\n";
}


//partitioning array segment
int partition(vector<int>&arr, int low, int high){
    int pivot = arr[high]; //choosing the last element as the pivot
    int i = (low -1); //index of the smaller element

    //iterate from low up to high
    for(int j = low; j < high; j++){
        if(arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return(i + 1);
}

void quickSortIterative(vector<int>& arr){//sort the arr using a non recursive
    int n = arr.size();
    if(n<= 1)
        return;

    stack<pair<int, int>> stack;

    stack.push({0, n-1});

    while(!stack.empty()){
        int low = stack.top().first;
        int high = stack.top().second;
        stack.pop();

        int pivotIndex = partition(arr,low,high);

        if(pivotIndex - 1 > low){
            stack.push({low, pivotIndex-1});
        }
        if(pivotIndex + 1 < high){
            stack.push({pivotIndex + 1, high});
        }
    }
}

int main() {
    // We use std::vector as a more flexible C++ array
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    cout << "Original array: ";
    printArray(arr);

    // Call our iterative sort function
    quickSortIterative(arr);

    cout << "Sorted array:   ";
    printArray(arr);

    return 0;
}

// question 4 

// K-way merge using a min-heap
vector<int> kWayMerge(vector<vector<int>>& lists) {
    vector<int> result;
    auto cmp = [&](pair<int,int>& a, pair<int,int>& b){
        return a.first > b.first; 
    };

    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> minHeap(cmp);

    vector<int> indices(lists.size(), 0);

    // Push first element of each list
    for(int i = 0; i < lists.size(); i++){
        if(!lists[i].empty()) {
            minHeap.push({lists[i][0], i});
        }
    }

    // Extract-min and push next element from that list
    while(!minHeap.empty()){
        auto [val, listIndex] = minHeap.top();
        minHeap.pop();
        result.push_back(val);

        indices[listIndex]++;
        if(indices[listIndex] < (int)lists[listIndex].size()){
            minHeap.push({lists[listIndex][indices[listIndex]], listIndex});
        }
    }

    return result;
}

// Recursive K-way "Funnel Sort"
vector<int> funnelSort(vector<int>& arr, int k){
    int n = arr.size();
    if(n <= 1) return arr;

    int size = n / k;
    vector<vector<int>> parts(k);

    // Split into k parts
    int start = 0;
    for(int i = 0; i < k; i++){
        int end = (i == k-1) ? n : start + size;
        parts[i] = vector<int>(arr.begin() + start, arr.begin() + end);
        start = end;
    }

    // Recursively sort each part
    for(int i = 0; i < k; i++){
        parts[i] = funnelSort(parts[i], k);
    }

    // Merge all k sorted lists
    return kWayMerge(parts);
}

// Timing experiment
int main() {
    int N = 1'000'000; // 10^6
    vector<int> arr(N);

    // fill with random integers
    for(int i = 0; i < N; i++){
        arr[i] = rand();
    }

    vector<int> ks = {2, 4, 8, 16, 32, 64}; // try different k values

    for(int k : ks){
        vector<int> temp = arr;

        auto start = chrono::high_resolution_clock::now();
        temp = funnelSort(temp, k);
        auto end = chrono::high_resolution_clock::now();

        double ms = chrono::duration<double, milli>(end - start).count();

        cout << "k = " << k << "   time = " << ms << " ms\n";
    }

    return 0;
}
