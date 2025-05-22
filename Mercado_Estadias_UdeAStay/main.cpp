#include "udeastay.h"
#include <fstream>

using namespace std;

// Guarda una reserva en un archivo
void guardarReservaEnArchivo(const Reserva* r, const char* nombreArchivo) {
    ofstream out(nombreArchivo, ios::app);
    if (!out) {
        cout << "Error al abrir archivo para escritura.\n";
        return;
    }

    out << r->getCodigoReserva() << ";"
        << r->getCodigoAlojamiento() << ";"
        << r->getDocumentoHuesped() << ";"
        << r->getFechaInicio().getDia() << "/"
        << r->getFechaInicio().getMes() << "/"
        << r->getFechaInicio().getAnio() << ";"
        << r->getNoches() << ";"
        << r->getMetodoPago() << ";"
        << r->getMonto() << ";"
        << r->getAnotaciones() << "\n";

    out.close();
    cout << "Reserva guardada en archivo.\n";
}

// Simula la lectura de reservas desde archivo
void leerReservasDesdeArchivo(const char* nombreArchivo) {
    ifstream in(nombreArchivo);
    if (!in) {
        cout << "Archivo no encontrado.\n";
        return;
    }

    cout << "\nContenido del archivo " << nombreArchivo << ":\n";
    string linea;
    while (getline(in, linea)) {
        cout << linea << "\n";
    }

    in.close();
}

// Guarda un usuario (huésped o anfitrión) en archivo
void guardarUsuarioEnArchivo(const Usuario* u, const char* tipo, const char* nombreArchivo) {
    ofstream out(nombreArchivo, ios::app);
    if (!out) {
        cout << "Error al abrir archivo de usuarios.\n";
        return;
    }

    out << tipo << ";"
        << u->getDocumento() << ";"
        << u->getAntiguedad() << ";"
        << u->getPuntuacion() << "\n";

    out.close();
    cout << tipo << " guardado en archivo.\n";
}

// Lee todos los usuarios desde el archivo
void leerUsuariosDesdeArchivo(const char* nombreArchivo) {
    ifstream in(nombreArchivo);
    if (!in) {
        cout << "Archivo de usuarios no encontrado.\n";
        return;
    }

    cout << "\nUsuarios registrados:\n";
    string linea;
    while (getline(in, linea)) {
        cout << linea << "\n";
    }

    in.close();
}

int main() {
    // Crear huésped y anfitrión
    Huesped h("123456789", 6, 4.2);
    Anfitrion a("987654321", 12, 4.8);

    // Guardar usuarios en archivo
    guardarUsuarioEnArchivo(&h, "HUESPED", "usuarios.txt");
    guardarUsuarioEnArchivo(&a, "ANFITRION", "usuarios.txt");

    // Leer usuarios desde archivo
    leerUsuariosDesdeArchivo("usuarios.txt");

    // Crear alojamiento
    Alojamiento* al = new Alojamiento();
    al->setCodigo("ALJ001");
    al->setTipo("Apartamento");
    al->setMunicipio("Medellin");
    al->setPrecio(150000);
    a.agregarAlojamiento(al);

    // Crear fechas
    Fecha fInicio(25, 5, 2025);
    Fecha fPago(20, 5, 2025);

    // Crear reserva
    Reserva* r = new Reserva("RES123", fInicio, 3, "PSE", fPago, 450000, "123456789", "ALJ001", "Todo bien");

    // Hacer reserva
    if (h.hacerReserva(r)) {
        cout << "\nReserva realizada por el huésped:\n";
        h.mostrarReservas();
    }

    // Guardar reserva en archivo
    guardarReservaEnArchivo(r, "reservas.txt");

    // Leer reservas desde archivo
    leerReservasDesdeArchivo("reservas.txt");

    // Cancelar la reserva
    cout << "\nCancelando reserva RES123 desde el huésped...\n";
    h.cancelarReserva("RES123");

    // Mostrar reservas después de cancelar
    h.mostrarReservas();

    // Liberar memoria
    delete al;

    return 0;
}
