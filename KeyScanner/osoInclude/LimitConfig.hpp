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
        double waichi1xiaxian{ 0.0 };
        double waichi2xiaxian{ 0.0 };
        double waichi3xiaxian{ 0.0 };
        double waichi4xiaxian{ 0.0 };
        double waichi1shangxian{ 0.0 };
        double waichi2shangxian{ 0.0 };
        double waichi3shangxian{ 0.0 };
        double waichi4shangxian{ 0.0 };
    };

    inline LimitConfig::LimitConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$LimitConfig$")
        {
            throw std::runtime_error("Assembly is not $class$LimitConfig$");
        }
        auto waichi1xiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi1xiaxian$"));
        if (!waichi1xiaxianItem) {
            throw std::runtime_error("$variable$waichi1xiaxian is not found");
        }
        waichi1xiaxian = waichi1xiaxianItem->getValueAsDouble();
        auto waichi2xiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi2xiaxian$"));
        if (!waichi2xiaxianItem) {
            throw std::runtime_error("$variable$waichi2xiaxian is not found");
        }
        waichi2xiaxian = waichi2xiaxianItem->getValueAsDouble();
        auto waichi3xiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi3xiaxian$"));
        if (!waichi3xiaxianItem) {
            throw std::runtime_error("$variable$waichi3xiaxian is not found");
        }
        waichi3xiaxian = waichi3xiaxianItem->getValueAsDouble();
        auto waichi4xiaxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi4xiaxian$"));
        if (!waichi4xiaxianItem) {
            throw std::runtime_error("$variable$waichi4xiaxian is not found");
        }
        waichi4xiaxian = waichi4xiaxianItem->getValueAsDouble();
        auto waichi1shangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi1shangxian$"));
        if (!waichi1shangxianItem) {
            throw std::runtime_error("$variable$waichi1shangxian is not found");
        }
        waichi1shangxian = waichi1shangxianItem->getValueAsDouble();
        auto waichi2shangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi2shangxian$"));
        if (!waichi2shangxianItem) {
            throw std::runtime_error("$variable$waichi2shangxian is not found");
        }
        waichi2shangxian = waichi2shangxianItem->getValueAsDouble();
        auto waichi3shangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi3shangxian$"));
        if (!waichi3shangxianItem) {
            throw std::runtime_error("$variable$waichi3shangxian is not found");
        }
        waichi3shangxian = waichi3shangxianItem->getValueAsDouble();
        auto waichi4shangxianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$waichi4shangxian$"));
        if (!waichi4shangxianItem) {
            throw std::runtime_error("$variable$waichi4shangxian is not found");
        }
        waichi4shangxian = waichi4shangxianItem->getValueAsDouble();
    }

    inline LimitConfig::LimitConfig(const LimitConfig& obj)
    {
        waichi1xiaxian = obj.waichi1xiaxian;
        waichi2xiaxian = obj.waichi2xiaxian;
        waichi3xiaxian = obj.waichi3xiaxian;
        waichi4xiaxian = obj.waichi4xiaxian;
        waichi1shangxian = obj.waichi1shangxian;
        waichi2shangxian = obj.waichi2shangxian;
        waichi3shangxian = obj.waichi3shangxian;
        waichi4shangxian = obj.waichi4shangxian;
    }

    inline LimitConfig& LimitConfig::operator=(const LimitConfig& obj)
    {
        if (this != &obj) {
            waichi1xiaxian = obj.waichi1xiaxian;
            waichi2xiaxian = obj.waichi2xiaxian;
            waichi3xiaxian = obj.waichi3xiaxian;
            waichi4xiaxian = obj.waichi4xiaxian;
            waichi1shangxian = obj.waichi1shangxian;
            waichi2shangxian = obj.waichi2shangxian;
            waichi3shangxian = obj.waichi3shangxian;
            waichi4shangxian = obj.waichi4shangxian;
        }
        return *this;
    }

    inline LimitConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$LimitConfig$");
        auto waichi1xiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi1xiaxianItem->setName("$variable$waichi1xiaxian$");
        waichi1xiaxianItem->setValueFromDouble(waichi1xiaxian);
        assembly.addItem(waichi1xiaxianItem);
        auto waichi2xiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi2xiaxianItem->setName("$variable$waichi2xiaxian$");
        waichi2xiaxianItem->setValueFromDouble(waichi2xiaxian);
        assembly.addItem(waichi2xiaxianItem);
        auto waichi3xiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi3xiaxianItem->setName("$variable$waichi3xiaxian$");
        waichi3xiaxianItem->setValueFromDouble(waichi3xiaxian);
        assembly.addItem(waichi3xiaxianItem);
        auto waichi4xiaxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi4xiaxianItem->setName("$variable$waichi4xiaxian$");
        waichi4xiaxianItem->setValueFromDouble(waichi4xiaxian);
        assembly.addItem(waichi4xiaxianItem);
        auto waichi1shangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi1shangxianItem->setName("$variable$waichi1shangxian$");
        waichi1shangxianItem->setValueFromDouble(waichi1shangxian);
        assembly.addItem(waichi1shangxianItem);
        auto waichi2shangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi2shangxianItem->setName("$variable$waichi2shangxian$");
        waichi2shangxianItem->setValueFromDouble(waichi2shangxian);
        assembly.addItem(waichi2shangxianItem);
        auto waichi3shangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi3shangxianItem->setName("$variable$waichi3shangxian$");
        waichi3shangxianItem->setValueFromDouble(waichi3shangxian);
        assembly.addItem(waichi3shangxianItem);
        auto waichi4shangxianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        waichi4shangxianItem->setName("$variable$waichi4shangxian$");
        waichi4shangxianItem->setValueFromDouble(waichi4shangxian);
        assembly.addItem(waichi4shangxianItem);
        return assembly;
    }

    inline bool LimitConfig::operator==(const LimitConfig& obj) const
    {
        return waichi1xiaxian == obj.waichi1xiaxian && waichi2xiaxian == obj.waichi2xiaxian && waichi3xiaxian == obj.waichi3xiaxian && waichi4xiaxian == obj.waichi4xiaxian && waichi1shangxian == obj.waichi1shangxian && waichi2shangxian == obj.waichi2shangxian && waichi3shangxian == obj.waichi3shangxian && waichi4shangxian == obj.waichi4shangxian;
    }

    inline bool LimitConfig::operator!=(const LimitConfig& obj) const
    {
        return !(*this == obj);
    }

}

