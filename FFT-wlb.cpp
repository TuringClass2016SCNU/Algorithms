//  
// ���ٸ���Ҷ�任 Fast Fourier Transform 
// By lbwang@gmail.com 
// 2014-09-18 
// �汾 1.0  
// ʵ���ˡ��㷨���ۡ��ĵ���FFT�㷨��

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>   

const int N = 1024; 
const float PI = 3.1416; 

//����2��n���� 
int pow2(int n)
{
	int res = 1;
	for(int i = 0; i < n; i++)
	{
		res = res*2;
	}
	return res;
}

//����a��b����ֵ 
inline void swap(float &a, float &b) 
{       
    float t;
	t = a;
	a = b;
	b = t; 
}   

//�ж���������x�Ƿ�2��ָ��. 
int is_power_of_two(int x)
{
	while (x > 1) 
		{           
             if (x % 2)    
		        return 0;           
			 x /= 2; 
	     }//end for while  
    return 1;
}

//��������ֵ�ı��س��� 
static int log_2(int n)
{
       int res;
       for (res = 0; n >= 2; res++)
             n = n >> 1;
       return res;
 }//end of log2 
 
//�Ա��ش����б��ط���ת�ã�����,0001���1000��1010���0101
//��������ֵ����һ������Ҫת�õ�ֵ���ڶ�����ֵ�ı��س��ȣ���Ҫ�������ʵ���ȶ��������ͳ���. 
int bitrev(int inp, int numbits)
{
     int i, rev = 0;
     for (i = 0; i < numbits; i++)
	 	 {
           rev = (rev << 1) | (inp & 1);
                 inp >>= 1;
         }
     return rev;
}

//���ط���ת�ã���bitrev��˳������������������飬n��һ��2��ָ��ֵ�� 
void bitrev_permute(float xreal [], float ximag [], int n) 
{   
    int len_n;
      len_n = log_2(n);
      for (int i = 0; i < n; i++) 
	  {       
          int bri = bitrev(i, len_n);
          //�����Ѿ�����������ֵ 
		  if (bri <= i) continue;             
		  swap (xreal [i], xreal [bri]);              
	      swap (ximag [i], ximag [bri]);    
   
	   }//end for 
}//bitrev_permute   

//����FFT��Դ�ԡ��㷨���ۡ�, lbwang codes it on 2014.0917 morning.
//����ֵΪ�������飬�ֱ��ʾ����ϵ����ʵ�����鲿��n�������С
//���ֵ�����ԭ������ 
void iterative_FFT(float xreal [], float ximag [], int n) 
{
	float treal, timag, ureal, uimag, theta, phi, wreal, wimag;
	  
	for(int s = 1; s < log_2(n) + 1; s++) 
	{
		int m = pow2(s);
		theta = 2 * PI / m; //ÿ������theta�� 
		//printf("theta is %8.4f\n", theta);

		for(int k = 0; k < n; k = k + m)
		{
		     phi = 0; //��ʼ��Ϊ0 
	         wreal  = 1.0;  //cos(phi)    
             wimag  = 0.0; // sin(phi)
             
			 for(int j = 0; j < m/2; j++)
             {
             	//t <- w*A[k + j + m/2]
             	//ע������ĳ˷�����(a+bi) * (c+di ) = (ac - bd) + (bc +ad) i
             	treal = wreal * xreal[k + j + m/2] - wimag * ximag[k + j + m/2]; 
             	timag = wreal * ximag[k + j + m/2] + wimag * xreal[k + j + m/2];
             	
				 //u <- A[k + j]
             	ureal = xreal[k + j];
             	uimag = ximag[k + j];
             	
             	//A[k+j] = u + t
             	xreal[k + j] = ureal + treal;
             	ximag[k + j] = uimag + timag;
             	
             	//for debgu
            	 //printf("Got a ximag as %8.4f", ximag[k + j]);
             	
             	//A[k + j +m/2] = u-t
             	xreal[k + j + m/2] = ureal - treal;
             	ximag[k + j + m/2] = uimag - timag;
             	//for debgu
            	 //printf("Got a ximag as %8.4f", ximag[k + j + m/2]);
             	
             	//w = w*w_m����ζ��w����theta�ǣ���Ϊ w_m = e^i*(theta);
             	phi = phi + theta;
             	wreal  = cos(phi);      
                wimag  = sin(phi); 
                //for debug
                //printf("Phi, wreal and wimag is %8.4f %8.4f %8.4f \n", phi,wreal,wimag);
             }
		}
	}
	//printf("One computation is finish.\n");
} 

//����FFT���棬w_n --->> w_n^-1 ,�����㷨��֮ǰ��ͬ���Ǹı���wn�ķ��ţ�theta�为��. 
//����ֵΪ�������飬�ֱ��ʾ����ϵ����ʵ�����鲿��n�������С
//���ֵ�����ԭ������ 
void iterative_FFT_rev(float xreal [], float ximag [], int n) 
{
	float treal, timag, ureal, uimag, theta, phi, wreal, wimag;
	  
	for(int s = 1; s < log_2(n) + 1; s++) 
	{
		int m = pow2(s);
		theta = - 2 * PI / m; //ÿ������theta�� 
		//printf("theta is %8.4f\n", theta);

		for(int k = 0; k < n; k = k + m)
		{
		     phi = 0; //��ʼ��Ϊ0 
	         wreal  = 1.0;  //cos(phi)    
             wimag  = 0.0; // sin(phi)
             
			 for(int j = 0; j < m/2; j++)
             {
             	//t <- w*A[k + j + m/2]
             	//ע������ĳ˷�����(a+bi) * (c+di ) = (ac - bd) + (bc +ad) i
             	treal = wreal * xreal[k + j + m/2] - wimag * ximag[k + j + m/2]; 
             	timag = wreal * ximag[k + j + m/2] + wimag * xreal[k + j + m/2];
             	
				 //u <- A[k + j]
             	ureal = xreal[k + j];
             	uimag = ximag[k + j];
             	
             	//A[k+j] = u + t
             	xreal[k + j] = ureal + treal;
             	ximag[k + j] = uimag + timag;
             	             	
             	//A[k + j +m/2] = u-t
             	xreal[k + j + m/2] = ureal - treal;
             	ximag[k + j + m/2] = uimag - timag;
             	
             	//w = w*w_m����ζ��w����theta�ǣ���Ϊ w_m = e^i*(theta);
             	phi = phi + theta;
             	wreal  = cos(phi);      
                wimag  = sin(phi); 
                
             }
		}
	}
	//���ݶ���F^-1 = 1/n F^H 
	for (int j=0; j < n; j ++) 
	   {          
	       xreal [j] /= n;          
		   ximag [j] /= n; 
	   } 
	
} 
	
//���Ժ������Զ�����2^n��n���ض�����ֵ������FFT���㣬Ȼ��������ı�output�С� 
void iFFT_test ()
{
	  char outputfile [] = "output.txt";     // �����������ļ� output.txt ��      
	  char inputfile [] = "input.txt";   
	  char tempfile [] = "temp.txt"; 
	  float xreal [N] = {}, ximag [N] = {};      
	  int n = 4, i;       
	  FILE *input, *output, *temp;
	  	      
	  //��������ļ� 
	  if (!(output = fopen (outputfile, "w"))) 
	  {           
	       printf ("Cannot open file. ");          
		   exit (1); 
      }
   	  //��������ļ� 
	  if (!(input = fopen (inputfile, "w"))) 
	  {           
	       printf ("Cannot open file. ");          
		   exit (1); 
       }
       //��������ļ� 
	  if (!(temp = fopen (tempfile, "w"))) 
	  {           
	       printf ("Cannot open file. ");          
		   exit (1); 
       }
    
	 //�������ԣ��������n�������� 
      for(int i = 0; i< pow2(n) ; i++) 
       {
       	  //�����������ݣ��������Ǵ�0000-1111 
	      int b = i; 
		  for(int j = 0; j < n; j++)
       	   {
             xreal[j] = b & 1;
  	         ximag[j] = 0.0 ;
  	       	
  	       	 b >>= 1;
       	   }
    	    
  	    //����ֵ�����input.txt�ļ���ȥ
        fprintf (input, "i      real        imag \n");      
        for (int i = 0; i < n; i ++) 
		    fprintf (input, "%4d      %8.4f        %8.4f \n", i, xreal [i], ximag [i]); 
        fprintf (input, "================================= \n"); 
  	    
	    //���ض���ֵ����iFFT����   
  	     iterative_FFT(xreal, ximag, n); 
		     
		 //��������output�ļ���  
         fprintf (output, "i       real     imag \n");      
         for (int i = 0; i < n; i ++) 
		    fprintf (output, "%4d     %8.4f     %8.4f \n", i, xreal [i], ximag [i]); 
		 fprintf (output, "================================= \n"); 
		 
		 //���ض���ֵ����iFFT-rev���㣬��֤�Ƿ��������
		 //iterative_FFT_rev(xreal, ximag, n); 
		 //�򵥽���ʵ�����鲿�ͽ�������ˡ�������ģ� �ƺ����У� 
		 iterative_FFT(ximag, xreal, n);
		 
		 fprintf (temp, "i       real     imag \n");      
         for (int i = 0; i < n; i ++) 
		    fprintf (temp, "%4d     %8.4f     %8.4f \n", i, ximag [i], xreal [i]); 
		 fprintf (temp, "================================= \n"); 
       	        
       }//end of the iterative computing.
		
		if ( fclose (output)) 
			{           
			    printf ("File close error. ");         
				exit (1); 
			 } 
			 
		 if ( fclose (input)) 
			{           
			    printf ("File close error. ");         
				exit (1); 
			 }   
		  if ( fclose (temp)) 
			{           
			    printf ("File close error. ");         
				exit (1); 
			 } 
}	   

//������ 
int main ()
{       
	iFFT_test ();        
    return 0;
}
