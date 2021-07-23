/*
TITLE : HOTEL BOOKING SYSTEM

GROUP MEMBERS:

 Sr.no         Roll_no.              Name

     1.        2401                  Bhakti Kulkarni
     2.        2421                  Bhakti Pagar
     3.        2423                  Yutika Patel
     4.        2424                  Riya Pathe
*/


#include <iostream>

using namespace std;



class Person
{
                                //person class storing person details
    string name;
    int age;
    int booking_id;
    int waiting_id;
    int no;
    int amount;
    Person *link;
    friend class Rooms;
    friend class Queue;
    friend class Hotel;
public:
	void accept();
	void display();
Person()        //person class constructor
{
	link=NULL;
	booking_id=0;
	waiting_id=0;
	amount=0;
}
};
void Person::accept()                               //accepting person details
{
    cout<<"\nEnter your name"<<endl;
    cin>>name;
    cout<<"Enter your age"<<endl;
    cin>>age;
    cout<<"Enter number of stay days "<<endl;
    cin>>no;
}

void Person::display()                          //displaying person details
{                           
 
	cout<<"Name: " <<name<<"   ";
	if(booking_id!=0)
	{
	cout<<"Booking ID: "<<booking_id<<"   ";
	}
	else
	{
	  cout<<"waiting ID: "<<waiting_id<<"   ";
	}
	cout<<"Age "<<age<<"   ";
	cout<<"Stay days: "<<no<<"   ";
	cout<<"Bill: "<<amount;
	cout<<endl;

}
class Queue
{                       // class queue
    Person *front;
    Person *rear;
    int count;
    friend class Rooms;
    friend class Person;
    friend class Hotel;
public:

    void enqueue(Person *n);
    Person *dequeue();
    bool isEmpty();
    void display_all();
    Queue(){
    	front=NULL;
    	rear=NULL;
    }
    
};
void Queue::display_all() 
{
   Person *temp = front;
   if (front == NULL) {
      cout<<"Waiting list is empty"<<endl;
      return;
   }
   cout<<"Waiting list elements are: \n";
   while (temp != NULL)
   {

      temp->display();
      temp = temp->link;
   }
   cout<<endl;
}
void Queue::enqueue(Person *n)    //enqueue in queue
{
	
	if(front==NULL)   //if queue is empty
	{
	   front=rear=n;
	}
	else                //if queue is not empty
	{
		rear->link=n;
		rear=n;
	}
}



bool Queue::isEmpty(){
	if (front == NULL) {
		 return true;
		   }
	return false;
}

Person *Queue::dequeue()
{
    Person *p;
    if(front == NULL)
    {
        return NULL;
    }
    else
    {
        p = front;
        front = front->link;
        p->link=NULL;
        return p;
    }
}

class Rooms{				//due to call in main
	Queue q;
	Person *confirmed[6];
	friend class Queue;
	friend class Person;
	friend class Hotel;
	public:
	Rooms(){

	   
		for(int i=0;i<6;i++){

			confirmed[i]=new Person;
		}
	}

};



class Hotel{
public:
	string name;
	int price;
	int ratings;
	Rooms r;
	int nr;
	
	friend class Rooms;
	friend class node_region;
	friend class region_list;
    void cancel();
    void search_p(int id,int select);
    int accept();
	Hotel(){
		price=0;
		ratings=0;
	}
};
int Hotel::accept()
{  

    Person *p= new Person;                          // node pointer of person class
    p->accept();                                     // this accept function accept the person details 

    int flag=0,choice=0,i=0,amount=0;       
 	for(i=0;i<nr;i++)
 	{                                               // nr is the number of  hotel rooms // loop till the empty room found
      if(r.confirmed[i]->booking_id==0)             //originally the booking id of person is zero       
 	    {
 		    flag=1;                                      // confirmed is the array which stores the confirmed bookings
 		    break;
 		 }
 	}
 	if(flag==1)                                         // hotel room found
    { 
 	    r.confirmed[i]=p;
 	    r.confirmed[i]->booking_id=i+1;                 // then add person to confirmed list and increment the booking id
 					
 	    cout<<"Reservation successful your details are\n";
        p->amount=(this->price)*(p->no);
 	    r.confirmed[i]->display();
        
    }
 	else
 	{                                                   // empty room not found
 		  cout<<"Cannot make the above reservation (Full Reservations!). If you want to apply in waiting list enter 1 or enter 0 for exit\n";
 		  cin>>choice;
 		  if(choice==1)                                 // when user wants to go to waiting list
          { 
 		    	if(r.q.rear!=NULL)
 		    	{

 		    		    p->waiting_id=r.q.rear->waiting_id+1;    // assigning waiting id
 		        }
 		    	else
 		    	{
 		    	    p->waiting_id=1;
 		    	}
 		    	r.q.enqueue(p);                         // add person  to waiting list
 		    	cout<<"Your entries have been added in waiting list"<<endl;
 		        p->amount=(this->price)*(p->no);
                r.q.rear->display();
          }
        
 	}
 		    	
 	return p->amount;
}
void Hotel::cancel()                                           //function to cancel particular booking
{
    int book_id,ind;
	Person *dequed;
	Person *temp=r.q.front;
	cout<<"Enter your booking_id no which you want to cancel \n";
	cin>>book_id;                                               //accepting booking id to cancel
	ind=book_id-1;
	if(ind>=0 && ind<nr)                                        //checking if user is in confirmed list or not
	{
		r.confirmed[ind]->booking_id=0;
		cout<<"Reservation cancelled successfully \n";
		cout<<"Amount refunded: "<<r.confirmed[ind]->amount<<"\n\n";         //amount is refunded if booking is cancelled
		if(!r.q.isEmpty())
		{
		    while(temp!=NULL)
		    {
		        temp->waiting_id=temp->waiting_id-1;
		        temp=temp->link;
		    }
			dequed=r.q.dequeue();                               //dequeing customer from waiting list
			dequed->waiting_id=0;

			if(dequed!=NULL)
			{
			r.confirmed[ind]=dequed;
			r.confirmed[ind]->booking_id=ind+1;             //booking room for first person in waiting list
			cout<<"Reservation for the following passenger from waiting list has been made :-\n";
			r.confirmed[ind]->display();

			}
		}
	}
	else
	{
		cout<<"Not a valid booking id \n";              //ID not existing
	}
}

void Hotel::search_p(int id,int select)         // search person in hotel
{    
    if(select==0)                               // search in confirmed list
    {          
        if(id>=1 && id<=nr )
        {
            if(r.confirmed[id-1]->booking_id!=0)
            {
                r.confirmed[id-1]->display();
            }
            else
            {
                cout<<"Invalid id\n";
            }
        }
        else
        {
            cout<<"Invalid id\n";               // when id does not exist
        }
    }
    else                                        // search waiting list
    {  
        Person *ptr=r.q.front;      
        while(ptr!=NULL)                         //traversing waiting list to find the person
        {                   
            if(ptr->waiting_id==id)
            {
                ptr->display();
                break;
            }
            ptr=ptr->link;
        }
        if(ptr==NULL)
        {
            cout<<"Invalid id\n";                   // when id does not exist
        }
    }
}

class node_region
{
	public:
	string rname;//name of region
	int nh;//no of hotels
	Hotel reg_hotel[5];//array of hotels
	friend class Hotel;
	node_region *link;
	int flag_s;

	node_region(int nh)
	{
		this->nh=nh;
		for(int i=0;i<nh;i++)
		{
			//reg_hotel[i]=new Hotel();
			//cout<<reg_hotel[i]->name<<endl;
		}

	}
	friend class region_list;
	void add_hotel(string hotel_names[5][5],int price[5][5], int ratings[5][5],int r,int size[5][5]);
    Hotel search_h(string hotel_n);
    void quickSort(int l, int h);
    void display_allHotels(int r);
    

};
void node_region::display_allHotels(int r){
    
    for(int i=0;i<nh;i++){
        
        cout<<i+1<<"."<<"Name: "<<this->reg_hotel[i].name<<"\tPrice: "<<this->reg_hotel[i].price<<"\tRatings: "<<this->reg_hotel[i].ratings<<endl;
        
    }
}

void node_region::add_hotel(string hotel_names[5][5],int price[5][5], int ratings[5][5],int r,int size[5][5]){


	for(int i=0;i<nh;i++){
	    
		this->reg_hotel[i].name=hotel_names[r][i];
		
		this->reg_hotel[i].price=price[r][i];
		this->reg_hotel[i].ratings=ratings[r][i];
		this->reg_hotel[i].nr=size[r][i];
		
		}

}

Hotel node_region::search_h(string hotel_n){
    int i=0;
    for(i=0;i<nh;i++){
        if(this->reg_hotel[i].name==hotel_n){
            return reg_hotel[i];
        }
    }
    //return NULL;

}
void node_region::quickSort( int start, int end) //sorting hotels in a given region by prices
{
    int pivot, i, j;
if (start<end) 
{ 
pivot=start; //set pivot to start
i=start+1;   //leftmark
j=end;       //rightmark
while(i<=j)   //loop till leftmark<rightmark
{
while(this->reg_hotel[i].price <= this->reg_hotel[pivot].price)//loop till leftmark element is less than pivot element
{
  i++;//increment leftmark
} 
while(this->reg_hotel[j].price > this->reg_hotel[pivot].price)//loop till rightmark element is greater than pivot element
{
 j--;//decrement rightmark	
} 
if(i<j)//if leftmark<rightmark
{
 Hotel temp; 
temp=reg_hotel[i];
reg_hotel[i]=reg_hotel[j];
reg_hotel[j]=temp;//swap leftmark and rightmark	
}
}//end while
Hotel temp; 
temp=reg_hotel[pivot];
reg_hotel[pivot]=reg_hotel[j];
reg_hotel[j]=temp;//swap pivot and rightmark
quickSort(start,j-1); // sort first partition
quickSort(j+1,end); 
    
}
}


class region_list     //list of regions
{
public:
   node_region *head;      
     //2D array for hotels,price,ratings,no.of rooms in a hotel respectively of all regions
    string hotel_names[5][5]={{"Ibis_New_Delhi" , "Taj_Palace", "Eros_Hotel", "Novotel_Delhi", "Pride_Plaza"},{"Novotel_Mumbai" , "Taj_Lands" , "Grand_Hayatt" , "NULL" , "NULL"},{"The_Park_Chennai ", "Ibis_Chennai_OMR", "Novotel_Chennai_VMRS", "Courtyard_by_Mariott" ,"NULL" },{"The_Park" , "Hyatt_Hyder" ," Taj_Deccan" ,"NULL"  , "NULL" },{"Novotel", "Orchid" , "Ibis" , "Hyatt" , "NULL" }};
    int price[5][5]={{1900,4275,2500,3200,2350},{2500,4250,3500,0,0},{3500,1519,4350,2700,0},{2600,4530,2570,0,0},{2399,2499,1600,3187,0}};
    int ratings[5][5]={{3,4,5,5,4},{1,2,3,0,0},{3,4,5,4,0},{3,4,5,0,0},{3,4,5,2,0}};
    int size[5][5]={{2,2,3,4,5},{2,1,1,0,0},{2,1,1,1,0},{3,4,5,0,0},{3,4,5,2,0}};
    
   	region_list()    //constructor
   	{
              head=NULL;     //set head to NULL
            }

    friend class node_region;
	void add_hotel_region();
	void add_r(string r_name,int n);
	node_region* search_r(string n);     //method declaratins
	void display_H(int n);
	void display_Allregions();
	int ind_setter(string n);
};

void region_list::display_Allregions()    //display all regions
{
    cout<<"Regions are :"<<"\n";
    
    node_region *ptr=head;
    int i=1;
    while(ptr!=NULL)           //loop till ptr not equal to NULL
    {
    cout<<i<<"."<<ptr->rname;   //print region name
    ptr=ptr->link;              //increment ptr i.e go to next region
    cout<<"\n";
    i++;                      //increment i
    }
}

void region_list::display_H(int n)    //display all hotels of given region 
{

    switch(n){       
        
        case 0:{      //if region is Delhi
            node_region *region_node= this->search_r("Delhi");   //return node_region Delhi 
            region_node->display_allHotels(0);  //call display_allHotels
            break;
        }
        case 1:{      //if region is Mumbai
            node_region *region_node= this->search_r("Mumbai");   //return node_region Mumbai
            region_node->display_allHotels( 1);  //call display_allHotels
            break;
        }
        case 2:{      //if region is Chennai
            node_region *region_node= this->search_r("Chennai");   //return node_region Chennaii
            region_node->display_allHotels(2);  //call display_allHotels
            break;
        }
        case 3: {      //if region is Hyderabad
            node_region *region_node= this->search_r("Hyderabad");   //return node_region Hyderabad
            region_node->display_allHotels( 3);  //call display_allHotels
            break;
        }
        case 4:{      //if region is Pune
            node_region *region_node= this->search_r("Pune");   //return node_region Pune
            region_node->display_allHotels(4);  //call display_allHotels
            break;
        }
    
    }// end switch
    
}// end display_H


void region_list::add_hotel_region(){    //add hotels in each region
    int i=0;
	node_region *ptr= head;
	while(ptr!=NULL){

	   
		ptr->add_hotel( hotel_names,price,ratings,i,size);//call add_hotel
		//cout<<ptr->rname<<endl;
	//	cout<<ptr->reg_hotel[0]->name<<endl;
		i++;          //increment i
		ptr=ptr->link;  //goto next region

	}//end while

}//end add_hotel_region
void region_list::add_r(string r_name,int n)   //add region by passing region name and no. of hotels in a region
{
	
	node_region *temp=new node_region(n);  //create new node_region
	temp->rname=r_name;                    //add region name in new node temp
	if(head==NULL)
    {
         head=temp;   //make head pointing to temp
    }
    else
    {
    	node_region *ptr=head;    //set ptr to head
        while(ptr->link!=NULL)
        {
            ptr=ptr->link;   //traverse ptr

        }
        ptr->link=temp;
       
        //cout<<ptr->link->rname<<endl;

    }
    this->add_hotel_region();    //call add_hotel_region
}

node_region* region_list::search_r(string n)
{

	  	node_region * temp = head;

	  	while(temp!=NULL)
	  	{
	  		if(temp->rname == n)

	  		{
	  			return temp;

	  		}
	  		temp = temp->link;

	  	}
	  	return NULL;
}
int region_list::ind_setter(string n){
    node_region * temp = head;
    int i=0;
    while(temp!=NULL)
	  	{
	  		if(temp->rname == n)

	  		{
	  			
	  			return i;

	  		}
	  		temp = temp->link;
            i++;
	  	}
	  	return -1;
}

int main()                                          //driver class to display menu and all operations
{

    int choice=0,ind,books,operate,status,hotel_op,id=0, bill=0,total_bill=0;
    string select_region,select_hotel;                  // variables to accept region name &hotel name
	region_list l;                                  //object of region list
	node_region *ptr;
	Hotel hotel;

	l.add_r("Delhi",5);                             //adding regions to the list
	l.add_r("Mumbai",3);
	l.add_r("Chennai",4);
	l.add_r("Hyderabad",3);
	l.add_r("Pune",4);

    do{                                             //displaying the MENU
        cout<<"-------------------------------------------------------------\n";
        l.display_Allregions();
        cout<<"Enter the region \n";
        cin>>select_region;
        ptr=l.search_r(select_region);
        ind=l.ind_setter(select_region);
        do{                                        //displaying available operations
        cout<<"-------------------------------------------------------------\n";
        cout<<"1.Display all hotels of the selected region\n";
        cout<<"2.Display all hotels of the selected region price wise in increasing order\n";
        cout<<"3.Select a hotel\n";
        cout<<"4.Change region\n";
        cout<<"5.Exit\n";
        cin>>operate;

        switch(operate){                           //performing operation according to user input
            case 1:                                //displaying hotels of a particular region
            {
                l.display_H(ind);
                break;
            }
            case 2:
            {
                ptr->quickSort(0,(ptr->nh-1));     //displaying hotels of region sorted price wise in ascending order
                l.display_H(ind);
                break;
            }
            case 3:
            {
                cout<<"Enter the hotel name from the above list\n";//accepting hotel name from user
                cin>>select_hotel;
                hotel=ptr->search_h(select_hotel);                 //searching for entered hotel
                cout<<"Hotel Selected is "<<hotel.name<<endl;
                do{                                                //options available for a hotel
                cout<<"-------------------------------------------------------------\n";
                cout<<"1.Book rooms in this hotel\n";
                cout<<"2.Cancel confirmed rooms in this hotel\n";
                cout<<"3.Check your status\n";
                cout<<"4.Exit\n";
                cin>>hotel_op;
                switch(hotel_op){
                    case 1:                                        //booking rooms in a hotel
                    {
                        total_bill=0;
                        cout<<"Enter the number of bookings max:- "<<hotel.nr<<"\n";
                        cin>>books;
                        for(int i=0;i<books;i++)
                        {
                            bill=hotel.accept();
                            if(bill==0){
                                break;
                            }
                            total_bill=total_bill+bill;            //displaying price according to number of rooms
                        }
                        cout<<"\nThe total Bill is: "<<total_bill<<endl;
                        break;
                    }
                    case 2:                                         //to cancel booked rooms
                    {
                       hotel.cancel();
                       break;
                    }
                    case 3:                                        //user can check booking status using ID
                    {
                        cout<<"Enter 0 if you want to check your status in booking list or enter 1 if you want to check in waiting list\n";
                        cin>>status;
                        cout<<"Enter your id\n";
                        cin>>id;
                        if(status==0){                            //if user's booking is confirmed
                            hotel.search_p(id,0);
                        }else{
                            hotel.search_p(id,1);               //if user is in waiting list
                        }
                        break;
                    }
                }
                }while(hotel_op!=4);
                break;
            }
            case 4:                                             //if user wants to look in different region
            {
                break;
            }
            case 5:                                            //to come out of booking system
            {
                cout<<"Exited\n";
                break;
            }
            default:                                           //invalid choice entered by user
            {
                cout<<"Enter a valid choice\n";
            }
        }
        }while(operate!=5 && operate!=4);                         //continuing if prompted by user

    }while(operate!=5);                                          //coming out of main menu
  return 0;
}



/*
OUTPUT:

-----------------------------------------------------------
Regions are :
1.Delhi
2.Mumbai
3.Chennai
4.Hyderabad
5.Pune
Enter the region
Delhi
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
1
1.Name: Ibis_New_Delhi  Price: 1900     Ratings: 3
2.Name: Taj_Palace      Price: 4275     Ratings: 4
3.Name: Eros_Hotel      Price: 2500     Ratings: 5
4.Name: Novotel_Delhi   Price: 3200     Ratings: 5
5.Name: Pride_Plaza     Price: 2350     Ratings: 4
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
2
1.Name: Ibis_New_Delhi  Price: 1900     Ratings: 3
2.Name: Pride_Plaza     Price: 2350     Ratings: 4
3.Name: Eros_Hotel      Price: 2500     Ratings: 5
4.Name: Novotel_Delhi   Price: 3200     Ratings: 5
5.Name: Taj_Palace      Price: 4275     Ratings: 4
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
3
Enter the hotel name from the above list
Taj_Palace
Hotel Selected is Taj_Palace
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
1
Enter the number of bookings max:- 2
4

Enter your name
John
Enter your age
20
Enter number of stay days
2
Reservation successful your details are
Name: John   Booking ID: 1   Age 20   Stay days: 2   Bill: 8550

Enter your name
Molly
Enter your age
35
Enter number of stay days
1
Reservation successful your details are
Name: Molly   Booking ID: 2   Age 35   Stay days: 1   Bill: 4275

Enter your name
Harry
Enter your age
25
Enter number of stay days
4
Cannot make the above reservation (Full Reservations!). If you want to apply in waiting list enter 1 or enter 0 for exit
1
Your entries have been added in waiting list
Name: Harry   waiting ID: 1   Age 25   Stay days: 4   Bill: 17100

Enter your name
Emma
Enter your age
34
Enter number of stay days
5
Cannot make the above reservation (Full Reservations!). If you want to apply in waiting list enter 1 or enter 0 for exit
0

The total Bill is: 29925
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
3
Enter 0 if you want to check your status in booking list or enter 1 if you want to check in waiting list
0
Enter your id
2
Name: Molly   Booking ID: 2   Age 35   Stay days: 1   Bill: 4275
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
3
Enter 0 if you want to check your status in booking list or enter 1 if you want to check in waiting list
1
Enter your id
1
Name: Harry   waiting ID: 1   Age 25   Stay days: 4   Bill: 17100
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
2
Enter your booking_id no which you want to cancel
1
Reservation cancelled successfully
Amount refunded: 8550

Reservation for the following passenger from waiting list has been made :-
Name: Harry   Booking ID: 1   Age 25   Stay days: 4   Bill: 17100
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
3
Enter 0 if you want to check your status in booking list or enter 1 if you want to check in waiting list
0
Enter your id
1
Name: Harry   Booking ID: 1   Age 25   Stay days: 4   Bill: 17100
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
3
Enter 0 if you want to check your status in booking list or enter 1 if you want to check in waiting list
1
Enter your id
1
Invalid id
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
4
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
4
-------------------------------------------------------------
Regions are :
1.Delhi
2.Mumbai
3.Chennai
4.Hyderabad
5.Pune
Enter the region
Mumbai
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
1
1.Name: Novotel_Mumbai  Price: 2500     Ratings: 1
2.Name: Taj_Lands       Price: 4250     Ratings: 2
3.Name: Grand_Hayatt    Price: 3500     Ratings: 3
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
2
1.Name: Novotel_Mumbai  Price: 2500     Ratings: 1
2.Name: Grand_Hayatt    Price: 3500     Ratings: 3
3.Name: Taj_Lands       Price: 4250     Ratings: 2
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
3
Enter the hotel name from the above list
Novotel_Mumbai
Hotel Selected is Novotel_Mumbai
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
1
Enter the number of bookings max:- 2
2

Enter your name
Fred
Enter your age
32
Enter number of stay days
2
Reservation successful your details are
Name: Fred   Booking ID: 1   Age 32   Stay days: 2   Bill: 5000

Enter your name
George
Enter your age
45
Enter number of stay days
4
Reservation successful your details are
Name: George   Booking ID: 2   Age 45   Stay days: 4   Bill: 10000

The total Bill is: 15000
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
3
Enter 0 if you want to check your status in booking list or enter 1 if you want to check in waiting list
0
Enter your id
1
Name: Fred   Booking ID: 1   Age 32   Stay days: 2   Bill: 5000
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
3
Enter 0 if you want to check your status in booking list or enter 1 if you want to check in waiting list
1
Enter your id
2
Invalid id
-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
2
Enter your booking_id no which you want to cancel
1
Reservation cancelled successfully
Amount refunded: 5000

-------------------------------------------------------------
1.Book rooms in this hotel
2.Cancel confirmed rooms in this hotel
3.Check your status
4.Exit
4
-------------------------------------------------------------
1.Display all hotels of the selected region
2.Display all hotels of the selected region price wise in increasing order
3.Select a hotel
4.Change region
5.Exit
5
Exited

--------------------------------
Process exited after 411.4 seconds with return value 0
Press any key to continue . . .*/
