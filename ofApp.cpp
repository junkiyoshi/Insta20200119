#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->radius = 30;
	vector<glm::vec2> start_location_list;
	auto x_span = this->radius * sqrt(3);
	auto flg = true;
	for (float y = 0; y < ofGetHeight() + this->radius; y += this->radius * 1.5) {

		for (float x = 0; x < ofGetWidth() + this->radius; x += x_span) {

			glm::vec2 location;
			if (flg) {

				location = glm::vec2(x, y);
			}
			else {

				location = glm::vec2(x + (this->radius * sqrt(3) / 2), y);
			}

			start_location_list.push_back(location);
		}
		flg = !flg;
	}

	for (int i = 0; i < 15; i++) {

		int r = ofRandom(start_location_list.size());

		auto log_list = vector<glm::vec2>();
		log_list.push_back(start_location_list[r]);
		this->hexagon_list.push_back(log_list);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	auto span = this->radius * sqrt(3);
	for (auto& log_list : this->hexagon_list) {

		int r = ofRandom(6);
		int deg_start = r * 60;
		for (int deg = deg_start; deg < deg_start + 360; deg += 60) {

			auto tmp_location = log_list.back() + glm::vec2(span * cos(deg * DEG_TO_RAD), span * sin(deg * DEG_TO_RAD));
			if (tmp_location.x < 0 || tmp_location.x > ofGetWidth() + this->radius || tmp_location.y < 0 || tmp_location.y > ofGetHeight() + this->radius) {

				continue;
			}

			log_list.push_back(tmp_location);
			break;
		}

		while (log_list.size() > 20) {

			log_list.erase(log_list.begin());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& log_list : this->hexagon_list) {

		for (int i = 0; i < log_list.size(); i++) {

			vector<glm::vec2> vertices;
			for (auto deg = 90; deg < 450; deg += 60) {

				vertices.push_back(log_list[i] + glm::vec2(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD)));
			}

			ofFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}