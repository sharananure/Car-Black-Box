#include <xc.h>

/* Enum for maintaining the app state */
typedef enum 
{
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log
} State_t;



extern State_t state; // App state

extern unsigned char key;
extern int event_index;
extern unsigned int collision;
extern unsigned int speed;
extern unsigned int count;
extern unsigned int event_count;
extern unsigned int stored_event_index;
extern unsigned char time[];
extern unsigned char event[9][3];
extern unsigned int address;
extern int read_add;

extern unsigned char read_ev[10][15];

//Function declarations
void external_eeprom_store(void);
void get_time(void);
void read_event(void);





//Dashboard function declaration
void view_dashboard(void);

//Storing events function declaration
void event_store(void);

//Password function declaration
void password(void);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void read_event(void);

//Change password function declaration
void change_password(void);

//Set time function declaration
void set_time(void);

//Download log function _ decleration
void download_log(void);

//Clear log function declaration
void clear_log(void);