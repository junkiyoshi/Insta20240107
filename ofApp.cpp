#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	vector<glm::vec2> target_list;
	for (int i = 0; i < 4; i++) {

		auto deg = ofMap(ofNoise(ofGetFrameNum() * 0.015), 0, 1, -360 * 2, 360 * 2);
		deg += i * 90;
		target_list.push_back(glm::vec2(150 * cos(deg * DEG_TO_RAD), 150 * sin(deg * DEG_TO_RAD)));
	}

	for (auto& target : target_list) {

		ofDrawCircle(target, 5);
	}

	ofNoFill();
	ofBeginShape();
	ofVertices(target_list);
	ofEndShape(true);

	for (int deg = 0; deg < 360; deg += 10) {

		int x = 300 * cos(deg * DEG_TO_RAD);
		int y = 300 * sin(deg * DEG_TO_RAD);

		auto target = target_list[deg / 90];
		this->draw_arrow(glm::vec2(x, y), target, 18, ofColor(255));
	}

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto translate_location = target - glm::vec2(size * 3 * cos(angle), size * 3 * sin(angle));
	auto distance = glm::distance(translate_location, location);

	ofPushMatrix();
	ofTranslate(translate_location);

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25);

	ofEndShape();

	ofPopMatrix();

	ofDrawCircle(location, 5);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}