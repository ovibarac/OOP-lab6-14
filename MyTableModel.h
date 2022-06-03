#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include "Film.h"
#include <vector>
#include <qdebug.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Film> filme;
public:
	MyTableModel(const std::vector<Film>& filme) :filme{ filme } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return filme.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
//		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		//qDebug() << index.data(role);

		if (role == Qt::DisplayRole) {

			Film p = filme[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getTitlu());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.getGen());
			}
			else if (index.column() == 2) {
                return QString::number(p.getAn());
			}
			else if (index.column() == 3) {
                return QString::fromStdString(p.getActor());
			}
		}

		return QVariant{};
	}

	void setFilme(const vector<Film> filme) {
		this->filme = filme;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}


	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return tr("Titlu");
				case 1:
					return tr("Gen");
				case 2:
					return tr("An");
				case 3:
					return tr("Actor");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};
