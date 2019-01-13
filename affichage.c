#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

#include "function.h"

void afficheTitre(WINDOW *win, char* chaine){
	attron(COLOR_PAIR(3));
	mvwaddstr(win, 2, 0, chaine);
	attroff(COLOR_PAIR(3));
}

void afficheChaine(WINDOW *win, int x, int y, char* chaine){
	
	mvwaddstr(win, x, y, chaine);
}

void afficheLigne(WINDOW *win, int num, char * txt){
	char * ch = malloc(sizeof(txt) + 3);
	strcpy(ch, " - ");
	strcat(ch,txt);
	mvwprintw(win, num +3, 1, ch);
}

void afficheCol_ID(WINDOW* stdscr, int nb_obj){
	
	WINDOW *col;
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	col= subwin(stdscr, 19*LINES/20, COLS/20, LINES/20, 0);
	
    box(col, ACS_VLINE, ACS_HLINE);
    
    wattron(col,A_STANDOUT);
    wattron(col,COLOR_PAIR(2));
    
    mvwprintw(col, 1,  (COLS/20)/2 - strlen("ID")/2, "ID");
    
    wattroff(col,COLOR_PAIR(2));
    wattroff(col,A_STANDOUT);
    
    char txt[4];
    
    for(int i = 1; i<= nb_obj; i++){
		sprintf(txt,"%d",i);
		mvwprintw(col, i+2, (COLS/20)/2 - strlen(txt)/2, txt);
	}
    wrefresh(col);
    
}

void afficheCol(WINDOW* stdscr, char * nom_fichier, char (*data)[TAILLE], int num, int max, int nb_obj){
	
	 WINDOW *col;
	 init_pair(2, COLOR_BLUE, COLOR_WHITE);
	col= subwin(stdscr, 19*LINES/20, 19*COLS/(max*20), LINES/20, COLS/20 + num*(19*COLS/(max*20))); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
	
	int cpt = 0;
	while(nom_fichier[cpt] != '.') cpt++;
	
	char* titrecol = malloc(sizeof(char)*cpt+1);
	for(int a= 0; a < cpt; a++){
		titrecol[a] = nom_fichier[a];
	}
	titrecol[cpt] = '\0';

    box(col, ACS_VLINE, ACS_HLINE);
    
    wattron(col,A_STANDOUT);
    wattron(col,COLOR_PAIR(2));
    
    mvwprintw(col, 1, (19*COLS/(max*20))/2 - strlen(nom_fichier)/2, titrecol);
    
    wattroff(col,COLOR_PAIR(2));
    wattroff(col,A_STANDOUT);
    
    for(int i = 0; i< nb_obj; i++){
		afficheLigne(col, i, data[i]);
	}
	
	free(titrecol);
    wrefresh(col);
    
}

void afficheAide(void){
	FILE * hp;
	char c;
	hp = fopen("help.txt","r");
	
	if (hp) {
    while ((c = getc(hp)) != EOF)
        putchar(c);
    fclose(hp);
	}
	else{
		printf("\t\033[0;31mIl n'existe pas d'aide pour le moment...\n");
	}
	
}

void afficheQuery(char (*query)[TAILLE], int nb_term){
	
	char  dmde[TAILLE + 15];

    initscr();
    
    //WINDOW * wquery;
	//wquery = subwin(stdscr, 2*LINES/20, COLS, 0, 0);
	 
	strcpy(dmde, "VOTRE QUERY : ");
	
	if(nb_term > 1){
		//Pour un passage sous forme de tableau prédécoupé
		for(int a = 0; a < nb_term; a++){
			strcat(dmde, query[a]);
			strcat(dmde," ");
		}
	}
	else{
	//Dans l'eventualité ou le nombre de terme est 1 (chaine non decoupee)
		strcat(dmde, query[0]);
	}
	
	attron(A_BOLD);
    printw(dmde);
    attroff(A_BOLD);
    
    endwin();
}

void afficheTables(char (*tables)[][TAILLE], char (*nom_cols)[TAILLE], int nb_objet, int nb_col){
    
    initscr();
    //wclear(stdscr);
    afficheCol_ID(stdscr,nb_objet);
	for(int i = 0; i < nb_col; i++){
		afficheCol(stdscr, nom_cols[i], (*tables+nb_objet*i), i, nb_col, nb_objet);
	}
    getch();
    
    wclear(stdscr);
    endwin();
    system("clear");
	
}
