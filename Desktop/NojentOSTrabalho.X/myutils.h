#ifndef MYUTILS_H
 #define MYUTILS_H

 #define _CONCAT(a,b) a##b
 #define PORT(x) _CONCAT(PORT,x)
 #define LAT(x) _CONCAT(LAT,x)
 #define TRIS(x) _CONCAT(TRIS,x)

#endif
