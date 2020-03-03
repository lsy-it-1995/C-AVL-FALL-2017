#include <iostream>
#include "avl.h"
#include "treenodeforavl.h"
#include <locale>

using namespace std;

void testbaby();

int main()
{
    testbaby();
    return 0;
}

void testbaby()
{
    char userinput;
    int userinputnumber;
    avl<int> test1;
    avl<int> test2;
    //    test1.insert(5);
    //    test1.insert(50);
    //    test1.insert(15);
    //    test1.insert(5);
    //    test1.insert(5);
    //    cout<<test1<<endl;
    //    return;
    int item=0;
    srand(time(NULL));
    cout<<"[R]andom [I]nsert [C]lear [E]rase [S]earch c[O]py [A]dd e[X]it"<<endl;
    cin>>userinput;
    do{
        userinput = toupper(userinput);
        if(userinput=='R')
        {
            int f = rand()%100+1;
            test1.insert(f);
            cout<<test1<<endl;
        }
        else if(userinput=='I')
        {
            cout<<"insert a number"<<endl;
            cin>>item;
            test1.insert(item);
            cout<<test1<<endl;
        }
        else if(userinput=='C')
        {
            test1.clearall();
        }
        else if(userinput=='E')
        {
            tree_node<int> *found = NULL;
            cout<<"which number you want to erase from the tree"<<endl;
            cin>>userinputnumber;
            if(test1.search(userinputnumber,found))
            {
                test1.erase(userinputnumber);
                cout<<"here is your tree"<<endl<<test1<<endl;
            }
            else
            {
                cout<<"the number isn't in the tree"<<endl;
            }
        }
        else if(userinput=='S')
        {
            tree_node<int> *found = NULL;
            cout<<" WHAT NUMBER ARE YOU LOOKING FOR"<<endl;
            cin>>item;
            if(test1.search(item,found))
            {
                cout << "item found: " << endl;
            }
            else
            {
                cout<<"item isn't found"<<endl;
            }
        }
        else if(userinput=='X')
        {
            return;
        }
        else if(userinput == 'O')
        {
            test2 = test1;
            cout<<"copy tree looks like: "<<endl<<test2;
        }
        else if(userinput == 'A')
        {
            cout<<"adding your copied tree to your original tree"<<endl;
            test1+=test2;
            cout<<"the combination of tree is : "<<endl<<test1;
        }
        else
        {
            cout<<"try again"<<endl;
        }
        cout<<"[R]andom [I]nsert [C]lear [E]rase [S]earch c[O]py [A]dd e[X]it"<<endl;
    }while(cin>>userinput);
}
