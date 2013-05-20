#ifndef VOCAHELP_H
#define VOCAHELP_H

#include <QDialog>
#include <QTableWidget>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QTextEdit>

class VocaHelp : public QDialog
{

public:
    VocaHelp();

private:
    QVBoxLayout *m_Vbox;
    QVBoxLayout *m_Vbox2;
    QTabWidget *m_onglets;
    QTextEdit *m_zone_aide;
    QTextEdit *m_zone_credits;
    QWidget *m_aide;
    QWidget *m_credits;
    QString *m_texte_aide;
    QString *m_texte_credits;
    QFile *m_aide_xml;
    QFile *m_credits_xml;
};

#endif // VOCAHELP_H
