// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class, 3D math helper
// 6/5/2012 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2012-06-05 - add 3D math helper file to DMP6 example sketch

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef _HELPER_3DMATH_H_
#define _HELPER_3DMATH_H_

#include <math.h>  // 🔥 THÊM DÒNG NÀY ĐỂ FIX sqrtf()
#include <stdint.h>

typedef struct {
    float w, x, y, z;
} Quaternion;

// Hàm khởi tạo
static inline Quaternion Quaternion_Init(float nw, float nx, float ny, float nz) {
    Quaternion q = {nw, nx, ny, nz};
    return q;
}

// Phép nhân quaternion
static inline Quaternion Quaternion_Product(Quaternion q1, Quaternion q2) {
    return Quaternion_Init(
        q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z,
        q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
        q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
        q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w
    );
}

// Liên hợp quaternion
static inline Quaternion Quaternion_Conjugate(Quaternion q) {
    return Quaternion_Init(q.w, -q.x, -q.y, -q.z);
}

// Độ lớn của quaternion
static inline float Quaternion_Magnitude(Quaternion q) {
    return sqrtf(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
}

// Chuẩn hóa quaternion
static inline Quaternion Quaternion_Normalized(Quaternion q) {
    float mag = Quaternion_Magnitude(q);
    return Quaternion_Init(q.w/mag, q.x/mag, q.y/mag, q.z/mag);
}

// -------------------- VectorInt16 --------------------
typedef struct {
    int16_t x, y, z;
} VectorInt16;

// Khởi tạo vector
static inline VectorInt16 VectorInt16_Init(int16_t nx, int16_t ny, int16_t nz) {
    VectorInt16 v = {nx, ny, nz};
    return v;
}

// Độ lớn của vector
static inline float VectorInt16_Magnitude(VectorInt16 v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

// Chuẩn hóa vector
static inline VectorInt16 VectorInt16_Normalized(VectorInt16 v) {
    float mag = VectorInt16_Magnitude(v);
    return VectorInt16_Init(v.x/mag, v.y/mag, v.z/mag);
}

// -------------------- VectorFloat --------------------
typedef struct {
    float x, y, z;
} VectorFloat;

// Khởi tạo vector float
static inline VectorFloat VectorFloat_Init(float nx, float ny, float nz) {
    VectorFloat v = {nx, ny, nz};
    return v;
}

// Độ lớn của vector float
static inline float VectorFloat_Magnitude(VectorFloat v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

// Chuẩn hóa vector float
static inline VectorFloat VectorFloat_Normalized(VectorFloat v) {
    float mag = VectorFloat_Magnitude(v);
    return VectorFloat_Init(v.x/mag, v.y/mag, v.z/mag);
}

#endif /* _HELPER_3DMATH_H_ */
