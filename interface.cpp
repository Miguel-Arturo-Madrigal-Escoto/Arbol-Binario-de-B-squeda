#include "interface.h"

using namespace std;

Interface::Interface(BTree<Persona>& myBTree){
    userInterface(myBTree);
}

void Interface::userInterface(BTree<Persona>& myBTree){
    int op;

    do{
        cout << " * Arbol Binario de Busqueda * " << endl << endl;
        cout << "1) Insertar elemento" << endl;
        cout << "2) Eliminar elemento" << endl;
        cout << "3) Buscar elemento" << endl;
        cout << "4) Recorrido PreOrden" << endl;
        cout << "5) Recorrido InOrden" << endl;
        cout << "6) Recorrido PostOrder" << endl;
        cout << "7) Guardar arbol" << endl;
        cout << "8) Cargar arbol" << endl;
        cout << "0) Salir del menu" << endl;
        cout << "-> Elige una opcion: ";
        cin >> op;

        switch(op)
        {
            case 0:
                break;

            case 1:
                insertInterface(myBTree);
                break;
            
            case 2:
                deleteInterface(myBTree);
                break;

            case 3:
                findInterface(myBTree);
                break;
            
            case 4:
                cout << myBTree.parsePreOrder();
                system("pause");
                system("cls");
                break;

            case 5:
                cout << myBTree.parseInOrder();
                system("pause");
                system("cls");
                break;

            case 6:
                cout << myBTree.parsePostOrder();
                system("pause");
                system("cls");
                break;

            case 7:
                saveBTree(myBTree);
                system("pause");
                system("cls");
                break;
            
            case 8:
                loadBTree(myBTree);
                system("pause");
                system("cls");
                break;

            default:
                deleteInterface(myBTree);
                break;
        }        
    }while(op != 0);

    cout << endl << endl;
    system("pause");
}

void Interface::insertInterface(BTree<Persona>& myBTree){
    Persona persona;
    char op;
    do{
        cout << " * Insertando Registro * " << endl;
        cin >> persona;

        try{
            myBTree.insertData(persona);
        }catch(BTree<Persona>::Exception ex){
            cout << ex.what() << endl;;
        }

        cout << "Desea insertar otro registro? (s/n): ";
        cin >> op; cin.sync();

    }while(tolower(op) != 'n');
    
    system("pause");
    system("cls");
}

void Interface::deleteInterface(BTree<Persona>& myBTree){
    Persona persona;
    int id;

    cout << " * Eliminando registro * " << endl;
    cout << "-> Ingresa el id del registro a eliminar: ";
    cin >> id; persona.setIdPersona(id);

    try{
        BTree<Persona>::Position& pos(myBTree.findData(persona));
        myBTree.deleteData(pos);
    }catch(BTree<Persona>::Exception ex){
        cout << ex.what() << endl;
    }

    system("pause");
    system("cls");
}

void Interface::findInterface(BTree<Persona>& myBTree){
    BTree<Persona>::Position pos;
    Persona persona;
    int id;
    cout << " * Buscando registro * " << endl;
    cout << "-> Ingresa el id del registro a buscar: ";
    cin >> id; persona.setIdPersona(id);

    try{
        pos = myBTree.findData(persona);
        cout << "La persona con id " << id;

        if(!pos) cout << " NO se encuentra en el árbol" << endl;
        else {
            persona = myBTree.retrieve(pos);
            cout << "Se encuentra en la posicion: " << pos << endl;
            cout << persona << endl;
        }
        
    }catch(BTree<Persona>::Exception ex){
        cout << ex.what() << endl;
    }

    system("pause");
    system("cls");
}

void Interface::saveBTree(BTree<Persona>& myBTree){
    try{
        myBTree.saveBTree();
    }catch(BTree<Persona>::Exception ex){
        cout << ex.what() << endl;
    }
}

void Interface::loadBTree(BTree<Persona>& myBTree){
    try{
        myBTree.loadBTree();
    }catch(BTree<Persona>::Exception ex){
        cout << ex.what() << endl;
    }
}