#define BUTTONS_PORT	PORTD
#define BUTTONS_DD		DDRD
#define BUTTONS_PINS	PIND
#define BUTTON1_PIN		PD2

#define BUTTON_SHORT_DELAY	5
#define BUTTON_LONG_DELAY	55

static char butt_state;
static char b1_count;

char init_buttons(void);
char butt_job (void);