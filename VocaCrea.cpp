#include "VocaCrea.h"

VocaCrea::VocaCrea() : QWidget()
{
    setWindowTitle("Assistant de création de liste");
    setMinimumWidth(300);

    m_titre_liste = new QString;

    while (m_titre_liste->isEmpty())
    {
        *m_titre_liste = QInputDialog::getText(this, "Titre ?", "Quel titre aura votre liste ?", QLineEdit::Normal, ".txt");
    }

    m_liste_liste = new QFile("liste.txt");
    if (m_liste_liste->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QTextStream flux_liste(m_liste_liste);
        flux_liste << *m_titre_liste + '\n';
    }

    m_titre_q = new QLabel("Donnez le mot:", this);
    m_fr = new QLabel("En Français:");
    m_tr = new QLabel("Traduit:");

    m_champ_tr = new QLineEdit;
    m_champ_fr = new QLineEdit;

    m_ajouter = new QPushButton("Ajouter à la liste", this);
    m_ajouter->setShortcut(QKeySequence(Qt::Key_Return));

    m_CGbox = new QGridLayout(this);
    m_CGbox->addWidget(m_titre_q, 2, 0, 1, 1);
    m_CGbox->addWidget(m_fr, 3, 0);
    m_CGbox->addWidget(m_champ_fr, 4, 0);
    m_CGbox->addWidget(m_tr, 3, 1);
    m_CGbox->addWidget(m_champ_tr, 4, 1);
    m_CGbox->addWidget(m_ajouter, 5, 0, 1, 2);

    QObject::connect(m_ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
}

void VocaCrea::ajouter()
{
    m_liste_fr = new QFile(*m_titre_liste);
    m_liste_tr = new QFile(*m_titre_liste + "_tr.txt");

    if (m_liste_fr->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)
            && m_liste_tr->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QTextStream m_flux_fr(m_liste_fr);
        QTextStream m_flux_tr(m_liste_tr);

        m_flux_fr << m_champ_fr->text() + '\n';
        m_flux_tr << m_champ_tr->text() + '\n';

        m_champ_fr->clear();
        m_champ_tr->clear();
    }
    else
    {
        QMessageBox::critical(this, "ERREUR !", "Espace disque insuffisant ou permission d'écriture limitée");
    }
}
