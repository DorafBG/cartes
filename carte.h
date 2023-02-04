#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

void parser(const string &ligne, string &nom,int & a,int &d,int &m);

class Carte{
    string _nom; // le nom de la carte
    int _attaque; // la valeur d'attaque de la carte
    int _defense; // la valeur de defense de la carte
    int _magie; // la puissance magique de la carte

public:

Carte();

Carte(string nom, int attaque, int defense, int magie);

void afficheLong() const; // Affiche toutes les données associées à la carte cible

void affichecourt() const; // Affiche toutes les données associées à la carte cible

string nom() const; //Retourne le nom de la carte

int atq() const; //Retourne l atq de la carte

int def() const;

int mag() const;

int score() const;

int degatMagique(const Carte & c)const;

int degatPhysique(const Carte &c2)const;

void remplir(const string & ligne);
};
ostream& operator<<(ostream& o, const Carte c);
void tri(vector<Carte> & reserve);
void triAttaque(vector <Carte> & reserve);
void triDefense(vector <Carte> & reserve);
void triMagie(vector <Carte> & reserve);
void triDecroissant(vector<Carte>& cartes);
void triScore(vector <Carte> & reserve);


#endif // CARTE_H_INCLUDED
