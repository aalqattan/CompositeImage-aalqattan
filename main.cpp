//Author: Ali Alqattan 
//p03-Composite Image

#include<iostream>
#include<vector>
#include<string>
#include "bitmap.h"


using namespace std;

//Function prototype
string getInput();
void pixeladjust(Pixel &p,Pixel d);



int main()


{
        //declear variables outside the while loop. 
        int imagenumber = 0;
        bool validBmp;
        Bitmap image;
        Pixel rgb;
        Pixel rgb2;
        string fileName;
        vector < vector < Pixel > > bmp [10];
        int row;
        int cols;


        // composite up to 10 files
        for(int i =0;i<10;i++)
        {
                cout<<"Please enter the file name which should be windows bmp"<<endl;
                cout<<"File " << i <<  " - "; 
                fileName = getInput();
                // if the user says DONE , end the loop and composite files
                if(fileName == "DONE" || fileName == "done" || fileName == "Done")
                {
                        imagenumber = i;
                        if(imagenumber <2)
                        {
                                cout <<"should have more than 1 file to do composite image" <<endl;
                                return 0;
                        }
                        break;
                }


                image.open(fileName); 
                // Check if the image is valid
                if(!image.isImage())
                {
                        i = i-1;
                        continue;
                }

                // Put the image to a matrix
                bmp[i] = image.toPixelMatrix(); 
                if(i==0)
                {

                        // get the row and column size from the first image

                        row = bmp[0].size();    
                        cols = bmp[0][0].size();
                }

                // If the SIze doesnt match with first picture , go back to the
                // top of the loop and decrement counter.

                if(bmp[i].size() != row) 

                {
                        cout <<"Size is different please pick another picture " << endl;
                        i = i-1;
                        continue;
                }
                if(bmp[i][0].size() != cols)
                {
                        cout <<"Size is different please pick another picture " << endl;
                        i = i-1;
                        continue;
                }





        }

        // Run for how many images
        for(int j = 1;j<imagenumber;j++) 
        {
                for(int i = 0; i < row; i++) 
                {
                        for(int c= 0; c < cols; c++)
                        {  
                                // get the pixel data from the image        
                                rgb = bmp[j][i][c]; 

                                // get the pixel data from the first image
                                rgb2 = bmp[0][i][c];    

                                // Put them to the pixeladjust function which will average the rgb of two pictures

                                pixeladjust(rgb2,rgb);   

                                //put the pixel back to the first image
                                bmp[0][i][c] = rgb2;       

                        }  

                }   
                cout <<"Image "<<j+1<<"/"<<imagenumber<< " Done" << endl;

        }



        // Save back to Image
        image.fromPixelMatrix(bmp[0]);
        image.save("composite-aalqattan.bmp");


        return 0;

}
// Get the input from user
string getInput()
{

        string in;
        cin >> in;

        return in;

}
// Average the values of the pixels
void pixeladjust(Pixel &p,Pixel d)
{
        int r = (p.red + d.red)/2;
        int g = (p.green + d.green) /2;
        int b = (p.blue + d.blue) /2 ;

        p.red = r;
        p.green = g;
        p.blue = b;

}
