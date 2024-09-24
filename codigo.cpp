#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

void multiplicar_flotantes(float a, float b) {
    const int sesgo = 127; 

    union {
        float numero;
        uint32_t bits;
    } flotante1, flotante2, resultado;

    flotante1.numero = a;
    flotante2.numero = b;

    int signo1 = (flotante1.bits >> 31) & 1;
    int signo2 = (flotante2.bits >> 31) & 1;
    int exponente1 = ((flotante1.bits >> 23) & 0xFF) - sesgo;
    int exponente2 = ((flotante2.bits >> 23) & 0xFF) - sesgo;

    uint32_t mantisa1 = (flotante1.bits & 0x7FFFFF) | (1 << 23);
    uint32_t mantisa2 = (flotante2.bits & 0x7FFFFF) | (1 << 23);

    uint64_t producto_mantisas = static_cast<uint64_t>(mantisa1) * mantisa2;

    int exponente_res = exponente1 + exponente2;

    if (producto_mantisas & (1ULL << 47)) {
        producto_mantisas >>= 1;
        exponente_res++;
    }

    if (exponente_res + sesgo >= 255) {
        resultado.bits = (1 << 31) | (0xFF << 23);
    } else if (exponente_res + sesgo <= 0) {
        resultado.bits = 0;
    } else {
        resultado.bits = ((signo1 ^ signo2) << 31) | ((exponente_res + sesgo) << 23) | ((producto_mantisas >> 24) & 0x7FFFFF);
    }

    cout << "Resultado en binario: " << bitset<32>(resultado.bits) << endl;
}

int main() {
    float num1, num2;
    cout << "Ingrese el primer numero flotante: ";
    cin >> num1;
    cout << "Ingrese el segundo numero flotante: ";
    cin >> num2;

    multiplicar_flotantes(num1, num2);
  //ejemplo puede poner 10.5, y 2.375
  //debeindo resultar 01000001111000111100000000000000

    return 0;
}
