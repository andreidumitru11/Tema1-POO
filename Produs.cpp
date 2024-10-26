#include "Produs.hpp"
int Produs::s_nrProduse = 100;

char * copy(const char * buffer) {
    if(buffer)
        return strcpy(new char[strlen(buffer) + 1], buffer);
    return NULL;
}

Produs::Produs(const char * denumire, const float pret) : id(Produs::s_nrProduse++), denumire(copy(denumire)), pret(pret) {}

Produs::Produs(const Produs & other) : id(Produs::s_nrProduse++), denumire(copy(other.denumire)), pret(other.pret) {
 std::cout << "copy Produs" << std::endl;
}

Produs & Produs::operator=(const Produs & other) {
    std::cout << "op Produs" << std::endl;
    if(this != &other) {
        delete[] denumire;
        denumire = copy(other.denumire);
        pret = other.pret;
    }
    return *this;
}

Produs::~Produs() {
    if(denumire) {
        delete[] denumire;
        denumire = NULL;
    }
}

float Produs::getPret() const {
    return pret;
}

const char * Produs::getDenumire() const {
    return denumire;
}

std::ostream & operator<<(std::ostream & COUT, const Produs & obj) {

    COUT << "id: " << obj.id << "\n";
    COUT << "Nume produs: " << (obj.denumire ? obj.denumire : "Unknown") << "\n";
    COUT << "Pret: " << obj.pret << "\n\n";
    return COUT;
}
