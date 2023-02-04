#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include <string>
#include <vector>
#include <fstream>
#include <limits>

class Joueur{
    string _nom;
    int _prestige;
    vector <Carte> _pileCartes;

public:

Joueur();

Joueur(string nom, int prestige);

string sonNom();

int sonPrestige();

void afficher() const;

void initCartes(vector <Carte> reserve);

bool ADesCartes() const;

bool EnVie() const;

void carteSuiv(Carte & c);

void jouentUneCarte(Joueur & j2);

void melangerEtAffecter(vector<Carte> &vecCartes);

void remplirATQCroissante(vector <Carte> reserve);

void remplirDEFCroissante(vector <Carte> reserve);

void remplirMAGCroissante(vector <Carte> reserve);

void remplirTOUTDeCroissante(vector <Carte> reserve);

void remplirScoreCroissant(vector <Carte> reserve);

void remplirAvecSaisie(vector<Carte>& reserve);

void remplirAvecSaisieAlphabetique(vector<Carte>& reserve);

};

#endif // JOUEUR_H_INCLUDED
