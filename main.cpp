#include "Produs.hpp"
#include "Comanda.hpp"
#include "Client.hpp"
#include <fstream>
std::ifstream inputFile("input.txt");
std::ofstream outFile("output.txt");

//Am tratat main - ul ca fiind corpul unei clase Magazin
//contine tot ce ar trebui sa aiba o clasa Magazin.
//Astfel tratam ca si cand toata discutia este despre un singur Magazin

void citireProduse(Produs **& produse, int & nrProduse, int *& cantitati) {
    inputFile >> nrProduse;

    produse = new Produs*[nrProduse];
    cantitati = new int[nrProduse];

    for(int i = 0; i < nrProduse; i++) {
        char denumire[100];
        float pret;
        int cantitate;

        inputFile >> denumire >> pret >> cantitate;
        produse[i] = new Produs(denumire, pret);
        cantitati[i] = cantitate;
    }
    inputFile.get();
}

void citireClientiComenzi(Client **& clienti, int & nrClienti, const Produs * const* produse, const int nrProduse) {
    inputFile >> nrClienti;
    inputFile.get();

    clienti = new Client*[nrClienti];

    for(int i = 0; i < nrClienti; i++) {
        char nume[250];
        inputFile.getline(nume, 250);
        clienti[i] = new Client(nume);

        int nrComenzi;
        inputFile >> nrComenzi;

        for(int j = 0; j < nrComenzi; j++) {
            int zi, luna, an, nrProduseComanda;
            inputFile >> zi >> luna >> an >> nrProduseComanda;
            Comanda comanda(zi, luna, an);

            for(int k = 0; k < nrProduseComanda; k++) {
                char denumire[100];
                int cantitate;
                inputFile >> denumire >> cantitate;

                for(int l = 0; l < nrProduse; l++)
                    if(!strcmp(denumire, produse[l]->getDenumire())) {
                        comanda.adaugareProdus(produse[l], cantitate);
                        break;
                    }
                inputFile.get();
            }
           clienti[i]->plaseazaComanda(comanda);
        }
        inputFile.get();
    }
}

int adaugareProdusInStoc(Produs **& produse, int size, Produs * produsNou) {
    Produs ** newProduse = new Produs*[size + 1];
    for(int i = 0; i < size; i++)
        newProduse[i] = produse[i];
    newProduse[size] = produsNou;
    produse = newProduse;
    return ++size;
}

int main()
{
   Produs ** produse = NULL;
   int nrProduse = 0, * cantitati = NULL;
   Client ** clienti = NULL;
   int nrClienti = 0;
   citireProduse(produse, nrProduse, cantitati);
   Produs * produsNou = new Produs("PC", 99999.99);
   nrProduse = adaugareProdusInStoc(produse, 3, produsNou);
   citireClientiComenzi(clienti, nrClienti, produse, nrProduse);
   for(int i = 0; i < nrClienti; i++)
        outFile << *clienti[i];
   for(int i = 0; i < nrProduse; i++)
        delete produse[i];
   delete[] produse;
   delete[] cantitati;

   for(int i = 0; i < nrClienti; i++)
       delete clienti[i];
   delete[] clienti;
}
