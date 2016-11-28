#include <iostream>
#include <math.h>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

typedef CImg<float> IF;
typedef size_t ST;

void nearest_neighbor(IF &img, ST zoom)
{
	ST width = img.width(),
	   height = img.height();
	  
	IF tmp(width,height*zoom,1,3,0);   
	
	for(ST i=0; i<width; i++)
	{
		for(ST j=0; j<height; j++)
		{
			for(ST k=0; k<zoom; k++)
			{
				tmp(i,j*zoom + k,0)=img(i,j,0);
				tmp(i,j*zoom + k,1)=img(i,j,1);
				tmp(i,j*zoom + k,2)=img(i,j,2);
			}
		}
	}
	
	img = tmp;
	IF tmp2(width*zoom,height*zoom,1,3,0);   
	for(ST i=0; i<width; i++)
	{
		for(ST j=0; j<height*zoom; j++)
		{
			for(ST k=0; k<zoom; k++)
			{
				tmp2(i*zoom + k,j,0)=img(i,j,0);
				tmp2(i*zoom + k,j,1)=img(i,j,1);
				tmp2(i*zoom + k,j,2)=img(i,j,2);
			}
		}
	}
	tmp2.display();
}


void bilineal(IF &img, ST zoom)
{
	ST width = img.width(),
	   height = img.height();
	  
	IF tmp(width*zoom-zoom, height*zoom-zoom,1,3,0);   
	
	for(ST i=0; i<height-1; i++)
	{
		for(ST j=0; j<width-1; j++)
		{		
			
			int a,b;	
			
			float Ais_0 = img(j,i,0), Ads_0 = img(j+1,i,0), Air_0 = img(j,i+1,0), Adr_0 = img(j+1,i+1,0) ;
			float Ais_1 = img(j,i,1), Ads_1 = img(j+1,i,1), Air_1 = img(j,i+1,1), Adr_1 = img(j+1,i+1,1) ;
			float Ais_2 = img(j,i,2), Ads_2 = img(j+1,i,2), Air_2 = img(j,i+1,2), Adr_2 = img(j+1,i+1,2) ;
					
			
			for(ST y_z=0; y_z<zoom; y_z++)
			{
				for(ST x_z=0; x_z<zoom; x_z++)
				{
					
					a = x_z; 	b = y_z;
					int u=zoom;					
					
					float interp_1 = (u-a)*(u-b)*Ais_0 + a*(u-b)*Ads_0 + (u-a)*b*Air_0 + a*b*Adr_0,
						  interp_2 = (u-a)*(u-b)*Ais_1 + a*(u-b)*Ads_1 + (u-a)*b*Air_1 + a*b*Adr_1,
					      interp_3 = (u-a)*(u-b)*Ais_2 + a*(u-b)*Ads_2 + (u-a)*b*Air_2 + a*b*Adr_2;
				
					tmp(j*zoom + x_z,i*zoom + y_z,0)=interp_1;
					tmp(j*zoom + x_z,i*zoom + y_z,1)=interp_2;
					tmp(j*zoom + x_z,i*zoom + y_z,2)=interp_3;
				}
			}
		}
	}
	
	
	
	tmp.display();
	
}


int main()
{
IF img("25.png");
//nearest_neighbor(img,30);
bilineal(img,10);


	
}

