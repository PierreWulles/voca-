#ifndef VOCACREA_H
#define VOCACREA_H

#include <QDialog>
#include <QTableWidget>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
#include <QPushButton>

class VocaCrea : public QWidget
{
    Q_OBJECT

public:
    VocaCrea();

public slots:
    void ajouter();

private:
    QGridLayout *m_CGbox;
    QPushButton *m_ajouter;
    QLineEdit *m_champ_fr;
    QLineEdit *m_champ_tr;
    QString *m_titre_liste;
    QLabel *m_titre_q;
    QLabel *m_titre_l;
    QLabel *m_fr;
    QLabel *m_tr;
    QFile *m_liste_fr;
    QFile *m_liste_tr;
    QFile *m_liste_liste;
};

#endif // VOCACREA_H
