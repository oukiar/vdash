#pragma once
#ifndef _XBOX
#include <d3d9.h>
#include <d3dx9tex.h>
#include <d3dx9math.h>
#include <xnamath.h>
#include <Windows.h>
#else
#include <xtl.h>
#endif
#ifdef __cplusplus

template<typename T> class Singleton
 {
   public:
     static T& Instance()
     {
         static T theSingleInstance; // suppose que T a un constructeur par défaut
         return theSingleInstance;
     }
 };

#endif