#ifndef SQLITE3_35_5_H
#define SQLITE3_35_5_H

#include <cplugininterface.h>

class SQLite3_35_5 : public CPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "CPluginInterface/Plugin/1.0")
    Q_INTERFACES(CPluginInterface)

public:
    QString name() override;
    QString version() override;
    QString query(IDataModel *dataModel) override;
};


#endif // SQLITE3_35_5_H
