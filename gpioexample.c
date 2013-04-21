#include <stdio.h>
#include <sys/types.h>
#include <sys/gpio.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
* author teverett
*/
int main (int argc, char *argv[])
	{
	char *device = "/dev/gpioc0";
	int gpiofd = open(device, O_RDWR);
	if (-1!=gpiofd)
		{
		// get total pins
		int maxpin=0;
		if (ioctl(gpiofd, GPIOMAXPIN, &maxpin) < 0) 
			{
			perror("ioctl(GPIOMAXPIN)");
			exit(1);
			}
			else
			{
			printf("GPIO has %d pins\n",maxpin);
			// walk the pins
			printf("pin# description capabilties flags\n");
			for (int i = 0; i <= maxpin; i++)
				{
				struct gpio_pin pinStatus;
				pinStatus.gp_pin=i;
				int r = ioctl(gpiofd, GPIOGETCONFIG, &pinStatus);
				if ( r>= 0)
					{
					printf("%i: %s  0x%x  0x%x\n",i, pinStatus.gp_name, pinStatus.gp_caps, pinStatus.gp_flags);
					}
					else 
					{
					printf("failed to get status of pin %d with status %d\n",i,r);
					}				
				} 
			}
		} 
		else 
		{
		printf("failed to open device with error%d\n",gpiofd);
		}	
	}

/*
* GPIO header is here: /usr/include/sys/gpio.h
*/

