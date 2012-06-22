#include <iostream>
#include <vector>
#include <stdio.h>
#include "global.h"
using namespace std;

void printMatrixToFile(FILE *outfile, vec3d &matrix)
{

  fprintf(outfile,"{");
  for (int i=0; i<matrix.size(); i++)
    {
      fprintf(outfile,"{");
      
      for (int k=0; k<matrix[0].size(); k++)
	{
	  fprintf(outfile,"{");

	  for (int j=0; j<matrix[0][0].size(); j++)
	    {
	      fprintf(outfile,"%-12.12g",matrix[i][k][j]);

	      if (j < (matrix[0][0].size()-1))
		{
		  fprintf(outfile,"\n");
		}
	      else
		{
		  fprintf(outfile,"},\n");
		}
	    }
	}
            fprintf(outfile,"}\n");
    }
    fprintf(outfile,"}\n");
}


void printMatrixToFile(FILE *outfile, vec2d &matrix)
{  

  for (int i=0; i<matrix.size(); i++)
    {
      //     fprintf(outfile,"\n");

      for (int k=0; k<matrix[0].size(); k++)
	{
   	  fprintf(outfile,"%-12.12g",matrix[i][k]);

	  if (k < (matrix[0].size()-1))
	    {
	      fprintf(outfile,"  ");
	    }
	  else
	    {
	      fprintf(outfile,"\n");
	    }
	}
    }

}


void printMatrixToFile(FILE *outfile, OneD &matrix)
{
  
  for (int i=0; i<matrix.size(); i++)
    {
      fprintf(outfile,"%-12.12g",matrix[i]);

      if (i < (matrix.size()-1))
	{
	  fprintf(outfile,"\n");
	}
    }
  fprintf(outfile,"\n");

}
