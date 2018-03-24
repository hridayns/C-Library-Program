//--------------------------HEADER FILES USED-------------------------------
#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
#include<stdio.h>
#include<ctype.h>
//--------------------------------------------------------------------------

//---------------GLOBAL VARIABLES AND FUNCTION PROTOTYPES-------------------

char session_user[20];
void main_screen();
void admin_access();
void mem_login();
//--------------------------------------------------------------------------



//-------------------------CLASSES-----------------------------------


//--------------------------CLASS BOOKS------------------------------

class books
{
  private:
  char book_name[30];
  char author_name[30];
  char book_category[20];
  char book_description[80];
  char avail[20];

  public:
//-----------------CONSTRUCTOR OF CLASS BOOKS-------------------------------
  books()
  {
   strcpy(avail,"Available");
  }
//--------------------------------------------------------------------------

//-------------------------GETTER FUNCTIONS---------------------------------
  char* get_book_avail()
  {
   return avail;
  }
  char* get_book_name()
  {
   return book_name;
  }
  char* get_author_name()
  {
   return author_name;
  }
  char* get_book_category()
  {
   return book_category;
  }
  char* get_book_description()
  {
   return book_description;
  }
//--------------------------------------------------------------------------

//-----------------FUNCTION TO GET NEW BOOK DETAILS------------------------
  void new_book_details()
  {
   clrscr();
   cout<<"\nName of Book: ";gets(book_name);
   cout<<"\nAuthor: ";gets(author_name);
   cout<<"\nCategory: ";assign_category();
   cout<<"\nDescription: ";gets(book_description);
  }
//--------------------------------------------------------------------------

//-----------------FUNCTION TO SHOW BOOK DETAILS----------------------------
 void show_book_details()
  {
   cout<<"\nName of Book:\t"<<strupr(book_name)<<"\n";
   cout<<"\nAuthor:\t\t"<<author_name;
   cout<<"\nCategory:\t"<<book_category;
   cout<<"\nDescription:\t"<<book_description;
   cout<<"\n\nPress any key to show next book\n";
   getch();
  }
//--------------------------------------------------------------------------

//-------------------FUNCTIONS ON BOOKS IN CLASS BOOKS----------------------
  void add_book();
  void assign_category();
  void remove_book();
  void modify_book();
  void display_books();
  void change_avail_borrowed(char b_name[]);
  void change_avail_available(char b_name[]);
//--------------------------------------------------------------------------
};

books book;
//--------------------------------------------------------------------------

//-----------------FUNCTION TO MAKE BOOK BORROWED---------------------------
void books::change_avail_borrowed(char b_name[20])
{
 int pos;
 char bk_name[20];
 strcpy(bk_name,b_name);

 fstream book_mod("books.dat",ios::binary|ios::in|ios::out);
 while(!book_mod.eof())
 {
  book_mod.read((char*)&book,sizeof(books));
  if(strcmpi(bk_name,book.get_book_name())==0)
  {
   pos=book_mod.tellg();
   book_mod.seekp(pos-1*sizeof(book),ios::beg);
   strcpy(book.get_book_avail(),"Borrowed");
   book_mod.write((char*)&book,sizeof(books));
  }
  else if(book_mod.eof())break;
 }
  book_mod.close();

}
//--------------------------------------------------------------------------

//---------------------FUNCTION TO MAKE BOOK AVAILABLE----------------------
void books::change_avail_available(char b_name[20])
{
 int pos;
 char bk_name[20];
 strcpy(bk_name,b_name);

 fstream book_mod("books.dat",ios::binary|ios::in|ios::out);
 while(!book_mod.eof())
 {
  book_mod.read((char*)&book,sizeof(books));
  if(strcmpi(bk_name,book.get_book_name())==0)
  {
   pos=book_mod.tellg();
   book_mod.seekp(pos-1*sizeof(book),ios::beg);
   strcpy(book.get_book_avail(),"Available");
   book_mod.write((char*)&book,sizeof(books));
  }
  else if(book_mod.eof())break;
 }
  book_mod.close();
}
//--------------------------------------------------------------------------

//-------------------FUNCTION TO ASSIGN CATEGORY----------------------------
void books::assign_category()
  {
   int k;
   cout<<"\n\n1. Science Fiction\n2. Fiction\n3. Horror";
   cout<<"\n4. Fantasy\n5. Adventure\n6. Action\n7. Romance\n8. Comedy\n\n";

   cin>>k;

   switch(k)
   {
    case 1:
    strcpy(book_category,"Sci-Fiction");
    break;

    case 2:
    strcpy(book_category,"Fiction");
    break;

    case 3:
    strcpy(book_category,"Horror");
    break;

    case 4:
    strcpy(book_category,"Fantasy");
    break;

    case 5:
    strcpy(book_category,"Adventure");
    break;

    case 6:
    strcpy(book_category,"Action");
    break;

    case 7:
    strcpy(book_category,"Romance");
    break;

    case 8:
    strcpy(book_category,"Comedy");
    break;

    default:
    cout<<"\nChoose from Category!\n";
    assign_category();
    break;
   }
  }
//--------------------------------------------------------------------------

//--------------------FUNCTION TO MODIFY BOOKS------------------------------
void books::modify_book()
{
 char ch = 'y';
 char b_name[20];

 do
 {
 book.display_books();
 int found = -1;
 int pos;
 cout<<"\nBook to modify(name): ";gets(b_name);

 fstream book_mod("books.dat",ios::binary|ios::in|ios::out);


 while(!book_mod.eof())
 {
  book_mod.read((char*)&book,sizeof(books));

  if(strcmpi(book.get_book_name(),b_name)==0)
  {
   pos = book_mod.tellg();
   book.new_book_details();
   book_mod.seekp(pos-1*sizeof(books),ios::beg);
   book_mod.write((char*)&book,sizeof(books));
   found = 1;
  }
 }

 book_mod.close();

 if(found == -1)cout<<"\nNo such book found!\n";

 cout<<"\nModify more books? [Y/N]\n\n";
 cin>>ch;
 }
while(ch=='y' || ch=='Y');
}
//--------------------------------------------------------------------------

//-------------------------FUNCTION TO REMOVE BOOKS--------------------------
void books::remove_book()
{
 char ch = 'y';
 char b_name[20];
 int found;

 do
 {
 book.display_books();
 cout<<"\nBook to delete(name): ";gets(b_name);

 ifstream book_in("books.dat",ios::binary|ios::in);
 ofstream book_out("temp.dat",ios::binary|ios::app);

 found = -1;

 while(!book_in.eof())
 {
  book_in.read((char*)&book,sizeof(books));

  if(book_in.eof())break;

  else if(strcmpi(b_name,book.get_book_name())==0)found = 1;

  else if(strcmpi(b_name,book.get_book_name())!=0)
  {
  book_out.write((char*)&book,sizeof(books));
  }
 }

 book_in.close();
 book_out.close();

 remove("books.dat");
 rename("temp.dat","books.dat");

 if(found == -1)cout<<"\nNo such book found!\n";
 cout<<"\nRemove more books? [Y/N]\n\n";
 cin>>ch;
 }
while(ch=='y' || ch=='Y');
}
//--------------------------------------------------------------------------

//----------------------FUNCTION TO DISPLAY BOOKS---------------------------
void books::display_books()
{
 clrscr();
 ifstream book_in("books.dat",ios::binary|ios::in);

 while(!book_in.eof())
 {
  book_in.read((char*)&book,sizeof(books));

  if(book_in.eof())break;

 else if(strcmpi(book.get_book_avail(),"Available")==0)
   {
   book.show_book_details();
   }
 }
 book_in.close();

 cout<<"\nNo more books. Press any key to continue.\n";
 getch();
}
//--------------------------------------------------------------------------

//-------------------FUNCTION TO ADD BOOKS----------------------------------
void books::add_book()
{
 strcpy(book.get_book_avail(),"Available");
 char ch = 'y';
 ofstream book_out("books.dat",ios::binary|ios::app);
 do
 {
  book.new_book_details();

  book_out.write((char*)&book,sizeof(books));
  cout<<"\n\nAdd more? [Y/N]\n";
  cin>>ch;
 }
 while(ch=='y' || ch=='Y');
 book_out.close();
}
//--------------------------------------------------------


//---------------Class MEMBER------------------------------
class member
{
 private:
 char user[30];
 char pass[30];
 char phone[11];
 char borrowed_book[40];

 public:

//----------------CONSTRUCTOR OF CLASS MEMBER-------------------------------
 member()
 {
  strcpy(borrowed_book,"No Books borrowed");
 }
//--------------------------------------------------------------------------

//---------------------------GETTER FUNCTIONS-------------------------------
 char* get_user()
 {
  return user;
 }
 char* get_pass()
 {
  return pass;
 }
 char* get_phone()
 {
  return phone;
 }
 char* get_borrowed_book()
 {
  return borrowed_book;
 }
//--------------------------------------------------------------------------

//----------------------FUNCTION TO SHOW MEMBER DETAILS---------------------
 void show_member_details()
  {
   cout<<"\nName:\t\t"<<user;
   cout<<"\nPhone:\t\t"<<phone;
   cout<<"\nBook Borrowed:\t"<<borrowed_book;
   cout<<"\n\nPress any key to show next member\n";
   getch();
  }
//--------------------------------------------------------------------------

//----------------------FUNCTION TO GET MEMBER DETAILS----------------------
 void new_member_details()
 {
  clrscr();
  cout<<"\nUsername: ";
  cin>>user;

  cout<<"\nPassword: ";
  cin>>pass;

  cout<<"\nPhone: ";
  cin>>phone;
 }
//--------------------------------------------------------------------------

//---------------FUNCTION TO COPY NEW NAME OF BORROWED BOOK-----------------
 void assign_borrowed_book(char b_name[])
 {
  strcpy(borrowed_book,b_name);
 }
//--------------------------------------------------------------------------

//-----------FUNCTION TO CHECK USER AND PASS FOR MEMBER LOGIN---------------
 int check_login(char u_input[],char p_input[])
 {
   if(strcmp(u_input,user)==0 && strcmp(p_input,pass)==0)
   {
    return 1;
   }
   else return -1;
 }
//--------------------------------------------------------------------------

//-------------FUNCTION TO DISPLAY LIBRARY HOME IN CLASS MEMBER-------------
 void home();
//--------------------------------------------------------------------------

//------------FUNCTION TO SUBSCRIBE AS A MEMBER IN CLASS MEMBER-------------
 void subscribe();
//--------------------------------------------------------------------------

//-----------FUNCTIONS TO BROWSE/SEARCH FOR BOOKS IN CLASS MEMBER-----------
 void browse_books();
 void browse_by_name();
 void browse_by_author();
//--------------------------------------------------------------------------

//--------------FUNCTIONS TO BORROW/RETURN BOOKS IN CLASS MEMBER------------
 void borrow_book(char b_name[]);
 void return_book();
//--------------------------------------------------------------------------

//---------FUNCTIONS FOR BORROWED BOOK BY MEMBERS IN CLASS MEMBER-----------
 void change_borrowed_book(char b_name[]);
 void return_borrowed_book();
 void display_borrowed_books();
 int check_can_borrow(char usr[]);
//--------------------------------------------------------------------------
};

member mem;
//--------------------------------------------------------------------------

//----------------FUNCTION FOR USER TO SUBSCRIBE AS MEMBER------------------
void member::subscribe()
{
 clrscr();

 ofstream mem_out("members.dat",ios::binary|ios::app);

  mem.new_member_details();

  mem_out.write((char*)&mem,sizeof(member));

  mem_out.close();

 cout<<"\nSuccessfully subscribed!\n";
 getch();
 main_screen();
}
//--------------------------------------------------------------------------

//-------------FUNCTION TO RETURN BORROWED BOOK FOR MEMBER------------------
void member::return_borrowed_book()
{
 int found = -1;
 int pos;

 fstream mem_mod("members.dat",ios::binary|ios::in|ios::out);

 while(!mem_mod.eof())
 {
  mem_mod.read((char*)&mem,sizeof(member));
  if(strcmpi(session_user,mem.get_user())==0)
  {
   pos = mem_mod.tellg();
   mem.assign_borrowed_book("No books borrowed");
   mem_mod.seekp(pos-1*sizeof(mem),ios::beg);
   mem_mod.write((char*)&mem,sizeof(member));
   found = 1;
  }
 }

 mem_mod.close();

 if(found == -1)
 {
 cout<<"\nFailed to Return!\n";
 getch();
 }
}
//--------------------------------------------------------------------------

//---------------FUNCTION TO UPDATE BORROWED BOOK FOR MEMBER----------------
void member::change_borrowed_book(char b_name[])
{
 int found = -1;
 int pos;

 fstream mem_mod("members.dat",ios::binary|ios::in|ios::out);

 while(!mem_mod.eof())
 {
  mem_mod.read((char*)&mem,sizeof(member));
  if(strcmpi(session_user,mem.get_user())==0)
  {
   pos = mem_mod.tellg();
   mem.assign_borrowed_book(b_name);
   mem_mod.seekp(pos-1*sizeof(mem),ios::beg);
   mem_mod.write((char*)&mem,sizeof(member));
   found = 1;
  }
 }

 mem_mod.close();

 if(found == -1)
 {
 cout<<"\nFailed to Borrow!\n";
 getch();
 }
}
//--------------------------------------------------------------------------

//------------------FUNCTION TO CHECK IF MEMBER CAN BORROW------------------
int member::check_can_borrow(char usr[20])
 {
  ifstream mem_in("members.dat",ios::binary|ios::in);

 while(!mem_in.eof())
 {
  mem_in.read((char*)&mem,sizeof(member));
  if(strcmpi(usr,mem.get_user())==0)
  {
   if(strcmpi(mem.get_borrowed_book(),"No books borrowed")==0)
   return 1;
  }
 }
 mem_in.close();

 return -1;
}
//--------------------------------------------------------------------------

//----------------------FUNCTION TO RETURN A BOOK---------------------------
void member::return_book()
{
 char ch;
 mem.display_borrowed_books();
 cout<<"\nAre you sure you want to return this book? [Y/N]\n";
 cin>>ch;

 if(ch=='Y' || ch=='y')
 {
 book.change_avail_available(mem.get_borrowed_book());//MAKING BOOK "AVAILABLE"
 mem.return_borrowed_book(); //RETURNING BORROWED BOOK
 cout<<"Book has successfully been returned!";
 getch();
 }
 mem.home();
}
//--------------------------------------------------------------------------

//--------------------FUNCTION TO BORROW BOOK-------------------------------
void member::borrow_book(char b_name[])
{
 clrscr();
 char bk_name[20];
 strcpy(bk_name,b_name);
 book.change_avail_borrowed(b_name);//AVAILABILITY OF BOOK CHANGED
 mem.change_borrowed_book(bk_name);//NAME OF BORROWED BOOK UPDATED
}
//--------------------------------------------------------------------------

//-----------------FUNCTION TO DISPLAY BORROWED BOOKS-----------------------
void member::display_borrowed_books()
{
 clrscr();
 char rt_book[20];
 ifstream mem_in("members.dat",ios::binary|ios::in);

 while(!mem_in.eof())
 {
  mem_in.read((char*)&mem,sizeof(member));
  if(strcmpi(session_user,mem.get_user())==0)
  {
  strcpy(rt_book,mem.get_borrowed_book());
  cout<<"Book to Return: "<<mem.get_borrowed_book()<<endl;
  getch();
  break;
  }
  else if(mem_in.eof())break;
 }

 ifstream book_in("books.dat",ios::binary|ios::in);
 while(!book_in.eof())
 {
  book_in.read((char*)&book,sizeof(book));

  if(book_in.eof())break;

  else if(strcmpi(book.get_book_name(),rt_book)==0)
   {
  book.show_book_details();
   }
  }
 book_in.close();
}
//--------------------------------------------------------------------------

//------------FUNCTION TO SEARCH/BROWSE BOOKS BY BOOK NAME------------------
void member::browse_by_name()
{
 clrscr();
 char b_name[20];
 char ch = 'y';
 int found;

 ifstream book_in("books.dat",ios::binary|ios::in);
 ofstream mem_out("members.dat",ios::binary|ios::out|ios::ate);

  found = -1;
  book.display_books();
  cout<<"\nName of Book: ";gets(b_name);

   while(!book_in.eof())
  {
   book_in.read((char*)&book,sizeof(books));


   if(strcmpi(book.get_book_name(),b_name)==0)
   {
   found = 1;
   break;
   }

   else if(book_in.eof())break;
  }

 book_in.close();
 mem_out.close();

 if(found == -1)
 {
 cout<<"\nNo such book found!\n";
 cout<<"\nTry again? [Y/N]\n";
 cin>>ch;
 if(ch=='y' || ch=='Y')browse_by_name();

 }

 else if(found == 1)
 {
  clrscr();
  book.show_book_details();
  cout<<"\nBorrow book? [Y/N]\n";
  cin>>ch;
  if(ch=='y' || ch=='Y')
   {
   if(mem.check_can_borrow(session_user)==1)
    {
   mem.borrow_book(book.get_book_name());
    }
   else
   {
    cout<<"\nPlease return the book you've borrowed first!\n";
    getch();
   }
  }
 }

 mem.home();
}
//--------------------------------------------------------------------------

//----------FUNCTION TO SEARCH/BROWSE BOOKS BY AUTHOR NAME------------------
void member::browse_by_author()
{
 clrscr();
 char a_name[20];
 char ch = 'y';
 int found;

 ifstream book_in("books.dat",ios::binary|ios::in);
 ofstream mem_out("members.dat",ios::binary|ios::out|ios::ate);

  found = -1;
  book.display_books();
  cout<<"\nName of Author: ";gets(a_name);

   while(!book_in.eof())
  {
   book_in.read((char*)&book,sizeof(books));


   if(strcmpi(book.get_author_name(),a_name)==0)
   {
   found = 1;
   break;
   }

   else if(book_in.eof())break;
  }

 book_in.close();
 mem_out.close();

 if(found == -1)
 {
 cout<<"\nNo such author found!\n";
 cout<<"\nTry again? [Y/N]\n";
 cin>>ch;
 if(ch=='y' || ch=='Y')browse_by_author();

 }

 else if(found == 1)
 {
  clrscr();
  book.show_book_details();
  cout<<"\nBorrow book? [Y/N]\n";
  cin>>ch;
  if(ch=='y' || ch=='Y')
   {
   if(mem.check_can_borrow(session_user)==1)
    {
   mem.borrow_book(book.get_book_name());
    }
   else
   {
    cout<<"\nPlease return the book you've borrowed first!\n";
    getch();
   }
  }
 }
 mem.home();
}
//--------------------------------------------------------------------------

//------------FUNCTION TO SELECT HOW TO SEARCH/BROWSE BOOKS-----------------
void member::browse_books()
{
 clrscr();
  int k;
  cout<<"\n\n"<<setw(50)<<"BROWSE BOOKS\n\n";
  cout<<"1. By book name\n\n2. By book author\n\n3. Go Back\n\n";
  cin>>k;

  switch(k)
  {
   case 1:
   browse_by_name();
   break;

   case 2:
   browse_by_author();
   break;

   case 3:
   home();
   break;

   default:
   browse_books();
   break;
  }
  getch();
}
//--------------------------------------------------------------------------

//---------------FUNCTION TO DISPLAY LIBRARY HOME PAGE----------------------
void member::home()
 {
  clrscr();
  int k;
  cout<<"\n\n"<<setw(50)<<"WELCOME TO THE LIBRARY\n\n";
  cout<<"1. Browse Books\n\n2. Return Book\n\n3. Logout\n\n";
  cin>>k;

  switch(k)
  {
   case 1:
   browse_books();
   break;

   case 2:
   return_book();
   break;

   case 3:
   main_screen();
   break;

   default:
   home();
   break;
  }
  getch();
 }
//--------------------------------------------------------------------------


//-----------------------CLASS ADMIN----------------------------------------
class admin
{
  public:
//----------------FUNCTION FOR ADMIN PANEL IN CLASS ADMIN-------------------
  void admin_panel();
//--------------------------------------------------------------------------

//-----------FUNCTIONS FOR LIBRARY MEMBERS IN CLASS ADMIN-------------------

  void member_operations();
  void add_member();
  void remove_member();
  void modify_member();
  void display_members();
//--------------------------------------------------------------------------

//---------------------BOOK FUNCTIONS IN CLASS ADMIN------------------------
  void book_operations();
//--------------------------------------------------------------------------
};

admin admin;
//--------------------------------------------------------------------------

//------------------------FUNCTION TO MODIFY MEMBER-------------------------
void admin::modify_member()
{
 char ch = 'y';
 char m_name[20];

 do
 {
 admin.display_members();
 int found = -1;
 int pos;
 cout<<"\nMember to modify(name): ";gets(m_name);

 fstream mem_mod("members.dat",ios::binary|ios::in|ios::out);


 while(!mem_mod.eof())
 {
  mem_mod.read((char*)&mem,sizeof(member));

  if(strcmpi(mem.get_user(),m_name)==0)
  {
   pos = mem_mod.tellg();
   mem.new_member_details();
   mem_mod.seekp(pos-1*sizeof(mem),ios::beg);
   mem_mod.write((char*)&mem,sizeof(member));
   found = 1;
  }

 }

 mem_mod.close();

 if(found == -1)cout<<"\nNo such member found!\n";

 cout<<"\nModify more member? [Y/N]\n\n";
 cin>>ch;
}
while(ch=='y' || ch=='Y');
}
//--------------------------------------------------------------------------

//--------------------------FUNCTION TO REMOVE MEMBER-----------------------
void admin::remove_member()
{
 char ch = 'y';
 char m_name[20];
 int found;

 do
 {
 admin.display_members();
 cout<<"\nMember to delete(name): ";gets(m_name);

 ifstream mem_in("members.dat",ios::binary|ios::in);
 ofstream mem_out("temp.dat",ios::binary|ios::app);

 found = -1;

 while(!mem_in.eof())
 {
  mem_in.read((char*)&mem,sizeof(member));

  if(mem_in.eof())break;

  else if(strcmp(m_name,mem.get_user())==0)
  {
  found = 1;
  book.change_avail_available(mem.get_borrowed_book());  //remove this incase of problems
  }

  else if(strcmp(m_name,mem.get_user())!=0)
  {
  mem_out.write((char*)&mem,sizeof(member));
  }
 }

 mem_in.close();
 mem_out.close();

 remove("members.dat");
 rename("temp.dat","members.dat");

 if(found == -1)cout<<"\nNo such member found!\n";
 cout<<"\nRemove more members? [Y/N]\n\n";
 cin>>ch;
 }
while(ch=='y' || ch=='Y');
}
//--------------------------------------------------------------------------

//------------------------FUNCTION TO ADD MEMBER----------------------------
void admin::add_member()
{
 char ch = 'y';
 ofstream mem_out("members.dat",ios::binary|ios::app);
 do
 {
  mem.new_member_details();

  mem_out.write((char*)&mem,sizeof(member));

  cout<<"\n\nAdd more? [Y/N]\n";
  cin>>ch;
 }
 while(ch=='y' || ch=='Y');

 mem_out.close();
}


void admin::display_members()
{
 clrscr();
 ifstream mem_in("members.dat",ios::binary|ios::in);
 while(!mem_in.eof())
 {
  mem_in.read((char*)&mem,sizeof(member));
  if(mem_in.eof())break;
  else mem.show_member_details();
 }
 mem_in.close();
 cout<<"\nNo more members. Press any key to continue.\n";
 getch();
}
//--------------------------------------------------------------------------

//--------------------FUNCTION TO SHOW ADMIN PANEL--------------------------
void admin::admin_panel()
  {
   clrscr();
   int k;
   cout<<endl<<setw(50)<<"ADMIN PANEL\n\n\n";
   cout<<"1. Members\n\n2. Books\n\n3. Logout\n\n";
   cin>>k;
   switch(k)
   {
    case 1:
    member_operations();
    break;

    case 2:
    book_operations();
    break;

    case 3:
    main_screen();
    break;

    default:
    admin_panel();
    break;
   }
  }
//--------------------------------------------------------------------------

//-------------------FUNCTION TO SELECT OPERATION ON MEMBERS----------------
void admin::member_operations()
  {
   clrscr();
    int k;
    cout<<"\n1. Add Members\n\n2. Remove Members\n\n3. Modify Members\n\n4. Display Members\n\n5. Back\n\n";
    cin>>k;
    switch(k)
    {
     case 1:
     add_member();
     break;

     case 2:
     remove_member();
     break;

     case 3:
     modify_member();
     break;

     case 4:
     display_members();
     break;

     default:
     admin_panel();
     break;
     }
   member_operations();
  }
//--------------------------------------------------------------------------

//--------------------FUNCTION TO SELECT OPERATION ON BOOKS-----------------
void admin::book_operations()
  {
   clrscr();
    int k;
    cout<<"\n1. Add Books\n\n2. Remove Books\n\n3. Modify Books\n\n4. Display Books\n\n5. Back\n\n";
    cin>>k;
    switch(k)
    {
     case 1:
     book.add_book();
     break;

     case 2:
     book.remove_book();
     break;

     case 3:
     book.modify_book();
     break;

     case 4:
     book.display_books();
     break;

     default:
     admin_panel();
     break;
     }
     book_operations();
  }
//--------------------------------------------------------------------------

//----------------------------GLOBAL FUNCTIONS------------------------------
void admin_access()
{
 int i;
 char user[20],pass[20];
 char ch = 'y';
 do
 {
 clrscr();
 cout<<"\n\n"<<setw(45)<<"ADMIN LOGIN"<<"\n";


 cout<<"\nUsername: ";
 cin>>user;
 cout<<"\nPassword: ";

   for(i=0;i<4;i++)
 {
  pass[i]=getch();
  cout<<'*';
 }
  pass[i]='\0';


if(strcmp(user,"admin")==0 && strcmp(pass,"pass")==0)
{
cout<<"\n\nACCESS GRANTED. Press anything to continue.\n";
getch();
admin.admin_panel();
}
 else
  {
  cout<<"\n\nACCESS DENIED. Try again? [Y/N]\n";
  cin>>ch;
  }
 }
 while(ch=='y' || ch=='Y');

 main_screen();
}
//--------------------------------------------------------------------------

//---------------------------MEMBER LOGIN-----------------------------------
void mem_login()
 {
  char pass_input[20];
  int auth;
  char ch = 'y';

  do
  {
  clrscr();
  auth = -1;

  cout<<"\n\n"<<setw(45)<<"MEMBER LOGIN\n\n";

  cout<<"\nUsername: ";
  cin>>session_user;

  cout<<"\nPassword: ";
  cin>>pass_input;

  ifstream in_mems("members.dat",ios::binary|ios::in);

  while(!in_mems.eof())
  {
   in_mems.read((char*)&mem,sizeof(mem));
   if(mem.check_login(session_user,pass_input)==1)
   {
    auth = 1;
   }
  }
  in_mems.close();

  if(auth == 1)break;

  else if(auth == -1)
  {
   cout<<"\n\nTry again? [Y/N]\n";
   cin>>ch;
  }
 }
 while(ch=='y' || ch=='Y');

 if(auth == 1)mem.home();

 main_screen();
}
//--------------------------------------------------------------------------

//--------------------------STARTING SCREEN---------------------------------
void main_screen()
{
 clrscr();
 int k;
 cout<<"\n1. Admin\n\n2. Member\n\n3. Subscribe\n\n4. Exit\n\n";
 cin>>k;

 switch(k)
 {
  case 1:
  admin_access();
  break;

  case 2:
  mem_login();
  break;

  case 3:
  mem.subscribe();
  break;

  case 4:
  exit(0);
  break;

  default:
  main_screen();
  break;
  }
}

//--------------------------------------------------------------------------

void reset() //TEST FUNCTION

{
remove("members.dat");
remove("books.dat");
}


void main()
{
main_screen();
//reset();
}