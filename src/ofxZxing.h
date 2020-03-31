#pragma once

#include "Result.h"
#include "ofPixels.h"

namespace ofxZxing {

	// returns the first decoded QR
	Result decode(ofPixels& pixels, bool adaptive = true);
	
	// returns all decoded QRs
	std::vector<Result> decodeMultiple(ofPixels& pixels, bool adaptive = true);

	// returns all ocurrences of first QR to have a minimun match count
	std::vector<Result> decodeSingleFromMultiple(ofPixels& pixels, int minimumResults = 2, bool adaptive = true);
	

}
