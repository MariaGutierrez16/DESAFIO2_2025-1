#ifndef UDEASTAY_H
#define UDEASTAY_H

// Clase Fecha
class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha();
    Fecha(int d, int m, int a);
    Fecha(const Fecha& otra);
    ~Fecha();

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    bool esIgual(const Fecha& otra) const;
    bool esMenor(const Fecha& otra) const;
    void mostrar() const;
};

// Clase base Usuario
class Usuario {
protected:
    char documento[20];
    int antiguedad; // en meses
    float puntuacion;

public:
    Usuario();
    Usuario(const char* doc, int ant, float punt);
    Usuario(const Usuario& otro);
    virtual ~Usuario();

    const char* getDocumento() const;
    int getAntiguedad() const;
    float getPuntuacion() const;

    void setDocumento(const char* doc);
    void setAntiguedad(int ant);
    void setPuntuacion(float punt);

    virtual void mostrar() const = 0;
};

// Clase Huésped
class Huesped : public Usuario {
private:
    int* codigosReservas;
    int cantidadReservas;
    int capacidadReservas;

    void expandirCapacidad();

public:
    Huesped();
    ~Huesped();

    void agregarReserva(int codigo);
    void mostrar() const override;
};

// Clase Anfitrión
class Anfitrion : public Usuario {
private:
    int cantidadAlojamientos;
    char** codigosAlojamientos;

public:
    Anfitrion();
    Anfitrion(const char* doc, int ant, float punt);
    Anfitrion(const Anfitrion& otro);
    ~Anfitrion();

    void agregarAlojamiento(const char* codigo);
    void eliminarAlojamiento(const char* codigo);
    void mostrar() const override;
};

// Clase Alojamiento
class Alojamiento {
private:
    char codigo[10];
    char nombre[50];
    char tipo[20];
    char direccion[100];
    char municipio[50];
    char departamento[50];
    float precioNoche;
    char amenidades[5][30];
    int cantidadAmenidades;
    char documentoAnfitrion[20];
    Fecha* fechasReservadas[365];

public:
    Alojamiento();
    Alojamiento(const char* cod, const char* nom, const char* t, const char* dir,
                const char* mun, const char* depto, float precio, const char* docAnf);
    Alojamiento(const Alojamiento& otro);
    ~Alojamiento();

    void agregarAmenidad(const char* amenidad);
    void agregarFechaReservada(const Fecha& f);
    bool estaDisponible(const Fecha& f, int noches) const;
    void mostrar() const;

    const char* getCodigo() const;
    const char* getDocumentoAnfitrion() const;
    float getPrecioNoche() const;
    const char* getMunicipio() const;
};

// Clase Reserva
class Reserva {
private:
    int codigo;
    char codigoAlojamiento[10];
    char documentoHuesped[20];
    Fecha fechaEntrada;
    int cantidadNoches;
    char metodoPago[10];
    Fecha fechaPago;
    float monto;
    char anotacion[1001];

public:
    Reserva();
    Reserva(int cod, const char* codAloj, const char* docH, const Fecha& fEntrada,
            int noches, const char* metodo, const Fecha& fPago, float monto, const char* nota);
    Reserva(const Reserva& otra);
    ~Reserva();

    void mostrar() const;
    const Fecha& getFechaEntrada() const;
    int getCantidadNoches() const;
    const char* getDocumentoHuesped() const;
    const char* getCodigoAlojamiento() const;
    int getCodigo() const;
};

#endif // UDEASTAY_H
