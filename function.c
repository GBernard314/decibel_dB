#include <stdlib.h>
#include <stdio.h>
#include "function.h"
#include <string.h>
#include <time.h>

#define TAILLE 100
#define true 1
#define false 0

int quit;
char results[BUFF_SIZE];

/* Fonction de comparaison d'une chaine à une autre */
/* Renvoie vrai (1) si la chaine est equivalente, faux (0) si elle ne l'est pas */
int compare_chaines(char * a, char * b){
  short i = 0;
  short egal;

  while(a[i] != '\0' && b[i] != '\0'){
    if(a[i] != b[i]){
      egal = false;
      break;
    }
    else{
      egal = true;
    }
    i++;
  }

  if(egal == true)
  return 1;
  else
  return 0;
}

/* Fonction de detection de ligne en fonction d'un mot */
/* Renvoie le numero de la ligne correspondant a la ligne contenant le mot */
int num_ligne(char * chemin_fichier, char * argument_a_trouver){
  int num = -1;
  FILE * f;
  char temp[TAILLE];
  strcpy(temp, "NULL");
  f = fopen(chemin_fichier, "rt");

  while (compare_chaines(temp, argument_a_trouver) != 1) {
    num ++;
    fgets(temp, TAILLE, f);
  }

  fclose(f);

  return num+1;
}

void create_(char * nom_database, int nb_mot_de_la_query, char (*phrase)[TAILLE]){
//CREATE nom
//CREATE nom WITH nom1 nom2 ...
if (nb_mot_de_la_query == 2 || nb_mot_de_la_query > 3) {
  char cmdcreate[TAILLE];
  strcpy(cmdcreate, "mkdir ");
  strcat(cmdcreate, nom_database);
  //exec cmd
  system(cmdcreate);

  //on reutilise notre variable cmd pour creer les nb tables
  strcpy(cmdcreate, "cd ");
  strcat(cmdcreate, nom_database);
  system(cmdcreate);

  strcat(cmdcreate, "");

  char temp[TAILLE];
  FILE * f;
  //Pour creer les fichiers demandes dans la query
  for (int i = 3; i < nb_mot_de_la_query; i++) {
    strcpy(temp, nom_database);
    strcat(temp, "/");
    strcat(temp, phrase[i]);
    strcat(temp, ".dcb");
    f = fopen(temp, "w");
    fclose(f);
  }
  char message_creation[TAILLE];
  strcpy(message_creation, "Table \033[32m ");
  strcat(message_creation, nom_database);
  strcat(message_creation, " \033[0m creee avec ");
  for (int o = 3; o < nb_mot_de_la_query-1; o++) {
    strcat(message_creation, phrase[o]);
    strcat(message_creation, " \033[0m,  \033[32m");
  }
  strcat(message_creation, phrase[nb_mot_de_la_query-1]);
  printf(" \033[0mDecibel\t~ %s\n", message_creation);
}

//CREATE nom WITH
}

char * chemin_acces(char * nom_dossier, char * nom_fichier){
  char * ch = (char *) malloc (sizeof(char) * TAILLE);
  int i = 0, j= 0;

  while(nom_dossier[i] != '\0'){
    ch[i] = nom_dossier[i];
    i++;
  }
  ch[i] = '/';
  i++;

  while(nom_fichier[j] != '\0'){
    ch[i+j] = nom_fichier[j];
    j++;
  }
  ch[i+j+1] = '.';
  ch[i+j+2] = 'd';
  ch[i+j+3] = 'c';
  ch[i+j+4] = 'b';
  ch[i+j] = '\0';

  return (char *) ch;
}

void add_(char * nom_attribut, char * nom_table){

  char cherche_fichier_cmd[3];
  strcpy(cherche_fichier_cmd, "ls");
  char list[TAILLE/2];

  strcpy(list,executeCmd(cherche_fichier_cmd));
  for (int k = 0; k < strlen(list)-1; k++) {
    if (list[k] == '\n') {
      list[k] = ' ';
    }
  }

  char liste_fichier_racine[TAILLE][TAILLE];
  split_entry(list, liste_fichier_racine);

  int cpt = 0;
  for (int i = 0; i < split_entry(list, liste_fichier_racine); i++) {
    if (compare_chaines(nom_table, liste_fichier_racine[i]) != 1) {
      cpt++;
    }
  }

  if (cpt == split_entry(list, liste_fichier_racine)) {
    printf("\033[0;31mDecibel\t~ Entrer un nom de table valide\n");
    return ;
  }

	FILE * f;
  // Transformer les '\n' en ' ' pour
  // utiliser la fonction de Thibaud
  char req[TAILLE/2];
  strcpy(req, "cd ./");
  strcat(req, nom_table);
  strcat(req, " ; ls");

  char * affiche = executeCmd(req);
  if (strlen(affiche) == 0) {
    printf("\033[0;31mDecibel\t~ dossier vide\n");
    char name[TAILLE/2];
    strcpy(name, nom_table);
    strcat(name, "/");
    strcat(name, nom_attribut);
    strcat(name, ".dcb");
    f = fopen(name, "w");
    fclose(f);
    return;
  }

  for (int k = 0; k < strlen(affiche)-1; k++) {
    if (affiche[k] == '\n') {
      affiche[k] = ' ';
    }
  }



  char chemin_fichier[TAILLE/2][TAILLE];

  split_entry(affiche, chemin_fichier);

  char temp[TAILLE];

  strcpy(temp, nom_table);
  strcat(temp, "/");
  strcat(temp, nom_attribut);

  char nombre_lignes_fichier[TAILLE];
  strcpy(nombre_lignes_fichier, nom_table);
  strcat(nombre_lignes_fichier, "/");
  strcat(nombre_lignes_fichier, chemin_fichier[0]);


  int nb_objet = nombre_lignes(nombre_lignes_fichier);
  //Pour creer le fichiers demande dans la query
  strcpy(temp, nom_table);
  strcat(temp, "/");
  strcat(temp, nom_attribut);
  strcat(temp, ".dcb");


  f = fopen(temp, "w");
  for (int i = 0; i < nb_objet; i++) {
    fprintf(f, "non_acquis\n");
  }
  fclose(f);
  printf("\033[1;35mDecibel\t~\033[0;32m Attribut \033[32m %s \033[0m ajoute dans \033[32m %s \033[0m\n", nom_attribut, nom_table);


}

void delete_(char * nom_dossier, char * nom_attribut, char * valeur_testee){
  FILE * f;
  char chemin[TAILLE];
  strcpy(chemin, nom_dossier);
  strcat(chemin, "/");
  strcat(chemin, nom_attribut);
  strcat(chemin, ".dcb");
  //printf("chemin = %s\n", chemin);

  int numero_ligne;
  char nom_fichier[TAILLE];
  strcpy(nom_fichier, nom_attribut);
  strcat(nom_fichier, ".dcb");
  //printf("nom_fichier = %s\n", nom_fichier);
  int nb_objet = nombre_lignes(chemin);
  //printf("nb_objet = %d\n", nb_objet);
  f = fopen(chemin, "r+");

  if (f == NULL) {
    //printf("Decibel\t~ Entrer une requete valide\n");
    return;
  }
  else {
    numero_ligne = num_ligne(chemin, valeur_testee);
    printf("numero_ligne = %d\n", numero_ligne);
  }
  if (numero_ligne == -1) {
    printf("\033[0;31mDecibel\t~ \033[1;31mValeur inexistante\033[0;31m dans la table\n");
    return;
  }

  // Transformer les '\n' en ' ' pour
  // utiliser la fonction de Thibaud
  char cmddel[TAILLE];

  strcpy(cmddel, "cd ./");
  strcat(cmddel, nom_dossier);
  strcat(cmddel, " ; ls");

  //printf("cmddel = %s\n", cmddel);

  char * ls = (char *) malloc(sizeof(char) * TAILLE/2 +1);
  strcpy(ls, "");
  ls = executeCmd(cmddel);
  //printf("ls = %s\n", ls);
  int k;

  for (k = 0; k < strlen(ls)-1; k++) {
    if (ls[k] == '\n') {
      ls[k] = ' ';
    }
  }
  ls[k] = '\0';

  strcpy(cmddel, "");

  //printf("executeCmd ok\n");


  char chemin_fichier[TAILLE/2][TAILLE];
  //printf("numero_ligne = %d\n", numero_ligne);

  int nb_fichier = split_entry(ls, chemin_fichier);
  char tmp[TAILLE];
  char buff[TAILLE];
  char ch_dump[TAILLE];

  FILE * dump;
  for (int i = 0; i < nb_fichier; i++) {
    //int cpt=0;

    strcpy(tmp, nom_dossier);
    strcat(tmp, "/");
    strcat(tmp, chemin_fichier[i]);

    strcpy(ch_dump, nom_dossier);
    strcat(ch_dump, "/.dump_");
    strcat(ch_dump, chemin_fichier[i]);
    //printf("tmp = %s\n", tmp);
    f = fopen(tmp, "r+");
    dump = fopen(ch_dump, "w+");
    for (int j = 0 ; j < numero_ligne-1; j++) {
      fscanf(f, "%s\r", buff);
      fprintf(dump, "%s\n", buff);
      //cpt++;
      //printf("cpt = %d\n", cpt);
    }
    fscanf(f, "%s\r", buff);
    for (int j = numero_ligne; j < nb_objet; j++) {
      fscanf(f, "%s\r", buff);
      fprintf(dump, "%s\n", buff);
    }
    fclose(f);
    fclose(dump);

    f = fopen(tmp, "w+");
    dump = fopen(ch_dump, "r+");
    for (int j = 0; j < nb_objet - 1; j++) {
      fscanf(dump, "%s\r", buff);
      fprintf(f, "%s\n", buff);
    }
    fclose(f);
    fclose(dump);
    //fprintf(f, "%s\r", "non_acquis");
    //printf("non acquis ecrit\n");
  }
  return;
}

void update_(char * nom_dossier, char * nom_attribut, char * valeur_testee){

  delete_(nom_dossier, nom_attribut, valeur_testee);
  //printf("delete fait\n");
  insert_(nom_dossier);
  //printf("insert fait\n");

  return;
}

void drop_table_(char * nom_table){
  char temp[TAILLE];
  strcpy(temp, "cd ");
  strcat(temp, nom_table);
  strcat(temp, " ; rm * ; rm .??* ; cd ../ ; rmdir ");
  strcat(temp, nom_table);
  printf("\n\033[0;33mDecibel\t~ Etes vous sur de vouloir supprimer la table \033[1;33m %s ? (y or n) \n", nom_table);
  char conf = 'n';
  scanf("%c", &conf);
  if (conf == 'y') {
    system(temp);
  }
  return;
}

void drop_attribute_(char * nom_table, char * nom_attribut){
  char temp[TAILLE];
  strcpy(temp, "cd ");
  strcat(temp, nom_table);
  strcat(temp, " ; ");
  strcat(temp, "rm ");
  strcat(temp, nom_attribut);
  strcat(temp, ".dcb");
  //printf("cmd finale = %s\n", temp);
  system(temp);
  return;
}

void select_(char (*phrase)[TAILLE], int nb_mot_requete){

  char cmdsel[TAILLE/2];
  char ls[TAILLE/2];
  char nom_dossier[TAILLE/2];
  char chemin_fichier[TAILLE/2][TAILLE];
  char lsreturn[TAILLE/2][TAILLE];

  int nb_fichier;
  int nb_objet;
  int compte_mot = 0;
  int nb_to_sel = 0;
	/*compteurs*/
  int k;
  int zz = 1;
  int yy;

  FILE * f;

  //On cherche à connaitre le nom du dossier (table) à parcourir à partir de l'entrée utilisateur.
  //On parcours donc la query en cherchant le mot qui suit FROM:
  while( compare_chaines(phrase[compte_mot], "FROM") !=1 && compare_chaines(phrase[compte_mot], "from") !=1 ){
	  compte_mot++;
  }

  strcpy(nom_dossier, phrase[compte_mot + 1] );

  strcpy(cmdsel, "cd ./");
  strcat(cmdsel, nom_dossier);
  strcat(cmdsel, " ; ls");

  strcpy(ls, "");
  strcpy(ls,executeCmd(cmdsel));

	// Transformer les '\n' en ' ' pour utiliser split_entry;
  for (k = 0; k < strlen(ls)-1; k++) {
    if (ls[k] == '\n') {
      ls[k] = ' ';
    }
  }
  ls[k] = '\0';

  strcpy(cmdsel, "");
  executeCmd("hash -r");

  nb_fichier = split_entry(ls, chemin_fichier);
			   split_entry(ls,lsreturn);

  for (int cpt = 0; cpt < nb_fichier; cpt++) {
    strcpy(chemin_fichier[cpt], chemin_acces(nom_dossier, chemin_fichier[cpt]) );
  }

  //Puisque chaque fichier possède un même nombre de lignes (meme si donnee vide), on connait le nb d'objet grace au 1er fichier.
  nb_objet = nombre_lignes(chemin_fichier[0]);

  char to_be_printed[nb_fichier][nb_objet][TAILLE];

	if (compare_chaines(phrase[1], "*") == 1 || compare_chaines(phrase[1], "ALL") == 1 || compare_chaines(phrase[1], "all") == 1){
	//CAS DE SELECTION UNIVERSELLE
		for (int i = 0; i < nb_fichier; i++) {
			f = fopen(chemin_fichier[i], "r+");

			if(f == NULL){
			  printf("\033[0;31mERREUR OUVERTURE DU FICHIER %s x\n",chemin_fichier[i]);
			}
			else{
			  for (int j = 0; j < nb_objet; j++) {
				fscanf(f, "%s\r",to_be_printed[i][j]);
			  }
			}
			fclose(f);
		 }
		 nb_to_sel = nb_fichier;
	}
	else{
	//SELECTION D'UN OU PLUSIEURS ATTRIBUTS
		while( (zz < nb_mot_requete-2) && ( compare_chaines(phrase[zz], "FROM") != 1 && compare_chaines(phrase[zz], "from") != 1) ){

			//nb_fichier est le compteur du retour de la commande ls.
			for(yy = 0; yy <= nb_fichier ; yy++){
				//On verifie si l'entree zz existe parmis tous les fichiers lus.
				if( compare_chaines(lsreturn[yy], phrase[zz]) == 1){
				//Comparaison vraie :
					//Ouverture du fichier en question pour lecture et enregistrement dans le tableau à afficher
					strcpy(chemin_fichier[nb_to_sel], chemin_acces(nom_dossier, phrase[zz]));
					strcat(chemin_fichier[nb_to_sel],".dcb");
					f = fopen( chemin_fichier[nb_to_sel] , "r+");
					for (int j = 0; j < nb_objet; j++) {
						//enregistre chaque ligne comme un objet.
						fscanf(f, "%s\r",to_be_printed[nb_to_sel][j]);
					 }
					 fclose(f);

					nb_to_sel++;
				}
			}

			zz++; //Increment peu importe echec ou réussite.
			// --> On va chercher le terme suivant dans la query.
		}
	}
	//Appel des fonctions d'affichage générales dans le terminal
	afficheQuery(phrase, nb_mot_requete);
	afficheTables( to_be_printed, chemin_fichier, nb_objet, nb_to_sel);
	//affiche		tableau	  table des fichiers	nb_terme   nb_to_sel



}

char* retourneChaine (char* str){
	char* ret = malloc(sizeof(char)*(strlen(str)+1));
	int i2 = 0;
	for(int i=strlen(str);i>0;i--){
		ret[i2] = str[i];
		i2++;
	}
	return ret;
}

char * executeCmd(char * cmd) {
  FILE *fp;

  int size_line;
  char line[BUFF_SIZE];
  char * ch_a_traiter = (char*) malloc(sizeof(char *)*strlen(cmd)+1);

  strcpy(results,"");
  strcpy(ch_a_traiter,cmd);

  if (ch_a_traiter != NULL) {
    /* Open the command for reading. */
    fp = popen(ch_a_traiter, "r");
    if (fp != NULL) {

      /* Read the output a line at a time - output it. */
      while (fgets(line, size_line = sizeof(line), fp) != NULL) {
        strcat(results, line);
      }
    }
    /* close */
    pclose(fp);
  }

  free(ch_a_traiter);
  ch_a_traiter = NULL;
  return results;
}

/* Fonction de decoupage d'une entree utilisateur en une suite de motes */
/* Renvoie un tableau de chaines (phrase qui contient plusieurs mots) */
int split_entry( char* raw_input, char (*phrase)[TAILLE]){

  //printf("size finale : %d\n",sizeof(*phrase)*sizeof(**phrase));


  int i = 0, num_mot = 0, lettre = 0;

  while(raw_input[i] != '\0'){

    if(raw_input[i] == 32){

      phrase[num_mot][lettre] = '\0';
      num_mot++;
      lettre = 0;

    }
    else{
      phrase[num_mot][lettre] = raw_input[i];

      lettre++;
    }

    i++;

  }

  phrase[num_mot][lettre] = '\0';

  if(i<2) {
	  strcpy(phrase[0], "null");
	  return 0;
  }

	return num_mot+1;
}


/* Fonction de detection de nombre de fichier dans un dossier */
/* AKA nombre d'attribut par "objet" */
int nombre_fichier(char * nom_dossier){
  FILE *fp;
  char path[1035];
  int nb_fichier;

  char commande[100] = "cd ./";
  strcat(commande, nom_dossier);
  strcat(commande, " ; ls -l | wc -l");

  /* Open the command for reading. */
  fp = popen(commande, "r");
  if (fp == NULL) {
    printf("\033[0;31mFailed to run popen() command\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    nb_fichier = path[0] - '0' - 1;
  }

  /* close */
  pclose(fp);


  return nb_fichier;
}

/* Fonction de detection de nombre de ligne dans un fichier courant */
/* AKA nombre d'entite dans la base */
int nombre_lignes(char * nom_fichier){
  FILE *f;
  f = fopen(nom_fichier, "r+");
  if (f == NULL) {
    printf("\033[0;31mDecibel\t~ Le fichier %s n'existe pas\n", nom_fichier);
    return 0;
  }
  int nb_lignes = 0;
  char chr;
  chr = getc(f);

  if (chr == EOF) {
    return 0;
  }


  while (chr != EOF) {
    if (chr == '\n') {
      nb_lignes++;
    }
    chr = getc(f);
  }
  fclose(f);

  return nb_lignes;
}

void insert_(char * nom_database){

  int nb_fichier;
  int nb_words;

  char liste[TAILLE];

  strcpy(liste,executeCmd("ls"));
  int k;

  for (k = 0; k < strlen(liste)-1; k++) {
    if (liste[k] == '\n') {
      liste[k] = ' ';
    }
  }
  liste[k] = '\0';

  char liste_fichier_racine[TAILLE/2][TAILLE];
  nb_words = split_entry(liste, liste_fichier_racine);

  int cpt = 0;
  for (int i = 0; i < nb_words; i++) {
    if (compare_chaines(nom_database, liste_fichier_racine[i]) != 1) {
      cpt++;
    }
  }

  if (cpt == nb_words) {
    printf("\033[0;31mDecibel\t~ Entrer un nom de table valide\n");
    return ;
  }

  executeCmd("cd ../");


  char chemin_fichier_ins[TAILLE/2][TAILLE];
  char liste_fichier[TAILLE/2][TAILLE];
  char commande[TAILLE];

  strcpy(commande, "cd ./");
  strcat(commande, nom_database);
  strcat(commande, " ; ls ");

  char ls_insert[TAILLE];
  strcpy(ls_insert,executeCmd(commande));

  for (k = 0; k < strlen(ls_insert)-1; k++) {
    if (ls_insert[k] == '\n') {
      ls_insert[k] = ' ';
    }
  }
  ls_insert[k] = '\0';

  executeCmd("hash -r");


  nb_fichier = split_entry(ls_insert, chemin_fichier_ins);

  char bufferi[TAILLE];
  char temp_chemin[TAILLE];
  int l;
  FILE * fs;

  for (int i = 0; i < nb_fichier; i++) {
    for (l = 0; l < strlen(chemin_fichier_ins[i])-4; l++) {
      liste_fichier[i][l] = chemin_fichier_ins[i][l];
    }
    liste_fichier[i][l] = '\0';

    printf("\033[1;35mDecibel\t~ \033[0;36m Quelle valeur voulez vous affecter a\033[1;30m %s \033[0;36m?\n", liste_fichier[i]);
    printf("\033[0;32m\t>\033[0;30m ");
    scanf("%[^\n]%*c", bufferi);

    //Pour ecrire dans le fichiers[i]

    strcpy(temp_chemin, nom_database);
    strcat(temp_chemin, "/");
    strcat(temp_chemin, liste_fichier[i]);
    strcat(temp_chemin, ".dcb");

    fs = fopen(temp_chemin, "ab+");
    if(fs != NULL){
      fprintf(fs, "%s\n", bufferi);

      fclose(fs);
    }
    else{
      printf("\033[0;31mErreur lors de l'affectation du champ : \033[1;31mfichier NULL\n");
    }

  }

  printf("\033[0;36mDecibel\t~ Information enregistree avec succes\n");


}


void fonction(char *requete){
  char phrase[TAILLE/2][TAILLE];
  int nb_mot_requete;
  nb_mot_requete = split_entry(requete, phrase);

  // Si la requete est vide
  if (nb_mot_requete < 1) {
	  printf("\033[0;31mRequête invalide, \n");
    return;
  }

  // Si on veut quitter
  if (compare_chaines(phrase[0], "QUIT") == 1 || compare_chaines(phrase[0], "quit") == 1){
    quit = true;
    return;
    //On quitte ainsi la boucle
  }


  //  Detection du SELECT
  if (compare_chaines(phrase[0], "SELECT") == 1 || compare_chaines(phrase[0], "select")) {
    //SELECT; (mot seul)
    if (nb_mot_requete == 1) {
      printf("\033[0;31mDecibel\t~ Entrer un ou plusieurs \033[1;31mnom de table a afficher \033[0;31msepares d'un espace\n");
    }
    //SELECT *
    else{
      //SELECT *;
      if (nb_mot_requete == 2) {
        printf("\033[0;31mDecibel\t~ Entrer une requete complete\n");
      }
      //SELECT * FROM;
      if (nb_mot_requete == 3) {
        printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom de base de donnee\n");
      }
      //SELECT * FROM [...];
      if (nb_mot_requete >= 4) {
        printf("launching select\n");
        select_(phrase, nb_mot_requete);
      }
	}
  }
  //
  // Detection du SELECT finie
  //

  //
  //  Detection du CREATE
  //
  if (compare_chaines(phrase[0], "CREATE") == 1 || compare_chaines(phrase[0], "create") == 1){
    //CREATE;
    if (nb_mot_requete == 1) {
      printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom de base de donnee\n");
    }
    //CREATE [...] [...] [...]
    else if (nb_mot_requete < 4) {
      printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
    }
    else{
      //printf("nb_mot = %d\nrequete = %s\n", nb_mot_requete, requete);

      create_(phrase[1], nb_mot_requete, phrase);
    }
  }
  //
  // CREATE finie
  //

  //
  //  Detection du ADD
  //
  if (compare_chaines(phrase[0], "ADD") == 1 || compare_chaines(phrase[0], "add") == 1){
    // ADD
    if (nb_mot_requete == 1) {
      printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom d'attribut\n");
      return;
    }
    // ADD nom_attribut
  // ADD nom_attribut INTO
  if (nb_mot_requete == 2 || nb_mot_requete == 3) {
    printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom de table\n");
    return;
  }
  // ADD nom_attribut INTO nom_table
  if (nb_mot_requete == 4) {
    add_(phrase[1], phrase[nb_mot_requete-1]);
  }
  // ADD nom_attribut INTO nom_table [...]
  if (nb_mot_requete > 4) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
    return;
  }
}
//
//  Detection du ADD finie
//

//
//  Detection du INSERT
//
if (compare_chaines(phrase[0], "INSERT") == 1 || compare_chaines(phrase[0], "insert") == 1){
  // INSERT
  if (nb_mot_requete == 1) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
    return;
  }
  // INSERT INTO
  if (nb_mot_requete == 2) {
    printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom de table a remplir\n");
    return;
  }
  //INSERT INTO nom_table
  if (nb_mot_requete == 3) {
    insert_(phrase[2]);
    return;
  }
  //INSERT INTO nom_table [...]
  if (nb_mot_requete > 3) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
    return;
  }
}
//
//  Detection du INSERT finie
//

//
//  Detection du DELETE
//
if (compare_chaines(phrase[0], "DELETE") == 1 || compare_chaines(phrase[0], "delete") == 1) {
  // DELETE
  if (nb_mot_requete == 1) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
  }
  // DELETE FROM
  if (nb_mot_requete == 2) {
    printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom de table\n");
  }
  // DELETE FROM nom_table
  if (nb_mot_requete == 3) {
    printf("\033[0;31mDecibel\t~ Entrer une condition \033[1;31mWHERE\n");
  }
  // DELETE FROM nom_table WHERE
  if (nb_mot_requete == 4) {
    printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom d'attribut\n");
  }
  // DELETE FROM nom_table WHERE nom_attribut
  // DELETE FROM nom_table WHERE nom_attribut =
  // DELETE FROM nom_table WHERE nom_attribut = valeur_testee [...]
  if (nb_mot_requete == 5 || nb_mot_requete == 6 || nb_mot_requete > 7) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
  }
  if (nb_mot_requete == 7) {
    delete_(phrase[2], phrase[4], phrase[6]);
  }
}
//
//  Detection du DELETE finie
//


//
// Detection des DROP
//
if ( compare_chaines(phrase[0], "DROP") == 1 || compare_chaines(phrase[0], "drop") == 1) {
  // DROP
  if (nb_mot_requete == 1) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
  }

  // DROP TABLE
  if (compare_chaines(phrase[1], "TABLE") == 1 || compare_chaines(phrase[1], "table")== 1) {

    if (nb_mot_requete > 3) {
      printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
    }
    if (nb_mot_requete == 2) {
      printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom de table a supprimer\n");
    }
    if (nb_mot_requete == 3) {
      drop_table_(phrase[2]);
    }
  }
  //DROP ATTRIBUTE
  if (compare_chaines(phrase[1], "ATTRIBUTE") == 1 || compare_chaines(phrase[1], "attribute")== 1) {
    // DROP nom_attribut
    if (nb_mot_requete == 2) {
      printf("\033[0;31mDecibel\t~ Entrer le \033[1;31mnom de l'attribut\n");
    }
    if (nb_mot_requete == 3 || nb_mot_requete == 4) {
      printf("\033[0;31mDecibel\t~ Entrer le \033[1;31mnom de la table cible\n");
    }
    if (nb_mot_requete > 5) {
      printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
    }
    if (nb_mot_requete == 5) {
      drop_attribute_(phrase[4], phrase[2]);
    }
  }
  //
  //  Detection du DROP finie
  //
}

//
// Detection du CLEAR
//
if ( (compare_chaines(phrase[0], "CLEAR") == 1) || (compare_chaines(phrase[0], "clear") == 1) ) {
  // AIDE
  system("clear");
}

//
// Detection du HELP --- ATTENTION : LAISSER CETTE VERIFICATION EN FIN DE FONCTION()
//
if ( (compare_chaines(phrase[0], "HELP") == 1) || (compare_chaines(phrase[0], "help") == 1) || (compare_chaines(phrase[0], "???") == 1) ) {
  // AIDE
  printf("\033[0;31m");
  afficheAide();

}
//
// Detection des DROP finie
//


//
// Detection du UPDATE
//
if (compare_chaines(phrase[0], "UPDATE") == 1 || compare_chaines(phrase[0], "update") == 1) {
  // UPDATE
  if (nb_mot_requete == 1) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
  }
  // UPDATE FROM
  if (nb_mot_requete == 2) {
    printf("\033[0;31mDecibel\t~ Entrer un nom de table\n");
  }
  // UPDATE FROM nom_table
  if (nb_mot_requete == 3) {
    printf("\033[0;31mDecibel\t~ Entrer une \033[1;31mcondition WHERE\n");
  }
  // UPDATE FROM nom_table WHERE
  if (nb_mot_requete == 4) {
    printf("\033[0;31mDecibel\t~ Entrer un \033[1;31mnom d'attribut\n");
  }
  // UPDATE FROM nom_table WHERE nom_attribut
  // UPDATE FROM nom_table WHERE nom_attribut =
  // UPDATE FROM nom_table WHERE nom_attribut = valeur_testee [...]
  if (nb_mot_requete == 5 || nb_mot_requete == 6 || nb_mot_requete > 7) {
    printf("\033[0;31mDecibel\t~ Entrer une requete valide\n");
  }
  if (nb_mot_requete == 7) {
    update_(phrase[2], phrase[4], phrase[6]);
  }
}
//
// Detection du UPDATE finie
//
}



int main (void) {
  char requete[TAILLE];
  clock_t start, end;
  double cpu_time_used;

  quit = false;
  system("clear");

  while (quit != true) {
	do{
		  //Entree utilisateur
		  printf("\033[1;35mDecibel\t~ \033[0;36m Entrer une requete (help : '???')\n");
		  printf("\033[0;32m\t>\033[0;30m ");
		scanf("%[^\n]%*c", requete);
	}while( strlen(requete) < 2);
	//DEBUT CLOCK
	start = clock();

	fonction(requete);

	//FIN CLOCK + AFFICHAGE
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\033[0;30mrequete effectuee en %f secondes.\n", cpu_time_used);
  }

  return 0;
}
