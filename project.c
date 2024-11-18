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
      case 000: 
      // Z = A + B
      *ALUResult = A + B;
      break;

      case 001:
      // Z = A - B
      *ALUResult = A - B;
      break;

      case 010:
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

      case 011:
      // if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
      if (A < B)
      {
        *ALUResult = 1;
      }
      
      else
      {
        *ALUResult = 0;
      }

      case 100:
      // Z = A AND B
      *ALUResult = A & B;
      break;
      
      case 101:
      // Z = A OR B
      *ALUResult = A | B;
      break;
      
      case 110:
      // Z = Shift B left by 16 bits
      B << 16;
      break;
      
      case 111:
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
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

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

