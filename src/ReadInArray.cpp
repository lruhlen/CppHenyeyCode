
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <float.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printVector.h"
#include "printMatrix.h"
using namespace std;

OneD ReadInArray(string filename, int xSize)
{
  OneD result(xSize,0);
  ifstream myfile(filename.c_str());
  stringstream ss;
  string line, foo;
  int xindex = 0;
  
  if (myfile.is_open())
    { 
      while((! myfile.eof()) && (xindex < xSize))
	{
	  getline(myfile,line);
	  ss.clear();
	  ss.str(line);
	  ss >> ws;

	  if (line.find("//") != string::npos) // skip over comments in the input file
	    {
	      continue;
	    }
	  
	   ss >> foo;
	   result[xindex] = atof(foo.c_str());
	   xindex++;
	}
    }
  else // If you can't find/open the file, halt the execution of this program
    {
      exit(1);
    }

  return result;
}


vec2d ReadInArray(string filename, int xSize, int ySize)
{
  vec2d result(xSize,ySize,0);
  ifstream myfile(filename.c_str());
  stringstream ss;
  string line, foo;
  int xindex = 0;

  
  if (myfile.is_open())
    { 
      while((! myfile.eof()) && (xindex < xSize))
	{
	  getline(myfile,line);
	  ss.clear();
	  ss.str(line);
	  ss >> ws;

	  if (line.find("//") != string::npos) // skip over comments in the input file
	    {
	      continue;
	    }
	  
	  for (int yindex = 0; yindex < ySize; yindex++)
	    {
	      ss >> foo;
	      result[xindex][yindex] = atof(foo.c_str());
	    }
	   xindex++;
	}
    }
  else // If you can't find/open the file, halt the execution of this program
    {
      exit(1);
    }

  return result;
}

vec3d ReadInArray(string filename, int xSize, int ySize, int zSize)
{
  vec3d result(xSize,ySize,zSize,0);
  ifstream myfile(filename.c_str());
  stringstream ss;
  string line, foo;
  int xindex = 0;

  
  if (myfile.is_open())
    { 
      while((! myfile.eof()) && (xindex < xSize))
	{
	  getline(myfile,line);
	  ss.clear();
	  ss.str(line);
	  ss >> ws; // clear out the white space in the line...

	  if (line.find("//") != string::npos) // skip over comments in the input file
	    {
	      continue;
	    }
	  
	  for (int zindex = 0; zindex < zSize; zindex++)
	    {
	      
	      for (int yindex = 0; yindex < ySize; yindex++)
		{
		  ss >> foo;
		  result[xindex][yindex][zindex] = atof(foo.c_str());
		}
	    }
	   xindex++;
	}
    }
  else // If you can't find/open the file, halt the execution of this program
    {
      exit(1);
    }

  return result;
}
