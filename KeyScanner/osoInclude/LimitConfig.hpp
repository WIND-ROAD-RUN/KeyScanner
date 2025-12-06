#pragma once

#include"oso_core.h"
#include <string>

namespace cdm {
    class LimitConfig
    {
    public:
        LimitConfig() = default;
        ~LimitConfig() = default;

        LimitConfig(const rw::oso::ObjectStoreAssembly& assembly);
        LimitConfig(const LimitConfig& obj);

        LimitConfig& operator=(const LimitConfig& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const LimitConfig& obj) const;
        bool operator!=(const LimitConfig& obj) const;

    public:
        int neichi1zuoxiaxian{ 0 };
        int neichi2zuoxiaxian{ 0 };
        int neichi3zuoxiaxian{ 0 };
        int neichi4zuoxiaxian{ 0 };
        int neichi1zuoshangxian{ 0 };
        int neichi2zuoshangxian{ 0 };
        int neichi3zuoshangxian{ 0 };
        int neichi4zuoshangxian{ 0 };
        int neichi1youxiaxian{ 0 };
        int neichi2youxiaxian{ 0 };
        int neichi3youxiaxian{ 0 };
        int neichi4youxiaxian{ 0 };
        int neichi1youshangxian{ 0 };
        int neichi2youshangxian{ 0 };
        int neichi3youshangxian{ 0 };
        int neichi4youshangxian{ 0 };
    };

    inline LimitConfig::LimitConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$LimitConfig$")
        {
            throw std::runtime_error("Assembly is not $class$LimitConfig$");
        }
        auto neichi1zuoxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi1zuoxiaxian$"));
        if (!neichi1zuoxiaxianItem) {
            throw std::runtime_error("$variable$neichi1zuoxiaxian is not found");
        }
        neichi1zuoxiaxian = neichi1zuoxiaxianItem->getValueAsInt();
        auto neichi2zuoxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi2zuoxiaxian$"));
        if (!neichi2zuoxiaxianItem) {
            throw std::runtime_error("$variable$neichi2zuoxiaxian is not found");
        }
        neichi2zuoxiaxian = neichi2zuoxiaxianItem->getValueAsInt();
        auto neichi3zuoxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi3zuoxiaxian$"));
        if (!neichi3zuoxiaxianItem) {
            throw std::runtime_error("$variable$neichi3zuoxiaxian is not found");
        }
        neichi3zuoxiaxian = neichi3zuoxiaxianItem->getValueAsInt();
        auto neichi4zuoxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi4zuoxiaxian$"));
        if (!neichi4zuoxiaxianItem) {
            throw std::runtime_error("$variable$neichi4zuoxiaxian is not found");
        }
        neichi4zuoxiaxian = neichi4zuoxiaxianItem->getValueAsInt();
        auto neichi1zuoshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi1zuoshangxian$"));
        if (!neichi1zuoshangxianItem) {
            throw std::runtime_error("$variable$neichi1zuoshangxian is not found");
        }
        neichi1zuoshangxian = neichi1zuoshangxianItem->getValueAsInt();
        auto neichi2zuoshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi2zuoshangxian$"));
        if (!neichi2zuoshangxianItem) {
            throw std::runtime_error("$variable$neichi2zuoshangxian is not found");
        }
        neichi2zuoshangxian = neichi2zuoshangxianItem->getValueAsInt();
        auto neichi3zuoshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi3zuoshangxian$"));
        if (!neichi3zuoshangxianItem) {
            throw std::runtime_error("$variable$neichi3zuoshangxian is not found");
        }
        neichi3zuoshangxian = neichi3zuoshangxianItem->getValueAsInt();
        auto neichi4zuoshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi4zuoshangxian$"));
        if (!neichi4zuoshangxianItem) {
            throw std::runtime_error("$variable$neichi4zuoshangxian is not found");
        }
        neichi4zuoshangxian = neichi4zuoshangxianItem->getValueAsInt();
        auto neichi1youxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi1youxiaxian$"));
        if (!neichi1youxiaxianItem) {
            throw std::runtime_error("$variable$neichi1youxiaxian is not found");
        }
        neichi1youxiaxian = neichi1youxiaxianItem->getValueAsInt();
        auto neichi2youxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi2youxiaxian$"));
        if (!neichi2youxiaxianItem) {
            throw std::runtime_error("$variable$neichi2youxiaxian is not found");
        }
        neichi2youxiaxian = neichi2youxiaxianItem->getValueAsInt();
        auto neichi3youxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi3youxiaxian$"));
        if (!neichi3youxiaxianItem) {
            throw std::runtime_error("$variable$neichi3youxiaxian is not found");
        }
        neichi3youxiaxian = neichi3youxiaxianItem->getValueAsInt();
        auto neichi4youxiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi4youxiaxian$"));
        if (!neichi4youxiaxianItem) {
            throw std::runtime_error("$variable$neichi4youxiaxian is not found");
        }
        neichi4youxiaxian = neichi4youxiaxianItem->getValueAsInt();
        auto neichi1youshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi1youshangxian$"));
        if (!neichi1youshangxianItem) {
            throw std::runtime_error("$variable$neichi1youshangxian is not found");
        }
        neichi1youshangxian = neichi1youshangxianItem->getValueAsInt();
        auto neichi2youshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi2youshangxian$"));
        if (!neichi2youshangxianItem) {
            throw std::runtime_error("$variable$neichi2youshangxian is not found");
        }
        neichi2youshangxian = neichi2youshangxianItem->getValueAsInt();
        auto neichi3youshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi3youshangxian$"));
        if (!neichi3youshangxianItem) {
            throw std::runtime_error("$variable$neichi3youshangxian is not found");
        }
        neichi3youshangxian = neichi3youshangxianItem->getValueAsInt();
        auto neichi4youshangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$neichi4youshangxian$"));
        if (!neichi4youshangxianItem) {
            throw std::runtime_error("$variable$neichi4youshangxian is not found");
        }
        neichi4youshangxian = neichi4youshangxianItem->getValueAsInt();
    }

    inline LimitConfig::LimitConfig(const LimitConfig& obj)
    {
        neichi1zuoxiaxian = obj.neichi1zuoxiaxian;
        neichi2zuoxiaxian = obj.neichi2zuoxiaxian;
        neichi3zuoxiaxian = obj.neichi3zuoxiaxian;
        neichi4zuoxiaxian = obj.neichi4zuoxiaxian;
        neichi1zuoshangxian = obj.neichi1zuoshangxian;
        neichi2zuoshangxian = obj.neichi2zuoshangxian;
        neichi3zuoshangxian = obj.neichi3zuoshangxian;
        neichi4zuoshangxian = obj.neichi4zuoshangxian;
        neichi1youxiaxian = obj.neichi1youxiaxian;
        neichi2youxiaxian = obj.neichi2youxiaxian;
        neichi3youxiaxian = obj.neichi3youxiaxian;
        neichi4youxiaxian = obj.neichi4youxiaxian;
        neichi1youshangxian = obj.neichi1youshangxian;
        neichi2youshangxian = obj.neichi2youshangxian;
        neichi3youshangxian = obj.neichi3youshangxian;
        neichi4youshangxian = obj.neichi4youshangxian;
    }

    inline LimitConfig& LimitConfig::operator=(const LimitConfig& obj)
    {
        if (this != &obj) {
            neichi1zuoxiaxian = obj.neichi1zuoxiaxian;
            neichi2zuoxiaxian = obj.neichi2zuoxiaxian;
            neichi3zuoxiaxian = obj.neichi3zuoxiaxian;
            neichi4zuoxiaxian = obj.neichi4zuoxiaxian;
            neichi1zuoshangxian = obj.neichi1zuoshangxian;
            neichi2zuoshangxian = obj.neichi2zuoshangxian;
            neichi3zuoshangxian = obj.neichi3zuoshangxian;
            neichi4zuoshangxian = obj.neichi4zuoshangxian;
            neichi1youxiaxian = obj.neichi1youxiaxian;
            neichi2youxiaxian = obj.neichi2youxiaxian;
            neichi3youxiaxian = obj.neichi3youxiaxian;
            neichi4youxiaxian = obj.neichi4youxiaxian;
            neichi1youshangxian = obj.neichi1youshangxian;
            neichi2youshangxian = obj.neichi2youshangxian;
            neichi3youshangxian = obj.neichi3youshangxian;
            neichi4youshangxian = obj.neichi4youshangxian;
        }
        return *this;
    }

    inline LimitConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$LimitConfig$");
        auto neichi1zuoxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi1zuoxiaxianItem->setName("$variable$neichi1zuoxiaxian$");
        neichi1zuoxiaxianItem->setValueFromInt(neichi1zuoxiaxian);
        assembly.addItem(neichi1zuoxiaxianItem);
        auto neichi2zuoxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi2zuoxiaxianItem->setName("$variable$neichi2zuoxiaxian$");
        neichi2zuoxiaxianItem->setValueFromInt(neichi2zuoxiaxian);
        assembly.addItem(neichi2zuoxiaxianItem);
        auto neichi3zuoxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi3zuoxiaxianItem->setName("$variable$neichi3zuoxiaxian$");
        neichi3zuoxiaxianItem->setValueFromInt(neichi3zuoxiaxian);
        assembly.addItem(neichi3zuoxiaxianItem);
        auto neichi4zuoxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi4zuoxiaxianItem->setName("$variable$neichi4zuoxiaxian$");
        neichi4zuoxiaxianItem->setValueFromInt(neichi4zuoxiaxian);
        assembly.addItem(neichi4zuoxiaxianItem);
        auto neichi1zuoshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi1zuoshangxianItem->setName("$variable$neichi1zuoshangxian$");
        neichi1zuoshangxianItem->setValueFromInt(neichi1zuoshangxian);
        assembly.addItem(neichi1zuoshangxianItem);
        auto neichi2zuoshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi2zuoshangxianItem->setName("$variable$neichi2zuoshangxian$");
        neichi2zuoshangxianItem->setValueFromInt(neichi2zuoshangxian);
        assembly.addItem(neichi2zuoshangxianItem);
        auto neichi3zuoshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi3zuoshangxianItem->setName("$variable$neichi3zuoshangxian$");
        neichi3zuoshangxianItem->setValueFromInt(neichi3zuoshangxian);
        assembly.addItem(neichi3zuoshangxianItem);
        auto neichi4zuoshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi4zuoshangxianItem->setName("$variable$neichi4zuoshangxian$");
        neichi4zuoshangxianItem->setValueFromInt(neichi4zuoshangxian);
        assembly.addItem(neichi4zuoshangxianItem);
        auto neichi1youxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi1youxiaxianItem->setName("$variable$neichi1youxiaxian$");
        neichi1youxiaxianItem->setValueFromInt(neichi1youxiaxian);
        assembly.addItem(neichi1youxiaxianItem);
        auto neichi2youxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi2youxiaxianItem->setName("$variable$neichi2youxiaxian$");
        neichi2youxiaxianItem->setValueFromInt(neichi2youxiaxian);
        assembly.addItem(neichi2youxiaxianItem);
        auto neichi3youxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi3youxiaxianItem->setName("$variable$neichi3youxiaxian$");
        neichi3youxiaxianItem->setValueFromInt(neichi3youxiaxian);
        assembly.addItem(neichi3youxiaxianItem);
        auto neichi4youxiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi4youxiaxianItem->setName("$variable$neichi4youxiaxian$");
        neichi4youxiaxianItem->setValueFromInt(neichi4youxiaxian);
        assembly.addItem(neichi4youxiaxianItem);
        auto neichi1youshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi1youshangxianItem->setName("$variable$neichi1youshangxian$");
        neichi1youshangxianItem->setValueFromInt(neichi1youshangxian);
        assembly.addItem(neichi1youshangxianItem);
        auto neichi2youshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi2youshangxianItem->setName("$variable$neichi2youshangxian$");
        neichi2youshangxianItem->setValueFromInt(neichi2youshangxian);
        assembly.addItem(neichi2youshangxianItem);
        auto neichi3youshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi3youshangxianItem->setName("$variable$neichi3youshangxian$");
        neichi3youshangxianItem->setValueFromInt(neichi3youshangxian);
        assembly.addItem(neichi3youshangxianItem);
        auto neichi4youshangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        neichi4youshangxianItem->setName("$variable$neichi4youshangxian$");
        neichi4youshangxianItem->setValueFromInt(neichi4youshangxian);
        assembly.addItem(neichi4youshangxianItem);
        return assembly;
    }

    inline bool LimitConfig::operator==(const LimitConfig& obj) const
    {
        return neichi1zuoxiaxian == obj.neichi1zuoxiaxian && neichi2zuoxiaxian == obj.neichi2zuoxiaxian && neichi3zuoxiaxian == obj.neichi3zuoxiaxian && neichi4zuoxiaxian == obj.neichi4zuoxiaxian && neichi1zuoshangxian == obj.neichi1zuoshangxian && neichi2zuoshangxian == obj.neichi2zuoshangxian && neichi3zuoshangxian == obj.neichi3zuoshangxian && neichi4zuoshangxian == obj.neichi4zuoshangxian && neichi1youxiaxian == obj.neichi1youxiaxian && neichi2youxiaxian == obj.neichi2youxiaxian && neichi3youxiaxian == obj.neichi3youxiaxian && neichi4youxiaxian == obj.neichi4youxiaxian && neichi1youshangxian == obj.neichi1youshangxian && neichi2youshangxian == obj.neichi2youshangxian && neichi3youshangxian == obj.neichi3youshangxian && neichi4youshangxian == obj.neichi4youshangxian;
    }

    inline bool LimitConfig::operator!=(const LimitConfig& obj) const
    {
        return !(*this == obj);
    }

}

