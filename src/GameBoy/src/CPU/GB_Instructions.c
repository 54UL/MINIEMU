#include <CPU/GB_Instructions.h>
#include <CPU/GB_Bus.h>
#include <CPU/GB_Registers.h>

#define xxx 0x38
#define yyy 0x07

// 8-BIT LOAD INSTRUCTIONS
uint8_t GB_LD_R_R(SystemContext *ctx)
{
    // encoding: b01xxxyyy/various
    const uint8_t r1 = (ctx->registers->INSTRUCTION & xxx) >> 3;
    const uint8_t r2 = (ctx->registers->INSTRUCTION & yyy);

    GB_SetReg8(ctx->registers, r1, GB_GetReg8(ctx->registers, r2));

    return 4; // instruction clock cycles
}

uint8_t GB_LD_R_N(SystemContext *ctx)
{
    // encoding: 0b00xxx110/various + n

    const uint8_t r = (ctx->registers->INSTRUCTION & xxx) >> 3;

    ctx->registers->CPU[r] = GB_BusRead(ctx, ctx->registers->PC++);
    
    return 8; // instruction clock cycles
}

uint8_t GB_LD_R_HL(SystemContext *ctx)
{
    // encoding: 0b01xxx110/various

    const uint8_t r = (ctx->registers->INSTRUCTION & xxx) >> 3;

    ctx->registers->CPU[r] = GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]);
}

uint8_t GB_LD_HL_R(SystemContext *ctx)
{
    // encoding: 0b01110xxx

    const uint8_t r = ctx->registers->INSTRUCTION & yyy;

    GB_SetReg8(ctx->registers, r, GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]));
}

uint8_t GB_LD_HL_N(SystemContext *ctx)
{
    // 0b00110110/0x36 + n
    /*
    opcode = read(PC++)
    if opcode == 0x36:
        n = read(PC++)
        write(HL, n)
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->PC++);

    GB_BusWrite(ctx, ctx->registers->CPU[GB_HL_OFFSET], n);
}

uint8_t GB_LD_A_BC(SystemContext *ctx)
{
    /*
    opcode = read(PC++)
    if opcode == 0x0A:
        A = read(BC)
    */

    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx, ctx->registers->CPU[GB_BC_OFFSET]);
}

uint8_t GB_LD_A_DE(SystemContext *ctx)
{
    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx, ctx->registers->CPU[GB_DE_OFFSET]);
}

uint8_t GB_LD_A_NN(SystemContext *ctx)
{
    /*
    opcode = read(PC++)
    if opcode == 0xFA:
        nn = unsigned_16(lsb=read(PC++), msb=read(PC++))
        A = read(nn)
    */

    const uint8_t lsb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t msb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint16_t nn = (uint16_t)(lsb | (msb << 8));

    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx, nn);
}

uint8_t GB_LD_BC_A(SystemContext *ctx)
{
    GB_BusWrite(ctx, ctx->registers->CPU[GB_BC_OFFSET], GB_GetReg8(ctx->registers, GB_A_OFFSET));
}

uint8_t GB_LD_DE_A(SystemContext *ctx)
{
    GB_BusWrite(ctx, ctx->registers->CPU[GB_DE_OFFSET], GB_GetReg8(ctx->registers, GB_A_OFFSET));
}

uint8_t GB_LD_NN_A(SystemContext *ctx)
{
    const uint8_t lsb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t msb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint16_t nn = (uint16_t)(lsb | (msb << 8));

    GB_BusWrite(ctx, nn, ctx->registers->CPU[GB_A_OFFSET]);
}

uint8_t GB_LDH_A_N(SystemContext *ctx)
{
    /*
        n = read(PC++)
        A = read(unsigned_16(lsb=n, msb=0xFF))
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->PC++);
    const uint16_t u16 = (uint16_t)(n | (0xFF << 8));

    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx, u16);
}

uint8_t GB_LDH_N_A(SystemContext *ctx)
{
    /*
        n = read(PC++)
        write(unsigned_16(lsb=n, msb=0xFF), A)
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->PC++);
    const uint16_t u16 = (uint16_t)(n | (0xFF << 8));

    GB_BusWrite(ctx, u16, ctx->registers->CPU[GB_A_OFFSET]);
}

uint8_t GB_LDH_A_C(SystemContext *ctx)
{
    //A = read(unsigned_16(lsb=C, msb=0xFF))
    const uint16_t u16 = (uint16_t)(GB_GetReg8(ctx->registers, GB_C_OFFSET) | (0xFF << 8));
    GB_SetReg8(ctx->registers, GB_A_OFFSET, GB_BusRead(ctx, u16));
}

uint8_t GB_LDH_C_A(SystemContext *ctx)
{
    //write(unsigned_16(lsb=C, msb=0xFF), A)
    const uint16_t u16 = (uint16_t)(GB_GetReg8(ctx->registers, GB_C_OFFSET) | (0xFF << 8));
    GB_BusWrite(ctx, u16,ctx->registers->CPU[GB_A_OFFSET]);
}

uint8_t GB_LDI_HL_A(SystemContext *ctx)
{
    //write(HL++, A)
    GB_BusWrite(ctx, ctx->registers->CPU[GB_HL_OFFSET]++, GB_GetReg8(ctx->registers, GB_A_OFFSET));
}

uint8_t GB_LDI_A_HL(SystemContext *ctx)
{
    //A = read(HL++)
    GB_SetReg8(ctx->registers, GB_A_OFFSET, GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]++));
}

uint8_t GB_LDD_HL_A(SystemContext *ctx)
{
    //write(HL--, A)
    GB_BusWrite(ctx, ctx->registers->CPU[GB_HL_OFFSET]--, GB_GetReg8(ctx->registers, GB_A_OFFSET));
}

uint8_t GB_LDD_A_HL(SystemContext *ctx)
{
    //A = read(HL--)
    GB_SetReg8(ctx->registers, GB_A_OFFSET, GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]--));
}

// 16 BIT LOAD INSTRUCTIONS
uint8_t GB_LD_RR_NN(SystemContext *ctx)
{
    //encoding: 0b00xx0001, xx = 0x30
    /*
        nn = unsigned_16(lsb=read(PC++), msb=read(PC++))
        BC = nn
    */
    const uint8_t nn = (ctx->registers->INSTRUCTION & 0x30) >> 4;
    const uint8_t lsb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t msb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint16_t u16 = (uint16_t)(lsb | (msb << 8));
    
    ctx->registers->CPU[nn] = u16;
    ctx->registers->CPU[GB_BC_OFFSET] = u16;
}

uint8_t GB_LD_NN_SP(SystemContext *ctx)
{
    //encoding: 0b00001000
    /*
        nn = unsigned_16(lsb=read(PC++), msb=read(PC++))
        write(nn, lsb(SP))
        write(nn+1, msb(SP))
    */

    const uint8_t lsb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t msb = GB_BusRead(ctx, ctx->registers->PC++);
    const uint16_t u16 = (uint16_t)(lsb | (msb << 8));
    const uint8_t spl = ctx->registers->SP & 0xFF;
    const uint8_t sph = (ctx->registers->SP >> 8) & 0xFF;

    GB_BusWrite(ctx, u16, spl);
    GB_BusWrite(ctx, u16 + 1, sph);
}

uint8_t GB_LD_SP_HL(SystemContext *ctx)
{
    //  SP = HL
    ctx->registers->SP = ctx->registers->CPU[GB_HL_OFFSET];
}

uint8_t GB_PUSH_RR(SystemContext *ctx)
{
    //encoding: 0b11xx0101,xx = 0x30
    /*
        SP--
        write(SP--, msb(BC))
        write(SP, lsb(BC))
    */

    const uint8_t rr = (ctx->registers->INSTRUCTION & 0x30) >> 4;
    const uint8_t l = ctx->registers->CPU[rr] & 0xFF;
    const uint8_t h = (ctx->registers->CPU[rr] >> 8) & 0xFF;

    ctx->registers->SP--;
    GB_BusWrite(ctx, ctx->registers->SP--, h);
    GB_BusWrite(ctx, ctx->registers->SP, l);
}

uint8_t GB_POP_RR(SystemContext *ctx)
{
    // encoding: 0b11xx0001
    // BC = unsigned_16(lsb=read(SP++), msb=read(SP++))

    const uint8_t rr = (ctx->registers->INSTRUCTION & 0x30) >> 4;
    const uint8_t l =  GB_BusRead(ctx,ctx->registers->SP++);
    const uint8_t h =  GB_BusRead(ctx,ctx->registers->SP++);

    ctx->registers->CPU[rr] = l | (h << 8);
}

// 8 BIT ALU INSTRUCTIONS
uint8_t GB_ADD_A_R(SystemContext *ctx)
{
    //encoding:0b10000xxx
    /*
        result, carry_per_bit = A + R (example)
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t rr = (ctx->registers->INSTRUCTION & yyy);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] + ctx->registers->CPU[rr];
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 0;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_ADD_A_N(SystemContext *ctx)
{
    //encoding:0b11000110
    /*
        n = read(PC++)
        result, carry_per_bit = A + n
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] + n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 0;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_ADD_A_HL(SystemContext *ctx)
{
    //encoding:0b10000110
    /*
        data = read(HL)
        result, carry_per_bit = A + data
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] + n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 0;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_ADC_A_R(SystemContext *ctx)
{
    //encoding:0b10001xxx
    /*
        result, carry_per_bit = A + flags.C + B
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t rr = (ctx->registers->INSTRUCTION & yyy);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] + ctx->flags->C + ctx->registers->CPU[rr];
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 0;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_ADC_A_N(SystemContext *ctx)
{
    //encoding: 0b11001110
    /*
        n = read(PC++)
        result, carry_per_bit = A + flags.C + n
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] + ctx->flags->C + n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 0;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_ADC_A_HL(SystemContext *ctx)
{
    //encoding: 0b10001110
    /*
        data = read(HL)
        result, carry_per_bit = A + flags.C + data
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET]+ ctx->flags->C + n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 0;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_SUB_R(SystemContext *ctx)
{
    //encoding: 0b10010xxx
    /*
        result, carry_per_bit = A - B
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t rr = (ctx->registers->INSTRUCTION & yyy);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] - ctx->registers->CPU[rr];
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 1;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_SUB_N(SystemContext *ctx)
{
    //encoding: 0b11010110
    /*
        n = read(PC++)
        result, carry_per_bit = A - n
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] - n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 1;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_SUB_HL(SystemContext *ctx)
{
    //encoding: 0b10010110
    /*
        data = read(HL)
        result, carry_per_bit = A - data
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] - n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 1;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_SBC_A_R(SystemContext *ctx)
{
    //encoding: 0b10011xxx
    /*
        result, carry_per_bit = A - flags.C - B
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */
    const uint8_t rr = (ctx->registers->INSTRUCTION & yyy);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] - ctx->flags->C - ctx->registers->CPU[rr];
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 1;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_SBC_A_N(SystemContext *ctx)
{
    //encoding: 0b11011110
    /*
        n = read(PC++)
        result, carry_per_bit = A - flags.C - n
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->PC++);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] - ctx->flags->C - n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 1;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_SBC_A_HL(SystemContext *ctx) 
{
    //encoding: 0b10011110
    /*
        data = read(HL)
        result, carry_per_bit = A - flags.C - data
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */

    const uint8_t n = GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]);
    const uint8_t sum = ctx->registers->CPU[GB_A_OFFSET] - ctx->flags->C - n;
    GB_SetReg8(ctx->registers, GB_A_OFFSET, sum);

    ctx->flags->Z = sum == 0;
    ctx->flags->N = 1;
    ctx->flags->H = sum >> 3 == 0x01;
    ctx->flags->C = sum >> 7 == 0x01;
}

uint8_t GB_AND_R(SystemContext *ctx)
{
    //encoding: 0b10100xxx
    /*
    result = A & B
    A = result
    flags.Z = 1 if result == 0 else 0
    */
}

uint8_t GB_AND_N(SystemContext *ctx)
{
    //encoding: 0b11100110 
    /*
    n = read(PC++)
    result = A & n
    A = result
    flags.Z = 1 if result == 0 else 0
    flags.N = 0
    flags.H = 1
    flags.C = 0
    */
}

uint8_t GB_AND_HL(SystemContext *ctx)
{
    //encoding: 0b10100110
    /*
    data = read(HL)
    result = A & data
    A = result
    flags.Z = 1 if result == 0 else 0
    flags.N = 0
    flags.H = 1
    flags.C = 0
    */
}
uint8_t GB_XOR_R(SystemContext *ctx)
{
    //encoding: 0b10101xxx
    /*
    # example: XOR B
    if opcode == 0xB8:
    result = A ^ B
    A = result
    flags.Z = 1 if result == 0 else 0
    flags.N = 0
    flags.H = 0
    flags.C = 0
    */

}
uint8_t GB_XOR_N(SystemContext *ctx)
{
    //encoding: 0b11101110
    /*
        n = read(PC++)
        result = A ^ n
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 0
        flags.C = 0
    */
}
uint8_t GB_XOR_HL(SystemContext *ctx)
{
    //encoding: 0b10101110
    /*
        data = read(HL)
        result = A ^ data
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 0
        flags.C = 0
    */
}
uint8_t GB_OR_R(SystemContext *ctx)
{
    //encoding: 0b10110xxx
    /*
        result = A | B
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 0
        flags.C = 0
    */
}
uint8_t GB_OR_N(SystemContext *ctx)
{
    //encoding: 0b11110110
    /*
        n = read(PC++)
        result = A | n
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 0
        flags.C = 0
    */
}
uint8_t GB_OR_HL(SystemContext *ctx)
{
    //encoding: 0b10110110
    /*
        data = read(HL)
        result = A | data
        A = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 0
        flags.C = 0
    */
}
uint8_t GB_CP_R(SystemContext *ctx)
{
    //encoding: 0b10111xxx
    /*
        result, carry_per_bit = A - B
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */
}

uint8_t GB_CP_N(SystemContext *ctx)
{
    //encoding: 0b11111110
    /*
        n = read(PC++)
        result, carry_per_bit = A - n
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */
}

uint8_t GB_CP_HL(SystemContext *ctx)
{
    //encoding: 0b10111110
    /*
        data = read(HL)
        result, carry_per_bit = A - data
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
        flags.C = 1 if carry_per_bit[7] else 0
    */
}

uint8_t GB_INC_R(SystemContext *ctx)
{
    //encoding:0b00xxx100
    /*
        result, carry_per_bit = B + 1
        B = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
    */
}

uint8_t GB_INC_HL(SystemContext *ctx)
{
    //encoding: 0b00110100
    /*
        data = read(HL)
        result, carry_per_bit = data + 1
        write(HL, result)
        flags.Z = 1 if result == 0 else 0
        flags.N = 0
        flags.H = 1 if carry_per_bit[3] else 0
    */
}

uint8_t GB_DEC_R(SystemContext *ctx)
{
    //encoding: 0b00xxx101
    /*
        result, carry_per_bit = B - 1
        B = result
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
    */
}

uint8_t GB_DEC_HL(SystemContext *ctx)
{
    //encoding: 0b00110101
    /*
        data = read(HL)
        result, carry_per_bit = data - 1
        write(HL, result)
        flags.Z = 1 if result == 0 else 0
        flags.N = 1
        flags.H = 1 if carry_per_bit[3] else 0
    */
}

uint8_t GB_DAA(SystemContext *ctx)
{
    //encoding: 0b00100111
    /*
      just flags???
    */
}

uint8_t GB_CPL(SystemContext *ctx)
{
    //encoding:0b00101111
    /*
    A = ~A
    flags.N = 1
    flags.H = 1
    */
}

// 16 BIT ALU INSTRUCTIONS
uint8_t GB_ADD_HL_RR(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_INC_RR(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_DEC_RR(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_ADD_SP_DD(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_LD_HL_SP_PLUS_DD(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
// ROTATE AND SHIFT INSTRUCTIONS
uint8_t GB_RLCA(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RLA(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RRCA(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RRA(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RLC_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RLC_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RL_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RL_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RRC_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RRC_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RR_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RR_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SLA_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SLA_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SWAP_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SWAP_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SRA_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SRA_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SRL_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SRL_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
// SINGLE BIT OPERATIONS
uint8_t GB_BIT_N_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_BIT_N_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SET_N_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SET_N_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RES_N_R(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RES_N_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
// CPU CONTROL INSTRUCTIONS
uint8_t GB_CCF(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_SCF(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_NOP(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_HALT(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_STOP(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_DI(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_EI(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
// JUMP INSTRUCTIONS
uint8_t GB_JP_NN(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_JP_HL(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_JP_F_NN(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_JR_PC_PLUS_DD(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_JR_F_PC_PLUS_DD(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_CALL_NN(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_CALL_F_NN(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RET(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}
uint8_t GB_RET_F(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}

uint8_t GB_RETI(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}

uint8_t GB_RST_N(SystemContext *ctx)
{
    //encoding:
    /*
    
    */
}