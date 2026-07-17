#pragma once
#include"MCSL_Fun.h"
#include"MCSL.h"
#include"kinematics.h"
#include"EcmDriver.h"
#include<iostream>

int InitSystem(double ratio[], double Pitch[], int pusle[], double HLimit[], double LLimit[], int dirReverse[], int wAxisMap[]);
void CloseSystem();