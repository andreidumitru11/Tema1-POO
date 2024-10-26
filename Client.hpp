#include "Comanda.hpp"

#ifndef CLIENT
#define CLIENT

class Client {
    const int id;
    static int s_nrClienti;

    char nume[250];
    int nrComenzi;
    int capacitate;
    Comanda * comenzi;
public:
    Client(const char * nume = NULL);
    Client(const Client &);
    Client & operator=(const Client &);
    ~Client();
    void plaseazaComanda(const Comanda &);
    friend std::ostream & operator<<(std::ostream &, const Client &);
};
#endif // CLIENT
