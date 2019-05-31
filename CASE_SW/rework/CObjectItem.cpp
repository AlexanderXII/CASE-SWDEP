#include "CObjectItem.h"
#include "CObject.h"

CObjectItem::CObjectItem(CObject *object) :
    _object(object),
    _editor(0)
{
    this->setFlags(ItemIsSelectable |
                   ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
}

CObjectItem::~CObjectItem()
{
    _object = NULL;
    _editor = NULL;
}

int CObjectItem::type() const
{
    return Type;
}

int CObjectItem::id()
{
    if(_object != 0)
        return _object->id();
    else
        return -1;
}

QString CObjectItem::name()
{
    if(_object != 0)
        return _object->name();
    else
        return "";
}

CObject *CObjectItem::object() const
{
    return _object;
}

QWidget *CObjectItem::editor() const
{
    return _editor;
}

void CObjectItem::setEditor(QWidget *editor)
{
    _editor = editor;
}
