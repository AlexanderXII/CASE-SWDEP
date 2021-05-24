#ifndef POSTGRESQL13_2_H
#define POSTGRESQL13_2_H

#include <cplugininterface.h>

class Postgresql13_2 : public CPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "CPluginInterface/Plugin/1.0")
    Q_INTERFACES(CPluginInterface)

public:
    QString name() override;
    QString version() override;
    QString query(IDataModel *dataModel) override;
};


#endif // POSTGRESQL13_2_H
