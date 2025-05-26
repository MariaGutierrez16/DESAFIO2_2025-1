#include <iostream>
#include "UdeAStay.h"

// Constructores
Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}

Fecha::Fecha(const Fecha& otra) {
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
}

// Destructor (vacío porque no hay memoria dinámica)
Fecha::~Fecha() {}

// Getters
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

// Setters
void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }

// Compara si dos fechas son iguales
bool Fecha::esIgual(const Fecha& otra) const {
    return (dia == otra.dia && mes == otra.mes && anio == otra.anio);
}

// Compara si esta fecha es menor que otra
bool Fecha::esMenor(const Fecha& otra) const {
    if (anio < otra.anio) return true;
    if (anio > otra.anio) return false;
    // mismo año, comparar mes
    if (mes < otra.mes) return true;
    if (mes > otra.mes) return false;
    // mismo mes, comparar día
    return (dia < otra.dia);
}

// Mostrar fecha en formato dd/mm/yyyy
void Fecha::mostrar() const {
    std::cout << (dia < 10 ? "0" : "") << dia << "/"
              << (mes < 10 ? "0" : "") << mes << "/"
              << anio;
}
