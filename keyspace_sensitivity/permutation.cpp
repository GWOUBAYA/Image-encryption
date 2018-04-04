#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const int MAX=1e4+79;

/**
  u is the control parameter for logistic chaotic map,also known as population rate
  Here u is taken 3.94
  x is the vector that contain the value generated by chaotic map
  The initial value of the logistic chaotic map is 0.4
*/

int main()
{
  Mat image,encImage1,encImage2,tempImage,diffImage;
  int i,l;
  double u1=3.94001,u2=3.94002,percenDiff,count=0;         
  vector<pair<double,int >> x1,x2;
  Vec<unsigned char, 3>  pixel,pixel1;


  image = imread("Image/sample_image_grey.jpg", 0 );
  if ( !image.data )
  {
    cout<<"No image data \n";
    return -1;
  }

  x1.push_back({0.400001,0});
  x2.push_back({0.400002,0});


  double temp;
  for (int i = 1; i <= 511; ++i){
    temp=u1*x1[i-1].first*(1-x1[i-1].first);
    x1.push_back({temp,i});
  }

  for (int i = 1; i <= 511; ++i){
    temp=u2*x2[i-1].first*(1-x2[i-1].first);
    x2.push_back({temp,i});
  }

  sort(x1.begin(), x1.end());
  sort(x2.begin(), x2.end());

  imshow("Original image", image);
  waitKey(0);

  i=0;
  tempImage=image;
  for(int r = 0; r < image.rows; ++r) {
    for(int c = 0; c < image.cols; ++c) {
      if(i>511)
        i=0;
      int temps= x1[i].second;

      pixel= image.at<Vec3b>(r,temps);
      image.at<Vec3b>(r,temps)=image.at<Vec3b>(r,c);
      image.at<Vec3b>(r,c)=pixel;

      i++;
    }
  }

  encImage1=image;
  image=tempImage;

  i=0;
  tempImage=image;
  for(int r = 0; r < image.rows; ++r) {
    for(int c = 0; c < image.cols; ++c) {
      if(i>511)
        i=0;
      int temps= x2[i].second;

      pixel= image.at<Vec3b>(r,temps);
      image.at<Vec3b>(r,temps)=image.at<Vec3b>(r,c);
      image.at<Vec3b>(r,c)=pixel;

      i++;
    }
  }

  encImage2=image;
  image=tempImage;

  for(int r = 0; r < image.rows; ++r) {
    for(int c = 0; c < image.cols; ++c) {
      pixel= encImage1.at<Vec3b>(r,c);
      pixel1= encImage2.at<Vec3b>(r,c);

      if(pixel[0] ==pixel[0])
        count +=1;
      if(pixel[1] ==pixel[1])
        count +=1;
      if(pixel[2] ==pixel[2])
        count +=1;
    }
  }

  percenDiff=count/(512*512*3)*100;
  cout<<"The first image and second encrypted image are "<<percenDiff<<"% different"<<endl;

  diffImage = encImage1 - encImage2;

  imwrite("Image/keyspace_sensitivity/perm_diff_1.jpg",encImage1);
  imshow("Encrypted test image 1", encImage1);
  waitKey(0);

  imwrite("Image/keyspace_sensitivity/perm_diff_2.jpg",encImage2);
  imshow("Encrypted test image 2", encImage2);
  waitKey(0);


  imwrite("Image/keyspace_sensitivity/difference_perm.jpg",diffImage);
  imshow("difference Image of the two encrypted image", diffImage);
  waitKey(0);

  return 0;

}