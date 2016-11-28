
// ofxGuiPresetSelector.h
// Nicola Pisanti, MIT License, 2016

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofxGuiPresetSelector {
    
public:
    ofxGuiPresetSelector();

    // add a gui for preset saving
    void add( ofxPanel & gui, int numPresets=8 );

    // adds and activate key switch
    void add( ofxPanel & gui, initializer_list<int> keysList );

    // save to a preset
    void save( int presetIndex, int guiIndex=0 ); 
    void save( int presetIndex, string guiName );
    
    // loads an already saved preset 
    void load( int presetIndex, int guiIndex=0 ); 
    void load( int presetIndex, string guiName );
    
    // get the last loaded preset
    int getPresetIndex( int guiIndex ) const;
    int getPresetIndex( string guiName ) const;
    
    // set the key you have to hold for saving, default is OF_KEY_CONTROL
    void setModeKey( int key );

    // set graphics position
    // cellsize is the size of each preset button
    void setPosition( int x, int y, int cellSize );    

    // draw some info, when the gui is drawn you can also click on the button to change / save presets
    void draw();
    void draw( int x, int y, int cellSize );
    
private:
    int getGuiIndex(string name ) const;
    string presetName( string guiName, int presetIndex );

    vector<ofxPanel*>   guis;
    vector<int>         lastIndices;
    vector<int>         presets;

    void addKeysListeners();
    void keyPressed( ofKeyEventArgs& eventArgs);
    void keyReleased( ofKeyEventArgs& eventArgs );
    
    vector<vector<int>> keys;
    bool                keysNotActivated;
    int                 modeKey;
    bool                bKeySave;
    
    int     x;
    int     y;
    int     cellSize;
    
    bool    lastMouseButtonState;
    void    mousePressed( int x, int y );
    
};
