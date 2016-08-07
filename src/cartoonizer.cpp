#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <string>
#include <string.h>

// The recipe of GIMP/Artistic Filters/Photocopy:
// http://www.imagemagick.org/discourse-server/viewtopic.php?t=14441
// * Mask radius = radius of pixel neighborhood for intensity comparison
// * Threshold = relative intensity difference which will result in darkening
// * Ramp = amount of relative intensity difference before total black

cv::Mat
performGimpPhotocopyFilter( const cv::Mat& image, int maskRadius, int treshold, int ramp ) {
   int blurRadius = maskRadius / 3;

   cv::Mat gray( image.size(), CV_8U);
   cv::cvtColor( image, gray, CV_BGR2GRAY );

   cv::Mat boxFiltered( gray.size(), gray.type() );
   cv::blur( gray, boxFiltered, cv::Size(2 * blurRadius + 1, 2 * blurRadius + 1) ); 

   return boxFiltered;
}

int main( int argc, char** argv )
{
   if( argc != 2) {
      std::cout <<"USAGE: " << std::string(basename(argv[0])) << " <filename>" << std::endl;
      return -1;
   }

   cv::Mat image;
   image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

   if( !image.data ) {
      std::cout <<  "Cannot not open image" << std::endl;
      return -1;
   }

   cv::Mat photocopy = performGimpPhotocopyFilter( image, 20, 100, 5 );

   cv::namedWindow( "Original", cv::WINDOW_NORMAL );
   cv::namedWindow( "Photocopy", cv::WINDOW_NORMAL );
   cv::imshow( "Original", image );
   cv::imshow( "Photocopy", photocopy );

   cv::waitKey(0);
   return 0;
}