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
        double zuobiaozhunxianjiange{ 0 };
        double zuobiaozhunxianshangjuli{ 0 };
        int zuobiaozhunxianshuliang{ 0 };
        double youbiaozhunxianjiange{ 0 };
        double youbiaozhunxianshangjuli{ 0 };
        int youbiaozhunxianshuliang{ 0 };
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
        auto zuobiaozhunxianjiangeItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zuobiaozhunxianjiange$"));
        if (!zuobiaozhunxianjiangeItem) {
            throw std::runtime_error("$variable$zuobiaozhunxianjiange is not found");
        }
        zuobiaozhunxianjiange = zuobiaozhunxianjiangeItem->getValueAsDouble();
        auto zuobiaozhunxianshangjuliItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zuobiaozhunxianshangjuli$"));
        if (!zuobiaozhunxianshangjuliItem) {
            throw std::runtime_error("$variable$zuobiaozhunxianshangjuli is not found");
        }
        zuobiaozhunxianshangjuli = zuobiaozhunxianshangjuliItem->getValueAsDouble();
        auto zuobiaozhunxianshuliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zuobiaozhunxianshuliang$"));
        if (!zuobiaozhunxianshuliangItem) {
            throw std::runtime_error("$variable$zuobiaozhunxianshuliang is not found");
        }
        zuobiaozhunxianshuliang = zuobiaozhunxianshuliangItem->getValueAsInt();
        auto youbiaozhunxianjiangeItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$youbiaozhunxianjiange$"));
        if (!youbiaozhunxianjiangeItem) {
            throw std::runtime_error("$variable$youbiaozhunxianjiange is not found");
        }
        youbiaozhunxianjiange = youbiaozhunxianjiangeItem->getValueAsDouble();
        auto youbiaozhunxianshangjuliItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$youbiaozhunxianshangjuli$"));
        if (!youbiaozhunxianshangjuliItem) {
            throw std::runtime_error("$variable$youbiaozhunxianshangjuli is not found");
        }
        youbiaozhunxianshangjuli = youbiaozhunxianshangjuliItem->getValueAsDouble();
        auto youbiaozhunxianshuliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$youbiaozhunxianshuliang$"));
        if (!youbiaozhunxianshuliangItem) {
            throw std::runtime_error("$variable$youbiaozhunxianshuliang is not found");
        }
        youbiaozhunxianshuliang = youbiaozhunxianshuliangItem->getValueAsInt();
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
        zuobiaozhunxianjiange = obj.zuobiaozhunxianjiange;
        zuobiaozhunxianshangjuli = obj.zuobiaozhunxianshangjuli;
        zuobiaozhunxianshuliang = obj.zuobiaozhunxianshuliang;
        youbiaozhunxianjiange = obj.youbiaozhunxianjiange;
        youbiaozhunxianshangjuli = obj.youbiaozhunxianshangjuli;
        youbiaozhunxianshuliang = obj.youbiaozhunxianshuliang;
        baoguang = obj.baoguang;
        zengyi = obj.zengyi;
    }

    inline SetConfig& SetConfig::operator=(const SetConfig& obj)
    {
        if (this != &obj) {
            xiangsudangliang = obj.xiangsudangliang;
            zuobiaozhunxianjiange = obj.zuobiaozhunxianjiange;
            zuobiaozhunxianshangjuli = obj.zuobiaozhunxianshangjuli;
            zuobiaozhunxianshuliang = obj.zuobiaozhunxianshuliang;
            youbiaozhunxianjiange = obj.youbiaozhunxianjiange;
            youbiaozhunxianshangjuli = obj.youbiaozhunxianshangjuli;
            youbiaozhunxianshuliang = obj.youbiaozhunxianshuliang;
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
        auto zuobiaozhunxianjiangeItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zuobiaozhunxianjiangeItem->setName("$variable$zuobiaozhunxianjiange$");
        zuobiaozhunxianjiangeItem->setValueFromDouble(zuobiaozhunxianjiange);
        assembly.addItem(zuobiaozhunxianjiangeItem);
        auto zuobiaozhunxianshangjuliItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zuobiaozhunxianshangjuliItem->setName("$variable$zuobiaozhunxianshangjuli$");
        zuobiaozhunxianshangjuliItem->setValueFromDouble(zuobiaozhunxianshangjuli);
        assembly.addItem(zuobiaozhunxianshangjuliItem);
        auto zuobiaozhunxianshuliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zuobiaozhunxianshuliangItem->setName("$variable$zuobiaozhunxianshuliang$");
        zuobiaozhunxianshuliangItem->setValueFromInt(zuobiaozhunxianshuliang);
        assembly.addItem(zuobiaozhunxianshuliangItem);
        auto youbiaozhunxianjiangeItem = std::make_shared<rw::oso::ObjectStoreItem>();
        youbiaozhunxianjiangeItem->setName("$variable$youbiaozhunxianjiange$");
        youbiaozhunxianjiangeItem->setValueFromDouble(youbiaozhunxianjiange);
        assembly.addItem(youbiaozhunxianjiangeItem);
        auto youbiaozhunxianshangjuliItem = std::make_shared<rw::oso::ObjectStoreItem>();
        youbiaozhunxianshangjuliItem->setName("$variable$youbiaozhunxianshangjuli$");
        youbiaozhunxianshangjuliItem->setValueFromDouble(youbiaozhunxianshangjuli);
        assembly.addItem(youbiaozhunxianshangjuliItem);
        auto youbiaozhunxianshuliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        youbiaozhunxianshuliangItem->setName("$variable$youbiaozhunxianshuliang$");
        youbiaozhunxianshuliangItem->setValueFromInt(youbiaozhunxianshuliang);
        assembly.addItem(youbiaozhunxianshuliangItem);
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
        return xiangsudangliang == obj.xiangsudangliang && zuobiaozhunxianjiange == obj.zuobiaozhunxianjiange && zuobiaozhunxianshangjuli == obj.zuobiaozhunxianshangjuli && zuobiaozhunxianshuliang == obj.zuobiaozhunxianshuliang && youbiaozhunxianjiange == obj.youbiaozhunxianjiange && youbiaozhunxianshangjuli == obj.youbiaozhunxianshangjuli && youbiaozhunxianshuliang == obj.youbiaozhunxianshuliang && baoguang == obj.baoguang && zengyi == obj.zengyi;
    }

    inline bool SetConfig::operator!=(const SetConfig& obj) const
    {
        return !(*this == obj);
    }

}

