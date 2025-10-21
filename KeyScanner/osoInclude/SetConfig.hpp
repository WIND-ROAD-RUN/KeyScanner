#pragma once

#include"oso_core.h"
#include <string>

namespace cdm {
    class SetConfig
    {
    public:
        SetConfig() = default;
        ~SetConfig() = default;

        SetConfig(const rw::oso::ObjectStoreAssembly& assembly);
        SetConfig(const SetConfig& obj);

        SetConfig& operator=(const SetConfig& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const SetConfig& obj) const;
        bool operator!=(const SetConfig& obj) const;

    public:
        double xiangsudangliang{ 0 };
        double biaozhunxianjiange{ 0 };
        double biaozhunxianshangjuli{ 0 };
        int biaozhunxianshuliang{ 0 };
        double baoguang{ 0 };
        double zengyi{ 0 };
    };

    inline SetConfig::SetConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$SetConfig$")
        {
            throw std::runtime_error("Assembly is not $class$SetConfig$");
        }
        auto xiangsudangliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangsudangliang$"));
        if (!xiangsudangliangItem) {
            throw std::runtime_error("$variable$xiangsudangliang is not found");
        }
        xiangsudangliang = xiangsudangliangItem->getValueAsDouble();
        auto biaozhunxianjiangeItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$biaozhunxianjiange$"));
        if (!biaozhunxianjiangeItem) {
            throw std::runtime_error("$variable$biaozhunxianjiange is not found");
        }
        biaozhunxianjiange = biaozhunxianjiangeItem->getValueAsDouble();
        auto biaozhunxianshangjuliItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$biaozhunxianshangjuli$"));
        if (!biaozhunxianshangjuliItem) {
            throw std::runtime_error("$variable$biaozhunxianshangjuli is not found");
        }
        biaozhunxianshangjuli = biaozhunxianshangjuliItem->getValueAsDouble();
        auto biaozhunxianshuliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$biaozhunxianshuliang$"));
        if (!biaozhunxianshuliangItem) {
            throw std::runtime_error("$variable$biaozhunxianshuliang is not found");
        }
        biaozhunxianshuliang = biaozhunxianshuliangItem->getValueAsInt();
        auto baoguangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$baoguang$"));
        if (!baoguangItem) {
            throw std::runtime_error("$variable$baoguang is not found");
        }
        baoguang = baoguangItem->getValueAsDouble();
        auto zengyiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zengyi$"));
        if (!zengyiItem) {
            throw std::runtime_error("$variable$zengyi is not found");
        }
        zengyi = zengyiItem->getValueAsDouble();
    }

    inline SetConfig::SetConfig(const SetConfig& obj)
    {
        xiangsudangliang = obj.xiangsudangliang;
        biaozhunxianjiange = obj.biaozhunxianjiange;
        biaozhunxianshangjuli = obj.biaozhunxianshangjuli;
        biaozhunxianshuliang = obj.biaozhunxianshuliang;
        baoguang = obj.baoguang;
        zengyi = obj.zengyi;
    }

    inline SetConfig& SetConfig::operator=(const SetConfig& obj)
    {
        if (this != &obj) {
            xiangsudangliang = obj.xiangsudangliang;
            biaozhunxianjiange = obj.biaozhunxianjiange;
            biaozhunxianshangjuli = obj.biaozhunxianshangjuli;
            biaozhunxianshuliang = obj.biaozhunxianshuliang;
            baoguang = obj.baoguang;
            zengyi = obj.zengyi;
        }
        return *this;
    }

    inline SetConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$SetConfig$");
        auto xiangsudangliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangsudangliangItem->setName("$variable$xiangsudangliang$");
        xiangsudangliangItem->setValueFromDouble(xiangsudangliang);
        assembly.addItem(xiangsudangliangItem);
        auto biaozhunxianjiangeItem = std::make_shared<rw::oso::ObjectStoreItem>();
        biaozhunxianjiangeItem->setName("$variable$biaozhunxianjiange$");
        biaozhunxianjiangeItem->setValueFromDouble(biaozhunxianjiange);
        assembly.addItem(biaozhunxianjiangeItem);
        auto biaozhunxianshangjuliItem = std::make_shared<rw::oso::ObjectStoreItem>();
        biaozhunxianshangjuliItem->setName("$variable$biaozhunxianshangjuli$");
        biaozhunxianshangjuliItem->setValueFromDouble(biaozhunxianshangjuli);
        assembly.addItem(biaozhunxianshangjuliItem);
        auto biaozhunxianshuliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        biaozhunxianshuliangItem->setName("$variable$biaozhunxianshuliang$");
        biaozhunxianshuliangItem->setValueFromInt(biaozhunxianshuliang);
        assembly.addItem(biaozhunxianshuliangItem);
        auto baoguangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        baoguangItem->setName("$variable$baoguang$");
        baoguangItem->setValueFromDouble(baoguang);
        assembly.addItem(baoguangItem);
        auto zengyiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zengyiItem->setName("$variable$zengyi$");
        zengyiItem->setValueFromDouble(zengyi);
        assembly.addItem(zengyiItem);
        return assembly;
    }

    inline bool SetConfig::operator==(const SetConfig& obj) const
    {
        return xiangsudangliang == obj.xiangsudangliang && biaozhunxianjiange == obj.biaozhunxianjiange && biaozhunxianshangjuli == obj.biaozhunxianshangjuli && biaozhunxianshuliang == obj.biaozhunxianshuliang && baoguang == obj.baoguang && zengyi == obj.zengyi;
    }

    inline bool SetConfig::operator!=(const SetConfig& obj) const
    {
        return !(*this == obj);
    }

}

