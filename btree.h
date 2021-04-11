#ifndef BTREE_H
#define BTREE_H

#include <exception>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "persona.h"

template <class T>
class BTree{
    private:
        class Node{
            private:
                T* dataPtr;
                Node* left;
                Node* right;

            public:
                class Exception : public std::exception{
                    private:
                        std::string msg;

                    public:
                        explicit Exception(const char* message) : msg(message){}

                        explicit Exception(const std::string& message) : msg(message){}

                        virtual ~Exception() throw(){}

                        virtual const char* what() const throw() {
                                return msg.c_str();
                        }
                };

                Node();
                Node(const T&);

                ~Node();

                T* getDataPtr() const;
                T getData() const;
                Node*& getLeft();
                Node*& getRight();

                void setDataPtr(T*);
                void setData(const T&);
                void setLeft(Node*&);
                void setRight(Node*&);
        };
    public:
        typedef Node* Position;
    private:
        Position root;

        void copyAll(Position&, Position&);

        void deleteAll(Position&);

        void insertData(Position&, const T&);

        Position& findData(Position&, const T&);

        Position& getLowest(Position&);
        Position& getHighest(Position&);

        std::string toStringPreOrder(Position&);
        std::string toStringInOrder(Position&);
        std::string toStringPostOrder(Position&);

        void saveBTree(Position&, std::ofstream&);
        void loadBTree(Position&, std::ifstream&);

    public:
        class Exception : public std::exception{
            private:
                std::string msg;

            public:
                explicit Exception(const char* message) : msg(message){}

                explicit Exception(const std::string& message) : msg(message){}

                virtual ~Exception() throw(){}

                virtual const char* what() const throw() {
                    return msg.c_str();
                }
        };
    
        BTree();
        BTree(BTree&);

        ~BTree();

        bool isEmpty() const;

        void insertData(const T&);

        void deleteData(Position&);

        T retrieve(Position&) const;

        int getHeight(Position&);

        Position& findData(const T&);

        Position& getLowest();
        Position& getHighest();

        bool isLeaf(Position&) const;

        int getHeight();
        int getLeftHeight();
        int getRightHeight();

        std::string parsePreOrder();
        std::string parseInOrder();
        std::string parsePostOrder();

        void deleteAll();

        void saveBTree();
        void loadBTree();

        BTree& operator = (const BTree&);
};

///Node
template <class T>
BTree<T>::Node::Node() : dataPtr(nullptr), left(nullptr), right(nullptr){}

template <class T>
BTree<T>::Node::Node(const T& e) : dataPtr(new T(e)), left(nullptr), right(nullptr){
    if(dataPtr == nullptr){
        throw Exception("Memoria insuficiente, creando nodo");
    }
}

template <class T>
BTree<T>::Node::~Node(){
    delete dataPtr;
}

template <class T>
T BTree<T>::Node::getData() const{
    if(dataPtr == nullptr){
        throw Exception("Dato no existente, getData");
    }

    return *dataPtr;
}

template <class T>
typename BTree<T>::Node*& BTree<T>::Node::getLeft(){
    return left;
}

template <class T>
typename BTree<T>::Node*& BTree<T>::Node::getRight(){
    return right;
}

template <class T>
void BTree<T>::Node::setDataPtr(T* p){
    dataPtr = p;
}

template <class T>
void BTree<T>::Node::setData(const T& e){
    if(dataPtr == nullptr){
        if((dataPtr = new T(e)) == nullptr){
            throw Exception("Memoria no disponible, setData");
        }
    }
    else{
        *dataPtr = e;
    }
}

template <class T>
void BTree<T>::Node::setLeft(Node*& p){
    left = p;
}

template <class T>
void BTree<T>::Node::setRight(Node*& p){
    right = p;
}

/// BTree
template <class T>
void BTree<T>::copyAll(Position& r1, Position& r2){
    if(r1 == nullptr) return;

    if(!(r2 = new Node(r1->getData()))){
        throw Exception("Memoria no disponible, copyAll");
    }

    copyAll(r1->getLeft(), r2->getLeft());
    copyAll(r1->getRight(), r2->getRight());
}

template <class T>
BTree<T>::BTree() : root(nullptr){}

template <class T>
BTree<T>::BTree(BTree& t) : root(nullptr){
    copyAll(t.root, root);
}

template <class T>
BTree<T>::~BTree(){
    saveBTree();
    deleteAll();
}

template <class T>
bool BTree<T>::isEmpty() const{
    return root == nullptr;
}

template <class T>
void BTree<T>::insertData(const T& e){
    insertData(root, e);
}

template <class T>
void BTree<T>::insertData(Position& r, const T& e){
    /// arbol vacio
    if(r == nullptr){
        try{
            if((r = new Node(e)) == nullptr){
                throw Exception("Memoria no disponible, insertData");
            }
        }catch(typename Node::Exception ex){
            throw Exception(ex.what());
        }
    }
    /// arbol NO vacio
    else{
        if(e < r->getData()){
            insertData(r->getLeft(), e);
        }
        else{
            insertData(r->getRight(), e);
        }
    }
}

template <class T>
void BTree<T>::deleteData(Position& r){

    if(r == nullptr){
        throw Exception("Posicion invalida, deleteData");
    }

    if(isLeaf(r)){
        delete r;
        r = nullptr;
        return;
    }
    else{
        Position& pos(r->getLeft() != nullptr ? getHighest(r->getLeft())
                      : getLowest(r->getRight()));
        r->setData(pos->getData());
        deleteData(pos);
    }
}

template <class T>
T BTree<T>::retrieve(Position& r) const{
    return r->getData();
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(const T& e){
    return findData(root, e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(Position& r, const T& e){
    if(r == nullptr or r->getData() == e){
        return r;
    }

    if(e < r->getData()){
        return findData(r->getLeft(), e);
    }

    return findData(r->getRight(), e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(){
    return getLowest(root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(Position& r){
    if(r == nullptr or r->getLeft() == nullptr){
        return r;
    }

    return getLowest(r->getLeft());
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(){
    return getHighest(root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(Position& r){
    if(r == nullptr or r->getRight() == nullptr){
        return r;
    }

    return getHighest(r->getRight());
}

template <class T>
bool BTree<T>::isLeaf(Position& r) const{
    return r != nullptr and r->getLeft() == nullptr and r->getRight() == nullptr;
}

template <class T>
int BTree<T>::getHeight(){
    return getHeight(root);
}

template <class T>
int BTree<T>::getLeftHeight(){
    return getHeight(root->getLeft());
}

template <class T>
int BTree<T>::getRightHeight(){
    return getHeight(root->getRight());
}

template <class T>
int BTree<T>::getHeight(Position& r){
    if(r == nullptr){
        return 0;
    }

    int lH(getHeight(r->getLeft()));
    int rH(getHeight(r->getRight()));

    return (lH > rH ? lH : rH) + 1;
}

template <class T>
std::string BTree<T>::parsePreOrder(){
    return toStringPreOrder(root);
}

template <class T>
std::string BTree<T>::toStringPreOrder(Position& a){
    if(a == nullptr){
        return "";
    }

    std::string r(a->getData().toString());
    r+= toStringPreOrder(a->getLeft());
    r+= toStringPreOrder(a->getRight());

    return r;
}

template <class T>
std::string BTree<T>::parseInOrder(){
    return toStringInOrder(root);
}

template <class T>
std::string BTree<T>::toStringInOrder(Position& a){
    std::string r;

    if(a == nullptr){
        return "";
    }

    r += toStringInOrder(a->getLeft());
    r += a->getData().toString();
    r += toStringInOrder(a->getRight());

    return r;
}

template <class T>
std::string BTree<T>::parsePostOrder(){
    return toStringPostOrder(root);
}

template <class T>
std::string BTree<T>::toStringPostOrder(Position& a){
    std::string r;

    if(a == nullptr){
        return "";
    }

    r += toStringPostOrder(a->getLeft());
    r += toStringPostOrder(a->getRight());
    r +=  a->getData().toString();

    return r;
}

template <class T>
void BTree<T>::deleteAll(){
    deleteAll(root);
}

template <class T>
void BTree<T>::deleteAll(Position& r){
    if(r == nullptr) return;

    deleteAll(r->getLeft());
    deleteAll(r->getRight());

    delete r;
    r = nullptr;
}

template <class T>
void BTree<T>::saveBTree(){
    if(isEmpty()){
        throw Exception("Error al guardar; arbol vacio, saveBTree");
    }
    std::ofstream file("file01.txt");
    if(!file) throw Exception("Error al abrir el fichero");
    else saveBTree(this->root, file);
    file.close();
}

template <class T>
void BTree<T>::saveBTree(Position& r, std::ofstream& file){
    if(r == nullptr){
        file << "#" << "*";
        return;
    }

    file << r->getData().getIdPersona() << '|'
         << r->getData().getNombre() << '|'
         << r->getData().getApellido() << '*';
    saveBTree(r->getLeft(), file);
    saveBTree(r->getRight(), file);
}

template <class T>
void BTree<T>::loadBTree(){
    std::ifstream file("file01.txt");
    if(!file) throw Exception("Error al abrir el fichero");
    else loadBTree(this->root, file);
    file.close();
}

template <class T>
void BTree<T>::loadBTree(Position& r, std::ifstream& file){
    std::string line;

    if(!getline(file, line, '*') || line == "#") return;

    T persona;
    std::string temp;
    std::stringstream ss(line);

    getline(ss, temp, '|');
    persona.setIdPersona(stoi(temp));
    getline(ss, temp, '|');
    persona.setNombre(temp);
    getline(ss, temp);
    persona.setApellido(temp);

    if(!(r = new Node(persona))) throw Exception("Error al cargar, loadBTree");

    loadBTree(r->getLeft(), file);
    loadBTree(r->getRight(), file);
}

/*template <class T>
void BTree<T>::loadBTree(Position& r, std::ifstream& file){
    T persona;
    std::string line, temp;
    
    try{
        while(getline(file, line, '*')){
            std::stringstream ss(line);

            getline(ss, temp, '|');
            persona.setIdPersona(stoi(temp));
            getline(ss, temp, '|');
            persona.setNombre(temp);
            getline(ss, temp);
            persona.setApellido(temp);

            insertData(persona);
        }
    }catch(BTree<T>::Exception ex){
        std::cout << ex.what() << std::endl;
    }
    file.close();
}*/

template <class T>
BTree<T>& BTree<T>::operator = (const BTree<T>& t){
    deleteAll();

    copyAll(t.root, root);

    return *this;
}

#endif // BTREE_H_INCLUDED
