#ifndef UDEASTAY_H
#define UDEASTAY_H

#include <iostream>
#include <cstring>
using namespace std;

#define MAX_RESERVAS 50
#define MAX_ALOJAMIENTOS 50
#define MAX_AMENIDADES 10

// ========================================================
// Clase Fecha: representa una fecha con día, mes y año.
// ========================================================
class Fecha {
private:
    int dia;
    int mes;
    int anio;
public:
    Fecha() : dia(1), mes(1), anio(2025) {}
    Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}
    Fecha(const Fecha& otra) {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    ~Fecha() {}

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAnio() const { return anio; }

    void setDia(int d) { dia = d; }
    void setMes(int m) { mes = m; }
    void setAnio(int a) { anio = a; }

    bool esValida() const {
        if (mes < 1 || mes > 12 || dia < 1) return false;
        int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (anio % 4 == 0 && mes == 2) return dia <= 29;
        return dia <= diasMes[mes - 1];
    }

    void mostrar() const {
        const char* nombresMes[] = {
            "enero", "febrero", "marzo", "abril", "mayo", "junio",
            "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"
        };
        cout << dia << " de " << nombresMes[mes - 1] << " del " << anio;
    }
};

// ======================== FORWARD ========================
class Reserva;
class Alojamiento;

// ========================================================
// Clase Usuario: base para Huésped y Anfitrión
// ========================================================
class Usuario {
protected:
    char documento[20];
    int antiguedad;
    float puntuacion;
public:
    Usuario() {
        strcpy(documento, "");
        antiguedad = 0;
        puntuacion = 0.0f;
    }

    Usuario(const char* doc, int antig, float punt) {
        strcpy(documento, doc);
        antiguedad = antig;
        puntuacion = punt;
    }

    virtual ~Usuario() {}

    const char* getDocumento() const { return documento; }
    int getAntiguedad() const { return antiguedad; }
    float getPuntuacion() const { return puntuacion; }

    void setDocumento(const char* doc) { strcpy(documento, doc); }
    void setAntiguedad(int a) { antiguedad = a; }
    void setPuntuacion(float p) { puntuacion = p; }

    virtual bool iniciarSesion(const char* docIngresado) {
        return strcmp(docIngresado, documento) == 0;
    }

    virtual void mostrarPerfil() const {
        cout << "Documento: " << documento << "\n";
        cout << "Antigüedad: " << antiguedad << " meses\n";
        cout << "Puntuación: " << puntuacion << "\n";
    }
};

// ========================================================
// Clase Reserva
// ========================================================
class Reserva {
private:
    char codigoReserva[20];
    Fecha fechaInicio;
    int noches;
    char metodoPago[15];
    Fecha fechaPago;
    float monto;
    char documentoHuesped[20];
    char codigoAlojamiento[20];
    char anotaciones[1001];

public:
    Reserva() {
        strcpy(codigoReserva, "");
        strcpy(metodoPago, "");
        strcpy(documentoHuesped, "");
        strcpy(codigoAlojamiento, "");
        strcpy(anotaciones, "");
        noches = 0;
        monto = 0;
    }

    Reserva(const char* cod, Fecha fInicio, int n, const char* mp, Fecha fPago, float m,
            const char* docH, const char* codAloj, const char* nota) :
        fechaInicio(fInicio), fechaPago(fPago), noches(n), monto(m) {
        strcpy(codigoReserva, cod);
        strcpy(metodoPago, mp);
        strcpy(documentoHuesped, docH);
        strcpy(codigoAlojamiento, codAloj);
        strncpy(anotaciones, nota, 1000);
        anotaciones[1000] = '\0';
    }

    // ======= GETTERS NECESARIOS PARA ARCHIVO =======
    const char* getCodigoReserva() const { return codigoReserva; }
    const char* getCodigoAlojamiento() const { return codigoAlojamiento; }
    const char* getDocumentoHuesped() const { return documentoHuesped; }
    Fecha getFechaInicio() const { return fechaInicio; }
    int getNoches() const { return noches; }
    const char* getMetodoPago() const { return metodoPago; }
    float getMonto() const { return monto; }
    const char* getAnotaciones() const { return anotaciones; }

    void generarComprobante() const {
        cout << "Comprobante de Reserva:\n";
        cout << "Código: " << codigoReserva << "\n";
        cout << "Alojamiento: " << codigoAlojamiento << "\n";
        cout << "Huésped: " << documentoHuesped << "\n";
        cout << "Fecha entrada: "; fechaInicio.mostrar(); cout << "\n";
        cout << "Fecha pago: "; fechaPago.mostrar(); cout << "\n";
        cout << "Noches: " << noches << "\n";
        cout << "Monto: $" << monto << "\n";
        cout << "Pago con: " << metodoPago << "\n";
        cout << "Anotación: " << anotaciones << "\n";
    }
};

// ========================================================
// Clase Huesped
// ========================================================
class Huesped : public Usuario {
private:
    Reserva* reservas[MAX_RESERVAS];
    int numReservas;

public:
    Huesped() : Usuario(), numReservas(0) {}
    Huesped(const char* doc, int antig, float punt)
        : Usuario(doc, antig, punt), numReservas(0) {}

    bool hacerReserva(Reserva* r) {
        if (numReservas < MAX_RESERVAS) {
            reservas[numReservas++] = r;
            return true;
        }
        return false;
    }

    void mostrarReservas() const {
        cout << "Reservas del huésped:\n";
        for (int i = 0; i < numReservas; ++i) {
            reservas[i]->generarComprobante();
            cout << "-----------------------\n";
        }
    }
};

// ========================================================
// Clase Alojamiento
// ========================================================
class Alojamiento {
private:
    char codigo[20];
    char nombre[50];
    char direccion[100];
    char tipo[20];
    char departamento[30];
    char municipio[30];
    float precio;
    bool amenidades[MAX_AMENIDADES]; // true o false por amenidad
    Fecha* fechasReservadas[MAX_RESERVAS];
    int numFechas;

public:
    Alojamiento() {
        strcpy(codigo, "");
        strcpy(nombre, "");
        strcpy(direccion, "");
        strcpy(tipo, "");
        strcpy(departamento, "");
        strcpy(municipio, "");
        precio = 0;
        for (int i = 0; i < MAX_AMENIDADES; ++i) amenidades[i] = false;
        numFechas = 0;
    }

    const char* getCodigo() const { return codigo; }
    const char* getTipo() const { return tipo; }
    const char* getMunicipio() const { return municipio; }
    float getPrecio() const { return precio; }

    void setCodigo(const char* c) { strcpy(codigo, c); }
    void setTipo(const char* t) { strcpy(tipo, t); }
    void setMunicipio(const char* m) { strcpy(municipio, m); }
    void setPrecio(float p) { precio = p; }

    bool estaDisponible(Fecha fecha, int noches) const {
        for (int i = 0; i < numFechas; ++i) {
            if (fechasReservadas[i]->getDia() == fecha.getDia() &&
                fechasReservadas[i]->getMes() == fecha.getMes() &&
                fechasReservadas[i]->getAnio() == fecha.getAnio()) {
                return false;
            }
        }
        return true;
    }

    bool agregarFechaReservada(Fecha* fecha) {
        if (numFechas < MAX_RESERVAS) {
            fechasReservadas[numFechas++] = fecha;
            return true;
        }
        return false;
    }
};

// ========================================================
// Clase Anfitrion
// ========================================================
class Anfitrion : public Usuario {
private:
    Alojamiento* alojamientos[MAX_ALOJAMIENTOS];
    int numAlojamientos;

public:
    Anfitrion() : Usuario(), numAlojamientos(0) {}
    Anfitrion(const char* doc, int antig, float punt)
        : Usuario(doc, antig, punt), numAlojamientos(0) {}

    bool agregarAlojamiento(Alojamiento* a) {
        if (numAlojamientos < MAX_ALOJAMIENTOS) {
            alojamientos[numAlojamientos++] = a;
            return true;
        }
        return false;
    }

    void mostrarAlojamientos() const {
        cout << "Alojamientos administrados:\n";
        for (int i = 0; i < numAlojamientos; ++i) {
            cout << "Código: " << alojamientos[i]->getCodigo() << ", Municipio: "
                 << alojamientos[i]->getMunicipio() << ", Precio: $" << alojamientos[i]->getPrecio() << "\n";
        }
    }
};

#endif
