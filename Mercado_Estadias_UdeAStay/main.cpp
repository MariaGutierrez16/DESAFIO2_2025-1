#include <iostream>
#include <fstream>
#include <cstring>
#include "UdeAStay.h"

#define MAX_RESERVAS 100
#define MAX_ALOJAMIENTOS 100

// ================= Clase Fecha =================
Fecha::Fecha() : dia(1), mes(1), anio(2000) {}
Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}
Fecha::Fecha(const Fecha& otra) : dia(otra.dia), mes(otra.mes), anio(otra.anio) {}
Fecha::~Fecha() {}
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }
void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }
bool Fecha::esIgual(const Fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}
bool Fecha::esMenor(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}
void Fecha::mostrar() const {
    std::cout << (dia < 10 ? "0" : "") << dia << "/"
              << (mes < 10 ? "0" : "") << mes << "/" << anio;
}

// ================= Clase Usuario =================
Usuario::Usuario() : antiguedad(0), puntuacion(0.0f) { documento[0] = '\0'; }
Usuario::Usuario(const char* doc, int ant, float punt) : antiguedad(ant), puntuacion(punt) {
    strncpy(documento, doc, 19); documento[19] = '\0';
}
Usuario::Usuario(const Usuario& otro) : antiguedad(otro.antiguedad), puntuacion(otro.puntuacion) {
    strncpy(documento, otro.documento, 19); documento[19] = '\0';
}
Usuario::~Usuario() {}
const char* Usuario::getDocumento() const { return documento; }
int Usuario::getAntiguedad() const { return antiguedad; }
float Usuario::getPuntuacion() const { return puntuacion; }
void Usuario::setDocumento(const char* doc) {
    strncpy(documento, doc, 19); documento[19] = '\0';
}
void Usuario::setAntiguedad(int ant) { antiguedad = ant; }
void Usuario::setPuntuacion(float punt) { puntuacion = punt; }

// ================= Clase Huesped =================
Huesped::Huesped() : Usuario(), cantidadReservas(0), capacidadReservas(10) {
    codigosReservas = new int[capacidadReservas];
}
Huesped::~Huesped() {
    delete[] codigosReservas;
}
void Huesped::expandirCapacidad() {
    int nuevaCapacidad = capacidadReservas * 2;
    int* nuevoArreglo = new int[nuevaCapacidad];
    for (int i = 0; i < cantidadReservas; ++i)
        nuevoArreglo[i] = codigosReservas[i];
    delete[] codigosReservas;
    codigosReservas = nuevoArreglo;
    capacidadReservas = nuevaCapacidad;
}
void Huesped::agregarReserva(int codigo) {
    if (cantidadReservas == capacidadReservas)
        expandirCapacidad();
    codigosReservas[cantidadReservas++] = codigo;
}
void Huesped::mostrar() const {
    std::cout << "Huesped: " << documento << "\nAntiguedad: " << antiguedad
              << " meses\nPuntuacion: " << puntuacion << "\nReservas: ";
    for (int i = 0; i < cantidadReservas; ++i)
        std::cout << codigosReservas[i] << (i < cantidadReservas - 1 ? ", " : "\n");
}

// ================= Clase Anfitrion =================
Anfitrion::Anfitrion() : Usuario(), cantidadAlojamientos(0), codigosAlojamientos(nullptr) {}
Anfitrion::Anfitrion(const char* doc, int ant, float punt) : Usuario(doc, ant, punt), cantidadAlojamientos(0), codigosAlojamientos(nullptr) {}
Anfitrion::Anfitrion(const Anfitrion& otro) : Usuario(otro), cantidadAlojamientos(otro.cantidadAlojamientos) {
    if (cantidadAlojamientos > 0) {
        codigosAlojamientos = new char*[cantidadAlojamientos];
        for (int i = 0; i < cantidadAlojamientos; ++i) {
            int len = std::strlen(otro.codigosAlojamientos[i]);
            codigosAlojamientos[i] = new char[len + 1];
            std::strcpy(codigosAlojamientos[i], otro.codigosAlojamientos[i]);
        }
    } else {
        codigosAlojamientos = nullptr;
    }
}
Anfitrion::~Anfitrion() {
    for (int i = 0; i < cantidadAlojamientos; ++i)
        delete[] codigosAlojamientos[i];
    delete[] codigosAlojamientos;
}
void Anfitrion::agregarAlojamiento(const char* codigo) {
    char** nuevo = new char*[cantidadAlojamientos + 1];
    for (int i = 0; i < cantidadAlojamientos; ++i)
        nuevo[i] = codigosAlojamientos[i];
    int len = std::strlen(codigo);
    nuevo[cantidadAlojamientos] = new char[len + 1];
    std::strcpy(nuevo[cantidadAlojamientos], codigo);
    delete[] codigosAlojamientos;
    codigosAlojamientos = nuevo;
    cantidadAlojamientos++;
}
void Anfitrion::eliminarAlojamiento(const char* codigo) {
    int indice = -1;
    for (int i = 0; i < cantidadAlojamientos; ++i) {
        if (std::strcmp(codigosAlojamientos[i], codigo) == 0) {
            indice = i;
            break;
        }
    }
    if (indice == -1) return;
    delete[] codigosAlojamientos[indice];
    char** nuevo = (cantidadAlojamientos > 1) ? new char*[cantidadAlojamientos - 1] : nullptr;
    for (int i = 0, j = 0; i < cantidadAlojamientos; ++i)
        if (i != indice) nuevo[j++] = codigosAlojamientos[i];
    delete[] codigosAlojamientos;
    codigosAlojamientos = nuevo;
    cantidadAlojamientos--;
}
void Anfitrion::mostrar() const {
    std::cout << "Anfitrion: " << documento << "\nAntiguedad: " << antiguedad << " meses\nPuntuacion: " << puntuacion << "\nAlojamientos: ";
    for (int i = 0; i < cantidadAlojamientos; ++i)
        std::cout << codigosAlojamientos[i] << (i < cantidadAlojamientos - 1 ? ", " : "\n");
}

// ================= Clase Alojamiento =================
Alojamiento::Alojamiento() : precioNoche(0.0f), cantidadAmenidades(0) {
    codigo[0] = nombre[0] = tipo[0] = direccion[0] = municipio[0] = departamento[0] = documentoAnfitrion[0] = '\0';
    for (int i = 0; i < 365; ++i) fechasReservadas[i] = nullptr;
}
Alojamiento::Alojamiento(const char* cod, const char* nom, const char* t, const char* dir,
                         const char* mun, const char* depto, float precio, const char* docAnf) : precioNoche(precio), cantidadAmenidades(0) {
    std::strncpy(codigo, cod, 9); codigo[9] = '\0';
    std::strncpy(nombre, nom, 49); nombre[49] = '\0';
    std::strncpy(tipo, t, 19); tipo[19] = '\0';
    std::strncpy(direccion, dir, 99); direccion[99] = '\0';
    std::strncpy(municipio, mun, 49); municipio[49] = '\0';
    std::strncpy(departamento, depto, 49); departamento[49] = '\0';
    std::strncpy(documentoAnfitrion, docAnf, 19); documentoAnfitrion[19] = '\0';
    for (int i = 0; i < 365; ++i) fechasReservadas[i] = nullptr;
}
Alojamiento::Alojamiento(const Alojamiento& otro) : precioNoche(otro.precioNoche), cantidadAmenidades(otro.cantidadAmenidades) {
    std::strcpy(codigo, otro.codigo);
    std::strcpy(nombre, otro.nombre);
    std::strcpy(tipo, otro.tipo);
    std::strcpy(direccion, otro.direccion);
    std::strcpy(municipio, otro.municipio);
    std::strcpy(departamento, otro.departamento);
    std::strcpy(documentoAnfitrion, otro.documentoAnfitrion);
    for (int i = 0; i < cantidadAmenidades; ++i)
        std::strcpy(amenidades[i], otro.amenidades[i]);
    for (int i = 0; i < 365; ++i)
        fechasReservadas[i] = (otro.fechasReservadas[i] != nullptr) ? new Fecha(*otro.fechasReservadas[i]) : nullptr;
}
Alojamiento::~Alojamiento() {
    for (int i = 0; i < 365; ++i) delete fechasReservadas[i];
}
void Alojamiento::agregarAmenidad(const char* amenidad) {
    if (cantidadAmenidades < 5) {
        std::strncpy(amenidades[cantidadAmenidades], amenidad, 29);
        amenidades[cantidadAmenidades][29] = '\0';
        cantidadAmenidades++;
    }
}
void Alojamiento::agregarFechaReservada(const Fecha& f) {
    for (int i = 0; i < 365; ++i) {
        if (fechasReservadas[i] == nullptr) {
            fechasReservadas[i] = new Fecha(f);
            break;
        }
    }
}
bool Alojamiento::estaDisponible(const Fecha& f, int noches) const {
    for (int i = 0; i < 365; ++i) {
        if (fechasReservadas[i] != nullptr && fechasReservadas[i]->esIgual(f))
            return false;
    }
    return true;
}
void Alojamiento::mostrar() const {
    std::cout << "Codigo: " << codigo << "\nNombre: " << nombre << "\nTipo: " << tipo << "\nDireccion: " << direccion
              << "\nMunicipio: " << municipio << "\nDepartamento: " << departamento << "\nPrecio por noche: " << precioNoche
              << "\nDocumento Anfitrion: " << documentoAnfitrion << "\nAmenidades: ";
    for (int i = 0; i < cantidadAmenidades; ++i)
        std::cout << amenidades[i] << (i < cantidadAmenidades - 1 ? ", " : "\n");
}
const char* Alojamiento::getCodigo() const { return codigo; }
const char* Alojamiento::getDocumentoAnfitrion() const { return documentoAnfitrion; }
float Alojamiento::getPrecioNoche() const { return precioNoche; }
const char* Alojamiento::getMunicipio() const { return municipio; }

// ================= Clase Reserva =================
Reserva::Reserva() : codigo(0), cantidadNoches(0), monto(0.0f) {
    codigoAlojamiento[0] = documentoHuesped[0] = metodoPago[0] = anotacion[0] = '\0';
}
Reserva::Reserva(int cod, const char* codAloj, const char* docH, const Fecha& fEntrada,
                 int noches, const char* metodo, const Fecha& fPago, float montoPago, const char* nota)
    : codigo(cod), fechaEntrada(fEntrada), cantidadNoches(noches), fechaPago(fPago), monto(montoPago) {
    std::strncpy(codigoAlojamiento, codAloj, 9); codigoAlojamiento[9] = '\0';
    std::strncpy(documentoHuesped, docH, 19); documentoHuesped[19] = '\0';
    std::strncpy(metodoPago, metodo, 9); metodoPago[9] = '\0';
    std::strncpy(anotacion, nota, 1000); anotacion[1000] = '\0';
}
Reserva::Reserva(const Reserva& otra)
    : codigo(otra.codigo), fechaEntrada(otra.fechaEntrada), cantidadNoches(otra.cantidadNoches), fechaPago(otra.fechaPago), monto(otra.monto) {
    std::strcpy(codigoAlojamiento, otra.codigoAlojamiento);
    std::strcpy(documentoHuesped, otra.documentoHuesped);
    std::strcpy(metodoPago, otra.metodoPago);
    std::strcpy(anotacion, otra.anotacion);
}
Reserva::~Reserva() {}
void Reserva::mostrar() const {
    std::cout << "Codigo Reserva: " << codigo << "\nCodigo Alojamiento: " << codigoAlojamiento
              << "\nDocumento Huesped: " << documentoHuesped << "\nFecha Entrada: ";
    fechaEntrada.mostrar();
    std::cout << "\nCantidad Noches: " << cantidadNoches << "\nMetodo de Pago: " << metodoPago
              << "\nFecha Pago: ";
    fechaPago.mostrar();
    std::cout << "\nMonto: " << monto << "\nAnotacion: " << anotacion << "\n";
}
const Fecha& Reserva::getFechaEntrada() const { return fechaEntrada; }
int Reserva::getCantidadNoches() const { return cantidadNoches; }
const char* Reserva::getDocumentoHuesped() const { return documentoHuesped; }
const char* Reserva::getCodigoAlojamiento() const { return codigoAlojamiento; }
int Reserva::getCodigo() const { return codigo; }



Reserva reservas[MAX_RESERVAS];
Alojamiento alojamientos[MAX_ALOJAMIENTOS];
int numReservas = 0;
int numAlojamientos = 0;

void guardarReservasEnArchivo(const char* nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    for (int i = 0; i < numReservas; ++i) {
        archivo << reservas[i].getCodigo() << ","
                << reservas[i].getCodigoAlojamiento() << ","
                << reservas[i].getDocumentoHuesped() << ","
                << reservas[i].getFechaEntrada().getDia() << "/"
                << reservas[i].getFechaEntrada().getMes() << "/"
                << reservas[i].getFechaEntrada().getAnio() << ","
                << reservas[i].getCantidadNoches() << ","
                << "TCredito" << ","  // simplificado
                << reservas[i].getFechaEntrada().getDia() << "/"
                << reservas[i].getFechaEntrada().getMes() << "/"
                << reservas[i].getFechaEntrada().getAnio() << ","
                << "450000" << ","
                << "Anotacion ejemplo" << "\n";
    }
    archivo.close();
}

void menuHuesped() {
    int opcion;
    do {
        std::cout << "\n--- Menu Huesped ---\n";
        std::cout << "1. Hacer reserva\n";
        std::cout << "2. Eliminar reserva\n";
        std::cout << "3. Mostrar reservas\n";
        std::cout << "4. Volver al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            if (numReservas < MAX_RESERVAS) {
                Fecha entrada(1, 6, 2025);
                Fecha pago(30, 5, 2025);
                Reserva r(1001 + numReservas, "ALOJ001", "123456789", entrada, 2, "TCredito", pago, 300000, "Reserva automatica");
                reservas[numReservas++] = r;
                std::cout << "Reserva creada.\n";
            } else {
                std::cout << "Limite de reservas alcanzado.\n";
            }
            break;
        }
        case 2: {
            int codigo;
            std::cout << "Ingrese el codigo de reserva a eliminar: ";
            std::cin >> codigo;
            bool eliminado = false;
            for (int i = 0; i < numReservas; ++i) {
                if (reservas[i].getCodigo() == codigo) {
                    for (int j = i; j < numReservas - 1; ++j)
                        reservas[j] = reservas[j + 1];
                    --numReservas;
                    std::cout << "Reserva eliminada.\n";
                    eliminado = true;
                    break;
                }
            }
            if (!eliminado)
                std::cout << "Codigo no encontrado.\n";
            break;
        }
        case 3:
            for (int i = 0; i < numReservas; ++i)
                reservas[i].mostrar();
            break;
        }
    } while (opcion != 4);
}

void menuAnfitrion() {
    int opcion;
    do {
        std::cout << "\n--- Menu Anfitrion ---\n";
        std::cout << "1. Agregar alojamiento\n";
        std::cout << "2. Eliminar alojamiento\n";
        std::cout << "3. Mostrar alojamientos\n";
        std::cout << "4. Volver al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            if (numAlojamientos < MAX_ALOJAMIENTOS) {
                Alojamiento a("ALOJ001", "Casa", "Casa", "Dir", "Ciudad", "Depto", 150000, "987654321");
                a.agregarAmenidad("WiFi");
                alojamientos[numAlojamientos++] = a;
                std::cout << "Alojamiento agregado.\n";
            } else {
                std::cout << "Limite de alojamientos alcanzado.\n";
            }
            break;
        }
        case 2: {
            char cod[10];
            std::cout << "Ingrese el codigo del alojamiento a eliminar: ";
            std::cin >> cod;
            bool eliminado = false;
            for (int i = 0; i < numAlojamientos; ++i) {
                if (strcmp(alojamientos[i].getCodigo(), cod) == 0) {
                    for (int j = i; j < numAlojamientos - 1; ++j)
                        alojamientos[j] = alojamientos[j + 1];
                    --numAlojamientos;
                    std::cout << "Alojamiento eliminado.\n";
                    eliminado = true;
                    break;
                }
            }
            if (!eliminado)
                std::cout << "Codigo no encontrado.\n";
            break;
        }
        case 3:
            for (int i = 0; i < numAlojamientos; ++i)
                alojamientos[i].mostrar();
            break;
        }
    } while (opcion != 4);
}

int main() {
    int opcion;
    do {
        std::cout << "\n=== UdeAStay ===\n";
        std::cout << "1. Ingresar como Huesped\n";
        std::cout << "2. Ingresar como Anfitrion\n";
        std::cout << "3. Guardar reservas\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            menuHuesped();
            break;
        case 2:
            menuAnfitrion();
            break;
        case 3:
            guardarReservasEnArchivo("reservas.txt");
            std::cout << "Reservas guardadas en archivo.\n";
            break;
        }

    } while (opcion != 4);

    return 0;
}
