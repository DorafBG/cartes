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

Joueur::Joueur() //constructeur vide
{
    _nom = "Yugi";
    _prestige = 25;
    Carte c1("MainDroite", 1, 0, 0);
    Carte c2("MainGauche", 0, 1, 0);
    Carte c3("Tete", 1, -2, 0);
    Carte c4("Bouche", 1, -1, 2);
    Carte c5("Genou", 2, 0, 0);

    _pileCartes.push_back(c1);
    _pileCartes.push_back(c2);
    _pileCartes.push_back(c3);
    _pileCartes.push_back(c4);
    _pileCartes.push_back(c5);

}

Joueur::Joueur(string nom, int prestige) //constructeur avec parametres
{
    _nom = nom;
    _prestige = prestige;
    Carte c1("MainDroite", 1, 0, 0);
    Carte c2("MainGauche", 0, 1, 0);
    Carte c3("Tete", 1, -2, 0);
    Carte c4("Bouche", 1, -1, 2);
    Carte c5("Genou", 2, 0, 0);

    _pileCartes.push_back(c1);
    _pileCartes.push_back(c2);
    _pileCartes.push_back(c3);
    _pileCartes.push_back(c4);
    _pileCartes.push_back(c5);

}

string Joueur::sonNom()
{
    return _nom;
}

int Joueur::sonPrestige()
{
    return _prestige;
}

void Joueur::afficher() const
{
    cout << "Le joueur " << _nom << " a " << _prestige << " points de prestige, il reste " << _pileCartes.size() << " carte(s) dans sa pile." << endl;
}

void Joueur::initCartes(vector <Carte> reserve)
{
    _pileCartes.pop_back();
    _pileCartes.pop_back();
    _pileCartes.pop_back();
    _pileCartes.pop_back();
    _pileCartes.pop_back();

    // Prendre les 20 premières cartes de la réserve et les ajouter à la pile du joueur.
    for (int i = 0; i < 20 && i < reserve.size(); i++)
    {
        _pileCartes.push_back(reserve[i]);
    }

for (int i = 0; i < _pileCartes.size(); i++) {  //Melange les cartes
    int j = rand() % _pileCartes.size();
    Carte temp = _pileCartes[i];
    _pileCartes[i] = _pileCartes[j];
    _pileCartes[j] = temp;
}


}

bool Joueur::ADesCartes() const
{
    if(_pileCartes.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Joueur::EnVie() const
{
    if(_prestige > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Joueur::carteSuiv(Carte & c) //Permet de connaitre la carte suivante
{
    if(_pileCartes.size() <= 0)
    {
        throw invalid_argument("Il n'y a plus de carte !");
    }
    c = _pileCartes[_pileCartes.size()-1];
    _pileCartes.pop_back();

}


void Joueur::jouentUneCarte(Joueur &j2)
{
    if (_pileCartes.size() <= 0 || j2.ADesCartes() == false)
    {
        throw invalid_argument("Un des joueurs n'a plus de cartes !");
    }

    //Carte Suivante J1
    Carte suiv1;
    suiv1 = _pileCartes[_pileCartes.size()-1];
    _pileCartes.pop_back();

    //Carte Suivante J2
    Carte suiv2;
    j2.carteSuiv(suiv2);

    //Combat entre les deux cartes
    int resPhysique, resMagie;
    resMagie = suiv1.degatMagique(suiv2);
    resPhysique = suiv1.degatPhysique(suiv2);
    bool magiedeg = false;
    bool physiquedeg = false;
    cout << "\n" << suiv1 << " VS " << suiv2 << endl;

    //Modif de prestige en fonction du combat magique
    if(resMagie < 0)
    {
        j2._prestige = j2._prestige + resMagie; //J2 recoit les degats (negatifs)
        cout << "Le joueur " << j2._nom << " a subit " << -resMagie << " degats magiques avec la carte " << suiv1.nom() << " ! " << j2._nom << " a desormais " << j2._prestige << " points de prestige !" << endl;
    }
    else if(resMagie > 0)
    {
        _prestige = _prestige - resMagie; //J1 recoit les degats (positifs)
        cout << "Le joueur " << _nom << " a subit " << resMagie << " degats magiques avec la carte " << suiv2.nom() << " ! " << _nom << " a desormais " << _prestige << " points de prestige !" << endl;
    } else{
        magiedeg = true;
    }

    //Modif de prestige en fonction du combat physique
    if(resPhysique < 0)
    {
        j2._prestige = j2._prestige + resPhysique; //J2 recoit les degats (negatifs)
        cout << "Le joueur " << j2._nom << " a subit " << -resPhysique << " degats physiques avec la carte " << suiv1.nom() << " ! " << j2._nom << " a desormais " << j2._prestige << " points de prestige !" << endl;
    }

    else if(resPhysique > 0)
    {
        _prestige = _prestige - resPhysique; //J1 recoit les degats (positifs)
        cout << "Le joueur " << _nom << " a subit " << resPhysique << " degats physiques avec la carte " << suiv2.nom() << " ! " << _nom << " a desormais " << _prestige << " points de prestige !" << endl;
    } else {
        physiquedeg = true;
    }

    if(magiedeg && physiquedeg){
        cout << "Les deux cartes se sont annulees ! Les points de prestige restent les memes." << endl;
    }

}

void Joueur::melangerEtAffecter(vector<Carte> &veccartes)
{
    srand(time(NULL));
    random_shuffle(veccartes.begin(), veccartes.end());
    _pileCartes = veccartes;
}

void Joueur::remplirATQCroissante(vector <Carte> reserve)  //remplit pile du joueur (20 premieres cartes ATQ croissante)
{
    triAttaque(reserve);
    initCartes(reserve);

}

void Joueur::remplirDEFCroissante(vector <Carte> reserve)  //remplit pile du joueur (20 premieres cartes DEF croissante)
{
    triDefense(reserve);
    initCartes(reserve);
}

void Joueur::remplirMAGCroissante(vector <Carte> reserve)  //remplit pile du joueur (20 premieres cartes MAG croissante)
{
    triMagie(reserve);
    initCartes(reserve);
}

void Joueur::remplirTOUTDeCroissante(vector <Carte> reserve)  //remplit pile du joueur (20 premieres cartes TOUT decroissante)
{
    triDecroissant(reserve);
    initCartes(reserve);
}

void Joueur::remplirScoreCroissant(vector <Carte> reserve)  //remplit pile du joueur (20 premieres cartes score croissante)
{
    triScore(reserve);
    initCartes(reserve);
}

void Joueur::remplirAvecSaisie(vector<Carte>& reserve)
{

    cout << "Voici les cartes que vous pouvez prendre : " << endl;
    for(int i=0; i<reserve.size(); i++)
    {
        reserve[i].affichecourt();
    }


    string nomCarte;
    vector<Carte> pileCartes;
    int compteur=0;
    bool selection;
    cout << "Veuillez saisir le nom des cartes que vous voulez ajouter à votre pile :" << endl;
    while (!(compteur>=20))
    {
        cin >> nomCarte;
        for (int i=0; i<reserve.size(); i++)
        {
            selection = false;
            if (reserve[i].nom() == nomCarte)
            {


                for (int i=0; i<pileCartes.size(); i++)
                {
                    if (pileCartes[i].nom() == nomCarte)
                    {
                        cout << "Carte deja selectionnee !" << endl;
                        selection = true;
                    }
                }
                if(selection == false)
                {
                    cout << "Carte Selectionnee" << endl;
                    pileCartes.push_back(reserve[i]);
                    compteur++;
                    break;
                }
            }
        }
    }
    _pileCartes = pileCartes;
}

void Joueur::remplirAvecSaisieAlphabetique(vector<Carte>& reserve)
{

    cout << "Voici les cartes que vous pouvez prendre : " << endl;
    for(int i=0; i<reserve.size(); i++)
    {
        reserve[i].affichecourt();
    }

        string nomCarte;
        vector<Carte> pileCartes;
        int compteur=0;
        bool selection;
        cout << "Veuillez saisir le nom des cartes que vous voulez ajouter à votre pile :" << endl;

        int debut = 0;
        int fin = reserve.size() - 1;
        bool trouve = false;

        while (!(compteur>=20))
        {
        cin >> nomCarte;
        while(!trouve && debut<=fin)
        {
            int milieu = (debut+fin)/2;
            if(reserve[milieu].nom() == nomCarte)
            {
                for (int i=0; i<pileCartes.size(); i++)
                {
                    if (pileCartes[i].nom() == nomCarte)
                    {
                        cout << "Carte deja selectionnee !" << endl;
                        selection = true;
                    }
                }
                if(selection == false)
                {
                    cout << "Carte Selectionnee" << endl;
                    pileCartes.push_back(reserve[milieu]);
                    compteur++;
                    break;
                }
            }
            else if(reserve[milieu].nom() < nomCarte)
            {
                debut = milieu + 1;
            }
            else if(reserve[milieu].nom() > nomCarte)
            {
                fin = milieu - 1;
            }
        }
        }



}
