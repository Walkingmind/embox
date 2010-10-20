/**
 * @file
 *
 * @date 17.10.2010
 * @author Darya Dzendzik
 */

#include <embox/test.h>
#include <drivers/lcd.h>
#include <types.h>

/* picture "embox"*/

EMBOX_TEST(run_picture);

extern int display_draw(uint8_t, uint8_t, uint8_t, uint8_t, char *);

static int run_picture(void) {
/*Part of "E" "M" "B" "O" */
	char pict_buff1[8] = {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF};
	char pict_buff2[8] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0};
	char pict_buff4[8] = {0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF};
	char pict_buff3[8] = {0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF};

	//HERE MAY BE SOME STRANGE
/*part of "X"*/
	char pict_buff5[8] = {0xC3, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC3};
	char pict_buff8[8] = {0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xFC, 0x7F};
	char pict_buff9[8] = {0xFF, 0x3F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00};
	char pict_buff7[8] = {0xFF, 0xFC, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00};
	char pict_buff6[8] = {0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x3F, 0xFF};
	char pict_buff10[8] = {0xFF, 0x3F, 0x0F, 0x03, 0x03, 0x0F, 0x3F, 0xFF};
	char pict_buff11[8] = {0xFF, 0xFC, 0xF0, 0xC0, 0xC0, 0xF0, 0xFC, 0xFF};


#if 0
/*e*/
	/*2*/	display_draw(2, 2, 1, 8, &pict_buff1[0]);
	/*3*/	display_draw(10, 2, 1, 8, &pict_buff3[0]);
	/*13*/	display_draw(2, 3, 1, 8, &pict_buff1[0]);
	/*14*/	display_draw(10, 3, 1, 8, &pict_buff4[0]);
	/*23*/	display_draw(2, 4, 1, 8, &pict_buff1[0]);
	/*24*/	display_draw(10, 4, 1, 8, &pict_buff2[0]);
/*m*/
	/*4*/	display_draw(18, 2, 1, 8, &pict_buff1[0]);
	/*5*/	display_draw(26, 2, 1, 8, &pict_buff2[0]);
	/*6*/	display_draw(34, 2, 1, 8, &pict_buff2[0]);
	/*15*/	display_draw(18, 3, 1, 8, &pict_buff1[0]);
	/*16*/	display_draw(26, 3, 1, 8, &pict_buff1[0]);
	/*17*/	display_draw(34, 3, 1, 8, &pict_buff1[0]);
	/*25*/	display_draw(18, 4, 1, 8, &pict_buff1[0]);
	/*26*/	display_draw(26, 4, 1, 8, &pict_buff1[0]);
	/*27*/	display_draw(34, 4, 1, 8, &pict_buff1[0]);
/*b*/
	/*1*/	display_draw(42, 1, 1, 8, &pict_buff1[0]);
	/*7*/	display_draw(42, 2, 1, 8, &pict_buff1[0]);
	/*18*/	display_draw(42, 3, 1, 8, &pict_buff1[0]);
	/*19*/	display_draw(50, 3, 1, 8, &pict_buff3[0]);
	/*28*/	display_draw(42, 4, 1, 8, &pict_buff1[0]);
	/*29*/	display_draw(50, 4, 1, 8, &pict_buff4[0]);
/*o*/
	/*8*/	display_draw(58, 2, 1, 8, &pict_buff1[0]);
	/*9*/	display_draw(66, 2, 1, 8, &pict_buff3[0]);
	/*20*/	display_draw(58, 3, 1, 8, &pict_buff1[0]);
	/*21*/	display_draw(66, 3, 1, 8, &pict_buff1[0]);
	/*30*/	display_draw(58, 4, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 4, 1, 8, &pict_buff4[0]);
/*x*/
	/*10*/	display_draw(74, 2, 1, 8, &pict_buff6[0]);
	/*11*/	display_draw(82, 2, 1, 8, &pict_buff11[0]);
	/*12*/	display_draw(90, 2, 1, 8, &pict_buff9[0]);
	/*22*/	display_draw(82, 3, 1, 8, &pict_buff5[0]);
	/*32*/	display_draw(74, 4, 1, 8, &pict_buff8[0]);
	/*33*/	display_draw(82, 4, 1, 8, &pict_buff10[0]);
	/*34*/	display_draw(90, 4, 1, 8, &pict_buff7[0]);
#else
	//int i;
	//uint8_t buff[1][8] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
	//for (i = 0C Ly`v; i < 5; i ++) {
	display_clear_screan();
/*1 line*/
	/*e*/
	/*23*/	display_draw(2, 0, 1, 8, &pict_buff1[0]);
	/*24*/	display_draw(10, 0, 1, 8, &pict_buff2[0]);

	/*m*/
	/*25*/	display_draw(18, 0, 1, 8, &pict_buff1[0]);
	/*26*/	display_draw(26, 0, 1, 8, &pict_buff1[0]);
	/*27*/	display_draw(34, 0, 1, 8, &pict_buff1[0]);
	
	/*b*/
	/*30*/	display_draw(58, 0, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 0, 1, 8, &pict_buff4[0]);
	
	/*o*/
	/*30*/	display_draw(58, 0, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 0, 1, 8, &pict_buff4[0]);
	
	/*x*/
	/*32*/	display_draw(74, 0, 1, 8, &pict_buff8[0]);
	/*33*/	display_draw(82, 0, 1, 8, &pict_buff10[0]);
	/*34*/	display_draw(90, 0, 1, 8, &pict_buff7[0]);
	usleep(250);

/*2 line*/
	display_clear_screan();
	/*e*/
	/*13*/	display_draw(2, 0, 1, 8, &pict_buff1[0]);
	/*14*/	display_draw(10, 0, 1, 8, &pict_buff4[0]);
	/*23*/	display_draw(2, 1, 1, 8, &pict_buff1[0]);
	/*24*/	display_draw(10, 1, 1, 8, &pict_buff2[0]);
	
	/*e*/
	/*15*/	display_draw(18, 0, 1, 8, &pict_buff1[0]);
	/*16*/	display_draw(26, 0, 1, 8, &pict_buff1[0]);
	/*17*/	display_draw(34, 0, 1, 8, &pict_buff1[0]);
	/*25*/	display_draw(18, 1, 1, 8, &pict_buff1[0]);
	/*26*/	display_draw(26, 1, 1, 8, &pict_buff1[0]);
	/*27*/	display_draw(34, 1, 1, 8, &pict_buff1[0]);
	
	/*b*/
	/*18*/	display_draw(42, 0, 1, 8, &pict_buff1[0]);
	/*19*/	display_draw(50, 0, 1, 8, &pict_buff3[0]);
	/*28*/	display_draw(42, 1, 1, 8, &pict_buff1[0]);
	/*29*/	display_draw(50, 1, 1, 8, &pict_buff4[0]);
	
	/*o*/
	/*20*/	display_draw(58, 0, 1, 8, &pict_buff1[0]);
	/*21*/	display_draw(66, 0, 1, 8, &pict_buff1[0]);
	/*30*/	display_draw(58, 1, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 1, 1, 8, &pict_buff4[0]);
	
	/*x*/	
	/*22*/	display_draw(82, 0, 1, 8, &pict_buff5[0]);
	/*32*/	display_draw(74, 1, 1, 8, &pict_buff8[0]);
	/*33*/	display_draw(82, 1, 1, 8, &pict_buff10[0]);
	/*34*/	display_draw(90, 1, 1, 8, &pict_buff7[0]);
	usleep(250);
/*3 line*/
	/*e*/
	display_clear_screan();
	/*2*/	display_draw(2, 0, 1, 8, &pict_buff1[0]);
	/*3*/	display_draw(10, 0, 1, 8, &pict_buff3[0]);
	/*13*/	display_draw(2, 1, 1, 8, &pict_buff1[0]);
	/*14*/	display_draw(10, 1, 1, 8, &pict_buff4[0]);
	/*23*/	display_draw(2, 2, 1, 8, &pict_buff1[0]);
	/*24*/	display_draw(10, 2, 1, 8, &pict_buff2[0]);
	
	/*m*/
	/*4*/	display_draw(18, 0, 1, 8, &pict_buff1[0]);
	/*5*/	display_draw(26, 0, 1, 8, &pict_buff2[0]);
	/*6*/	display_draw(34, 0, 1, 8, &pict_buff2[0]);
	/*15*/	display_draw(18, 1, 1, 8, &pict_buff1[0]);
	/*16*/	display_draw(26, 1, 1, 8, &pict_buff1[0]);
	/*17*/	display_draw(34, 1, 1, 8, &pict_buff1[0]);
	/*25*/	display_draw(18, 2, 1, 8, &pict_buff1[0]);
	/*26*/	display_draw(26, 2, 1, 8, &pict_buff1[0]);
	/*27*/	display_draw(34, 2, 1, 8, &pict_buff1[0]);
	
	/*b*/
	/*7*/	display_draw(42, 0, 1, 8, &pict_buff1[0]);
	/*18*/	display_draw(42, 1, 1, 8, &pict_buff1[0]);
	/*19*/	display_draw(50, 1, 1, 8, &pict_buff3[0]);
	/*28*/	display_draw(42, 2, 1, 8, &pict_buff1[0]);
	/*29*/	display_draw(50, 2, 1, 8, &pict_buff4[0]);
	
	/*o*/
	/*8*/	display_draw(58, 0, 1, 8, &pict_buff1[0]);
	/*9*/	display_draw(66, 0, 1, 8, &pict_buff3[0]);
	/*20*/	display_draw(58, 1, 1, 8, &pict_buff1[0]);
	/*21*/	display_draw(66, 1, 1, 8, &pict_buff1[0]);
	/*30*/	display_draw(58, 2, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 2, 1, 8, &pict_buff4[0]);
	
	/*x*/
	/*10*/	display_draw(74, 0, 1, 8, &pict_buff6[0]);
	/*11*/	display_draw(82, 0, 1, 8, &pict_buff11[0]);
	/*12*/	display_draw(90, 0, 1, 8, &pict_buff9[0]);
	/*22*/	display_draw(82, 1, 1, 8, &pict_buff5[0]);
	/*32*/	display_draw(74, 2, 1, 8, &pict_buff8[0]);
	/*33*/	display_draw(82, 2, 1, 8, &pict_buff10[0]);
	/*34*/	display_draw(90, 2, 1, 8, &pict_buff7[0]);
	usleep(250);
	
	display_clear_screan();
/*4 line*/
	/*e*/
	/*2*/	display_draw(2, 1, 1, 8, &pict_buff1[0]);
	/*3*/	display_draw(10, 1, 1, 8, &pict_buff3[0]);
	/*13*/	display_draw(2, 2, 1, 8, &pict_buff1[0]);
	/*14*/	display_draw(10, 2, 1, 8, &pict_buff4[0]);
	/*23*/	display_draw(2, 3, 1, 8, &pict_buff1[0]);
	/*24*/	display_draw(10, 3, 1, 8, &pict_buff2[0]);
	
	/*m*/
	/*4*/	display_draw(18, 1, 1, 8, &pict_buff1[0]);
	/*5*/	display_draw(26, 1, 1, 8, &pict_buff2[0]);
	/*6*/	display_draw(34, 1, 1, 8, &pict_buff2[0]);
	/*15*/	display_draw(18, 2, 1, 8, &pict_buff1[0]);
	/*16*/	display_draw(26, 2, 1, 8, &pict_buff1[0]);
	/*17*/	display_draw(34, 2, 1, 8, &pict_buff1[0]);
	/*25*/	display_draw(18, 3, 1, 8, &pict_buff1[0]);
	/*26*/	display_draw(26, 3, 1, 8, &pict_buff1[0]);
	/*27*/	display_draw(34, 3, 1, 8, &pict_buff1[0]);
	
	/*b*/
	/*1*/	display_draw(42, 0, 1, 8, &pict_buff1[0]);
	/*7*/	display_draw(42, 1, 1, 8, &pict_buff1[0]);
	/*18*/	display_draw(42, 2, 1, 8, &pict_buff1[0]);
	/*19*/	display_draw(50, 2, 1, 8, &pict_buff3[0]);
	/*28*/	display_draw(42, 3, 1, 8, &pict_buff1[0]);
	/*29*/	display_draw(50, 3, 1, 8, &pict_buff4[0]);
	
	/*o*/
	/*8*/	display_draw(58, 1, 1, 8, &pict_buff1[0]);
	/*9*/	display_draw(66, 1, 1, 8, &pict_buff3[0]);
	/*20*/	display_draw(58, 2, 1, 8, &pict_buff1[0]);
	/*21*/	display_draw(66, 2, 1, 8, &pict_buff1[0]);
	/*30*/	display_draw(58, 3, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 3, 1, 8, &pict_buff4[0]);
	
	/*x*/
	/*10*/	display_draw(74, 1, 1, 8, &pict_buff6[0]);
	/*11*/	display_draw(82, 1, 1, 8, &pict_buff11[0]);
	/*12*/	display_draw(90, 1, 1, 8, &pict_buff9[0]);
	/*22*/	display_draw(82, 2, 1, 8, &pict_buff5[0]);
	/*32*/	display_draw(74, 3, 1, 8, &pict_buff8[0]);
	/*33*/	display_draw(82, 3, 1, 8, &pict_buff10[0]);
	/*34*/	display_draw(90, 3, 1, 8, &pict_buff7[0]);
	usleep(250);
	
	display_clear_screan();
/*5 line*/
	/*e*/
	/*2*/	display_draw(2, 2, 1, 8, &pict_buff1[0]);
	/*3*/	display_draw(10, 2, 1, 8, &pict_buff3[0]);
	/*13*/	display_draw(2, 3, 1, 8, &pict_buff1[0]);
	/*14*/	display_draw(10, 3, 1, 8, &pict_buff4[0]);
	/*23*/	display_draw(2, 4, 1, 8, &pict_buff1[0]);
	/*24*/	display_draw(10, 4, 1, 8, &pict_buff2[0]);
	
	/*m*/
	/*4*/	display_draw(18, 2, 1, 8, &pict_buff1[0]);
	/*5*/	display_draw(26, 2, 1, 8, &pict_buff2[0]);
	/*6*/	display_draw(34, 2, 1, 8, &pict_buff2[0]);
	/*15*/	display_draw(18, 3, 1, 8, &pict_buff1[0]);
	/*16*/	display_draw(26, 3, 1, 8, &pict_buff1[0]);
	/*17*/	display_draw(34, 3, 1, 8, &pict_buff1[0]);
	/*25*/	display_draw(18, 4, 1, 8, &pict_buff1[0]);
	/*26*/	display_draw(26, 4, 1, 8, &pict_buff1[0]);
	/*27*/	display_draw(34, 4, 1, 8, &pict_buff1[0]);
	
	/*b*/
	/*1*/	display_draw(42, 1, 1, 8, &pict_buff1[0]);
	/*7*/	display_draw(42, 2, 1, 8, &pict_buff1[0]);
	/*18*/	display_draw(42, 3, 1, 8, &pict_buff1[0]);
	/*19*/	display_draw(50, 3, 1, 8, &pict_buff3[0]);
	/*28*/	display_draw(42, 4, 1, 8, &pict_buff1[0]);
	/*29*/	display_draw(50, 4, 1, 8, &pict_buff4[0]);
	
	/*o*/
	/*8*/	display_draw(58, 2, 1, 8, &pict_buff1[0]);
	/*9*/	display_draw(66, 2, 1, 8, &pict_buff3[0]);
	/*20*/	display_draw(58, 3, 1, 8, &pict_buff1[0]);
	/*21*/	display_draw(66, 3, 1, 8, &pict_buff1[0]);
	/*30*/	display_draw(58, 4, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 4, 1, 8, &pict_buff4[0]);
	
	/*x*/
	/*10*/	display_draw(74, 2, 1, 8, &pict_buff6[0]);
	/*11*/	display_draw(82, 2, 1, 8, &pict_buff11[0]);
	/*12*/	display_draw(90, 2, 1, 8, &pict_buff9[0]);
	/*22*/	display_draw(82, 3, 1, 8, &pict_buff5[0]);
	/*32*/	display_draw(74, 4, 1, 8, &pict_buff8[0]);
	/*33*/	display_draw(82, 4, 1, 8, &pict_buff10[0]);
	/*34*/	display_draw(90, 4, 1, 8, &pict_buff7[0]);
	usleep(250);

	display_clear_screan();
/*6 line*/
	/*e*/
	/*2*/	display_draw(2, 3, 1, 8, &pict_buff1[0]);
	/*3*/	display_draw(10, 3, 1, 8, &pict_buff3[0]);
	/*13*/	display_draw(2, 4, 1, 8, &pict_buff1[0]);
	/*14*/	display_draw(10, 4, 1, 8, &pict_buff4[0]);
	/*23*/	display_draw(2, 5, 1, 8, &pict_buff1[0]);
	/*24*/	display_draw(10, 5, 1, 8, &pict_buff2[0]);
	
	/*m*/
	/*4*/	display_draw(18, 3, 1, 8, &pict_buff1[0]);
	/*5*/	display_draw(26, 3, 1, 8, &pict_buff2[0]);
	/*6*/	display_draw(34, 3, 1, 8, &pict_buff2[0]);
	/*15*/	display_draw(18, 4, 1, 8, &pict_buff1[0]);
	/*16*/	display_draw(26, 4, 1, 8, &pict_buff1[0]);
	/*17*/	display_draw(34, 4, 1, 8, &pict_buff1[0]);
	/*25*/	display_draw(18, 5, 1, 8, &pict_buff1[0]);
	/*26*/	display_draw(26, 5, 1, 8, &pict_buff1[0]);
	/*27*/	display_draw(34, 5, 1, 8, &pict_buff1[0]);
	
	/*b*/
	/*1*/	display_draw(42, 2, 1, 8, &pict_buff1[0]);
	/*7*/	display_draw(42, 3, 1, 8, &pict_buff1[0]);
	/*18*/	display_draw(42, 4, 1, 8, &pict_buff1[0]);
	/*19*/	display_draw(50, 4, 1, 8, &pict_buff3[0]);
	/*28*/	display_draw(42, 5, 1, 8, &pict_buff1[0]);
	/*29*/	display_draw(50, 5, 1, 8, &pict_buff4[0]);
	
	/*o*/
	/*8*/	display_draw(58, 3, 1, 8, &pict_buff1[0]);
	/*9*/	display_draw(66, 3, 1, 8, &pict_buff3[0]);
	/*20*/	display_draw(58, 4, 1, 8, &pict_buff1[0]);
	/*21*/	display_draw(66, 4, 1, 8, &pict_buff1[0]);
	/*30*/	display_draw(58, 5, 1, 8, &pict_buff1[0]);
	/*31*/	display_draw(66, 5, 1, 8, &pict_buff4[0]);
	
	/*x*/
	/*10*/	display_draw(74, 3, 1, 8, &pict_buff6[0]);
	/*11*/	display_draw(82, 3, 1, 8, &pict_buff11[0]);
	/*12*/	display_draw(90, 3, 1, 8, &pict_buff9[0]);
	/*22*/	display_draw(82, 4, 1, 8, &pict_buff5[0]);
	/*32*/	display_draw(74, 5, 1, 8, &pict_buff8[0]);
	/*33*/	display_draw(82, 5, 1, 8, &pict_buff10[0]);
	/*34*/	display_draw(90, 5, 1, 8, &pict_buff7[0]);
	usleep(250);
	//display_draw(18, 32, 8, 8, buff);
#endif
	return 0;
}


