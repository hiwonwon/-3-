#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
int main() {
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;

	FILE* inputFIle1 = NULL;
	inputFIle1 = fopen("AICenterY.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle1);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle1);

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	printf("W: %d(%d)\nH: %d\nS: %d\nD: %d\n", width, stride, height, size, bitCnt);

	unsigned char* inputImg1 = NULL, * outputImg4 = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	outputImg4 = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);
	double pi = 3.1415926535;
	double Degree;
	scanf("%lf", &Degree);
	double radian = Degree * pi / 180.0;
	double cc = cos(radian), ss = sin(radian);
	
	
	int orig_x, orig_y;
	double xcenter = 256, ycenter = 256;
	double x2, y2;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			unsigned char Y = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];

			orig_x = (int)(((double)i - xcenter) * cc - ((double)j - ycenter) * ss + xcenter);
			orig_y = (int)(((double)i - xcenter) * ss + ((double)j - ycenter) * cc + ycenter);

			if ((orig_y >= 0 && orig_y < height) && (orig_x >= 0 && orig_x < width)) {
				outputImg4[orig_y * stride + 3 * orig_x + 0] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
				outputImg4[orig_y * stride + 3 * orig_x + 1] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
				outputImg4[orig_y * stride + 3 * orig_x + 2] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
			}


		}
	}
	//////////////////////////////
	//hole filling

	double tempArray[4];
	int d = 0;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
		;
			orig_x = (int)(((double)i - xcenter) * cc - ((double)j - ycenter) * ss + xcenter);
			orig_y = (int)(((double)i - xcenter) * ss + ((double)j - ycenter) * cc + ycenter);

			if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{
			}
			else{		
				if (outputImg4[j * stride + 3 * i + 0] == 0) {

					tempArray[0] = 0.299 * outputImg4[(j - 1) * stride + 3 * (i)+2] + 0.587 * outputImg4[(j - 1) * stride + 3 * (i)+1] + 0.114 * outputImg4[(j - 1) * stride + 3 * (i)+0];
					tempArray[1] = 0.299 * outputImg4[j * stride + 3 * (i - 1) + 2] + 0.587 * outputImg4[(j)*stride + 3 * (i - 1) + 1] + 0.114 * outputImg4[(j)*stride + 3 * (i - 1) + 0];
					tempArray[2] = 0.299 * outputImg4[(j)*stride + 3 * (i + 1) + 2] + 0.587 * outputImg4[(j)*stride + 3 * (i + 1) + 1] + 0.114 * outputImg4[(j)*stride + 3 * (i + 1) + 0];
					tempArray[3] = 0.299 * outputImg4[(j + 1) * stride + 3 * (i)+2] + 0.587 * outputImg4[(j + 1) * stride + 3 * (i)+1] + 0.114 * outputImg4[(j + 1) * stride + 3 * (i)+0];


					d = 0;
					double sum = 0;
					for (int k = 0; k < 4; k++)
					{
						sum += tempArray[k];

					}

					double mean = sum / 4;

					//printf("mean=%.2lf\n", mean);
					outputImg4[j * stride + 3 * i + 0] = (unsigned char)(mean > 255 ? 255 : mean < 0 ? 0 : mean);
					outputImg4[j * stride + 3 * i + 1] = (unsigned char)(mean > 255 ? 255 : mean < 0 ? 0 : mean);
					outputImg4[j * stride + 3 * i + 2] = (unsigned char)(mean > 255 ? 255 : mean < 0 ? 0 : mean);//Sorting 후 중간 값을 출력 이미지 값에 저장



				}

			}

		}
	}





	FILE* outputFile4 = fopen("rotation.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile4);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile4);
	fwrite(outputImg4, sizeof(unsigned char), size, outputFile4);

	free(outputImg4);
	fclose(outputFile4);
	free(inputImg1);
	fclose(inputFIle1);
	



	return 0;
}