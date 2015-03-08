#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // init video input
    vidInput.initGrabber(CAM_WIDTH,CAM_HEIGHT);
    vidInput.setUseTexture(true);
    
    // window setup
    ofSetWindowShape(SCREEN_WIDTH, SCREEN_HEIGHT);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0,0,0);
    
    // allocate stuff
    colorImg.allocate(CAM_WIDTH, CAM_HEIGHT);
    grayImg.allocate(CAM_WIDTH, CAM_HEIGHT);
    
    choosing_img = false;
    chosen_img = false;

    
//    #ifdef _USE_LIVE_VIDEO
//        vidGrabber.setVerbose(true);
//        vidGrabber.initGrabber(320,240);
//    #else
//        vidPlayer.loadMovie("cards_01.mov");
//        vidPlayer.play();
//    #endif
//        
//    colorImg.allocate(320,240);
//    grayImage.allocate(320,240);
//    grayBg.allocate(320,240);
//    grayDiff.allocate(320,240);
//    
//    bLearnBakground = true;
//    threshold = 80;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int i;
    
    vidInput.update();
    if(vidInput.isFrameNew())
    {
        // get camera img into iplimage
        colorImg.setFromPixels(vidInput.getPixels(), CAM_WIDTH, CAM_HEIGHT);
        
        if (chosen_img) {
            grayImg = colorImg;
            detector.setImageSearch(grayImg.getCvImage());
            detector.update();
        }
        
        
    } 

//    ofBackground(100,100,100);
//    
//    bool bNewFrame = false;
//    
//    #ifdef _USE_LIVE_VIDEO
//        vidGrabber.update();
//           bNewFrame = vidGrabber.isFrameNew();
//    #else
//        vidPlayer.update();
//        bNewFrame = vidPlayer.isFrameNew();
//    #endif
//        
//    if (bNewFrame){
//            
//        #ifdef _USE_LIVE_VIDEO
//                colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
//        #else
//                colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
//        #endif
//                
//        grayImage = colorImg;
//        if (bLearnBakground == true){
//            grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
//            bLearnBakground = false;
//        }
//        
//        // take the abs value of the difference between background and incoming and then threshold:
//        grayDiff.absDiff(grayBg, grayImage);
//        grayDiff.threshold(threshold);
//        
//        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
//        // also, find holes is set to true so we will get interior contours as well....
//        contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
//    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0,0,0);
    
    ofSetColor(255, 255, 255);
    
    // camera image
    vidInput.draw(0, 0);
    
    // draw a rectanlge around the current selection
    if (choosing_img) {
        int x = mouseX;
        int y = mouseY;
        
        ofNoFill();
        ofRect(x_start < x ? x_start : x,
               y_start < y ? y_start : y,
               abs(x_start - x),
               abs(y_start - y));
        
    }
    
    if (chosen_img) {
        
        ofPushMatrix();
        ofTranslate(CAM_WIDTH, 0, 0);
        testImg.draw(0, 0);
        ofPopMatrix();
        
        ofSetColor(200, 20, 50);
        
        ofLine(detector.dst_corners[0].x, detector.dst_corners[0].y,
               detector.dst_corners[1].x, detector.dst_corners[1].y);
        
        ofLine(detector.dst_corners[2].x, detector.dst_corners[2].y,
               detector.dst_corners[1].x, detector.dst_corners[1].y);
        
        ofLine(detector.dst_corners[2].x, detector.dst_corners[2].y,
               detector.dst_corners[3].x, detector.dst_corners[3].y);
        
        ofLine(detector.dst_corners[0].x, detector.dst_corners[0].y,
               detector.dst_corners[3].x, detector.dst_corners[3].y);
        
    }

//    // draw the incoming, the grayscale, the bg and the thresholded difference
//    ofSetHexColor(0xffffff);
//    colorImg.draw(20,20);
//    grayImage.draw(360,20);
//    grayBg.draw(20,280);
//    grayDiff.draw(360,280);
//    
//    // then draw the contours:
//    
//    ofFill();
//    ofSetHexColor(0x333333);
//    ofRect(360,540,320,240);
//    ofSetHexColor(0xffffff);
//    
//    // we could draw the whole contour finder
//    //contourFinder.draw(360,540);
//    
//    // or, instead we can draw each blob individually from the blobs vector,
//    // this is how to get access to them:
//    for (int i = 0; i < contourFinder.nBlobs; i++){
//        contourFinder.blobs[i].draw(360,540);
//        
//        // draw over the centroid if the blob is a hole
//        ofSetColor(255);
//        if(contourFinder.blobs[i].hole){
//            ofDrawBitmapString("hole",
//                               contourFinder.blobs[i].boundingRect.getCenter().x + 360,
//                               contourFinder.blobs[i].boundingRect.getCenter().y + 540);
//        }
//    }
//    
//    // finally, a report:
//    ofSetHexColor(0xffffff);
//    stringstream reportStr;
//    reportStr << "bg subtraction and blob detection" << endl
//    << "press ' ' to capture bg" << endl
//    << "threshold " << threshold << " (press: +/-)" << endl
//    << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
//    ofDrawBitmapString(reportStr.str(), 20, 600);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   
    switch (key){
        case 's':
            vidInput.videoSettings();
            break;
        case '1':
            break;
        case '2':
            break;
            
        case 'b':
            break;
            
    }
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
    
    // start a rectangle selection
    if(!choosing_img)
    {
        choosing_img = true;
        x_start = x;
        y_start = y;
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
   
    // end the rectangle selection
    if (choosing_img) {
        choosing_img = false;
        x_end = x;
        y_end = y;
        
        if(x_start > x_end)
            std::swap(x_start, x_end);
        if(y_start > y_end)
            std::swap(y_start, y_end);
        
        int w = x_end - x_start;
        int h = y_end - y_start;
        
        cvSetImageROI(colorImg.getCvImage(),
                      cvRect(x_start,
                             y_start,
                             w, h));
        
        if (testImg.bAllocated) {
            testImg.clear();
            testGrayImg.clear();
        }
        testImg.allocate(w, h);
        testGrayImg.allocate(w, h);
        testImg = colorImg;
        testGrayImg = testImg;
        cvResetImageROI(colorImg.getCvImage());
        
        detector.setImageTemplate(testGrayImg.getCvImage());
        chosen_img = true;
    }

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
