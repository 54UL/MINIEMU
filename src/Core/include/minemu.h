#ifndef MINEMU_H
#define MINEMU_H
#include <stdint.h>

typedef enum {Keyboard, Window, System} ActionType;
typedef enum {Start, Stop, Reset, Quit} ShellAction;
typedef enum {Idle, Starting, Running, Stopped, Exception} ShellState;

//Callbacks
typedef void (*StepCallback)(unsigned int * pixels);
typedef void (*ActionCallback)(const char inputCode);
typedef void (*ShellCallback)(void * data);

typedef struct 
{
    uint8_t         (*LoadProgram)(const char * filePath);
    void            (*QuitProgram)();
    int             (*TickEmulation)();
    int             (*TickDelayTimer)();
    void            (*SetEmulationContext)(const void * context);
} EmulationApi;

//Models
typedef struct 
{
    ActionType  type;
    uint8_t     code;
    uint8_t     value;
} ActionArg;

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
    uint8_t     (*Render)(StepCallback renderCallback);//todo: add input
    void        (*Reset)(void);
    void        (*Exit)(void);
} AppApi;

#endif