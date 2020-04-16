#if defined MVector
  #endinput
#endif
#define MVector
#define type_int 1
#define type_float 2
#define type_bool 3
#define type_string 4
native vector:Vector(type);
native Push_Back(vector: vec, set = 0, {Float,_}:value = 0.0);
native Pop_Back(vector: vec);
native At(vector: vec, index, set = 0, {Float,_}:value = 0.0);
native Float:AtFloat(vector: vec, index, set = 0, {Float,_}:value = 0.0);
native Clear(vector: vec);
native Size(vector: vec);
native Erase(vector: vec, start, end = -1);
native Free(vector: vec);
native MVector_Free();
native AtString(vector: vec, index, set = 0, value[], len = sizeof value);
native Push_BackString(vector: vec, set = 0, value[]);                                                                   