#include "Produs.hpp"

#ifndef COMANDA
#define COMANDA

class Comanda {
    struct ultimulProdusAdaugat {
        const Produs * produs;
        int cantitate;
    };

    const int id;
    static int s_nrComenzi;

    int zi;
    int luna;
    int an;

    int nrProduse;
    int capacitate;
    float total;
    ultimulProdusAdaugat * produse;
public:
    Comanda(const int zi = 0, const int luna = 0, const int an = 0);
    Comanda(const Comanda &);
    Comanda & operator=(const Comanda &);
    ~Comanda();
    void adaugareProdus(const Produs *, const int);
    bool eliminareProdus();
    friend std::ostream & operator<<(std::ostream &, const Comanda &);
};

#endif
