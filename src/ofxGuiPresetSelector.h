
// ofxGuiPresetSelector.h
// Nicola Pisanti, MIT License, 2016

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofxGuiPresetSelector {
    
public:
    ofxGuiPresetSelector();

    // add a gui for preset saving
    void add( ofxPanel & gui );

    // adds and activate key switch
    void add( ofxPanel & gui, initializer_list<int> keysList );

    
    // save to a preset
    void save( int guiIndex, int presetIndex ); 
    void save( string guiName, int presetIndex );
    
    // loads an already saved preset 
    void load( int guiIndex, int presetIndex ); 
    void load( string guiName, int presetIndex );
    
    // get the last loaded preset
    int getPresetIndex( int guiIndex ) const;
    int getPresetIndex( string guiName ) const;
    
    // set the key you have to hold for saving
    void setModeKey( int key );

    void keyPressed( ofKeyEventArgs& eventArgs);
    void keyReleased( ofKeyEventArgs& eventArgs );

private:
    
    int getGuiIndex(string name ) const;
    string presetName( string guiName, int presetIndex );

    vector<ofxPanel*>   guis;
    vector<int>         lastIndices;

    void addKeysListeners();
    
    vector<vector<int>> keys;
    bool                keysNotActivated;
    int                 modeKey;
    bool                bKeySave;
    
};
