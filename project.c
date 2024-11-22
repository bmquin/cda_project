#include "spimcore.h"
// Damon Bullock & Benjamin Quintero
// CDA Final Project
// 11/15/2024
// MySPIM - A MIPS Processor Simulator

/* ALU */
/* 10 Points */
/* Written by Damon Bullock */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    switch(ALUControl) 
    {
      case 0: 
      // Z = A + B
      *ALUResult = A + B;
      break;

      case 1:
      // Z = A - B
      *ALUResult = A - B;
      break;

      case 2:
      // if A < B, Z = 1; otherwise, Z = 0
      if ((signed) A < (signed) B)
      {
        *ALUResult = -1;
      }
      
      else 
      {
        *ALUResult = 1;
      }
      break;

      case 3:
      // if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
      if (A < B)
      {
        *ALUResult = 1;
      }
      
      else
      {
        *ALUResult = 0;
      }

      case 4:
      // Z = A AND B
      *ALUResult = A & B;
      break;
      
      case 5:
      // Z = A OR B
      *ALUResult = A | B;
      break;
      
      case 6:
      // Z = Shift B left by 16 bits
      *ALUresult = B << 16;
      break;
      
      case 7:
      //Z = NOT A
      *ALUResult = ~A;
      break;
    }
    
  if (*ALUResult == 0)
  {
    *Zero == 1;
  }
  
  else
  {
    *Zero == 0;
  }
}

/* instruction fetch */
/* 10 Points */
/* Written by Damon Bullock */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    // checks for word alignment 
    if (PC % 4 == 0)
    {
        *instruction = Mem[PC >> 2];
        return 0;
    }
    // Halt condition if no word alignment
    else
    {
        return 1;
    }
}


/* instruction partition */
/* 10 Points */
/* Written by Benjamin Quintero */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    *op = (instruction >> 26) & 0x3f;

    *r1 = (instruction >> 21) & 0x1f;

    *r2 = (instruction >> 16) & 0x1f;

    *r3 = (instruction >> 11) & 0x1f;

    *funct = instruction & 0x1f;

    *offset = instruction & 0xFFFF;

    *jsec = instruction & 0x3FFFFFF;
}


/* instruction decode */
/* 15 Points */
/* Written by Benjamin Quintero */
int instruction_decode(unsigned op,struct_controls *controls)
{
    controls->RegDst = 0;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 0;
    controls->ALUOp = 0;
    controls->MemWrite = 0;
    controls->ALUSrc = 0;
    controls->RegWrite = 0;

    if(op == 0){
        controls->RegDst = 1;
        controls->ALUOp = 7;
        controls->RegWrite = 1;
    }
    else if(op == 2 ){
        controls->Jump=1;
    }
    else if(op == 4){
        controls->RegDst = 2;
        controls->Branch = 1;
        controls-> MemtoReg = 2;
        controls->ALUOp = 1;
    }
    else if(op == 8){
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    }
    else if(op == 10){
        controls->RegDst = 1;
        controls->ALUOp = 2;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    }
    else if(op == 11){
        controls->RegDst = 1;
        controls->ALUOp = 3;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    }
    else if(op == 15){
        controls->ALUOp = 6;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    }
    else if(op == 35){
        controls->MemRead = 1;
        controls->MemtoReg = 1;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    }
    else if(op == 43){
        controls->RegWrite = 2;
        controls->MemtoReg = 2;
        controls->MemWrite = 1;
        controls->ALUSrc = 1;
    }
    else{
        return 1;
    }

    return 0;

}


/* Read Register */
/* 5 Points */
/* Written by Damon Bullock */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    // Writes the registers r1 and r2 (Addressed by Reg into data1 and data2)
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
/* Written by Damon Bullock */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    // checks if sgn but is 1
    if ((offset >> 15) == 1)
        *extended_value = offset | 0xffff0000;
    else
        *extended_value = offset | 0x0000ffff;
}

/* ALU operations */
/* 10 Points */
/* Written by Benjamin Quintero */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    if(ALUSrc == 1) {
        data2 = extended_value;
    }

    if(ALUOp == 7) {
        if(funct == 32) {
            ALUOp = 0;
        }
        else if(funct == 34) {
            ALUOp = 1;
        }
        else if(funct == 42) {
            ALUOp = 2;
        }
        else if(funct == 43) {
            ALUOp = 3;
        }
        else if(funct == 36) {
            ALUOp = 4;
        }
        else if(funct == 37) {
            ALUOp = 5;
        }
        else if(funct == 6) {
            ALUOp = 6;
        }
        else if(funct == 39) {
            ALUOp = 7;
        }
        else {
            return 1;
        }

        ALU(data1,data2, ALUOp, ALUresult, Zero);

    }

    else {
        ALU(data1,data2, ALUOp, ALUresult, Zero);
    }

    return 0;
}


/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

