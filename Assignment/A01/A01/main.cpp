#include <iostream>
#include "Queue.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
void Wrapper();

int main()
{
    Wrapper();
    _CrtDumpMemoryLeaks();
}

void Wrapper() {

	//Create Queues
    Queue<int>* ints = new Queue<int>();
    Queue<char>* chars = new Queue<char>();
    Queue<float>* floats = new Queue<float>();

	cout << "Is the queue empty? " << ints->IsEmpty() << endl;

    //Populate Queues
    for (int i = 5; i > 0; i--) {
        ints->Push(i);
        floats->Push((i * 867) % 11);
        chars->Push(i + 45);
    }

    cout << "\nIs the queue empty? " << ints->IsEmpty() << endl << endl;

    cout << "Printing contents of ints:";
    ints->Print();
    cout << "\nPrinting contents of chars:";
    chars->Print();
    cout << "\nPrinting contents of floats:";
    floats->Print();

    cout << endl << endl << "Popping items..." << endl;
    for (int i = 0; i < 3; i++) {
        ints->Pop();
        floats->Pop();
        chars->Pop();
    }

    cout << "\nPrinting contents of ints:";
    ints->Print();
    cout << "\nPrinting contents of chars:";
    chars->Print();
    cout << "\nPrinting contents of floats:";
    floats->Print();


    cout << "Adding numbers 1 and 10 to ints to test sorting..." << endl;
    ints->Push(1);
    ints->Push(10);
    cout << "\nPrinting contents of ints:";
    ints->Print();

    delete ints;
    delete floats;
    delete chars;

}