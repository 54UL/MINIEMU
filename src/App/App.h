#ifndef APP_H
#define APP_H

#include <stdint.h>

typedef enum {Keyboard, Window, System} ActionType;
typedef enum {Start, Stop, Reset, Quit} ShellAction;
typedef enum {Idle, Starting, Running, Stopped, Exception} ShellState;

//Models
typedef struct 
{
    ActionType  type;
    uint8_t     code;
    uint8_t     value;
} ActionArg;

//Callbacks
typedef void (*StepCallback)(unsigned int * pixels);
typedef void (*ActionCallback)(const char inputCode);
typedef void (*ShellCallback)(void * data);

typedef struct
{
    void       (*Init)(void);
    void       (*UpdateFrame)(uint32_t *pixels);
    void       (*OnInput)(const char code);
    uint8_t    (*Shown)(void);
    void       (*ShellAction)(const ShellAction action, ShellCallback callback);
    void       (*SetState)(const ShellState state);
    ShellState (*GetState)();
} EmulatorShell;

typedef struct 
{       
    void        (*Init)(uint16_t w, uint16_t h, ActionCallback eventCallback, EmulatorShell * shell);
    uint8_t     (*Render)(StepCallBack renderCallback);//todo: add input
    void        (*Reset)(void);
    void        (*Exit)(void);
} App;

#endif