/*
 * Hidraw Userspace Example
 *
 * Copyright (c) 2010 Alan Ott <alan@signal11.us>
 * Copyright (c) 2010 Signal 11 Software
 *
 * The code may be used by anyone for any purpose,
 * and can serve as a starting point for developing
 * applications using hidraw.
 * Under GPL version 3
 */

/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>


/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


struct LOGITECH_BUTTON {
	char buttmode;
	char keymod;
	char keyvalue;
};

struct LOGITECH_SETTINGS {
	char feature_request; // F3 for 1-mode F4 for 2-mode F5 for 3-mode
	char R;
	char G;
	char B;
	char lighteffect; // 0 -> fest ; 1 -> pulse ; 2 -> rainbow
	char effectspeed; // begins with 15 ends with 0
	char g7;
	char g8;
	char g9;
	char g10;
	char g11;
	char samples; // begins with 0x07(125) 0x06(142) 0x05(166) 0x04(200) 0x03(250) 0x02(333) 0x01(500) 0x00(1000)
	char defaultdpi; // begins with 0x04(200dpi) ends 0xa4(8200dpi) (50dpi increment )
	char dpisteps; // begins with 1 ends with 4
	char dpi1; // values like defaultdpi
	char dpi2; // values like defaultdpi
	char dpi3;
	char dpi4;
	char g19;
	char g20;
	char g21;
	char g22;
	char g23;
	char g24;
	char g25;
	char g26;
	char g27;
	char g28;
	char g29;
	char g30;
	char g31;
	struct LOGITECH_BUTTON leftbutton;
	struct LOGITECH_BUTTON rightbutton;
	struct LOGITECH_BUTTON middlebutton;
	struct LOGITECH_BUTTON leftscrollbutton;
	struct LOGITECH_BUTTON rightscrollbutton;
	struct LOGITECH_BUTTON mostrightbutton;
	struct LOGITECH_BUTTON g7button;
	struct LOGITECH_BUTTON g8button;
	struct LOGITECH_BUTTON g9button;
	struct LOGITECH_BUTTON g10button;
	struct LOGITECH_BUTTON g11button;
	struct LOGITECH_BUTTON g12button;
	struct LOGITECH_BUTTON g13button;
	struct LOGITECH_BUTTON g14button;
	struct LOGITECH_BUTTON g15button;
	struct LOGITECH_BUTTON g16button;
	struct LOGITECH_BUTTON g17button;
	struct LOGITECH_BUTTON g18button;
	struct LOGITECH_BUTTON g19button;
	struct LOGITECH_BUTTON g20button;
	char R1; //alternativemodes
	char G1;
	char B1;
	struct LOGITECH_BUTTON leftbutton1;
	struct LOGITECH_BUTTON rightbutton1;
	struct LOGITECH_BUTTON middlebutton1;
	struct LOGITECH_BUTTON leftscrollbutton1;
	struct LOGITECH_BUTTON rightscrollbutton1;
	struct LOGITECH_BUTTON mostrightbutton1;
	struct LOGITECH_BUTTON g7button1;
	struct LOGITECH_BUTTON g8button1;
	struct LOGITECH_BUTTON g9button1;
	struct LOGITECH_BUTTON g10button1;
	struct LOGITECH_BUTTON g11button1;
	struct LOGITECH_BUTTON g12button1;
	struct LOGITECH_BUTTON g13button1;
	struct LOGITECH_BUTTON g14button1;
	struct LOGITECH_BUTTON g15button1;
	struct LOGITECH_BUTTON g16button1;
	struct LOGITECH_BUTTON g17button1;
	struct LOGITECH_BUTTON g18button1;
	struct LOGITECH_BUTTON g19button1;
	struct LOGITECH_BUTTON g20button1;
	} l;

int main(int argc, char **argv)
{
	int fd;
	int i, res;
	char buf[256];
	fd = open(argv[1], O_RDWR|O_NONBLOCK);

	if (fd < 0) {
		perror("Unable to open device");
		return 1;
	}

	memset(buf, 0x0, sizeof(buf));

	/* Get Feature */
	buf[0] = 0xF3; /* Report Number  0xF3 for mode1 0xF4 for mode2 0xF5 for mode3*/
	res = ioctl(fd, HIDIOCGFEATURE(154), buf);
	if (res < 0) {
		perror("HIDIOCGFEATURE");
	} else {
		for (i = 1; i <= res; i++) {
			printf("%03i:%02hhx ", i,buf[i-1]);
			printf("\n");
		}
		puts("\n");
	}

	/* Set Feature */
	memcpy(&l,buf,154);
	printf("%hhx\n",l.g7button.buttmode);
	printf("%hhx\n",l.G1);
	printf("%hhx\n",l.B1);
	l.G1=255;
	l.R1=255;
	l.B1=255;
	l.G=20;
	l.R=20;
	l.B=20;
	l.lighteffect=0;
	l.effectspeed=0;
	l.samples=0x02;
	l.defaultdpi=0xa4;
	l.dpisteps=2;
	l.dpi1=0xa4;
	l.dpi2=32;
	
	l.g7button1.buttmode=0x13;
	l.g7button1.keymod=0;
	l.g7button1.keyvalue=0;
	l.g7button.buttmode=0x13;
	l.g7button.keymod=0;
	l.g7button.keyvalue=0;
	
	res = ioctl(fd, HIDIOCSFEATURE(154), &l);
	if (res < 0) 
		perror("HIDIOCSFEATURE");

	close(fd);
	return 0;
}

