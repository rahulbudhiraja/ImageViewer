#include "testApp.h"


float x_conversion=0.8,y_conversion=0.9375;
float scaling_factor=1.0,prevRotY=0,prevRotZ=0;;
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

	modelInitialPosition.x=-model.getPosition().x;
	modelInitialPosition.y=-model.getPosition().y/2;

}

//--------------------------------------------------------------
void testApp::update(){

	char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message=udpMessage;

	if(message.length()>0)
	std::cout<<"Message Received"<<message<<"\n\n";

	if(message!="")
	{
		vector<string> components= ofSplitString(message,",");
		
		if(components[0]=="Translation")
		{
			;
			/*receivedPosition.x=ofToFloat(components[2]);
			receivedPosition.y=ofToFloat(components[4]);

			cout<<receivedPosition.x<<"  "<<receivedPosition.y;*/

	    }
		else if(components[0]=="Scaling Up"||components[0]=="Scaling Down")
			scaling_factor=ofToFloat(components[1]);
		
		else if(components[0]=="Rotate")
		{
			if(components[1]=="Z")
				receivedRotation.y+=ofToFloat(components[2])/100;
			if(components[1]=="Y")
				receivedRotation.x+=ofToFloat(components[2])/150;

		}

}
}
 

float Y=10;
//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0);


	cam.begin();	
	ofPushMatrix();
	    
	ofRotateY(receivedRotation.y);
	ofRotateX(receivedRotation.x);	
	ofTranslate(-model.getPosition().x,-model.getPosition().y/2,0);
		//ofTranslate( receivedPosition.y*y_conversion,receivedPosition.x*x_conversion, 0);
	

	model.drawFaces();
		
		
		model.setScale(scaling_factor,scaling_factor,scaling_factor);

    ofPopMatrix();
	cam.end();
	



	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	ofSetFullscreen(true);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key=='r')
		receivedPosition.x=receivedPosition.y=0;
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