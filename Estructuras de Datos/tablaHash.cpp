#include <iostream>
#include <list>
#include <vector>

class tablaHash{
private:
  int buckets;
  std::vector<std::list<int>> tabla;

  int funcionHash(int key){
    return key % buckets;
  }

public:

  tablaHash(int buck) : buckets(buck){
    tabla.resize(buckets);
  }

  void Insertar(int key){
    int index = funcionHash(key);
    tabla[index].push_back(key);
  }

  void Eliminar(int key){
    int index = funcionHash(key);
    tabla[index].remove(key);
  }

  bool Buscar(int key){
    int index = funcionHash(key);
    for (int x : tabla[index]){
      if (x == key) return true;
    }
    return false;
  }

  void mostrarTabla(){
    for (int i=0; i<buckets; i++){
      std::cout<<"Bucket"<< i << ": ";
      for (int x : tabla[i]){
        std::cout<<"["<< x <<"]";
      }
      std::cout << "NULL" <<std::endl;
    }
  }
};

int main(){
  tablaHash miTabla(7);

  miTabla.Insertar(10);
  miTabla.Insertar(20);
  miTabla.Insertar(15);
  miTabla.Insertar(7);
  miTabla.Insertar(14);

  std::cout << "------- TABLA -------"<<std::endl;
  miTabla.mostrarTabla();

  std::cout << "\nBuscando el 15: " << (miTabla.Buscar(15) ? "Encontrado" : "No está") << std::endl;

  miTabla.Eliminar(20);
  std::cout<< "Eliminando..."<<std::endl;
  miTabla.mostrarTabla();

  return 0;
}