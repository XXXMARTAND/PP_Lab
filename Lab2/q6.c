#include<stdio.h>
#include"mpi.h"
#include<string.h>
#include<ctype.h>
#define mc MPI_COMM_WORLD
int main(int argc, char* argv[])
{
  FILE *f;
  int rank,size,k,j,tot=0,l=1;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(mc,&rank);
  MPI_Comm_size(mc,&size);
  char arr[200],str[200],arr1[10]="<TEXT>",arr2[10]="</TEXT>";
  char *ca,*cb;
  MPI_Status status;
  if(rank==0)
  {
    f=fopen("in.txt","r");
    while(fgets(str,sizeof(str),f))
    {
      if((ca=strstr(str,arr1)) && (cb=strstr(str,arr2)))
      {
        ca+=6;
        j=0;
        memset(arr,'\0',sizeof(arr));
        while(ca!=cb)
        {
          arr[j++]=ca[0];
          ca++;
        }
        MPI_Send(arr,150,MPI_CHAR,l,l,mc);
        l++;
      }
    }
    for(int i=1;i<size;i++)
    {
      MPI_Recv(&k,1,MPI_INT,i,i*10,mc,&status);
      tot+=k;
    }
    printf("Total is %d\n",tot);
  }
  else
  {
    MPI_Recv(str,150,MPI_CHAR,0,rank,mc,&status);
    k=1;
    for(int i=0;i<strlen(str);i++)
    {
      if(str[i]==' ' && str[i+1]!=' ')
        k++;
    }
    MPI_Send(&k,1,MPI_INT,0,rank*10,mc);
  }
  MPI_Finalize();
}
