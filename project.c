/* Written by Sanchit Karve (born2c0de)
   Contact me on born2c0de AT dreamincode DOT net
*/

//********************************************************************************//
//Data Communications & Networking-2                                              //
//Project 1                                                                       //
//Topic: Evaluation of Adaptive Routing using Dijkstra's                          //
//By, Urvi Gada                                                                   //
//Student ID: 801029135                                                           //
//Email: ugada@uncc.edu                                                           //
//********************************************************************************//

#include <stdio.h>
#include <string.h>

#define MAX 6  // Number of nodes
#define INFINITE 998  //infinity 

int allselected(float *selected)
{
  int i;
  for(i=0;i<MAX;i++)
    if(selected[i]==0)
      return 0;
  return 1;
}

void shortpath(float cost[][MAX],int *preced,float *distance)
{
  float selected[MAX]={0},dc,smalldist,newdist;
  int current=0,i,k;
  for(i=0;i<MAX;i++)
    distance[i]=INFINITE;
  selected[current]=1;
  distance[0]=0;
  current=0;
  while(!allselected(selected))
  {
    smalldist=INFINITE;
    dc=distance[current];
    for(i=0;i<MAX;i++)
    {
      if(selected[i]==0)
      {                                             
        newdist=dc+cost[current][i];
        if(newdist<distance[i])
        {
          distance[i]=newdist;
          preced[i]=current;
        }
        if(distance[i]<smalldist)
        {
          smalldist=distance[i];
          k=i;
        }
      }
    }
    current=k;
    selected[current]=1;
   }
}



int main()
{

//Fill in W (weight)matrix
//If a link between two nodes exist, enter the link cost value else enter INFINITE
//Cost of transmission between same node is also INFINITE
 float W[MAX][MAX]= 
     {{INFINITE,2,INFINITE,1,INFINITE,INFINITE}, 
      {2,INFINITE,3,2,INFINITE,INFINITE}, 
      {INFINITE,3,INFINITE,INFINITE,1,5},
      {1,2,INFINITE,INFINITE,9,INFINITE},
      {INFINITE,INFINITE,1,9,INFINITE,2},
      {INFINITE,INFINITE,5,INFINITE,2,INFINITE}};


  int link[MAX][MAX] = {{0}};
  int i,preced[MAX]={0};
  float distance[MAX];

//Copy weight matrix to cost matrix
  float cost[MAX][MAX] = {{INFINITE}};
      for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
        	cost[i][j] = W[i][j];
        }
      }

//Loop for setting the p value
  for(float p=0.2; p<=1; p+=0.2){

//Reinitialize cost matrix to weight matrix
      for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
        	cost[i][j] = W[i][j];
        }
      }

    printf("\n------------------------------------------------------");
    printf("\nValue of p = %f",p);
    printf("\n------------------------------------------------------");

//Loop for setting the iterations 
    for(int iterations = 1; iterations <= 20; iterations++){
     printf ("\nIteration number:%d\n", iterations);


//Call the shortpath function to calculate the shortest path between two nodes
      shortpath(cost,preced,distance);

//Printing the link cost matrix
	  printf ("The Link Cost matrix is: \n");

          for(int i = 0; i < MAX; i++){
          	for(int j = 0; j < MAX; j++){
                	printf("%f          ", cost[i][j]);
        	}
        	printf("\n");
      	  }



//Printing the predecessor array
	  printf ("The Predecessor Array is: \n");
          for(i=0;i<MAX;i++){
          	printf("Node %d, Predecessor= %d, Total cost= %f\n",i+1,preced[i]+1,distance[i]);
       	  }	 
   	 
//Least Cost Routing and Link Load Computation
      int total = 0;
      for(int i=0;i<MAX;i++){
        int transmission = 0;
        int j = i;

       printf ("\nPath from Node %d:", j + 1);

        while(j != preced[j]){
          printf ("%d to ", j + 1);
			  transmission++;
			  link[preced[j]][j] += 1;
			  link[j][preced[j]] += 1;
          j = preced[j];
          
        }
        printf ("1");
	printf ("\nNumber of transmissions:%d\n", transmission);
	total = total + transmission;
	}
	printf ("\nTotal number of transmissions=%d", total);

//Printing the Link Transmission Array
	  printf ("\nThe Link Transmission Array is:\n");
          for(int i = 0; i < MAX; i++){
          	for(int j = 0; j < MAX; j++){
	          printf(" %d ", link[i][j]);
	        }
	        printf("\n");
	        }

    
//Cost Adaptation

      for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
          cost[i][j] = (1-p)*(cost[i][j]) + (p)*(W[i][j] + 5*(link[i][j]));
        }
      }


//Refreshing the preced,distance and link matrix
      
      int Preced[MAX] = {0};
      float Distance[MAX] = {0};
      preced[MAX] = Preced[MAX];
      distance[MAX] = Distance[MAX];

      int Link[MAX][MAX] = {{0}};
      for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
        	link[i][j] = Link[i][j];
        }
      }

      
 
    }
  }
  
  return 0;
}
