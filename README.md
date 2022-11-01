# SLIC Superpixel Implementation
## Preface
- This repository contains an implementation of the [SLIC Superpixel algorithm](https://core.ac.uk/download/pdf/147983593.pdf) by Achanta et al. (PAMI'12, vol. 34, num. 11, pp. 2274-2282). 
- [PSMM](https://github.com/PSMM/SLIC-Superpixels) reproduced this paper ten years ago, and this repository mainly inherented his codes but upgraded the OpenCV lib version up to over 2.0, here many thanks to [PSMM](https://github.com/PSMM/SLIC-Superpixels).
  
## A Little Bit of Background

- Superpixel algorithm was first raised by Xiaofeng Ren and Jitendra Malik from UC Berkeley in 2003. They published a paper on ICCV in 2003 and wanted to learning a classification model from segmentation. 

- Superpixel algorithm was used in the preprocessing state to simplify the later segmentation procedure. Because the principle of SuperPixels is to combine the original multiple pixels into a large pixel. For example, the original image has more than 200,000 pixels, after the superpixel processing, only a few thousand pixels. Histogram and other processing will be more convenient. 

- In 2011, Achanta proposed a refined Superpixels algorithm named "SLIC-Superpixels" and it quickly became one of the most popular Superpixels algorithms. In this homework, i mainly used SLIC-Superpixels algorithm as well.

## Details of SLIC-Superpixels
SLIC-Superpixels adapts a **k-means** clustering approach to efficiently generate superpixels. And its main idea shows as follow:

- Orderly sowing $k$ seed points as cluster centers on the image with interval of $S = \sqrt{\frac{N}{k}}$, where $N$ is the total pixels of image(By doing this, it can make the seed points uniformly distributed in the whole image).
- Move cluster centers to the lowest gradient position in a 3 × 3 neighborhood(This is done to avoid centering a superpixel on an edge, and to reduce the chance of seeding a superpixel with a noisy pixel).
- Considering every cluster centers have a spatial domain of 2S × 2S region, and calculating the distance of every pixels in this region to cluster center(From step1 we can see that the expected spatial domain of a superpixel should be a region of approximate size S × S. So there is overlap for adjacent cluster centers, and every pixel in the overlap areas only belong to cluster center which has the minimum distance to the pixel. This is a very tricky method and I will explain in analysis part).
- Updating the cluster centers. Adding every pixel's values(Lab values and coordinate values) to the corresponding cluster center, and then normalize the cluster to get a new cluster center.
- loop upon steps for 10 times(empirical value).


## Exemplary Result
There are two parameters to control the quality of segmented image:

one is the **number of superpixels** and the other is **weight factor** which defines the relative importance between color similarity and spatial proximity. When weight factor is large, spatial proximity is more important and the resulting superpixels are more compact (i.e. they have a lower area to perimeter ratio). When weight factor is small, the resulting superpixels adhere more tightly to image boundaries, but have less regular size and shape.

<p align="center">
  <img src="https://user-images.githubusercontent.com/64240681/197374522-a578156c-5862-4288-ae3e-22338b788a62.png" />
  <img src="https://user-images.githubusercontent.com/64240681/197374556-aea820fb-a0ac-48a4-8e34-753187cf8b37.png" />
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/64240681/197374568-72f5bd1d-4681-4915-8928-df4ccd135969.png" />
  <img src="https://user-images.githubusercontent.com/64240681/197374571-4b2276da-572c-4ceb-ad89-2bfd0df1db8e.png" />
</p>


From the figure of dog we can see that when we increase the weights, the contours of every cell become more clear and every cell's areas tend to be more equal, which means spatial proximity is more important in segmentation. It seems that bigger weights value can lead a better segmentation quality. But is that true for general situation? Then I do an implementation in a more complex picture.

<p align="center">
  <img src="https://user-images.githubusercontent.com/64240681/197375590-d46e90d5-b109-41e8-9a5b-10881c6896da.png" />
  <img src="https://user-images.githubusercontent.com/64240681/197375584-25b5b642-3f22-44e0-8084-287456c421bf.png" />
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/64240681/197375585-53ae5221-c847-453d-b500-ac1856b3f154.png" />
  <img src="https://user-images.githubusercontent.com/64240681/197375587-d2f1f369-0180-4d7a-83dc-502441995293.png" />
</p>


In the figure of tiger, due to the tiger's skin is mottled with stripes, the colors' distribution becomes more complex than the figure of dog which has strong contrast between backgroud and foreground and easy to ditiguish them. So for the weights=200 case, the segmentation between back strips and yellow skin is not good. And at this time, we need to take a overall consideration and make a balance between color similarity and spatial proximity(I think weiths=150 is better for this picture). 

## Analysis
Up to now, the SLIC-Superpixels algorithm is one of the wildly used segmentation algorithms. I think these two merits contribute a lot and this is also the essence:

- Limiting the search area (2Sx2S). The key to speeding up this algorithm because limiting the size of the search region significantly reduces the number of distance calculations, and results in a significant speed advantage over conventional k-means clustering where each pixel must be compared with all cluster centers. It reduces the complexity of k-means algorithm to a constant during clustering and the complexity of the whole algorithm becomes linear.
    
- Set a weight factor which can let us decide the relative importance between color similarity and spatial proximity. Through weights factor, the proportion of color and distance can be adjusted, which is flexible and super pixel is more regular.
- Consider LAB color and XY distance when calculating distance. That takes into account both color and distance. 


## Some Other Examples
<p align="center">
  <img src="https://user-images.githubusercontent.com/64240681/197375674-ee269cc3-973c-49e0-908d-6d9aea1fe81e.png" />
  <img src="https://user-images.githubusercontent.com/64240681/197375677-a2bee216-d50e-49f3-8a8a-203cba2c74a5.png" />
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/64240681/197375681-ea94970c-f28d-48bb-9f04-b4e18d101547.png" />
  <img src="https://user-images.githubusercontent.com/64240681/197375689-7eb0f541-8a89-4db7-ac25-9701ed927dee.png" />
</p>


