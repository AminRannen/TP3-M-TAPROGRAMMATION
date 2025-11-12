#include <stdio.h>
#include <stdlib.h>

typedef enum { FAUX = 0, VRAI = 1 } bool;
typedef enum OG_t {CERCLE=0, RECTANGLE=1, OG=2} OG_t;
#define NBCLASSES 3

// Forward declarations
struct ObjetGraphique;
struct MetaObjetGraphique;
struct Cercle;
struct MetaCercle;
struct Rectangle;
struct MetaRectangle;

// Structure ObjetGraphique
typedef struct ObjetGraphique {
    struct MetaObjetGraphique* myClass;
    int x;
    int y;
    OG_t type;  // Pour le polymorphisme
} ObjetGraphique;

typedef struct MetaObjetGraphique {
    void (*setX)(int, struct ObjetGraphique*);
    void (*setY)(int, struct ObjetGraphique*);
    int (*getX)(struct ObjetGraphique*);
    int (*getY)(struct ObjetGraphique*);
    
    void (*TVMeffacer[NBCLASSES])(struct ObjetGraphique*);
    void (*TVMafficher[NBCLASSES])(struct ObjetGraphique*);
    void (*TVMdeplacer[NBCLASSES])(struct ObjetGraphique*);
    int (*TVMgetCentreX[NBCLASSES])(struct ObjetGraphique*);
    int (*TVMgetCentreY[NBCLASSES])(struct ObjetGraphique*);
    
    void (*effacer)(struct ObjetGraphique*);
    void (*afficher)(struct ObjetGraphique*);
    void (*deplacer)(struct ObjetGraphique*);
    int (*getCentreX)(struct ObjetGraphique*);
    int (*getCentreY)(struct ObjetGraphique*);
    
    int NbObjetGraphique;
    
    int (*GetNbObjetGraphique)(void);
    
    void (*ConstructeurObjetGraphique)(struct ObjetGraphique*);
} MetaObjetGraphique;

typedef struct Cercle {
    ObjetGraphique superClasse;
    struct MetaCercle* myClass;
    int rayon;
} Cercle;

typedef struct MetaCercle {
    MetaObjetGraphique* superMetaClasse;
    
    void (*setRayon)(int, struct Cercle*);
    int (*getRayon)(struct Cercle*);
    
    void (*ConstructeurCercle)(struct Cercle*);
} MetaCercle;

typedef struct Rectangle {
    ObjetGraphique superClasse;
    struct MetaRectangle* myClass;
    int largeur;
    int hauteur;
} Rectangle;

typedef struct MetaRectangle {
    MetaObjetGraphique* superMetaClasse;
    
    void (*setLargeur)(int, struct Rectangle*);
    void (*setHauteur)(int, struct Rectangle*);
    int (*getLargeur)(struct Rectangle*);
    int (*getHauteur)(struct Rectangle*);
    
    void (*ConstructeurRectangle)(struct Rectangle*);
} MetaRectangle;

MetaObjetGraphique LeMetaObjetGraphique;
MetaCercle LeMetaCercle;
MetaRectangle LeMetaRectangle;

// ============================================================================
// IMPLÉMENTATION DES MÉTHODES DE OBJETGRAPHIQUE
// ============================================================================

int getX(ObjetGraphique* this) {
    return this->x;
}

void setX(int inX, ObjetGraphique* this) {
    this->x = inX;
}

int getY(ObjetGraphique* this) {
    return this->y;
}

void setY(int inY, ObjetGraphique* this) {
    this->y = inY;
}

int GetNbObjetGraphique(void) {
    return LeMetaObjetGraphique.NbObjetGraphique;
}

void ConstruireObjetGraphique(ObjetGraphique* this) {
    printf("ObjetGraphique::Constructeur\n");
    this->myClass = &LeMetaObjetGraphique;
    this->x = 0;
    this->y = 0;
    this->type = OG;  // Type par défaut
    LeMetaObjetGraphique.NbObjetGraphique++;
    printf("NbObjetGraphique = %d\n", LeMetaObjetGraphique.NbObjetGraphique);
}

// ============================================================================
// IMPLÉMENTATION DES MÉTHODES POLYMORPHIQUES
// ============================================================================

void afficherCercle(ObjetGraphique* this) {
    Cercle* thisCercle = (Cercle*) this;  // Cast
    printf("📘 Cercle: centre=(%d,%d), rayon=%d\n", 
           this->x, this->y, thisCercle->rayon);
}

void effacerCercle(ObjetGraphique* this) {
    printf("🧹 Effacement du cercle en (%d,%d)\n", this->x, this->y);
}

void deplacerCercle(ObjetGraphique* this) {
    printf("➡️  Déplacement du cercle de (%d,%d) vers (%d,%d)\n", 
           this->x, this->y, this->x + 1, this->y + 1);
    this->x++;
    this->y++;
}

int getCentreXCercle(ObjetGraphique* this) {
    return this->x; 
}

int getCentreYCercle(ObjetGraphique* this) {
    return this->y;
}

void afficherRectangle(ObjetGraphique* this) {
    Rectangle* thisRect = (Rectangle*) this;  // Cast
    printf("📗 Rectangle: coin=(%d,%d), taille=%dx%d\n", 
           this->x, this->y, thisRect->largeur, thisRect->hauteur);
}

void effacerRectangle(ObjetGraphique* this) {
    printf("🧹 Effacement du rectangle en (%d,%d)\n", this->x, this->y);
}

void deplacerRectangle(ObjetGraphique* this) {
    printf("➡️  Déplacement du rectangle de (%d,%d) vers (%d,%d)\n", 
           this->x, this->y, this->x + 2, this->y + 2);
    this->x += 2;
    this->y += 2;
}

int getCentreXRectangle(ObjetGraphique* this) {
    Rectangle* thisRect = (Rectangle*) this;
    return this->x + thisRect->largeur / 2;  
}

int getCentreYRectangle(ObjetGraphique* this) {
    Rectangle* thisRect = (Rectangle*) this;
    return this->y + thisRect->hauteur / 2;  
}

void afficherOG(ObjetGraphique* this) {
    printf("📓 ObjetGraphique: position=(%d,%d)\n", this->x, this->y);
}

void effacerOG(ObjetGraphique* this) {
    printf("🧹 Effacement de l'objet graphique en (%d,%d)\n", this->x, this->y);
}

void deplacerOG(ObjetGraphique* this) {
    printf("➡️  Déplacement de l'objet graphique de (%d,%d) vers (%d,%d)\n", 
           this->x, this->y, this->x + 5, this->y + 5);
    this->x += 5;
    this->y += 5;
}

int getCentreXOG(ObjetGraphique* this) {
    return this->x;  
}

int getCentreYOG(ObjetGraphique* this) {
    return this->y;
}

void afficher(ObjetGraphique* this) {
    LeMetaObjetGraphique.TVMafficher[this->type](this);
}

void effacer(ObjetGraphique* this) {
    LeMetaObjetGraphique.TVMeffacer[this->type](this);
}

void deplacer(ObjetGraphique* this) {
    LeMetaObjetGraphique.TVMdeplacer[this->type](this);
}

int getCentreX(ObjetGraphique* this) {
    return LeMetaObjetGraphique.TVMgetCentreX[this->type](this);
}

int getCentreY(ObjetGraphique* this) {
    return LeMetaObjetGraphique.TVMgetCentreY[this->type](this);
}

// ============================================================================
// IMPLÉMENTATION DES MÉTHODES DE CERCLE
// ============================================================================

void setRayonCercle(int inRayon, Cercle* this) {
    this->rayon = inRayon;
}

int getRayonCercle(Cercle* this) {
    return this->rayon;
}

void ConstruireCercle(Cercle* this) {
    printf("Cercle::ConstruireCercle\n");
    this->myClass = &LeMetaCercle;
    
   
    this->myClass->superMetaClasse->ConstructeurObjetGraphique(&this->superClasse);
    this->superClasse.type = CERCLE;  
    
    printf("Construction partie propre au Cercle\n");
    this->rayon = 1;  
    
    printf("Cercle::ConstruireCercle effectué\n");
}

// ============================================================================
// IMPLÉMENTATION DES MÉTHODES DE RECTANGLE
// ============================================================================

void setLargeurRectangle(int inLargeur, Rectangle* this) {
    this->largeur = inLargeur;
}

void setHauteurRectangle(int inHauteur, Rectangle* this) {
    this->hauteur = inHauteur;
}

int getLargeurRectangle(Rectangle* this) {
    return this->largeur;
}

int getHauteurRectangle(Rectangle* this) {
    return this->hauteur;
}

void ConstruireRectangle(Rectangle* this) {
    printf("Rectangle::ConstruireRectangle\n");
    this->myClass = &LeMetaRectangle;
    
    this->myClass->superMetaClasse->ConstructeurObjetGraphique(&this->superClasse);
    this->superClasse.type = RECTANGLE;  
    
    printf("Construction partie propre au Rectangle\n");
    this->largeur = 2; 
    this->hauteur = 1;  
    
    printf("Rectangle::ConstruireRectangle effectué\n");
}

// ============================================================================
// INITIALISATION DES MÉTA-CLASSES
// ============================================================================

void initMetaObjetGraphique(void) {
    LeMetaObjetGraphique.setX = setX;
    LeMetaObjetGraphique.setY = setY;
    LeMetaObjetGraphique.getX = getX;
    LeMetaObjetGraphique.getY = getY;
    
    LeMetaObjetGraphique.TVMeffacer[CERCLE] = effacerCercle;
    LeMetaObjetGraphique.TVMeffacer[RECTANGLE] = effacerRectangle;
    LeMetaObjetGraphique.TVMeffacer[OG] = effacerOG;
    
    LeMetaObjetGraphique.TVMafficher[CERCLE] = afficherCercle;
    LeMetaObjetGraphique.TVMafficher[RECTANGLE] = afficherRectangle;
    LeMetaObjetGraphique.TVMafficher[OG] = afficherOG;
    
    LeMetaObjetGraphique.TVMdeplacer[CERCLE] = deplacerCercle;
    LeMetaObjetGraphique.TVMdeplacer[RECTANGLE] = deplacerRectangle;
    LeMetaObjetGraphique.TVMdeplacer[OG] = deplacerOG;
    
    LeMetaObjetGraphique.TVMgetCentreX[CERCLE] = getCentreXCercle;
    LeMetaObjetGraphique.TVMgetCentreX[RECTANGLE] = getCentreXRectangle;
    LeMetaObjetGraphique.TVMgetCentreX[OG] = getCentreXOG;
    
    LeMetaObjetGraphique.TVMgetCentreY[CERCLE] = getCentreYCercle;
    LeMetaObjetGraphique.TVMgetCentreY[RECTANGLE] = getCentreYRectangle;
    LeMetaObjetGraphique.TVMgetCentreY[OG] = getCentreYOG;
    
    LeMetaObjetGraphique.effacer = effacer;
    LeMetaObjetGraphique.afficher = afficher;
    LeMetaObjetGraphique.deplacer = deplacer;
    LeMetaObjetGraphique.getCentreX = getCentreX;
    LeMetaObjetGraphique.getCentreY = getCentreY;
    
    LeMetaObjetGraphique.GetNbObjetGraphique = GetNbObjetGraphique;
    LeMetaObjetGraphique.ConstructeurObjetGraphique = ConstruireObjetGraphique;
    LeMetaObjetGraphique.NbObjetGraphique = 0;
}

void initMetaCercle(void) {
    LeMetaCercle.superMetaClasse = &LeMetaObjetGraphique;
    LeMetaCercle.setRayon = setRayonCercle;
    LeMetaCercle.getRayon = getRayonCercle;
    LeMetaCercle.ConstructeurCercle = ConstruireCercle;
}

void initMetaRectangle(void) {
    LeMetaRectangle.superMetaClasse = &LeMetaObjetGraphique;
    LeMetaRectangle.setLargeur = setLargeurRectangle;
    LeMetaRectangle.setHauteur = setHauteurRectangle;
    LeMetaRectangle.getLargeur = getLargeurRectangle;
    LeMetaRectangle.getHauteur = getHauteurRectangle;
    LeMetaRectangle.ConstructeurRectangle = ConstruireRectangle;
}

// ============================================================================
// PROGRAMMES DE TEST
// ============================================================================

int main_encapsulation() {
    printf("=== TEST ENCAPSULATION ===\n");
    
    initMetaObjetGraphique();
    
    ObjetGraphique obj1, obj2;
    
    printf("\n1. Construction des objets:\n");
    LeMetaObjetGraphique.ConstructeurObjetGraphique(&obj1);
    LeMetaObjetGraphique.ConstructeurObjetGraphique(&obj2);
    
    printf("\n2. Test des accesseurs/mutateurs:\n");
    obj1.myClass->setX(10, &obj1);
    obj1.myClass->setY(20, &obj1);
    
    obj2.myClass->setX(30, &obj2);
    obj2.myClass->setY(40, &obj2);
    
    printf("Obj1: x=%d, y=%d\n", obj1.myClass->getX(&obj1), obj1.myClass->getY(&obj1));
    printf("Obj2: x=%d, y=%d\n", obj2.myClass->getX(&obj2), obj2.myClass->getY(&obj2));
    
    printf("\n3. Test méthode de classe:\n");
    printf("Nombre total d'objets graphiques: %d\n", 
           LeMetaObjetGraphique.GetNbObjetGraphique());
    
    return 0;
}

int main_heritage() {
    printf("\n=== TEST HERITAGE ===\n");
    
    initMetaObjetGraphique();
    initMetaCercle();
    initMetaRectangle();
    
    printf("\n1. Test avec Cercle:\n");
    Cercle monCercle;
    LeMetaCercle.ConstructeurCercle(&monCercle);
    
    monCercle.myClass->setRayon(5, &monCercle);
    monCercle.superClasse.myClass->setX(10, &monCercle.superClasse);
    monCercle.superClasse.myClass->setY(15, &monCercle.superClasse);
    
    printf("Cercle: x=%d, y=%d, rayon=%d\n",
           monCercle.superClasse.myClass->getX(&monCercle.superClasse),
           monCercle.superClasse.myClass->getY(&monCercle.superClasse),
           monCercle.myClass->getRayon(&monCercle));
    
    printf("\n2. Test avec Rectangle:\n");
    Rectangle monRectangle;
    LeMetaRectangle.ConstructeurRectangle(&monRectangle);
    
    monRectangle.myClass->setLargeur(8, &monRectangle);
    monRectangle.myClass->setHauteur(6, &monRectangle);
    monRectangle.superClasse.myClass->setX(20, &monRectangle.superClasse);
    monRectangle.superClasse.myClass->setY(25, &monRectangle.superClasse);
    
    printf("Rectangle: x=%d, y=%d, largeur=%d, hauteur=%d\n",
           monRectangle.superClasse.myClass->getX(&monRectangle.superClasse),
           monRectangle.superClasse.myClass->getY(&monRectangle.superClasse),
           monRectangle.myClass->getLargeur(&monRectangle),
           monRectangle.myClass->getHauteur(&monRectangle));
    
    printf("\n3. Nombre total d'objets graphiques: %d\n",
           LeMetaObjetGraphique.GetNbObjetGraphique());
    
    return 0;
}

int main_polymorphisme() {
    printf("\n=== TEST POLYMORPHISME ===\n");
    
    initMetaObjetGraphique();
    initMetaCercle();
    initMetaRectangle();
    
    ObjetGraphique objBase;
    Cercle monCercle;
    Rectangle monRectangle;
    
    LeMetaObjetGraphique.ConstructeurObjetGraphique(&objBase);
    LeMetaCercle.ConstructeurCercle(&monCercle);
    LeMetaRectangle.ConstructeurRectangle(&monRectangle);
    
    monCercle.superClasse.myClass->setX(10, &monCercle.superClasse);
    monCercle.superClasse.myClass->setY(10, &monCercle.superClasse);
    monCercle.myClass->setRayon(3, &monCercle);
    
    monRectangle.superClasse.myClass->setX(20, &monRectangle.superClasse);
    monRectangle.superClasse.myClass->setY(20, &monRectangle.superClasse);
    monRectangle.myClass->setLargeur(4, &monRectangle);
    monRectangle.myClass->setHauteur(6, &monRectangle);
    
    ObjetGraphique* objets[3];
    objets[0] = &objBase;
    objets[1] = (ObjetGraphique*)&monCercle;
    objets[2] = (ObjetGraphique*)&monRectangle;
    
    printf("\n1. Test d'affichage polymorphique:\n");
    for(int i = 0; i < 3; i++) {
        objets[i]->myClass->afficher(objets[i]);
    }
    
    printf("\n2. Test de déplacement polymorphique:\n");
    for(int i = 0; i < 3; i++) {
        objets[i]->myClass->deplacer(objets[i]);
    }
    
    printf("\n3. Test des centres polymorphiques:\n");
    for(int i = 0; i < 3; i++) {
        int centreX = objets[i]->myClass->getCentreX(objets[i]);
        int centreY = objets[i]->myClass->getCentreY(objets[i]);
        printf("Centre de l'objet %d: (%d,%d)\n", i, centreX, centreY);
    }
    
    printf("\n4. Test d'effacement polymorphique:\n");
    for(int i = 0; i < 3; i++) {
        objets[i]->myClass->effacer(objets[i]);
    }
    
    return 0;
}

int main() {
    printf("=== TP IMPLEMENTATION DES CONCEPTS OBJET EN C ===\n");
    
    main_encapsulation();
    main_heritage();
    main_polymorphisme();
    
    printf("\n=== FIN DU TP ===\n");
    return 0;
}