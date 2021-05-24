#ifndef MYSQL8_0_25_H
#define MYSQL8_0_25_H

#include <cplugininterface.h>

class MySQL8_0_25 : public CPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "CPluginInterface/Plugin/1.0")
    Q_INTERFACES(CPluginInterface)

public:
    QString name() override;
    QString version() override;
    QString query(IDataModel *dataModel) override;
};

#endif // MYSQL8_0_25_H
