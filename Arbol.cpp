#include <iostream>
using namespace std;

class BTNodo {
public:
    float fdato;
    BTNodo* pIzq;
    BTNodo* pDer;

    BTNodo(float valor) {
        fdato = valor;
        pIzq = nullptr;
        pDer = nullptr;
    }

    bool ToTheLeft(float nd) {
        return nd < fdato;
    }

    void Insertar(float nd) {
        if (ToTheLeft(nd)) {
            if (pIzq == nullptr) {
                pIzq = new BTNodo(nd);
            } else {
                pIzq->Insertar(nd);
            }
        } else {
            if (pDer == nullptr) {
                pDer = new BTNodo(nd);
            } else {
                pDer->Insertar(nd);
            }
        }
    }

    void PreOrden() {
        cout << fdato << " ";
        if (pIzq != nullptr) pIzq->PreOrden();
        if (pDer != nullptr) pDer->PreOrden();
    }

    void InOrden() {
        if (pIzq != nullptr) pIzq->InOrden();
        cout << fdato << " ";
        if (pDer != nullptr) pDer->InOrden();
    }

    void PostOrden() {
        if (pIzq != nullptr) pIzq->PostOrden();
        if (pDer != nullptr) pDer->PostOrden();
        cout << fdato << " ";
    }

    // Retorna true si la raiz fue eliminada y debe ponerse pRaiz = nullptr
    bool Eliminar(float nd) {
        BTNodo* MalPadre = BuscarMalPadre(nd);

        // ── CASO RAIZ: MalPadre es null pero el dato coincide con this ──
        if (MalPadre == nullptr && this->fdato == nd) {

            // Caso 1: Raiz sin hijos — se avisa a Arbol para que ponga pRaiz=nullptr
            if (cuantosHijos() == 0) {
                return true;

            // Caso 2: Raiz con 1 hijo — se copia el hijo a la raiz y se borra el hijo
            } else if (cuantosHijos() == 1) {
                BTNodo* unico = DameUnicoHijo();
                this->fdato = unico->fdato;
                this->pIzq  = unico->pIzq;
                this->pDer  = unico->pDer;
                delete unico;

            // Caso 3: Raiz con 2 hijos — predecesor inorden (mayor del subarbol izquierdo)
            } else {
                BTNodo* padreSucesor = this;
                BTNodo* sucesor      = this->pIzq;
                while (sucesor->pDer != nullptr) {
                    padreSucesor = sucesor;
                    sucesor      = sucesor->pDer;
                }
                this->fdato = sucesor->fdato;
                if (padreSucesor == this) {
                    padreSucesor->pIzq = sucesor->pIzq;
                } else {
                    padreSucesor->pDer = sucesor->pIzq;
                }
                delete sucesor;
            }

        // ── RAMA IZQUIERDA ──
        } else if (MalPadre != nullptr && MalPadre->ToTheLeft(nd)) {
            BTNodo* nodoAEliminar = MalPadre->pIzq;

            if (nodoAEliminar->cuantosHijos() == 0) {
                MalPadre->pIzq = nullptr;
                delete nodoAEliminar;

            } else if (nodoAEliminar->cuantosHijos() == 1) {
                MalPadre->pIzq = nodoAEliminar->DameUnicoHijo();
                delete nodoAEliminar;

            } else {
                BTNodo* padreSucesor = nodoAEliminar;
                BTNodo* sucesor      = nodoAEliminar->pIzq;
                while (sucesor->pDer != nullptr) {
                    padreSucesor = sucesor;
                    sucesor      = sucesor->pDer;
                }
                nodoAEliminar->fdato = sucesor->fdato;
                if (padreSucesor == nodoAEliminar) {
                    padreSucesor->pIzq = sucesor->pIzq;
                } else {
                    padreSucesor->pDer = sucesor->pIzq;
                }
                delete sucesor;
            }

        // ── RAMA DERECHA ──
        } else if (MalPadre != nullptr) {
            BTNodo* nodoAEliminar = MalPadre->pDer;

            if (nodoAEliminar->cuantosHijos() == 0) {
                MalPadre->pDer = nullptr;
                delete nodoAEliminar;

            } else if (nodoAEliminar->cuantosHijos() == 1) {
                MalPadre->pDer = nodoAEliminar->DameUnicoHijo();
                delete nodoAEliminar;

            } else {
                BTNodo* padreSucesor = nodoAEliminar;
                BTNodo* sucesor      = nodoAEliminar->pIzq;
                while (sucesor->pDer != nullptr) {
                    padreSucesor = sucesor;
                    sucesor      = sucesor->pDer;
                }
                nodoAEliminar->fdato = sucesor->fdato;
                if (padreSucesor == nodoAEliminar) {
                    padreSucesor->pIzq = sucesor->pIzq;
                } else {
                    padreSucesor->pDer = sucesor->pIzq;
                }
                delete sucesor;
            }

        } else {
            cout << "Dato no encontrado." << endl;
        }

        return false;
    }

private:
    int cuantosHijos() {
        int count = 0;
        if (pIzq != nullptr) count++;
        if (pDer != nullptr) count++;
        return count;
    }

    BTNodo* DameUnicoHijo() {
        if (cuantosHijos() != 1) return nullptr;
        if (pIzq != nullptr) return pIzq;
        return pDer;
    }

    BTNodo* BuscarMalPadre(float d) {
        BTNodo* pActual = this;

        while (pActual != nullptr) {
            if (pActual->ToTheLeft(d)) {
                if (pActual->pIzq != nullptr && pActual->pIzq->fdato == d) {
                    return pActual;
                } else if (pActual->pIzq != nullptr) {
                    pActual = pActual->pIzq;
                } else {
                    return nullptr;
                }
            } else {
                if (pActual->pDer != nullptr && pActual->pDer->fdato == d) {
                    return pActual;
                } else if (pActual->pDer != nullptr) {
                    pActual = pActual->pDer;
                } else {
                    return nullptr;
                }
            }
        }
        return nullptr;
    }
};

class Arbol {
public:
    BTNodo* pRaiz;

    Arbol() {
        pRaiz = nullptr;
    }

    void InsertarRa(float nd) {
        if (pRaiz == nullptr) {
            pRaiz = new BTNodo(nd);
        } else {
            pRaiz->Insertar(nd);
        }
    }

    void Eliminar(float nd) {
        if (pRaiz == nullptr) {
            cout << "El arbol esta vacio." << endl;
            return;
        }
        // Si Eliminar devuelve true, la raiz era hoja y debe borrarse
        if (pRaiz->Eliminar(nd)) {
            delete pRaiz;
            pRaiz = nullptr;
        }
    }

    void PreOrden() {
        if (pRaiz != nullptr) pRaiz->PreOrden();
        cout << endl;
    }

    void InOrden() {
        if (pRaiz != nullptr) pRaiz->InOrden();
        cout << endl;
    }

    void PostOrden() {
        if (pRaiz != nullptr) pRaiz->PostOrden();
        cout << endl;
    }
};

int main() {
    Arbol arbol;

    arbol.InsertarRa(50.0f);
    arbol.InsertarRa(30.0f);
    arbol.InsertarRa(70.0f);
    arbol.InsertarRa(20.0f);
    arbol.InsertarRa(40.0f);
    arbol.InsertarRa(60.0f);
    arbol.InsertarRa(80.0f);

    cout << "InOrden inicial:            ";
    arbol.InOrden();

    arbol.Eliminar(20.0f);          // Hoja normal
    cout << "Tras eliminar 20 (hoja):    ";
    arbol.InOrden();

    arbol.Eliminar(30.0f);          // Nodo con 1 hijo
    cout << "Tras eliminar 30 (1 hijo):  ";
    arbol.InOrden();

    arbol.Eliminar(70.0f);          // Nodo con 2 hijos
    cout << "Tras eliminar 70 (2 hijos): ";
    arbol.InOrden();

    arbol.Eliminar(50.0f);          // Raiz con 2 hijos
    cout << "Tras eliminar 50 (raiz):    ";
    arbol.InOrden();

    return 0;
}