#include "VocaDow.h"

VocaDow::VocaDow() : QWidget()
{
    setWindowTitle("Voca+ v2.0b");
    setWindowIcon(QIcon("icone.png"));
    resize(600, 150);

    i = 0;
    r = 0;
    p = 0;
    o = 0;
    m_faux = 0;
    m_taux = 0;

    m_lock = false;

    m_tirage = true;

    m_vocaliser = new QPushButton(this);
    m_vocaliser->setIcon(QIcon("engrenage.png"));
    m_vocaliser->setShortcut(QKeySequence(Qt::Key_Return));
    m_vocaliser->setToolTip("Vérification (entrée)");

    m_help = new QPushButton("Aide",this);
    m_help->setToolTip("Affiche l'aide (F1)");
    m_help->setShortcut(QKeySequence(Qt::Key_F1));

    m_ouvrir_fichier = new QPushButton("Charger une liste exterieure", this);
    m_ouvrir_fichier->setToolTip("Cliquez ici pour charger une liste de vocabulaire au format liste.txt située sur le disque dur");

    m_charger_erreur = new QPushButton("Charger erreurs", this);
    m_charger_erreur->setToolTip("Charge le fichier erreur.txt contenant les erreurs");

    m_creation_liste = new QPushButton("Créer une liste", this);
    m_creation_liste->setToolTip("Utiliser l'assistant de création de liste pour créer une liste de mot");

    m_champ = new QLineEdit("Entrez votre réponse ici:", this);
    m_champ->setToolTip("Tapez ici le mot traduit puis appuyez sur entrée");

    m_question = new QLabel(this);

    m_progression = new QProgressBar;
    m_progression->setValue(0);
    m_progression->setToolTip("Progression dans la liste");

    m_emplacement = new QString;

    m_liste_texte = new QStringList;

    m_tmp = new QString;

    m_liste_bouton = new QComboBox;
    initListe();
    m_liste_bouton->setToolTip("Charger une liste prédéfinie");
    m_liste_bouton->addItem("Charger une liste prédéfinie", 0);
    m_liste_bouton->addItems(*m_liste_texte);

    m_case = new QCheckBox("Aléatoire", this);
    m_case->setToolTip("Charge les mots de façon aléatoire");

    m_inversion = new QCheckBox("Inverser", this);
    m_inversion->setToolTip("Demande les mots en français");

    m_Gbox = new QGridLayout(this);
    m_Gbox->addWidget(m_liste_bouton, 0, 0, 2, 1);
    m_Gbox->addWidget(m_ouvrir_fichier, 0, 1, 2, 1);
    m_Gbox->addWidget(m_charger_erreur, 0, 2, 2, 1);
    m_Gbox->addWidget(m_creation_liste, 0, 3, 2, 1);
    m_Gbox->addWidget(m_help, 0, 4, 2, 1);
    m_Gbox->addWidget(m_case, 2, 0);
    m_Gbox->addWidget(m_inversion, 2, 1);
    m_Gbox->addWidget(m_question, 3, 0, 2, 2);
    m_Gbox->addWidget(m_champ, 6, 0, 2, 4);
    m_Gbox->addWidget(m_vocaliser, 6, 4, 2, 1);
    m_Gbox->addWidget(m_progression, 8, 0, 2, 5);

    QObject::connect(m_ouvrir_fichier, SIGNAL(clicked()), this, SLOT(ouvrirFichier()));
    QObject::connect(m_help, SIGNAL(clicked()), this, SLOT(ouvrirAide()));
    QObject::connect(m_vocaliser, SIGNAL(clicked()), this, SLOT(vocaliser()));
    QObject::connect(m_charger_erreur, SIGNAL(clicked()), this, SLOT(gestionErreur()));
    QObject::connect(m_liste_bouton, SIGNAL(currentTextChanged(QString)), this, SLOT(ouvrirListe()));
    QObject::connect(m_creation_liste, SIGNAL(clicked()), this, SLOT(ouvrirCrea()));
}

void VocaDow::ouvrirFichier()
{
    m_progression->setValue(0);

    if (m_lock == false)
    {
        *m_emplacement = QFileDialog::getOpenFileName(this, "Ouvrir une liste", QString(),"Liste (*.txt)");
    }

    m_liste_fr = new QFile(*m_emplacement);
    m_liste_tr = new QFile(*m_emplacement + "_tr.txt");

    m_flux_fr = new QTextStream(m_liste_fr);
    m_flux_tr = new QTextStream(m_liste_tr);

    if (*m_emplacement == "Charger une liste prédéfinie")
    {
        m_lock = false;
    }
    else if (m_emplacement->isEmpty() || !m_liste_tr->open(QIODevice::ReadOnly) || !m_liste_fr->open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "ERREUR", "Le fichier n'a pas pu être chargé");
        *m_emplacement = "";
        m_lock = false;
    }
    else
    {
        QMessageBox::information(this, "Chargement", "Le fichier <strong>" + *m_emplacement + "</strong> a été chargé");


        m_mot_fr = new QString;
        m_mot_tr = new QString;

        i = 0;

        while(!m_flux_fr->atEnd())
        {
            *m_mot_fr = m_flux_fr->readLine();
            i++;
        }

        qsrand(QTime::currentTime().msec());
        m_hasard =(qrand() % (i)) + 1;

        //QMessageBox::warning(this, "nbr ligne", QString::number(m_hasard));//DEBUG

        m_flux_fr->seek(0);
        *m_mot_fr = "";

        if (m_case->isChecked())
        {
            for (int v = 0; v < m_hasard; ++v)
            {
                *m_mot_tr = "";
                *m_mot_fr = "";
                *m_mot_tr += m_flux_tr->readLine();
                *m_mot_fr += m_flux_fr->readLine();
            }
            m_verif_alea.push_back(m_hasard);
            m_flux_tr->seek(0);
            m_flux_fr->seek(0);
        }

        else
        {
            *m_mot_tr += m_flux_tr->readLine();
            *m_mot_fr += m_flux_fr->readLine();
        }

        r = 0;
        p = 0;
        o = 0;
        m_faux = 0;
        m_taux = 0;

        if (!m_inversion->isChecked())
        {
            m_question->setText("Comment dit-on <strong>" + *m_mot_fr + "</strong> en anglais ?");
        }

        else if (m_inversion->isChecked())
        {
            m_question->setText("Comment dit-on <strong>" + *m_mot_tr + "</strong> en français ?");
        }
        m_lock = true;

    }

    m_champ->setText("");
}

void VocaDow::vocaliser()
{
    if (m_lock)
    {
        m_test = new QString(m_champ->text());
        if (*m_test == *m_mot_tr || *m_test == *m_mot_fr)
        {
            //QMessageBox::information(this, "Correct", "Correct !");
        }
        else
        {
            if (!m_inversion->isChecked())
            {
                QMessageBox::critical(this, "Faux", "Faux ! <strong>" + *m_mot_fr + "</strong> se dit <strong>" + *m_mot_tr + "</strong>.");
            }
            else if (m_inversion->isChecked())
            {
                QMessageBox::critical(this, "Faux", "Faux ! <strong>" + *m_mot_tr + "</strong> se dit <strong>" + *m_mot_fr + "</strong>.");
            }

            m_erreur_fr = new QFile("erreur.txt");
            m_erreur_tr = new QFile("erreur.txt_tr.txt");

            if (m_erreur_fr->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
            {
                if (m_erreur_tr->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
                {
                        QTextStream flux_erreur_tr(m_erreur_tr);
                        flux_erreur_tr << *m_mot_tr << '\n';

                        if (*m_emplacement == "erreur.txt")
                        {
                            i++;
                        }
                }
                QTextStream flux_erreur_fr(m_erreur_fr);
                flux_erreur_fr << *m_mot_fr << '\n';
            }

            else
            {
                QMessageBox::information(this, "Erreur 257", "Erreur 257");
            }

            m_faux++;
        }

        m_mot_tr->clear();
        m_mot_fr->clear();

        m_champ->setText("");

        if (m_flux_fr->atEnd() || o == i-1)
        {
            m_taux = m_faux*100;
            m_taux /= i;
            m_question->setText("Fin de liste: <strong>" + QString::number(m_faux) + " erreur(s) !</strong> (" + QString::number(m_taux) + " %)");
            if (*m_emplacement == "erreur.txt")
            {
                m_liste_fr->remove();
                m_liste_tr->remove();
            }
            m_lock = false;
        }
        else
        {
            while (m_tirage)
            {
                m_hasard =(qrand() % (i)) + 1;
                m_tirage = false;
                for (int l = 0; l < m_verif_alea.size(); ++l)
                {
                    if(m_verif_alea[l] == m_hasard)
                    {
                            m_tirage = true;
                    }
                }
            }

            m_tirage = true;


            //QMessageBox::warning(this, "nbr ligne", QString::number(m_hasard));//DEBUG

            if (m_case->isChecked())
            {
                for (int v = 0; v < m_hasard; ++v)
                {
                    *m_mot_tr = "";
                    *m_mot_fr = "";
                    *m_mot_tr += m_flux_tr->readLine();
                    *m_mot_fr += m_flux_fr->readLine();
                }
                m_flux_tr->seek(0);
                m_flux_fr->seek(0);
                m_verif_alea.push_back(m_hasard);
                ++o;
            }

            else
            {
                *m_mot_tr += m_flux_tr->readLine();
                *m_mot_fr += m_flux_fr->readLine();
                m_verif_alea.push_back(p+1);
                ++o;
            }

            if (!m_inversion->isChecked())
            {
                m_question->setText("Comment dit-on <strong>" + *m_mot_fr + "</strong> en anglais ?");
            }

            else if (m_inversion->isChecked())
            {
                m_question->setText("Comment dit-on <strong>" + *m_mot_tr + "</strong> en français ?");
            }

        }

        p++;

        r = p*100;
        r /= i;

        m_progression->setValue(r);
    }
    else
    {
        QMessageBox::warning(this, "Pas de liste", "Vous n'avez pas chargé de liste, impossible de continuer.");
    }
}

void VocaDow::gestionErreur()
{
    *m_emplacement = "erreur.txt";
    m_lock = true;
    ouvrirFichier();
}

void VocaDow::initListe()
{
    QFile liste("liste.txt");
    QTextStream flux(&liste);
    if (liste.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!flux.atEnd())
        {
            *m_tmp = flux.readLine();
            *m_liste_texte << *m_tmp;
        }
    }
}

void VocaDow::ouvrirAide()
{
    m_aide = new VocaHelp;
    m_aide->exec();
}

void VocaDow::ouvrirListe()
{
    *m_emplacement = m_liste_bouton->currentText();
    m_lock = true;
    m_champ->clear();
    m_question->clear();
    ouvrirFichier();
}

void VocaDow::ouvrirCrea()
{
    m_creation = new VocaCrea;
    m_creation->show();
}
