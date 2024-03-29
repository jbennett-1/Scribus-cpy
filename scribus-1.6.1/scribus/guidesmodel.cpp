/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#include <algorithm>
#include <QLocale>

#include "guidesmodel.h"
#include "units.h"


GuidesModel::GuidesModel(QObject * /*parent*/)
{
}

GuidesModel::~GuidesModel() = default;

int GuidesModel::rowCount(const QModelIndex & /*parent*/) const
{
	return m_values.count();
}

int GuidesModel::columnCount(const QModelIndex & /*parent*/) const
{
	// for future RFEs - color per guide etc.
	return 1;
}

QVariant GuidesModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();
	// DisplayRole and EditRole *must* be split. There is rounding
	// in pts2value(), toString() sequence. It disallows to compare
	// these values with m_data list.
	// Call it with EditRole when you need exact value.
	if (role == Qt::DisplayRole)
	{
		QLocale l;
		return QVariant(l.toString(pts2value(m_values.at(index.row()) - m_rule,
											  m_docUnitIndex), 'f',
											  m_docUnitDecimals)
						);
	}
	if (role == Qt::EditRole)
		return pts2value(m_values.at(index.row()) - m_rule, m_docUnitIndex);
	if (role == Qt::UserRole)
		return m_values.at(index.row());

	if (role == Qt::BackgroundRole && m_values.at(index.row()) == 0.0)
		return QVariant(QColor(Qt::red));
	return QVariant();
}

bool GuidesModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role != Qt::EditRole || !index.isValid())
		return false;
	bool ok;
	double newVal = value.toDouble(&ok);
	if (!ok)
		return false;
	m_values[index.row()] = value2pts(newVal, m_docUnitIndex) + m_rule;
	std::sort(m_values.begin(), m_values.end());
	emit dataChanged(index, index);
	emit valueChanged();
	return true;
}

Qt::ItemFlags GuidesModel::flags(const QModelIndex & /*index*/) const
{
	return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

QVariant GuidesModel::headerData(int /*section*/, Qt::Orientation orientation, int /*role*/) const
{
	if (orientation == Qt::Horizontal)
		return "Value";
	return "";
}

void GuidesModel::removeValues(const Guides & guides)
{
	beginResetModel();
	for (double d : guides)
		m_values.removeAll(d);
	endResetModel();
}

// bool GuidesModel::removeRows(int row, int count, const QModelIndex & parent)
// {
// 	if (count <= 0 || row < 0 || (row + count - 1) > m_values.count())
// 		return false;
// 
// 	beginRemoveRows(parent, row, row + count - 1);
// 	for (int i = 0; i < count; ++i)
// 		m_values.removeAt(row);
// 	endRemoveRows();
// 	return true;
// }

// bool GuidesModel::insertRows( int row, int count, const QModelIndex & parent)
// {
// 	beginInsertRows(parent, row, row + count - 1);
// 	for (int i = 0; i < count; ++i)
// 		m_values.insert(row + count, 0.0);
// 	endInsertRows();
// 	return true;
// }

void GuidesModel::insertRow()
{
// 	insertRows(rowCount(), 1);
	beginResetModel();
	if (m_values.contains(0.0))
		return;
	m_values.append(0.0);
	std::sort(m_values.begin(), m_values.end());
	endResetModel();
}

void GuidesModel::setValues(const Guides& values)
{
	beginResetModel();
	m_values = values;
	std::sort(m_values.begin(), m_values.end());
	endResetModel();
}

const Guides& GuidesModel::values() const
{
	return m_values;
}

void GuidesModel::unitChange(int docUnitIndex, int docUnitDecimals,double offset)
{
	beginResetModel();
	m_rule = offset;
	m_docUnitIndex = docUnitIndex;
	m_docUnitDecimals = docUnitDecimals;
	endResetModel();
}

#if 0
// debug
#include <QtDebug>
void GuidesModel::printValues()
{
	qDebug() << "GuidesModel dump start";
	for (int i = 0; i < m_values.count(); ++i)
		qDebug() << "GuidesModel dump: " << m_values[i];
	qDebug() << "GuidesModel end of dump";
}
#endif
