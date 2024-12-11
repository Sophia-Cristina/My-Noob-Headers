#pragma once

#ifndef YSXELECDEVICESCONSTS_H
#define YSXELECDEVICESCONSTS_H

// #####################
// ####### By Sophia Cristina
// ####### Constants found in electrical devices, like NTSC frame rate.
// #####################

// #################################################
/* REFERENCES:
 [1] 
*/

// #################################################
// ############## TV ##############

#define NTSCFPS 29.97002997 // NTSC FPS is 30/1.001, people normally round to 29.97
#define NTSCSCANLIN 525 // NTSC uses two field, divide by two if you need
#define NTSCSCANVISIBLE 486 // The NTSC scan lines that are visible and not obfuscated by Vertical Blanking


// #################################################
// #################################################
// #################################################
#endif // SCPARSE_
