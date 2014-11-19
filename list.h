//
//initialize
//destroy
//isEmpty
//removeNth
//append
//find
//getNth
//getSize
//

template <class T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
};

template <class T>
struct List {
    Node<T>* head;
};

template <class T>
void initialize(List<T>& l)
{
    l.head=NULL;
}

template <class T>
void destroy(List<T>& l)
{
    Node<T>* walker=l.head;
    while(walker!=NULL){
        l.head=walker;
        walker=walker->next;
        delete l.head;
    }
    walker=NULL;
    l.head=NULL;
}

template <class T>
bool isEmpty(List<T> l)
{
    if (l.head==NULL) {
        return true;
    }
    return false;
}

template <class T>
void append(List<T>& l,T value)
{
    Node<T>* walker=l.head;
    Node<T>* n=new Node<T>;
    n->data=value;
    if (l.head==NULL) {
        l.head=n;
        l.head->prev=NULL;
        l.head->next=NULL;
    }
    else{
        while (walker->next!=NULL) {
            walker=walker->next;
        }
        walker->next=n;
        n->prev=walker;
        n->next=NULL;
    }
}

template <class T>
int  find(List<T> l,T value)
{
    int count=0;
    Node<T>* walker=l.head;
    if (l.head==NULL) {
        return 0;
    }
    while (walker!=NULL) {
        count++;
        if (walker->data==value) {
            break;
        }
        if (walker->next==NULL) {
            return 0;
        }
        walker=walker->next;
    }
    
    return count;
}

template <class T>
int  getSize(List<T> l)
{
    if (l.head==NULL) {
        return 0;
    }
    int count=0;
    Node<T>* walker=l.head;
    while (walker!=NULL) {
        count++;
        walker=walker->next;
    }
    return count;
}

template <class T>
T    getNth(List<T> l,int n)
{
    int count=0;
    Node<T>* walker=l.head;
    while (count < n-1) {
        count++;
        walker=walker->next;
    }
    return walker->data;
}

template <class T>
void removeNth(List<T>& l,int n)
{
    int number=0;
    Node<T>* walker=l.head;
    Node<T>* trailer;
    while (number<n-1) {
        number++;
        trailer=walker;
        walker=walker->next;
    }
    if (getSize(l)==1 && n==1) {
        //delete l.head;
        l.head=NULL;
    }
    else if (n==1) {
        Node<T>* del=l.head;
        l.head=l.head->next;
        l.head->prev=NULL;
        del=del;	//no-op to remove unused but set variable compile warning
        del=NULL;
    }
    else{
        if (walker->next==NULL) {
            trailer->next=NULL;
            //delete walker;
            walker=NULL;
        }
        else{
           trailer->next=walker->next;
           walker->next->prev=walker->prev;
           //delete walker;
           walker=NULL;
        }
    }
}