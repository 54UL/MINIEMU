#ifndef APP_H
#define APP_H

#include <stdint.h>

typedef enum {Keyboard, Window, System} ActionType;

//Models
typedef struct 
{
    ActionType  type;
    uint8_t     code;
    uint8_t     value;
} ActionArg;

//CallBacks
typedef void (*StepCallBack)(unsigned int * pixels);
typedef void (*ActionCallback)(const char inputCode);

typedef struct
{
    void    (*Init)(void);
    void    (*UpdateFrame)(uint32_t *pixels);
    void    (*OnInput)(const char code);
    uint8_t (*Shown)(void);
} EmulatorShell;

typedef struct 
{       
    void        (*Init)(uint16_t w, uint16_t h, ActionCallback eventCallback, EmulatorShell * shell);
    uint8_t     (*Render)(StepCallBack renderCallback);//todo: add input
    void        (*Reset)(void);
    void        (*Exit)(void);
} App;

#endif