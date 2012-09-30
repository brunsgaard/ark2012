/*******************************************************
 * RECURSIVE
 *******************************************************/

/*

   program =

   line = [label | statement] { comment } ;

   label = identifier ":" ;
   statement = rtype | itype | jtype ;
   comment = "#" {char whitespace} ;

   register = "$", ["zero" | (char, [char | digit])] ;

   rinstr = "add" | "sub" | "and" | "or" | "slt" ;
   iinstr = "lw" | "sw" ;
   jinstr = "beq" | "j" ;

   rtype = rinstr, register, ",", register, ",", register ;
   itype = iinstr, register, ",", register, ",", immediate ;
   jtype = jinstr, address ;

*/


#include <stdio.h>
