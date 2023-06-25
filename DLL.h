#include<iostream>
#include<algorithm>
using namespace std;


template<typename T>
void Swap(T &data1, T &data2) {
    T temp = data2;
    data2 = data1;
    data1 = temp;
}

template <class T>
class Node{
private:
    T element;
    Node *Previous;
    Node *next;
public:
    Node(T e, Node *n = NULL, Node *last = NULL): element(e), next(n), Previous(last) {}
    T retrieve(){
        return this->element;
        }
    void setnext(Node * n){
            this->next = n;
    }

    void setPrevious(Node * n){
        this->Previous = n;
    }
    
    void setElement(T ele){
        this->element = ele;
    }


    Node* getnext(){
        return this->next;
    }

    Node* getPrevious(){
        return this->Previous;
    }

};

template <class T>
class LinkedList{
private:
    Node<T> *head;
    Node<T> *Tail;
public:
    LinkedList(){
        head  = NULL;
        Tail = NULL;
    }
    Node<T> *gethead(){
        return this->head;
    }

    Node<T> *getTail(){
        return this->Tail;
    } 


    void push_front(T var){
        Node<T> *n = new Node<T>(var, head, NULL);
        if(head == NULL){
            head = n;
        }
        
        else{
            head->setPrevious(n);
            n->setnext(head);
            n->setPrevious(NULL);
            head = n;
        }
    }

    void push_back(T var){
        Node<T> *nodeToAppend = new Node<T>(var, NULL, this->getTail());
        if(head == NULL && Tail == NULL){
            push_front(var);
        }
        else if(Tail == NULL){
            Node<T> *last = this->gethead();
                while(last->getnext() != NULL){
                    last = last->getnext();
                }
                last->setnext(nodeToAppend);
                Tail = nodeToAppend;
        }
        else{
            Tail->setnext(nodeToAppend);
            Tail = nodeToAppend;
        }
        
    }

    void insert(Node<T> *point, T ele){
        Node<T> *ptr = new Node<T>(ele, NULL);
        ptr->setnext(point->getnext()); 
        ptr->setPrevious(point);
        point->setnext(ptr);
        point->getnext()->setPrevious(ptr);
    }

    int Size(){
        int count = 0;
        Node<T> *iter = gethead();
        while(iter != NULL){
            count++;
            iter = iter->getnext();
        }
        return count;
        }

    T pop_front(){
        Node<T> *to_Be_Deleted = gethead();
        head = head->getnext();
        head->setPrevious(NULL);
        to_Be_Deleted->setnext(NULL);
        T val = to_Be_Deleted->retrieve();
        delete to_Be_Deleted;
        to_Be_Deleted = NULL;
        return val;

        }
        
    T pop_back(){
        T val = Tail->retrieve();
        Node<T> *to_Be_Deleted = getTail();
        Tail = Tail->getPrevious();
        Tail->setnext(NULL);
        to_Be_Deleted->setPrevious(NULL);
        delete to_Be_Deleted;
        to_Be_Deleted = NULL;
        return val;
    }

    void pop(T val){
        Node<T> *n = gethead();
        Node<T> *toDelete;
        if(gethead()->retrieve() == val){
            this->pop_front();
        }
        while (n->getnext()->retrieve() != val)
        {
            n = n->getnext();
        }
        if (n->getnext()->retrieve() == val){
            toDelete = n->getnext();
            n->setnext( n->getnext()->getnext());
            toDelete->getnext()->setPrevious(n);
            toDelete->setnext(NULL);
            toDelete->setPrevious(NULL);
        }
        
        delete toDelete;
        toDelete = NULL;
    }
    // delete a node using pointer to that node.
    void pop(Node<T> *tobeDeleted) {
        Node<T> *n = tobeDeleted->getPrevious();
        n->setnext(n->getnext()->getnext());
        tobeDeleted->getnext()->setPrevious(n);
        tobeDeleted->setnext(NULL);
        tobeDeleted->setPrevious(NULL);
        delete tobeDeleted;
        tobeDeleted = NULL;
    }

    void Display(){
        Node<T> *n = gethead();
        while (n != NULL)
        {
            cout << n->retrieve() << " ";
            n = n->getnext();
        }
        cout << endl;
    }

    void Search(T variable){
        int count = 0;
        Node<T> *n = gethead();
        while (n != NULL)
        {
            count++;
            if(variable == n->retrieve()){
                cout << n->retrieve() << " exists in the list at position " << count << endl;
            }
            n = n->getnext();
            
        }
        n = NULL;
    }

    void sortReverse(){
        Node<T> *i = gethead();
        Node<T> *j = NULL;
        while (i != NULL)
        {
            j = gethead();
            while (j != NULL)
            {
                if(i->retrieve() < j->retrieve()){
                    T temp = j->retrieve();
                    j->setElement(i->retrieve());
                    i->setElement(temp);
                }
                j = j->getnext();

            }
            i = i->getnext();
        }
        
    }

    void sort(){
        Node<T> *i = gethead();
        Node<T> *j = gethead();
        while (i != NULL)
        {
            j = gethead();
            while (j != NULL)
            {
                if(i->retrieve() > j->retrieve()){
                    T temp = j->retrieve();
                    j->setElement(i->retrieve());
                    i->setElement(temp);
                }
                j = j->getnext();

            }
            i = i->getnext();
        }
        
    }

    

    bool isEmpty(){
        return (head == NULL);
    }
};



template <class T>
class Stack {
    LinkedList<T> list;
    public:
    Stack(){

    }
    void push(T var){
        list.push_front(var);
    }

    int Size(){
        return list.Size();
    }

    T pop(){
        if( ! list.isEmpty()){
            return  list.pop_front();
        }
        else{
            cout << "Error Stack is Empty" << endl;
            return list.pop_front();
        }    
    }

    T top(){

            return list.gethead()->retrieve();
    }

    bool empty(){
        return list.isEmpty();
    }

    void swap(Stack * N){

    }
    

    ~Stack(){ }
};

template <typename T>
class Queue
{
private:
    LinkedList<T> list;
    int size;
public:
    Queue(){
        size = 0;
    }
    bool isEmpty(){
        return list.isEmpty();
    }
    void enQueue(T data){
        list.push_back(data);
        size++;
    }
    void deQueue(){
        list.pop_front();
        size--;
    }
    T front(){
        return list.gethead()->retrieve();
    
    }
    void Display(){
        list.Display();
    }
    int Qsize(){
        return this->size;
    }
    ~Queue(){}
};