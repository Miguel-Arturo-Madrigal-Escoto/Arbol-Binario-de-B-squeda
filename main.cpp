#include <iostream>
#include "interface.h"
#include "btree.h"

using namespace std;

int main()
{
    BTree<Persona> myBTree;
    Interface myInterface(myBTree);

    return 0;
}
