/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkVoronoiSegmentationRGBImageFilter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkVoronoiSegmentationRGBImageFilter_h
#define _itkVoronoiSegmentationRGBImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkVoronoiSegmentationImageFilterBase.h"
#include "itkImage.h"

namespace itk
{

/** \class VoronoiSegmentationRGBImageFilter
 * 
 * Segmentation of 2D RGB images using Voronoi Diagram.
 * This is not a standard 3 channel image filter, it also investigates the  
 * HSV color space information. from RGBHSV, the user can specify or by giving 
 * a prior binary mask, the algorithm will decide which 3 channels out of the 
 * 6 channels will be used for homogeneity testing. 
 * the homogeneity testing requires all the three testing channels to have the  
 * similar mean and variance value from the gold-standard in the sense that the 
 * difference will be under the tolerance value. 
 * 
 * Input parameters are: 
 * (1) Image data, in the format: itkImage<itkVector<PixelType,3>, 2>.
 * (2) Object statistics: mean and standard deviation
 * (3) Tolerance level for the classifier. This level is usually set
 *     around the mean and standard deviation values.
 *
 * These parameters can also be automatically set by providing a binary image prior. 
 *
 * Detailed information about this algorithm can be found in:
 *  " Semi-automated color segmentation of anatomical tissue,"
 *   C. Imelinska, M. Downes, and W. Yuan  
 *  Computerized Medical Imaging and Graphics, Vol.24, pp 173-180, 2000.
 *
 *
 * \ingroup HybridSegmentation 
 */
template <class TInputImage, class TOutputImage>
class VoronoiSegmentationRGBImageFilter:
public VoronoiSegmentationImageFilterBase<TInputImage,TOutputImage>
{

public:
  /** Standard class typedefs. */
  typedef VoronoiSegmentationRGBImageFilter       Self;
  typedef VoronoiSegmentationImageFilterBase<TInputImage,TOutputImage> Superclass;
  typedef SmartPointer <Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(VoronoiSegmentationRGBImageFilter,
               VoronoiSegmentationImageFilterBase);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Convenient typedefs. */
  typedef typename Superclass::BinaryObjectImage BinaryObjectImage;
  typedef typename Superclass::IndexList IndexList;
  typedef typename Superclass::InputImagePointer InputImagePointer;
  typedef Vector<float,6> RGBHCVPixel;
  typedef Image<RGBHCVPixel> RGBHCVImage;

  /** \todo Document. */
  void SetMeanPercentError(double x[6]);
  void SetVarPercentError(double x[6]);
  void GetMeanPercentError(double x[6]){for(int i=0;i<6;i++) x[i]=m_MeanPercentError[i];};
  void GetVarPercentError(double x[6]){for(int i=0;i<6;i++) x[i]=m_VarPercentError[i];};
  void GetMean(double x[6]){for(int i=0;i<6;i++) x[i]=m_Mean[i];};
  void GetVar(double x[6]){for(int i=0;i<6;i++) x[i]=m_Var[i];};
  void SetMean(double x[6]){for(int i=0;i<6;i++) m_Mean[i]=x[i];};
  void SetVar(double x[6]){for(int i=0;i<6;i++) m_Var[i]=x[i];};
  void GetMeanTolerance(double x[6]){for(int i=0;i<6;i++) x[i]=m_MeanTolerance[i];};
  void GetVarTolerance(double x[6]){for(int i=0;i<6;i++) x[i]=m_VarTolerance[i];};

  /** Maximum value of the RGB, needed for color space coversions.
   * default as 8 bit per channel, if it is different, need to be
   * set before doing anything. */
  itkSetMacro(MaxValueOfRGB,double);
  itkGetMacro(MaxValueOfRGB,double);

  /** Set the three channels to test the mean and var respectivley
   * 0:red, 1:green, 2:blue, 3:hue, 4:chroma, 5:value. */
  void SetTestMean(unsigned int t1,unsigned int t2,unsigned int t3){
    m_TestMean[0] = t1;
    m_TestMean[1] = t2;
    m_TestMean[2] = t3;
  }
  void SetTestVar(unsigned int t1,unsigned int t2,unsigned int t3){
    m_TestVar[0] = t1;
    m_TestVar[1] = t2;
    m_TestVar[2] = t3;
  }
  void GetTestMean(unsigned int x[3]){
    x[0]=m_TestMean[0];x[1]=m_TestMean[1];x[2]=m_TestMean[2];
  }
  void GetTestVar(unsigned int x[3]){
    x[0]=m_TestVar[0];x[1]=m_TestVar[1];x[2]=m_TestVar[2];
  }
  void TakeAPrior(BinaryObjectImage* aprior);

  void SetInput(InputImagePointer input); 

protected:
  VoronoiSegmentationRGBImageFilter();
  ~VoronoiSegmentationRGBImageFilter();


private:
  double m_Mean[6];
  double m_Var[6];  //actually it is the STD of the object. (sqrt(Var)).
  double m_MeanTolerance[6];
  double m_VarTolerance[6];
  double m_MeanPercentError[6];
  double m_VarPercentError[6];
  double m_MaxValueOfRGB;
  unsigned int m_TestMean[3];
  unsigned int m_TestVar[3];
  typename RGBHCVImage::Pointer m_WorkingImage;

  virtual bool TestHomogeneity(IndexList Plist);
};

}//end namespace


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkVoronoiSegmentationRGBImageFilter.txx"
#endif

#endif




