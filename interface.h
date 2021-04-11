#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "persona.h"
#include "btree.h"

class Interface{
    private:
      void userInterface(BTree<Persona>&);
      void insertInterface(BTree<Persona>&);
      void deleteInterface(BTree<Persona>&);
      void findInterface(BTree<Persona>&);
      void saveBTree(BTree<Persona>&);
      void loadBTree(BTree<Persona>&);

  public:
      Interface(BTree<Persona>&);
};

#endif // INTERFACE_H_INCLUDED
