#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("ofxGuiSelector example");
    ofDisableAntiAliasing();
    
    gui.setup("", "squares.xml", 10, 10);
    gui.setName("squares"); // it is really important to set the name as it will be used as base for the .xml preset files
                            // remember to give each ofxPanel an unique name
    gui.add( numSquares.set("num squares", 1, 1, 24) );
    gui.add( separation.set("separation", 5, 1, 100) );
    gui.add( squareSide.set("square side", 50, 5, 200) );
    
    selector.add( gui, { '1', '2', '3', '4', '5'} ); 
    // selector.add( gui, 6 ); // add without activating key switch, 6 presets
    // selector.add( anotherGui, {'q', 'w', 'e', 'r', 't', 'y'} ); // add another gui with other keys
    // selector.setModeKey( OF_KEY_TAB ); // change the key you have to hold for saving 
                                          // remember that the switch key change the keycodes
                                          // so it shouldn't work

    // remember to have a bin/data folder in your app directories
    // the first time you save you probably have to press the key twices, the first it just create the .xml file
    
    // x, y, button size
    selector.setPosition( 20, 360, 50 );

    selector.load( 1 ); // load the second preset of the first added gui
    //selector.load( 0, 1 ); // load the first preset of the second added gui

    // remember to have a bin/data folder in your app directories
    // there are alredy 3 saved presets in the bin/data folder of this example
    
}

//--------------------------------------------------------------
void ofApp::update(){
   

}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    
    gui.draw();

    ofSetColor(255, 95, 95);
    ofNoFill();
    ofPushMatrix();
        ofTranslate( 320, 50 );
        for( int i=0; i<numSquares; ++i){
            ofDrawRectangle(0, 0, squareSide, squareSide);
            ofTranslate( separation, separation );
        }
    ofPopMatrix();
        
    selector.draw(); // draws some minimalistic graphics to monitor the active preset
                     // when graphics are drawn you can also click on them for saving/loading
        
    string info = "press 1-5 for loading a preset, press CTRL+1-5 for saving presets\n";
    info += "or click on the selector buttons above\n";
    info += "the last button save the currently selected preset";
    ofDrawBitmapString( info , 20, ofGetHeight() - 40 );
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
