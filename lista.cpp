#include <iostream>
using namespace std;

class CDLLLista;

class CDLLNodo {
    friend class CDLLLista;
private:
    float Dato;
    CDLLNodo *pNodoSig;
    CDLLNodo *pNodoAnt;

    CDLLNodo(float v = 0) {
        Dato = v;
        pNodoSig = nullptr;
        pNodoAnt = nullptr;
    }

    void insertaAdelante(float NewData) {
        CDLLNodo *nuevo = new CDLLNodo(NewData);

        nuevo->pNodoSig = this->pNodoSig;
        nuevo->pNodoAnt = this;

        this->pNodoSig->pNodoAnt = nuevo;
        this->pNodoSig = nuevo;
    }

    float eliminarAdelante() {
        CDLLNodo *temp = this->pNodoSig;
        float valor = temp->Dato;

        this->pNodoSig = temp->pNodoSig;
        temp->pNodoSig->pNodoAnt = this;

        delete temp;
        return valor;
    }
};

class CDLLLista {
private:
    CDLLNodo Inicio;
    CDLLNodo Final;

public:
    CDLLLista() {
        Inicio.pNodoSig = &Final;
        Inicio.pNodoAnt = nullptr;

        Final.pNodoAnt = &Inicio;
        Final.pNodoSig = nullptr;
    }

    ~CDLLLista() {
        vaciar();
    }

    void InsertarInicio(float newData) {
        Inicio.insertaAdelante(newData);
    }

    void InsertarFinal(float newData) {
        Final.pNodoAnt->insertaAdelante(newData);
    }

    float EliminarInicio() {
        return Inicio.eliminarAdelante();
    }

    float EliminarFinal() {
        CDLLNodo *ultimo = Final.pNodoAnt;
        float valor = ultimo->Dato;

        ultimo->pNodoAnt->pNodoSig = &Final;
        Final.pNodoAnt = ultimo->pNodoAnt;

        delete ultimo;
        return valor;
    }

    void vaciar() {
        while (!isEmpty()) {
            EliminarInicio();
        }
    }

    int size() {
        int contador = 0;
        CDLLNodo *aux = Inicio.pNodoSig;

        while (aux != &Final) {
            contador++;
            aux = aux->pNodoSig;
        }
        return contador;
    }

    bool isEmpty() {
        return Inicio.pNodoSig == &Final;
    }

    void imprimir() {
        CDLLNodo *aux = Inicio.pNodoSig;

        while (aux != &Final) {
            cout << aux->Dato << " <-> ";
            aux = aux->pNodoSig;
        }
        cout << "NULL\n";
    }
};


int main() {
    CDLLLista L;

    L.InsertarInicio(10);
    L.InsertarInicio(20);
    L.InsertarInicio(30);
    L.InsertarFinal(40);
    L.InsertarFinal(50);

    L.imprimir();

    L.EliminarInicio();
    L.imprimir();

    L.EliminarFinal();
    L.imprimir();

    cout << "Size: " << L.size() << endl;

    return 0;
}