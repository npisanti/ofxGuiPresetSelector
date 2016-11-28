
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
    
    lastMouseButtonState = false;

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


void ofxGuiPresetSelector::add( ofxPanel & gui, int numPresets ) {
    guis.push_back( &gui );
    lastIndices.push_back( 0 );
    presets.push_back(numPresets);
}


void ofxGuiPresetSelector::add( ofxPanel & gui, initializer_list<int> keysList ) {

    add( gui, keysList.size() );
    keys.resize(guis.size());
    int i = guis.size() - 1;
    
    keys[i].reserve(keysList.size());
    
    for (const int & key : keysList) keys[i].push_back( key );

    if(keysNotActivated) addKeysListeners();
    
}
    
    
void ofxGuiPresetSelector::save( int presetIndex, int guiIndex ) {
    if(guiIndex>=0 && guiIndex<(int)guis.size()){
        guis[guiIndex]->saveToFile( presetName( guis[guiIndex]->getName(), presetIndex) );
    }
}

void ofxGuiPresetSelector::load( int presetIndex, int guiIndex ) {
    if(guiIndex>=0 && guiIndex<(int)guis.size()){
        guis[guiIndex]->loadFromFile( presetName( guis[guiIndex]->getName(), presetIndex) );
        lastIndices[guiIndex] = presetIndex;
    }
}
    
    
void ofxGuiPresetSelector::save( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);
    
    if(guiIndex>=0 && guiIndex<(int)guis.size()){
        guis[guiIndex]->saveToFile( presetName( guiName, presetIndex) );
    }
}


void ofxGuiPresetSelector::load( int presetIndex, string guiName ) {
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
                    save( k, i);
                }else{
                    load( k, i );
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




void ofxGuiPresetSelector::setPosition( int x, int y, int cellSize ) {
    this->x = x;
    this->y = y;
    this->cellSize = cellSize;
}

void ofxGuiPresetSelector::draw( int x, int y, int cellSize ) {
    setPosition(x, y, cellSize);    
    draw();
}

void ofxGuiPresetSelector::draw( ) {
    
    if( !lastMouseButtonState && ofGetMousePressed() ){
        mousePressed( ofGetMouseX(), ofGetMouseY() );
    }
    lastMouseButtonState = ofGetMousePressed();
    
    ofPushMatrix();
        ofTranslate(x, y);
        for(size_t i=0; i<keys.size(); ++i){
            size_t k=0;
            for(; k<keys[i].size(); ++k){
                ofDrawRectangle( cellSize*k, cellSize*i, cellSize, cellSize );
                ofDrawBitmapString( ofToString((char)keys[i][k]), cellSize*k+8, cellSize*i+18 );
                if( lastIndices[i]==k ) ofDrawRectangle( cellSize*k+4, cellSize*i+4, cellSize-8, cellSize-8 );
            }
            for(; k<presets[i]; ++k){
                ofDrawRectangle( cellSize*k, cellSize*i, cellSize, cellSize );
                if( lastIndices[i]==k ) ofDrawRectangle( cellSize*k+4, cellSize*i+4, cellSize-8, cellSize-8 );
            }
            
            
            ofDrawRectangle( cellSize*k, cellSize*i, cellSize, cellSize );
            ofDrawCircle ( cellSize*k + cellSize/2, cellSize*i + cellSize/2, cellSize * 0.1f );
            ofDrawRectangle( cellSize*k + cellSize*0.24f, cellSize*i, cellSize*0.09f, cellSize*0.20f );
            ofDrawRectangle( cellSize*k + cellSize*0.18f, cellSize*i, cellSize*0.55f, cellSize*0.25f );
            
            
            k++;
            ofDrawBitmapString( guis[i]->getName(), cellSize*k+8, cellSize*i+18 );
        }
    ofPopMatrix();
}


void ofxGuiPresetSelector::mousePressed( int x, int y ) {

    x -= this->x;
    y -= this->y;

    int xIndex = x/cellSize;
    int yIndex = y/cellSize;

    xIndex = (x>0) ? xIndex : -1;
    yIndex = (y>0) ? yIndex : -1;
    
    if( yIndex >=0 &&  yIndex < (int)guis.size() ){
        if(xIndex>=0 && xIndex< presets[yIndex] ){
            //load
            load( xIndex, yIndex);
        }else if( xIndex == presets[yIndex]){
            // save
            save( lastIndices[yIndex], yIndex );
        }
    }
}  
