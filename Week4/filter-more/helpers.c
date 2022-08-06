#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = (int)round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][j].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0  && j == 0)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue +
                                                   buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int)round((buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen +
                                                    buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int)round((buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed +
                                                  buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 4.0);
            }
            else if (i == height - 1  && j == 0)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue +
                                                   buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int)round((buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen +
                                                    buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int)round((buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed +
                                                  buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed) / 4.0);
            }
            else if (i == 0  && j == width - 1)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i][j].rgbtBlue + buffer[i][j - 1].rgbtBlue +
                                                   buffer[i + 1][j].rgbtBlue + buffer[i + 1][j - 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int)round((buffer[i][j].rgbtGreen + buffer[i][j - 1].rgbtGreen +
                                                    buffer[i + 1][j].rgbtGreen + buffer[i + 1][j - 1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int)round((buffer[i][j].rgbtRed + buffer[i][j - 1].rgbtRed +
                                                  buffer[i + 1][j].rgbtRed + buffer[i + 1][j - 1].rgbtRed) / 4.0);
            }
            else if (i == height - 1  && j == width - 1)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i][j].rgbtBlue + buffer[i][j - 1].rgbtBlue +
                                                   buffer[i - 1][j].rgbtBlue + buffer[i - 1][j - 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int)round((buffer[i][j].rgbtGreen + buffer[i][j - 1].rgbtGreen +
                                                    buffer[i - 1][j].rgbtGreen + buffer[i - 1][j - 1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int)round((buffer[i][j].rgbtRed + buffer[i][j - 1].rgbtRed +
                                                  buffer[i - 1][j].rgbtRed + buffer[i - 1][j - 1].rgbtRed) / 4.0);
            }
            else if (i == 0)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue +
                                                   buffer[i + 1][j - 1].rgbtBlue + buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int)round((buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen +
                                                    buffer[i + 1][j - 1].rgbtGreen + buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int)round((buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed +
                                                  buffer[i + 1][j - 1].rgbtRed + buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 6.0);
            }
            else if (i == height - 1)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue +
                                                   buffer[i - 1][j - 1].rgbtBlue + buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int)round((buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen +
                                                    buffer[i - 1][j - 1].rgbtGreen + buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int)round((buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed +
                                                  buffer[i - 1][j - 1].rgbtRed + buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed) / 6.0);
            }
            else if (j == 0)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue +
                                                   buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue +
                                                   buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int)round((buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen +
                                                    buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen +
                                                    buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int)round((buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed +
                                                  buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed +
                                                  buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 6.0);
            }
            else if (j == width - 1)
            {
                image[i][j].rgbtBlue = (int)round((buffer[i - 1][j - 1].rgbtBlue + buffer[i - 1][j].rgbtBlue +
                                                   buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue +
                                                   buffer[i + 1][j - 1].rgbtBlue + buffer[i + 1][j].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int)round((buffer[i - 1][j - 1].rgbtGreen + buffer[i - 1][j].rgbtGreen +
                                                    buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen +
                                                    buffer[i + 1][j - 1].rgbtGreen + buffer[i + 1][j].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int)round((buffer[i - 1][j - 1].rgbtRed + buffer[i - 1][j].rgbtRed +
                                                  buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed +
                                                  buffer[i + 1][j - 1].rgbtRed + buffer[i + 1][j].rgbtRed) / 6.0);
            }
            else
            {
                image[i][j].rgbtBlue = (int)round((buffer[i - 1][j - 1].rgbtBlue + buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue +
                                                   buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue +
                                                   buffer[i + 1][j - 1].rgbtBlue + buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 9.0);
                image[i][j].rgbtGreen = (int)round((buffer[i - 1][j - 1].rgbtGreen + buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen +
                                                    buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen +
                                                    buffer[i + 1][j - 1].rgbtGreen + buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 9.0);
                image[i][j].rgbtRed = (int)round((buffer[i - 1][j - 1].rgbtRed + buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed +
                                                  buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed +
                                                  buffer[i + 1][j - 1].rgbtRed + buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 9.0);
            }
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //create a buffer to store the output of filter
    RGBTRIPLE buffer[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                buffer[i][j].rgbtBlue = 0;
                buffer[i][j].rgbtGreen = 0;
                buffer[i][j].rgbtRed = 0;
            }
            else
            {
                buffer[i][j] = image[i - 1][j - 1];
            }
        }
    }
    int temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp = (int)round(sqrt(pow((-buffer[i][j].rgbtBlue - 2 * buffer[i + 1][j].rgbtBlue - buffer[i + 2][j].rgbtBlue +
                                        buffer[i][j + 2].rgbtBlue + 2 * buffer[i + 1][j + 2].rgbtBlue + buffer[i + 2][j + 2].rgbtBlue), 2) +
                                   pow((-buffer[i][j].rgbtBlue - 2 * buffer[i][j + 1].rgbtBlue - buffer[i][j + 2].rgbtBlue +
                                        buffer[i + 2][j].rgbtBlue + 2 * buffer[i + 2][j + 1].rgbtBlue + buffer[i + 2][j + 2].rgbtBlue), 2)));
            if (temp > 255)
            {
                temp = 255;
            }
            image[i][j].rgbtBlue = temp;

            temp = (int)round(sqrt(pow((-buffer[i][j].rgbtGreen - 2 * buffer[i + 1][j].rgbtGreen - buffer[i + 2][j].rgbtGreen +
                                        buffer[i][j + 2].rgbtGreen + 2 * buffer[i + 1][j + 2].rgbtGreen + buffer[i + 2][j + 2].rgbtGreen), 2) +
                                   pow((-buffer[i][j].rgbtGreen - 2 * buffer[i][j + 1].rgbtGreen - buffer[i][j + 2].rgbtGreen +
                                        buffer[i + 2][j].rgbtGreen + 2 * buffer[i + 2][j + 1].rgbtGreen + buffer[i + 2][j + 2].rgbtGreen), 2)));
            if (temp > 255)
            {
                temp = 255;
            }
            image[i][j].rgbtGreen = temp;

            temp = (int)round(sqrt(pow((-buffer[i][j].rgbtRed - 2 * buffer[i + 1][j].rgbtRed - buffer[i + 2][j].rgbtRed +
                                        buffer[i][j + 2].rgbtRed + 2 * buffer[i + 1][j + 2].rgbtRed + buffer[i + 2][j + 2].rgbtRed), 2) +
                                   pow((-buffer[i][j].rgbtRed - 2 * buffer[i][j + 1].rgbtRed - buffer[i][j + 2].rgbtRed +
                                        buffer[i + 2][j].rgbtRed + 2 * buffer[i + 2][j + 1].rgbtRed + buffer[i + 2][j + 2].rgbtRed), 2)));
            if (temp > 255)
            {
                temp = 255;
            }
            image[i][j].rgbtRed = temp;
        }
    }
    return;
}