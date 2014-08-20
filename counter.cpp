#include "camac.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "opt.h"

Crate crate(0,5);
/*int Reset_data(int position)
{
  int a,XQ;
  unsigned int data[8];
for (a=0;a<8;a++)
	{
	  XQ = CAM(crate.GetFd(),NAF(position,a,2),&data[a]);
	  printf("data%d = %d  ",a,data[a]);
          printf("XQ=%d\n", XQ&0x3);    
        }
}

int Read_data(int position)
{
  int a,XQ;
  unsigned int data[8];
for (a=0;a<8;a++)
	{
	  XQ = CAM(crate.GetFd(),NAF(position,a,0),&data[a]);
	  printf("data%d = %d  ",a,data[a]);
          printf("XQ=%d\n", XQ&0x3);    
        }
}*/
int main(int argc, char ** argv)
{
char program_name[1024];
int channel;
int position;
double T;
int diskr_value;
int FEU_voltage;
int status =0;
sscanf(argv[0],"%s",&program_name);
if(argc!=7)
{
cerr << "Usage: " << program_name << " <program_name> <channel> <position> <ticks> <diskrimination value> <feu voltage> <status>" << endl;
exit(1);
}
sscanf(argv[1],"%d",&channel);
sscanf(argv[2],"%d",&position);
sscanf(argv[3],"%lf",&T);
sscanf(argv[4],"%lf",&diskr_value);
sscanf(argv[5],"%lf",&FEU_voltage);
sscanf(argv[6],"%lf",&status);
cout << program_name << " channel = " << channel << endl << " position = " << position << endl << " count time = "<< T << endl "diskriminator value = " << diskr_value << endl <<"feu voltage = "<< feu_voltage << endl;
crate.C(); 
crate.Z();
Timer timer(&crate,position);
Counter counter(&crate,position+1);
Diskriminator diskr(&crate,position+/*???*/);
Coincidense con(&crate,position+4);
HVPS hvps(&crate,position);
cout << "Time is set to " << timer.GetTime() << endl;
diskr.D_SetLevel(0,diskr_value);
diskr.D_SetLevel(0,diskr_value);
hvps.HVPS_SetV(0,feu_voltage); 
hvps.HVPS_SetV(1,feu_voltage);
con.SetMask(1,0);
if(status==1){
hvps->HVPS_On(0);
hvps->HVPS_On(1);
printf("FEU is turned ON");
while(1) 
{
	counter.ResetCounter();
	timer.Reset();
	timer.SetTime(T);
	timer.Start();
	timer.Wait();
	//CAM_LWAIT(crate.GetFd(),position,-1);
	for(int a=0;a<4;a++)
		{
		double data =  counter.ReadCounter(a)/T*1e-6;
		printf("%9.6f\t",data);         
		}
		printf("\n");

}
}
if(status==2)
		{
			hvps.HVPS_ResetV(0);
			hvps.HVPS_ResetV(1);
			cout<<"FEU voltage has reseted\n"<<endl;		
		}
if (status==0)
		{
			hvps->HVPS_Off(0);
			hvps->HVPS_Off(1);
			cout<<"FEU has turned off\n"<<endl;		
		}

}
