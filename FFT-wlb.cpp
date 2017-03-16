//  
// 快速傅立叶变换 Fast Fourier Transform 
// By lbwang@gmail.com 
// 2014-09-18 
// 版本 1.0  
// 实现了《算法导论》的迭代FFT算法，

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>   

const int N = 1024; 
const float PI = 3.1416; 

//计算2的n次幂 
int pow2(int n)
{
	int res = 1;
	for(int i = 0; i < n; i++)
	{
		res = res*2;
	}
	return res;
}

//交换a与b的数值 
inline void swap(float &a, float &b) 
{       
    float t;
	t = a;
	a = b;
	b = t; 
}   

//判断输入整数x是否2的指数. 
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

//计算输入值的比特长度 
static int log_2(int n)
{
       int res;
       for (res = 0; n >= 2; res++)
             n = n >> 1;
       return res;
 }//end of log2 
 
//对比特串进行比特反向转置，比如,0001变成1000，1010变成0101
//输入两个值，第一个是需要转置的值，第二个是值的比特长度，需要逆向的真实长度而不是类型长度. 
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

//比特反向转置，以bitrev的顺序重新排列输入的数组，n是一个2的指数值。 
void bitrev_permute(float xreal [], float ximag [], int n) 
{   
    int len_n;
      len_n = log_2(n);
      for (int i = 0; i < n; i++) 
	  {       
          int bri = bitrev(i, len_n);
          //跳过已经交换过的数值 
		  if (bri <= i) continue;             
		  swap (xreal [i], xreal [bri]);              
	      swap (ximag [i], ximag [bri]);    
   
	   }//end for 
}//bitrev_permute   

//迭代FFT，源自《算法导论》, lbwang codes it on 2014.0917 morning.
//输入值为两个数组，分别表示输入系数的实部、虚部，n是数组大小
//输出值存放在原数组中 
void iterative_FFT(float xreal [], float ximag [], int n) 
{
	float treal, timag, ureal, uimag, theta, phi, wreal, wimag;
	  
	for(int s = 1; s < log_2(n) + 1; s++) 
	{
		int m = pow2(s);
		theta = 2 * PI / m; //每次增加theta度 
		//printf("theta is %8.4f\n", theta);

		for(int k = 0; k < n; k = k + m)
		{
		     phi = 0; //初始角为0 
	         wreal  = 1.0;  //cos(phi)    
             wimag  = 0.0; // sin(phi)
             
			 for(int j = 0; j < m/2; j++)
             {
             	//t <- w*A[k + j + m/2]
             	//注意这里的乘法规则：(a+bi) * (c+di ) = (ac - bd) + (bc +ad) i
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
             	
             	//w = w*w_m，意味着w增加theta角，因为 w_m = e^i*(theta);
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

//迭代FFT求逆，w_n --->> w_n^-1 ,所以算法与之前不同的是改变了wn的符号，theta变负角. 
//输入值为两个数组，分别表示输入系数的实部、虚部，n是数组大小
//输出值存放在原数组中 
void iterative_FFT_rev(float xreal [], float ximag [], int n) 
{
	float treal, timag, ureal, uimag, theta, phi, wreal, wimag;
	  
	for(int s = 1; s < log_2(n) + 1; s++) 
	{
		int m = pow2(s);
		theta = - 2 * PI / m; //每次增加theta度 
		//printf("theta is %8.4f\n", theta);

		for(int k = 0; k < n; k = k + m)
		{
		     phi = 0; //初始角为0 
	         wreal  = 1.0;  //cos(phi)    
             wimag  = 0.0; // sin(phi)
             
			 for(int j = 0; j < m/2; j++)
             {
             	//t <- w*A[k + j + m/2]
             	//注意这里的乘法规则：(a+bi) * (c+di ) = (ac - bd) + (bc +ad) i
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
             	
             	//w = w*w_m，意味着w增加theta角，因为 w_m = e^i*(theta);
             	phi = phi + theta;
             	wreal  = cos(phi);      
                wimag  = sin(phi); 
                
             }
		}
	}
	//根据定理F^-1 = 1/n F^H 
	for (int j=0; j < n; j ++) 
	   {          
	       xreal [j] /= n;          
		   ximag [j] /= n; 
	   } 
	
} 
	
//测试函数，自动生成2^n个n比特二进制值，进行FFT计算，然后输出到文本output中。 
void iFFT_test ()
{
	  char outputfile [] = "output.txt";     // 将结果输出到文件 output.txt 中      
	  char inputfile [] = "input.txt";   
	  char tempfile [] = "temp.txt"; 
	  float xreal [N] = {}, ximag [N] = {};      
	  int n = 4, i;       
	  FILE *input, *output, *temp;
	  	      
	  //创建输出文件 
	  if (!(output = fopen (outputfile, "w"))) 
	  {           
	       printf ("Cannot open file. ");          
		   exit (1); 
      }
   	  //创建输出文件 
	  if (!(input = fopen (inputfile, "w"))) 
	  {           
	       printf ("Cannot open file. ");          
		   exit (1); 
       }
       //创建输出文件 
	  if (!(temp = fopen (tempfile, "w"))) 
	  {           
	       printf ("Cannot open file. ");          
		   exit (1); 
       }
    
	 //迭代测试，穷举所有n比特数； 
      for(int i = 0; i< pow2(n) ; i++) 
       {
       	  //产生测试数据，本质上是从0000-1111 
	      int b = i; 
		  for(int j = 0; j < n; j++)
       	   {
             xreal[j] = b & 1;
  	         ximag[j] = 0.0 ;
  	       	
  	       	 b >>= 1;
       	   }
    	    
  	    //输入值输出到input.txt文件中去
        fprintf (input, "i      real        imag \n");      
        for (int i = 0; i < n; i ++) 
		    fprintf (input, "%4d      %8.4f        %8.4f \n", i, xreal [i], ximag [i]); 
        fprintf (input, "================================= \n"); 
  	    
	    //对特定的值进行iFFT计算   
  	     iterative_FFT(xreal, ximag, n); 
		     
		 //结果输出到output文件中  
         fprintf (output, "i       real     imag \n");      
         for (int i = 0; i < n; i ++) 
		    fprintf (output, "%4d     %8.4f     %8.4f \n", i, xreal [i], ximag [i]); 
		 fprintf (output, "================================= \n"); 
		 
		 //对特定的值进行iFFT-rev计算，验证是否等于输入
		 //iterative_FFT_rev(xreal, ximag, n); 
		 //简单交换实部与虚部就解决问题了。。。真的？ 似乎不行！ 
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

//主函数 
int main ()
{       
	iFFT_test ();        
    return 0;
}
