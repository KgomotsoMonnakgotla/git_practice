//
//  Mbb.hpp
//  kg
//
//  Created by Kgomotso Monnakgotla on 4/26/19.
//  Copyright © 2019 Kgomotso Monnakgotla. All rights reserved.
//

#ifndef Mbb_hpp
#define Mbb_hpp

#include <stdio.h>
//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWBTAGCOUNTEROBS__
#define __HWWBTAGCOUNTEROBS__
#include "CAFxAODUtils/TQEventObservable.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"
#include "xAODBTaggingEfficiency/BTaggingSelectionTool.h"
#include "AsgTools/AnaToolHandle.h"
#include "FTagAnalysisInterfaces/IBTaggingSelectionTool.h"

class HWWmbbObs : public TQEventObservable {
protected:
    TString mContName = "";
    
    mutable xAOD::CompositeParticleContainer const * mCand = 0;
public:
    virtual double getValue() const override;
protected:
    virtual bool initializeSelf() override;
    virtual bool finalizeSelf() override;
    ToolHandle<IBTaggingSelectionTool>  m_btagtool; //!
    bool m_wasInitialized = false; //!
public:
    HWWmbbObs();
    HWWmbbObs(const TString& name, std::string BTagName="MV2c10", std::string BTagWP = "FixedCutBEff_85",
                      float PtCut=20000.0, bool UseOtherJets=false, bool UseHardCuts=false, float BTagCut=0.0);
    virtual ~HWWmbbObs();
    ClassDefOverride(HWWmbbObs, 1);
    std::string getBTagName();
    std::string getBTagWP();
    float getBTagCut();
    float getPtCut();
    bool getUseOtherJets();
    bool getUseHardCuts();
    void setBTagName(std::string BTagName, std::string BTagWP);
    void setBTagCut(float BTagCut);
    void setPtCut(float PtCut);
    void setUseOtherJets(bool UseOtherJets);
    void setUseHardCuts(bool UseHardCuts);
    
private:
    
    /// The name of the b-tag variable
    std::string m_bTagVarName;
    // Working Point name
    std::string m_OperatingPoint;
    /// The cut value
    float m_ptCut;
    /// Flag to say that we should also look at the other sub-threshold jets
    bool m_useOtherJets;
    /// Flag to do hard cuts to allow for custom working points.  (Only supports MV2 currently)
    bool m_useHardCuts;
    float m_bTagCut;
    
};

#endif

