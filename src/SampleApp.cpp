#include "CinderOpenCV.h"

#include "cinder/Capture.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "spdlog/spdlog.h"

using namespace ci;
using namespace ci::app;

class SampleApp : public App
{
  public:
	void setup();
	void update();
	void draw();

	CaptureRef mCapture;
	gl::TextureRef mTexture;
};

void SampleApp::setup()
{
	try
	{
		mCapture = Capture::create( 640, 480 );
		mCapture->start();
	}
	catch ( ... )
	{
		console() << "Failed to initialize capture" << std::endl;
	}

	spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
	spdlog::shutdown();
}

void SampleApp::update()
{
	if ( mCapture && mCapture->checkNewFrame() )
	{
		cv::Mat input( toOcv( *mCapture->getSurface(), CV_8UC1 ) ), output;

		cv::Sobel( input, output, CV_8UC1, 1, 0 );

		mTexture = gl::Texture::create( fromOcv( output ), gl::Texture::Format().loadTopDown() );
	}
}

void SampleApp::draw()
{
	gl::clear();
	if ( mTexture )
	{
		gl::draw( mTexture );
	}
}

CINDER_APP( SampleApp, RendererGl )
