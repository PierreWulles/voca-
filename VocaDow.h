#ifndef VOCADOW_H
#define VOCADOW_H

#include <QtWidgets>
#include <QPushButton>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QProgressBar>
#include <QCheckBox>

#include "VocaHelp.h"
#include "VocaCrea.h"

class VocaDow : public QWidget
{
    Q_OBJECT

public:
    VocaDow();

public slots:
    void ouvrirFichier();
    void ouvrirAide();
    void vocaliser();
    void ouvrirCrea();
    void gestionErreur();
    void initListe();
    void ouvrirListe();

private:
    QProgressBar *m_progression;
    QPushButton *m_vocaliser;
    QPushButton *m_ouvrir_fichier;
    QPushButton *m_help;
    QPushButton *m_charger_erreur;
    QPushButton *m_creation_liste;
    QStringList *m_liste_texte;
    QGridLayout *m_Gbox;
    QTextStream *m_flux_tr;
    QTextStream *m_flux_fr;
    QCheckBox *m_case;
    QCheckBox *m_inversion;
    QComboBox *m_liste_bouton;
    QLineEdit *m_champ;
    VocaHelp *m_aide;
    VocaCrea *m_creation;
    QString *m_emplacement;
    QString *m_mot_fr;
    QString *m_mot_tr;
    QString *m_test;
    QString *m_text;
    QString *m_tmp;
    QVector <int> m_verif_alea;
    QLabel *m_question;
    QFile *m_liste_fr;
    QFile *m_liste_tr;
    QFile *m_erreur_fr;
    QFile *m_erreur_tr;
    bool m_lock;
    bool m_tirage;
    int m_hasard;
    int m_faux;
    int m_taux;
    int i;
    int p;
    int r;
    int o;
};

#endif // VOCADOW_H
