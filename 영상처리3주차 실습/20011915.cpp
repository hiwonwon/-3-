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



	int ratio = 2;//1번문제
	int width2 = bmpInfo.biWidth >> ratio;
	int height2 = bmpInfo.biHeight >> ratio;
	int stride2 = (((bitCnt / 8) * width2) + 3) / 4 * 4;
	int size2 = stride2 * height2;
	unsigned char* inputImg1 = NULL, * outputImg = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);


	int ratio2 = 2;//2번문제
	int width2_2 = bmpInfo.biWidth << ratio2;
	int height2_2 = bmpInfo.biHeight << ratio2;
	int stride2_2 = (((bitCnt / 8) * width2_2) + 3) / 4 * 4;
	int size2_2 = stride2_2 * height2_2;
	unsigned char * outputImg2 = NULL;
	outputImg2 = (unsigned char*)calloc(size2_2, sizeof(unsigned char));

	unsigned char* outputImg3_1 = NULL; //3번문제
	outputImg3_1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	unsigned char* outputImg3 = NULL;
	outputImg3 = (unsigned char*)calloc(size, sizeof(unsigned char));

	unsigned char* outputImg4 = NULL; //4번문제
	outputImg4 = (unsigned char*)calloc(size, sizeof(unsigned char));
	double pi = 3.1415926535;
	double Degree=45;
	double radian = Degree * pi / 180.0;
	double cc = cos(radian), ss = sin(radian);





	int n;
	scanf("%d", &n);

	double mse = 0, psnr;

	while (n != 5) {
		if (n == 1) {//downsampling
			unsigned char* Y1 = NULL;
			Y1 = (unsigned char*)calloc(size, sizeof(unsigned char));

			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					Y1[j * width + i] = inputImg1[j * stride + 3 * i + 0];;
				}
			}


			unsigned char* Y2 = NULL;
			Y2 = (unsigned char*)calloc(width2 * height2, sizeof(unsigned char));


			for (int j = 0; j < height2; j++) {
				for (int i = 0; i < width2; i++) {
					Y2[j * width2 + i] = Y1[(j << ratio) * width + (i << ratio)];
					outputImg[j * stride2 + 3 * i + 0] = Y2[j * width2 + i];
					outputImg[j * stride2 + 3 * i + 1] = Y2[j * width2 + i];
					outputImg[j * stride2 + 3 * i + 2] = Y2[j * width2 + i];


				}
			}

		}
		if (n == 2) {//upsampling
			unsigned char* Y1_2 = NULL;
			Y1_2 = (unsigned char*)calloc(size, sizeof(unsigned char));

			unsigned char* Y2_2 = NULL;
			Y2_2 = (unsigned char*)calloc(size2_2, sizeof(unsigned char));


			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					Y1_2[j * width + i] = inputImg1[j * stride + 3 * i + 0];

					for (int a = 0; a < 4; a++) {
						for (int b = 0; b < 4; b++) {
							outputImg2[(4 * j + a) * stride2_2 + 3 * (4 * i + b) + 0] = Y1_2[j * width + i];
							outputImg2[(4 * j + a) * stride2_2 + 3 * (4 * i + b) + 1] = Y1_2[j * width + i];
							outputImg2[(4 * j + a) * stride2_2 + 3 * (4 * i + b) + 2] = Y1_2[j * width + i];
						}
					}

					//mse += (double)((Y2_2[j * width + i] - Y1_2[j * width + i]) * (Y2_2[j * width + i] - Y1_2[j * width + i]));
				}
			}
			/*mse /= (width * height);
			psnr = mse != 0.0 ? 10.0 * log10(255 * 255 / mse) : 99.99;
			printf("MSE = %.2lf\nPSNR = %.2lf dB\n", mse, psnr);
			*/
		}

		if (n == 3) { //3번문제
			unsigned char* Y1 = NULL;
			Y1 = (unsigned char*)calloc(size, sizeof(unsigned char));

			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					Y1[j * width + i] = inputImg1[j * stride + 3 * i + 0];;
				}
			}


			unsigned char* Y2 = NULL;
			Y2 = (unsigned char*)calloc(width2 * height2, sizeof(unsigned char));


			for (int j = 0; j < height2; j++) {
				for (int i = 0; i < width2; i++) {
					Y2[j * width2 + i] = Y1[(j << ratio) * width + (i << ratio)];
					outputImg3_1[j * stride2 + 3 * i + 0] = Y2[j * width2 + i];
					outputImg3_1[j * stride2 + 3 * i + 1] = Y2[j * width2 + i];
					outputImg3_1[j * stride2 + 3 * i + 2] = Y2[j * width2 + i];


				}
			}
			////////////////////////////////
			unsigned char* Y1_2 = NULL;
			Y1_2 = (unsigned char*)calloc(width2 * height2, sizeof(unsigned char));

			unsigned char* Y2_2 = NULL;
			Y2_2 = (unsigned char*)calloc(size, sizeof(unsigned char));


			for (int j = 0; j < height2; j++) {
				for (int i = 0; i < width2; i++) {
					Y1_2[j * width2 + i] = outputImg3_1[j * stride2 + 3 * i + 0];

					for (int a = 0; a < 4; a++) {
						for (int b = 0; b < 4; b++) {
							outputImg3[(4 * j + a) * stride + 3 * (4 * i + b) + 0] = Y1_2[j * width2 + i];
							outputImg3[(4 * j + a) * stride + 3 * (4 * i + b) + 1] = Y1_2[j * width2 + i];
							outputImg3[(4 * j + a) * stride + 3 * (4 * i + b) + 2] = Y1_2[j * width2 + i];
						}
					}

				}
			}

		}


		if (n == 4) {//4번문제

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
		}

		scanf("%d", &n);
	}


	
	FILE* outputFile = fopen("20011915_1.bmp", "wb");
	bmpInfo.biWidth = width2;
	bmpInfo.biHeight = height2;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size2, outputFile);

	FILE* outputFile2 = fopen("20011915_2.bmp", "wb");
	bmpInfo.biWidth = width2_2;
	bmpInfo.biHeight = height2_2;
	bmpInfo.biSizeImage = size2_2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2_2;
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile2);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile2);
	fwrite(outputImg2, sizeof(unsigned char), size2_2, outputFile2);

	FILE* outputFile3 = fopen("20011915_3.bmp", "wb");
	bmpInfo.biWidth = width;
	bmpInfo.biHeight = height;
	bmpInfo.biSizeImage = size;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size;
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile3);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile3);
	fwrite(outputImg3, sizeof(unsigned char), size, outputFile3);


	FILE* outputFile4 = fopen("20011915_4.bmp", "wb");
	bmpInfo.biWidth = width;
	bmpInfo.biHeight = height;
	bmpInfo.biSizeImage = size;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size;
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile4);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile4);
	fwrite(outputImg4, sizeof(unsigned char), size, outputFile4);

	free(outputImg4);
	fclose(outputFile4);
	free(outputImg3_1);
	free(outputImg3);
	fclose(outputFile3);
	free(outputImg2);
	fclose(outputFile2);
	free(outputImg);
	fclose(outputFile);
	free(inputImg1);
	fclose(inputFIle1);
	return 0;
}