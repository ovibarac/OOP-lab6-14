//
// Created by ovi on 6/2/22.
//

#ifndef QTLAB10_COSGUI_H
#define QTLAB10_COSGUI_H
#include "FilmService.h"
#include "Observer.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QHeaderView>
#include <QMessageBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>


class CosCRUDGUI : public QWidget, Observer{
private:
    FilmService& srv;
    QListWidget* qlistCos;

    QHBoxLayout* lyMainCos;
    QPushButton* btnAddCos;
    QPushButton* btnEmptyCos;
    QPushButton* btnGenCos;
    QPushButton* btnExportCos;
    QLineEdit* editTitluCos;
    QLineEdit* editGenerate;
    QLineEdit* editExport;

    void reloadCos(vector<Film> filme);

    void initialize();

    void connectSignalsSlots();
public:
    CosCRUDGUI(FilmService& s): srv{s}{
        initialize();
        connectSignalsSlots();
    }

    void update()override{
        reloadCos(srv.allCos());
    }

    ~CosCRUDGUI(){
        srv.removeObserver(this);
    }
};

class CosReadOnlyGUI : public QWidget, Observer{

};


#endif //QTLAB10_COSGUI_H
