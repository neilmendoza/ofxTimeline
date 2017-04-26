/**
 * ofxTimeline
 * openFrameworks graphical timeline addon
 *
 * Copyright (c) 2011-2012 James George
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/
 * http://jamesgeorge.org + http://flightphase.com
 * http://github.com/obviousjim + http://github.com/flightphase
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxTLKeyframes.h"

enum ofxTLLFOType {
	OFXTL_LFO_TYPE_SINE  = 0,
	OFXTL_LFO_TYPE_NOISE = 1,
};

//custom keyframe container
//inherits time and value from the super class
class ofxTLLFOKey : public ofxTLKeyframe {
  public:
	//an example of how to add more information into this keyframe
	//just make some random colors
	ofxTLLFOType type;
	float phaseShift; //in millis
    bool  phaseMatch;
	float amplitude; 
	float frequency;
	float seed; // for noise
	float center; // 0 is middle
	float freqDeviation;
	bool interpolate;
    bool expInterpolate;
};

//Just a simple useless random color keyframer
//to show how to create a custom keyframer
class ofxTLLFO : public ofxTLKeyframes {
  public:
	ofxTLLFO();
	virtual ~ofxTLLFO();

	//draw your keyframes
	//some default style is done before this
	virtual void draw();
	virtual void drawModalContent();
	//you can implement custom behavior here, but can get tricky
	//with when to call the super class.
	//see some of the other tracks for interesting patterns on how to
	//extend default interaction behavior
	virtual bool mousePressed(ofMouseEventArgs& args, long millis);
	virtual bool mouseMoved(ofMouseEventArgs& args, long millis);
	virtual bool mouseDragged(ofMouseEventArgs& args, long millis);
	virtual bool mouseReleased(ofMouseEventArgs& args, long millis);
	
	//keys pressed events, and nuding from arrow keys with normalized nudge amount 0 - 1.0
	virtual bool keyPressed(ofKeyEventArgs& args);
	
	//time range contains MIN and MAX time in milliseconds
	//valueRange is 0 at the bottom of the track, and 1 at the top
	//if you have anything other than small dots keyframes you'll want to override
	//the default behavior
    virtual void regionSelected(ofLongRange timeRange, ofRange valueRange);

	//return a custom name for this keyframe
	virtual string getTrackType() const;
	static constexpr const char* TRACK_TYPE = "LFO";

  protected:
	
	virtual float interpolateValueForKeys(ofxTLKeyframe* start,ofxTLKeyframe* end, unsigned long long sampleTime);
	virtual float evaluateKeyframeAtTime(ofxTLKeyframe* key, unsigned long long sampleTime, bool firstKey = false);

	
	virtual ofxTLKeyframe* keyframeAtScreenpoint(ofVec2f p);
	//always return the type for your track, in our case ofxTLEmptyKeyframe;
	//this will enusre that all keyframe objects passed to this class are of this type
	virtual ofxTLKeyframe* newKeyframe();
	
	//load this keyframe out of xml, which is alraedy pushed to the right level
	//only need to save custom properties that our subclass adds
	virtual void restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);
	//save custom properties into the xml
    virtual void storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);

	//responde to right clicks on keyframes
    virtual void selectedKeySecondaryClick(ofMouseEventArgs& args);
	
	//you can responde to a keyframe about to be killed with this function right before the parent class deletes it
	virtual void willDeleteKeyframe(ofxTLKeyframe* keyframe);

	int rectWidth;
	int rectHeight;
	bool drawingLFORect;
	ofRectangle lfoRect;
	ofRectangle sineTypeRect;
	ofRectangle noiseTypeRect;
	ofRectangle phaseShiftRect;
	ofRectangle amplitudeRect;
	ofRectangle frequencyRect;
	ofRectangle seedRect;
	ofRectangle centerRect;
	ofRectangle interpolateRect;
    ofRectangle expInterpolateRect;
//    ofRectangle phaseMatchRect;
	ofRectangle* mouseDownRect;
	float* editingParam;
	float editingStartValue;
	ofRange editingRange;
	float editingSensitivity;
	float editingExponent;
	float editingClickX;
	bool draggedValue;
	
};
