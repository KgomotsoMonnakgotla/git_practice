//
//  Mbb.cpp
//  kg
//
//  Created by Kgomotso Monnakgotla on 4/26/19.
//  Copyright © 2019 Kgomotso Monnakgotla. All rights reserved.
//

#include "Mbb.hpp"
#include "HWWAnalysisCode/HWWBTagCounterObs.h"
#include <limits>
// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
ClassImp(HWWmbbObs)

//______________________________________________________________________________________________

HWWmbbObs::HWWmbbObs(){
    // default constructor
    DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
/* example block:
 //#include "xAODParticleEvent/CompositeParticleContainer.h"
 */
#include "xAODBTaggingEfficiency/BTaggingSelectionTool.h"

//______________________________________________________________________________________________

std::string HWWmbbObs::getBTagName() {
    return m_bTagVarName;
}

std::string HWWmbbObs::getBTagWP() {
    return m_OperatingPoint;
}

float HWWmbbObs::getPtCut() {
    return m_ptCut;
}

bool HWWmbbObs::getUseOtherJets() {
    return m_useOtherJets;
}

bool HWWmbbObs::getUseHardCuts() {
    return m_useHardCuts;
}

float HWWmbbObs::getBTagCut() {
    return m_bTagCut;
}
//______________________________________________________________________________________________

void HWWmbbObs::setBTagName(std::string BTagName, std::string BTagWP) {
    m_bTagVarName = BTagName;
    m_OperatingPoint = BTagWP;
}


void HWWmbbObs::setPtCut(float PtCut) {
    m_ptCut = PtCut;
}

void HWWmbbObs::setUseOtherJets(bool UseOtherJets) {
    m_useOtherJets = UseOtherJets;
}

void HWWmbbObs::setUseHardCuts(bool UseHardCuts) {
    m_useHardCuts = UseHardCuts;
}

void HWWmbbObs::setBTagCut(float BTagCut) {
    m_bTagCut = BTagCut;
    m_useHardCuts = true;
}

//______________________________________________________________________________________________
double HWWmbbObs::getValue() const {
    // value retrieval function, called on every event for every cut and histogram
    DEBUGclass("entering function");
    
    // the TQEventObservable only works in an ASG RELEASE, hence
    // we encapsulate the implementation in an ifdef/ifndef block
#ifndef HAS_XAOD
#warning "using plain ROOT compilation scheme - please add an ASG Analysis Release in order to use this feature!"
    return std::numeric_limits<double>::quiet_NaN();
#else
    const xAOD::CompositeParticleContainer *cand = 0;
    if(!this->fEvent->retrieve(cand, this->mContName.Data()).isSuccess()){
        DEBUGclass("failed to retrieve candidates!");
        return false;
    }
    
    // Get the event candidate from the container
    const xAOD::CompositeParticle *Evt = cand->at(0);
    
    
    
    
    // Get the number of b-tags from the nominally-selected jets
   // Get the invariant mass of the bjets
  //  TLorentzVector myBjets1;
   // TLorentzVector myBjets2;
    std::vector<double> massbjet;
    for ( size_t i=0; i<Evt->nParts(); ++i ){
        const xAOD::IParticle* part = Evt->part(i);
        if ( part->type() != xAOD::Type::Jet ) continue;
        const xAOD::Jet* jet = static_cast<const xAOD::Jet*>(part);
        if ( std::abs( jet->eta() ) > 2.5 ) continue;
        if ( jet->pt() < m_ptCut ) continue;
        
        if (m_useHardCuts) {
            const float tagWeight = jet->btagging()->auxdata<double>(m_bTagVarName);
            DEBUGclass("Got other jet tagWeight of %f", tagWeight );
            if ( tagWeight > m_bTagCut )
                 massbjet.push_push(jet->m());
            
        } else{
            bool isBtagged = m_btagtool->accept(*jet);
            if ( isBtagged ) {
                //      nPassBTag += 1;
                      massbjet.push_push(jet->m());
            }
        }
        
    }

    if (m_useOtherJets) {
        for ( size_t i=0; i<Evt->nOtherParts(); ++i ){
            const xAOD::IParticle* part = Evt->otherPart(i);
            if ( part->type() != xAOD::Type::Jet ) continue;
            const xAOD::Jet* jet = static_cast<const xAOD::Jet*>(part);
            if ( std::abs( jet->eta() ) > 2.5 ) continue;
            if ( jet->pt() < m_ptCut ) continue;
            
            
            if (m_useHardCuts){
                const float tagWeight = jet->btagging()->auxdata<double>(m_bTagVarName);
                DEBUGclass("Got other jet tagWeight of %f", tagWeight );
                if ( tagWeight > m_bTagCut )
                    massbjet.push_push(jet->m());
            } else {
                bool isOtherBtagged = m_btagtool->accept(*jet);
                if ( isOtherBtagged ) {
                
                   massbjet.push_push(jet->m());
                }
            }
        }
        
    }
    double massbb = massbjet [0] + massbjet[1];
    DEBUGclass("Got %d mass-bb",massbb);
    return static_cast<double>(massbb);
#endif
}

//______________________________________________________________________________________________

bool HWWmbbObs::initializeSelf(){
    // initialize this observable
    // called once per sample (input file) so that the observable knows the name of the event candidate
    // will be EventEM or EventME in the case of DF analysis (depending on the current channel)
    TString ContName = "";
    if(!this->fSample->getTagString("~cand",ContName)) return false;
    this->mContName = "Event"+ContName;
    
    using namespace asg::msgUserCode;
    
    if( m_wasInitialized || m_useHardCuts ) return true;
    
    // Initialize BTaggingSelectionTool
    if( m_btagtool.empty() ) {
        TString toolName = "HWWBTagTool";
        if( asg::ToolStore::contains<BTaggingSelectionTool>(toolName.Data()) ) {
            m_btagtool = dynamic_cast<IBTaggingSelectionTool*>(asg::ToolStore::get(toolName.Data()));
        }
        else {
            IBTaggingSelectionTool* tool = new BTaggingSelectionTool(toolName.Data());
            DEBUGclass("created new tool '%s'",tool->name().c_str());
            m_btagtool = tool;
            ANA_CHECK_THROW(asg::setProperty( tool, "MaxEta", 2.5 ));
            ANA_CHECK_THROW(asg::setProperty( tool, "MinPt", m_ptCut ));
            ANA_CHECK_THROW(asg::setProperty( tool, "JetAuthor", "AntiKt4EMTopoJets" ));
            ANA_CHECK_THROW(asg::setProperty( tool, "TaggerName", m_bTagVarName ));
            ANA_CHECK_THROW(asg::setProperty( tool, "FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2017-21-13TeV-MC16-CDI-2018-06-29_v1.root" ));
            ANA_CHECK_THROW(asg::setProperty( tool, "OperatingPoint", m_OperatingPoint ));
            
            //if( !m_btagtool->initialize() ) throw std::runtime_error("Failed to initialise BTaggingSelectionTool");
            ANA_CHECK_THROW(m_btagtool->initialize());
        }
    }
    else {
        throw std::runtime_error("Encountered non-empty BTag tool handle. Most likely this was already set, otherwise something went horribly wrong...");
    }
    m_wasInitialized = true;
    
    DEBUGclass("initializing");
    return true;
