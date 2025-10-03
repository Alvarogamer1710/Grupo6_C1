
#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

// generos
enum class Genero {
    Accion,
    Drama,
    Comedia,
    Romantico,
    Aventura,
    Fantasia
};

//genero a string, los defino fuera de la clase, uso enum para que se puedan elegir de unos
//predeterminados, para facilitar en momento de clasificarlo los libros
static inline std::string generoToString(Genero g) {
    switch (g) {
        case Genero::Accion:     return "Accion";
        case Genero::Drama:      return "Drama";
        case Genero::Comedia:    return "Comedia";
        case Genero::Romantico:  return "Romantico";
        case Genero::Aventura:   return "Aventura";
        case Genero::Fantasia:   return "Fantasia";
        default:                 return "Desconocido";
    }
}

class Libro {
private:
    int id_libro;              // id
    std::string nombre_libro;  // titulo
    std::string autor_libro;   // autor
    Genero genero_libro;       // genero

public:
    // constructor vacio
    Libro() {
    }

    // constructor
    Libro(std::string titulo, int id, std::string autor, Genero g)
    :nombre_libro(titulo), id_libro(id), autor_libro(autor), genero_libro(g) {
    }

    // getters
    int getId() const { return id_libro; }
    std::string getTitulo() const { return nombre_libro; }
    std::string getAutor() const { return autor_libro; }
    Genero getGenero() const { return genero_libro; }

    // setters
    void setTitulo(const std::string& t) { nombre_libro = t; }
    void setAutor(const std::string& a) { autor_libro = a; }
    void setGenero(Genero g) { genero_libro = g; }
    void setId(int id) { id_libro = id; }

    // info
    void getInfoLibro() const {
        std::cout << "ID: " << id_libro << std::endl;
        std::cout << "Titulo: " << nombre_libro << std::endl;
        std::cout << "Autor: " << autor_libro << std::endl;
        std::cout << "Genero: " << generoToString(genero_libro) << std::endl;
    }
};

class Usuario {
private:
    std::string nombre;
    std::string apellido;
    std::string dni;

    static const int MAX_LIBROS = 20;
    Libro librosActuales[MAX_LIBROS];
    Libro historial[MAX_LIBROS];
    int numLibrosActuales = 0;
    int numHistorial = 0;

public:
    Usuario() {}

    Usuario(const std::string& n, const std::string& a, const std::string& d)
        : nombre(n), apellido(a), dni(d) {}

    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    std::string getDni() const { return dni; }

    void setNombre(const std::string& n) { nombre = n; }
    void setApellido(const std::string& a) { apellido = a; }
    void setDni(const std::string& d) { dni = d; }

    void agregarLibro(const Libro& libro) {
        if (numLibrosActuales < MAX_LIBROS) {
            librosActuales[numLibrosActuales++] = libro;
            std::cout << "Libro agregado a " << nombre << " " << apellido << "." << std::endl;
        } else {
            std::cout << "No se pueden agregar más libros, límite alcanzado." << std::endl;
        }
    }

    void devolverLibro(int id) {
        for (int i = 0; i < numLibrosActuales; i++) {
            if (librosActuales[i].getId() == id) {
                if (numHistorial < MAX_LIBROS) {
                    historial[numHistorial++] = librosActuales[i];
                }
                librosActuales[i] = librosActuales[numLibrosActuales - 1];
                numLibrosActuales--;
                std::cout << "Libro devuelto correctamente." << std::endl;
                return;
            }
        }
        std::cout << "No se encontró el libro con ID " << id << " en los libros actuales." << std::endl;
    }

    void mostrarInfo() const {
        std::cout << "Usuario: " << nombre << " " << apellido << std::endl;
        std::cout << "DNI: " << dni << std::endl;
        std::cout << "Libros actuales: " << numLibrosActuales << std::endl;
        std::cout << "Historial de libros leídos: " << numHistorial << std::endl;
    }

    void mostrarLibrosActuales() const {
        std::cout << "\nLibros actuales de " << nombre << ":\n";
        for (int i = 0; i < numLibrosActuales; i++) {
            librosActuales[i].getInfoLibro();
            std::cout << "-------------------\n";
        }
    }

    void mostrarHistorial() const {
        std::cout << "\nHistorial de libros de " << nombre << ":\n";
        for (int i = 0; i < numHistorial; i++) {
            historial[i].getInfoLibro();
            std::cout << "-------------------\n";
        }
    }
};


template <typename T>
class Biblioteca {
private:
    T items[20];
    int siguientePosicionLibre = 0;

public:
    Biblioteca(){
    }

    void agregarLibro( T &item) {
        if (siguientePosicionLibre < 20) {
            items[siguientePosicionLibre] = item;
            siguientePosicionLibre++;
            std::cout << "Item agregado exitosamente." << std::endl;
        } else {
            std::cout << "La biblioteca está llena. No se pueden agregar más items." << std::endl;
        }
    }



    void darLibro(T &libro, Usuario &usuario) {

        bool completado = false;
        for(int i = 0; i < siguientePosicionLibre; i++){
            if(items[i] == libro && !completado){
                usuario.agregarLibro(items[i]);
                items[i] = NULL;
                completado = true;
                std::cout << "Libro dado Exitosamente" << std::endl;
            }
            if (completado && i !=siguientePosicionLibre) {
                items[i] = items[i+1];
            }

        }
        if (completado) {
            siguientePosicionLibre--;
        }
    }


    bool comprobarLibroDisponible(T &libro) {
        for (int i = 0; i < siguientePosicionLibre-1; i++) {
            if (items[i] == libro) {
                return true;
            }

        }
        return false;
    }

    bool verSiTienePersonaLibro(T &libro , Usuario &usuario) {
        // aqui vemos si el usuario tiene el libro o no
        return false;
    }


};

int main() {
    Libro l1("El Hobbit", 1, "J.R.R. Tolkien", Genero::Fantasia);
    Libro l2("Cien anos de soledad", 2, "Gabriel Garcia Marquez", Genero::Drama);
    Libro l3("El Quijote", 3, "Miguel de Cervantes", Genero::Aventura);

    Usuario u1("Juan", "Perez", "12345678");

    u1.mostrarInfo();

    u1.agregarLibro(l1);
    u1.agregarLibro(l2);

    u1.mostrarLibrosActuales();

    u1.devolverLibro(1);

    u1.mostrarLibrosActuales();
    u1.mostrarHistorial();

    return 0;
}

