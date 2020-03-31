#include "ofxZxing.h"

#include "ofPixelsBitmapSource.h"

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/multi/qrcode/QRCodeMultiReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/Exception.h>

namespace ofxZxing {
	
	using namespace std;
	using namespace zxing;
	using namespace zxing::qrcode;
	
	Result decode(ofPixels& pixels, bool adaptive)
	{
		try {
			Ref<ofPixelsBitmapSource> source(new ofPixelsBitmapSource(pixels));
			
			Ref<Binarizer> binarizer(NULL);
			if(adaptive) {
				binarizer = new HybridBinarizer(source);
			} else {
				binarizer = new GlobalHistogramBinarizer(source);
			}
			
			Ref<BinaryBitmap> image(new BinaryBitmap(binarizer));
			QRCodeReader reader;
			DecodeHints hints;
			hints.addFormat(BarcodeFormat::QR_CODE);
			hints.setTryHarder(true);
			
			//  Ref<Result> decode(Ref<BinaryBitmap> image, DecodeHints hints);
			Ref<zxing::Result> qr(reader.decode(image, hints));
			
			string text = qr->getText()->getText();
			vector<ofVec2f> points;
			ArrayRef< Ref<ResultPoint> > resultPoints = qr->getResultPoints();
			for(int i = 0; i < resultPoints->size(); i++) {
				Ref<ResultPoint> cur = resultPoints[i];
				points.push_back(ofVec2f(cur->getX(), cur->getY()));
			}
			return Result(text, points);
		} catch (zxing::Exception& e) {
			//cerr << "Error: " << e.what() << endl;
			return Result();
		}
	}
	
	std::vector<Result> decodeMultiple(ofPixels& pixels, bool adaptive)
	{
		std::vector<Result> result;
		try {
			Ref<ofPixelsBitmapSource> source(new ofPixelsBitmapSource(pixels));
			
			Ref<Binarizer> binarizer(NULL);
			if(adaptive) {
				binarizer = new HybridBinarizer(source);
			} else {
				binarizer = new GlobalHistogramBinarizer(source);
			}
			
			Ref<BinaryBitmap> image(new BinaryBitmap(binarizer));
			multi::QRCodeMultiReader reader;
			DecodeHints hints;
			hints.addFormat(BarcodeFormat::QR_CODE);
			hints.setTryHarder(true);
			std::vector<Ref<zxing::Result>> qrs = reader.decodeMultiple(image, hints);
			for(auto it = qrs.begin() ; it != qrs.end() ; ++it)
			{
				const Ref<zxing::Result>& qr = *it;
				string text = qr->getText()->getText();
				vector<ofVec2f> points;
				ArrayRef< Ref<ResultPoint> > resultPoints = qr->getResultPoints();
				for(int i = 0; i < resultPoints->size(); i++) {
					Ref<ResultPoint> cur = resultPoints[i];
					points.push_back(ofVec2f(cur->getX(), cur->getY()));
				}
				result.push_back( Result(text, points) );
			}
		} catch (zxing::Exception& e) {
			//cerr << "Error: " << e.what() << endl;
		}
		return result;
	}
	
	std::vector<Result> decodeSingleFromMultiple(ofPixels& pixels, int minimumResults, bool adaptive)
	{
		std::vector<Result> results( decodeMultiple(pixels, adaptive) );
		
		std::map<std::string, std::vector<Result>> sortedResults;
		for(auto it = results.begin() ; it != results.end() ; ++it)
		{
			auto key = it->getText();
			auto& values = sortedResults[key];
			values.push_back( *it );
		}

		for(auto it = sortedResults.begin() ; it != sortedResults.end() ; ++it)
		{
			auto key = it->first;
			auto& values = it->second;
			if( values.size() >= minimumResults)
				return values;
		}

		return std::vector<Result>();
	}
}
