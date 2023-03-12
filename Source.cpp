#include <iostream>
#include<vector>            //Для  class vector
#include"Unique_ptr.h"      //Для мого власного Unique_ptr
#include<memory>            //Для  unique_ptr



 using std::cout;
 using std::cin ;
 using std::endl;

class myClass;
void  Test1();
void  Test2();
void  Test3();
void  Test4();
void  Test5();




int main()             //Головна функція точка входу в програму
{
    cout << "Let's go test" << endl << endl;

    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}



template<typename T>
void MyDeleter(T* ptr) 
{
    cout << "i'm delete pointer\n";
    delete ptr;
}


template<typename T>
struct MyDel 
{ 
    void operator() (T* ptr )
       {
        cout << "i'm delete pointer\n";
        delete ptr; 
       }
}; 


class myClass
{

public:
    int age = 10;
    myClass(int temp) : age( temp )
    {cout << " myClass() \n";};

    ~myClass() 
    { cout << " ~myClass() \n"; };

    void Show() 
    { cout << " Show() \n"; }
};

void Test1()
{   cout << "\n test #1 \n" << endl;
    
    Unique_ptr<int> ptr;
    cout << endl;
    Unique_ptr<float> pt1(nullptr);
}

void Test2()
{
    cout << "\n test #2\n " << endl;
    Unique_ptr<myClass> ptr { new myClass (50) };
    cout << "End test" << endl;
}

void Test3()
{
    cout << "\n test #3\n"  << endl;
    Unique_ptr<int>ptr1{ new int };   cout << endl;
    Unique_ptr<int>ptr2{ std::move (ptr1 )};    //Unique_ptr<int>ptr2{ ptr1 }; такий варіант не працює ptr1(lvalue)
    cout << "End test " << endl;
}
  
void Test4()
{
    cout << "\n test #4\n "   << endl;
    Unique_ptr<int, void (*)(int*) > ptr2{ new int(1) , MyDeleter };
    cout << "End test  " << endl;
}

void Test5()
{
    cout << "\n test #5\n " << endl;
    MyDel<int> Dl;

    cout << endl;
    Unique_ptr<int, MyDel<int>>  ptr1(   new  int (20), Dl  );
    cout << "End test " << endl;
}
