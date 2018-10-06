/**************************************************
*                                                 *
*  @file     Global.cpp                           *
*  @brief    Global variables source file         *
*                                                 *
*                                                 *
*  @author   atlanswer                            *
*  @email    atlanswer@gmail.com                  *
*  @version  Beta-2                               *
*  @date     2018-10-06                           *
*                                                 *
***************************************************/

#include "../inc/Timer.hpp"

//----------------------------
// Global variables
//----------------------------

//! Timer
decisecond timeDelta;

/** 
 * @brief status enum type
 */
status action;

/**
 * @brief THread control
 */
//! Mutex
mutex mut;
//! Condition variable
condition_variable cvar;