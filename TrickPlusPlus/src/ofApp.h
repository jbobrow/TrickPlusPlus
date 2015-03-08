#pragma once

#include "ofMain.h"

#include "pkmDetector.h"

#include "ofxOpenCv.h"
#include "ofShader.h"

#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
// otherwise, we'll use a movie file

const int CAM_WIDTH = 320;
const int CAM_HEIGHT = 240;
const int SCREEN_WIDTH = CAM_WIDTH*2;
const int SCREEN_HEIGHT = CAM_HEIGHT + 75;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofVideoGrabber			vidInput;
        
        ofxCvColorImage			colorImg, testImg;
        ofxCvGrayscaleImage		grayImg, testGrayImg;
        
        int						x_start, x_end, y_start, y_end;
        bool					choosing_img, chosen_img;
        pkmDetector				detector;
        int						detection;

		
//        #ifdef _USE_LIVE_VIDEO
//                  ofVideoGrabber 		vidGrabber;
//        #else
//                  ofVideoPlayer 		vidPlayer;
//        #endif
//            
//        ofxCvColorImage			colorImg;
//        
//        ofxCvGrayscaleImage 	grayImage;
//        ofxCvGrayscaleImage 	grayBg;
//        ofxCvGrayscaleImage 	grayDiff;
//        
//        ofxCvContourFinder 	contourFinder;
//            
//        int 				threshold;
//        bool				bLearnBakground;

};
