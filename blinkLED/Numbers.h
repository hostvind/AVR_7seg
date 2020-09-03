#define DIGITS 3

#define seg_0 0x3F
#define seg_1 0x06
#define seg_2 0x5B
#define seg_3 0x4F
#define seg_4 0x66
#define seg_5 0x6D
#define seg_6 0x7D
#define seg_7 0x07
#define seg_8 0x7F
#define seg_9 0x6F

#define DIGIT_DISP_PORT	PORTC
#define DIGIT_DISP_DD	DDRC

#define DIGIT_SEL_PORT	PORTA
#define DIGIT_SEL_DD	DDRA
#define DIGIT1_PIN		PA5
#define DIGIT2_PIN		PA6
#define DIGIT3_PIN		PA7

static char disp_select=1;
static char disp_arr[3]={0,5,2};
char nums[10] = {seg_0, seg_1, seg_2, seg_3, seg_4, seg_5, seg_6, seg_7, seg_8, seg_9};

char init_7seg	(void);
char dig_set (char* array);
char dig_run (char MODE);
char dig_sel (char selection);
char dig_show (char digit);