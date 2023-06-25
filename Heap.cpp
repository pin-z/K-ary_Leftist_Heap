#include<iostream>
#include "DLL.h"
#include<queue>
using namespace std;

template<typename T> 
void Descend_Sort(Node<T>* head){
    Node<T> *i = head;
        Node<T> *j = NULL;
        while (i != NULL)
        {
            j = head;
            while (j != NULL)
            {
                if(i->retrieve()->getData() < j->retrieve()->getData()){
                    T temp = j->retrieve();
                    j->setElement(i->retrieve());
                    i->setElement(temp);
                }
                j = j->getnext();

            }
            i = i->getnext();
        }
}


//Max K-ary leftist heap.
template <typename T>
class Heap {
    T data;
    Heap * ParentNode;
    LinkedList<Heap*> child;
    int K;
    public:
    //Constructor
    Heap( int K = 2, Heap* p = NULL){
        this->ParentNode = p;
        this->K = K;
    }
    //getter functions
    T getData(){
        return this->data;
    }
    Heap* getParent(){
        return this->ParentNode;
    }
    Heap* getChild(int n){
        if(n<0 || n>child.Size() || n>K){
            return NULL;
        }
        else if(n == 1){
            return child.gethead()->retrieve();
        }
        else{
            Node<Heap*> *iter = child.gethead();
            for(int i = 1; i<=n; i++){
                iter = iter->getnext();
            }
            return iter->retrieve();
        }
    }

    //get degree
    int degree(){
        return this->child.Size();
    }
    bool isRoot(){
        return (ParentNode == NULL);
    }
    bool isLeaf(){
        return (degree()==0);
    }
    void setData(T ele){
        if(ParentNode != NULL && ParentNode->getData() >= ele){
            this->data = ele;
        }
        else if(this->ParentNode == NULL){
            this->data = ele;
        }
        else{
            cout << "Warning: Can not add element against the rule of Max Heap!" << endl;
            Swap(ParentNode->data, ele);
            this->data = ele;
        }
    }

    void insert(T ele){
        Heap* toAdd = new Heap();
        if(child.Size() < K && this->data < ele ){
            Swap(this->data, ele);
            toAdd->setData(ele);
            toAdd->ParentNode = this;
            child.push_back(toAdd);
            Descend_Sort(child.gethead());
        }
        else if(child.Size() >= K){
            if(this->data < ele){
                Swap(this->data, ele);

            }
                toAdd->setData(ele);
                child.push_back(toAdd);
                Descend_Sort(child.gethead());
                Heap* toAdd = child.pop_back();
                ele = toAdd->getData();
                Node<Heap*>* n = child.gethead();
                bool match = false;
                for(int i = 0; i<K; i++){
                    if(n->retrieve()->degree() < K){
                        match = true;
                        n->retrieve()->insert(ele);
                        break;
                    }
                    n = n->getnext();
                }
                if(!match){
                    child.gethead()->retrieve()->insert(ele);
                }
            
        }
        else{
            toAdd->setData(ele);
            toAdd->ParentNode = this;
            child.push_back(toAdd);
            Descend_Sort(child.gethead());
        }
    }

    int Size(){
        int size = 1;
        for(Node<Heap*>* iter = child.gethead(); iter!= NULL; iter = iter->getnext()){
            size+=iter->retrieve()->Size();
        }
        return size;
    }

    int height(){
        Node<Heap*>* iter = child.gethead();
        int height = 1;
        while (iter != NULL)
        {
            height++;
            iter = iter->retrieve()->child.gethead();
        }
        return height;
        
    }

    void delete_Node(T val){
        queue<Heap*> line;
        Node<Heap*>* iterNode;
        Heap* todelete;
        Heap* myHeap;
        line.push(this);
        while (!line.empty())
        {
            myHeap = line.front();
            iterNode = myHeap->child.gethead();
            while (iterNode != NULL)
            {
                line.push(iterNode->retrieve());
                iterNode = iterNode->getnext();
            }
            if( val == line.front()->getData()){
                todelete = line.front();
            }
            line.pop();
        }
        myHeap = NULL;
        if(todelete->isLeaf()){
            todelete->detach();
            delete todelete;
            todelete = NULL;
        }
        else{
            while (todelete->isLeaf())
            {
                Heap* LeftChild = todelete->child.gethead();
                Swap(todelete->data, LeftChild->data);
                todelete = LeftChild;
            }
            todelete->detach();
            delete todelete;
            todelete = NULL;

        }

     
        
    }
    

    void attach(Heap* SubHeap){
        if(this->data < SubHeap->getData() ){
            cout << "Warning: Can not add element against the rule of Max Heap!" << endl;
        }
        else if(child.Size() >= K){
            cout << "Error: you are allowed to add " << this->K  << " childs only." << endl;
        }
        else {
            if(!SubHeap->isRoot()){
            SubHeap->detach();
            }
            SubHeap->ParentNode = this;
            child->push_back(SubHeap);
        }
        

    }

    void detach(){
        if(isRoot()){
            return;
        }
        ParentNode->child.pop(this);
        ParentNode = NULL;

    }
    
// logical error in  traversal
    void Breath_First_Traversal(){
        queue<Heap*> line;
        Node<Heap*>* iterNode;
        Heap* myHeap;
        line.push(this);
        while (!line.empty())
        {
            myHeap = line.front();
            iterNode = myHeap->child.gethead();
            while (iterNode != NULL)
            {
                line.push(iterNode->retrieve());
                iterNode = iterNode->getnext();
            }
            cout << line.front()->getData() << ", ";
            
            line.pop();
        }

        cout << "Ending "<< endl;
        myHeap = NULL;
        
    }

    void BFT_in_LinkedList(LinkedList<T> *list){
        queue<Heap*> line;
        Node<Heap*>* iterNode;
        Heap* myHeap;
        line.push(this);
        
        while (!line.empty())
        {
            myHeap = line.front();
         
            iterNode = myHeap->child.gethead();
            while (iterNode != NULL)
            {
                line.push(iterNode->retrieve());
                iterNode = iterNode->getnext();
                
            }
            if(line.front() != NULL) {
                T val = line.front()->getData();
                list->push_back(val);
            }
            
            line.pop();
        }
        
    }


};
// a solution better then heapsort using heap with same time complexity but more simple and short
template<class T>
void Heap_sorting(T* arr, int len){
    Heap<T> myheap;
    myheap.setData(arr[0]);
    LinkedList<T>* list;
    for(int i = 1; i<len; i++){
        myheap.insert(arr[i]);
    }
    myheap.BFT_in_LinkedList(list);
    int i = 0;
    while( i<len && !list->isEmpty() ){
        arr[i] = list->pop_front();
        i++;
    }
}

template <typename t>
class store {
        int priority;
        t info;
        public:
        store(t info, int priority){
            this->info  = info;
            this->priority = priority;
        }
        int getPriority(){
            return this->priority;
        }
        t getInfo(){
            return this->info;
        }
        };

template <typename Q>
class PriorityQueue{
    LinkedList<store<Q>*> storeList;
    Heap<int> priority_heap;
    queue<Q> data_queue;
    public:
    PriorityQueue(){
        priority_heap.setData(0);
    }

    void enqueue(Q info, int key){
        store<Q>* data = new store<Q>(info, key);
        storeList.push_back(data);
        priority_heap.insert(key);
        
    }


    void Make_Queue(){
        
        LinkedList<int>* temp = new LinkedList<int>();
        priority_heap.BFT_in_LinkedList(temp);
        Node<int>* i = temp->gethead();
        Node<store<Q>*>* j = storeList.gethead();
        while (i != NULL)
        {
            j = storeList.gethead();
            while (j != NULL)
            {
                if(i->retrieve() == j->retrieve()->getPriority()){
                    data_queue.push(j->retrieve()->getInfo());
                    
                    
                }
               j =  j->getnext();
            }
            
            i = i->getnext();
        }
        

    }

    void Dequeue(){
        Make_Queue();
        data_queue.pop();
    }

    Q front(){
       Make_Queue();
        return  data_queue.front();
    }

    void Retreive(){
        Make_Queue();
        while (!data_queue.empty())
        {
            cout << data_queue.front() << " " << endl;
            data_queue.pop();
        }
        
    }

    void Delete_Queue(){
        Make_Queue();
        while (data_queue.size() != 0)
        {
            data_queue.pop();
        } 
    }

};


int main(){
    
    PriorityQueue<string> list;
    list.enqueue("Name", 5);
    list.enqueue("MY", 7);
    list.enqueue("Zaim", 1);
    list.enqueue("is", 2);
    list.enqueue("Hello", 10);
    list.enqueue("World", 8);
   
    
    list.Retreive();

    

    bool exit = false;
    while (exit)
    {
        start:
        system("cls");
        cout << "||-----------------||" << endl;
        cout << "|  PRIORITY LIST    |" << endl;
        cout << "|       MENU        |" << endl;
        cout << "||-----------------||" << endl;
        int opt = 0;
        cout << "Select from the given options:-    " << endl;
        cout << "1. Add an Element to List. " << endl;
        cout << "2. Pop the Element with highest priority from List. " << endl;
        cout << "3. Display all Elements in the List. " << endl;
        cout << "4. Display element with highest priority" << endl;
        cout << "5. Delete the List. " << endl;
        cout << "6. Exit the List" << endl;
        cout << "   ->>------> ";
        cin >> opt;
        redirect:
        while (opt <= 0 || opt > 6)
        {
            cout << "ERROR : Invalid Input! " << endl;
            cout << "   ->>------> ";
            cin >> opt;
        }
        //Making a priority Queue.
        PriorityQueue<string> myList;
        string element;
        int key;
        char confirm = 'N';
        system("cls");
        switch (opt)
        {
        case 1:
            cout << "Enter data you want to add: ";
            cin >> element;
            cout << "Set Priority: ";
            cin >> key;
            myList.enqueue(element, key);
            system("pause");
            break;
        case 2:
            myList.Dequeue();
            system("pause");
            break;
        case 3:
            myList.Retreive();
            system("pause");
            break;
        case 4:
            cout << "Highest priority Element: " << myList.front() << endl;
            system("pause");
            break;
        case 5:
            myList.Delete_Queue();
            system("pause");
            break;
        case 6:
            cout << "Do you really want to exit? (Y/N) : ";
            cin >> confirm;
            while (confirm != 'Y' || confirm != 'y' || confirm != 'N' || confirm != 'n')
            {
                cout << "   ERROR : Invalid Input! " << endl;
                cout << " Do you really want to exit? (Y/N) :  ";
                cin >> confirm;
            }
            if(confirm != 'Y' || confirm != 'y' ){
                exit = true;
            }
            else{
                goto start;
            }
            break;
        default:
            goto redirect;
            break;
        }
    }
    
    Heap<int> test;
    test.setData(12);
    test.insert(10);
    cout << "test data:" << test.getData() << endl;
    test.insert(40);
    cout << test.getChild(1)->getData() << endl;
    test.insert(89);
    Heap<int> A;
    cout << "Size: " << test.Size() << endl;
    test.Breath_First_Traversal();
   
    return 0;
}