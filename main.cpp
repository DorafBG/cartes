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


int main()
{
try{
bool rejouer;
do{
char choix;

cout << "Mettez en plein ecran" << endl;
cout << " ::::::::      :::     :::::::::  :::::::::     :::::::::: :::::::::::  ::::::::  :::    ::: ::::::::::: :::::::::: :::::::::   ::::::::  " << endl;
cout << ":+:    :+:   :+: :+:   :+:    :+: :+:    :+:    :+:            :+:     :+:    :+: :+:    :+:     :+:     :+:        :+:    :+: :+:    :+: " << endl;
cout << "+:+         +:+   +:+  +:+    +:+ +:+    +:+    +:+            +:+     +:+        +:+    +:+     +:+     +:+        +:+    +:+ +:+        " << endl;
cout << "+#+        +#++:++#++: +#++:++#:  +#+    +:+    :#::+::#       +#+     :#:        +#++:++#++     +#+     +#++:++#   +#++:++#:  +#++:++#++ " << endl;
cout << "+#+        +#+     +#+ +#+    +#+ +#+    +#+    +#+            +#+     +#+   +#+# +#+    +#+     +#+     +#+        +#+    +#+        +#+ " << endl;
cout << "#+#    #+# #+#     #+# #+#    #+# #+#    #+#    #+#            #+#     #+#    #+# #+#    #+#     #+#     #+#        #+#    #+# #+#    #+# " << endl;
cout << " ########  ###     ### ###    ### #########     ###        ###########  ########  ###    ###     ###     ########## ###    ###  ########  \n" << endl;

do{
cout << "Voulez vous jouer contre un humain ou une IA ? (H/I)" <<endl;
cin >> choix;

}while(choix!='H' && choix!='I');
if(choix=='H'){ //CHOIX HUMAINS
    cout << "Vous jouerez contre un autre joueur." << endl;
    cout << "Selectionner le nom de deux joueurs :" << endl;
    string nomj1 ,nomj2;
    cin >> nomj1 >> nomj2;
    Joueur j1(nomj1, 25);
    Joueur j2(nomj2, 25);

    vector<Carte> reserve;
    Jeu jeuH(reserve, j1, j2);
    jeuH.afficheRegles();
    jeuH.remplirJeu("cartes.txt");
    jeuH.afficheReserve();
    reserve = jeuH.saReserve();

    do{ //CARTES JOUEUR 1
    cout << "\nQuel strategie voulez vous adopter pour votre pile de cartes " << nomj1 <<"?\n- [1] Tri par score, equivalent a ATQ+DEF+MAG\n- [2] Tri par ATQ croissante\n- [3] Tri par DEF croissante\n- [4] Tri par tout decroissante\n- [5] Tri par MAG croissante\n- [6] Vous choissisez vous meme vos cartes" << endl;
    cin >> choix;
    }while(choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6');


    if(choix=='1'){
        j1.remplirScoreCroissant(reserve);
        jeuH.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en score !" << endl;
    } else if(choix=='2'){
        j1.remplirATQCroissante(reserve);
        jeuH.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en attaque !" << endl;
    } else if(choix=='3'){
        j1.remplirDEFCroissante(reserve);
        jeuH.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en defense !" << endl;
    } else if(choix=='4'){
        j1.remplirTOUTDeCroissante(reserve);
        jeuH.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus faibles en caracteristiques !" << endl;
    } else if(choix=='5'){
        j1.remplirMAGCroissante(reserve);
        jeuH.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en magie !" << endl;
    } else {
        j1.remplirAvecSaisie(reserve);
        jeuH.initJoueur1(j1);
        cout << "Votre pile est terminee !" << endl;
    }

    do{ //CARTES JOUEURS2
    cout << "\nQuel strategie voulez vous adopter pour votre pile de cartes " << nomj2 <<"?\n- [1] Tri par score, equivalent a ATQ+DEF+MAG\n- [2] Tri par ATQ croissante\n- [3] Tri par DEF croissante\n- [4] Tri par tout decroissante\n- [5] Tri par MAG croissante\n- [6] Vous choissisez vous meme vos cartes" << endl;
    cin >> choix;
    }while(choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6');


    if(choix=='1'){
        j2.remplirScoreCroissant(reserve);
        jeuH.initJoueur2(j2);
        cout << "Votre pile est constituee des cartes les plus fortes en score !" << endl;
    } else if(choix=='2'){
        j2.remplirATQCroissante(reserve);
        jeuH.initJoueur2(j2);
        cout << "Votre pile est constituee des cartes les plus fortes en attaque !" << endl;
    } else if(choix=='3'){
        j2.remplirDEFCroissante(reserve);
        jeuH.initJoueur2(j2);
        cout << "Votre pile est constituee des cartes les plus fortes en defense !" << endl;
    } else if(choix=='4'){
        j2.remplirTOUTDeCroissante(reserve);
        jeuH.initJoueur2(j2);
        cout << "Votre pile est constituee des cartes les plus faibles en caracteristiques !" << endl;
    } else if(choix=='5'){
        j2.remplirMAGCroissante(reserve);
        jeuH.initJoueur2(j2);
        cout << "Votre pile est constituee des cartes les plus fortes en magie !" << endl;
    } else{
        j2.remplirAvecSaisie(reserve);
        jeuH.initJoueur2(j2);
        cout << "Votre pile est terminee !" << endl;
    }

    Joueur vainqueur;
    while(jeuH.fini(vainqueur) == false){ //Jeu en boucle
    jeuH.jouerCarte();
    }

cout << "\nLa partie est terminee ! Le vainqueur est : " << vainqueur.sonNom() << " ! Il lui reste " << vainqueur.sonPrestige() << " points de prestige !\nBien joue a lui!" << endl;
do{
cout << "Voulez vous rejouer ? (o/n) : " <<endl;
cin >> choix;
}while(choix!='o' && choix!='n');
if(choix=='n'){
    rejouer = false;
    break;
}


}
else { // CHOIX IA
    cout << "Vous jouerez contre une IA." << endl;
    cout << "Selectionner le nom de votre joueur :" << endl;
    string nomj1;
    cin >> nomj1;
    Joueur j1(nomj1, 25);
    Joueur j2("BOT", 25);

    vector<Carte> reserve;
    Jeu jeuIA(reserve, j1, j2);
    jeuIA.afficheRegles();
    jeuIA.remplirJeu("cartes.txt");
    jeuIA.afficheReserve();
    reserve = jeuIA.saReserve();

    do{ //CARTES JOUEUR 1
     cout << "\nQuel strategie voulez vous adopter pour votre pile de cartes " << nomj1 <<"?\n- [1] Tri par score, equivalent a ATQ+DEF+MAG\n- [2] Tri par ATQ croissante\n- [3] Tri par DEF croissante\n- [4] Tri par tout decroissante\n- [5] Tri par MAG croissante\n- [6] Vous choissisez vous meme vos cartes" << endl;
    cin >> choix;
    }while(choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6');


    if(choix=='1'){
        j1.remplirScoreCroissant(reserve);
        jeuIA.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en score !" << endl;
    } else if(choix=='2'){
        j1.remplirATQCroissante(reserve);
        jeuIA.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en attaque !" << endl;
    } else if(choix=='3'){
        j1.remplirDEFCroissante(reserve);
        jeuIA.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en defense !" << endl;
    } else if(choix=='4'){
        j1.remplirTOUTDeCroissante(reserve);
        jeuIA.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus faibles en caracteristiques !" << endl;
    } else if(choix=='5'){
        j1.remplirMAGCroissante(reserve);
        jeuIA.initJoueur1(j1);
        cout << "Votre pile est constituee des cartes les plus fortes en magie !" << endl;
    } else {
        j1.remplirAvecSaisie(reserve);
        jeuIA.initJoueur1(j1);
        cout << "Votre pile est terminee !" << endl;
    }

    int alea = rand() % 5 + 1; //Choix IA
    if(alea == 1){
        j2.remplirScoreCroissant(reserve);
        jeuIA.initJoueur2(j2);
    } else if(alea == 2){
        j2.remplirATQCroissante(reserve);
        jeuIA.initJoueur2(j2);
    } else if(alea == 3){
        j2.remplirDEFCroissante(reserve);
        jeuIA.initJoueur2(j2);
    } else if(alea == 4){
        j2.remplirTOUTDeCroissante(reserve);
        jeuIA.initJoueur2(j2);
    } else if(alea == 5){
        j2.remplirMAGCroissante(reserve);
        jeuIA.initJoueur2(j2);
    }

    Joueur vainqueur;
    while(jeuIA.fini(vainqueur) == false){ //Jeu en boucle
    jeuIA.jouerCarte();
    }

cout << "\nLa partie est terminee ! Le vainqueur est : " << vainqueur.sonNom() << " ! Il lui reste " << vainqueur.sonPrestige() << " points de prestige !\nBien joue a lui!" << endl;
do{
cout << "Voulez vous rejouer ? (o/n) : " <<endl;
cin >> choix;
}while(choix!='o' && choix!='n');
if(choix=='n'){
    rejouer = false;
    break;
}
}
}while(rejouer != true);



}
catch(invalid_argument & e)
{
    cerr << "ERR : " << e.what() << endl;
}

}
