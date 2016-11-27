
// ofxGuiPresetSelector.cpp
// Nicola Pisanti, MIT License, 2016

#include "ofxGuiPresetSelector.h"

ofxGuiPresetSelector::ofxGuiPresetSelector(){
        
    modeKey = OF_KEY_CONTROL;
    keysNotActivated = true;
    bKeySave = false;
    
    guis.reserve(32);
    lastIndices.reserve(32);
    keys.reserve(32);

}


int ofxGuiPresetSelector::getGuiIndex( string name ) const {
    
    for( size_t i = 0; i<guis.size(); ++i ){
        if( guis[i]->getName() == name ){
            return i;
        }
    }
    
    return -1;
}


string ofxGuiPresetSelector::presetName( string guiName, int presetIndex ) {
    return (guiName + "_preset_" + ofToString(presetIndex) + ".xml" );
}


void ofxGuiPresetSelector::add( ofxPanel & gui ) {
    guis.push_back( &gui );
    lastIndices.push_back( 0 );
}


void ofxGuiPresetSelector::add( ofxPanel & gui, initializer_list<int> keysList ) {

    add( gui );
    keys.resize(guis.size());
    int i = guis.size() - 1;
    
    keys[i].reserve(keysList.size());
    
    for (const int & key : keysList) keys[i].push_back( key );

    if(keysNotActivated) addKeysListeners();
}
    
    
void ofxGuiPresetSelector::save( int guiIndex, int presetIndex ) {
    if(guiIndex>=0 && guiIndex<(int)guis.size()){
        guis[guiIndex]->saveToFile( presetName( guis[guiIndex]->getName(), presetIndex) );
    }
}

void ofxGuiPresetSelector::load( int guiIndex, int presetIndex ) {
    if(guiIndex>=0 && guiIndex<(int)guis.size()){
        guis[guiIndex]->loadFromFile( presetName( guis[guiIndex]->getName(), presetIndex) );
        lastIndices[guiIndex] = presetIndex;
    }
}
    
    
void ofxGuiPresetSelector::save( string guiName, int presetIndex ) {
    int guiIndex = getGuiIndex(guiName);
    
    if(guiIndex>=0 && guiIndex<(int)guis.size()){
        guis[guiIndex]->saveToFile( presetName( guiName, presetIndex) );
    }
}


void ofxGuiPresetSelector::load( string guiName, int presetIndex ) {
    int guiIndex = getGuiIndex(guiName);
    
    if(guiIndex>=0 && guiIndex<(int)guis.size()){
        guis[guiIndex]->loadFromFile( presetName( guiName, presetIndex) );
        lastIndices[guiIndex] = presetIndex;
    }
}


int ofxGuiPresetSelector::getPresetIndex( int guiIndex ) const {
    if(guiIndex>0 && guiIndex<(int)guis.size()){
        return lastIndices[guiIndex];
    }else{
        return -1;
    }    
}


int ofxGuiPresetSelector::getPresetIndex( string guiName )const {
    int guiIndex = getGuiIndex(guiName);
    
    if(guiIndex>0 && guiIndex<(int)guis.size()){
        return lastIndices[guiIndex];
    }else{
        return -1;
    }    
}


void ofxGuiPresetSelector::setModeKey( int key ){
    modeKey = key;
}


void ofxGuiPresetSelector::keyPressed( ofKeyEventArgs& eventArgs ) {
    
    const int & key = eventArgs.key;
    
    if(key == modeKey){
        bKeySave = true;
        return;
    } 
    
    for(size_t i=0; i<keys.size(); ++i){
        for(size_t k=0; k<keys[i].size(); ++k){
            if(key == keys[i][k]){
                
                if(bKeySave){
                    save(i, k);
                }else{
                    load(i, k);
                }
                
                return;
            }
        }   
    }
    
}


void ofxGuiPresetSelector::keyReleased( ofKeyEventArgs& eventArgs ) {
    if( eventArgs.key == modeKey) bKeySave = false;
}


void ofxGuiPresetSelector::addKeysListeners(){
    ofAddListener( ofEvents().keyPressed, this, &ofxGuiPresetSelector::keyPressed );
    ofAddListener( ofEvents().keyReleased, this, &ofxGuiPresetSelector::keyReleased );
    keysNotActivated = false;
}
