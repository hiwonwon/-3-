#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <cstdlib>
int main() {
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;

	FILE* inputFIle1 = NULL;
	inputFIle1 = fopen("AICenterY_CombinedNoise.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle1);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle1);

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	printf("W: %d(%d)\nH: %d\nS: %d\nD: %d\n", width, stride, height, size, bitCnt);

	unsigned char* inputImg1 = NULL, * outputImg = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);

	
	double tempArray[10];
	int d = 0;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{
				unsigned char Y = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				outputImg[j * stride + 3 * i + 0] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
				outputImg[j * stride + 3 * i + 1] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
				outputImg[j * stride + 3 * i + 2] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
			}
			else

			{
				for (int a = -1; a < 2; a++) {
					for (int b = -1; b < 2; b++) {
							tempArray[d] = 0.299 * inputImg1[(j + a) * stride + 3 * (i + b) + 2] + 0.587 * inputImg1[(j + a) * stride + 3 * (i + b) + 1] + 0.114 * inputImg1[(j + a) * stride + 3 * (i + b) + 0];
							d++;
						
					}
				}

				d = 0;
				double sum=0;
				for (int k = 0; k < 9; k++)  
				{
					sum += tempArray[k];

				}
				double mean = sum / 9;
				outputImg[j * stride + 3 * i + 0] = (unsigned char)(mean > 255 ? 255 : mean < 0 ? 0 : mean);
				outputImg[j * stride + 3 * i + 1] = (unsigned char)(mean > 255 ? 255 : mean < 0 ? 0 : mean);
				outputImg[j * stride + 3 * i + 2] = (unsigned char)(mean > 255 ? 255 : mean < 0 ? 0 : mean);//Sorting 후 중간 값을 출력 이미지 값에 저장


			}
		}
	}





	FILE* outputFile = fopen("meanFilter.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	free(outputImg);
	free(inputImg1);
	fclose(inputFIle1);
	fclose(outputFile);



	return 0;
}
