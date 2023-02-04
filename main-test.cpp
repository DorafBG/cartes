#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include "carte.h"
#include "joueur.h"
#include "jeu.h"

using namespace std;

int main_test()
{

try{

Carte c1("Ano magique", 2, 2, 12);
Carte c2("Epee", 5, 0, 0);
Carte c3("cuillere", 2, 0, 0);
Carte c4("Epee simple", 5, 1, 0);
vector <Carte> reserve;

c1.affichecourt();
cout << endl;
c1.afficheLong();
c2.afficheLong();





cout << "Degat subis magiques : " << c1.degatMagique(c2) << endl;

cout << "Degat subis physiques : " << c3.degatPhysique(c4) << endl;

Joueur J1("Lucas", 45);

cout << "Nom du Joueur 1 : " << J1.sonNom() << " et il a " << J1.sonPrestige() << " pts de prestige !" << endl;
cout << endl;
J1.afficher();

reserve.push_back(c1);
reserve.push_back(c2);
J1.initCartes(reserve); //je rajoute 2 cartes
J1.afficher(); //doit afficher que 5+2 cartes

if(J1.EnVie() == true){
    cout << "Joueur en vie !" << endl;
} else {
    cout << "Joueur mort !" << endl;
    }
if(J1.ADesCartes() == true){
    cout << "Joueur a des cartes !" << endl;
} else {
    cout << "Joueur n'a plus de cartes !" << endl;
}

Carte Suiv;
J1.carteSuiv(Suiv); // stocke la carte suivante dans J1 et l'enleve de sa pile
J1.afficher();  // Affiche bien le fait que J1 n'a plus que une carte
Suiv.affichecourt(); // Affiche la carte qui a ete retire de sa pile


int atq, def, mag;
string nn;
parser("baguette,0,-2,8", nn, atq, def, mag);
Carte cVide2(nn, atq, def, mag);
cout << "Carte vide 2 : " << endl;
cVide2.affichecourt();

Jeu game;
game.remplirJeu("cartes.txt");

J1.melangerEtAffecter(reserve);
cout << "J1 apres melange :" << endl;
J1.afficher();
vector <Carte> reserveVraie = game.saReserve();
J1.remplirATQCroissante(reserveVraie);

J1.remplirAvecSaisie(reserveVraie);

}
catch(invalid_argument & e)
{
    cerr << "ERR : " << e.what() << endl;
}




}
