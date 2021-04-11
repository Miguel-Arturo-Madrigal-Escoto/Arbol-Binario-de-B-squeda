#include "persona.h"
#include <iostream>

using namespace std;

Persona::Persona(){}

Persona::Persona(const Persona& p): id_persona(p.id_persona), nombre(p.nombre), apellido(p.apellido){}

Persona::Persona(const int& id_persona, const string& nombre, const string& apellido){
    this->id_persona = id_persona;
    this->nombre = nombre;
    this->apellido = apellido;
}

void Persona::setIdPersona(const int& id_persona){
    this->id_persona = id_persona;
}
int Persona::getIdPersona() const{
    return this->id_persona;
}

void Persona::setNombre(const string& nombre){
    this->nombre = nombre;
}
string Persona::getNombre() const{
    return this->nombre;
}

void Persona::setApellido(const string& apellido){
    this->apellido = apellido;
}
string Persona::getApellido() const{
    return this->apellido;
}

string Persona::toString(){
    string myStr;

    myStr = "| Id: " + to_string(this->id_persona) + " | ";
    myStr += " Nombre: " + this->nombre + " | ";
    myStr += " Apellidos: " + this->apellido + " | \n";
    
    return myStr;
}

bool Persona::compararId(const Persona&x, const Persona& y){
    return x.id_persona == y.id_persona;
}

bool Persona::operator == (const Persona& p) const {
    return id_persona == p.id_persona;
}

bool Persona::operator != (const Persona& p) const {
    return id_persona != p.id_persona;
}

bool Persona::operator < (const Persona& p) const{
    return id_persona < p.id_persona;
}

bool Persona::operator <= (const Persona& p) const{
    return id_persona <= p.id_persona;
}

bool Persona::operator > (const Persona& p) const{
    return id_persona > p.id_persona;
}

bool Persona::operator >= (const Persona& p) const{
    return id_persona >= p.id_persona;
}

ostream& operator << (ostream& os, Persona& p){
    os << "| Id: " << to_string(p.id_persona) << " | ";
    os  << " Nombre: " << p.nombre << " | ";
    os << " Apellidos: " + p.apellido << " | " << endl;

    return os;
}

istream& operator >> (istream& is, Persona& p){
    cout << "Id: ";
    cin >> p.id_persona;

    cin.sync();

    cout << "Nombre: ";
    getline(std::cin, p.nombre);
    cout << "Apellido: ";
    getline(cin, p.apellido);
    
    return is;
}
