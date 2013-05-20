#include "VocaHelp.h"

VocaHelp::VocaHelp() : QDialog()
{
    setFixedSize(470, 500);
    setWindowTitle("Aide");

    m_onglets = new QTabWidget(this);
    m_onglets->setGeometry(10, 10, 450, 480);

    //AIDE

    m_aide = new QWidget;

    m_texte_aide = new QString;

    m_aide_xml = new QFile("Aide.xml");

    if (m_aide_xml->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        *m_texte_aide = m_aide_xml->readAll();
        m_aide_xml->close();
    }
    else
    {
        *m_texte_aide = "Fichier xml manquant !";
    }

    m_zone_aide = new QTextEdit;
    m_zone_aide->setText(*m_texte_aide);
    m_zone_aide->setReadOnly(true);

    m_Vbox = new QVBoxLayout;
    m_Vbox->addWidget(m_zone_aide, 0);

    m_aide->setLayout(m_Vbox);

    //CREDITS

    m_credits = new QWidget;

    m_texte_credits = new QString;

    m_credits_xml = new QFile("Credits.xml");

    if (m_credits_xml->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        *m_texte_credits = m_credits_xml->readAll();
        m_credits_xml->close();
    }
    else
    {
        *m_texte_credits = "Fichier xml manquant !";
    }

    m_zone_credits = new QTextEdit;
    m_zone_credits->setText(*m_texte_credits);
    m_zone_credits->setReadOnly(true);

    m_Vbox2 = new QVBoxLayout;
    m_Vbox2->addWidget(m_zone_credits, 0);

    m_credits->setLayout(m_Vbox2);

    m_onglets->addTab(m_aide, "Aide");
    m_onglets->addTab(m_credits, "Crédits");
}
