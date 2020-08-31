#define D_SW_1_PIN	PB1
#define D_SW_1_PINS	PINB
#define D_SW_1_PORT	PORTB
#define D_SW_2_PIN	PB2
#define D_SW_2_PINS	PINB
#define D_SW_2_PORT	PORTB
#define D_SW_3_PIN	PB3
#define D_SW_3_PINS	PINB
#define D_SW_3_PORT	PORTB


int init_TIM (void);
int init_GPIO (void);
char dig_sel (char selection);
char dig_show (char digit);
int main(void);