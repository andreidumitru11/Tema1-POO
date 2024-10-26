#include "Client.hpp"
int Client::s_nrClienti = 300;

Client::Client(const char * nume)
    : id(Client::s_nrClienti++), nrComenzi(0), capacitate(2)
{
    strcpy(this->nume, nume);
    comenzi = new Comanda[capacitate];
}

Client::Client(const Client & other)
    : id(Client::s_nrClienti++), nrComenzi(other.nrComenzi), capacitate(other.capacitate)
{
    std::cout << "copy Client" << std::endl;
    strcpy(this->nume, other.nume);
    comenzi = new Comanda[capacitate];
    for (int i = 0; i < nrComenzi; ++i) {
        comenzi[i] = other.comenzi[i];
    }
}

Client & Client::operator=(const Client & other) {
    std::cout << "op Client" << std::endl;
    if (this != &other) {
        strcpy(this->nume, other.nume);
        nrComenzi = other.nrComenzi;

        delete[] comenzi;

        capacitate = other.capacitate;
        comenzi = new Comanda[capacitate];

        for (int i = 0; i < nrComenzi; ++i) {
            comenzi[i] = other.comenzi[i];
        }
    }
    return *this;
}

Client::~Client() {
    if(comenzi) {
       delete[] comenzi;
       comenzi = NULL;
    }
}

void Client::plaseazaComanda(const Comanda& comanda) {
    if (nrComenzi >= capacitate) {
        capacitate *= 2;
        Comanda* temp = new Comanda[capacitate];

        for (int i = 0; i < nrComenzi; ++i) {
            temp[i] = comenzi[i];
        }

        delete[] comenzi;
        comenzi = temp;
    }
    comenzi[nrComenzi++] = comanda;
    std::cout << nrComenzi << std::endl;
}

std::ostream & operator<<(std::ostream & COUT, const Client & obj) {
    COUT << "ID Client: " << obj.id << "\n";
    COUT << "Nume: " << obj.nume << "\n";
    COUT << "Numar Comenzi: " << obj.nrComenzi << "\n\n";
    for (int i = 0; i < obj.nrComenzi; ++i) {
        COUT << "Comanda #" << (i + 1) << ":\n" << obj.comenzi[i] << "\n";
    }
    return COUT;
}
