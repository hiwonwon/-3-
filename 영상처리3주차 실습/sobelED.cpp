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

	unsigned char* inputImg1 = NULL, * gx_Img = NULL, * gy_Img = NULL, * Y3 = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	gx_Img = (unsigned char*)calloc(size, sizeof(unsigned char));
	gx_Img = (unsigned char*)calloc(size, sizeof(unsigned char));
	gy_Img = (unsigned char*)calloc(size, sizeof(unsigned char));
	gy_Img = (unsigned char*)calloc(size, sizeof(unsigned char));
	Y3 = (unsigned char*)calloc(size, sizeof(unsigned char));
	Y3 = (unsigned char*)calloc(size, sizeof(unsigned char));

	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			double sum1=0, sum2=0;


			if (i == 0 && j==0) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[(j+1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[(j+1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];

				
				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;
			}
			else if (i!=0 &&i!=width-1&&j==0) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[(j+1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[(j+1) * stride + 3 * (i-1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[(j + 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];


				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;
			}
			else if(i == width-1 && j == 0){
				unsigned char Gx_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[(j + 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];


				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;

			}
			else if (i == 0 && j != 0 && j!=height-1) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[(j-1) * stride + 3 * (i+1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[(j-1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[(j-1) * stride + 3 * (i+1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[(j + 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];



				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;

			}
			else if (i ==width-1 && j != 0 && j != height - 1) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[(j-1) * stride + 3 * (i-1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[(j - 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[(j + 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];



				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;

			}
			else if (i == 0 && j == height - 1) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[(j - 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];


				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;
			}
			else if (i!=0&&i != width - 1 && j == height - 1) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[(j - 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];


				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;

			}
			else if (i == width-1 && j == height - 1) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[(j - 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];


				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;
			}
			else if (i != 0 && i != width - 1 && j != 0 && j != height - 1) {
				unsigned char Gx_Y1 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y2 = 0.299 * inputImg1[j * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y3 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gx_Y4 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y5 = 0.299 * inputImg1[j * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[j * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[j * stride + 3 * (i + 1) + 0];
				unsigned char Gx_Y6 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];

				unsigned char Gy_Y1 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y2 = 0.299 * inputImg1[(j - 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * i + 0];
				unsigned char Gy_Y3 = 0.299 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j - 1) * stride + 3 * (i + 1) + 0];
				unsigned char Gy_Y4 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i - 1) + 0];
				unsigned char Gy_Y5 = 0.299 * inputImg1[(j + 1) * stride + 3 * i + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * i + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * i + 0];
				unsigned char Gy_Y6 = 0.299 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 2] + 0.587 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 1] + 0.114 * inputImg1[(j + 1) * stride + 3 * (i + 1) + 0];


				sum1 = Gx_Y1 * (-1) + Gx_Y2 * (-2) + Gx_Y3 * (-1) + Gx_Y4 + Gx_Y5 * 2 + Gx_Y6;
				sum2 = Gy_Y1 * (-1) + Gy_Y2 * (-2) + Gy_Y3 * (-1) + Gy_Y4 + Gy_Y5 * 2 + Gy_Y6;
			}


			gx_Img[j * stride + 3 * i + 0] = (unsigned char)(sum1 > 255 ? 255 : (sum1 < 0 ? 0 : sum1));
			gx_Img[j * stride + 3 * i + 1] = (unsigned char)(sum1 > 255 ? 255 : (sum1 < 0 ? 0 : sum1));
			gx_Img[j * stride + 3 * i + 2] = (unsigned char)(sum1 > 255 ? 255 : (sum1 < 0 ? 0 : sum1));


			gy_Img[j * stride + 3 * i + 0] = (unsigned char)(sum2 > 255 ? 255 : (sum2 < 0 ? 0 : sum2));
			gy_Img[j * stride + 3 * i + 1] = (unsigned char)(sum2 > 255 ? 255 : (sum2 < 0 ? 0 : sum2));
			gy_Img[j * stride + 3 * i + 2] = (unsigned char)(sum2 > 255 ? 255 : (sum2 < 0 ? 0 : sum2));

			double Gx = sum1;
			double Gy = sum2;

			double G = sqrt(Gx * Gx + Gy * Gy);
			Y3[j * stride + 3 * i + 0] = (unsigned char)(G > 255 ? 255 : (G < 0 ? 0 : G));
			Y3[j * stride + 3 * i + 1] = (unsigned char)(G > 255 ? 255 : (G < 0 ? 0 : G));
			Y3[j * stride + 3 * i + 2] = (unsigned char)(G > 255 ? 255 : (G < 0 ? 0 : G));

		}
	};


	FILE* outputFile = fopen("Gx_Img.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(gx_Img, sizeof(unsigned char), size, outputFile);

	FILE* outputFile2 = fopen("Gy_Img.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile2);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile2);
	fwrite(gy_Img, sizeof(unsigned char), size, outputFile2);

	FILE* outputFile3 = fopen("edge.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile3);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile3);
	fwrite(Y3, sizeof(unsigned char), size, outputFile3);

	free(gx_Img);
	free(gy_Img);
	free(Y3);
	free(inputImg1);
	fclose(inputFIle1);
	fclose(outputFile);
	fclose(outputFile2);
	fclose(outputFile3);


	return 0;
}