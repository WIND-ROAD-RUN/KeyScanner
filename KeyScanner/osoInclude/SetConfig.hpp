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
        double chuiqishijian{ 0 };
        double xiangsudangliang{ 0 };
        double jishuguangdianyanshi{ 0 };
        double paizhaoyanshi{ 0 };
        double tifeiyanshi{ 0 };
        double score{ 0 };
        int cipinguangdianjiange{ 0 };
        double fenliaojishu{ 0 };
        double xiangjiguangdianpingbishijian{ 0 };
        double pidaiduibiyanse{ 0 };
        double shangxianwei{ 0 };
        double xiaxianwei{ 0 };
        double baoguang{ 0 };
        double zengyi{ 0 };
        int changeLanguageIndex{ 0 };
    };

    inline SetConfig::SetConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$SetConfig$")
        {
            throw std::runtime_error("Assembly is not $class$SetConfig$");
        }
        auto chuiqishijianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$chuiqishijian$"));
        if (!chuiqishijianItem) {
            throw std::runtime_error("$variable$chuiqishijian is not found");
        }
        chuiqishijian = chuiqishijianItem->getValueAsDouble();
        auto xiangsudangliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangsudangliang$"));
        if (!xiangsudangliangItem) {
            throw std::runtime_error("$variable$xiangsudangliang is not found");
        }
        xiangsudangliang = xiangsudangliangItem->getValueAsDouble();
        auto jishuguangdianyanshiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$jishuguangdianyanshi$"));
        if (!jishuguangdianyanshiItem) {
            throw std::runtime_error("$variable$jishuguangdianyanshi is not found");
        }
        jishuguangdianyanshi = jishuguangdianyanshiItem->getValueAsDouble();
        auto paizhaoyanshiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$paizhaoyanshi$"));
        if (!paizhaoyanshiItem) {
            throw std::runtime_error("$variable$paizhaoyanshi is not found");
        }
        paizhaoyanshi = paizhaoyanshiItem->getValueAsDouble();
        auto tifeiyanshiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tifeiyanshi$"));
        if (!tifeiyanshiItem) {
            throw std::runtime_error("$variable$tifeiyanshi is not found");
        }
        tifeiyanshi = tifeiyanshiItem->getValueAsDouble();
        auto scoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$score$"));
        if (!scoreItem) {
            throw std::runtime_error("$variable$score is not found");
        }
        score = scoreItem->getValueAsDouble();
        auto cipinguangdianjiangeItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$cipinguangdianjiange$"));
        if (!cipinguangdianjiangeItem) {
            throw std::runtime_error("$variable$cipinguangdianjiange is not found");
        }
        cipinguangdianjiange = cipinguangdianjiangeItem->getValueAsInt();
        auto fenliaojishuItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$fenliaojishu$"));
        if (!fenliaojishuItem) {
            throw std::runtime_error("$variable$fenliaojishu is not found");
        }
        fenliaojishu = fenliaojishuItem->getValueAsDouble();
        auto xiangjiguangdianpingbishijianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangjiguangdianpingbishijian$"));
        if (!xiangjiguangdianpingbishijianItem) {
            throw std::runtime_error("$variable$xiangjiguangdianpingbishijian is not found");
        }
        xiangjiguangdianpingbishijian = xiangjiguangdianpingbishijianItem->getValueAsDouble();
        auto pidaiduibiyanseItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$pidaiduibiyanse$"));
        if (!pidaiduibiyanseItem) {
            throw std::runtime_error("$variable$pidaiduibiyanse is not found");
        }
        pidaiduibiyanse = pidaiduibiyanseItem->getValueAsDouble();
        auto shangxianweiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shangxianwei$"));
        if (!shangxianweiItem) {
            throw std::runtime_error("$variable$shangxianwei is not found");
        }
        shangxianwei = shangxianweiItem->getValueAsDouble();
        auto xiaxianweiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiaxianwei$"));
        if (!xiaxianweiItem) {
            throw std::runtime_error("$variable$xiaxianwei is not found");
        }
        xiaxianwei = xiaxianweiItem->getValueAsDouble();
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
        auto changeLanguageIndexItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$changeLanguageIndex$"));
        if (!changeLanguageIndexItem) {
            throw std::runtime_error("$variable$changeLanguageIndex is not found");
        }
        changeLanguageIndex = changeLanguageIndexItem->getValueAsInt();
    }

    inline SetConfig::SetConfig(const SetConfig& obj)
    {
        chuiqishijian = obj.chuiqishijian;
        xiangsudangliang = obj.xiangsudangliang;
        jishuguangdianyanshi = obj.jishuguangdianyanshi;
        paizhaoyanshi = obj.paizhaoyanshi;
        tifeiyanshi = obj.tifeiyanshi;
        score = obj.score;
        cipinguangdianjiange = obj.cipinguangdianjiange;
        fenliaojishu = obj.fenliaojishu;
        xiangjiguangdianpingbishijian = obj.xiangjiguangdianpingbishijian;
        pidaiduibiyanse = obj.pidaiduibiyanse;
        shangxianwei = obj.shangxianwei;
        xiaxianwei = obj.xiaxianwei;
        baoguang = obj.baoguang;
        zengyi = obj.zengyi;
        changeLanguageIndex = obj.changeLanguageIndex;
    }

    inline SetConfig& SetConfig::operator=(const SetConfig& obj)
    {
        if (this != &obj) {
            chuiqishijian = obj.chuiqishijian;
            xiangsudangliang = obj.xiangsudangliang;
            jishuguangdianyanshi = obj.jishuguangdianyanshi;
            paizhaoyanshi = obj.paizhaoyanshi;
            tifeiyanshi = obj.tifeiyanshi;
            score = obj.score;
            cipinguangdianjiange = obj.cipinguangdianjiange;
            fenliaojishu = obj.fenliaojishu;
            xiangjiguangdianpingbishijian = obj.xiangjiguangdianpingbishijian;
            pidaiduibiyanse = obj.pidaiduibiyanse;
            shangxianwei = obj.shangxianwei;
            xiaxianwei = obj.xiaxianwei;
            baoguang = obj.baoguang;
            zengyi = obj.zengyi;
            changeLanguageIndex = obj.changeLanguageIndex;
        }
        return *this;
    }

    inline SetConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$SetConfig$");
        auto chuiqishijianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        chuiqishijianItem->setName("$variable$chuiqishijian$");
        chuiqishijianItem->setValueFromDouble(chuiqishijian);
        assembly.addItem(chuiqishijianItem);
        auto xiangsudangliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangsudangliangItem->setName("$variable$xiangsudangliang$");
        xiangsudangliangItem->setValueFromDouble(xiangsudangliang);
        assembly.addItem(xiangsudangliangItem);
        auto jishuguangdianyanshiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        jishuguangdianyanshiItem->setName("$variable$jishuguangdianyanshi$");
        jishuguangdianyanshiItem->setValueFromDouble(jishuguangdianyanshi);
        assembly.addItem(jishuguangdianyanshiItem);
        auto paizhaoyanshiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        paizhaoyanshiItem->setName("$variable$paizhaoyanshi$");
        paizhaoyanshiItem->setValueFromDouble(paizhaoyanshi);
        assembly.addItem(paizhaoyanshiItem);
        auto tifeiyanshiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        tifeiyanshiItem->setName("$variable$tifeiyanshi$");
        tifeiyanshiItem->setValueFromDouble(tifeiyanshi);
        assembly.addItem(tifeiyanshiItem);
        auto scoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        scoreItem->setName("$variable$score$");
        scoreItem->setValueFromDouble(score);
        assembly.addItem(scoreItem);
        auto cipinguangdianjiangeItem = std::make_shared<rw::oso::ObjectStoreItem>();
        cipinguangdianjiangeItem->setName("$variable$cipinguangdianjiange$");
        cipinguangdianjiangeItem->setValueFromInt(cipinguangdianjiange);
        assembly.addItem(cipinguangdianjiangeItem);
        auto fenliaojishuItem = std::make_shared<rw::oso::ObjectStoreItem>();
        fenliaojishuItem->setName("$variable$fenliaojishu$");
        fenliaojishuItem->setValueFromDouble(fenliaojishu);
        assembly.addItem(fenliaojishuItem);
        auto xiangjiguangdianpingbishijianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangjiguangdianpingbishijianItem->setName("$variable$xiangjiguangdianpingbishijian$");
        xiangjiguangdianpingbishijianItem->setValueFromDouble(xiangjiguangdianpingbishijian);
        assembly.addItem(xiangjiguangdianpingbishijianItem);
        auto pidaiduibiyanseItem = std::make_shared<rw::oso::ObjectStoreItem>();
        pidaiduibiyanseItem->setName("$variable$pidaiduibiyanse$");
        pidaiduibiyanseItem->setValueFromDouble(pidaiduibiyanse);
        assembly.addItem(pidaiduibiyanseItem);
        auto shangxianweiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        shangxianweiItem->setName("$variable$shangxianwei$");
        shangxianweiItem->setValueFromDouble(shangxianwei);
        assembly.addItem(shangxianweiItem);
        auto xiaxianweiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiaxianweiItem->setName("$variable$xiaxianwei$");
        xiaxianweiItem->setValueFromDouble(xiaxianwei);
        assembly.addItem(xiaxianweiItem);
        auto baoguangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        baoguangItem->setName("$variable$baoguang$");
        baoguangItem->setValueFromDouble(baoguang);
        assembly.addItem(baoguangItem);
        auto zengyiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zengyiItem->setName("$variable$zengyi$");
        zengyiItem->setValueFromDouble(zengyi);
        assembly.addItem(zengyiItem);
        auto changeLanguageIndexItem = std::make_shared<rw::oso::ObjectStoreItem>();
        changeLanguageIndexItem->setName("$variable$changeLanguageIndex$");
        changeLanguageIndexItem->setValueFromInt(changeLanguageIndex);
        assembly.addItem(changeLanguageIndexItem);
        return assembly;
    }

    inline bool SetConfig::operator==(const SetConfig& obj) const
    {
        return chuiqishijian == obj.chuiqishijian && xiangsudangliang == obj.xiangsudangliang && jishuguangdianyanshi == obj.jishuguangdianyanshi && paizhaoyanshi == obj.paizhaoyanshi && tifeiyanshi == obj.tifeiyanshi && score == obj.score && cipinguangdianjiange == obj.cipinguangdianjiange && fenliaojishu == obj.fenliaojishu && xiangjiguangdianpingbishijian == obj.xiangjiguangdianpingbishijian && pidaiduibiyanse == obj.pidaiduibiyanse && shangxianwei == obj.shangxianwei && xiaxianwei == obj.xiaxianwei && baoguang == obj.baoguang && zengyi == obj.zengyi && changeLanguageIndex == obj.changeLanguageIndex;
    }

    inline bool SetConfig::operator!=(const SetConfig& obj) const
    {
        return !(*this == obj);
    }

}

