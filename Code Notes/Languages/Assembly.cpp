//////////////////////////////////////////////////////////////////////////////
//ASSEMBLY LANGUAGE
//////////////////////////////////////////////////////////////////////////////
/*

 ===========================================================================
|       |                                      Stack    Base                |
|       | Accum.   Counter   Data     Base    Pointer  Pointer  Src   Dest  |
|=======|===================================================================|
| 16bit |   AX       CX       DX       BX       SP       BP     SI     DI   |
|       | [AL/AH]  [CL/CH]  [DL/DH]  [BL/BH]                                |
|-------|-------------------------------------------------------------------|
| 32bit |   EAX      ECX      EDX      EBX      ESP     EBP     ESI   EDI   |
|       |                                                                   |
|-------|-------------------------------------------------------------------|
| 64bit |   RAX      RCX      RDX      RBX      RSP     RBP     RSI   RDI   |
|       |                                                                   |
 ===========================================================================

-----------------------------------------------------------------------------
 GENERAL PURPOSE REGISTERS
-----------------------------------------------------------------------------

ESP: STACK POINTER REGISTER
• Always points to the top of the stack
• Minus from register address moves down stack, plus moves above top

EBP: STACK BASE POINTER REGISTER
• Pointer to data on the stack. 
• Local variables are accessed via a negative offset from top
• Minus from register address moves down stack, plus moves above top
    
EAX: ACCUMULATOR REGISTER
• Primarly used for mathematical operations
     
EBX: BASE REGISTER
• Pointer to data in the DS segment

ECX: COUNTER REGISTER
• Used in shift/rotate instructions
• Counter for string and loop operations
     
EDX: DATA REGISTER
• Used in arithmetic operations and I/O operations
     
ESI: SOURCE REGISTER
• Used as a pointer to a source in stream operations
     
EDI: DESTINATION REGISTER
• Used as a pointer to a destination in stream operations

-----------------------------------------------------------------------------
SEGMENT REGISTERS
-----------------------------------------------------------------------------

STACK SEGMENT (SS): Pointer to the stack
CODE SEGMENT (CS): Pointer to the code
DATA SEGMENT (DS): Pointer to the data
EXTRA SEGMENT (ES): Pointer to extra data
F SEGMENT (FS): Pointer to more extra data
G SEGMENT (GS): Pointer to even more data

-----------------------------------------------------------------------------
OTHER REGISTERS
-----------------------------------------------------------------------------

FLAGS REGISTER
• reports on the status of the program being executed
• allow limited control of the processor

IP (INTRUCTION POINTER) REGISTER:
• Contains a 32-bit pointer to the next intruction to be executed

*/
//////////////////////////////////////////////////////////////////////////////
//MNEMONICS
//////////////////////////////////////////////////////////////////////////////

nop //no operation; same opcode (0x90) as xchgl %eax, %eax.

[ebp-16h] //The memory address as an offset from the epb register (h = hex)
dword ptr [ ] //The 32-bit value stored in the address in the square brackets

al //maps to the lowest byte of the eax register

hlt //halts the processor


//===========================================================================
// MOVING
//===========================================================================

mov eax,dword ptr [ebp-20h] //move epb-20h to eax register
mov dword ptr [ebp-20h],eax //move value in eax to ebp-20h
mov dword ptr [ebp-20h],0   //move value of 0 into epb-20h

xchg dest,src //swaps src operand with dest operand

lea dest,src //load effective address; copys address in src into dest

//MOVE ZERO EXTEND
//pads remaining bits not given by src with 0s
//used for copying small vars to bigger types
movz src, dest
movzx dest, src

//MOVE SIGN EXTEND
//pads remaining bits not given by src with src's sign
//used for copying a signed small var to to bigger types
movs src,dest
movsx dest,src

//MOVE SINGLE BYTE/WORD
//copies 1 byte (2 bytes for movsw) from location in esi to edi
//if direction flag is cleared, esi/edi are incremented after operation
//else decremented until reaching end of counter in ecx
mov esi,mystring    //loads address of mystring into esi
mov edi,mystring2   //loads address of mystring into edi
cld                 //clear direction flag (forward)
mov ecx,6           //move six into ecx
rep movsb           //copy six times

 
//===========================================================================
// ARITHMATIC
//===========================================================================

sub esp,44h //subtract 68bytes from esp; allocates 68b on stack after epb

add eax,2 //add 2 to whatever is in eax

xor eax,eax  //xor itself makes value in eax 0

and eax,5 //bitwise & between eax and 5

mul 3 //multiplies eax by 3
imul 3 //multiplies eax by 3 (argument is always signed)

div 2 //divides eax by 2
idiv 2 //divides eax by 2 (argument is always signed)

inc eax //eax++
dec eax //eax--

//===========================================================================
// STACK INSTRUCTIONS
//===========================================================================

//NOTE: If there's a push without a pop, it means reserving space for
//      automatic vars on the stack

esp-4 | ebp+4 //data above top of stack
esp+4 | ebp-4 //data below top of stack

mov ebp, esp //Creates a stack frame

push ebx //decrements stack pointer (add space to stack) and loads data in
sub esp, 4 //adds 4 bytes to stack; same as a single push

pop ebx //increments stack pointer (remove from stack) into ebx register
add esp, 4 //adds 4 bytes to stack; same as a single pop

pushf //decrements stack pointer and loads with contents of the flag register
popf //loads the flag register with the stack pointer then increments it

pusha  //pushes all general registers onto stack in order
popa   //EAX,ECX,EDX,EBX,ESP,EBP,ESI,EDI. Pops in reverse order

ret 5 //loads next value on stack into EIP and pops stack 5 times
ret   //loads next value on stack into EIP and don't pop any value

enter 2 //creates a stack frame with the specified amount of space allocated

leave //destroys the current stack frame and restores the previous

//////////////////////////////////////////////////////////////////////////////
// CONDITIONAL LOGIC/FLOW
//////////////////////////////////////////////////////////////////////////////

//Assembly tests using the opposite to C++
//When jumping, loads EIP (instruction pointer) with the jump address
jne: !=    replaces    ==
jnz: !=    replaces    ==
je:  ==    replaces    !=
jz:  ==    replaces    !=
jg:  >     replaces    <=  (signed vars)
ja:  >     replaces    <=  (unsigned vars)
jl:  <     replaces    >=  (signed vars)
jb:  <     replaces    >=  (unsigned vars)
jle: <=    replaces    >   (signed vars)
jbe: <=    replaces    >   (unsigned vars)
jge: >=    replaces    <   (signed vars)
jae: >=    replaces    <   (unsigned vars)

jmp 0A7126Dh //jump to the memory location
jo 0A7126Dh //jump on overflow; jump if overflow bit is set
jno 0A7126Dh //jump on not overflow; jump if overflow bit isn't set

test arg1,arg2 //uses bitwise &, sets flags but doesn't store result
cmp arg1,arg2 //uses bitwise -, sets flags but doesn't store result

//LOOP INSTRUCTION
//decrements counter in ECX and jumps to the address unless counter == 0
mov ecx, 5
start_loop:
    //code here executed five times
loop start_loop

loope   //loop if equal
loopne  //loop if not equal
loopnz  //loop if not zero
loopz   //loop if zero


//===========================================================================
//CONDITIONAL EXAMPLES
//===========================================================================

//IF-STATEMENTS: if(myInt < 0)
cmp dword ptr [myInt],0 //compare myInt to 0 and store result in EFLAGS reg
jge main+1Dh (0A7126Dh) //move to address 00A7126D if >=

//IF-STATEMENTS: if(myInt == 0)
cmp dword ptr [myInt],0 //compare myInt to 0 and store result in EFLAGS reg
jne main+1Fh (12126Fh) //move to 0012126F if !=

//IF-STATEMENTS: if(myInt != 0)
cmp dword ptr [myInt],0 //compare myInt to 0 and store result in EFLAGS reg
je  main+2Eh (12127Eh) //move to 0012127E if ==

//IF-STATEMENTS: if((myInt >= 7) && (myInt <= 13))
cmp dword ptr [myInt],7  
jl  main+25h (0E61275h) //jump to end if first condition isn't true
cmp dword ptr [argc],0Dh  
jg  main+25h (0E61275h) //jump to end if second condition isn't true

//IF-STATEMENTS: if(myInt || (!myInt) || (myInt == 1))
cmp   dword ptr [argc],0 
jne   main+37h (0E61287h) //jump to body of statement
cmp   dword ptr [argc],0  
je    main+37h (0E61287h) //jump to body of statement
cmp   dword ptr [argc],45h  
jne   main+3Eh (0E6128Eh) //jump to end of statement

//IF-THEN-ELSE
if(myInt == 0)
cmp dword ptr [myInt],0  
jne main+1Fh (12126Fh) //jump to else if
{
    jmp main+35h (121285h)  
}
else if(myInt != 2)
cmp dword ptr [myInt],2  
je  main+2Eh (12127Eh)  
{   
    //no jump for the last else-if
}
else
jmp main+35h (121285h) //jump to end of statement
{
}

//TERNARY OPERATOR
int myResult = (myInt > 2) ? 3 : 7;
xor eax,eax  //xor itself makes value in eax 0
cmp dword ptr [myInt],2 //store result in EFLAGS
setle al //set less equal; if cmp was true, sets al to 1, else 0
lea eax,[eax*4+3] //depending on 0/1 set will give 3/7
mov dword ptr [iLocal],eax

//TERNARY OPERATOR WITH VARIABLES
int three = 3;
int seven = 7;
int myResult = (myInt > 2) ? three : seven;
00CF1627  cmp  dword ptr [myInt],2  //(myInt > 2)
00CF162B  jle  main+25h (0CF1635h) //jump to [1]
00CF162D  mov  eax,dword ptr [three]
00CF1630  mov  dword ptr [ebp-50h],eax
00CF1633  jmp  main+2Bh (0CF163Bh) //jump to [2]
00CF1635  mov  ecx,dword ptr [seven] //[1]
00CF1638  mov  dword ptr [ebp-50h],ecx
00CF163B  mov  edx,dword ptr [ebp-50h] //[2]
00CF163E  mov  dword ptr [myResult],edx

//SWITCH STATEMENT
switch(myInt)
mov  eax,dword ptr [myInt] //move myInt into eax
mov  dword ptr [ebp-48h],eax //move eax onto stack
cmp  dword ptr [ebp-48h],1 //compare with value 1
je   main+2Ah (0C6163Ah) //if equals 1, jump to case 1
cmp  dword ptr [ebp-48h],3 //compare with value 3
je   main+31h (0C61641h) //if equals 3, jump to case 3
jmp  main+43h (0C61653h) //else jump to default
{
case 1:
    iLocal = 6;
    mov dword ptr [iLocal],6
case 3:
    iLocal = 7;
    mov dword ptr [iLocal],7
    break;
    jmp main+4Ah (0C6165Ah) //jump to end
default:
    iLocal = 9;
    mov dword ptr [iLocal],9
    break;
 }

//CONTINUOUS SWITCH STATEMENT (0,1,2...)
switch(myInt)
mov  eax,dword ptr [myInt] //move myInt into eax
mov  dword ptr [ebp-48h],eax //move eax onto stack
cmp  dword ptr [ebp-48h],3 //compare with largest switch value
ja   $LN1+7 (311298h) //jump to end if > 3
mov  ecx,dword ptr [ebp-48h] //move into ecx

//[ecx*4+003112A4h] without symbols
//value in ecx (myInt) * 4bytes gives the address offset from 003112A4
//address used is after switch statement and is offset backwards
jmp  dword ptr  (3112A4h)[ecx*4]

{
case 0:
    iLocal = 4;
    mov dword ptr [iLocal],4  
    break;
    jmp $LN1+7 (311298h) //jump to end
case 1:
    iLocal = 5;
    mov dword ptr [iLocal],5  
    break;
    jmp $LN1+7 (311298h) //jump to end
case 2:
    iLocal = 6;
    mov dword ptr [iLocal],6  
    break;
    jmp $LN1+7 (311298h) //jump to end
case 3:
    iLocal = 7;
    mov dword ptr [iLocal],7  
    break;
}

//WHILE LOOP
while(true)
mov  eax,1 //[1]
test eax,eax  
je   main+14h (2C1254h) //exit loop
{
    //inside loop
}
jmp main+9 (2C1249h) //jump to [1]


//FOR LOOP
for(int i = 0; i < 5; ++i)
mov  dword ptr [i],0  
jmp  main+1Bh (0E3125Bh) //jump to [1]
mov  eax,dword ptr [i] //[2]
add  eax,1  
mov  dword ptr [i],eax  
cmp  dword ptr [i],5  //[1]
jge  main+23h (0E31263h) //jump to end of loop (exit)
{
    //inside loop
}
jmp  main+12h (0E31252h) //jump to [2]


//////////////////////////////////////////////////////////////////////////////
//CALLING CONVENTIONS/FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
/*
=========================================================================
CDECL
=========================================================================
• ARGUMENTS: passed on stack in right-to-left order 
• RETURN: passed in eax
• Calling function cleans the stack; allows variadic functions
• Assembler/Linker cannot determine if incorrect number of arguments are used
• Functions prepended with _ in assembly

/*-------------------------------------------------------------
CALLING FUNCTION
-------------------------------------------------------------*/
x = MyFunction(2, 3);

push 3
push 2
call _MyFunction
add esp, 8

/*-------------------------------------------------------------
FUNCTION BODY
-------------------------------------------------------------*/
_cdecl int MyFunction(int a, int b)
{
  return a + b;
}

_MyFunction:
push ebp
mov ebp, esp
mov eax, [ebp + 8]
mov edx, [ebp + 12]
add eax, edx
pop ebp
ret

/*
=========================================================================
STDCALL
=========================================================================
• ARGUMENTS: passed on stack in right-to-left order 
• RETURN: passed in eax
• Called function cleans the stack; doesn't allow variadic functions
• Ret has optional argument indicating how many bytes to pop off the stack
• Names are prepended with _ and ended with @x (bytes passed on the stack)

/*-------------------------------------------------------------
CALLING FUNCTION
-------------------------------------------------------------*/
x = MyFunction(2, 3);
push 3
push 2
call _MyFunction@8

/*-------------------------------------------------------------
FUNCTION BODY
-------------------------------------------------------------*/
_stdcall int MyFunction(int a, int b)
{
   return a + b;
}

:_MyFunction@8
push ebp
mov ebp, esp
mov eax, [ebp + 8]
mov edx, [ebp + 12]
add eax, edx
pop ebp
ret 8

/*
=========================================================================
FASTCALL
=========================================================================
• The first 2-3 32-bit (or smaller) arguments are passed in registers 
  eax,ecx,edx. Additional arguments/arguments larger than 4 bytes are 
  passed via stack (right-left order)
• The calling function cleans the stack
• Names are prepended with @ and ended with @x (bytes passed on the stack)

/*-------------------------------------------------------------
CALLING FUNCTION
-------------------------------------------------------------*/
x = MyFunction(2, 3);

mov eax, 2
mov edx, 3
call @MyFunction@8

/*-------------------------------------------------------------
FUNCTION BODY
-------------------------------------------------------------*/
_fastcall int MyFunction(int a, int b)
{
   return a + b;
}

:@MyFunction@8
push ebp
mov ebp, esp //many compilers create a stack frame even if it isn't used
add eax, edx 
pop ebp
ret

/*
=========================================================================
THISCALL
=========================================================================
ARGUMENTS: passed right-to-left on stack; this pointer passed in ecx
RETURN: passed in eax

/*-------------------------------------------------------------
CALLING FUNCTION
-------------------------------------------------------------*/
MyObj.MyFunction(a, b, c);

mov ecx, MyObj
push c
push b
push a
call ?MyFunction@MyClass@@QAEHH@Z