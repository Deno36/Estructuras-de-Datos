#include <iostream>
#include <string>
using namespace std;

class Videojuego {
public:
    string nombre;
    string genero;
    string plataforma;   // Pc | Switch | Ps5 | Xbox
    float  calificacion;

    Videojuego(string nombre, string genero, string plataforma, float calificacion) {
        this->nombre = nombre;
        this->genero = genero;
        this->plataforma = plataforma;
        this->calificacion = calificacion;
    }

    void mostrar() const {
        cout << "  * " << nombre
             << "\t| Plataforma: " << plataforma
             << "\t| Calificacion: " << calificacion
             << endl;
    }
};

//  DLL INTERNA  almacena Videojuego*
//  lista de objetos dentro de cada nodo invertido
class CDLLListaVJ;

class CDLLNodoVJ {
    friend class CDLLListaVJ;
    friend struct CNodo;          
    friend class ListaInvertida;

private:
    Videojuego* Dato;
    CDLLNodoVJ* pNodoSig;
    CDLLNodoVJ* pNodoAnt;

    CDLLNodoVJ(Videojuego* v = nullptr) {
        Dato = v;
        pNodoSig = nullptr;
        pNodoAnt = nullptr;
    }

    void insertaAdelante(Videojuego* NewData) {
        CDLLNodoVJ* nuevo = new CDLLNodoVJ(NewData);

        nuevo->pNodoSig = this->pNodoSig;
        nuevo->pNodoAnt = this;
        this->pNodoSig->pNodoAnt = nuevo;
        this->pNodoSig = nuevo;
    }

    Videojuego* eliminarAdelante() {
        CDLLNodoVJ* temp = this->pNodoSig;
        Videojuego* valor = temp->Dato;

        this->pNodoSig = temp->pNodoSig;
        temp->pNodoSig->pNodoAnt = this;

        delete temp;
        return valor;
    }

    
};

class CDLLListaVJ {
private:
    CDLLNodoVJ Inicio;
    CDLLNodoVJ Final;

public:
    CDLLListaVJ() {
        Inicio.pNodoSig = &Final;
        Inicio.pNodoAnt = nullptr;
        Final.pNodoAnt  = &Inicio;
        Final.pNodoSig  = nullptr;
    }

    ~CDLLListaVJ() { vaciar(); }

    void InsertarInicio(Videojuego* newData) { Inicio.insertaAdelante(newData); }
    void InsertarFinal (Videojuego* newData) { Final.pNodoAnt->insertaAdelante(newData); }

    Videojuego* EliminarInicio() { return Inicio.eliminarAdelante(); }

    Videojuego* EliminarFinal() {
        CDLLNodoVJ* ultimo = Final.pNodoAnt;
        Videojuego* valor  = ultimo->Dato;

        ultimo->pNodoAnt->pNodoSig = &Final;
        Final.pNodoAnt = ultimo->pNodoAnt;

        delete ultimo;
        return valor;
    }

    void vaciar() {
        while (!estaVacia())
            EliminarInicio();
    }

    bool estaVacia()  const { return Inicio.pNodoSig == &Final; }
    CDLLNodoVJ* getPrimero() const { return Inicio.pNodoSig; }
    CDLLNodoVJ* getSentinel()const { return const_cast<CDLLNodoVJ*>(&Final); }

    bool EliminarVideojuego(const string& nombre) {
    CDLLNodoVJ* actual = Inicio.pNodoSig;

    while (actual != &Final) {
        if (actual->Dato->nombre == nombre) {

            // Desenlazar el nodo de la lista doblemente enlazada
            actual->pNodoAnt->pNodoSig = actual->pNodoSig;
            actual->pNodoSig->pNodoAnt = actual->pNodoAnt;

            delete actual->Dato;   // liberar Videojuego
            delete actual;         // liberar CDLLNodoVJ
            return true;
        }
        actual = actual->pNodoSig;
    }
    return false;   // no se encontró el videojuego
}
};

//  CNodo  Nodo de la Lista Invertida
//  Lista interna usa CDLLListaVJ
struct CNodo {
    string ValorAI;   // Atributo invertido (genero)
    CDLLListaVJ  Lista;     // Lista interna de Videojuego*  DLL interna
    CNodo* siguiente; // solo se usa desde CDLLListaCN

    CNodo(string valorAI) {
        ValorAI = valorAI;
        siguiente = nullptr;
    }

    void mostrar() const {
        cout << "[Genero: " << ValorAI << "]" << endl;

        CDLLNodoVJ* actual   = Lista.getPrimero();
        CDLLNodoVJ* sentinel = Lista.getSentinel();
        while (actual != sentinel) {
            actual->Dato->mostrar();
            actual = actual->pNodoSig;
        }
    }
};

//  DLL EXTERNA  almacena CNodo*
//  lista de nodos invertidos
class CDLLListaCN;

class CDLLNodoCN {
    friend class CDLLListaCN;
    friend class ListaInvertida;
    

private:
    CNodo* Dato;
    CDLLNodoCN* pNodoSig;
    CDLLNodoCN* pNodoAnt;

    CDLLNodoCN(CNodo* v = nullptr) {
        Dato = v;
        pNodoSig = nullptr;
        pNodoAnt = nullptr;
    }

    void insertaAdelante(CNodo* NewData) {
        CDLLNodoCN* nuevo = new CDLLNodoCN(NewData);

        nuevo->pNodoSig          = this->pNodoSig;
        nuevo->pNodoAnt          = this;
        this->pNodoSig->pNodoAnt = nuevo;
        this->pNodoSig           = nuevo;
    }

    CNodo* eliminarAdelante() {
        CDLLNodoCN* temp = this->pNodoSig;
        CNodo* valor     = temp->Dato;

        this->pNodoSig           = temp->pNodoSig;
        temp->pNodoSig->pNodoAnt = this;

        delete temp;
        return valor;
    }
};

class CDLLListaCN {
private:
    CDLLNodoCN Inicio;
    CDLLNodoCN Final;

public:
    CDLLListaCN() {
        Inicio.pNodoSig = &Final;
        Inicio.pNodoAnt = nullptr;
        Final.pNodoAnt = &Inicio;
        Final.pNodoSig = nullptr;
    }

    ~CDLLListaCN() { vaciar(); }

    void InsertarInicio(CNodo* newData) { Inicio.insertaAdelante(newData); }
    void InsertarFinal (CNodo* newData) { Final.pNodoAnt->insertaAdelante(newData); }

    CNodo* EliminarInicio() { return Inicio.eliminarAdelante(); }

    CNodo* EliminarFinal() {
        CDLLNodoCN* ultimo = Final.pNodoAnt;
        CNodo* valor= ultimo->Dato;

        ultimo->pNodoAnt->pNodoSig = &Final;
        Final.pNodoAnt= ultimo->pNodoAnt;

        delete ultimo;
        return valor;
    }

    void vaciar() {
        while (!estaVacia())
            EliminarInicio();
    }

    bool estaVacia()  const { return Inicio.pNodoSig == &Final; }
    CDLLNodoCN* getPrimero() const { return Inicio.pNodoSig; }
    CDLLNodoCN* getSentinel()const { return const_cast<CDLLNodoCN*>(&Final); }
};

//  ListaInvertida
//  Lista externa usa CDLLListaCN
class ListaInvertida {
private:
    CDLLListaCN lista;   // Lista de CNodo* ← DLL externa

public:
    //  Busqueda 
    // Recibe el ValorAI y regresa un puntero a CDLLListaVJ
    // correspondiente, o nullptr si no existe el genero.
    CDLLListaVJ* Busqueda(const string& valorAI) {
        CDLLNodoCN* actual = lista.getPrimero();
        CDLLNodoCN* sentinel = lista.getSentinel();

        while (actual != sentinel) {
            if (actual->Dato->ValorAI == valorAI)
                return &actual->Dato->Lista;
            actual = actual->pNodoSig;
        }
        return nullptr;
    }

    //  Insercion 
    // Llama a Busqueda; si encuentra el nodo inserta el objeto,
    // si no, crea un CNodo nuevo y luego inserta el objeto.
    void Insercion(Videojuego* vj) {
        string       genero   = vj->genero;
        CDLLListaVJ* listaObj = Busqueda(genero);

        if (listaObj != nullptr) {
            // El genero ya existe  agregar al final de su lista interna
            listaObj->InsertarFinal(vj);
        } else {
            // El genero no existe crear CNodo nuevo al inicio
            CNodo* nuevo = new CNodo(genero);
            nuevo->Lista.InsertarFinal(vj);
            lista.InsertarInicio(nuevo);
        }
    }

    // Mostrar 
  void Mostrar() const {
        if (lista.estaVacia()) {
            cout << "La lista invertida esta vacia." << endl;
            return;
        }
        CDLLNodoCN* actual   = lista.getPrimero();
        CDLLNodoCN* sentinel = lista.getSentinel();

        while (actual != sentinel) {
            cout << string(55, '-') << endl;
            actual->Dato->mostrar();
            actual = actual->pNodoSig;
        }
        cout << string(55, '-') << endl;
   }

  void MostrarPorGenero(const string& valorAI) {
        cout << "\n======  BUSQUEDA: genero '" << valorAI << "'  ======" << endl;

        CDLLListaVJ* resultado = Busqueda(valorAI);

        if (resultado != nullptr) {
            CDLLNodoVJ* actual   = resultado->getPrimero();
            CDLLNodoVJ* sentinel = resultado->getSentinel();
            while (actual != sentinel) {
                actual->Dato->mostrar();
                actual = actual->pNodoSig;
            }
        } else {
            cout << "Genero '" << valorAI << "' no encontrado." << endl;
        }
   }

  ~ListaInvertida() {
        CDLLNodoCN* actual   = lista.getPrimero();
        CDLLNodoCN* sentinel = lista.getSentinel();

        while (actual != sentinel) {
            CDLLNodoCN* temp = actual;
            actual = actual->pNodoSig;

            CDLLNodoVJ* vActual   = temp->Dato->Lista.getPrimero();
            CDLLNodoVJ* vSentinel = temp->Dato->Lista.getSentinel();
            while (vActual != vSentinel) {
                CDLLNodoVJ* vTemp = vActual;
                vActual = vActual->pNodoSig;
                delete vTemp->Dato;   
            }
            delete temp->Dato;       
        }
   }

  void Eliminar(const string& genero, const string& nombre) {
    CDLLNodoCN* actual   = lista.getPrimero();
    CDLLNodoCN* sentinel = lista.getSentinel();

    while (actual != sentinel) {
        if (actual->Dato->ValorAI == genero) {

            // Intentar eliminar el videojuego en la lista interna
            bool eliminado = actual->Dato->Lista.EliminarVideojuego(nombre);

            if (eliminado) {
                cout << "Videojuego '" << nombre
                     << "' eliminado del genero '" << genero << "'." << endl;

                // Si la lista interna quedo vacia, eliminar el CNodo del genero
                if (actual->Dato->Lista.estaVacia()) {
                    actual->pNodoAnt->pNodoSig = actual->pNodoSig;
                    actual->pNodoSig->pNodoAnt = actual->pNodoAnt;

                    delete actual->Dato;   // liberar CNodo
                    delete actual;         // liberar CDLLNodoCN

                    cout << "Genero '" << genero
                         << "' eliminado (sin videojuegos restantes)." << endl;
                }
            } else {
                cout << "Videojuego '" << nombre
                     << "' no encontrado en genero '" << genero << "'." << endl;
            }
            return;
        }
        actual = actual->pNodoSig;
    }
    cout << "Genero '" << genero << "' no encontrado." << endl;
  }
};

int main() {
    ListaInvertida li;

    li.Insercion(new Videojuego("Zelda: Tears of the Kingdom", "Aventura", "Switch", 10.0f));
    li.Insercion(new Videojuego("Elden Ring",                  "RPG",      "Ps5",     9.5f));
    li.Insercion(new Videojuego("Hollow Knight",               "Aventura", "Pc",      9.3f));
    li.Insercion(new Videojuego("Baldur's Gate 3",             "RPG",      "Pc",      9.8f));
    li.Insercion(new Videojuego("Halo Infinite",               "FPS",      "Xbox",    8.0f));
    li.Insercion(new Videojuego("Metroid Dread",               "Aventura", "Switch",  9.0f));
    li.Insercion(new Videojuego("Cyberpunk 2077",              "RPG",      "Ps5",     8.5f));
    li.Insercion(new Videojuego("Doom Eternal",                "FPS",      "Pc",      9.0f));

    cout << "\n======  LISTA INVERTIDA COMPLETA  ======" << endl;
    li.Mostrar();

    li.MostrarPorGenero("RPG");

    // Caso 1 — género y videojuego existen
    li.Eliminar("RPG", "Elden Ring");

    // Caso 2 — género existe pero el videojuego no
    li.Eliminar("RPG", "Minecraft");

    // Caso 3 — el género no existe
    li.Eliminar("Deportes", "FIFA");

    return 0;
}
