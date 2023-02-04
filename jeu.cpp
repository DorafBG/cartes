#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "carte.h"
#include "joueur.h"
#include "jeu.h"

using namespace std;

    Jeu::Jeu()//Constructeur Vide
    {
        Joueur J1("Alpha", 45);
        Joueur J2("Omega", 45);
        _reserve= {};
        _joueur1=J1;
        _joueur2=J2;
    }
    Jeu::Jeu(vector<Carte> reserve,Joueur joueur1,Joueur joueur2)//Constructeur avec parametres
    {
        _reserve=reserve;
        _joueur1=joueur1;
        _joueur2=joueur2;
    }

    void Jeu::initJoueur1(Joueur joueur)
    {
        _joueur1=joueur;
    }
    void Jeu::initJoueur2(Joueur joueur)
    {
        _joueur2=joueur;
    }

    bool Jeu::fini(Joueur & vainqueur)
    {
        if(!(_joueur1.EnVie()))
        {
            vainqueur=_joueur2;
            return true;
        }

        else if(!(_joueur2.EnVie()))
        {
            vainqueur=_joueur1;
            return true;
        }

        else
        {
            return false;
        }
    }
    bool Jeu::Partiefinie()
    {
        if(!(_joueur1.EnVie()))
        {
            return true;
        }
        else if(!(_joueur2.EnVie()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Jeu::jouerCarte() //les joueurs jouent une carte et cela modifie leur prestige en fonction du resultat
    {
        _joueur1.jouentUneCarte(_joueur2);
    }

    int Jeu::vainqueur()
    {
        if(_joueur1.sonPrestige()<=0 && _joueur2.sonPrestige() > 0)
        {
            return -1; //Si vainqueur est j2
        }

        else if(_joueur2.sonPrestige()<=0 && _joueur1.sonPrestige() > 0)
        {
            return +1; //Si vainqueur est j1
        }

        else if(_joueur1.sonPrestige()<=0 && _joueur2.sonPrestige()<=0)
        {
            return 0; //Si match nul

        }
        else
        {
            return 2; //Si partie non finie
        }
    }

    void Jeu::remplirJeu(const string & nomFichier)
    {

        ifstream nomFic;
        string ligne;
        vector<Carte> reserve; //reserve temporaire

        nomFic.open(nomFichier);
        if(!(nomFic.is_open())) throw("ERREUR");
        while(getline(nomFic, ligne))
        {
            int atq, def, mag;
            string nn;
            parser(ligne, nn, atq, def, mag);
            Carte carteLigne(nn, atq, def, mag);
            reserve.push_back(carteLigne);
        }
        tri(reserve);
        _reserve = reserve;

    }

    void Jeu::afficheRegles(){
    cout << "Le jeu consiste en l'affrontement de deux joueurs tres prestigieux (ils ont 25 points de prestige) chacun muni d'une pile de 20 cartes selectionnees a partir d'une reserve identique.\nChaque carte a trois statistiques : une valeur d'attaque physique, une valeur de puissance magique et une valeur de defense physique.\nL'objectif est de reduire les points de prestige de son adversaire et de defendre les siens.\nLe vainqueur est le premier a envoyer son adversaire dans la boue (prestige a zero) ou d'avoir plus de prestige que son adversaire a la fin de l’affrontement (lorsqu'il n'y a plus de carte ou lorsque les deux joueurs sont dans le negatif).\nDans un premier temps chaque joueur classe ses cartes dans l'ordre de son choix.\nEnsuite, on fait defiler les cartes, une carte de chaque joueur a la fois simultanement, comme a la bataille.\nLes cartes de chaque joueur sont comparees et des degats sont infliges au prestige de chacun.\nLes attaques se confrontent aux defenses et les magies se confrontent entre elles.\nLe calcul des degats suit les regles :\n- Le joueur qui a le plus d'attaque physique diminue le prestige de son adversaire de la difference entre sa valeur d'attaque et la valeur de defense de l'autre joueur.\nSi les deux joueurs ont la meme valeur d'attaque physique, aucun degat physique n'est inflige au prestige des joueurs.\nSi le defenseur a plus de defense que la valeur d’attaque, le defenseur ne regagne pas de point de prestige.\n- Le joueur qui a le plus de puissance magique diminue le prestige de son adversaire de la difference entre les valeurs de puissance magique des deux joueurs." << endl;
    }

    void Jeu::afficheReserve(){
        cout << "\nVoici la reserve actuelle du jeu :" << endl;
        for(int i=0; i<_reserve.size(); i++){
            _reserve[i].affichecourt();
        }
    }

    vector<Carte> Jeu::saReserve()
    {
        return _reserve;
    }
