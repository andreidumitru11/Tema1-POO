#include "Comanda.hpp"
#include <iostream>
#include <cstring>

int Comanda::s_nrComenzi = 200;

Comanda::Comanda(const int zi, const int luna, const int an)
    : id(Comanda::s_nrComenzi++), zi(zi), luna(luna), an(an),
      nrProduse(0), capacitate(2), total(0.0)
{
    produse = new ultimulProdusAdaugat[capacitate];
}

Comanda::Comanda(const Comanda & other)
    : id(Comanda::s_nrComenzi++), zi(other.zi), luna(other.luna), an(other.an),
      nrProduse(other.nrProduse), capacitate(other.capacitate), total(other.total)
{
    std::cout << "copy Comanda" << std::endl;
    produse = new ultimulProdusAdaugat[capacitate];
    memcpy(produse, other.produse, nrProduse * sizeof(ultimulProdusAdaugat));
}

Comanda & Comanda::operator=(const Comanda & other) {
    std::cout << "op Comanda" << std::endl;
    if (this != &other) {
        zi = other.zi;
        luna = other.luna;
        an = other.an;
        nrProduse = other.nrProduse;
        total = other.total;

        if (capacitate != other.capacitate) {
            delete[] produse;
            capacitate = other.capacitate;
            produse = new ultimulProdusAdaugat[capacitate];
        }

        memcpy(produse, other.produse, nrProduse * sizeof(ultimulProdusAdaugat));
    }
    return *this;
}

Comanda::~Comanda() {
    delete[] produse;
    produse = nullptr;
}

void Comanda::adaugareProdus(const Produs * produs, const int cantitate) {
    if (nrProduse >= capacitate) {
        capacitate *= 2;
        ultimulProdusAdaugat* temp = new ultimulProdusAdaugat[capacitate];

        memcpy(temp, produse, nrProduse * sizeof(ultimulProdusAdaugat));
        delete[] produse;
        produse = temp;
    }

    produse[nrProduse].produs = produs;
    produse[nrProduse].cantitate = cantitate;
    nrProduse++;
    total += produs->getPret() * cantitate;
}

bool Comanda::eliminareProdus() {
    int index;
    std::cout << "Tastati numarul din dreptul produsului pe care doriti sa il eliminati:\n";
    for (int i = 0; i < nrProduse; i++) {
        std::cout << i + 1 << ". " << produse[i].produs->getDenumire() << std::endl;
    }
    std::cout << "\nNumar: ";
    std::cin >> index;

    if (index < 1 || index > nrProduse) {
        std::cout << "Index invalid!\n";
        return false;
    }

    total -= produse[index - 1].produs->getPret() * produse[index - 1].cantitate;

    for (int i = index - 1; i < nrProduse - 1; ++i) {
        produse[i] = produse[i + 1];
    }
    nrProduse--;
    return true;
}

std::ostream & operator<<(std::ostream & COUT, const Comanda & obj) {
    COUT << "Data comenzii: " << obj.zi << "/" << obj.luna << "/" << obj.an << "\n";
    COUT << "Produse comandate:\n";
    for (int i = 0; i < obj.nrProduse; ++i) {
        COUT << obj.produse[i].cantitate << " x "
             << obj.produse[i].produs->getDenumire()
             << " (" << obj.produse[i].produs->getPret() * obj.produse[i].cantitate << ")\n";
    }
    COUT << "Total comanda: " << obj.total << " RON\n";
    return COUT;
}
