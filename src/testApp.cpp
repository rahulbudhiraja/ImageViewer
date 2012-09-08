#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){


	 // we need GL_TEXTURE_2D for our models coords.
    ofDisableArbTex();

    if(model.loadModel("astroBoy_walk.dae",true)){
    	model.setAnimation(0);
    	model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.75 , 0);
    	//model.createLightsFromAiModel();
    	//model.disableTextures();
    	//model.disableMaterials();

    	mesh = model.getMesh(0);
    	position = model.getPosition();
    	normScale = model.getNormalizedScale();
    	scale = model.getScale();
    	sceneCenter = model.getSceneCenter();
    	material = model.getMaterialForMesh(0);
        tex = model.getTextureForMesh(0);
    }

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	glEnable(GL_DEPTH_TEST);

    //some model / light stuff
    glShadeModel(GL_SMOOTH);
    light.enable();
    ofEnableSeparateSpecularLight();
		//cam.setDistance(100);

	udpConnection.Create();
	udpConnection.Bind(12002);
	udpConnection.SetNonBlocking(true);

}

//--------------------------------------------------------------
void testApp::update(){

	char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message=udpMessage;

	if(message.length()>0)
	std::cout<<"Message Received"<<message<<"\n\n";

	/*if(message!=""){
		stroke.clear();
		float x,y;
		vector<string> strPoints = ofSplitString(message,"[/p]");
		for(int i=0;i<strPoints.size();i++){
			vector<string> point = ofSplitString(strPoints[i],"|");
			if( point.size() == 2 ){
				x=atof(point[0].c_str());
				y=atof(point[1].c_str());
				stroke.push_back(ofPoint(x,y));
			}
		}
	}*/

}
 

float Y=10;
//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0);


	cam.begin();	
	ofPushMatrix();
	
		ofTranslate(-model.getPosition().x, -model.getPosition().y/2, 0);

		model.drawFaces();

    ofPopMatrix();
	cam.end();
	



	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	ofSetFullscreen(true);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	y=Y;
	Y++;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}