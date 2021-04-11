#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <iostream>

class Persona{
    private:
        int id_persona;
        std::string nombre;
        std::string apellido;
    public:
        Persona();
        Persona(const Persona&);
        Persona(const int&, const std::string&, const std::string&);

        void setIdPersona(const int&);
        int getIdPersona() const;

        void setNombre(const std::string&);
        std::string getNombre() const;

        void setApellido(const std::string&);
        std::string getApellido() const;

        std::string toString();

        static bool compararId(const Persona&, const Persona&);

        bool operator == (const Persona&) const;
        bool operator != (const Persona&) const;
        bool operator < (const Persona&) const;
        bool operator <= (const Persona&) const;
        bool operator > (const Persona&) const;
        bool operator >= (const Persona&) const;

        friend std::ostream& operator << (std::ostream&, Persona&);
        friend std::istream& operator >> (std::istream&, Persona&);
};

#endif