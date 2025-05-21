#ifndef UDEASTAY_H
#define UDEASTAY_H

class Fecha {
private:
    int dia, mes, anio;
public:
    Fecha();
    Fecha(int d, int m, int a);
    bool validar();
};

class Usuario {
protected:
    char documento[20];
    int antiguedad;
    float puntuacion;
public:
    Usuario();
    Usuario(const char* doc, int antig, float punt);
    void iniciarSesion();
    void mostrarPerfil();
};

class Huesped : public Usuario {
public:
    Huesped();
    void buscarAlojamiento();
    void hacerReserva();
};

class Anfitrion : public Usuario {
public:
    Anfitrion();
    void gestionarAlojamientos();
    void verReservas();
};

class Alojamiento {
private:
    char codigo[10];
    char tipo[20];
    float precio;
    char municipio[30];
    bool disponible;
public:
    Alojamiento();
    Alojamiento(const char* cod, const char* t, float p, const char* muni);
    bool estaDisponible();
};

class Reserva {
private:
    Fecha fechaInicio;
    int noches;
    char metodoPago[20];
public:
    Reserva();
    Reserva(Fecha f, int n, const char* metodo);
    void generarComprobante();
};

class Fecha {
public:
    int dia, mes, anio;

    Fecha() : dia(1), mes(1), anio(2023) {}
    Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

    bool validar() {
        if (mes < 1 || mes > 12 || dia < 1 || dia > 31) return false;
        if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
        if (mes == 2) {
            bool bisiesto = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
            if (dia > (bisiesto ? 29 : 28)) return false;
        }
        return true;
    }
};

// ---------------- Clase Usuario ----------------
class Usuario {
protected:
    char documento[20];
    int antiguedad;
    float puntuacion;

public:
    Usuario() {}
    Usuario(const char* doc, int ant, float punt) {
        strcpy(documento, doc);
        antiguedad = ant;
        puntuacion = punt;
    }

    const char* getDocumento() { return documento; }
    virtual void mostrarPerfil() {
        cout << "Documento: " << documento << " | Antiguedad: " << antiguedad << " meses | Puntuacion: " << puntuacion << endl;
    }
};
#endif // UDEASTAY_H
