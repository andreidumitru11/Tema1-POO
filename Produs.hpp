#include <iostream>
#include <cstring>

#ifndef PRODUS
#define PRODUS

char * copy(const char * buffer);

class Produs {
    static int s_nrProduse;
    const int id;

    char * denumire;
    float pret;
public:
    Produs(const char * denumire = NULL, const float pret = 0.0);
    Produs(const Produs &);
    Produs & operator=(const Produs &);
    ~Produs();
    float getPret() const;
    const char * getDenumire() const;
    friend std::ostream & operator<<(std::ostream &, const Produs &);
};

#endif // PRODUS
