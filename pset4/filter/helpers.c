#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float colors =  image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed; // for each loop, assign all the colors into a float sum
            int average = round(colors / 3); // average the colors
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average; // assign the average of all sum colors across all pixel colors. 
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue; //original color values per pixel
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;
            
            // Blue
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue); // apply the algorithm to adjust the colors accordingly
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255; // if above 255, cap the value to 255, the maximum value for an 8-bit color. 
            }
            
            else
            {
                image[i][j].rgbtBlue = sepiaBlue; // assign the new value to the picture
            }
            
            // Green
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue); 
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            
            // Blue
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue); 
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // Loop til the halfway point of the picture, as that's what is required.
        {
            RGBTRIPLE temp = image[i][j]; // temporary array to hold our current pixels.
            image[i][j] = image[i][width - (j + 1)]; // flipping the pixels
            image[i][width - (j + 1)] = temp; //
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width]; // Need a temporary image, as the early loops would mess up the colors for the latter loops. 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];
        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tot_Blue; // to store neighbour colors
            int tot_Green;
            int tot_Red;
            float counter;

            tot_Blue = tot_Green = tot_Red = counter = 0;

            for (int k = -1; k < 2; k++) // check for the neighbour pixels
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k >= 0 && i + k < height & j + l >= 0
                        && j + l < width) // if they match these values, then they exist. Proceed by storing their values. 
                    {
                        tot_Blue += tmp_image[i + k][j + l].rgbtBlue;
                        tot_Green += tmp_image[i + k][j + l].rgbtGreen;
                        tot_Red += tmp_image[i + k][j + l].rgbtRed;
                        counter++;
                    }
                }
            }

            // find average colour value for neighbouring pixels and assign it to the original image
            image[i][j].rgbtBlue = round(tot_Blue / counter);
            image[i][j].rgbtGreen = round(tot_Green / counter);
            image[i][j].rgbtRed = round(tot_Red / counter);
        }
    }
    return;
}


