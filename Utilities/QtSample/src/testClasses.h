#pragma once

#include <qobject.h>

namespace Test
{
    Q_NAMESPACE

    class Object : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(int id MEMBER m_id)
        Q_PROPERTY(ObjectEnum e MEMBER m_enum)

    public:
        Object(int ID = -1, QObject* parent = nullptr)
            : QObject(parent)
            , m_id(ID)
        {
        }

        ~Object()
        {
        }

        enum class ObjectEnum
        {
            ONE,
            TWO,
            THREE
        };
        Q_ENUM(ObjectEnum)

    private:
        ObjectEnum m_enum = ObjectEnum::THREE;
        int m_id = 0;
    };

    class Gadget
    {
        Q_GADGET
        Q_PROPERTY(int id MEMBER m_id)

    public:
        Gadget(int ID = -1)
            : m_id(ID)
        {
        }

        ~Gadget()
        {
        }

        bool operator!=(const Gadget& g) const
        {
            return g.m_id != m_id;
        }

        bool operator==(const Gadget& g) const
        {
            return g.m_id == m_id;
        }

    private:
        int m_id = 0;
    };
    Q_DECLARE_METATYPE(Gadget)

    enum class Enum
    {
        ONE,
        TWO, 
        THREE
    };
    Q_ENUM_NS(Enum)
}