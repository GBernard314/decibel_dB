#define TAILLE 100
#define true 1
#define false 0
#define BUFF_SIZE 1024
// char phrase[TAILLE/2][TAILLE]
int compare_chaines(char * a, char * b);
int num_ligne(char *chemin_fichier, char *argument_a_trouver);
int nombre_fichier(char *nom_dossier);
int nombre_lignes(char *nom_fichier);
char * chemin_acces(char *nom_dossier, char *nom_fichier);

char * executeCmd(char * cmd);
int split_entry( char* raw_input, char (*phrase)[TAILLE]);


void create_(char *nom_table, int nb_attribut, char (*phrase)[TAILLE]);
void add_(char * nom_attribut, char * nom_table);
int select_all(char * nom_dossier);
void select_(char (*phrase)[TAILLE], int nb_mot_requete);
void insert_(char * nom_database);
void delete_(char * nom_dossier, char * nom_attribut, char * valeur_testee);
void update_(char * nom_dossier, char * nom_attribut, char * valeur_testee);
void drop_table_(char * nom_table);
void drop_attribute_(char * nom_table, char * nom_attribut);


void afficheTables(char (*tables)[][TAILLE], char (*nom_cols)[TAILLE], int nb_objet,int nb_col);
void afficheQuery(char (*query)[TAILLE], int nb_term);
void afficheAide(void);
