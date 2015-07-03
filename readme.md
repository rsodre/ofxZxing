[kylemcdonald's ofxZxing](https://github.com/kylemcdonald/ofxZxing) only works on OSX and iOS, since those are the platforms for which he includes ZXing as a static library. I couldn't find the source code for whichever version of ZXing he used, so I modified the addon to use the [lastest C++ version](https://github.com/glassechidna/zxing-cpp). Since there are a couple of minor diferences between this one and the one Kyle used, I had to change the addon source files a bit (mainly changing pointer types to LLVM's ArrayRef).

If the static libraries included don't work on your platform, you can compile them natively following the instructions on the zxing-cpp repo, and then link against those files.
