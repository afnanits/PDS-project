#include<bits/stdc++.h>
using namespace std;

const int capacity=581;

bool roomsOccupied[capacity];
string dateToday;

int total=0;




struct Guest
{
    string name;
    string startDate;
    string endDate;
    string address;
    int age;
    int RoomNo;

};

struct CompareDate {
    bool operator()(Guest const& p1, Guest const& p2)
    {
        return p1.endDate < p2.endDate;
    }
};

   priority_queue<Guest, vector<Guest>, CompareDate> check;





struct node
{
    struct Guest info;
    struct node *left;
    struct node *right;
}*root;

/*
 * Class Declaration
 */
class BST
{
    public:
        void find(string, node **, node **);
        void insert(node *, node *);
        void del(string);
        void case_a(node *,node *);
        void case_b(node *,node *);
        void case_c(node *,node *);
        void preorder(node *);
        void inorder(node *);
        void postorder(node *);
        void display(node *, string);
        BST()
        {
            root = NULL;
        }
};





/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode)
{
    if (root == NULL)
    {
        root = new node;
        root->info = newnode->info;
        root->left = NULL;
        root->right = NULL;
        cout<<"Guest is added"<<endl;
        return;
    }
    if (tree->info.name == newnode->info.name)
    {
        cout<<"Element already in the tree"<<endl;
        return;
    }
    if (tree->info.name > newnode->info.name)
    {
        if (tree->left != NULL)
        {
            insert(tree->left, newnode);
	}
	else
	{
            tree->left = newnode;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            cout<<"Node Added To Left"<<endl;
            return;
        }
    }
    else
    {
        if (tree->right != NULL)
        {
            insert(tree->right, newnode);
        }
        else
        {
            tree->right = newnode;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            cout<<"Node Added To Right"<<endl;
            return;
        }
    }
}

 /*
 * Find Element in the Tree
 */
void BST::find(string name, node **par, node **loc)
{
    node *ptr, *ptrsave;
    if (root == NULL)
    {
        *loc = NULL;
        *par = NULL;
        return;
    }
    if (name == root->info.name)
    {
        *loc = root;
        *par = NULL;
        return;
    }
    if (name < root->info.name)
        ptr = root->left;
    else
        ptr = root->right;
    ptrsave = root;
    while (ptr != NULL)
    {
        if (name == ptr->info.name)
        {
            *loc = ptr;
            *par = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (name < ptr->info.name)
            ptr = ptr->left;
	else
	    ptr = ptr->right;
    }
    *loc = NULL;
    *par = ptrsave;
}









/*
 * Delete Element from the tree
 */
void BST::del(string item)
{
    node *parent, *location;
    if (root == NULL)
    {
        cout<<"All rooms empty"<<endl;
        return;
    }
    find(item, &parent, &location);
    if (location == NULL)
    {
        cout<<"Guest Not Found"<<endl;
        return;
    }
    if (location->left == NULL && location->right == NULL)
        case_a(parent, location);
    if (location->left != NULL && location->right == NULL)
        case_b(parent, location);
    if (location->left == NULL && location->right != NULL)
        case_b(parent, location);
    if (location->left != NULL && location->right != NULL)
        case_c(parent, location);
    free(location);
}

/*
 * Case A
 */
void BST::case_a(node *par, node *loc )
{
    if (par == NULL)
    {
        root = NULL;
    }
    else
    {
        if (loc == par->left)
            par->left = NULL;
        else
            par->right = NULL;
    }
}


/*
 * Case B
 */
void BST::case_b(node *par, node *loc)
{
    node *child;
    if (loc->left != NULL)
        child = loc->left;
    else
        child = loc->right;
    if (par == NULL)
    {
        root = child;
    }
    else
    {
        if (loc == par->left)
            par->left = child;
        else
            par->right = child;
    }
}

/*
 * Case C
 */
void BST::case_c(node *par, node *loc)
{
    node *ptr, *ptrsave, *suc, *parsuc;
    ptrsave = loc;
    ptr = loc->right;
    while (ptr->left != NULL)
    {
        ptrsave = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrsave;
    if (suc->left == NULL && suc->right == NULL)
        case_a(parsuc, suc);
    else
        case_b(parsuc, suc);
    if (par == NULL)
    {
        root = suc;
    }
    else
    {
        if (loc == par->left)
            par->left = suc;
        else
            par->right = suc;
    }
    suc->left = loc->left;
    suc->right = loc->right;
}


  BST guests;


void checkIn()
{
    Guest newGuest;
    string name;
     string startDate;
    string endDate;
     string address;
     int age;
    int RoomNo;


    cout<<"Please enter the following data with regards to the guest details"<<endl;
    cout<<"Enter Guest name"<<endl;
    cin>>name;
    cout<<"Enter guest check-out date in yyyy-mm-dd format"<<endl;
    cin>>endDate;
    cout<<"Enter Guest Address"<<endl;
    cin>>address;
    cout<<"Enter guest age"<<endl;
    cin>>age;
    cout<<"Please choose a room from the following list of unoccupied rooms"<<endl;

        int count=0;
        for(int i=81;i<581 && count<10; i++)
        {
            if(!roomsOccupied[i])
            {
                cout<<i<<" ";
                count+=1;
            }
        }
        cout<<endl;
       cin>>RoomNo;

    newGuest.name=name;
    newGuest.startDate=dateToday;
    newGuest.endDate=endDate;
    newGuest.address=address;
    newGuest.age=age;
    newGuest.RoomNo=RoomNo;

    roomsOccupied[RoomNo]=true;

    check.push(newGuest);

    node *add=new node;

    add->info=newGuest;

    guests.insert(root,add);

    cout<<"The guest "<<name<<" was succesfully checked in"<<endl<<endl;

    total++;

}


void checkOutGuest(string name){


    node *parent, *guest;

    guests.find(name, &parent, &guest);

    if(guest== NULL){
        cout<<"not found";
        return;
    }

    roomsOccupied[guest->info.RoomNo]=false;
    total--;
    guests.del(name);





        return;



    }


void displayInfo(Guest foundGuest){

        cout<<"Name:"<<foundGuest.name<<endl;
        cout<<"address:"<<foundGuest.startDate<<endl;
        cout<<"Check-in Date:"<<foundGuest.startDate<<endl;
        cout<<"Check-out Date:"<<foundGuest.endDate<<endl;
        cout<<"roomNo.:"<<foundGuest.RoomNo<<endl<<endl;

}


    void searchGuest(string name)
{
    node *parent, *guest;

    guests.find(name, &parent, &guest);
    if (guest == NULL)
    {
        cout<<"Guest not found"<<endl;
        return;
    }

    else{

        struct Guest foundGuest=guest->info;
        displayInfo(foundGuest);
    }


}




void checkNearestAvailable(){

    if(check.empty()){
        cout<<"No room occupied currently"<<endl;
    }
     Guest a[5];
    int i=0;
    while(!check.empty()&&i<5){
        a[i++]=check.top();
        check.pop();
        displayInfo(a[i-1]);

        }
    while(i>0){
        cout<<a[i-1].name;
        check.push(a[--i]);

}
return;



    }






void displayRooms()
{
    cout<<"Occupied "<<total<<"Available"<<500-total<<endl<<endl;
    cout<<"Occupied:"<<endl;
    for (int i = 81; i < 581; i++)
    {
        if(roomsOccupied[i]) cout<<i<<" ";
    }
    cout<<endl<<endl;
    cout<<"Available:"<<endl;

    for (int i = 81; i < 581; i++)
    {
        if(!roomsOccupied[i]) cout<<i<<" ";

        if(i%10==0) cout<<endl;
    }


}



void start()
{
    bool end=false;
    cout<<"ENTER YOUR CHOICE ACCORDING TO THE GIVEN OPTIONS"<<endl;
    cout<<"(Rooms Occupied: "<<total<<")"<<endl;



    cout<<"1. Check in a New Guest"<<endl;
    cout<<"2. Search for a guest"<<endl;
    cout<<"3. Display vacant and Occupied rooms"<<endl;
    cout<<"4. Check rooms which will be available shortly"<<endl;
    cout<<"5. Exit the portal"<<endl;
    cout<<"Enter your choice here --> ";
    int choice;
    cin>>choice;

    cout<<endl;
    switch(choice){

    case 1:{

        if(total<500) checkIn();

        else cout<<"There are no more empty rooms"<<endl;
        break;

        }

   case 2:{
        cout<<"Enter the name Of the Person You Want to search"<<endl<<endl;
        string a;
        cin>>a;
         searchGuest(a);
    break;}

   case 3:{
        displayRooms();
        break;}



    case 4:{

        checkNearestAvailable();
    break;
    }


   case 6:{

        cout<<"Are you sure you want to exit? (y/n)"<<endl;
        char confirmation;
        cin>>confirmation;
        if(confirmation=='y')
        {
            end=true;

        }
        break;}
    default:

        cout<<"INVALID INPUT"<<endl;
    }

   if(!end) start();
    }


int main()
{
    cout<<"****NIT SILCHAR QUARRENTINE CENTER****"<<endl;

        for (int i = 0; i < capacity; i++)
    {
        roomsOccupied[i]=false;
    }
    cout<<"Enter todays date --> in the  'yyyy-mm-dd' format only"<<endl;
    cin>>dateToday;


    //check until endDate is equal to todays date and keeps in checking out guest
     while(!check.empty()&&check.top().endDate==dateToday){

        checkOutGuest(check.top().name);

    }


    start();

}





